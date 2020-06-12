'''
Script to read serial data from arduino and plot 
the live feed and create a dataset.txt aswell
if required
''' 


import serial
import matplotlib.pyplot as plt
import numpy as np
import time

plot_graph = True




def xtract_value(string_i):
	'''
	function to remove info text from the serial input
	'''
	string_i = string_i.replace('Measured_distance:','')
	#string_i = string_i.replace('distance:','')
	string_i = string_i.replace('Predicted_distance:','')
	string_i = string_i.replace('\\','')
	string_i = string_i.replace('r','')
	string_i = string_i.replace('n','')
	string_i = string_i.replace('\'','')
	string_i = string_i.replace('b','')
	return string_i


bluetooth = '/dev/rfcomm0'
usb = '/dev/ttyUSB0'

arduino = serial.Serial(usb, 9600, timeout=0.1)


V = []
D = []
true_length =70
fig = plt.figure()
x = []



written = 0
file_write = False
no_of_data_pts = 60
no_of_sets = 12


if(file_write):
	file_2 = open("sharp_dataset.txt","a")
	file_2.write("\n\nNew_Readings,True distance ="+str(true_length)+"cm\n")
	file_2.write("{")

for i in range(no_of_data_pts):

	volt_raw= arduino.readline()#the last bit gets rid of the new-line chars
	distance_raw= arduino.readline()#the last bit gets rid of the new-line chars
	print(volt_raw)
	print(distance_raw)
	
	if volt_raw and distance_raw :
		written = written +1 
		volt_value = float(xtract_value(str(volt_raw)))
		V.append(volt_value)
		distance_value = float(xtract_value(str(distance_raw)))
		D.append(distance_value)
		x.append(i)
		print("Measured_distance:",volt_value)
		print("Predicted_distance:",distance_value)
		if(file_write):
			file_2.write(str(distance_value/80.0)+",")
			if(written%5 == 0):
				if(written!=0):
					file_2.write("},")
					file_2.write("\n")
				if(written!=no_of_data_pts):
					file_2.write("{")

		if(plot_graph):
			ax1 = plt.subplot(211)
			ax1.clear()
			plt.plot(x,V,label = "Measured_distance")
			ax2 = plt.subplot(212)
			ax2.clear()
			plt.plot(x,D,label = "Predicted_distance")
			ax1.legend()
			ax2.legend()
			plt.pause(0.01)
	

file_2.write("\n\nLabels:\n")
for i in range(no_of_sets):
	#file_2.write("{"+str((true_length/70.0) - (1.0/7.0))+"},")
	file_2.write("{"+str((true_length/80.0))+"},")

file_2.close()
plt.savefig(str(true_length)+".png")

