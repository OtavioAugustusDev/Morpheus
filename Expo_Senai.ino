
#include <Servo.h> 

#define pinServ1 3
#define pinServ2 5
#define pinServ3 6
#define pinServ4 9

#define pot1 A0
#define pot2 A1
#define pot3 A2
#define pot4 A3

Servo serv1,serv2,serv3,serv4;

int motor1,motor2,motor3,motor4;

bool detectado;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);

  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);

  return pulseIn(echoPin, HIGH);
}

void setup() {

  Serial.begin(9600);

  serv1.attach(pinServ1);
  serv2.attach(pinServ2);
  serv3.attach(pinServ3);
  serv4.attach(pinServ4);
  
  serv1.write(177);
  serv2.write(37);
  serv3.write(85);
  serv4.write(0);
  
}

void loop()
{
  if (!detectado && 0.01723 * readUltrasonicDistance(8, 7) <= 10) {
    detectado = true;
    Serial.println("Perto");
    AutoMode();
  } else {    Serial.println("Longe");
}
  delay(10);
}

void ManualMode()
{
  motor1 = map(analogRead(pot1),0,1023,0,180);
  motor2 = map(analogRead(pot2),0,1023,0,180);
  motor3 = map(analogRead(pot3),0,1023,85,180);
  motor4 = map(analogRead(pot4),0,1023,0,43);

  serv1.write(motor1);
  serv2.write(motor2);
  serv3.write(motor3);
  serv4.write(motor4);

  delay(100);
}

void AutoMode()
{
  serv1.write(177);
  serv2.write(37);
  serv3.write(85);
  serv4.write(0);

  delay(500);

  for(int i = 177; i > 2; i--)
  {
    serv1.write(i);
    delay(10);
  }

  delay(500);

  for(int i = 37; i < 82; i++)
  {
    serv2.write(i);
    delay(10);
  }

  delay(500);

  serv4.write(75);

  delay(500);

  serv2.write(37);
  
  delay(100);

  for (int i = 2; i < 177; i++)
  {
    serv1.write(i);
    delay(10);
  }

  delay(500);
  
  serv3.write(85);

  delay(500);

  for(int i = 37; i < 94; i++)
  {
    serv2.write(i);
    delay(10);
  }

  delay(500);

  serv4.write(0);

  delay(500);

  for(int i = 94; i > 37; i--)
  {
    serv2.write(i);
    delay(10);
  }

  delay(1000);
  
  detectado = false;
}