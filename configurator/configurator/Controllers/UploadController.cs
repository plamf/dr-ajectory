using System.IO.Ports;
using System.Threading;
using System.Windows;
using System.Windows.Input;
using configurator.Models;

namespace configurator.Controllers
{
    public class UploadController
    {
        private const string OkResult = "O";
        private readonly SerialPort _serialPort; 
        public ManualResetEvent DataReceivedEvent = new ManualResetEvent(false);

        public UploadController(SerialPort serialPort)
        {
            _serialPort = serialPort;
            _serialPort.DataReceived += DataReceived;
        }

        protected void DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            var sp = (SerialPort)sender;
            var result = sp.ReadExisting();

            if (result.Equals(OkResult))
            {
                DataReceivedEvent.Set();
            }

            _serialPort.Close();
        }

        public void UpdateConfiguration(ConfigVariables cv)
        {
            Application.Current.Dispatcher.Invoke(() =>
            {
                Mouse.OverrideCursor = Cursors.Wait;
            });

            _serialPort.Open();
            _serialPort.WriteLine(cv.PayLoad);
        }
    }
}