using System;
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
using System.IO.Ports;
using System.Threading;
namespace SerialMonitorTest01
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        Boolean connectionStatus;
        String[] ports, motorPWM;
        String incomingLine;
        SerialPort serial;
        int numberOfPorts, cutLength = 6*4, decrease = 10, increase = 10;


        public MainWindow()
        {
            InitializeComponent();
          
            this.connectionStatus = false;
            this.serial = new SerialPort();

            this.refreshComPorts();
            this.ClearPWM();
        }

        #region ComPortManaging
        private void refreshComPorts()
        {
            this.comboPorts.Items.Clear();
            this.ports = SerialPort.GetPortNames();
            Console.WriteLine("Number of Ports Available: " + this.numberOfPorts);
            this.numberOfPorts = ports.Length;
            for (int i = 0; i < numberOfPorts; i++)
            {
                this.comboPorts.Items.Insert(i, ports[i]);
            }

            this.txtBaudRate.Text = "115200";
            this.btnDisconnect.IsEnabled = false;
            this.lblStatus.Content = "No ports online.";
        }

        private void btnRefresh_Click(object sender, RoutedEventArgs e)
        {
            this.refreshComPorts();
        }

        private void btnDisconnect_Clicked(object sender, RoutedEventArgs e)
        {
            this.serial.Close();
            this.connectionStatus = false;

            this.txtBaudRate.Text = "115200";
            this.btnDisconnect.IsEnabled = false;
            this.btnConnect.IsEnabled = true;
            this.btnRefresh.IsEnabled = true;
            this.lblStatus.Content = "No ports online.";
        }

        private void btnConnect_Clicked(object sender, RoutedEventArgs e)
        {

            if (comboPorts.Text.Length > 0 && (txtBaudRate.Text.Equals("115200") || txtBaudRate.Text.Equals("9600")))
            {
                this.serial.PortName = comboPorts.Text;
                this.serial.BaudRate = int.Parse(txtBaudRate.Text);
                // connecting empty event to the actual method
                serial.DataReceived += serial_DataReceived;
                if (!this.connectionStatus)
                {
                    this.serial.Open();
                    this.btnDisconnect.IsEnabled = true;
                    this.btnConnect.IsEnabled = false;
                    this.connectionStatus = true;
                    this.btnRefresh.IsEnabled = false;
                    this.lblStatus.Content = serial.PortName + " online";
                }
                else
                {
                    MessageBox.Show("Convention doesn't hold.");
                }
                
            }
            else
            {
                MessageBox.Show("Check your port or baud rate.");
            }

        }

        #endregion

        #region ComPortOpen

        #region DataParse
        private void serial_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;
            String indata = (String) serial.ReadExisting();
            Console.WriteLine(indata);
            this.getLine(indata);
        }

        private void getLine(String indata)
        {
            int mLocation = indata.IndexOf('M');
            if ((indata.Length - mLocation) < cutLength)
            {
                return;
            }
            this.incomingLine = indata.Substring(mLocation, this.cutLength);
            //Console.WriteLine(this.incomingLine);
            this.parse();
        }
        private void parse()
        {
            this.motorPWM = new String[4];
            for (int i = 0; i < 4; i++)
            {
                
                motorPWM[i] = this.incomingLine.Substring(1 + i * 6, 5);
               // Console.WriteLine(motorPWM[i]);
                if (motorPWM[i].Substring(0, 1).Equals("1"))
                {
                    Dispatcher.Invoke(() =>
                    {
                        this.txtMotor1.Text = motorPWM[i].Substring(1, 4); ;
                    });
                }
                else if(motorPWM[i].Substring(0, 1).Equals("2"))
                {
                    Dispatcher.Invoke(() =>
                    {
                        this.txtMotor2.Text = motorPWM[i].Substring(1, 4); ;
                    });
                }
                else if(motorPWM[i].Substring(0, 1).Equals("3"))
                {
                    Dispatcher.Invoke(() =>
                    {
                        this.txtMotor3.Text = motorPWM[i].Substring(1, 4); ;
                    });

                }
                else if (motorPWM[i].Substring(0, 1).Equals("4"))
                {
                    Dispatcher.Invoke(() =>
                    {
                        this.txtMotor4.Text = motorPWM[i].Substring(1, 4); ;
                    });
                }
                else
                {

                }
            }



        }
        #endregion

        #region DataSend
        private void sendPWM(int motor, int PWM)
        {
            String result, index, content;
            index = motor.ToString();
            content = PWM.ToString();
            result = index + content;
            
            this.serial.Write(result);
            Console.WriteLine(result);

            this.serial.WriteLine(String.Format("{0}{1}", index, content));
            Console.WriteLine(String.Format("{0}{1}", index, content));
            
        }

        #endregion

        #endregion

        #region Misc
        private void btnClearPWM_Click(object sender, RoutedEventArgs e)
        {
            this.ClearPWM();
        }

        private void ClearPWM()
        {
            this.txtMotor1.Text = "";
            this.txtMotor2.Text = "";
            this.txtMotor3.Text = "";
            this.txtMotor4.Text = "";
        }
        #endregion

        #region ChangedEvents

        private void comboPorts_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }

        private void txtSend_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        private void txtBaudRate_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        private void txtMotor1_TextChanged(object sender, TextChangedEventArgs e)
        {

        }
        private void txtMotor2_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        private void txtMotor3_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        private void txtMotor4_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        #endregion

        #region DecreaseButtons
        private void btnDecreaseMotor1_Click(object sender, RoutedEventArgs e)
        {
            int pwm = Convert.ToInt32(this.txtMotor1.Text) - this.decrease;
            this.sendPWM(1, pwm);
        }

        private void btnDecreaseMotor2_Click(object sender, RoutedEventArgs e)
        {
            int pwm = Convert.ToInt32(this.txtMotor2.Text) - this.decrease;
            this.sendPWM(2, pwm);
        }

        private void btnDecreaseMotor3_Click(object sender, RoutedEventArgs e)
        {
            int pwm = Convert.ToInt32(this.txtMotor3.Text) - this.decrease;
            this.sendPWM(3, pwm);
        }

        private void btnDecreaseMotor4_Click(object sender, RoutedEventArgs e)
        {
            int pwm = Convert.ToInt32(this.txtMotor4.Text) - this.decrease;
            this.sendPWM(4, pwm);
        }

        #endregion

        #region IncreaseButtons
        private void btnIncreaseMotor1_Click(object sender, RoutedEventArgs e)
        {
            int pwm = Convert.ToInt32(this.txtMotor1.Text) + this.increase;
            this.sendPWM(1, pwm);
        }

        private void btnIncreaseMotor2_Click(object sender, RoutedEventArgs e)
        {
            int pwm = Convert.ToInt32(this.txtMotor2.Text) + this.increase;
            this.sendPWM(2, pwm);
        }

        private void btnIncreaseMotor3_Click(object sender, RoutedEventArgs e)
        {
            int pwm = Convert.ToInt32(this.txtMotor3.Text) + this.increase;
            this.sendPWM(3, pwm);
        }

        private void btnIncreaseMotor4_Click(object sender, RoutedEventArgs e)
        {
            int pwm = Convert.ToInt32(this.txtMotor4.Text) + this.increase;
            this.sendPWM(4, pwm);
        }
        #endregion

        #region sliders

        #endregion


    }
}
