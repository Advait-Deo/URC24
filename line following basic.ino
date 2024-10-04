#define ENA 10
#define ENB 11
#define IN1 7
#define IN2 6
#define IN3 5
#define IN4 4


// IR

#define lefts 13
#define middles 2
#define rights 3


#define basespeed 150

void setup() {
  Serial.begin(9600);

  // MOTOR
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

  // IR
  pinMode(lefts,INPUT);
  pinMode(middles,INPUT);
  pinMode(rights,INPUT);

}


// // PID CONSTANTS
// float Kp=0.6;
// float Ki=0.0;
// float Kd=0.3;

// // VARIABLES FOR PID
// float error = 0, previous_error = 0;
// float derivative = 0;
// float integral = 0;
// float correction = 0;

void loop() {

int middleval = digitalRead(middles);
int leftval = digitalRead(lefts);
int rightval = digitalRead(rights);

Serial.print("Left Sensor: ");
Serial.print(leftval);
Serial.print(" | Center Sensor: ");
Serial.print(middleval);
Serial.print(" | Right Sensor: ");
Serial.println(rightval);


if (middleval==1 && leftval==0 && rightval==0){
  //error = 0;
  forward(200);
}
else if(leftval==1 && middleval==0 && rightval==0) {
  //error = -1;
  left(200);
}
else if(leftval==1 && middleval==1 && rightval==0) {
  //error = -1;
  left(150);
}
else if (rightval==1 && leftval==0 && middleval==0) { 
  //error = +1;
  right(200);
}
else if (rightval==1 && leftval==1 && middleval==0) { 
  //error = +1;
  right(150);
}
else{     
  //error= previous_error;
  backward(100);
}

}

//            motor left                    motor right
//               ENA                            ENB
//               IN1 (A)                        IN3 (A)   
//               IN2 (C)                        IN4 (C)  


void stop() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

}

void forward(int speed) {
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  analogWrite(ENA, speed);  // Speed for motor 1
  analogWrite(ENB, speed);  // Speed for motor 2

}

void backward(int speed) {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
  analogWrite(ENA, speed);  // Speed for motor 1
  analogWrite(ENB, speed);

}

void left(int speed) {
  digitalWrite(IN1, 1); 
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  analogWrite(ENA, speed/2 );  // Half speed for motor 1 (left)
  analogWrite(ENB, speed); 

}

void right(int speed) {
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  analogWrite(ENA, speed);      // Full speed for motor 1 (left)
  analogWrite(ENB, speed/2 );
}
