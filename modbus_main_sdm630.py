# -*- coding: utf-8 -*-
"""
Created on Sat Jan 22 13:05:30 2022

@author: chris
"""

# Main Program for Data Acquisition and storing in mysql

import mysql.connector
import sdm_modbus
import time
from datetime import datetime
from operator import itemgetter

# Settings of Sensor Device
meter = sdm_modbus.SDM630(
    device='/dev/ttyUSB0',          #USB port of Raspi
    stopbits=1,
    parity='N',
    baud=9600,
    timeout=2,
    unit=1
    )
            
def start_script():
    # This function connects to the database and starts the data acquisition
    #try:
        # Enter here your mysql credentials
        db = mysql.connector.connect(
            host ="localhost",      #put in IP-adress of raspi
            user ="root",
            password="",
            database = "messwerte",
            )
        cursor = db.cursor()
        #https://github.com/nmakel/sdm_modbus/blob/master/src/sdm_modbus/sdm.py
        sqlStatement = ("""INSERT INTO sdm630
                        (`ID`,`Datum`,`Voltage_L1N`,`Voltage_L2N`,`Voltage_L3N`,`Current_L1`,`Current_L2`,`Current_L3`,
                        `Power_L1`,`Power_L2`,`Power_L3`,`Frequency`,`Total_kWh`,`Total_kVarh`,
                        `Power_factor_L1`,`Power_factor_L2`,`Power_factor_L3`,`Phase_angle_L1`,`Phase_angle_L2`,`Phase_angle_L3`)
                        VALUES (ID,UTC_TIMESTAMP(),'l1_voltage','l2_voltage','l3_voltage','l1_current','l2_current','l3_current',
                                'l1_power_active','l2_power_active','l3_power_active','frequency','total_power_active','total_power_reactive',
                                'l1_power_factor','l2_power_factor','l3_power_factor','l1_phase_angle','l2_phase_angle','l3_phase_angle')""")
        while True:
            read_data(db, cursor, sqlStatement)

    #except:
        handle_crash()

def read_data(db, cursor, sqlStatement):
    # This function reads the device and stores the data in the database
    data = meter.read_all(sdm_modbus.registerType.INPUT)
    data_list = itemgetter('l1_voltage','l2_voltage','l3_voltage','l1_current','l2_current','l3_current',
                                'l1_power_active','l2_power_active','l3_power_active','frequency','total_power_active','total_power_reactive',
                                'l1_power_factor','l2_power_factor','l3_power_factor','l1_phase_angle','l2_phase_angle','l3_phase_angle')(data)
    cursor.execute(sqlStatement, data_list)
    db.commit()
    print("Service running! Timestamp: " + str(datetime.now()))

def handle_crash():
    # This function is the crash handler
    print("Ein Fehler ist aufgetreten, erneuter Versuch in 5 Sekunden.")
    time.sleep(5)
    start_script()
        
start_script()