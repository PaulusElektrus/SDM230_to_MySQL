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

# This line is for the ESP32 drehzahl Device
cursor.execute("CREATE TABLE esp32 (`ID` INT AUTO_INCREMENT PRIMARY KEY,`Datum` TIMESTAMP DEFAULT CURRENT_TIMESTAMP,`drehzahl` FLOAT(5,1),`flowRate` FLOAT(6,2),`total` FLOAT(6,2))")

# Other devices will follow...