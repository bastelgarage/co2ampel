const bodyParser = require('body-parser');

var express = require('express');
var app = express();
var port = process.env.PORT || 80;
app.use(bodyParser.urlencoded({ extended: true }));

var sensors = {};

app.get('/', function (request, response) {
    response.json(sensors);
});

app.post('/co2ampel', function (request, response) {
    console.log('Got body:', request.body);
    response.sendStatus(200);
    var sensor_id = request.body.id;
    var co2 = request.body.c;
    var temperature = request.body.t;
    var humidity = request.body.h;
    var brightness = request.body.l;
    var sensor_data = {
        "co2": co2,
        "temperature": temperature,
        "humitity": humidity,
        "brightness": brightness
    };
    sensors[sensor_id] = sensor_data;
});

// Start the server
app.listen(port);
console.log('Server started! Is running at http://localhost:' + port);
