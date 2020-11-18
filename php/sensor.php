<?php 
// connector mit totmannschalter - Westiform
// 26.07.2020 Alfred Müller purecrea gmbh  (purecrea.com)
error_reporting(-1);
ini_set('display_errors', true); 

date_default_timezone_set('Europe/Paris');

require_once('asset/config.php');

// Parameter to handle string from sensor
$mac 		= $_GET["id"];
$sco2 		= $_GET["c"];
$stemp		= $_GET["t"];
$shum 		= $_GET["h"];
$slux		= $_GET["l"];

// Parameters
$datum 		= date("Y-m-d H:i:s");
$statusneu 	= 1;	// State of a new sensor
$sname		= "CO2Ampel (neu)";

try {
	$conn = new PDO("mysql:host=$servername;dbname=$dbname", $username, $password);
	$conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

	
 }  
catch(PDOException $e)
    {
    echo "Error: " . $e->getMessage();
    }

// Test for new sensor
$stmt = $conn->prepare("SELECT * FROM Sensor WHERE 	smac=:MAC;");
$stmt->bindParam(':MAC', $mac, PDO::PARAM_STR, 60);
$stmt->execute();
$row =$stmt->fetch(PDO::FETCH_ASSOC);

if ($row["id_sensor"]) {
	// Save record
	$stmt = $conn->prepare("INSERT SensorData SET id_sensor=:IDS, co2=:CO, cels=:CE, hum=:HU, lux=:LU, reading_time=:LAST");
	$stmt->bindParam(':IDS', $row["id_sensor"] , PDO::PARAM_INT, 10);
	$stmt->bindParam(':CO', $sco2  , PDO::PARAM_STR,6);
	$stmt->bindParam(':CE', $stemp  , PDO::PARAM_STR,6);
	$stmt->bindParam(':HU', $shum  , PDO::PARAM_STR,6);
	$stmt->bindParam(':LU', $slux , PDO::PARAM_STR, 7);
	$stmt->bindParam(':LAST', $datum , PDO::PARAM_STR);
	$stmt->execute();
}else{
	if ($slux <> ""){
		// Insert new sensor
		$stmt = $conn->prepare("INSERT Sensor SET smac=:MAC, sname=:name, firstseen=:LAST");
		$stmt->bindParam(':MAC', $mac , PDO::PARAM_STR, 30);
		$stmt->bindParam(':name', $sname , PDO::PARAM_STR, 220);
		$stmt->bindParam(':LAST', $datum , PDO::PARAM_STR);
		$stmt->execute();
		$id_sensor = $conn->lastInsertId();
		
		if ($sco2 == 0){ // Fail after start stop
			$sco2  = 400;
		}		
		
		// Save record for new sensor
		$stmt = $conn->prepare("INSERT SensorData SET id_sensor=:IDS, co2=:CO, cels=:CE, hum=:HU, lux=:LU, reading_time=:LAST");
		$stmt->bindParam(':IDS', $id_sensor , PDO::PARAM_INT, 10);
		$stmt->bindParam(':CO', $sco2  , PDO::PARAM_STR,6);
		$stmt->bindParam(':CE', $stemp  , PDO::PARAM_STR,6);
		$stmt->bindParam(':HU', $shum  , PDO::PARAM_STR,6);
		$stmt->bindParam(':LU', $slux , PDO::PARAM_STR, 7);
		$stmt->bindParam(':LAST', $datum , PDO::PARAM_STR);
		$stmt->execute();
	}
}

$conn=null;
?>
	
