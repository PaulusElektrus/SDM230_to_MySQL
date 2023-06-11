<?php

if(isset($_GET["drehzahl"])) {
   isset($_GET["flowRate"]);
   isset($_GET["total"]);
   $drehzahl = $_GET["drehzahl"]; // get drehzahl value from HTTP GET
   $flowRate = $_GET["flowRate"];
   $total = $_GET["total"];
   
   $servername = "localhost";
   $username = "root";
   $password = "";
   $database_name = "messwerte";

   // Create MySQL connection fom PHP to MySQL server
   $connection = new mysqli($servername, $username, $password, $database_name);
   // Check connection
   if ($connection->connect_error) {
      die("MySQL connection failed: " . $connection->connect_error);
   }

   $sql = "INSERT INTO esp32 (ID,Datum,drehzahl,flowRate,total) VALUES (ID,UTC_TIMESTAMP(),$drehzahl,$flowRate,$total)";

   if ($connection->query($sql) === TRUE) {
      echo "New record created successfully";
   } else {
      echo "Error: " . $sql . " => " . $connection->error;
   }

   $connection->close();
} else {
   echo "drehzahl is not set in the HTTP request";
}
?>

