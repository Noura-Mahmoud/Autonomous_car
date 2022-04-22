//void setup() {
//// Open serial communications and wait for port to open:
//Serial.begin(115200);
//while (!Serial) {
//; // wait for serial port to connect. Needed for native USB port only
//}
//}
//void loop() { // run over and over
//if (Serial.available()) {
//Serial.write(Serial.read());
//}
//}

//------- ultrasonic----------
//const int pingPin = 6; // Trigger Pin of Ultrasonic Sensor
//const int echoPin = 5; // Echo Pin of Ultrasonic Sensor

//const int pingPin = A1; // Trigger Pin of Ultrasonic Sensor
//const int echoPin = A0; // Echo Pin of Ultrasonic Sensor

//------- RFID----------
//RFID
// 36 70 16 7E
#include <SPI.h>
#include <MFRC522.h>
#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

#define NOTE_G4  392
#define NOTE_C5  523
#define NOTE_G5  784
#define NOTE_C6  1047

int granted = 0;
int led_red = A2;      // access denied
int led_green = A3;    // access granted
int led_blue = A4; // indicating 3 RFID granted access

//------- motors ----------
char dir = 0;
int ENA = 6; // MCU PWM Pin 10 to ENA on L298n Board
int IN1 = 2;
int IN2 = 3;

int ENB = 9;  // MCU PWM Pin 9 to ENB on L298n Board
int IN3 = 4;
int IN4 = 5;

// pins from esp to control
int first = 7;
int second = 8;
int first_in = 0;
int second_in = 0;
int mod = 19; //A5  // to check mode whether automatic or manual
int state = 1;  // if 0 automatic, if 1 manual

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  //  while (!Serial) {
  //    ; // wait for serial port to connect. Needed for native USB port only
  //  }

  //------- RFID----------
  //   while (!Serial);      // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();          // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  Serial.println("Please put your card on the RFID reader..");

  pinMode(led_red, OUTPUT);  // sets the pin as output
  pinMode(led_green, OUTPUT);
  pinMode(led_blue, OUTPUT);
  analogWrite(led_red, 200);

  //------- motors ----------
  pinMode(ENA, OUTPUT); //Set all the L298n Pin to output
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(first, INPUT);
  pinMode(second, INPUT);
  pinMode(mod, INPUT);
}


//------- ultrasonic function----------
//
//void obstacle(long distance) {
//  char direc;
//  if (distance < 18)
//  {
//    direc = Serial.read();
//    walk(direc);
//
//    Serial.print("Stop \n");
//    off();
//    delay(500);
//
//    direc = Serial.read();
//    walk(direc);
//
//    Serial.print("movebackword \n");
//    backward();
//    delay(500);
//
//    direc = Serial.read();
//    walk(direc);
//
//    Serial.print("Stop \n");
//    off();
//    delay(100);
//
//    direc = Serial.read();
//    walk(direc);
//
//    Serial.print("left \n");
//    left();
//    delay(500);
//
//    direc = Serial.read();
//    walk(direc);
//
//    Serial.print("Stop \n");
//    off();
//    delay(100);
//
//    direc = Serial.read();
//    walk(direc);
//
//    Serial.print("front \n");
//    forward();
//    delay(1000);
//
//    direc = Serial.read();
//    walk(direc);
//
//    Serial.print("Stop \n");
//    off();
//    delay(100);
//
//    direc = Serial.read();
//    walk(direc);
//
//    Serial.print("right \n");
//    right();
//    delay(500);
//
//    direc = Serial.read();
//    walk(direc);
//
//    Serial.print("Stop \n");
//    off();
//    delay(100);
//
//    direc = Serial.read();
//    walk(direc);
//
//    Serial.print("front \n");
//    forward();
//    delay(500);
//
//    direc = Serial.read();
//    walk(direc);
//
//  }
////}
//
//long microsecondsToCentimeters(long microseconds) {
//  return microseconds / 29 / 2;
//}


void loop() // run over and over
{
  delay(1000);
  first_in = digitalRead(first);
  second_in = digitalRead(second);
  //  Serial.print("first_in ");
  //  Serial.println(first_in);
  //  Serial.print("second_in ");
  //  Serial.println(second_in);
  state = digitalRead(mod);
  //  Serial.write("state \n");
  //  Serial.write(state);
  //  Serial.write("\n");

  if (state == 2) // automatic
  {
    Serial.println("automatic");
    if (Serial.available())
    {
      dir = Serial.read();
    }

    //------- ultrasonic----------
    //  long duration, inches, cm;
    //  pinMode(pingPin, OUTPUT);
    //  digitalWrite(pingPin, LOW);
    //  delayMicroseconds(2);
    //  digitalWrite(pingPin, HIGH);
    //  delayMicroseconds(10);
    //  digitalWrite(pingPin, LOW);
    //  pinMode(echoPin, INPUT);
    //  duration = pulseIn(echoPin, HIGH);
    //  cm = microsecondsToCentimeters(duration);
    //  Serial.print(cm);
    //  Serial.print("cm");
    //  Serial.println();
    //  delay(500);

    //  obstacle(cm);

  }
  else if (state == 1 || state == 0) // manual
  {
    Serial.println("manual");
    if (first_in == 0 & second_in == 0)
    {
      dir = 'F';
      Serial.println("front");
    }
    else if (first_in == 0 & second_in == 1)
    {
      dir = 'B';
      Serial.println("back");
    }
    else if (first_in == 1 & second_in == 0)
    {
      dir = 'R';
      Serial.println("right");
    }
    else if (first_in == 1 & second_in == 1)
    {
      dir = 'L';
      Serial.println("left");
    }
    //      Serial.println(dir);
  }

  switch (dir) {

    case 'F': // forward
      Serial.write("forward \n");
      forward();
      delay(350);
      Serial.write("off \n");
      off();
      delay(1000);
      dir = 'O';
      break;

    case 'B': //backward
      Serial.write("backward \n");
      backward();
      delay(200);
      Serial.write("off \n");
      off();
      delay(1000);
      dir = 'O';
      break;

    case 'R': //right
      Serial.write("right \n");
      right();
      delay(200);
      //      forward();
      //      delay(2000);
      Serial.write("off \n");
      off();
      delay(1000);
      dir = 'O';
      break;

    case 'L': //left
      Serial.write("left \n");
      left();
      delay(200);
      //      forward();
      //      delay(2000);
      Serial.write("off \n");
      off();
      delay(1000);
      dir = 'O';
      break;

    case 'O': // off
      off();
      Serial.write("off \n");
      delay(1000);
      dir = 'O';
      break;
  }

  //------- RFID----------
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  //Show UID on serial monitor
  Serial.print("UID tag :");
  String RFIDtag = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    RFIDtag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    RFIDtag.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  RFIDtag.toUpperCase();

  if ( RFIDtag.substring(1) == "36 70 16 7E" )//Change the 00 00 00 00 to your UID card number that you want to give access

  {
    Serial.println("Access is granted");
    granted = granted + 1;
    digitalWrite(led_green, HIGH);
    digitalWrite(led_red, LOW);
    if (granted == 3)
    {
      Serial.println("you passed three times");
      digitalWrite(led_blue, HIGH);
      granted = 0;
      //      delay(1500);
      //      digitalWrite(led_blue,LOW);
    }
    //    playTrueMelody();
    //    digitalWrite(GREEN_LED,HIGH);
    //    digitalWrite(RED_LED,LOW);
    delay(1500);
    digitalWrite(led_green, LOW);
    digitalWrite(led_blue, LOW);
    digitalWrite(led_red, HIGH);
    Serial.println("\n");
    Serial.println("Please put your card on the RFID reader.. \n");

  }

  else   {
    Serial.println("Access is denied");
    //    playFalseMelody();
    digitalWrite(led_green, LOW);
    digitalWrite(led_red, LOW);
    delay(200);
    digitalWrite(led_red, HIGH);
    delay(1000);
    Serial.println("Please put your card on the RFID reader..");
  }

  delay(1000);
}

//------- motors functions----------
void forward()
{
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
  // Run the motors on both direction at fixed speed
  digitalWrite(IN1, HIGH); // Turn HIGH motor A
  digitalWrite(IN2, LOW);
  //  analogWrite(ENA, 200); // TO set the turning speed to 200 out of possible range 0 to 255

  digitalWrite(IN3, HIGH); // turn HIGH motor B
  digitalWrite(IN4, LOW);  // To set the turning speed to 200 out of possible range 0 to 255
  //  analogWrite(ENB, 200);
}

void backward()
{
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void off()
{
  digitalWrite(IN1, LOW); // Turn the motor off
  digitalWrite(IN2, LOW); // Turn the motor off
  digitalWrite(IN3, LOW); // Turn the motor off
  digitalWrite(IN4, LOW); // Turn the motor off
}

void right()
{
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  // Run the motors on both direction at fixed speed
  digitalWrite(IN1, HIGH); // Turn HIGH motor A
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW); // turn HIGH motor B
  digitalWrite(IN4, HIGH);
}

void left()
{
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  // Run the motors on both direction at fixed speed
  digitalWrite(IN1, LOW); // Turn HIGH motor A
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH); // turn HIGH motor B
  digitalWrite(IN4, LOW);
}
