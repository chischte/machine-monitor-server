<?php
$output = shell_exec('cd /home/michi/git/machine-monitor-server ; git pull; ls');
echo "<pre>$output</pre>";
?>
