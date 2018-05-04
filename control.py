# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt
import time
import pyfirmata
import datetime
import matplotlib.animation as animation
from motorModificado import *

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
		print('integral', self.inte)
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
	

def ang2ang(x):
	return 90*(x - 1) + 45
	

def init():
	ax1.set_ylim(-50, 50)
	ax1.set_xlim(0, 100)
	ax2.set_ylim(-0.1, 0.3)
	ax2.set_xlim(0, 100)
	return


def run(t):
    	# update the data
	vel_set = A0.read()*0.2
	vel_act = A2.read()*0.5
	vel_act += A2.read()*0.5
	ang = ang2ang(A1.read())
	pid.kd = A3.read()	
	m_izq.set_vel(v=vel_set, ang=ang)
	m_der.set_vel(v=vel_set, ang=ang)	
	er = m_izq.vel - vel_act
	error.append(er)
	pid.set_out(er)
	f = pid.out
	print('out', f)
	D3.write(f)
	Act.append(vel_act)
	Set.append(vel_set)
	y1data.append(ang)

	y_izq.append(m_izq.vel)
	y_der.append(m_der.vel)

	xdata.append(len(Set))

	xmin, xmax = ax1.get_xlim()
	if t>n:
		ax1.set_xlim(xdata[t - n], xdata[t])
		ax2.set_xlim(xdata[t - n], xdata[t])
		ax1.figure.canvas.draw()
		ax2.figure.canvas.draw()
	if t>n:
		line1.set_data(xdata[t - n:], Set[t - n:])
		line2.set_data(xdata[t - n:], y1data[t - n:])
		line3.set_data(xdata[t - n:], y_izq[t - n:])
		line4.set_data(xdata[t - n:], y_der[t - n:])
		line5.set_data(xdata[t - n:], Act[t - n:])
		line6.set_data(xdata[t - n:], Set[t - n:])
	else:
		line1.set_data(xdata, Set)
		line2.set_data(xdata, y1data)
		line3.set_data(xdata, y_izq)
		line4.set_data(xdata, y_der)
		line5.set_data(xdata, Act)
		line5.set_data(xdata, Set)
	return line1,


fig = plt.figure() 
ax1 = fig.add_subplot(2, 1, 1)
ax2 = fig.add_subplot(2, 1, 2)

line1, = ax1.plot([], [], lw=2, label='velocidad')
line2, = ax1.plot([], [], lw=2, label='angulo')
line3, = ax2.plot([], [], lw=2, label='motor izq', color='red')
line4, = ax2.plot([], [], lw=2, label='motor der', color='navy')
line5, = ax2.plot([], [], lw=2, label='actual', color='green')
line6, = ax2.plot([], [], lw=2, label='set', color='brown')

ax1.grid()
ax2.grid()

xdata = []
Set = []
y1data = []
y_der = []
y_izq = []
Set = []
Act = []
error = []

l = 2
w = 1
m_izq = MotorIzquierdo(l, w)
m_der = MotorDerecho(l, w)
pid = PID(kp=1, kd=1, ki=1, o_min=0, o_max=1)
n = 100 # muestras plot

port = '/dev/ttyACM0' # puerto donde esta conectado el arduino (hay que cambiarlo dependiendo del pc)
board = pyfirmata.Arduino(port) # crea objeto como arduino en puerto anterior

it = pyfirmata.util.Iterator(board) # para que el buffer no haga overflow
it.start()

A0 = board.get_pin('a:0:i') # define pin analogico A0 como input
A1 = board.get_pin('a:1:i') # define pin analogico A0 como input
A2 = board.get_pin('a:2:i')
A3 = board.get_pin('a:3:i')
D2 = board.get_pin('d:2:o') # define pin digital D2 como input (ampolleta 1)
D3 = board.get_pin('d:3:p') # pwm

D3.write(0.50)

ani = animation.FuncAnimation(fig=fig, func=run, blit=False, interval=1, repeat=False, init_func=init)

fig.legend()
plt.show()
