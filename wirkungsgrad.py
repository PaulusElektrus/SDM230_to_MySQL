import mysql.connector
import time
from datetime import datetime
        
def start_script():
    # This function connects to the database and starts the data acquisition
    try:
        # Enter here your mysql credentials
        db = mysql.connector.connect(
            host ="localhost",      #put in IP-adress of raspi
            user ="root",
            password="",
            database = "messwerte",
            )
        cursor = db.cursor()
        while True:
            edit_data(db, cursor)

    except:
        handle_crash()

def edit_data(db, cursor):
    cursor.execute("SELECT Power_Active FROM sdm230")
    input = cursor.fetchall()
    cursor.execute("SELECT Power_L1 + Power_L2 + Power_L3 FROM sdm630")
    output = cursor.fetchall()
    sql = "INSERT INTO wirkungsgrad (`ID`,`Datum`,`Wirkungsgrad`) VALUES (ID,UTC_TIMESTAMP(),%s)"
    val = output / input
    cursor.execute(sql, val)
    db.commit()
    print("Service running! Timestamp: " + str(datetime.now()))
    time.sleep(1)

def handle_crash():
    # This function is the crash handler
    print("Ein Fehler ist aufgetreten, erneuter Versuch in 5 Sekunden.")
    time.sleep(5)
    start_script()
        
start_script()