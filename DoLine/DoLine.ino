// Khai báo chân cảm biến line
#define sensorLeft 24
#define sensorMiddle 26
#define sensorRight 28

// Khai báo chân điều khiển động cơ
// Motor 1
#define in1_L298N_no1 4
#define in2_L298N_no1 5
// Motor 2
#define in3_L298N_no1 6
#define in4_L298N_no1 7
// Motor 3
#define in1_L298N_no2 8
#define in2_L298N_no2 9
// Motor 4
#define in3_L298N_no2 10
#define in4_L298N_no2 11
// PWM
#define ENA 3
#define ENB 2
//Line
int L,M,R;  // 1: Có line ; 0: Không có line
void setup() {
  Serial.begin(9600);

  // Cảm biến line
  pinMode(sensorLeft, INPUT);
  pinMode(sensorMiddle, INPUT);
  pinMode(sensorRight, INPUT);

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

  analogWrite(ENA, 80);
  analogWrite(ENB, 80);
}

void loop() {
  readLineSensors();

  Serial.print("L: "); Serial.print(L);
  Serial.print(" M: "); Serial.print(M);
  Serial.print(" R: "); Serial.println(R);

  if (M == 1 && L == 0 && R == 0) {
    motorRun(1, 1);
    delay(50); // Đi thẳng
  } 
  else if (L == 1 && M == 1 && R == 0) {
    motorRun(-1, 1);
    delay(30); // Rẽ phải nhẹ
  } 
  else if (R == 1 && M == 1 && L == 0) {
    motorRun(1, -1);
    delay(30); // Rẽ trái nhẹ
  }
  else if (L == 1 && M == 0 && R == 0) {
    motorRun(-1, 1);
    delay(50); // Rẽ phải mạnh
  }
  else if (R == 1 && M == 0 && L == 0) {
    motorRun(1, -1);
    delay(50); // Rẽ trái mạnh
  }
  else {
    motorRun(1, 1); // Mặc định tiến nếu nhiều cảm biến cùng thấy line
  }


}

// Đọc cảm biến có lọc nhiễu
void readLineSensors() {
  int Lcount = 0, Mcount = 0, Rcount = 0;
  for (int i = 0; i < 5; i++) {
    Lcount += digitalRead(sensorLeft);
    Mcount += digitalRead(sensorMiddle);
    Rcount += digitalRead(sensorRight);
    delay(5);
  }
  L = (Lcount >= 1) ? 1 : 0;
  M = (Mcount >= 1) ? 1 : 0;
  R = (Rcount >= 1) ? 1 : 0;
}
// Hàm điều khiển động cơ
void motorRun(float speedl, float speedr) {
  if (speedl < 0 && speedr < 0) {
    // Lùi
    digitalWrite(in1_L298N_no1, LOW);
    digitalWrite(in2_L298N_no1, HIGH);
    digitalWrite(in3_L298N_no1, LOW);
    digitalWrite(in4_L298N_no1, HIGH);
    digitalWrite(in1_L298N_no2, LOW);
    digitalWrite(in2_L298N_no2, HIGH);
    digitalWrite(in3_L298N_no2, LOW);
    digitalWrite(in4_L298N_no2, HIGH);
  } else if (speedl < 0) {
    // Quay phải
    digitalWrite(in1_L298N_no1, LOW);
    digitalWrite(in2_L298N_no1, HIGH);
    digitalWrite(in3_L298N_no1, HIGH);
    digitalWrite(in4_L298N_no1, LOW);
    digitalWrite(in1_L298N_no2, LOW);
    digitalWrite(in2_L298N_no2, HIGH);
    digitalWrite(in3_L298N_no2, HIGH);
    digitalWrite(in4_L298N_no2, LOW);
  } else if (speedr < 0) {
    // Quay trái
    digitalWrite(in1_L298N_no1, HIGH);
    digitalWrite(in2_L298N_no1, LOW);
    digitalWrite(in3_L298N_no1, LOW);
    digitalWrite(in4_L298N_no1, HIGH);
    digitalWrite(in1_L298N_no2, HIGH);
    digitalWrite(in2_L298N_no2, LOW);
    digitalWrite(in3_L298N_no2, LOW);
    digitalWrite(in4_L298N_no2, HIGH);
  } else {
    // Tiến
    digitalWrite(in1_L298N_no1, HIGH);
    digitalWrite(in2_L298N_no1, LOW);
    digitalWrite(in3_L298N_no1, HIGH);
    digitalWrite(in4_L298N_no1, LOW);
    digitalWrite(in1_L298N_no2, HIGH);
    digitalWrite(in2_L298N_no2, LOW);
    digitalWrite(in3_L298N_no2, HIGH);
    digitalWrite(in4_L298N_no2, LOW);
  }

  analogWrite(ENA, abs(speedl * 80));
  analogWrite(ENB, abs(speedr * 80));
}