import pytest
import serial
import time

class TestGPIO:
    def test_gpio_toggle(self, serial_port):
        """Test GPIO toggle functionality"""
        # Send command to toggle GPIO
        serial_port.write(b'gpio_toggle\n')
        time.sleep(0.1)
        
        # Read response
        response = serial_port.read(100).decode('utf-8')
        assert 'GPIO toggled' in response
        
    def test_gpio_read(self, serial_port):
        """Test GPIO read functionality"""
        serial_port.write(b'gpio_read\n')
        time.sleep(0.1)
        
        response = serial_port.read(100).decode('utf-8')
        assert 'GPIO state:' in response