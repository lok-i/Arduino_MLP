#define NumberOf(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0]))) //calculates the amount of layers (in this case 4)


#include <NeuralNetwork_loki.h>
#define lr_w 0.5
#define lr_b 0.1
#define input_layer 5
#define output_layer 1
#define training_led 5
#define inference_led 4

unsigned int layers[] = {
  input_layer, 10,10, output_layer}; // 4 layers (1st)layer with 3 input neurons (2nd & 3rd)layer 9 hidden neurons each and (4th)layer with 1 output neuron
float *outputs; // 4th layer's outputs (in this case output)

//Default Inputs
const float inputs[20][5] =
{
{0.125,0.1125,0.125,0.125,0.1125,},
{0.1125,0.1125,0.125,0.125,0.125,},
{0.125,0.125,0.125,0.125,0.1125,},
{0.125,0.125,0.125,0.125,0.1125,},
{0.1125,0.1125,0.1,0.1125,0.1125,},


{0.425,0.425,0.4,0.3375,0.3125,},
{0.4,0.4125,0.425,0.4125,0.4125,},
{0.4125,0.4125,0.3125,0.4125,0.4625,},
{0.3375,0.3125,0.3625,0.4125,0.4125,},
{0.4125,0.4125,0.425,0.425,0.4125,},


{0.6375,0.6875,0.6875,0.7375,1.275,},
{0.6,0.7,0.6875,0.6875,0.75,},
{0.675,0.6875,0.7,0.775,1.225,},
{0.6875,0.6875,0.6875,0.6875,0.7125,},
{0.625,0.6875,0.6875,0.8,0.825,},


{0.8625,1.0625,1.0125,0.75,0.9,},
{0.825,0.475,1.0,1.0,0.8625,},
{0.8625,1.075,0.9875,0.825,0.7875,},
{0.8625,0.825,0.6875,0.825,0.825,},
{0.475,1.0125,0.65,0.65,0.8,}


};


float expectedOutput[20][1] = 
{
  {0.125},{0.125},{0.125},{0.125},{0.125},
  {0.375},{0.375},{0.375},{0.375},{0.375},
  {0.625},{0.625},{0.625},{0.625},{0.625},
  {0.875},{0.875},{0.875},{0.875},{0.875}
};


double mse(float*prediction,float*correct_labels,int len)

{
  double   sum = 0;
  for (int i=0;i<len;i++)


    sum+=pow((prediction[i] - correct_labels[i]),2);

  return(sum/len);

}
void train(NeuralNetwork* A,int no_of_epochs,int log_interval)
{
  unsigned long start_time_1,end_time_1 ;
  double avg_mse_this_epoch = 1;

  for (int i = 0;i<=no_of_epochs ; i++)
  { 
    avg_mse_this_epoch = 0;
    start_time_1 = millis();

    for (int j = 0; j < NumberOf(inputs); j++)
    {
      outputs = A[0].FeedForward(inputs[j]); // Feeds-Forward the inputs to the first layer of the NN and Gets the output.
      A[0].BackProp(expectedOutput[j]); // Tells to the NN if the output was right/the-expectedOutput and then, teaches it.
      avg_mse_this_epoch += mse(outputs,expectedOutput[j],output_layer);
    }
    end_time_1 = millis();
    if(i%log_interval==0)
    {
      Serial.print("Epoch:");
      Serial.print(i);
      Serial.print("\tMSE:");
      Serial.print(avg_mse_this_epoch/float(NumberOf(inputs)),7);
      Serial.print("\ttime taken:");
      Serial.println((end_time_1 - start_time_1)/1000.0,7);

    }


    //    if(i%1000)
    //    N.print();
  }
}

void test(NeuralNetwork* A)
{
  for (int i = 0; i < NumberOf(inputs); i++)
  {
    outputs = A[0].FeedForward(inputs[i]); // Feeds-Forward the inputs[i] to the first layer of the NN and Gets the output
    String test = "\nTest:\t";
    Serial.print(test+(i+1));

    for (int j =0;j<output_layer;j++)
    {
      Serial.print("\t");
      Serial.print(outputs[j], 7); // prints the first 7 digits after the comma.

    }

    Serial.print("\ttest_Error:\t");
    if(fabs(expectedOutput[i][0] - outputs[0])<=0.1)

      Serial.println("Right");
    else
    { 
 
        Serial.println("Wrong");

    }
  }


}

NeuralNetwork NN(layers, NumberOf(layers),lr_w,lr_b); // Creating a NeuralNetwork with default learning-rates
unsigned long start_time,end_time ;
int User_input = 0;

void setup()
{
  pinMode(training_led,OUTPUT);
  pinMode(inference_led,OUTPUT);



  Serial.begin(9600);
  //Trains the NeuralNetwork for given epochs
  digitalWrite(training_led,HIGH);
  Serial.println("Training...");
  
//start_time = millis();
  train(&NN,1000,50);
 // end_time = millis();
  digitalWrite(training_led,LOW);
 // Serial.print("Total_training_time_taken(in sec):");
 // Serial.println((end_time- start_time)/1000.0,7);

  //Goes through all inputs
   test(&NN);

  // prints the weights and biases of each layer
  NN.print(); 


}




void loop() {

}






