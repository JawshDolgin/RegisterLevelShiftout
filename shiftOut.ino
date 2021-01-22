//Project: register level shiftout
//Author: Josh Dolgin
//Date: YY/MM/DD
//Status:
#define ENABLE 1<<PA6
#define LATCH 1<<PA7
#define DATA 1<<PB2
#define CLOCK 1<<PB0
uint8_t dir = 0xFF;

void setup() {
  DDRA |= LATCH | ENABLE;
  DDRB |= CLOCK | DATA;
  PORTA &= ~ENABLE;
}

void shiftout(uint8_t order, uint8_t value) {
  PORTA &= ~LATCH;
  uint8_t mask = order ? 0x80 : 0x01; // if non-zero (255), the mask changes based of the order
  for (uint8_t i = 0; i < 8; i++) {
    PORTB &= ~CLOCK;
    if (value & mask)
      PORTB |= DATA;
    else
      PORTB &= ~DATA;
    PORTB |= CLOCK;
    value = order ? value << 1 : value>>1;
  }
  PORTA |= LATCH;
}

void loop() {
  for (uint8_t i = 0; i < 8; i++) {
    shiftout(dir, 1 << i);
    delay(100);
  }
  dir = ~dir;
}
