-- phpMyAdmin SQL Dump
-- version 5.0.4
-- https://www.phpmyadmin.net/

-- Erstellungszeit: 18. Nov 2020 um 12:05
-- Server-Version: 10.3.27-MariaDB-log
-- PHP-Version: 7.2.33

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Datenbank: `co2ampel`
--

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Sensor`
--

CREATE TABLE `Sensor` (
  `id_sensor` int(11) NOT NULL,
  `smac` varchar(50) COLLATE utf8mb4_unicode_ci NOT NULL,
  `sname` varchar(220) COLLATE utf8mb4_unicode_ci NOT NULL,
  `id_user` int(10) NOT NULL,
  `status` int(11) NOT NULL,
  `firstseen` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `SensorData`
--

CREATE TABLE `SensorData` (
  `id` int(6) UNSIGNED NOT NULL,
  `id_sensor` int(10) NOT NULL,
  `co2` decimal(10,1) DEFAULT NULL,
  `cels` decimal(10,1) DEFAULT NULL,
  `hum` decimal(10,1) DEFAULT NULL,
  `lux` decimal(7,0) NOT NULL,
  `reading_time` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Indizes der exportierten Tabellen
--

--
-- Indizes für die Tabelle `Sensor`
--
ALTER TABLE `Sensor`
  ADD PRIMARY KEY (`id_sensor`);

--
-- Indizes für die Tabelle `SensorData`
--
ALTER TABLE `SensorData`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT für exportierte Tabellen
--

--
-- AUTO_INCREMENT für Tabelle `Sensor`
--
ALTER TABLE `Sensor`
  MODIFY `id_sensor` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT für Tabelle `SensorData`
--
ALTER TABLE `SensorData`
  MODIFY `id` int(6) UNSIGNED NOT NULL AUTO_INCREMENT;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
