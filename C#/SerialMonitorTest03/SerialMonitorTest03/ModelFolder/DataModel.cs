using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SerialMonitorTest03
{
    class DataModel
    {
        private String[] pwm;
        private double[] dirCos;
        private String fileName;

        public DataModel()
        {
            pwm = new String[4];
            dirCos = new double[3];
        }

        public String getPwm(int motorNumber)
        {
            String result = null;
            switch (motorNumber)
            {
                case 1: 
                    result = this.pwm[0];
                    break;
                case 2:
                    result = this.pwm[1];
                    break;
                case 3:
                    result = this.pwm[2];
                    break;
                case 4:
                    result = this.pwm[3];
                    break;
            }

            return result;
        }

        public void setPwm(String value)
        {
            switch (value.Substring(0, 1))
            {
                case "1":
                    this.pwm[0] = value.Substring(1,4);
                    break;
                case "2":
                    this.pwm[1] = value.Substring(1, 4);
                    break;
                case "3":
                    this.pwm[2] = value.Substring(1, 4);
                    break;
                case "4":
                    this.pwm[3] = value.Substring(1, 4);
                    break;
            }
        }

        public String getDirCos(int axisNumber)
        {
            String result = null;
            switch (axisNumber)
            {
                case 1:
                    result = this.dirCos[0].ToString();
                    break;
                case 2:
                    result = this.dirCos[1].ToString();
                    break;
                case 3:
                    result = this.dirCos[2].ToString();
                    break;
            }

            return result;
        }
        
        public void setDirCos(String value)
        {
            String temp;
            temp = value.Substring(2, value.Length - 2);
            switch (value.Substring(0, 2))
            {
                case "Cx":
                    this.dirCos[0] = double.Parse(temp);
                    break;
                case "Cy":
                    this.dirCos[1] = double.Parse(temp);
                    break;
                case "Cz":
                    this.dirCos[2] = double.Parse(temp);
                    break;
            }


        }

        public void finishWriting()
        {

        }

        public void startWriting()
        {
            this.prepareFile();

        }

        private void prepareFile()
        {

        }



    }
}
