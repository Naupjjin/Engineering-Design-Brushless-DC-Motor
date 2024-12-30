# Engineering-Design-Brushless-DC-Motor-RPM Measurement 
> Author: 堇姬Naup

This project demonstrates how to measure and display the RPM (Revolutions Per Minute) of a rotating object using an Arduino, an I2C LCD module, and a magnetic sensor. The system includes real-time RPM calculation, tracking the maximum RPM, and computing the average RPM over time.

## Installation    
```bash
git clone https://github.com/yourusername/rpm-measurement.git
cd rpm-measurement
```

update to your arduino.

## Usage
The LCD displays:
- R=Current RPM
- M=Maximum RPM
- A=Average RPM

## Function intro

| Function Name         | Purpose                                   |
|-----------------------|-------------------------------------------|
| `counter`             | Handles Hall sensor interrupts and counts triggers. |
| `setup`               | Initializes the LCD, variables, and interrupts. |
| `RPM_CAL_MAX`         | Updates the maximum RPM value.           |
| `RPM_CAL_AVERAGE`     | Accumulates valid RPM values and calculates the average RPM. |
| `display_lcd_num`     | Displays current, maximum, and average RPM values on the LCD. |
| `loop`                | Calculates and updates RPM values, handles LCD refresh. |
