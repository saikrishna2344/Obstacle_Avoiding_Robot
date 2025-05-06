import serial
import time
import matplotlib.pyplot as plt
import numpy as np
from datetime import datetime

# Setup Serial Port for communication with Arduino
port = 'COM3'  # Change to the appropriate port for your system (Linux: /dev/ttyUSB0)
baud = 9600
ser = serial.Serial(port, baud, timeout=1)
time.sleep(2)  # Wait for the serial connection to establish

# Create a figure for plotting
plt.ion()  # Interactive mode on for real-time updates
fig, ax = plt.subplots()
x_data = []
y_data = []
line, = ax.plot([], [], 'r-', label='Distance (cm)')
ax.set_xlabel('Time (s)')
ax.set_ylabel('Distance (cm)')
ax.set_title('Real-time Distance Monitoring')
ax.legend()
ax.grid(True)

# File to log the data
log_file = open('distance_data_log.csv', 'w')
log_file.write('Timestamp,Distance (cm)\n')  # Header for the CSV file

# Function to update plot
def update_plot():
    if len(x_data) > 100:  # Limit the data points on the graph for clarity
        x_data.pop(0)
        y_data.pop(0)

    line.set_xdata(x_data)
    line.set_ydata(y_data)
    plt.draw()
    plt.pause(0.1)

# Function to handle real-time alerts
def check_alert(distance):
    if distance < 15:
        print(f"ALERT! Distance {distance} cm is too close! Obstacle detected.")
    else:
        print(f"Safe distance: {distance} cm.")

try:
    print("Starting to read data from Arduino...\n")
    start_time = time.time()  # Start the time for logging and graphing
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').strip()
            if line.isdigit():  # Check if the received data is a number
                distance = int(line)
                current_time = time.time() - start_time  # Time elapsed since start

                # Log the data with timestamp
                timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                log_file.write(f"{timestamp},{distance}\n")
                
                # Update plot with new data
                x_data.append(current_time)
                y_data.append(distance)
                update_plot()

                # Check for distance alerts
                check_alert(distance)

except KeyboardInterrupt:
    print("\nTerminating...")

finally:
    # Clean up
    ser.close()
    log_file.close()
    plt.ioff()  # Turn off interactive plotting
    plt.show()  # Show the final plot
