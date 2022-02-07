import serial
import mysql.connector
import time
from datetime import datetime

def start_script():
    try:
        db = mysql.connector.connect(
                    host ="localhost",
                    user ="root",
                    password="",
                    database = "messwerte",
                    )

        cursor = db.cursor() 
        sqlStatement = ("INSERT INTO esp32 (ID,Datum,drehzahl,flowRate,total) VALUES (ID,UTC_TIMESTAMP(),%s,%s,%s)")

        arduinoData=serial.Serial('COM8',9600)

        while True:
            arduinoString=arduinoData.readline()
            dataArray=arduinoString.split(b',')
            rpm = float(dataArray[0])
            flowRate = float(dataArray[1])
            total = float(dataArray[2])
            data = tuple([rpm, flowRate, total])
            cursor.execute(sqlStatement, data)
            db.commit()
            print("Service running! Timestamp: " + str(datetime.now()))
            
    except:
        handle_crash()

def handle_crash():
    # This function is the crash handler
    print("Ein Fehler ist aufgetreten, erneuter Versuch in 5 Sekunden.")
    time.sleep(5)
    start_script()

start_script()