import pytest
import serial
import time

@pytest.fixture
def serial_port():
    """Create serial connection to device"""
    port = serial.Serial(
        port='/dev/ttyACM0',  # Adjust for your system
        baudrate=115200,
        timeout=1
    )
    
    # Wait for device to be ready
    time.sleep(2)
    
    yield port
    
    port.close()