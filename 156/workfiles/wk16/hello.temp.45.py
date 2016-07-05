#!/usr/bin/python3
#
# hello.temp.45.py
#
# receive and display temperature
# hello.temp.45.py serial_port
#
# Neil Gershenfeld
# CBA MIT 3/27/12
#
# (c) Massachusetts Institute of Technology 2012
# Permission granted for experimental and personal use;
# license for commercial sale available from MIT
#
# Edited by Yue Siew Chin
# Fablab Singapore, 2016

from tkinter import *
from numpy import log
from tkinter import ttk 
import serial

WINDOW = 600 # window size
eps = 0.5 # filter time constant
filter = 0.0 # filtered value
ctemp = 0.0
ftemp = 0.0

def idle(parent,canvas):
   global filter, eps, ctemp, ftemp, text2
   #
   # idle routine
   #
   byte2 = 0
   byte3 = 0
   byte4 = 0
   ser.flush()
   while 1:
      #
      # find framing 
      #
      byte1 = byte2
      byte2 = byte3
      byte3 = byte4
      byte4 = ord(ser.read())
      if ((byte1 == 1) & (byte2 == 2) & (byte3 == 3) & (byte4 == 4)):
         break
   low = ord(ser.read())
   high = ord(ser.read())
   value = 256*high + low
   print(value)
   
   if (value > 511):
      value -= 1024     # value = value - 1024
   V = 2.5 - value*5.0/(20.0*512.0)    # Voltage out (Vo) = R / (R + 10K) * Vcc = 2.5
   R = 10000.0/(5.0/V-1.0)
   # NHQ103B375R5
   # R25 10000 (O)
   # B (25/85) 3750 (K)
   # R(T(C)) = R(25)*exp(B*(1/(T(C)+273.15)-(1/(25+273.15))))
   B = 3950.0
   R25 =  10000.0
   T = 1.0/(log(R/R25)/B+(1/(25.0+273.15))) - 273.15
 
   filter = (1-eps)*filter + eps*T
   x = int(.2*WINDOW + (.9-.2)*WINDOW*(filter-20.0)/10.0)

   ctemp = filter
   ftemp = (ctemp*9.0)/5.0+32  # Celcius to Fahrenheit
   display_temp()
   #canvas.itemconfigure("text",text="%.2f"%filter)
   #canvas.itemconfigure("text1",text="%s"%T)
   canvas.coords('rect1',.1*WINDOW,.06*WINDOW,x,.1*WINDOW)
   canvas.coords('rect2',x,.06*WINDOW,.95*WINDOW,.1*WINDOW)
   canvas.update()  
   parent.after_idle(idle,parent,canvas)


def display_temp():
      if rbVar.get() == 2: # display Fahrenheit
         text2 = "°F"
         canvas.itemconfigure("text2",text="%s"%text2)
         canvas.itemconfigure("text",text="%.2f"%ftemp) 
         
      else: # display Celcius
         text2 = "°C"
         canvas.itemconfigure("text2",text="%s"%text2)
         canvas.itemconfigure("text",text="%.2f"%ctemp) 

         
#
#  check command line arguments
#
if (len(sys.argv) != 2):
   print ("command line: hello.temp.45.py serial_port")
   sys.exit()
port = sys.argv[1]
#
# open serial port
#
ser = serial.Serial(port,9600)
ser.setDTR()
#
# start plotting
#
root = Tk()
rbVar = IntVar()
root.title('Environment Temperature Sensor (Press Q to exit)')
root.bind('q','exit')

canvas = Canvas(root, width=WINDOW, height=.25*WINDOW)
#root.resizable(False,False)
canvas.create_text(.5*WINDOW,.15*WINDOW,text=".33",font=("impact", 30),tags="text",fill="#ff0000")
canvas.create_text(.62*WINDOW,.15*WINDOW,text="°C",font=("impact", 30),tags="text2",fill="#ff0000")
canvas.create_rectangle(.2*WINDOW,.06*WINDOW,.2*WINDOW,.2*WINDOW, tags='rect1', fill='#ff880e') 
canvas.create_rectangle(.3*WINDOW,.06*WINDOW,.9*WINDOW,.2*WINDOW, tags='rect2', fill='#944605') 
canvas.create_text(.55*WINDOW,.22*WINDOW,text='By Yue Siew Chin | Fablab Singapore | 2016',font=("Arial", 9),fill="black")
rb1 = ttk.Radiobutton(root, text='Celcius °C ', variable=rbVar, value=1, command=display_temp).place(x=220,y=10)
rb2 = ttk.Radiobutton(root, text='Fahrenheit °F', variable=rbVar, value=2, command=display_temp).place(x=320,y=10)
canvas.pack()
root.after(100,idle,root,canvas)
root.mainloop()
