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
cursor.execute("CREATE TABLE sdm230 (`ID` INT AUTO_INCREMENT PRIMARY KEY,`Datum` TIMESTAMP DEFAULT CURRENT_TIMESTAMP,`Voltage` FLOAT(8,3),`Current` FLOAT(8,3),`Power_Active` FLOAT(8,3),`Power_Apparent` FLOAT(8,3),`Power_Reactive` FLOAT(8,3),`Power_Factor` FLOAT(8,3),`Phase_Angle` FLOAT(8,3),`Frequency` FLOAT(8,3),`Imported_Energy_Active` FLOAT(8,3),`Exported_Energy_Active` FLOAT(8,3),`Imported_Energy_Reactive` FLOAT(8,3),`Exported_Energy_Reactive` FLOAT(8,3),`Total_Demand_Power_Active` FLOAT(8,3),`Maximum_Total_Demand_Power_Active` FLOAT(8,3),`Import_Demand_Power_Active` FLOAT(8,3),`Maximum_Import_Demand_Power_Active` FLOAT(8,3),`Export_Demand_Power_Active` FLOAT(8,3),`Maximum_Export_Demand_Power_Active` FLOAT(8,3),`Total_Demand_Current` FLOAT(8,3),`Maximum_Total_Demand_Current` FLOAT(8,3),`Total_Energy_Active` FLOAT(8,3),`Total_Energy_Reactive` FLOAT(8,3),`drehzahl` FLOAT(5,1))")

# Other devices will follow...