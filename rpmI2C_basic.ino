#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

volatile unsigned int count = 0;
const byte counterPin = 2;
unsigned long count_start;
unsigned int rpm;
const byte magnet_num = 3;
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
const int debounceDelay = 200;   // the debounce time; increase if the output flickers
const unsigned long one_sec = 1000000;

unsigned int RPM_MAX; // Maximum recorded RPM value
unsigned int RPM_average; // Average RPM value
unsigned long RPM_ROUND; // Total number of RPM measurements
unsigned long long RPM_count; // Accumulated RPM values for averaging

void counter() {
  if ((micros() - lastDebounceTime) > debounceDelay)
  {
    count++;
  lastDebounceTime = micros();
  }
}


void setup() {
  lcd.begin(16, 2);
  lcd.init();       // initialize the lcd
  lcd.backlight();  // turn on the lcd backlight module
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("R= ");
  lcd.setCursor(0, 1);
  lcd.print("M=");
  lcd.setCursor(8, 0);
  lcd.print("A=");
  pinMode(counterPin, INPUT);
  attachInterrupt(0, counter, FALLING);
  count = 0;
  rpm = 0;
  RPM_MAX = 0;
  RPM_ROUND = 0;
  RPM_count = 0;
  RPM_average = 0;
  count_start = 0;
}

void RPM_CAL_MAX(unsigned int f_RPM){
    // if now round's RPM bigger than previous maxium RPM. Updating max RPM.
    if(f_RPM > RPM_MAX){
        RPM_MAX = f_RPM;
    }
}

void RPM_CAL_AVERAGE(unsigned int f_RPM){
    // filter some RPM, because it is abnormal
    if(f_RPM != 0 && f_RPM > 1000 && f_RPM < 40000){
        RPM_count += f_RPM;
        RPM_ROUND += 1;
        RPM_average = RPM_count/RPM_ROUND; //caculate RPM's average.
    }
}

// lcd display three measurements result.
void display_lcd_num(unsigned int f_RPM){
    lcd.setCursor(3, 0);
    lcd.print(f_RPM);
    lcd.setCursor(3, 1);
    lcd.print(RPM_MAX);
    lcd.setCursor(11, 0);
    lcd.print(RPM_average);
}

void loop() {
    if (micros() -  count_start  >= one_sec) {  /* 每秒更新 */
    detachInterrupt(0); // 計算 rpm 時，停止計時  //  cmd();
    // 偵測的格數count * (60 * 1000 / 一圈網格數3）/ 時間差)
    rpm = (60.0 * (float)one_sec / (float)magnet_num ) / ((float)micros() - (float) count_start ) * (float)count;
    count = 0;
    count_start = micros();
    
    RPM_CAL_AVERAGE(rpm);
    RPM_CAL_MAX(rpm);

    attachInterrupt(0, counter, FALLING);
    display_lcd_num(rpm);

  }
}
