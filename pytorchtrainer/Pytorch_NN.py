import torch
import pandas as pd
import time
import torch.nn as nn
import torch.nn.functional as F
file_name = "./trainingSet.csv"
color_data = pd.read_csv(file_name).values
input_layer_size = 3
output_layer_size = 10 
X = color_data[0:len(color_data),0:input_layer_size]
Y = color_data[0:len(color_data),input_layer_size:13]
Y_train = []

for i in range(len(color_data)):
  for j in range(10):
    if(Y[i][j]==1.0):
      Y_train.append(j)
      break

X_train= torch.FloatTensor(X)
Y_train = torch.LongTensor(Y_train)





'''
for data_pt in range(75):
  print('X:',X[data_pt],'Y:',Y_train[data_pt])
  #print(Y_train)
'''


class Lin_Net(nn.Module):

    def __init__(self):
        super(Lin_Net, self).__init__()

        self.input_l = nn.Linear(input_layer_size,6)
        self.fc1 = nn.Linear(6,6)  # 6*6 from image dimension 
        self.fc2 = nn.Linear(6, output_layer_size)
        #self.fc3 = nn.Linear(84, 10)

    def forward(self, x):

        x = F.relu(self.input_l(x))
        x = F.relu(self.fc1(x))
        #x = F.relu(self.fc2(x))
        x = self.fc2(x)
        return x



model = Lin_Net()
print("Lin_Network_architecture:",model)

def train():
  epochs = 1000
  loss_arr = []
  criterion = nn.CrossEntropyLoss()
  optimizer = torch.optim.Adam(model.parameters(), lr=0.01)
  for i in range(epochs):
    y_hat = model.forward(X_train)
    loss = criterion(y_hat, Y_train)
    loss_arr.append(loss)
    if i % 10 == 0:
      print(f'Epoch: {i} Loss: {loss}')
    optimizer.zero_grad()
    loss.backward()
    optimizer.step()

train()
preds = []
i = 0
running_avg_time = 0
for x in X_train:
  start = time.time()
  y=model.forward(x)
  end = time.time()
  time_taken = end-start
  running_avg_time = (running_avg_time*(i) + time_taken )/(i+1)
  preds.append(y.argmax().item())

print('Y_train:\n',Y_train)
error = torch.zeros(len(preds))
for i in range(len(preds)):
	error[i] = preds[i] - Y_train[i]

#print('preds:\n',preds)
#print("Avg_inf_time:",running_avg_time)
print("error:",error)
print("input wieghts")
print(model.input_l.weight)
print("fc1 weights")
print(model.fc1.weight)
print("fc2 weights")
print(model.fc2.weight)
