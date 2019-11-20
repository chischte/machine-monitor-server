<?php

$mysqli = new mysqli("84.74.164.121", "michi", "uint8_t0-255", "MACHINE_LOG_DB");

 
$query = "SELECT * FROM machinelog";
echo "<b> <center>Database Output</center> </b> <br> <br>";
 
if ($result = $mysqli->query($query)) {
 
    while ($row = $result->fetch_assoc()) {
        $field1name = $row["col1"];
        $field2name = $row["col2"];
        $field3name = $row["col3"];
        $field4name = $row["col4"];
        $field5name = $row["col5"];
 
        echo '<b>'.$field1name.$field2name.'</b><br />';
        echo $field5name.'<br />';
        echo $field5name.'<br />';
        echo $field5name;
    }
 
/*freeresultset*/
$result->free();
}
