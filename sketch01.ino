
#define DIGIN_L 12
#define DIGIN_R 4

#define ANAOUT_L 11
#define ANAOUT_R 5

#define MAX_VEL 250
#define MIN_VEL 180

#define inLA 10
#define inLB 9
#define inRA 6
#define inRB 7

const int analogPin = A0;
int value;                  //variable que almacena la lectura analógica
int velocity = 0;

void setup() {
  
  pinMode(DIGIN_L, INPUT);
  pinMode(DIGIN_R, INPUT);

  pinMode(inLA, OUTPUT);
  pinMode(inLB, OUTPUT);
  pinMode(inRA, OUTPUT);
  pinMode(inRB, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int sLeft = 0;
  int sRight = 0;

  sLeft = digitalRead(DIGIN_L);
  sRight = digitalRead(DIGIN_R);

  value = analogRead(analogPin);           // realizar la lectura analógica raw
  value = map(value, 0, 1023, 0, 100);    // convertir a valores de salida

  value = 33;

  velocity = (int)(value * MAX_VEL)/100;

  //Si el sensor izq detecta linea negra => girar izq
  if((sLeft == HIGH)&&(sRight == LOW)){
    velocity = (int) (velocity * 0.8);
    velocity = (velocity < MIN_VEL ? MIN_VEL : velocity);
    turnLeft();
  }else if((sRight == HIGH)&&(sLeft == LOW)){
    //Si el sensor der detecta linea negra => girar der
    velocity = (int) (velocity * 0.8);
    velocity = (velocity < MIN_VEL ? MIN_VEL : velocity);
    turnRight();
  } else if((sLeft == HIGH) && (sRight == HIGH) ) {
    //Si los dos detectan linea negra o no detectan nada => detenerse
    velocity = 0;
    stopRobot();
  } else {
    //Si los dos detectan el blanco, seguir adelante
    velocity = (int) (velocity == 0 ? MIN_VEL : velocity * 1.2);
    velocity = (velocity > MAX_VEL ? MAX_VEL : velocity);
    goAhead();
  }
}

void turnRight() {
  //detener der y avanza izq
  analogWrite(ANAOUT_R,0);
  analogWrite(ANAOUT_L,velocity);

  digitalWrite(inRA, LOW);
  digitalWrite(inRB, LOW);
  digitalWrite(inLA, HIGH);
  digitalWrite(inLB, LOW);
}

void turnLeft() {
  //detener izq y anvaza der
  analogWrite(ANAOUT_R, velocity);
  analogWrite(ANAOUT_L, 0);

  digitalWrite(inRA, HIGH);
  digitalWrite(inRB, LOW);
  digitalWrite(inLA, LOW);
  digitalWrite(inLB, LOW);
}

void goAhead() {
  //ambos motores activos
  analogWrite(ANAOUT_R, velocity);
  analogWrite(ANAOUT_L, velocity);

  digitalWrite(inRA, HIGH);
  digitalWrite(inRB, LOW);
  digitalWrite(inLA, HIGH);
  digitalWrite(inLB, LOW);
}

void stopRobot () {
  //ambos motores detenidos
  analogWrite(ANAOUT_R, 0);
  analogWrite(ANAOUT_L, 0);

  digitalWrite(inRA, LOW);
  digitalWrite(inRB, LOW);
  digitalWrite(inLA, LOW);
  digitalWrite(inLB, LOW);
}

