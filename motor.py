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
