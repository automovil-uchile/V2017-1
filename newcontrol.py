import time
import numpy as np
import matplotlib.pyplot as plt
from Motor import *
from Pid import *
from Comm import *

class Control:
	def __init__(self, com, l, w):
		"""
		com: Com object
		l: car length
		w: car width
		"""
		self.ml = MotorIzquierdo(l, w)
		self.mr = MotorDerecho(l, w)
		self.pid = PID(kp=1, kd=1, ki=1, kaw=10, o_min=0, o_max=1)
		self.com = com
		self.ang = 1
		self.acc = 1

	def Read(self):
		"""Convierte lecturas de sensores en lista a variable para cada lectura."""
		self.com.WriteSerial()
		self.com.ReadSerial()
		lec = self.com.get_value()
		if len(lec)!=1:
			self.ang = lec[0] # steering angle
			self.acc = lec[1] # user acceleration
			#self.vl = lec[2] # left motor velocity
			#self.vr = lec[3] # right motor velocity 
			#self.state = lec[4] # state neutral, forward or backward
			

	def diff(self):
		"""Realiza calculos de diferencial"""
		self.ml.set_vel(v=self.acc, ang=self.ang)
		self.mr.set_vel(v=self.acc, ang=self.ang)

	def update_control(self):
		"""
		pid.set_kp(kp)
		pid.set_kd(kd)
		pid.set_ki(ki)
		pid.set_kaw(kaw)
		eI = m_I.vel - vel1
		eD = m_D.vel - vel2
		pid.update(eI)
		# set de frecuencias
		f1 = pid.out
		D5.write(f1)
		"""
		pass



baudrate = 115200
l = 2
w = 1		

# check arduino port
for p in list(serial.tools.list_ports.comports()):
	port = p[0]
# port = '/dev/ttyACM1'

com = Com(port=port, baudrate=baudrate)
control = Control(com, l, w)

while True:
	try:
		control.Read()
		control.diff()
		print('motor izq', control.ml.get_vel())
		print('motor der', control.mr.get_vel())
	except KeyboardInterrupt:
		ser.close()
