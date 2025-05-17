# Heater_arduino

This project is Arduino UNO based. Its a basic heater device made using Arduino uno, DHT22 sensor, use of buzzer as a feedback loop and rgb led to show heater response.
The entire project was simulated in wokwi- https://tinyurl.com/4sxm6hua
---------------------------------------------------------------
Major features of this projects:

1. Temperature-Based State Tracker- I have implemented the required states:
  •	Idle: This is when the sensor is giving an error, and you stop the motor and turn off the RGB.

  •	Heating: If the temperature is below 25°C, it goes into the "HEATING" state.
  
•	Stabilizing: When the temperature is between 25°C and 35°C, it enters "STABILIZING."

•	Target Reached: When the temperature reaches between 35°C and 35.5°C, it shows "TARGET REACHED."

•	Overheat: When the temperature exceeds 40°C, it switches to "OVERHEAT."

3. Continuous Temperature Reading: continuously reading the temperature every 2 seconds with dht.readTemperature() in the loop() function.

4. Heater On/Off Based on Thresholds: (HEATING, STABILIZING, TARGET REACHED, OVERHEAT) are correctly linked to temperature thresholds. The heater should turn on/off automatically based on the temperature reading.

5. Logging Temperature and Heater Status Over Serial: Logging the temperature and the current state to the Serial Monitor with the following line:

       cpp
        Copy code
        Serial.print("Temperature: ");
        Serial.print(temp);
        Serial.print(" °C  |  State: ");

This logs both the temperature and the corresponding heater state.

6. Additional Elements:

•	The RGB LED provides a visual cue for each state: Red for heating, Orange for stabilizing, Green for target reached, Blue for overheating, and White in case of an overheat alert.

•	The buzzer alerts with different pitches corresponding to each state.

•	The stepper motor behavior (stopping when overheating and slowly rotating when heating) is implemented with stepper.stop() in the overheating case and controlling motor speed in the "HEATING" state.


----------------------------------------------
Libraries installed in wokwi are

![image](https://github.com/user-attachments/assets/83ecdc0b-ff41-4cc9-bf1d-56cb30fd827d)
--------------------------------------------------------------------------------------

The connection diagram:

![image](https://github.com/user-attachments/assets/db608fc0-f75b-4d72-bc0c-b262006845f3)
