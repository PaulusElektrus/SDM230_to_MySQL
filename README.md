# TUM DESL Project with ESP32 for drehzahl acquisition
# Readme NOT Up to date!
# EASTRON_Modbus_Visualization_with_Grafana

Generally to install the software you need these packages and software:

mysql-connector-python, sdm_modbus, mysql Database, Apache Server, phpmyAdmin, grafana

Don`t forget to use a virtual environment while developing...

## How to:

1) In the Command Line: "pip install mysql-connector-python sdm_modbus"

2) Install Apache Server, phpmyAdmin, mysql, grafana (When using Windows the first three software components are bundeled in XAMPP)

3) Open phpmyadmin --> http://localhost/phpmyadmin/ and add a new database "messwerte"

3) Start sql_initial.py first once to add the correct table for your device in the database, don`t forget to enter your mysql credentials.

4) Now you can run modbus_main.py and the data will be acquised and stored in your database.

5) Open localhost:3000 in your browser and you can access grafana with credentials "admin" & "admin"

6) Add your mysql as datasource and start building dashboards. I exported also my dashboard Grafana Dashboard.json. That`s it! :-)

## Terminal Testing App:

For testing purposes with your device you can use modbus_terminal_app.py in the terminal:

Like this: "python modbus_terminal_app.py COM5" <-- You have to specify where your device is here.

Big Thanks to https://github.com/nmakel/sdm_modbus