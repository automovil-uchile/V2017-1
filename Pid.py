# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt
import time
import pyfirmata
import datetime
import matplotlib.animation as animation


class PID:
	def __init__(self, kp, ki, kd, kaw, o_min, o_max):
		self.kp = kp
		self.ki = ki
		self.kd = kd
		self.kaw = kaw
		self.e0 = 0
		self.inte = 0
		self.out = 0
		self.min = o_min
		self.max = o_max
		self.t1 = 0


	def saturation(self): # saturation + anti windup
		if self.out>self.max:
			self.inte += self.kaw*(self.max - self.out)
			self.out = self.max
		elif self.out<self.min:
			self.inte += self.kaw*(self.min - self.out)
			self.out = self.min
 
	
	def update(self, e):
		t2 = time.time()
		dt = t2 - self.t1
		prop = e*self.kp		
		deri = (e - self.e0)/dt*self.kd
		self.inte += e*dt
		self.out = prop + deri + self.ki*self.inte
		print('prop', prop)
		print('der', deri)
		print('inte', self.inte*self.ki)
		print('out act', self.out)
		self.saturation()
		self.e0 = e
		self.t1 = t2

	def set_kp(self, kp):
		self.kp = kp
	
	def get_kp(self):
		return self.kp
	
	def set_ki(self, ki):
		self.ki = ki

	def get_ki(self):
                return self.ki

	def set_kd(self, kd):
		self.kd = kd
	
	def get_kd(self):
                return self.kd

	def set_kaw(self, kaw):
		self.kaw = kaw
	
	def get_kaw(self):
                return self.kaw
