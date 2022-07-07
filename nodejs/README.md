# NodeJS backend

You need to have [nodejs](https://nodejs.org/en/) and [`npm`](https://www.npmjs.com/) installed on the system
that acts as the backend for the CO2-Ampel.

Keep in mind that there is no persistent storage.

## Setup

Copy the content of this directory and execute:

```bash
npm install
```

## Usage

The server can be running with `node`:

```bash
sudo node server.js 
Server started! Is running at http://localhost:80
```

You can set the enviroment variable `PORT` if you want to run the server on a different port,
e. g., one that doesn't require you to be `root`.

## Testing

To test if the server is able to get the data, use `httpie` or `curl` to create a request. 

```bash
http --form POST http://192.168.1.2:80/co2ampel id=39:64:d5:04:08:56 c=1050 t=22.1 h=50 l=390
```
