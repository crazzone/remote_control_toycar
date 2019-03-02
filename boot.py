# This file is executed on every boot (including wake-boot from deepsleep)
import esp
esp.osdebug(None)
from machine import PWM, Pin
import gc
import webrepl
import network
webrepl.start()
gc.collect()

wlan = network.WLAN(network.STA_IF) # create station interface
wlan.active(True)       # activate the interface
wlan.connect('nckuasme', 'nckuasme') # connect to an AP
wlan.ifconfig()  
ap = network.WLAN(network.AP_IF) # create access-point interface
ap.active(False)         # activate the interface



