'''
Script to plot optained results
as bar plots 

'''






import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure(figsize = (12,9))

ax = fig.add_subplot(111)

def add_text(rects,text,ignore_bar_no=-1,rotate=0,align = 'center'):
	i=0
	for rect in rects:
		height = rect.get_height()
		if(i==ignore_bar_no):
			ax.text(rect.get_x() + rect.get_width()/2., 1*height,text[i],
                ha='center', va='bottom',rotation=0)
		else:
			ax.text(rect.get_x() + rect.get_width()/2., 1*height,text[i],
                ha=align, va='bottom',rotation=rotate)
		i+=1


'''
plt.title("Price and Spec of available computation options for an Average NN based task - in log scale")
x = ['Price','Processor_bitrate','No. of cores','Clock_Speed']
X = np.arange(4)
y_pc = [30000,64,8,16000000000]
y_pc_text=['Average PC~INR:30k','Intel I5-64Bit','8','1.6GHz']
y_rp = [5000,64,4,15000000000]
y_rp_text=['Raspberrypi4~INR:5k','ARM Cortex A72-64Bit','4','1.5GHz']
y_arduino = [200,8,1,16000000]
y_arduino_text=['Arduino Nano~INR:200','Atmega328p-8Bit','1','16MHz']
rects1=ax.bar(X, y_pc, color = 'b', width = 0.25,label='PC')
rects2=ax.bar(X+0.25 ,y_rp, color = 'r', width = 0.25,label='Raspberrypi4')
rects3=ax.bar(X+0.5, y_arduino, color = 'g', width = 0.25,label='Arduino Nano')
add_text(rects1,y_pc_text,3,45,'left')
add_text(rects2,y_rp_text,3,45,'left')
add_text(rects3,y_arduino_text,3,45,'left')
ax.set_xticks(X+0.25)
'''

'''
plt.title("Performace comparison of a traditional PC vs Arduino Nano (Mean performance of all NN based tasks) - in log scale")
x = ['Power_consumed','Accuracy','Inference_time','Training_time(300 epochs)']
X = np.arange(4)
y_pc = [65,99.98,0.1,0.26]
y_pc_text=['65W','99.98%','0.1ms','0.26s']
y_arduino = [0.14,92.5,7,65]
y_arduino_text=['140mW','92.5%','7ms','71.1s']
rects1=ax.bar(X, y_pc, color = 'b', width = 0.25,label='PC')
rects2=ax.bar(X+0.25 ,y_arduino, color = 'r', width = 0.25,label='Arduino Nano')
add_text(rects1,y_pc_text)
add_text(rects2,y_arduino_text)
ax.set_xticks(X+0.125)
'''




plt.title("Hardware capacity of a traditional PC vs Arduino Nano - in log scale")
x = ['CPU_bits','RAM','Clock_Speed']
X = np.arange(3)
y_pc = [64,8000000000,16000000000]
y_pc_text=['64Bit','8GB','1.6Ghz']
y_arduino = [8,2000,16000000]
y_arduino_text=['8Bit','2KB','16Mhz']
rects1=ax.bar(X, y_pc, color = 'b', width = 0.25,label='PC')
rects2=ax.bar(X+0.25 ,y_arduino, color = 'r', width = 0.25,label='Arduino Nano')
add_text(rects1,y_pc_text)
add_text(rects2,y_arduino_text)
ax.set_xticks(X+0.125)






ax.legend(loc='upper left')
ax.set_xticklabels(x, rotation = 0)
plt.yscale("log")
plt.show()

fig.savefig(fname = "./hard_ard_pc.png")