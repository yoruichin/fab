#!/usr/bin/python3
#
# display_temperature
#
# receive and display temperature
# hello.temp.45.py serial_port
#
# Written by Yue Siew Chin
# Fablab Singapore, 2016

import matplotlib.pyplot as plt
from numpy import log
from drawnow import *
import serial

 
#plt.ion() # interactive mode to plot live data
tempV=[]

filter = 0.0
eps = 0.5
cnt = 0
SerialData = serial.Serial('COM9',9600)


def makeGraph():        # a function that makes desire plot 
    plt.ylim(22,32)     # y axis limiter
    plt.title('Live Temperature Sensor')
    plt.grid(True)
    plt.ylabel('Temperature (Celcius)')
    plt.xlabel('time')
    plt.plot(tempV, "bo-", label='Temperature') # blue round dot
    plt.legend(loc='upper left')
     
    
while True:
    global low, high
    
    byte2 = 0
    byte3 = 0
    byte4 = 0
    SerialData.flush() 
    while 1:
      #
      # find framing 
      #
      byte1 = byte2
      byte2 = byte3
      byte3 = byte4
      byte4 = ord(SerialData.read())
      if ((byte1 == 1) & (byte2 == 2) & (byte3 == 3) & (byte4 == 4)):
         break
        
    low = ord(SerialData.read())
    high = ord(SerialData.read())
    print(low)
    print(high)
    value = 256*high + low
    
    
    if (value > 511):
      value -= 1024                     # value = value - 1024
    V = 2.5 - value*5.0/(20.0*512.0)    # Voltage out (Vo) = R / (R + 10K) * Vcc = 2.5
    R = 10000.0/(5.0/V-1.0)
    B = 3950.0
    R25 =  10000.0
    T = 1.0/(log(R/R25)/B+(1/(25.0+273.15))) - 273.15
    filter = (1-eps)*filter + eps*T

    temp = float(filter)
    tempV.append("%.2f" % temp)         # Build our array by appending temperature readings
    print("%.2f" % temp)
    drawnow(makeGraph)                  # call drawnow to draw live graph
    plt.pause (.0001)
    cnt=cnt+1
    if(cnt>30):                         # delete the first item from the array
        tempV.pop(0)                    # this allows us to just see the last 30 data points
    



