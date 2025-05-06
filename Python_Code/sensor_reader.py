# sensor_reader.py — Python code to read IR sensor values from Arduino via Serial

import serial
import time

def read_sensor_data(serial_port='/dev/ttyACM0', baud_rate=9600):
    try:
        arduino = serial.Serial(serial_port, baud_rate, timeout=1)
        time.sleep(2)  # Wait for Arduino to reset

        print("Reading sensor data...")
        while True:
            if arduino.in_waiting:
                data = arduino.readline().decode('utf-8').strip()
                if data:
                    print(f"IR Sensor Value: {data}")
    except serial.SerialException:
        print("Could not connect to Arduino. Check the serial port.")
    except KeyboardInterrupt:
        print("\nStopped by user.")
    finally:
        if 'arduino' in locals():
            arduino.close()

if __name__ == "__main__":
    read_sensor_data()
