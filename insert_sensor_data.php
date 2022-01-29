<?php

if(isset($_GET["drehzahl"])) {
   $drehzahl = $_GET["drehzahl"]; // get temperature value from HTTP GET

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

   $sql = "INSERT INTO sdm230 (drehzahl) VALUES ($drehzahl)";

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

