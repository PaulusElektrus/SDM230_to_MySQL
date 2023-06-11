# Use this to add the correct table to your mysql database

import mysql.connector

# Enter here your mysql login data
db = mysql.connector.connect(
                host ="localhost",
                user ="root",
                password="",
                database = "messwerte",
                )

cursor = db.cursor()

# This line is for the Eastron SDM230 Device
cursor.execute("CREATE TABLE sdm630 (`ID` INT AUTO_INCREMENT PRIMARY KEY,`Datum` TIMESTAMP DEFAULT CURRENT_TIMESTAMP,`Voltage_L1N` FLOAT(8,3),`Voltage_L2N` FLOAT(8,3),`Voltage_L3N` FLOAT(8,3),`Current_L1` FLOAT(8,3),`Current_L2` FLOAT(8,3),`Current_L3` FLOAT(8,3),`Power_L1` FLOAT(8,3),`Power_L2` FLOAT(8,3),`Power_L3` FLOAT(8,3),`Frequency` FLOAT(8,3),`Total_kWh` FLOAT(8,3),`Total_kVarh` FLOAT(8,3),`Power_factor_L1` FLOAT(8,3),`Power_factor_L2` FLOAT(8,3),`Power_factor_L3` FLOAT(8,3),`Phase_angle_L1` FLOAT(8,3),`Phase_angle_L2` FLOAT(8,3),`Phase_angle_L3` FLOAT(8,3))")

# Other devices will follow...