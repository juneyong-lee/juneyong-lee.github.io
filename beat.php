<?php
$file = 'beat.html';
$data = $_POST["beat"];
file_put_contents($file, $data);
?>
