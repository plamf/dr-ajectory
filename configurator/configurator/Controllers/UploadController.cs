using System.IO.Ports;
using configurator.Models;

namespace configurator.Controllers
{
    public class UploadController
    {
        private readonly SerialPort _serialPort;

        public UploadController(SerialPort serialPort)
        {
            _serialPort = serialPort;
        }

        public void UpdateConfiguration(ConfigVariables cv)
        {
            _serialPort.Open();
            _serialPort.WriteLine(cv.PayLoad);
            _serialPort.Close();
        }
    }
}