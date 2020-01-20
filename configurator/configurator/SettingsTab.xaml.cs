using System;
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

namespace configurator
{
    public partial class SettingsTab : UserControl
    {
        private SerialPort _serialPort;

        public SettingsTab()
        {
            InitializeComponent();
            InitializeComboboxes();

            CheckConnection();
        }

        private void NumberValidationTextBox(object sender, TextCompositionEventArgs e)
        {
            var regex = new Regex("[^0-9]+");
            e.Handled = regex.IsMatch(e.Text);
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

            cbDevice.DisplayMemberPath = "Key";
            cbDevice.SelectedValuePath = "Value";
            cbDevice.ItemsSource = portslist;
            cbDevice.SelectedIndex = 0;
            cbDevice.SelectionChanged += CbDevice_SelectionChanged;
        }

        private void InitializeProfiles()
        {
            var profileList = new List<KeyValuePair<string, string>>();
            profileList.Add(new KeyValuePair<string, string>("Select Profile...", ""));
            profileList.AddRange(new List<KeyValuePair<string, string>>());

            cbProfile.DisplayMemberPath = "Key";
            cbProfile.SelectedValuePath = "Value";
            cbProfile.ItemsSource = profileList;
            cbProfile.SelectedIndex = 0;
            cbProfile.SelectionChanged += CbProfile_SelectionChanged;
        }

        private void CbProfile_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            //LoadProfile();
        }

        private void CbDevice_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ToggleUploadButton(enabled: cbDevice.SelectedIndex > 0);
        }

        private void BtnUploadSettings_OnClick(object sender, RoutedEventArgs e)
        {
            var serialPort = cbDevice.SelectionBoxItem as SerialPort;
            var uploadController = new UploadController(serialPort);
            var config = new ConfigVariables
            {
                iboRating = int.Parse(tbIboRating.Text),
                weightOnBowstring = int.Parse(tbWeightOnBowstring.Text),
                drawLength = int.Parse(tbDrawLength.Text),
                arrowWeight = int.Parse(tbArrowWeight.Text),
                lbsOfForce = int.Parse(tbLbsOfForce.Text)
            };

            uploadController.UpdateConfiguration(config);
        }
    }
}