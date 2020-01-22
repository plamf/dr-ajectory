using System.IO.Ports;
using System.Windows;
using configurator.Models;

namespace configurator.Controllers
{
    public class UploadController
    {
        private const string OkResult = "O";
        private readonly SerialPort _serialPort;

        public UploadController(SerialPort serialPort)
        {
            _serialPort = serialPort;
            _serialPort.DataReceived += DataReceived;
        }

        private void DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            var sp = (SerialPort)sender;
            var result = sp.ReadExisting();

            if (result.Equals(OkResult))
            {
                MessageBox.Show("Upload successful!", "Data upload", MessageBoxButton.OK, MessageBoxImage.Asterisk);
            }

            _serialPort.Close();
        }

        public void UpdateConfiguration(ConfigVariables cv)
        {
            _serialPort.Open();
            _serialPort.WriteLine(cv.PayLoad); 
        }
    }
}