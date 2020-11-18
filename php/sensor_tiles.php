<?php
session_start();

error_reporting(-1);
ini_set('display_errors', true); 

require_once('asset/config.php');

	try {
		$conn = new PDO("mysql:host=$servername;dbname=$dbname", $username, $password);
		$conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

	 }  
	catch(PDOException $e)
		{
		echo "Error: " . $e->getMessage();
		}

	$stmt = $conn->prepare("SELECT * FROM Sensor ORDER BY sname;");
	$stmt->execute();


	while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {

		$stmtS = $conn->prepare("SELECT * FROM SensorData WHERE id = (SELECT MAX(id) FROM SensorData WHERE `id_sensor` =".$row["id_sensor"] .")");
		$stmtS->execute();
		$rowS = $stmtS->fetch();
		
		$myDateTime = DateTime::createFromFormat('Y-m-d H:i:s', $rowS["reading_time"]);
		$newDateString = $myDateTime->format('d.m.Y H:i:s');
    ?>

	<div class="container quote">
                <blockquote class=" blockquote my-4">
                    <p class="mb-0 text-secondary"><a href="#"><strong><?php echo($row["sname"]);?></strong></a> <cite title="Source Title">  - <?php echo($newDateString);?> - <?php echo($row["smac"]);?></cite></p>
                    
                </blockquote>
            </div>
    <!-- Draw the card deck -->
    <div class="card-deck">
        <div class="card text-secondary bg-dark mb-3 shadow">
            
            <div class="card-body">
                <h5 class="card-title">CO₂</h5>
                <!--print reading here-->
                <h1 class="card-title text-success"><?php echo($rowS["co2"]);?> ppm</h1>
                 <p class="card-text">
                   
                </p>
            </div>
        </div>

        <div class="card text-secondary bg-dark mb-3 shadow">
          
            <div class="card-body">
                <h5 class="card-title">Temperatur</h5>
                <!--print reading here-->
                <h1 class="card-title text-primary"><?php echo($rowS["cels"]);?>°C</h1>
                <!-- <h2 class="card-title text-primary">millibar</h2> -->
                <p class="card-text">
                   
                </p>
            </div>
        </div>

        <div class="card text-secondary bg-dark mb-3 shadow ">
   
            <div class="card-body">
                <h5 class="card-title">Luftfeuchtigkeit</h5>
                <!--print reading here-->
                <h1 class="card-title text-info"><?php echo($rowS["hum"]);?> %</h1>
                <p class="card-text">
                   
                </p>
            </div>
        </div>
		
		   <div class="card text-secondary bg-dark mb-3 shadow">
 
            <div class="card-body">
                <h5 class="card-title">Lichtstärke</h5>
                <!--print reading here-->
                <h1 class="card-title text-warning"><?php echo($rowS["lux"]);?> Ω</h1>
                <p class="card-text">
                   
                </p>
            </div>
        </div>
    </div>
    </div>



    <?php
		}
  $conn.close
    ?>