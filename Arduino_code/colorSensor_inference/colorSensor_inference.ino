
#include "MLP.cpp"


#define THRESHOLD 2000
//#define LED_DELAY 500

#define RECOGNIZE 1
#define CALIBRATE 2
#define CALIBRATE_B 3
#define CALIBRATE_W 4

#define NET_INPUTS 3
#define NET_OUTPUTS 10
#define NET_LAYERS 2
int choice = 0;

int lastState=0, op=0;
unsigned long pressTime = 0;

int rgb[] = {8, 9, 10}; //led pins
int input[] = {0, 0, 0}; //RGB values
double netInput[] = {-1.0, 0.0, 0.0, 0.0};
int calib[3][2] = {{329, 778}, {166, 569}, {140, 528}};

char *colors[] = {"BLACK", "RED", "GREEN", "BLUE", "YELLOW", "BROWN", "PURPLE", "ORANGE", "PINK", "WHITE"};

int layerSizes[] = {6, NET_OUTPUTS, -1};
int offset=0, iOffset=0, yOffset=0;
double PROGMEM const initW[] = {2.753086,-11.472257,-3.311738,16.481226,19.507006,20.831778,7.113330,-6.423491,1.907215,6.495393,-27.712126,26.228203,-0.206367,-5.724560,-22.278070,30.065610,6.139262,-10.814282,28.513130,-9.784946,6.467021,0.055005,3.730361,4.145092,2.479019,0.013003,-3.582416,-16.364391,14.133357,-5.089288,1.637492,5.894826,1.415764,-3.315533,14.814289,-20.906571,-1.568656,1.917658,4.910184,4.039419,-10.848469,-5.641680,-4.132432,10.711442,3.759935,19.507702,17.728724,-3.210244,-2.476992,8.988450,5.196827,2.636043,17.357207,2.005429,11.713386,-5.453253,-6.940325,10.752005,0.666605,-7.266082,-3.587120,-9.921817,-12.682059,-15.456143,-13.740927,0.508265,15.179410,-11.143178,-19.085120,1.251235,22.006491,-4.227328,-0.444516,3.589025,0.649661,13.675598,-13.026884,-11.229070,-15.300703,-1.718191,6.737973,-28.176802,-2.505471,5.197970,7.007983,-2.869269,3.650349,18.029204,4.098356,10.481188,-2.566311,9.927770,2.344936,4.524327};

MLP mlp(NET_INPUTS,NET_OUTPUTS,layerSizes,choice,initW,true);

void setup(){

  Serial.begin(9600);
  for(int i=0;i<3;i++){
    pinMode(rgb[i], OUTPUT);
    digitalWrite(rgb[i], HIGH);
  }
  
}

void loop(){
  
  //checkListeners();
  if(Serial.available()>0)
  {
    input[0] = Serial.parseInt();
    input[1] = Serial.parseInt();
    input[2] = Serial.parseInt();

    char junk = Serial.read();

   op =1;

  }

  else 
    op = 0;


   if(op==1){
    Serial.println("Recognizing...  ");

    for(int i=0;i<3;i++){
      Serial.print(input[i]);
      if(i<2)
        Serial.print(" / ");
      netInput[i+1] = (double)input[i]/255.0;
    }

    Serial.println();

   Serial.print(colors[mlp.getActivation(netInput)]);
    delay(5000);
 
}
}

