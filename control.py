# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt
import time
import pyfirmata
import datetime
import matplotlib.animation as animation

class Motor:
	'Common base class for all employees'
	MotCount = 0

	def __init__(self, pos, l, w):
		Motor.MotCount += 1
		self.vel = 0
		self.pos = pos
		self.l = l
		self.w = w

	def set_vel(self, v, ang):
		ang = ang*np.pi/180
		a = self.l/(np.tan(ang) + 1e-5)
		if self.pos=='der':
			self.vel = v*(1 + self.w/2/a)
		elif self.pos=='izq':
			self.vel = v*(1 - self.w/2/a)
	

def ang2ang(x):
	return 90*(x - 1) + 45
	

def init():
	ax1.set_ylim(-50, 50)
	ax1.set_xlim(0, 100)
	ax2.set_ylim(0, 55)
	ax2.set_xlim(0, 100)
	del xdata[:]
	del ydata[:]
	line1.set_data(xdata, ydata)
	line3.set_data(xdata, ydata)
	return line1,


def run(t):
    	# update the data
	vel = 40*A0.read()
	ang = ang2ang(A1.read())
	m_izq.set_vel(v=vel, ang=ang)
	m_der.set_vel(v=vel, ang=ang)
	D3.write(m_izq.vel/40)

	print(A2.read())
	ydata.append(vel)
	y1data.append(ang)

	y_izq.append(m_izq.vel)
	y_der.append(m_der.vel)


	xdata.append(len(ydata))

	xmin, xmax = ax1.get_xlim()
	if t>n:
		ax1.set_xlim(xdata[t - n], xdata[t])
		ax2.set_xlim(xdata[t - n], xdata[t])
		ax1.figure.canvas.draw()
		ax2.figure.canvas.draw()
	if t>n:
		line1.set_data(xdata[t - n:], ydata[t - n:])
		line2.set_data(xdata[t - n:], y1data[t - n:])
		line3.set_data(xdata[t - n:], y_izq[t - n:])
		line4.set_data(xdata[t - n:], y_der[t - n:])
	else:
		line1.set_data(xdata, ydata)
		line2.set_data(xdata, y1data)
		line3.set_data(xdata, y_izq)
		line4.set_data(xdata, y_der)
	return line1,


fig = plt.figure() 
ax1 = fig.add_subplot(2, 1, 1)
ax2 = fig.add_subplot(2, 1, 2)

line1, = ax1.plot([], [], lw=2, label='velocidad')
line2, = ax1.plot([], [], lw=2, label='angulo')
line3, = ax2.plot([], [], lw=2, label='motor izq', color='red')
line4, = ax2.plot([], [], lw=2, label='motor der', color='navy')

ax1.grid()
ax2.grid()

xdata = []
ydata = []
y1data = []
y_der = []
y_izq = []

l = 2
w = 1
m_izq = Motor(pos='izq', l=l, w=w)
m_der = Motor(pos='der', l=l, w=w)
n = 100 # muestras plot

port = '/dev/ttyACM0' # puerto donde esta conectado el arduino (hay que cambiarlo dependiendo del pc)
board = pyfirmata.Arduino(port) # crea objeto como arduino en puerto anterior

it = pyfirmata.util.Iterator(board) # para que el buffer no haga overflow
it.start()

A0 = board.get_pin('a:0:i') # define pin analogico A0 como input
A1 = board.get_pin('a:1:i') # define pin analogico A0 como input
A2 = board.get_pin('a:2:i')
D2 = board.get_pin('d:2:o') # define pin digital D2 como input (ampolleta 1)
D3 = board.get_pin('d:3:p') # pwm

D3.write(0.50)

ani = animation.FuncAnimation(fig=fig, func=run, blit=False, interval=1, repeat=False, init_func=init)

fig.legend()
plt.show()
