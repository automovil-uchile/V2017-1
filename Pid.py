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
