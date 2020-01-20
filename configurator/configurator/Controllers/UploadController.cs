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
            var dataToSend =
                $"<{cv.iboRating},{cv.weightOnBowstring},{cv.lbsOfForce},{cv.drawLength},{cv.arrowWeight}>";

            using (_serialPort)
            {
                _serialPort.WriteLine(dataToSend);
            }
        }
    }
}