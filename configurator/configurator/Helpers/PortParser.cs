using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Management;

namespace configurator.Helpers
{
    public static class PortParser
    {
        public static List<KeyValuePair<string, SerialPort>> GetPorts()
        {
            var portsList = new List<KeyValuePair<string, SerialPort>>();

            var connectionScope = new ManagementScope();
            var serialQuery =
                new SelectQuery(
                    "SELECT * FROM Win32_PnPEntity WHERE ClassGuid=\"{4d36e978-e325-11ce-bfc1-08002be10318}\"");
            var searcher = new ManagementObjectSearcher(connectionScope, serialQuery);

            try
            {
                foreach (var item in searcher.Get())
                {
                    var caption = item["Caption"].ToString();
                    var comPort = ExtractComPort(caption);
                    var device = $"{item["Description"]} on {comPort}";

                    portsList.Add(CreatePortEntry(device, comPort));
                }
            }
            catch (ManagementException e)
            {
                throw new Exception("Could not resolve COM Ports.\n" + e.Message);
            }

            return portsList;
        }

        private static KeyValuePair<string, SerialPort> CreatePortEntry(string device, string comPort)
        {
            return new KeyValuePair<string, SerialPort>(
                device,
                new SerialPort(comPort, 115200) {Handshake = Handshake.None});
        }

        private static string ExtractComPort(string caption)
        {
            return caption.Substring(caption.LastIndexOf("(COM")).Replace("(", string.Empty)
                .Replace(")", string.Empty);
        }
    }
}