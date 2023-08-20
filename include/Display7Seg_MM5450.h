/*
 * @author Ricardo Pinto
 * @date 20/08/2023
 * @brief
 */

#ifndef Display7Seg_MM5450_h
#define Display7Seg_MM5450_h

#define STARTBIT 1                     // value of the starting bit;
#define ARRAY_LENGTH 5
#define DATABITS 36                    // what we must send to the chip in order to control the lights

class Display7Seg_MM5450 {
  public:
    Display7Seg_MM5450(uint8_t clockPin, uint8_t dataPin) {
      this->clockPin = clockPin;
      this->dataPin = dataPin;

      for(int i = 0; i < ARRAY_LENGTH; i++) {
        ledArray[i] = 0;
      }
    }

    void send(uint16_t num) {
      // get units, dec, cent and mil
      uint8_t digits[4] = {0, 0, 0, 0}; // m, c, d, u
      digits[0] = num / 1000;

      num -= digits[0] * 1000;
      digits[1] = num / 100;

      num -= digits[1] * 100;
      digits[2] = num / 10;

      num -= digits[2] * 10;
      digits[3] = num;
      
      for (int i=0; i<4; i++) {
        ledArray[i] = intTo8Seg(digits[i]);
      }

      sendToChip();
    }

    void allOn() {
      for(int i = 0; i < ARRAY_LENGTH; i++) {
        ledArray[i] = 0b11111111;
      }
      sendToChip();
    }

    void allOff() {
      for(int i = 0; i < ARRAY_LENGTH; i++) {
        ledArray[i] = 0;
      }
      sendToChip();
    }

    void initTest() {
      // Turns On the Leds 1 by 1 to test the connections
      allOff();
      int diplay_idx;
      for (int i=0; i<8*4; i++) {
        diplay_idx = i/8;
        ledArray[diplay_idx] = ledArray[diplay_idx] | 0b00000001;
        sendToChip();
        delay(300);
        ledArray[diplay_idx] = ledArray[diplay_idx] << 1;
      }
    }

  private:
    uint8_t intTo8Seg(uint8_t num) {
      // 0 < num < 9
      uint8_t patterns[] = {0b01111110, 0b00001100, 0b10110110, 0b10011110, 0b11001100, 0b11011010, 0b11111010, 0b00001110, 0b11111110, 0b11011110};
      return patterns[num];
    }

    void sendToChip() {
      digitalWrite(this->clockPin, LOW);
      delay(2);
      digitalWrite(this->dataPin, STARTBIT);
      delay(2);
      digitalWrite(this->clockPin, HIGH);
      delay(5);
      digitalWrite(this->clockPin, LOW);
      delay(2);
      for(int i = 0; i < ARRAY_LENGTH-1; i++) {
        shiftOut(this->dataPin, this->clockPin, LSBFIRST, ledArray[i]);
      }
      shiftOut(this->dataPin, this->clockPin, LSBFIRST, 0b00);
    }

    uint8_t clockPin;
    uint8_t dataPin;

    byte ledArray[ARRAY_LENGTH]; // 34/4 = 8, but we have 2 more leds
};

#endif
