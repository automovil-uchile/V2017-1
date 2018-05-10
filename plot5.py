#import serial
from tkinter import *
from matplotlib import pyplot as plt
import matplotlib.animation as animation
from matplotlib import style
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import time
import numpy as np

def ang2ang(x):
	return 90*(x - 1) + 45


def animate(i):
	#ser.reset_input_buffer()
	#data = ser.readline().decode("utf-8")
	#data_array = data.split(',')
	#yvalue = float(data_array[1])
	t1 = time.time()
	yar.append(np.random.normal(0, w.get()))
	xar.append(i)
	n = len(xar)
	if n<N:
		line.set_data(xar, yar)
		ax1.set_xlim(0, i+1)
		ax1.set_ylim(min(yar), max(yar))
	else:
		ynew = yar[-N:]
		line.set_data(xar[-N:], yar[-N:])
		ax1.set_xlim(xar[-N], i+1)
		ax1.set_ylim(min(ynew), max(ynew))
	t2 = time.time()
	print('lag', t2 - t1)

def _quit():
	root.quit()     # stops mainloop
	root.destroy()  # this is necessary on Windows to prevent Fatal Python Error: PyEval_RestoreThread: NULL tstate


def refresh():
	ax1.clear()

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
root.title('This is my root window')
#root.state('zoomed')
root.config(background='#fafafa')


#---------------------------------------------------
# Data
xar = []
yar = []
N = 100

#---------------------------------------------------
# Plot
style.use('ggplot')
fig = plt.figure(figsize=(14, 4.5), dpi=100)
ax1 = fig.add_subplot(1, 1, 1)
ax1.set_ylim(0, 100)
line, = ax1.plot(xar, yar, 'r', marker='o')
#ser = serial.Serial('com3', 9600)


	
button = Button(master=root, text='Quit', command=_quit)
button2 = Button(master=root, text='Refresh', command=refresh)
w = Scale(master=root, from_=0, to=200, orient=HORIZONTAL)
w.pack()
button2.pack(side=BOTTOM)
button.pack(side=BOTTOM)

plotcanvas = FigureCanvasTkAgg(fig, root)
plotcanvas.get_tk_widget().pack()#grid(column=1, row=1)
ani = animation.FuncAnimation(fig, animate, interval=1, blit=False)

root.mainloop()
