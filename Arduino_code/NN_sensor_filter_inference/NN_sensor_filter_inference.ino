#define NumberOf(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0]))) //calculates the amount of layers (in this case 4)


#include <NeuralNetwork_loki.h>
#define lr_w 0.5
#define lr_b 0.1
#define input_layer 5
#define output_layer 1
#define training_led 5
#define inference_led 4
#define front_sensor A0

unsigned int layers[] = {
  input_layer, 10,10, output_layer}; // 4 layers (1st)layer with 3 input neurons (2nd & 3rd)layer 9 hidden neurons each and (4th)layer with 1 output neuron
float *outputs; // 4th layer's outputs (in this case output)

//Default Inputs
const float inputs[20][5] =
{
  {
    0.125,0.1125,0.125,0.125,0.1125,    }
  ,
  {
    0.1125,0.1125,0.125,0.125,0.125,    }
  ,
  {
    0.125,0.125,0.125,0.125,0.1125,    }
  ,
  {
    0.125,0.125,0.125,0.125,0.1125,    }
  ,
  {
    0.1125,0.1125,0.1,0.1125,0.1125,    }
  ,


  {
    0.425,0.425,0.4,0.3375,0.3125,    }
  ,
  {
    0.4,0.4125,0.425,0.4125,0.4125,    }
  ,
  {
    0.4125,0.4125,0.3125,0.4125,0.4625,    }
  ,
  {
    0.3375,0.3125,0.3625,0.4125,0.4125,    }
  ,
  {
    0.4125,0.4125,0.425,0.425,0.4125,    }
  ,


  {
    0.6375,0.6875,0.6875,0.7375,1.275,    }
  ,
  {
    0.6,0.7,0.6875,0.6875,0.75,    }
  ,
  {
    0.675,0.6875,0.7,0.775,1.225,    }
  ,
  {
    0.6875,0.6875,0.6875,0.6875,0.7125,    }
  ,
  {
    0.625,0.6875,0.6875,0.8,0.825,    }
  ,


  {
    0.8625,1.0625,1.0125,0.75,0.9,    }
  ,
  {
    0.825,0.475,1.0,1.0,0.8625,    }
  ,
  {
    0.8625,1.075,0.9875,0.825,0.7875,    }
  ,
  {
    0.8625,0.825,0.6875,0.825,0.825,    }
  ,
  {
    0.475,1.0125,0.65,0.65,0.8,    }


};


float expectedOutput[20][1] = 
{
  {
    0.125    }
  ,{
    0.125    }
  ,{
    0.125    }
  ,{
    0.125    }
  ,{
    0.125    }
  ,
  {
    0.375    }
  ,{
    0.375    }
  ,{
    0.375    }
  ,{
    0.375    }
  ,{
    0.375    }
  ,
  {
    0.625    }
  ,{
    0.625    }
  ,{
    0.625    }
  ,{
    0.625    }
  ,{
    0.625    }
  ,
  {
    0.875    }
  ,{
    0.875    }
  ,{
    0.875    }
  ,{
    0.875    }
  ,{
    0.875    }
};


double mse(float*prediction,float*correct_labels,int len)

{
  double   sum = 0;
  for (int i=0;i<len;i++)


    sum+=pow((prediction[i] - correct_labels[i]),2);

  return(sum/len);

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

float biases[] = {
  1, 1, 1.10};
float weights[] = {
  -0.6484233,  -0.0755488,  0.5026687 , 0.9587239 , -0.6764968, 
  -0.3852889,  -0.7400205,  -0.7024137,  -0.7265924,  0.0376824 ,
  -0.1325785,  0.7455864 , 0.6546943 , 0.1584578 , 0.6062610 ,
  -0.2621020,  -1.0343898,  0.0992688 , -1.0170639,  -0.1341378, 
  0.5778557 , 0.2421243 , 0.5670714 , 0.2182014 , -0.6702500, 
  -0.1183346,  -0.9461521,  -0.2211389,  -1.5656046,  0.4585381 ,
  -0.1322309,  -0.9531138,  -1.0135576,  -1.3257031,  1.0579726 ,
  0.9381559 , 0.4181199 , -0.2166521,  0.1926925 , 0.3200315 ,
  -1.0070719,  -1.1773892,  -0.5828179,  -0.4684364,  0.6772394 ,
  -0.4123711,  0.5477338 , 0.9689661 , 0.3844870 , 0.2056200 ,


  -0.1143880,  0.7154710 , -0.1983905,  0.5872960 , -1.1058602,  0.6055155 , 0.2475018 , -0.6954590,  -0.5127610,  -0.5223888, 
  0.7669292 , -0.7614714,  0.0860177 , -0.7535028,  -0.7688074,  -0.5271659,  -0.8287199,  -0.1134520,  -0.6684827,  0.5622174 ,
  0.2282454 , 0.4972378 , 0.3387800 , -0.7040200,  -0.7066989,  -1.2308013,  -0.7253687,  -0.0043790,  -0.7329177,  0.6644775 ,
  -0.7624959,  0.9695514 , -0.8571860,  0.3668788 , -0.3002726,  1.1452354 , 0.6254220 , -0.4741785,  0.9000235 , -1.2484794, 
  -0.7338368,  -0.4108086,  0.5747357 , -0.1144247,  -0.3964538,  0.2940071 , -0.7926874,  0.2646511 , -0.9196021,  0.6932129 ,
  -0.2764264,  -0.3770282,  0.2463975 , -0.1550042,  0.9398299 , -1.1007025,  -1.1669603,  -0.1714096,  -0.6450152,  -0.6100318, 
  0.6553032 , -0.2218111,  -0.1124572,  0.6377093 , 0.4094083 , 0.5833497 , -0.8690656,  -0.5121718,  0.5290698 , -0.8131736, 
  0.0383087 , 0.6622461 , 0.5065584 , 0.2927902 , 0.2351315 , -0.2001044,  -0.0379105,  -0.4704418,  -0.6221297,  -0.2080642, 
  -0.6684966,  -0.0266420,  -0.1533159,  0.5211578 , 0.5793947 , 0.6439046 , -0.4897862,  -0.9070886,  -0.2252475,  -0.9608922, 
  -0.4599701,  1.4979410 , -1.0495219,  0.8769186 , -0.6520221,  2.0684115 , 2.3515670 , -0.2321527,  1.4503932 , -0.8259346, 



  -1.0919977,  
  1.2058241 , 
  1.1460921 ,
  -1.8048533,
  1.0300854 ,
  1.3245826 , 
  0.3785012 , 
  0.3960425 , 
  -0.3284512,  
  -3.1392621

};


unsigned long start_time,end_time ;
int User_input = 0;
float distance_5[5] = {
  0.0,0.0,0.0,0.0,0.0};
NeuralNetwork NN(layers, weights, biases, NumberOf(layers)); // Creating a NeuralNetwork with Pretrained Weights and Biases
void setup()
{
  pinMode(training_led,OUTPUT);
  pinMode(inference_led,OUTPUT);

  pinMode(front_sensor,INPUT);

  Serial.begin(9600);

  Serial.println("Initial Test...");


  //Trains the NeuralNetwork for given epochs
  digitalWrite(training_led,HIGH);


  //Goes through all inputs
  test(&NN);
  digitalWrite(training_led,   LOW);

  // prints the weights and biases of each layer
  NN.print(); 


}




void loop() {

  float volts,distance;
  float *current_output; 
  volts= analogRead(front_sensor)*0.0048828125;
  distance = 29.988*pow(volts, -1.173);
  Serial.print("Measured_distance:");
  Serial.println(distance); 

//  Serial.print("\tNetwork Input:\t"); 
  for(int i =0;i<4;i++)
  {
    distance_5[i] = distance_5[i+1];
    //Serial.print(distance_5[i]);
    //Serial.print(","); 
  }
  distance_5[4] = distance/80.0;
  //Serial.print(distance_5[4]);
  //Serial.println();
  start_time = millis();
  current_output = NN.FeedForward(distance_5);
  end_time = millis();
  //Serial.print("\tInference_time(in sec):");
  //Serial.println((end_time- start_time)/1000.0,7);
 // Serial.print("model_prediction:");
 // Serial.print(current_output[0]);
 Serial.print("Predicted_distance:");
 //Serial.println(current_output[0]*80.0);
  
  if(current_output[0] > 0.025 && current_output[0] < 0.225)
    Serial.println(10.00);
  else if ( current_output[0] > 0.275 && current_output[0] < 0.475)
    Serial.println(30.00);
  else if ( current_output[0] > 0.525 && current_output[0] < 0.725)
    Serial.println(50.00);
  else if ( current_output[0] > 0.775 && current_output[0] < 0.975)
    Serial.println(70.00);



  digitalWrite(inference_led,HIGH);
  delay(100);
  digitalWrite(inference_led,LOW);



}








