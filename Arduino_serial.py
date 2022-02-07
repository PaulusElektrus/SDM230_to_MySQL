import serial
import time
 
s = serial.Serial('/dev/ttyUSB0', 9600) # Namen ggf. anpassen
s.open()
time.sleep(5) # der Arduino resettet nach einer Seriellen Verbindung, daher muss kurz gewartet werden
 
s.write("test")
try:
    while True:
        response = s.readline()
        print(response)
except KeyboardInterrupt:
    s.close()