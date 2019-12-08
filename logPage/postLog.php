<?php
// Creates new record as per request
// Connect to database
$servername = "machinelogger.synology.me";
$username = "machineloguser";
$password = "demopassword";
$dbname = "machinelogger";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Database Connection failed: " . $conn->connect_error);
}

// Get current date and time
date_default_timezone_set('Europe/Zurich');
$d = date("Y-m-d");
// echo " Date:".$d."<BR>";
$t = date("H:i:s");

if (! empty($_POST['testrig']) && ! empty($_POST['status']) && ! empty($_POST['cyclereset']) && ! empty($_POST['cycletotal'])) {
    $testrig = $_POST['testrig'];
    $status = $_POST['status'];
    $cyclereset = $_POST['cyclereset'];
    $cycletotal = $_POST['cycletotal'];

    $rigname = 'PTH STANDARD';
    $rigid = '1';

    if (strcomp($testrig, $rigid)==0) { //0 = Strings are equal
        $testrig = $rigname;
    }

    $sql = "INSERT INTO logs (testrig, status, cyclereset, cycletotal)
		
		VALUES ('" . $testrig . "', '" . $status . "', '" . $cyclereset . "', '" . $cycletotal . "')";

    if ($conn->query($sql) === TRUE) {
        echo "OK";
    } else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }
}

$conn->close();
?>