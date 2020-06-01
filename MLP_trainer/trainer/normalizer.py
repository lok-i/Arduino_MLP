import numpy as np
file_name = "iris_training.txt"
file = open(file_name,"r")
data = file.readlines()
#print(data)
input_counter = 0
no_of_lines = 0
max_input = [-np.inf,-np.inf,-np.inf,-np.inf]


for i in data:
	print("string:",i)

	value = float(i.replace('\n',''))

	print("i_changed",value)
	if(input_counter==0 or input_counter==1 or input_counter==2 or input_counter==3):
		if(max_input[input_counter]<value):
			max_input[input_counter] = value
	
	if(input_counter<=5):
		input_counter = input_counter +1
	else:
		input_counter = 0
		no_of_lines +=1
		
print("max _values:",max_input)

file_2 = open("iris_normalized.txt","w")
for i in data:
	print("string:",i)

	value = float(i.replace('\n',''))


	if(input_counter==0 or input_counter==1 or input_counter==2 or input_counter==3):
		value = value/max_input[input_counter]

	if(input_counter==6):
		file_2.write(str(value))
	else:
		file_2.write(str(value)+" ")

	if(input_counter<=5):
		input_counter = input_counter +1
	else:
		input_counter = 0
		no_of_lines +=1
		file_2.write('\n')
file_2.close()

	#for i in range(len(i)):

