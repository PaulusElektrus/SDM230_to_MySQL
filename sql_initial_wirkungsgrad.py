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
cursor.execute("CREATE TABLE wirkungsgrad (`ID` INT AUTO_INCREMENT PRIMARY KEY,`Datum` TIMESTAMP DEFAULT CURRENT_TIMESTAMP,`Wirkungsgrad` FLOAT(5,2))")