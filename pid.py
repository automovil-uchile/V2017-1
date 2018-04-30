# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt
import time
import pyfirmata
import datetime
import matplotlib.animation as animation


class PID:
	def __init__(self, kp, ki, kd, o_min, o_max):
		self.kp = kp
		self.ki = ki
		self.kd = kd
		self.e0 = 0
		self.inte = 0
		self.out = 0
		self.min = o_min
		self.max = o_max

	def set_out(self, e):
		#print('kp', self.kp)
		#self.kd = self.kp/2
		#self.ki = self.kp/2
		prop = e*self.kp		
		deri = (e - self.e0)*self.kd
		if self.out!=1 and self.out!=0:
			self.inte += e*self.ki
		self.out = prop + deri + self.inte
		if self.out>self.max:
			self.out = self.max
		elif self.out<self.min:
			self.out = self.min

	def set_kp(self, kp):
		self.kp = kp
	
	def set_ki(self, ki):
		self.ki = ki

	def set_kd(self, kd):
		self.kd = kd


def init():
	ax1.set_ylim(-0.1, 0.4)
	ax1.set_xlim(0, 100)
	ax2.set_ylim(0, 55)
	ax2.set_xlim(0, 100)
	return line1,


def run(t):
    	# update the data
	sett = A0.read()*0.3
	kp = A2.read()
	pid.set_kp(kp=kp)
	act = A1.read()	
	er = sett - act
	error.append(er)
	pid.set_out(error)	
	f = pid.out
	print('out', f)
	D3.write(f)
	actual.append(act)
	sete.append(sett)
	xdata.append(len(actual))

	xmin, xmax = ax1.get_xlim()
	if t>n:
		ax1.set_xlim(xdata[t - n], xdata[t])
		#ax2.set_xlim(xdata[t - n], xdata[t])
		ax1.figure.canvas.draw()
		#ax2.figure.canvas.draw()
	if t>n:
		line1.set_data(xdata[t - n:], actual[t - n:])
		line2.set_data(xdata[t - n:], error[t - n:])
		line3.set_data(xdata[t - n:], sete[t - n:])
		#line4.set_data(xdata[t - n:], y_der[t - n:])
	else:
		line1.set_data(xdata, actual)
		line2.set_data(xdata, error)
		line3.set_data(xdata, sete)
		#line4.set_data(xdata, y_der)
	return line1,


fig = plt.figure() 
ax1 = fig.add_subplot(2, 1, 1)
ax2 = fig.add_subplot(2, 1, 2)

line1, = ax1.plot([], [], lw=2, label='actual')
line2, = ax1.plot([], [], lw=2, label='error')
line3, = ax1.plot([], [], lw=2, label='set')
line4, = ax2.plot([], [], lw=2, label='motor der', color='navy')

ax1.grid()
ax2.grid()

xdata = []
actual = []
error = []
sete = []

l = 2
w = 1
n = 100 # muestras plot
pid = PID(kp=1, ki=1, kd=1) 

port = '/dev/ttyACM0' # puerto donde esta conectado el arduino (hay que cambiarlo dependiendo del pc)
board = pyfirmata.Arduino(port) # crea objeto como arduino en puerto anterior

it = pyfirmata.util.Iterator(board) # para que el buffer no haga overflow
it.start()

A0 = board.get_pin('a:0:i') # define pin analogico A0 como input
A1 = board.get_pin('a:1:i') # define pin analogico A0 como input
A2 = board.get_pin('a:2:i')
D2 = board.get_pin('d:2:o') # define pin digital D2 como input (ampolleta 1)
D3 = board.get_pin('d:3:p') # pwm



ani = animation.FuncAnimation(fig=fig, func=run, blit=False, interval=1, repeat=False, init_func=init)

fig.legend()
plt.show()
