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
using SerialMonitorTest03.ControllerFolder;

namespace SerialMonitorTest03
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        SimpleController _controller;

        public MainWindow()
        {
            // initializing build in components 
            InitializeComponent(); 
            _controller = new SimpleController(this);
        }


        private void btnRefresh_Click(object sender, RoutedEventArgs e)
        {
            _controller.refreshComports();
        }

        private void btnConnect_Clicked(object sender, RoutedEventArgs e)
        {
            _controller.connect();   
        }


      
        private void menuFileOpen_click(object sender, RoutedEventArgs e)
        {

        }

        private void btnClearPWM_Click(object sender, RoutedEventArgs e)
        {
           _controller.clearPwm();
        }


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




        private void btnDecreaseMotor1_Click(object sender, RoutedEventArgs e)
        {
            _controller.decreaseMotor(1);
        }
        private void btnDecreaseMotor2_Click(object sender, RoutedEventArgs e)
        {
            _controller.decreaseMotor(2);
        }

        private void btnDecreaseMotor3_Click(object sender, RoutedEventArgs e)
        {
            _controller.decreaseMotor(3);
        }

        private void btnDecreaseMotor4_Click(object sender, RoutedEventArgs e)
        {
            _controller.decreaseMotor(4);
        }


        #region IncreaseButtons
        private void btnIncreaseMotor1_Click(object sender, RoutedEventArgs e)
        {
            _controller.increaseMotor(1);
        }

        private void btnIncreaseMotor2_Click(object sender, RoutedEventArgs e)
        {
            _controller.increaseMotor(2);
        }

        private void btnIncreaseMotor3_Click(object sender, RoutedEventArgs e)
        {
            _controller.increaseMotor(3);
        }

        private void btnIncreaseMotor4_Click(object sender, RoutedEventArgs e)
        {
            _controller.increaseMotor(4);
        }


        #endregion


        private void moterSlide1_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {

        }

        private void moterSlide2_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {

        }

        private void motorSlide3_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {

        }

        private void motorSlide4_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {

        }

        private void btnDecreaseAll_Click(object sender, RoutedEventArgs e)
        {
            _controller.decreaseAll();
        }

        private void btnStop_Click(object sender, RoutedEventArgs e)
        {
            _controller.stop();
        }

        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            
        }

        private void menuAuthor_click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("Elliot Lee");
        }

        private void btnIncreaseAll_Click(object sender, RoutedEventArgs e)
        {
            _controller.increaseAll();
        }

        #region sliders

        #endregion


    }
}
        