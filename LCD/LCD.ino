#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int buttonPin[4] = {29, 30, 31, 18}; // RIGHT, RUN, LEFT, STOP
const int buttonNum = sizeof(buttonPin) / sizeof(buttonPin[0]);
int cntFragment = 0;
bool pre[] = {HIGH, HIGH, HIGH, HIGH};
bool cur[] = {HIGH, HIGH, HIGH, HIGH};
volatile bool stop = false;

void stopISR() {
  stop = true;
}

bool check_stop() {
  if (stop) {
    stop = false;
    lcd.clear();
    lcd.print("Stopped");
    delay(1500);
    return true;
  }
  return false;
}

void ir_scan_mode() {
  bool printed = false;
  lcd.clear();
  while (1) {
    if (check_stop()) {
      break;
    }
    // Robot is running
    if (!printed) {
      lcd.print("ir scan orz");
      printed = true;
    }
  }
}

void line_scan_mode() {
  bool printed = false;
  lcd.clear();
  while (1) {
    if (check_stop()) {
      break;
    }
    // Robot is running
    if (!printed) {
      lcd.print("line scan orz");
      printed = true;
    }
  }
}

void camera_mode() {
  bool printed = false;
  lcd.clear();
  while (1) {
    if (check_stop()) {
      break;
    }
    // Robot is running
    if (!printed) {
      lcd.print("camera orz");
      printed = true;
   }
  }
}

void bluetooth_mode() {
  bool printed = false;
  lcd.clear();
  while (1) {
    if (check_stop()) {
      break;
    }
    // Robot is running
    if (!printed) {
      lcd.print("bluetooth orz");
      printed = true;
    }
  }
}

void showFragment(int cnt) {
  lcd.clear();
  switch (cnt) {
    case 0:
      lcd.print("< Bluetooth >");
      break;
    case 1:
      lcd.print("< Camera >");
      break;
    case 2:
      lcd.print("< Line scan >");
      break;
    case 3:
      lcd.print("< IR scan >");
      break;
  }
}

void runFragment(int cnt) {
  lcd.clear();
  lcd.print("Done !!!");
  delay(1000);
  lcd.clear();
  switch (cnt) {
    case 0:
      bluetooth_mode();
      break;
    case 1:
      camera_mode();
      break;
    case 2:
      line_scan_mode();
      break;
    case 3:
      ir_scan_mode();
      break;
  }
}

void loading() {
  lcd.print("Loading all mode");
  for (int i = 0; i < 3; i += 1) {
    delay(300);
    lcd.print(".");
  }
}

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < buttonNum; i += 1) {
    pinMode(buttonPin[i], INPUT_PULLUP);
  }
  attachInterrupt(digitalPinToInterrupt(buttonPin[3]), stopISR, FALLING);
  lcd.init();
  lcd.backlight();
  loading();
  showFragment(cntFragment);
}

void loop() {
  for (int i = 0; i < buttonNum; i += 1) {
    cur[i] = digitalRead(buttonPin[i]);
    if (pre[i] == HIGH && cur[i] == LOW) {
      stop = false;
      switch (i) {
        case 0: // LEFT
          cntFragment -= 1;
          if (cntFragment < 0) {
            cntFragment = buttonNum - 1;
          }
          showFragment(cntFragment);
          break;
        case 1: // RUN
          stop = false;
          runFragment(cntFragment);
          showFragment(cntFragment);
          for (int i = 0; i < buttonNum; i += 1) {
            pre[i] = HIGH;
          }
          break;
        case 2: // RIGHT
          cntFragment += 1;
          if (cntFragment >= buttonNum) {
            cntFragment = 0;
          }
          showFragment(cntFragment);
          break;
      }
    }
    pre[i] = cur[i];
  }
}