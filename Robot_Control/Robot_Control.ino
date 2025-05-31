#define in1_L298N_no1 4
#define in2_L298N_no1 5
// Motor 2
#define in3_L298N_no1 6
#define in4_L298N_no1 7
// Motor 3
#define in1_L298N_no2 10
#define in2_L298N_no2 11
// Motor 4
#define in3_L298N_no2 8
#define in4_L298N_no2 9

#define ENA 3
#define ENB 2

#define LOW_SPEED 80
#define NORMAL_SPEED 150
#define HIGH_SPEED 180

unsigned int TRIG_PIN = 12;
unsigned int ECHO_PIN = 13;

int distance = 0;

bool hasTimedOut = false; // Add this at global scope
unsigned long lastCommandTime = 0;
const unsigned long timeout = 1000; // 2.1 second

void setup() {
  //bt.begin(9600);	/* Define baud rate for software serial communication */
  Serial.begin(9600);	/* Define baud rate for serial communication */
  //Serial.setTimeout(100);

  // Initialize Serial for debugging
  while (!Serial);

  // Initialize Serial3 for HC-05
  Serial3.begin(9600); // HC-05 default baud rate is usually 9600
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  // Motor
  pinMode(in1_L298N_no1, OUTPUT);
  pinMode(in2_L298N_no1, OUTPUT);
  pinMode(in3_L298N_no1, OUTPUT);
  pinMode(in4_L298N_no1, OUTPUT);
  pinMode(in1_L298N_no2, OUTPUT);
  pinMode(in2_L298N_no2, OUTPUT);
  pinMode(in3_L298N_no2, OUTPUT);
  pinMode(in4_L298N_no2, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void moveMotors(
  bool m1_in1, bool m1_in2, bool m1_in3, bool m1_in4,
  bool m2_in1, bool m2_in2, bool m2_in3, bool m2_in4,
  int speedA, int speedB
) {
  digitalWrite(in1_L298N_no1, m1_in1);
  digitalWrite(in2_L298N_no1, m1_in2);
  digitalWrite(in3_L298N_no1, m1_in3);
  digitalWrite(in4_L298N_no1, m1_in4);
  digitalWrite(in1_L298N_no2, m2_in1);
  digitalWrite(in2_L298N_no2, m2_in2);
  digitalWrite(in3_L298N_no2, m2_in3);
  digitalWrite(in4_L298N_no2, m2_in4);
  analogWrite(ENA, speedA);
  analogWrite(ENB, speedB);
}

int Distance(){
  unsigned long duration;

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the pulse duration
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration / 29 / 2; // Convert to distance in cm

  return distance;
}

void loop() {
  bool commandReceived = false;
  
  while(Serial3.available()){
    char c = Serial3.read();

    commandReceived = true; // A command was received
    lastCommandTime = millis(); // Reset timeout
    hasTimedOut = false; // Reset timeout flag
    
    Serial.print(c);
    Serial.print(" ");
    Serial.print(lastCommandTime);

    // If we received a complete c
    switch(c){
      //if (c == 'F') {
      case 'F':
        Serial.println(" -> Đi Thẳng");
        moveMotors(
          1, 0, 1, 0,  // L298N_no1
          1, 0, 1, 0,  // L298N_no2
          80, 80       // Speeds
        );
        break;
      case 'R':
        Serial.println(" -> Đi Sang Phải");
        moveMotors(
          1, 0, 0, 1,  // L298N_no1
          0, 1, 1, 0,  // L298N_no2
          100, 100       // Speeds
        );
        break;
      case 'L':
        Serial.println(" -> Đi Sang Trái");
        moveMotors(
          0, 1, 1, 0,  // L298N_no1
          1, 0, 0, 1,  // L298N_no2
          100, 100       // Speeds
        );
        break;
      case 'B':
        Serial.println(" -> Đi Lùi");
        moveMotors(
          0, 1, 0, 1,  // L298N_no1
          0, 1, 0, 1,  // L298N_no2
          80, 80       // Speeds
        );
        break;
      case 'A':
        Serial.println(" -> Đi Thẳng Chéo Trái");
        moveMotors(
          0, 0, 1, 0,  // L298N_no1
          1, 0, 0, 0,  // L298N_no2
          180, 180       // Speeds
        );
        break;
      case 'I':
        Serial.println(" -> Đi Thẳng Chéo Phải");
        moveMotors(
          1, 0, 0, 0,  // L298N_no1
          0, 0, 1, 0,  // L298N_no2
          180, 180       // Speeds
        );
        break;
      case 'C':
        Serial.println(" -> Đi Lùi Chéo Trái");
        moveMotors(
          0, 1, 0, 0,  // L298N_no1
          0, 0, 0, 1,  // L298N_no2
          180, 180       // Speeds
        );
        break;
      case 'D':
        Serial.println(" -> Đi Lùi Chéo Phải");
        moveMotors(
          0, 0, 0, 1,  // L298N_no1
          0, 1, 0, 0,  // L298N_no2
          180, 180       // Speeds
        );
        break;
      case 'G':
        Serial.println(" -> Quay Vòng Trái");
        moveMotors(
          0, 1, 1, 0,  // L298N_no1
          0, 1, 1, 0,  // L298N_no2
          80, 80       // Speeds
        );
        break;
      case 'H':
        Serial.println(" -> Quay Vòng Phải");
        moveMotors(
          1, 0, 0, 1,  // L298N_no1
          1, 0, 0, 1,  // L298N_no2
          80, 80       // Speeds
        );
        break; 
      case 'M':
        Serial.println(" -> Dừng Khẩn Cấp");
        //stop();
        moveMotors(
          0, 0, 0, 0,  // L298N_no1
          0, 0, 0, 0,  // L298N_no2
          0, 0       // Speeds
        );
        break;
      case 'S':
        Serial.println(" -> Dừng");
        //stop();
        moveMotors(
          0, 0, 0, 0,  // L298N_no1
          0, 0, 0, 0,  // L298N_no2
          0, 0       // Speeds
        );
      break; 
    }
  }
  // If no command has been received and timeout occurred
  if (!commandReceived && (millis() - lastCommandTime > timeout) && !hasTimedOut) {
    Serial.print(millis());
    Serial.println(" Timeout -> Dừng");
    moveMotors(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    hasTimedOut = true; // Prevent repeated printing
  }
}