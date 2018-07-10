import serial
import serial.tools.list_ports

class Com:
	def __init__(self, port, baudrate):
		"""
		port: string, puerto del arduino
		baudrate: int, baudrate
		"""
		self.ser = serial.Serial(port, baudrate)

	def String2Int(self, string):
		"""
		string: string, lecturas del arduino
		"""		
		myread = string.split(',')
		mr = []
		for i in myread:
			mr.append(int(i))
		return mr

	def ReadSerial(self):
		"""Lee puerto serial""" 
		self.rec = (self.ser.readline()[:-2]).decode("utf-8")
		self.rec = self.String2Int(self.rec)

	def WriteSerial(self):
		self.ser.write(b'hola')

	def get_value(self):
		return self.rec
