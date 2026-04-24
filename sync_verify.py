import serial
import time
from datetime import datetime

port = "/dev/cu.usbserial-14130"
baud = 115200

try:
    ser = serial.Serial(port, baud, timeout=1)
    time.sleep(2)  # Wait for boot
    
    # Get current time and format it as TYYYYMMDDHHMMSS
    now = datetime.now()
    sync_cmd = now.strftime("T%Y%m%d%H%M%S\n")
    print(f"Sending sync command: {sync_cmd.strip()}")
    
    ser.write(sync_cmd.encode())
    
    # Read output for 5 seconds to verify
    end_time = time.time() + 5
    while time.time() < end_time:
        line = ser.readline().decode('utf-8', errors='ignore').strip()
        if line:
            print(f"Received: {line}")
            if "RTC Sync Successful!" in line:
                print("Verification SUCCESS: RTC synced successfully!")
                
    ser.close()
except Exception as e:
    print(f"Error: {e}")
