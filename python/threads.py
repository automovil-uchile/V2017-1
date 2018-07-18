import threading
import time

# Define a function for the thread
def print_time( threadName, delay):
   count = 0
   while count < 5:
      time.sleep(delay)
      count += 1
      print("%s: %s" % ( threadName, time.time() ))

# Create two threads as follows
threading.start(print_time, ("Thread-1", 2, ) )
try:
   threading.start(print_time, ("Thread-1", 2, ) )
   threading.start(print_time, ("Thread-2", 4, ) )
except:
   print("Error: unable to start thread")

while 1:
   pass
