using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Microsoft.Kinect;



namespace Kinect001
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        #region Member Variables
        private KinectSensor _Kinect;
        #endregion Member Variables

        #region Constructor
        public MainWindow()
        {
            InitializeComponent();
            this.Loaded += (s, e) => { DiscoverKinectSensor(); };
            this.Unloaded += (s, e) => { this.Kinect = null; };
            Console.WriteLine("Form Loading....");
        }
        #endregion Constructor

        #region Methods
        private void DiscoverKinectSensor()
        {
            Console.WriteLine("Detecting Kinect Sensor...");
            KinectSensor.KinectSensors.StatusChanged += KinectSensors_StatusChanged;
            if (this.Kinect == null)
            {
                Console.WriteLine("Kinect Sensor Null");
                this.Kinect = KinectSensor.KinectSensors.FirstOrDefault(x => x.Status == KinectStatus.Connected);
            }
        }

        private void KinectSensors_StatusChanged(object sender, StatusChangedEventArgs e)
        {
            Console.WriteLine("Kinect sensor status: " + e.Status);
                      
            switch (e.Status)
            {
                case KinectStatus.Connected:
                    if (this.Kinect == null)
                    {
                        this.Kinect = e.Sensor;
                    }
                    break;

                case KinectStatus.Disconnected:
                    if (this.Kinect == e.Sensor)
                    {
                        this.Kinect = null;
                        this.Kinect = KinectSensor.KinectSensors.FirstOrDefault(x => x.Status == KinectStatus.Connected);

                        if (this.Kinect == null)
                        {
                            // Notify the user that the sensor is disconnected
                            Console.WriteLine("Kinect sensor is disconnected.");
                        }
                    }
                    break;
                //Handle all other statuses according to needs
            }
        }
        #endregion Methods

        #region Properties
        public KinectSensor Kinect
        {
            get { return this._Kinect; }

            set
            {
                if (this._Kinect != value)
                {
                    if (this._Kinect != null)
                    {
                        Console.WriteLine("Uninitializing stream...");
                        UninitializeKinectSensor(this._Kinect);
                        this._Kinect = null;
                        Console.WriteLine("Stream Uninitialized");
                    }

                    if (value != null && value.Status == KinectStatus.Connected)
                    {
                        Console.WriteLine("Initializing stream...");
                        this._Kinect = value;
                        InitializeKinectSensor(this._Kinect);
                        Console.WriteLine("Stream Initialized");
                    }
                }
            }


        }
        #endregion Properties

        private void InitializeKinectSensor(KinectSensor sensor)
        {
            if (sensor != null)
            {
                sensor.Stop(); //dont know why but somehow the sensor has not stopped during uninitialization
                sensor.ColorStream.Enable();
                sensor.ColorFrameReady += Kinect_ColorFrameReady;
                sensor.Start();
               
            }
        }

        private void UninitializeKinectSensor(KinectSensor sensor)
        {
            if (sensor != null)
            {
                sensor.Stop();
                sensor.ColorFrameReady -= Kinect_ColorFrameReady;
            }
        }

        private void Kinect_ColorFrameReady(object sender, ColorImageFrameReadyEventArgs e)
        {
            using (ColorImageFrame frame = e.OpenColorImageFrame())
            {
                if (frame != null)
                {
                    byte[] pixelData = new byte[frame.PixelDataLength];
                    frame.CopyPixelDataTo(pixelData);

                    ColorImageElement.Source = BitmapImage.Create(frame.Width, frame.Height, 96, 96, PixelFormats.Bgr32, null, pixelData, frame.Width * frame.BytesPerPixel);
                 
                }
            }
        }

    }
}
