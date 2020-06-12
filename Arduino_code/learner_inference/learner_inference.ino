#define NumberOf(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0]))) //calculates the amount of layers (in this case 4)


#include <NeuralNetwork_loki.h>
#include <Servo.h>

#define training_led 5
#define inference_led 4
#define front_sensor A0
#define right_sensor A1
#define right_servo 10 
#define left_servo 9


#define lr_w 0.5
#define lr_b 0.1
#define input_layer 4
#define output_layer 1

k..open 
unsigned int layers[] = {
  input_layer, 10,10, output_layer}; // 4 layers (1st)layer with 3 input neurons (2nd & 3rd)layer 9 hidden neurons each and (4th)layer with 1 output neuron
float *outputs; // 4th layer's outputs (in this case output)

//Default Inputs
const float inputs[16][4] =

{
  {
    0,0,0,0  }
  ,
  {
    0,0,0,1  }
  ,
  {
    0,0,1,0  }
  ,
  {
    0,0,1,1  }
  ,

  {
    0,1,0,0  }
  ,
  {
    0,1,0,1  }
  ,
  {
    0,1,1,0  }
  ,
  {
    0,1,1,1  }
  ,

  {
    1,0,0,0  }
  ,
  {
    1,0,0,1  }
  ,
  {
    1,0,1,0  }
  ,
  {
    1,0,1,1  }
  ,

  {
    1,1,0,0  }
  ,
  {
    1,1,0,1  }
  ,
  {
    1,1,1,0  }
  ,
  {
    1,1,1,1  }
  ,
};

float expectedOutput[16][1] = 
{
  {
    0.00      }
  ,
  {
    0.50      }
  ,
  {
    0.75      }
  ,
  {
    1.00      }
  ,

  {
    0.00      }
  ,
  {
    0.50      }
  ,
  {
    0.25      }
  ,
  {
    1.00      }
  ,

  {
    0.00      }
  ,
  {
    0.25      }
  ,
  {
    0.75      }
  ,
  {
    1.00      }
  ,

  {
    0.00      }
  ,
  {
    0.25      }
  ,
  {
    0.25      }
  ,
  {
    1.00      }
};

double mse(float*prediction,float*correct_labels,int len)
{
  double   sum = 0;
  for (int i=0;i<len;i++)


    sum+=pow((prediction[i] - correct_labels[i]),2);

  return(sum/len);
}


void train(NeuralNetwork* A,int no_of_epochs)
{

  double avg_mse_this_epoch = 1;

  for (int i = 0;i<=no_of_epochs ; i++)
  { 
    avg_mse_this_epoch = 0;

    for (int j = 0; j < NumberOf(inputs); j++)
    {
      outputs = A[0].FeedForward(inputs[j]); // Feeds-Forward the inputs to the first layer of the NN and Gets the output.
      A[0].BackProp(expectedOutput[j]); // Tells to the NN if the output was right/the-expectedOutput and then, teaches it.
      avg_mse_this_epoch += mse(outputs,expectedOutput[j],output_layer);
    }
    if(i%100 ==0)
    {
      Serial.print("Epoch:");
      Serial.print(i);
      Serial.print("\tMSE:");
      Serial.println(avg_mse_this_epoch/float(NumberOf(inputs)),7);

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
      if(expectedOutput[i][0] <=0.25 and outputs[0]<=0.25)
        Serial.println("Right");
      else
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
  pinMode(front_sensor,INPUT);
  pinMode(right_sensor,INPUT);
  R_Servo.attach(right_servo);
  L_Servo.attach(left_servo);
   R_Servo.write(89);
   L_Servo.write(91);


  Serial.begin(9600);

  Serial.println("Training...");
  /*
  Serial.print("Lr_w\t");
   Serial.print(NN.LearningRateOfWeights,3);
   Serial.print("Lr_b\t");
   Serial.println(NN.LearningRateOfBiases,3);
   NN.print();
   */
  //Trains the NeuralNetwork for given epochs
  digitalWrite(training_led,HIGH);
  start_time = millis();
  train(&NN,350);
  end_time = millis();
  digitalWrite(training_led,LOW);
  Serial.print("training_time_taken(in sec):");
  Serial.println((end_time- start_time)/1000.0,7);

  //Goes through all inputs
  test(&NN);

  // prints the weights and biases of each layer
  //NN.print(); 


}

void loop() 
{
  if(Serial.available()>0)
  {
    User_input = Serial.parseInt();



    Serial.flush();
    digitalWrite(inference_led,HIGH);

  }
  else
    digitalWrite(inference_led,LOW);

  //User_input = 0;


  float volts[2],distance[2]; 
  float current_input[4];
  float* current_output;

  for(int i=0;i<2;i++)
  {

    if(i==0)
     { Serial.print("Front Sensor:\t");
    volts[i]= analogRead(front_sensor)*0.0048828125;}
    else
     { Serial.print("Right Sensor:\t");
    volts[i]= analogRead(right_sensor)*0.0048828125;}

    distance[i] = 29.988*pow(volts[i], -1.173);
    current_input[i] = distance[i] <=15 ? 1 : 0;
    
    Serial.print("volts:");
    Serial.print( volts[i]);
    Serial.print("\tdistance:");
    Serial.println(distance[i]);   // print the distance

  }

  switch(User_input)

  {

    case(1):
    { // Forward
      current_input[2]=0;
      current_input[3]=1;
      break;
    }
    case(2):
    { // clockwise rotate
      current_input[2]=1;
      current_input[3]=0;
      break;
    }
    case(3):
    { // Backward
      current_input[2]=1;
      current_input[3]=1;
      break;
    }
  default:
    { // No command
      current_input[2]=0;
      current_input[3]=0;
      break;
    }



  }
  Serial.print("model_input:\t");
  for(int i=0;i<4;i++)
    Serial.print(current_input[i]);
  Serial.println();

  start_time = millis();
  current_output = NN.FeedForward(current_input);
  end_time = millis();

  Serial.print("Inference_time(in sec):");
  Serial.println((end_time- start_time)/1000.0,7);

  Serial.print("model_prediction:");
  Serial.println(current_output[0]);

  
if(current_output [0]<=0.3)
   {
   R_Servo.write(89);
   L_Servo.write(91);
   }
   else
   if(current_output[0] >=0.4 and current_output[0] <0.6)
   {
   R_Servo.write(0);
   L_Servo.write(180);
   }
   else
   if(current_output[0] >=0.65 and current_output[0] <0.85)
   {
   R_Servo.write(180);
   L_Servo.write(180);
   }
   else
   {
   R_Servo.write(180);
   L_Servo.write(0);
   }
   
   
  delay(250);

}









