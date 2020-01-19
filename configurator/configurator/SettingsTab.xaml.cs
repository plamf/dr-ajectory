using System.ComponentModel;
using System.IO;
using System.IO.Ports;
using System.Windows.Controls;
using configurator.Helpers;

namespace configurator
{
    public partial class SettingsTab : UserControl
    {
        private SerialPort _serialPort;

        public SettingsTab()
        {
            InitializeComponent();

            var portslist = PortParser.GetPorts(); //TODO: Add to dropdownlist and connect to port with buttonclick

            CheckConnection();
        }

        private void CheckConnection()
        {
            _serialPort = new SerialPort("COM5", 115200) {Handshake = Handshake.None};
            try
            {
                _serialPort.Open();
                _serialPort.WriteLine("123"); //C - Check connection to Dr. Ajectory
            }
            catch (IOException e)
            {
                //No connection found on this port
            }
        }

        private void SerialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            var serialBuffer = _serialPort.ReadExisting();

            if (serialBuffer.Contains("O")) //O - Connection OK
            {
                ToggleUploadButton(enabled: true);
            }
            else
            {
                ToggleUploadButton(enabled: false);
            }

            _serialPort.Close();

        }

        private void ToggleUploadButton(bool enabled)
        {
            var worker = new BackgroundWorker();
            var buttonText = string.Empty;

            switch (enabled)
            {
                case true:
                    buttonText = "Upload to Dr. Ajectory";
                    break;
                case false:
                    buttonText = "Looking for Dr. Ajectory...";
                    break;
            }

            worker.DoWork += delegate
            {
                this.Dispatcher?.Invoke(() =>
                {
                    btnUploadSettings.Content = buttonText;
                    btnUploadSettings.IsEnabled = enabled;
                });
            };
            
            worker.RunWorkerAsync();
        }
    }
}