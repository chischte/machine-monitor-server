
<?php
// Create Data base if not exists
$servername = "machinelogger.synology.me";
$username = "machineloguser";
$password = "demopassword";

// Create connection
$conn = new mysqli($servername, $username, $password);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Create database
$sql = "CREATE DATABASE machinelogger";
if ($conn->query($sql) === TRUE) {
    echo "Database created successfully";
} else {
    echo "Error creating database: " . $conn->error;
}

$conn->close();

echo "<br>";
// Connect to database and create table
$servername = "machinelogger.synology.me";
$username = "machineloguser";
$password = "demopassword";
$dbname = "machinelogger";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Sr No, Station, Status(OK, NM, WM, ACK) Date, Time
// 1 A NM 12-5-18 12:15:00 am
// sql to create table
$sql = "CREATE TABLE logs (
	id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
	testrig VARCHAR(30),
	status VARCHAR(30),
	cyclereset VARCHAR(30),
    cycletotal VARCHAR(30),
	`TimeStamp` TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
   )";

if ($conn->query($sql) === TRUE) {
    echo "Table logs created successfully";
} else {
    echo "Error creating table: " . $conn->error;
}

$conn->close();
?>
