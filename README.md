# remote_control_toycar

This is a project for asme 2019 competition.

![](https://i.imgur.com/9I0JE1H.jpg)

# How to connect all devices?
4 L298n motor drivers control 8 motors.

1 arduino mega board controls 4 L298n.(arduino language)

Build an http API(GET action) on esp8266 board to gets user command from tablet and cellphone and send keyword to arduino(5v) by low-voltage-uart(3.3v).(micropython)

2 joysticks connect with a tablet with ubuntu.(c++)

(I want to use python-like language only in the future)

# Do we have some problems?
1. 4 motor need different voltage value for same speed.

2. App inventor's APM(Actions Per Minute) is too low.

3. One L298n control 2 movement motor will have very high temperature.

4. Our toycar have some delay problems because a iron flat weakens the wireless connection.
