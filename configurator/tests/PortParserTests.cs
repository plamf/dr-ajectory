using System;
using System.Collections.Generic;
using System.IO.Ports;
using configurator.Helpers;
using FluentAssertions;
using NUnit.Framework;

namespace tests
{
    public class PortParserTests
    {
        [Test]
        public void GetPorts_NoException()
        {
            Action result = () => PortParser.GetPorts();

            result.Should().NotThrow<Exception>();
        }

        [Test]
        public void GetPorts_ReturnsList_ValidType()
        {
            var ports = PortParser.GetPorts();

            ports.Should().BeOfType<List<KeyValuePair<string, SerialPort>>>();
        }

        [Test]
        public void GetPorts_ReturnsList_NotNullOrEmpty()
        {
            var ports = PortParser.GetPorts();

            ports.Should().NotBeNullOrEmpty();
        }
    }
}