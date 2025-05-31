unsigned long lastCommandTime = 0;
const unsigned long timeout = 1000; // 1 second

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

unsigned int TRIG_PIN = 12;
unsigned int ECHO_PIN = 13;

int distance = 0;

void setup() {
  //bt.begin(9600);	/* Define baud rate for software serial communication */
  Serial.begin(9600);	/* Define baud rate for serial communication */
  //delay(500);
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

void stop(){
  digitalWrite(in1_L298N_no1, LOW);
  digitalWrite(in2_L298N_no1, LOW);
  digitalWrite(in3_L298N_no1, LOW);
  digitalWrite(in4_L298N_no1, LOW);
  digitalWrite(in1_L298N_no2, LOW);
  digitalWrite(in2_L298N_no2, LOW);
  digitalWrite(in3_L298N_no2, LOW);
  digitalWrite(in4_L298N_no2, LOW);
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
  while(Serial3.available()){
    char c = Serial3.read();
    Serial.print(c);         // Optional: echo to serial monitor  
    // If we received a complete c
    if (c == 'F') {
      Serial.println(" -> Đi Thẳng");
      digitalWrite(in1_L298N_no1, HIGH);
      digitalWrite(in2_L298N_no1, LOW);
      digitalWrite(in3_L298N_no1, HIGH);
      digitalWrite(in4_L298N_no1, LOW);
      digitalWrite(in1_L298N_no2, HIGH);
      digitalWrite(in2_L298N_no2, LOW);
      digitalWrite(in3_L298N_no2, HIGH);
      digitalWrite(in4_L298N_no2, LOW);
      analogWrite(ENA, 80);
      analogWrite(ENB, 80);
    }
    // If we received a complete c
    else if (c == 'R') {
      Serial.println(" -> Đi Sang Phải");
      digitalWrite(in1_L298N_no1, HIGH);
      digitalWrite(in2_L298N_no1, LOW);
      digitalWrite(in3_L298N_no1, LOW);
      digitalWrite(in4_L298N_no1, HIGH);
      digitalWrite(in1_L298N_no2, LOW);
      digitalWrite(in2_L298N_no2, HIGH);
      digitalWrite(in3_L298N_no2, HIGH);
      digitalWrite(in4_L298N_no2, LOW);
      analogWrite(ENA, 100);
      analogWrite(ENB, 100);
    } 
    // If we received a complete c
    else if (c == 'L') {
      Serial.println(" -> Đi Sang Trái");
      digitalWrite(in1_L298N_no1, LOW);
      digitalWrite(in2_L298N_no1, HIGH);
      digitalWrite(in3_L298N_no1, HIGH);
      digitalWrite(in4_L298N_no1, LOW);
      digitalWrite(in1_L298N_no2, HIGH);
      digitalWrite(in2_L298N_no2, LOW);
      digitalWrite(in3_L298N_no2, LOW);
      digitalWrite(in4_L298N_no2, HIGH);
      analogWrite(ENA, 100);
      analogWrite(ENB, 100);
    } 
    // If we received a complete c
    else if (c == 'B') {
      Serial.println(" -> Đi Lùi");
      digitalWrite(in1_L298N_no1, LOW);
      digitalWrite(in2_L298N_no1, HIGH);
      digitalWrite(in3_L298N_no1, LOW);
      digitalWrite(in4_L298N_no1, HIGH);
      digitalWrite(in1_L298N_no2, LOW);
      digitalWrite(in2_L298N_no2, HIGH);
      digitalWrite(in3_L298N_no2, LOW);
      digitalWrite(in4_L298N_no2, HIGH);
      analogWrite(ENA, 80);
      analogWrite(ENB, 80);
    }   
    // If we received a complete c
    if (c == 'A') {
      Serial.println(" -> Đi Thẳng Chéo Trái");
      digitalWrite(in1_L298N_no1, LOW);
      digitalWrite(in2_L298N_no1, LOW);
      digitalWrite(in3_L298N_no1, HIGH);
      digitalWrite(in4_L298N_no1, LOW);
      digitalWrite(in1_L298N_no2, HIGH);
      digitalWrite(in2_L298N_no2, LOW);
      digitalWrite(in3_L298N_no2, LOW);
      digitalWrite(in4_L298N_no2, LOW);
      analogWrite(ENA, 180);
      analogWrite(ENB, 180);
    } 
    // If we received a complete c
    else if (c == 'I') {
      Serial.println(" -> Đi Thẳng Chéo Phải");
      digitalWrite(in1_L298N_no1, HIGH);
      digitalWrite(in2_L298N_no1, LOW);
      digitalWrite(in3_L298N_no1, LOW);
      digitalWrite(in4_L298N_no1, LOW);
      digitalWrite(in1_L298N_no2, LOW);
      digitalWrite(in2_L298N_no2, LOW);
      digitalWrite(in3_L298N_no2, HIGH);
      digitalWrite(in4_L298N_no2, LOW);
      analogWrite(ENA, 180);
      analogWrite(ENB, 180);
    } 
    // If we received a complete c
    else if (c == 'C') {
      Serial.println(" -> Đi Lùi Chéo Trái");
      digitalWrite(in1_L298N_no1, LOW);
      digitalWrite(in2_L298N_no1, HIGH);
      digitalWrite(in3_L298N_no1, LOW);
      digitalWrite(in4_L298N_no1, LOW);
      digitalWrite(in1_L298N_no2, LOW);
      digitalWrite(in2_L298N_no2, LOW);
      digitalWrite(in3_L298N_no2, LOW);
      digitalWrite(in4_L298N_no2, HIGH);
      analogWrite(ENA, 180);
      analogWrite(ENB, 180);
    } 
    // If we received a complete c
    else if (c == 'D') {
      Serial.println(" -> Đi Lùi Chéo Phải");
      digitalWrite(in1_L298N_no1, LOW);
      digitalWrite(in2_L298N_no1, LOW);
      digitalWrite(in3_L298N_no1, LOW);
      digitalWrite(in4_L298N_no1, HIGH);
      digitalWrite(in1_L298N_no2, LOW);
      digitalWrite(in2_L298N_no2, HIGH);
      digitalWrite(in3_L298N_no2, LOW);
      digitalWrite(in4_L298N_no2, LOW);
      analogWrite(ENA, 180);
      analogWrite(ENB, 180);
    } 
    // If we received a complete c
    else if (c == 'G') {
      Serial.println(" -> Quay Vòng Trái");
      digitalWrite(in1_L298N_no1, LOW);
      digitalWrite(in2_L298N_no1, HIGH);
      digitalWrite(in3_L298N_no1, HIGH);
      digitalWrite(in4_L298N_no1, LOW);
      digitalWrite(in1_L298N_no2, LOW);
      digitalWrite(in2_L298N_no2, HIGH);
      digitalWrite(in3_L298N_no2, HIGH);
      digitalWrite(in4_L298N_no2, LOW);
      analogWrite(ENA, 80);
      analogWrite(ENB, 80);
    } 
    // If we received a complete c
    else if (c == 'H') {
      Serial.println(" -> Quay Vòng Phải");
      digitalWrite(in1_L298N_no1, HIGH);
      digitalWrite(in2_L298N_no1, LOW);
      digitalWrite(in3_L298N_no1, LOW);
      digitalWrite(in4_L298N_no1, HIGH);
      digitalWrite(in1_L298N_no2, HIGH);
      digitalWrite(in2_L298N_no2, LOW);
      digitalWrite(in3_L298N_no2, LOW);
      digitalWrite(in4_L298N_no2, HIGH);
      analogWrite(ENA, 80);
      analogWrite(ENB, 80);
    } 
    // If we received a complete c
    else if (c == 'M') {
      Serial.println(" -> Dừng Khẩn Cấp");
      stop();
    } 
    else if(c == 'S'){
      Serial.println(" -> Dừng");
      //stop();
    }
  }
  // Timeout condition
  if (millis() - lastCommandTime > timeout) {
    stop(); // Stop if no command received in timeout period
  }
}