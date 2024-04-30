import serial, time
ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)

while True:
    if ser.in_waiting > 0:
        data = ser.readline().decode().strip()
        print("Data received:", data)
    time.sleep(1/2)