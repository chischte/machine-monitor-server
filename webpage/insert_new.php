<?php

$con = new mysqli("84.74.164.121", "michi", "uint8_t0-255", "MACHINE_LOG_DB");

if (mysqli_connect_errno())
{
echo "Failed to connect to MySQL: " . mysqli_connect_error();
}

$result = mysqli_query($con,"SELECT * FROM machinelog");

echo "<table border='1'>
<tr>
<th>machine_id</th>
<th>machine_status</th>
</tr>";

while($row = mysqli_fetch_array($result))
{
echo "<tr>";
echo "<td>" . $row['machine_id'] . "</td>";
echo "<td>" . $row['machine_status'] . "</td>";
echo "</tr>";
}
echo "</table>";

mysqli_close($con);
?>