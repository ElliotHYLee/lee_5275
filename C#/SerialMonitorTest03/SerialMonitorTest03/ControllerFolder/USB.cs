using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Threading;



namespace SerialMonitorTest03.ControllerFolder
{
    // This class doesn't check convention
    class USB
    {
        private MainWindow _mainWindow;
        private SerialPort _serial;
        private String[] ports;
        private int numberOfPorts;
        private String motorLine, dirCosLine;
        private DataModel _data;

        public USB(MainWindow sender, DataModel data)
        {

            this._data = data;
            this._mainWindow = sender;
            this._serial = new SerialPort();
            this.ports = SerialPort.GetPortNames();
            numberOfPorts = this.ports.Length;
        }

        public int getNumberOfPorts()
        {
            return this.numberOfPorts;
        }

        public String[] getPorts()
        {
            return this.ports;
        }

        public String getPortName()
        {
            return this._serial.PortName;
        }

        public Boolean connect()
        {
            Boolean result = false;
            this._serial.PortName = this._mainWindow.comboPorts.Text;
            this._serial.BaudRate = int.Parse(this._mainWindow.txtBaudRate.Text);
            // connecting empty event to the actual method
            // LHS is empty event for serial object, which original has this empty even handler(method)
            // RHS is the actual methods that I have to implement
            this._serial.DataReceived += serial_DataReceived;
            this._serial.Open();
            result = true;
            return result;
        }

        private void serial_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;
            String indata = (String)this._serial.ReadExisting();
            this.getLine(indata);
            this.updateMainWidow();
        }

        public void sendData(String value)
        {
            this._serial.WriteLine(value);
        }

        private void getLine(String indata)
        {
            if (!indata.Contains("/"))
            {
                Console.WriteLine("Searching for slash");
                return;
            }
            //if there's no charater '/' in the propeller, this will crash.
            String targetLine, temp;
            int dividerLocation = indata.IndexOf('/');
            targetLine = indata.Substring(dividerLocation+1, indata.Length - dividerLocation-1);
            //Console.WriteLine("traget line="+targetLine);
            if (targetLine.Substring(0, 1).Equals("M"))
            {
                //Console.WriteLine("M");
                if (targetLine.Length < 24)
                {
                    return;
                }
                motorLine = targetLine.Substring(0, 24);
                temp = targetLine.Substring(25, targetLine.Length - motorLine.Length -1);
                //Console.WriteLine("TEMP " + temp);
                dividerLocation = temp.IndexOf('/');
                if (dividerLocation <= 0) {return;}
                dirCosLine = temp.Substring(0, dividerLocation);
            }
            else if (targetLine.Substring(0, 1).Equals("C"))
            {
                //Console.WriteLine("C");
                dividerLocation = targetLine.IndexOf('/');
                if (dividerLocation <= 0) { return; }
                dirCosLine = targetLine.Substring(0, dividerLocation);
                if (targetLine.Length < dividerLocation + 24){return;}
                motorLine = targetLine.Substring(dividerLocation+1, 24);
            }

            //Console.WriteLine("motorLine :"+motorLine);
            //Console.WriteLine("dirCosLine :" + dirCosLine);
            this.parse();

        }
      
        private void parse()
        {
            String[] tempPwm = new String[4];
            String[] tempDirCos = new String[3];
            int nextCy=0, nextCz=0;;

            for (int i = 0; i < 4; i++)
            {
                tempPwm[i] = motorLine.Substring(6 * i + 1, 5);
                //Console.WriteLine(tempPwm[i]);
                this._data.setPwm(tempPwm[i]);
            }

            nextCy = dirCosLine.IndexOf("Cy");
            nextCz = dirCosLine.IndexOf("Cz");
            if (nextCy <= 0 || nextCz <= 0)
            {
                return;
            }
            tempDirCos[0] = dirCosLine.Substring(0, nextCy);
            tempDirCos[1] = dirCosLine.Substring(nextCy, nextCz-nextCy);
            tempDirCos[2] = dirCosLine.Substring(nextCz, dirCosLine.Length - nextCz );
            this._data.setDirCos(tempDirCos[0]);
            this._data.setDirCos(tempDirCos[1]);
            this._data.setDirCos(tempDirCos[2]);
            //Console.WriteLine(dirCosLine);
            //Console.WriteLine("1 :" + this._data.getDirCos(1));
            //Console.WriteLine("2 :" + this._data.getDirCos(2));
            //Console.WriteLine("3 :" + this._data.getDirCos(3));

         }

        private void updateMainWidow()
        {
            this._mainWindow.Dispatcher.Invoke(() =>
            {
                this._mainWindow.txtMotor1.Text = this._data.getPwm(1);
                this._mainWindow.txtMotor2.Text = this._data.getPwm(2);
                this._mainWindow.txtMotor3.Text = this._data.getPwm(3);
                this._mainWindow.txtMotor4.Text = this._data.getPwm(4);

                this._mainWindow.txtDirCosX.Text = this._data.getDirCos(1);
                this._mainWindow.txtDirCosY.Text = this._data.getDirCos(2);
                this._mainWindow.txtDirCosZ.Text = this._data.getDirCos(3);

                this._mainWindow.txtAngleX.Text = (Math.Acos(Double.Parse(this._data.getDirCos(1))) * 180 / Math.PI).ToString();
                this._mainWindow.txtAngleY.Text = (Math.Acos(Double.Parse(this._data.getDirCos(2))) * 180 / Math.PI).ToString();
                this._mainWindow.txtAngleZ.Text = (Math.Acos(Double.Parse(this._data.getDirCos(3))) * 180 / Math.PI).ToString();
            });
        }

        public Boolean disconnect()
        {
            Boolean result = false;
            this._serial.Close();
            result = false;
            
            return result;
        }


    }
}
