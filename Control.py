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


def read(pin, l=100):
	lec = 0
	for i in range(l):
		lec += pin.read()
	return lec/l


def animate(i):
	t1 = time.time() # tiempo de inicio ejecucion
	# lectura de gui y arduino
	vel_set = Bvel.get()/100
	ang = Bang.get()
	vel1 = read(A0)
	vel2 = read(A1)
	kp = Bkp.get()/100
	kd = Bkd.get()/100
	ki = Bki.get()/100
	kaw = Bkaw.get()/100
	# diferencial
	m_I.set_vel(v=vel_set, ang=ang)
	m_D.set_vel(v=vel_set, ang=ang)

	# pid
	pid.set_kp(kp)
	pid.set_kd(kd)
	pid.set_ki(ki)
	pid.set_kaw(kaw)
	eI = m_I.vel - vel1
	eD = m_D.vel - vel2
	pid.update(eI)
	# set de frecuencias
	f1 = pid.out
	print(f1)
	#print('velset', vel_set, 'vel1', vel1, 'error', vel_set - vel1)
	D5.write(f1)

	
	# guarda elementos para plot
	y1.append(ang)
	y2.append(vel_set)
	y3.append(m_I.get_vel())
	y4.append(m_D.get_vel())	
	y5.append(vel1)
	y6.append(vel2)
	y7.append(eI)
	y8.append(pid.inte*pid.get_ki()) # eD
	xar.append(np.around(t1 - ti, 2))
	n = len(xar)

	if n<N:
		line1.set_data(xar, y1)
		line2.set_data(xar, y2)
		line3.set_data(xar, y3)
		line4.set_data(xar, y4)
		line5.set_data(xar, y5)
		line6.set_data(xar, y6)
		line7.set_data(xar, y7)
		line8.set_data(xar, y8)
		ax1.set_xlim(0, xar[-1])
		ax2.set_xlim(0, xar[-1])
		ax3.set_xlim(0, xar[-1])
		min1 = min(min(y1), min(y2))
		max1 = max(max(y1), max(y2))
		ax1.set_ylim(min1*(1 - 0.1), max1*(1 + 0.1))
	else:
		ynew1 = y1[-N:]
		ynew2 = y2[-N:]
		ynew3 = y3[-N:]
		ynew4 = y4[-N:]
		ynew7 = y7[-N:]
		ynew8 = y8[-N:]
		line1.set_data(xar[-N:], ynew1)
		line2.set_data(xar[-N:], ynew2)
		line3.set_data(xar[-N:], ynew3)
		line4.set_data(xar[-N:], ynew4)
		line5.set_data(xar[-N:], y5[-N:])
		line6.set_data(xar[-N:], y6[-N:])
		line7.set_data(xar[-N:], ynew7[-N:])
		line8.set_data(xar[-N:], ynew8[-N:])
		ax1.set_xlim(xar[-N], xar[-1])
		ax2.set_xlim(xar[-N], xar[-1])
		ax3.set_xlim(xar[-N], xar[-1])
		min1 = min(min(ynew1), min(ynew2))
		max1 = max(max(ynew1), max(ynew2))
		min2 = min(min(ynew7), min(ynew8))
		max2 = max(max(ynew7), max(ynew8))
		ax1.set_ylim(min1*(1 - 0.1), max1*(1 + 0.1))
		ax3.set_ylim(min2*(1 - 0.1), max2*(1 + 0.1))
	t2 = time.time()
	print('lag', t2 - t1)
	return


def _quit():
	# apaga pwm
	D5.write(0)
	D6.write(0)
	root.quit()     # stops mainloop
	root.destroy()  # this is necessary on Windows to prevent Fatal Python Error: PyEval_RestoreThread: NULL tstate
	return


def refresh():
	ax1.clear()
	return


def set_mean():
	1
	return m


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


#-----------------------------------------------------
# Gui
root = Tk()
root.geometry('1366x768+200+100')
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
y7 = []
y8 = []
N = 100
ti = time.time()

#-------------------------------------------------------
# Car configuration
l = 2
w = 1
m_I = MotorIzquierdo(l, w)
m_D = MotorDerecho(l, w)
pid = PID(kp=1, kd=1, ki=1, kaw=10, o_min=0, o_max=1)

#---------------------------------------------------
# Plot
style.use('ggplot')
fig = plt.figure(figsize=(14, 10), dpi=100)

ax1 = fig.add_subplot(3, 1, 1)
ax1.set_ylim(0, 100)
ax1.set_ylabel('ang deg, vel auto')

ax2 = fig.add_subplot(3, 1, 2)
ax2.set_ylim(0, 0.3)
ax2.set_ylabel('vel motores V')


ax3 = fig.add_subplot(3, 1, 3)
ax3.set_ylim(0, 100)
ax3.set_ylabel('error')
ax3.set_xlabel('tiempo s')

line1, = ax1.plot(xar, y1, 'r')
line2, = ax1.plot(xar, y2, 'r')
line3, = ax2.plot(xar, y3, 'r', color='red', label='set', ls='dashed')
line4, = ax2.plot(xar, y4, 'r', color='navy', label='set', ls='dashed')
line5, = ax2.plot(xar, y5, 'r', color='red', label='izq')
line6, = ax2.plot(xar, y6, 'r', color='navy', label='der')
line7, = ax3.plot(xar, y7, 'r', color='green', label='error')
line8, = ax3.plot(xar, y8, 'r', color='brown', label='integral')

ax2.legend()
ax3.legend()


#ser = serial.Serial('com3', 9600)


#---------------------------------------------------------
# Buttons and scale
button = Button(master=root, text='Quit', command=_quit)
button2 = Button(master=root, text='unitario', command=refresh)
Bang = Scale(master=root, from_=-45, to=45, orient=HORIZONTAL, label='angulo')
Bvel = Scale(master=root, from_=0, to=25, orient=HORIZONTAL, label='vel auto')
lim = 1000
Bkp = Scale(master=root, from_=0, to=lim, orient=HORIZONTAL, label='kp')
Bkd = Scale(master=root, from_=0, to=int(lim/2), orient=HORIZONTAL, label='kd')
Bki = Scale(master=root, from_=0, to=int(lim/2), orient=HORIZONTAL, label='ki')
Bkaw = Scale(master=root, from_=0, to=int(lim/2), orient=HORIZONTAL, label='kaw')

#Bang.grid()

button2.pack(side=BOTTOM)
button.pack(side=BOTTOM)
Bang.pack(side=LEFT)
Bvel.pack(side=TOP)
Bkp.pack(side=LEFT)
Bkd.pack(side=LEFT)
Bki.pack(side=LEFT)
Bkaw.pack(side=TOP)




#---------------------------------------------------------------
plotcanvas = FigureCanvasTkAgg(fig, root)
plotcanvas.get_tk_widget().pack()
#plotcanvas.get_tk_widget().grid()
ani = animation.FuncAnimation(fig, animate, interval=1, blit=False)

root.mainloop()
