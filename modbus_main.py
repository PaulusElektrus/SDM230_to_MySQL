# Main Program for Data Acquisition and storing in mysql

import mysql.connector
import sdm_modbus
import time
from datetime import datetime

# Settings of Sensor Device
meter = sdm_modbus.SDM230(
    device='/dev/ttyUSB0',
    stopbits=1,
    parity='N',
    baud=2400,
    timeout=2,
    unit=1
    )
            
def start_script():
    # This function connects to the database and starts the data acquisition
    try:
        # Enter here your mysql credentials
        db = mysql.connector.connect(
            host ="localhost",
            user ="root",
            password="",
            database = "messwerte",
            )
        cursor = db.cursor()   
        sqlStatement = ("INSERT INTO sdm230 "
                        "(ID,Datum,Voltage,Current,Power_Active,Power_Apparent,Power_Reactive,Power_Factor,Phase_Angle,Frequency,Imported_Energy_Active,Exported_Energy_Active,Imported_Energy_Reactive,Exported_Energy_Reactive,Total_Demand_Power_Active,Maximum_Total_Demand_Power_Active,Import_Demand_Power_Active,Maximum_Import_Demand_Power_Active,Export_Demand_Power_Active,Maximum_Export_Demand_Power_Active,Total_Demand_Current,Maximum_Total_Demand_Current,Total_Energy_Active,Total_Energy_Reactive) "
                        "VALUES (ID,UTC_TIMESTAMP(),%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)")
        while True:
            read_data(db, cursor, sqlStatement)

    except:
        handle_crash()

def read_data(db, cursor, sqlStatement):
    # This function reads the device and stores the data in the database
    data = meter.read_all(sdm_modbus.registerType.INPUT)
    data_list = tuple(data.values())
    cursor.execute(sqlStatement, data_list)
    db.commit()
    print("Service running! Timestamp: " + str(datetime.now()))

def handle_crash():
    # This function is the crash handler
    print("Ein Fehler ist aufgetreten, erneuter Versuch in 5 Sekunden.")
    time.sleep(5)
    start_script()
        
start_script()
