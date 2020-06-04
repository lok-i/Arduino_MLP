import serial
import matplotlib.pyplot as plt

def xtract_value(string_i):
	string_i = string_i.replace('\\','')
	string_i = string_i.replace('r','')
	string_i = string_i.replace('n','')
	string_i = string_i.replace('\'','')
	string_i = string_i.replace('b','')
	return string_i


arduino = serial.Serial('/dev/ttyUSB0', 9600, timeout=0.1)
V = []
D = []
for i in range(1000):
	volt= xtract_value(str(arduino.readline()))#the last bit gets rid of the new-line chars

	distance=xtract_value(str(arduino.readline()))#the last bit gets rid of the new-line chars
	if volt:
		volt = float(volt)
		print("volts:",volt)
		V.append(volt)
		distance = float(distance)
		print("distance:",distance)
		D.append(distance)
plt.plot(D,V)
plt.show()