using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;


namespace SerialMonitorTest03.ControllerFolder
{
    class SimpleController 
    {

        private MainWindow _mainWindow;
        private DataModel _data;
        private USB _usb;
        private Boolean isConnected;

        public SimpleController(MainWindow sender)
        {
            this._data = new DataModel();
            this.isConnected = false;
            this._mainWindow = sender;
            this._usb = new USB(this._mainWindow, this._data);
            this._mainWindow.txtIncraseCalInterval.Text = "10";
            this._mainWindow.txtDecraseCalInterval.Text = "10";
            this.refreshComports();
            checkConvention();
        }
                
        private void checkConvention()
        {
            this._mainWindow.btnConnect.IsEnabled = true;
            if (this.isConnected)
            {
                this._mainWindow.lblStatus.Content = this._usb.getPortName() + " online";
                this._mainWindow.btnRefresh.IsEnabled = false;
                this._mainWindow.btnConnect.Content = "Disconnect";
                this._mainWindow.btnClearPWM.IsEnabled = true;
                this._mainWindow.btnStop.IsEnabled = true;
                this._mainWindow.btnDecreaseAll.IsEnabled = true;
                this._mainWindow.btnDecreaseMotor1.IsEnabled = true;
                this._mainWindow.btnDecreaseMotor2.IsEnabled = true;
                this._mainWindow.btnDecreaseMotor3.IsEnabled = true;
                this._mainWindow.btnDecreaseMotor4.IsEnabled = true;
                this._mainWindow.btnIncreaseAll.IsEnabled = true;
                this._mainWindow.btnIncreaseMotor1.IsEnabled = true;
                this._mainWindow.btnIncreaseMotor2.IsEnabled = true;
                this._mainWindow.btnIncreaseMotor3.IsEnabled = true;
                this._mainWindow.btnIncreaseMotor4.IsEnabled = true;
                
            }
            else
            {
                this._mainWindow.lblStatus.Content = "No ports online";
                this._mainWindow.btnRefresh.IsEnabled = true;
                this._mainWindow.btnConnect.Content = "Connect";
                this._mainWindow.btnClearPWM.IsEnabled = false;
                this._mainWindow.btnStop.IsEnabled = false;
                this._mainWindow.btnDecreaseAll.IsEnabled = false;
                this._mainWindow.btnDecreaseMotor1.IsEnabled = false;
                this._mainWindow.btnDecreaseMotor2.IsEnabled = false;
                this._mainWindow.btnDecreaseMotor3.IsEnabled = false;
                this._mainWindow.btnDecreaseMotor4.IsEnabled = false;
                this._mainWindow.btnIncreaseAll.IsEnabled = false;
                this._mainWindow.btnIncreaseMotor1.IsEnabled = false;
                this._mainWindow.btnIncreaseMotor2.IsEnabled = false;
                this._mainWindow.btnIncreaseMotor3.IsEnabled = false;
                this._mainWindow.btnIncreaseMotor4.IsEnabled = false;
            }

        }
        
        public void refreshComports()
        {
            this._mainWindow.comboPorts.Items.Clear();
            Console.WriteLine("Number of Ports Available: " + _usb.getNumberOfPorts());
            String[] ports =  _usb.getPorts();
            for (int i = 0; i < _usb.getNumberOfPorts(); i++)
            {
                this._mainWindow.comboPorts.Items.Insert(i, ports[i]);
            }

            this._mainWindow.txtBaudRate.Text = "115200";
            this._mainWindow.lblStatus.Content = "No ports online.";
        }
        
        public void connect()
        {
            if (this.isConnected)
            {
                this.isConnected = this._usb.disconnect();
                this._data.finishWriting();

                if (!this.isConnected)
                {
                    this._mainWindow.btnConnect.Content = "Connect";                  
                }
            }
            else
            {
                if (this._mainWindow.comboPorts.Text.Length > 0 && (this._mainWindow.txtBaudRate.Text.Equals("115200") || this._mainWindow.txtBaudRate.Text.Equals("9600") || this._mainWindow.txtBaudRate.Text.Equals("230400")))
                {
                    this.isConnected = _usb.connect();
                    this._data.startWriting();
                    if (this.isConnected)
                    {
                        this._mainWindow.btnConnect.Content = "Disconnect";
                    }
                }
                else
                {
                    MessageBox.Show("Check your port or baud rate.");
                }
            }
            checkConvention();
        }
        
        public void decreaseAll()
        {
            decreaseMotor(1);
            decreaseMotor(2);
            decreaseMotor(3);
            decreaseMotor(4);
        }
        
        public void increaseAll()
        {
            increaseMotor(1);
            increaseMotor(2);
            increaseMotor(3);
            increaseMotor(4);
        }
       
        public void decreaseMotor(int motorNumber)
        {
            int temp = Convert.ToInt32(this._data.getPwm(motorNumber)) - Convert.ToInt32(this._mainWindow.txtDecraseCalInterval.Text);
            String value = "M" +motorNumber.ToString()+ temp.ToString();
            this._usb.sendData(value);
            Console.WriteLine("New Sending:" + value);
        }
        
        public void increaseMotor(int motorNumber)
        {
            int temp = Convert.ToInt32(this._data.getPwm(motorNumber)) + Convert.ToInt32(this._mainWindow.txtIncraseCalInterval.Text);
            String value = "M" + motorNumber.ToString() + temp.ToString();
            this._usb.sendData(value);
            Console.WriteLine("New Sending:" + value);

        }
        
        public void clearPwm()
        {
            this._mainWindow.txtMotor1.Text = "";
            this._mainWindow.txtMotor2.Text = "";
            this._mainWindow.txtMotor3.Text = "";
            this._mainWindow.txtMotor4.Text = "";
        }
        
        public void stop()
        {
            this._usb.sendData("M11210");
            this._usb.sendData("M21210");
            this._usb.sendData("M31210");
            this._usb.sendData("M41210");
        }
    }
}

