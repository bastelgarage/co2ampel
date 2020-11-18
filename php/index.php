<!doctype html>
<html>
<head>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
	<!-- initial scale 1 for mobile website -->
	<meta http-equiv="X-UA-Compatible" content="IE=edge">
	<title>CO2 -Ampel Backend</title>
	<meta name="apple-mobile-web-app-title" content="CO2-Ampel">
	<link href="asset/css/style.css" rel="stylesheet" type="text/css">
	<link href="asset/css/bootstrap-4.3.1.css" rel="stylesheet" type="text/css">

	<!-- Javascript's powerful AJAX load() is used to load data tiles from load_dashboard_tiles.php every 2 seconds -->
	<script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
	<script type="text/javascript">
		var auto_refresh = setInterval(
			function () {
				$( '#load_sensor_tiles' ).load( 'sensor_tiles.php' ).fadeIn( "slow" );
			}, 60000 ); // refresh every 60 seconds
	</script>
</head>

<body>

	<nav class="navbar navbar-expand-lg navbar-dark bg-dark shadow">
		<a class="navbar-brand" href="/index.php"><i class="far fa-chart-bar math-red"></i> CO2-Ampel Dashboard</a>
	</nav>

	<div class="container mt-3">
		<!-- dashboard tiles -->
		<div class="container-fluid">
			<h1 class="display-4 text-secondary mb-2">CO2 - Ampeln</h1>
			<!-- Javascript's AJAX load() method updating dashboard tiles will be loaded here from sensor_tiles.php and replaces the bootstrap spinner animation -->
			<div id="load_sensor_tiles">
				<div class="spinner-border text-primary m-5 dark-mode" style="width: 3rem; height: 3rem;" role="status">
					<span class="sr-only">Laden...</span>
					<!-- this will be replaced by the loading dashboard tiles -->
				</div>
			</div>
			<div class="container quote">
				<blockquote class=" blockquote my-4">
					<p class="mb-0 text-secondary">Neue Ampeln</p>
					<footer class="blockquote-footer"> <cite title="Source Title">Bitte zuweisen</cite>
					</footer>
				</blockquote>
			</div>
		</div>
		<div class="container container-spacer"></div>
		<!-- Bootstrap footer-->
		<nav class="navbar fixed-bottom navbar-dark bg-primary-custom text-center p-0 m-0">
			<div class="col-md-8 col-xs-6 p-0">
			</div>
			<div class="author-bg col-md-4 col-xs-6 p-0"><span class="author-text navbar-text bottom text-primary">
                    © by Alf Müller purecrea gmbh<i class="fas fa-copyright"></i> 2020
                </span>
			
			</div>
		</nav>
		<script type="text/javascript">
			// load on start
			$( '#load_sensor_tiles' ).load( 'sensor_tiles.php' ).fadeIn( "slow" );
		</script>
</body>
</html>