<?php

$con = new mysqli("machinelogger.synology.me", "michi", "uint8_t0-255", "MACHINE_LOG_DB");

if (mysqli_connect_errno())
{
echo "Failed to connect to MySQL: " . mysqli_connect_error();
}

$result = mysqli_query($con,"SELECT * FROM machinelog");

echo "<table border='1'>
<tr>
<th>TestRig</th>
<th>Status</th>
<th>  Anzahl Zyklen___  </th>

</tr>";

while($row = mysqli_fetch_array($result))
{
echo "<tr>";
echo "<td>" . $row['machine_id'] . "</td>";
echo "<td>" . $row['machine_status'] . "</td>";
echo "<td>" . $row['cycles'] . "</td>";
echo "</tr>";
}
echo "</table>";

mysqli_close($con);
?>