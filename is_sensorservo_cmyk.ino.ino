// Color Recognition Program カラー認識　サーボ駆動
// TSCC230 Sensor and SG90 MicroServo 

#include<Servo.h>
#define SW1 7
#define SW2 2

#define S0 8
#define S1 9
#define S2 10
#define S3 11
#define Out 12
 
Servo servoC;
Servo servoM;
Servo servoY;
Servo servoW;

int frequency = 0;
int color_red = 0;
int color_green = 0;
int color_blue = 0;

int degC = 0;
int degM = 0;
int degY = 0;
int degW = 0;

//White and Black Balance Calibration
int whiteR =180;
int whiteG =240;
int whiteB =170;
int blackR =20;
int blackG =20;
int blackB =16;
 
void setup() {
  pinMode(SW1,INPUT); //D13をスイッチとして使用
  pinMode(SW2,INPUT);
  digitalWrite(SW1,HIGH);    //pull-up ON
  digitalWrite(SW2,HIGH);
  
 // Color Sensor output
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(Out, INPUT);

 // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  servoC.attach(3);    
  servoM.attach(4);    
  servoY.attach(5);   
  servoW.attach(6);   

 Serial.begin(9600);
}
 
void loop() {

  if(digitalRead(SW1)==LOW){
 // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
 
// Reading the output frequency
  frequency = pulseIn(Out, LOW);
 // Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, whiteR, blackR,255,0);
  color_red = constrain(frequency, 0, 255);

 // Printing the value on the serial monitor
// Arduino IDEの「シリアルモニタ」に、color_redの値を表示
  Serial.print("R= ");
  Serial.print(color_red);
  Serial.print(" ");
  delay(100);

 // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
 // Reading the output frequency
  frequency = pulseIn(Out, LOW);
 //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, whiteG, blackG,255,0);
  color_green = constrain(frequency, 0, 255);

 // Printing the value on the serial monitor
// Arduino IDEの「シリアルモニタ」に、color_greenの値を表示
  Serial.print("G= ");
  Serial.print(color_green);
  Serial.print(" ");
  delay(100);

 // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
 // Reading the output frequency
  frequency = pulseIn(Out, LOW);
 //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, whiteB, blackB,255,0);
  color_blue = constrain(frequency, 0, 255);

 // Printing the value on the serial monitor and output to LED
// Arduino IDEの「シリアルモニタ」に、color_blueの値を表示
  Serial.print("B= ");//printing name
  Serial.print(color_blue);//printing Blue color frequency
  Serial.println(" ");

  int color_c;
  int color_m;
  int color_y;
  int color_w;

  color_c = color_red;
  color_m = color_green;
  color_y = color_blue;
  color_w =(255-(color_c + color_m + color_y))*0.1;

  degC = map(color_c, 0, 255, 0, 180)*3+20;
  degM = map(color_m, 0, 255, 0, 180)*3-20;
  degY = map(color_y, 0, 255, 0, 180)*3-10;
  degW = map(color_w, 0, 255, 0, 180)*3;

  Serial.print("degC= ");
  Serial.print(degC);
  Serial.print(" degM= ");
  Serial.print(degM);
  Serial.print(" degY= ");
  Serial.print(degY);
  Serial.print(" degW= ");
  Serial.print(degW);
  Serial.println("");
  delay(1000);
  } 
  if(digitalRead(SW2)==LOW){      
     delay(1000);
     servoC.write(degC);
     delay(1000);
     servoM.write(degM);
     delay(1000);
     servoY.write(degY);
     delay(1000);
     servoW.write(degW);
     delay(1000);
   }else{  
     servoC.write(0);       
     servoM.write(0);
     servoY.write(0);
     servoW.write(0);
   }    
delay(1000);
}

