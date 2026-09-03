# Arduino-Based Blood Pressure Monitoring System

## Overview

This project is an Arduino-based blood pressure monitoring system designed to measure cuff pressure using an HX710B pressure sensor module.

The system uses an Arduino UNO to acquire pressure data from the sensor, perform calibration and signal processing, and continuously display the measured pressure in mmHg through the Arduino Serial Monitor.

The project focuses on sensor interfacing, pressure measurement, calibration, data averaging, and digital filtering to obtain stable and reliable pressure readings.

## Objectives

- Interface the HX710B pressure sensor with an Arduino UNO.
- Measure pressure from a blood pressure cuff.
- Perform automatic zero-offset calibration.
- Reduce sensor noise using multiple-sample averaging.
- Apply digital filtering for smoother pressure readings.
- Convert the sensor output into pressure in mmHg.
- Continuously monitor and display cuff pressure through the Serial Monitor.

## Hardware Used

- Arduino UNO
- HX710B pressure sensor module
- Blood pressure cuff
- Pressure pump
- Connecting wires

## Software Used

- Arduino IDE
- Embedded C / Arduino C++

## System Architecture

The basic system consists of:

Blood Pressure Cuff
        ↓
HX710B Pressure Sensor
        ↓
Arduino UNO
        ↓
Signal Processing
        ↓
Pressure in mmHg
        ↓
Serial Monitor

## Working Principle

1. The blood pressure cuff generates pressure that is sensed by the HX710B pressure sensor.
2. The HX710B provides a 24-bit digital output corresponding to the measured pressure.
3. The Arduino UNO reads the sensor output through the DOUT and SCK pins.
4. Multiple raw sensor readings are collected and averaged to reduce measurement fluctuations.
5. When the system starts, the cuff is kept deflated and an automatic zero-offset calibration is performed.
6. The calibrated sensor value is converted into pressure in mmHg using an experimentally determined scale factor.
7. An exponential smoothing filter is applied to reduce short-term fluctuations in the measured pressure.
8. The resulting pressure value is continuously displayed through the Arduino Serial Monitor.

## Sensor Interface

The HX710B communicates with the Arduino using two digital signals:

- DOUT (Data Output)
- SCK (Serial Clock)

The current implementation uses:

| HX710B | Arduino UNO |
|--------|-------------|
| DOUT   | Digital Pin 2 |
| SCK    | Digital Pin 3 |

## Signal Processing

The system uses multiple stages of signal processing to improve measurement stability.

### 1. Sample Averaging

The system collects multiple sensor readings and calculates their average before converting the value into pressure.

The current implementation uses:

- Number of samples = 20

Averaging multiple readings helps reduce random fluctuations in the sensor output.

### 2. Zero-Offset Calibration

When the system starts, the cuff is kept completely deflated.

The Arduino collects several readings and calculates the baseline sensor value. This baseline is used as the zero-pressure reference.

The calibrated pressure is calculated from the difference between the measured raw value and the baseline.

### 3. Exponential Smoothing

An exponential smoothing filter is applied to the calculated pressure:

Filtered Pressure = α × Current Pressure + (1 − α) × Previous Filtered Pressure

where:

α = 0.2

A lower value of α provides greater smoothing, while a higher value provides a faster response to changes in pressure.

## Calibration

The pressure conversion was calibrated experimentally using known reference pressure values.

The calibration process involved:

- Measuring the sensor output with the cuff deflated.
- Determining the zero-pressure offset.
- Comparing measured pressure against reference pressure values.
- Adjusting the scale factor to improve the correspondence between sensor output and pressure in mmHg.

The current implementation uses an experimentally determined scale factor:

```cpp
scaleFactor = 0.0000252;
```

## Author

**Aanshi Gandhi**  
B.Tech – Electronics & Instrumentation Engineering  
Nirma University

## Hardware Setup

The complete experimental setup consists of the blood pressure cuff, HX710B pressure sensor, Arduino UNO, pressure pump, and the Arduino Serial Monitor used to observe the measured pressure.

![Hardware Setup](hardware_setup.jpeg)
