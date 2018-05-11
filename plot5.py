#import serial
from tkinter import *
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import style
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import time
import numpy as np
import pyfirmata

from Motor import *
from Pid import *


def ang2ang(x):
	return 90*(x - 1) + 45


def animate(i):
	#ser.reset_input_buffer()
	#data = ser.readline().decode("utf-8")
	#data_array = data.split(',')
	#yvalue = float(data_array[1])
	t1 = time.time()
	vel_set = Bvel.get()
	ang = Bang.get()
	m_I.set_vel(v=vel_set, ang=ang)
	m_D.set_vel(v=vel_set, ang=ang)

	y1.append(ang)
	y2.append(vel_set)
	y3.append(m_I.get_vel())
	y4.append(m_D.get_vel())	
	xar.append(np.around(t1 - ti, 2))
	n = len(xar)

	if n<N:
		line1.set_data(xar, y1)
		line2.set_data(xar, y2)
		line3.set_data(xar, y3)
		line4.set_data(xar, y4)
		ax1.set_xlim(0, xar[-1])
		ax2.set_xlim(0, xar[-1])
		ax3.set_xlim(0, xar[-1])
		ax1.set_ylim(min(y1) - 1, max(y1) + 1)
	else:
		ynew1 = y1[-N:]
		line1.set_data(xar[-N:], ynew1)
		line2.set_data(xar[-N:], y2[-N:])
		line3.set_data(xar[-N:], y3[-N:])
		line4.set_data(xar[-N:], y4[-N:])
		ax1.set_xlim(xar[-N], xar[-1])
		ax2.set_xlim(xar[-N], xar[-1])
		ax3.set_xlim(xar[-N], xar[-1])
		ax1.set_ylim(min(ynew1) - 1, max(ynew1) + 1)
	t2 = time.time()
	print('lag', t2 - t1)
	return


def _quit():
	root.quit()     # stops mainloop
	root.destroy()  # this is necessary on Windows to prevent Fatal Python Error: PyEval_RestoreThread: NULL tstate
	return


def refresh():
	ax1.clear()
	return


def set_mean():
	return m

"""
#-------------------------------------------
# Arduino
port = '/dev/ttyACM0' # puerto donde esta conectado el arduino (hay que cambiarlo dependiendo del pc)
board = pyfirmata.Arduino(port) # crea objeto como arduino en puerto anterior

it = pyfirmata.util.Iterator(board) # para que el buffer no haga overflow
it.start()

A0 = board.get_pin('a:0:i')
A1 = board.get_pin('a:1:i')
A2 = board.get_pin('a:2:i')
A3 = board.get_pin('a:3:i')
D5 = board.get_pin('d:5:p') # pwm motor 1
D6 = board.get_pin('d:6:p') # pwm motor 2

"""
#-----------------------------------------------------
# Gui
root = Tk()
root.geometry('1200x700+200+100')
root.title('Display Controlador')
#root.state('zoomed')
root.config(background='#fafafa')


#---------------------------------------------------
# Data
xar = []
y1 = []
y2 = []
y3 = []
y4 = []
y5 = []
y6 = []
N = 100
ti = time.time()

#-------------------------------------------------------
# Car configuration
l = 2
w = 1
m_I = MotorIzquierdo(l, w)
m_D = MotorDerecho(l, w)
pid = PID(kp=1, kd=1, ki=1, o_min=0, o_max=1)

#---------------------------------------------------
# Plot
style.use('ggplot')
fig = plt.figure(figsize=(14, 10), dpi=100)
ax1 = fig.add_subplot(3, 1, 1)
ax1.set_ylim(0, 100)
ax1.set_ylabel('angulo deg')

ax2 = fig.add_subplot(3, 1, 2)
ax2.set_ylim(0, 100)
ax2.set_ylabel('vel auto V')

ax3 = fig.add_subplot(3, 1, 3)
ax3.set_ylim(0, 100)
ax3.set_ylabel('vel motores V')
ax3.set_xlabel('tiempo s')

line1, = ax1.plot(xar, y1, 'r')
line2, = ax2.plot(xar, y2, 'r')
line3, = ax3.plot(xar, y3, 'r', color='red', label='set', ls='dashed')
line4, = ax3.plot(xar, y4, 'r', color='navy', label='set', ls='dashed')
line5, = ax3.plot(xar, y3, 'r', color='red', label='izq')
line6, = ax3.plot(xar, y4, 'r', color='navy', label='der')

ax3.legend()


#ser = serial.Serial('com3', 9600)


#---------------------------------------------------------
# Buttons and scale
button = Button(master=root, text='Quit', command=_quit)
button2 = Button(master=root, text='Refresh', command=refresh)
Bang = Scale(master=root, from_=-45, to=45, orient=HORIZONTAL, label='angulo')
Bvel = Scale(master=root, from_=0, to=100, orient=HORIZONTAL, label='vel auto')
Bkp = Scale(master=root, from_=-100, to=100, orient=HORIZONTAL, label='kp')
Bkd = Scale(master=root, from_=-100, to=100, orient=HORIZONTAL, label='kd')
Bki = Scale(master=root, from_=-100, to=100, orient=HORIZONTAL, label='ki')

#Bang.grid()

button2.pack(side=BOTTOM)
button.pack(side=BOTTOM)
Bang.pack(side=LEFT)
Bvel.pack(side=TOP)
Bkp.pack(side=LEFT)
Bkd.pack(side=LEFT)
Bki.pack(side=LEFT)




#---------------------------------------------------------------
plotcanvas = FigureCanvasTkAgg(fig, root)
plotcanvas.get_tk_widget().pack()
#plotcanvas.get_tk_widget().grid()
ani = animation.FuncAnimation(fig, animate, interval=1, blit=False)

root.mainloop()
