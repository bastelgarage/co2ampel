# Python backend

The Python backend of a simple demo of running a backend for the CO2-Ampel with [aiohttp](https://docs.aiohttp.org/en/stable/).  

The endpoint that is handling the sensor's data is called `co2ampel`.

The following parameters are sent by the sensor:

`id`: MAC address of the ESP8266
`c`: CO2 level
`t`: Temperature
`h`: Humidity
`l`: Brightness

## Usage

Download the content of this directory and install `aiohttp`, e.g., `pip install aiohttp`.

Run the server:

```bash
$ sudo python server.py 
======== Running on http://0.0.0.0:80 ========
(Press CTRL+C to quit)
```

At the moment you can't set the port where your server is running. Only 80 is supported by the CO2-Ampel.

![Python backend](https://raw.githubusercontent.com/bastelgarage/co2ampel/master/images/python-backend.png)

## Testing

To test if the server is able to get the data, use `httpie` or `curl` to create a request. 

```bash
http --form POST http://192.168.1.2/co2ampel id=39:64:d5:04:08:56 c=1050 t=22.1 h=50 l=390
```
