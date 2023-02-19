# Running your CO2-Ampel with ESPhome

ESPhome is a different way to programm your ESP8266 development boards. It's
more like that you have to describe what you want your device to do than
actually write code. ESPhome is taking care of the translation.


**This is incomplete!**

## Features

- OTA
- Web interface
- MQTT
- Fall-back WLAN AP `co2ampel`
- Logging to serial console

## Setup

Follow this [installation guide](https://esphome.io/guides/getting_started_command_line.html) to set up ESPHome.

In short:

```bash
pip install esphome
```

## Flashing

Create the `secrets.yaml` file for the details you don't want to share like passwords, usersname and alike. Or
rename the sample file: `secrets.sample.yaml`.

```bash
touch secrets.yaml
```

```text
# Wifi
wifi_ssid: wireless3
wifi_password: Netzgesichert

# AP for fall-ack
wifi_ap_ssid: co2ampel
wifi_ap_password: co2ampel

# MQTT
mqtt_broker: 192.168.1.20
mqtt_username: mqtt
mqtt_password: mqtt
```

Flash the firmware. The very first run will take some time as additional parts needs to be downloaded.

```bash
esphome co2ampel.yml run
```

At some point you have to choose your upload port:

```bash
INFO Successfully compiled program.
Found multiple options, please choose one:
  [1] /dev/gps0 (USB-Serial Controller D)
  [2] /dev/ttyUSB0 (USB-Serial Controller D)
  [3] /dev/ttyUSB1 (USB2.0-Serial)
(number): 
```
