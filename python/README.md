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

## Testing

To test if the server is able to get the data, use `httpie` or `curl` to create a request. 

```bash
http --form POST http://192.168.1.2/co2ampel id=B4:E7:2D:5A:52:85 c=1 t=2 h=3 l=4
```
