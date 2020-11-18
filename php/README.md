# PHP backend

- Create a Mysql or MariaDB with `SensorData.sql`
- Save your database connection settings in `asset/config.php`
- Press the button on back of the co2ampel two times (2x) (all LED are green).
- Connect your smartphone/laptop with Wifi SSID `co2ampel` and go to 192.168.4.1 in your browser.
- Set Wifi details. Point to your `sensor.php`, e.g., www.mywebsite.com/sensor.php, as URL in WiFimanger.

## Limitations

- It's HTTP-only. This means that HTTPS is not working out-of-the-box. If you need HTTPS support then you need the fingerprint of your SSL/TLS certificate and the ability to adjust the code.
