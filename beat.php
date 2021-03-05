<?php
$data = $_POST["beat"];
$file = 'beat.html';
file_put_contents($file, $data);
?>
