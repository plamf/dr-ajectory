using System;
using System.IO;
using System.IO.Ports;
using System.Timers;
using System.Windows.Controls;

namespace configurator
{
    public partial class SettingsTab : UserControl
    {
        private SerialPort serialPort;
        private Timer timer;

        public SettingsTab()
        {
            InitializeComponent();

            timer = new Timer(1000);
            timer.Elapsed += CheckConnection;
            timer.Start();

            serialPort = new SerialPort("COM4", 9600) {Handshake = Handshake.None};
            serialPort.DataReceived += SerialPort_DataReceived;
        }

        private void CheckConnection(object sender, ElapsedEventArgs e)
        {
            try
            {
                serialPort.Open();
            }
            catch (IOException exception)
            {
                Console.WriteLine(exception);
            }
}

        private void SerialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            var serialBuffer = serialPort.ReadExisting();

            if (serialBuffer.Contains("state="))
            {
                var status = serialBuffer.Replace("state=", string.Empty);
                if (status.Contains("O"))
                {
                    //Arduino connected
                    //- Check if Dr. Ajectory is installed
                    //-- If yes, then enable upload button
                }
            }
        }
    }
}