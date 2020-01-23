using System;
using System.IO.Ports;
using System.Threading;
using configurator.Controllers;
using configurator.Models;
using FluentAssertions;
using NUnit.Framework;

namespace tests
{
    public class UploadControllerTests
    {
       [Test]
        public void Upload_ConfigVariables_Empty_Valid()
        {
            var uc = new UploadController(GetValidSerialPort());

            Action result = () => uc.UpdateConfiguration(new ConfigVariables());

            result.Should().NotThrow();
        }

        [Test]
        public void Upload_ConfigVariables_NULL_Invalid()
        {
            var uc = new UploadController(GetValidSerialPort());

            Action result = () => uc.UpdateConfiguration(null);

            result.Should().Throw<UnauthorizedAccessException>();
        }

        [Test]
        public void Upload_ResultReceived_SerialPortIsClosed()
        {
            var serialPort = GetValidSerialPort();
            var resetEvent = new ManualResetEvent(true);

            serialPort.DataReceived += (s,e) => { resetEvent.Set(); };

            serialPort.IsOpen.Should().BeFalse();

        }

        private static SerialPort GetValidSerialPort()
        {
            return new SerialPort("COM1");
        }
    }
}
