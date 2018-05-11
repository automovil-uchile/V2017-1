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


def read(pin, l=40):
	lec = 0
	for i in range(l):
		lec += pin.read()
	return lec/l


def animate(i):
	t1 = time.time() # tiempo de inicio ejecucion
	# lectura de gui y arduino
	vel_set = Bvel.get()
	ang = Bang.get()
	vel1 = read(A0)*100
	vel2 = read(A1)*100
	kp = Bkp.get()
	kd = Bkd.get()
	ki = Bki.get()
	# diferencial
	m_I.set_vel(v=vel_set, ang=ang)
	m_D.set_vel(v=vel_set, ang=ang)

	# pid
	pid.set_kp(kp)
	pid.set_kd(kd)
	pid.set_ki(ki)
	eI = m_I.vel - vel1
	eD = m_D.vel - vel2
	pid.set_out(eI)
	# set de frecuencias
	f1 = pid.out/100
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
	y8.append(0) # eD
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
		ax1.set_ylim(min(min(y1), min(y2)) - 2, max(max(y1), max(y2)) + 2)
	else:
		ynew1 = y1[-N:]
		ynew2 = y2[-N:]
		ynew7 = y7[-N:]
		ynew8 = y8[-N:]
		line1.set_data(xar[-N:], ynew1)
		line2.set_data(xar[-N:], ynew2)
		line3.set_data(xar[-N:], y3[-N:])
		line4.set_data(xar[-N:], y4[-N:])
		line5.set_data(xar[-N:], y5[-N:])
		line6.set_data(xar[-N:], y6[-N:])
		line7.set_data(xar[-N:], ynew7[-N:])
		line8.set_data(xar[-N:], ynew8[-N:])
		ax1.set_xlim(xar[-N], xar[-1])
		ax2.set_xlim(xar[-N], xar[-1])
		ax3.set_xlim(xar[-N], xar[-1])
		ax1.set_ylim(min(min(ynew1), min(ynew2)) - 2, max(max(ynew1), max(ynew2)) + 2)
		ax3.set_ylim(min(min(ynew7), min(ynew8)) - 2, max(max(ynew7), max(ynew8)) + 2)
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
pid = PID(kp=1, kd=1, ki=1, o_min=0, o_max=100)

#---------------------------------------------------
# Plot
style.use('ggplot')
fig = plt.figure(figsize=(14, 10), dpi=100)

ax1 = fig.add_subplot(3, 1, 1)
ax1.set_ylim(0, 100)
ax1.set_ylabel('ang deg, vel auto')

ax2 = fig.add_subplot(3, 1, 2)
ax2.set_ylim(0, 100)
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
line7, = ax3.plot(xar, y7, 'r', color='green', label='der')
line8, = ax3.plot(xar, y8, 'r', color='brown', label='izq')

ax2.legend()
ax3.legend()


#ser = serial.Serial('com3', 9600)


#---------------------------------------------------------
# Buttons and scale
button = Button(master=root, text='Quit', command=_quit)
button2 = Button(master=root, text='Refresh', command=refresh)
Bang = Scale(master=root, from_=-45, to=45, orient=HORIZONTAL, label='angulo')
Bvel = Scale(master=root, from_=0, to=25, orient=HORIZONTAL, label='vel auto')
lim = 500
Bkp = Scale(master=root, from_=0, to=lim, orient=HORIZONTAL, label='kp')
Bkd = Scale(master=root, from_=0, to=int(lim/2), orient=HORIZONTAL, label='kd')
Bki = Scale(master=root, from_=0, to=int(lim/2), orient=HORIZONTAL, label='ki')

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
