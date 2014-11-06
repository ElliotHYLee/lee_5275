﻿using System;
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
        string[] ports;
        SerialPort serial;
        int numberOfPorts;
        string recieved_data;



        public MainWindow()
        {
            InitializeComponent();
            this.connectionStatus = false;

            this.serial = new SerialPort();
            this.ports = SerialPort.GetPortNames();
            this.numberOfPorts = ports.Length;
            for (int i = 0; i < numberOfPorts; i++)
            {
                this.comboPorts.Items.Insert(i, ports[i]);
            }
            this.txtMonitor.Document.Blocks.Clear();
            this.txtBaudRate.Text = "115200";
            this.txtSend.Text = "";
            this.btnDisconnect.IsEnabled = false;
            this.btnSend.IsEnabled = false;
            this.lblStatus.Content = "No ports online.";
            
            Console.WriteLine("Number of Ports Available: " + this.numberOfPorts);
        }

   
        private void btnDisconnect_Clicked(object sender, RoutedEventArgs e)
        {
            this.serial.Close();
            this.connectionStatus = false;


            this.txtBaudRate.Text = "";
            this.btnDisconnect.IsEnabled = false;
            this.btnConnect.IsEnabled = true;
            this.btnSend.IsEnabled = false;
        }

        private void btnConnect_Clicked(object sender, RoutedEventArgs e)
        {
            if (comboPorts.Text.Length > 0 && (txtBaudRate.Text.Equals("115200") || txtBaudRate.Text.Equals("9600")))
            {
                this.serial.PortName = comboPorts.Text;
                this.serial.BaudRate = int.Parse(txtBaudRate.Text);
                this.serial.Open();
                this.btnDisconnect.IsEnabled = true;
                this.btnConnect.IsEnabled = false;
                this.connectionStatus = true;
                this.btnSend.IsEnabled = true;
                this.lblStatus.Content = serial.PortName + " online";
            }
            else
            {
                MessageBox.Show("Check your port or baud rate.");
            }
           
        }

        private void txtSend_TextChanged(object sender, TextChangedEventArgs e)
        {
            
        }

        private void txtBaudRate_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        private void btnRefresh_Click(object sender, RoutedEventArgs e)
        {
            this.comboPorts.Items.Clear();
            this.ports = SerialPort.GetPortNames();
            this.numberOfPorts = ports.Length;
            for (int i = 0; i < numberOfPorts; i++)
            {
                this.comboPorts.Items.Insert(i, ports[i]);
            }
        }

        private void txtMonitor_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        private void btnSend_Click(object sender, RoutedEventArgs e)
        {
            if (this.connectionStatus)
            {

            }
        }


        private static void DataReceivedHandler(
                        object sender,
                        SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;
            string indata = sp.ReadExisting();
            Console.WriteLine("Data Received:");
            Console.Write(indata);
        }
        private void comboPorts_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }
    }
}