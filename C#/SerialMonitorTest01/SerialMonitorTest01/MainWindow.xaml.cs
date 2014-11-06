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

namespace SerialMonitorTest01
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            txtComPort.Text = "";
            txtBaudRate.Text = "";
            txtSend.Text = "";
            btnDisconnect.IsEnabled = false;

        }
                
        private void btnSend(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("USB should be connected");
            return;
            
        }

        private void btnDisconnect_Clicked(object sender, RoutedEventArgs e)
        {
            txtBaudRate.Text = "";
            btnDisconnect.IsEnabled = false;
            btnConnect.IsEnabled = true;
        }

        private void btnConnect_Clicked(object sender, RoutedEventArgs e)
        {
            txtBaudRate.Text = "115200";
            btnDisconnect.IsEnabled = true;
            btnConnect.IsEnabled = false;
        }

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        private void txtSend_TextChanged(object sender, TextChangedEventArgs e)
        {
            
        }

        private void txtMonitor_TextChanged(object sender, TextChangedEventArgs e)
        {

        }




    }
}
