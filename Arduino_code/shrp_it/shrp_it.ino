
/*
all CALCULATIONS refer
https://github.com/guillaume-rico/SharpIR
*/

#define sensor A0 


void setup() {
  Serial.begin(9600); // start the serial port
}

void loop() {
  
  // 
  //Serial.println(analogRead(sensor));
  float volts = analogRead(sensor)*0.0048828125;  // value from sensor * (5/1024)
  Serial.print("volts:");
  Serial.println( volts);               


  int distance = 29.988*pow(volts, -1.173); // worked out from datasheet graph
  delay(500); // slow down serial port 
  
  if (distance <= 80){
    Serial.print("\tdistance:");
    Serial.println(distance);   // print the distance
  }
}
