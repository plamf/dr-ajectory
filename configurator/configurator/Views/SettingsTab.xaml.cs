using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.IO.Ports;
using System.Text.RegularExpressions;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using configurator.Controllers;
using configurator.Helpers;
using configurator.Models;

namespace configurator.Views
{
    public partial class SettingsTab : UserControl
    {
        private SerialPort _serialPort;

        public SettingsTab()
        {
            InitializeComponent();
            InitializeComboboxes();
        }

        private void NumberValidationTextBox(object sender, TextCompositionEventArgs e)
        {
            var regex = new Regex("[^0-9]+");
            e.Handled = regex.IsMatch(e.Text);
        }

        private bool CheckConnection(string port)
        {
            _serialPort = new SerialPort(port, 115200) {Handshake = Handshake.None};
            try
            {
                _serialPort.Open();
                _serialPort.Close();
            }
            catch (IOException e)
            {
                MessageBox.Show($"A connection on {port} could not be established.\n\n{e.Message}", "Error", MessageBoxButton.OK,
                    MessageBoxImage.Error);
            }

            return true;
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
                    buttonText = "No connection...";
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

        private void InitializeComboboxes()
        {
            InitializeDevices();
            InitializeProfiles();
        }

        private void InitializeDevices()
        {
            var portslist = new List<KeyValuePair<string, SerialPort>>();
            portslist.Add(new KeyValuePair<string, SerialPort>("Select Device...", null));
            portslist.AddRange(PortParser.GetPorts());

            cbDevice.ItemsSource = portslist;
            cbDevice.SelectionChanged += CbDevice_SelectionChanged;
        }

        private void InitializeProfiles()
        {
            var profileList = new List<KeyValuePair<string, string>>();
            profileList.Add(new KeyValuePair<string, string>("Select Profile...", ""));
            profileList.AddRange(new List<KeyValuePair<string, string>>());

            cbProfile.ItemsSource = profileList;
            cbProfile.SelectionChanged += CbProfile_SelectionChanged;
        }

        private void CbProfile_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            //LoadProfile();
        }

        private void CbDevice_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (cbDevice.SelectedValue is SerialPort port)
            {
                ToggleUploadButton(enabled: CheckConnection(port.PortName));
            }
        }

        private void BtnUploadSettings_OnClick(object sender, RoutedEventArgs e)
        {
            var serialPort = cbDevice.SelectedValue as SerialPort;
            var uploadController = new UploadController(serialPort);
            var config = new ConfigVariables
            {
                ArrowWeight = tbArrowWeight.Text,
                DrawLength = tbDrawLength.Text,
                IboRating = tbIboRating.Text,
                LbsOfForce = tbLbsOfForce.Text,
                WeightOnBowstring = tbWeightOnBowstring.Text
            };

            uploadController.UpdateConfiguration(config);
        }
    }
}