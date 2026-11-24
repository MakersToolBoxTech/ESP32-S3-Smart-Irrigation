// MICRODUCK SMART FARM - AUTO SOIL MOISTURE DEMO / ESP32-S3
// Changes a VIRTUAL soil-moisture value every 5 seconds.
// Real soil sensor / potentiometer is NOT being read in this AUTO DEMO.
// LCD1602 (I2C), relay and LED show soil percentage and pump state.
// Wokwi simulation only; do not power a real pump from ESP32 GPIO.
//
// 65 -> 55 -> 45 -> 35 -> 25 [PUMP ON] -> 35 -> 45 -> 55
//    -> 65 [PUMP OFF] -> ... repeating every 5 seconds.
// <35%: start watering; >55%: stop watering (hysteresis).
// LCD driver uses only built-in Wire.h (no external library).

#include <Wire.h>

const int RELAY_PIN = 5;
const int PUMP_LED_PIN = 6;
const int LCD_SDA_PIN = 8;
const int LCD_SCL_PIN = 9;
const uint8_t LCD_ADDRESS = 0x27;
const unsigned long SENSOR_INTERVAL_MS = 5000;
const int START_WATERING_BELOW = 35;
const int STOP_WATERING_ABOVE = 55;

int soilMoisture = 65;   // Initial VIRTUAL soil moisture in percent
bool pumpOn = false;
unsigned long lastSensorChange = 0;

// PCF8574T -> HD44780: P0=RS, P2=E, P3=backlight, P4..7=D4..7
void lcdExpander(uint8_t data) {
  Wire.beginTransmission(LCD_ADDRESS);
  Wire.write(data | 0x08); // Keep backlight on
  Wire.endTransmission();
}

void lcdWrite4(uint8_t nibble, bool dataMode) {
  uint8_t value = (nibble << 4) | (dataMode ? 0x01 : 0x00);
  lcdExpander(value);
  delayMicroseconds(2);
  lcdExpander(value | 0x04); // E high
  delayMicroseconds(2);
  lcdExpander(value);        // E low: latch the nibble
  delayMicroseconds(60);
}

void lcdSend(uint8_t value, bool dataMode) {
  lcdWrite4(value >> 4, dataMode);
  lcdWrite4(value & 0x0f, dataMode);
}

void lcdCommand(uint8_t value) {
  lcdSend(value, false);
  if (value == 0x01 || value == 0x02) delay(2);
}

void lcdInit() {
  delay(60);
  lcdWrite4(0x03, false);
  delay(5);
  lcdWrite4(0x03, false);
  delayMicroseconds(200);
  lcdWrite4(0x03, false);
  delayMicroseconds(200);
  lcdWrite4(0x02, false);  // switch to four-bit mode
  lcdCommand(0x28);       // 4-bit, 2 lines, 5x8 font
  lcdCommand(0x0C);       // display on, cursor off
  lcdCommand(0x06);       // move cursor forward
  lcdCommand(0x01);       // clear LCD
}

void lcdRow(int row, const char *text) {
  lcdCommand(0x80 | (row == 0 ? 0x00 : 0x40));
  bool reachedEnd = false;
  for (int i = 0; i < 16; ++i) {
    if (!reachedEnd && text[i] == '\0') reachedEnd = true;
    lcdSend(reachedEnd ? ' ' : (uint8_t)text[i], true);
  }
}

void showStatus() {
  const char *soilLabel = soilMoisture < START_WATERING_BELOW ? "DRY" :
                          soilMoisture > STOP_WATERING_ABOVE ? "WET" : "OK";
  char firstRow[17];
  char secondRow[17];
  snprintf(firstRow, sizeof(firstRow), "SOIL:%3d%% %-6s", soilMoisture, soilLabel);
  snprintf(secondRow, sizeof(secondRow), "PUMP:%-3s STEP:5s", pumpOn ? "ON" : "OFF");
  lcdRow(0, firstRow);
  lcdRow(1, secondRow);
  Serial.printf("[AUTO 5s] SOIL: %3d%% (%s) | PUMP: %s | <35 ON / >55 OFF\n",
                soilMoisture, soilLabel, pumpOn ? "ON" : "OFF");
}

void setPump(bool enabled) {
  if (pumpOn == enabled) return;
  pumpOn = enabled;
  digitalWrite(RELAY_PIN, pumpOn ? LOW : HIGH);  // Wokwi NPN relay active LOW
  digitalWrite(PUMP_LED_PIN, pumpOn ? HIGH : LOW);
  Serial.println(pumpOn ? ">>> PUMP ON  - watering dry soil" :
                          ">>> PUMP OFF - soil is moist enough");
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(PUMP_LED_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Pump OFF at power-up
  digitalWrite(PUMP_LED_PIN, LOW);
  Wire.begin(LCD_SDA_PIN, LCD_SCL_PIN);
  lcdInit();
  Serial.println("MICRODUCK - SMART IRRIGATION / AUTO DEMO");
  Serial.println("VIRTUAL SENSOR updates every 5 seconds. No hand turning required.");
  showStatus();
  lastSensorChange = millis();
}

void loop() {
  if (millis() - lastSensorChange >= SENSOR_INTERVAL_MS) {
    lastSensorChange += SENSOR_INTERVAL_MS;
    // When pump is running, soil gradually gets wetter;
    // without watering, it gradually gets drier.
    soilMoisture += pumpOn ? 10 : -10;
    soilMoisture = constrain(soilMoisture, 0, 100);

    if (!pumpOn && soilMoisture < START_WATERING_BELOW) {
      setPump(true);
    } else if (pumpOn && soilMoisture > STOP_WATERING_ABOVE) {
      setPump(false);
    }
    showStatus();
  }
  delay(50);
}
