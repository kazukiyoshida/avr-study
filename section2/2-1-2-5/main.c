#include <avr/io.h>
#include <avr/wdt.h>

#define CTOP 250000UL
#define STEP 100

int main(void) {
  unsigned long count = 0;  // 32bit
  unsigned long cmp   = 0;  // 32bit

  DDRC  = 0x30;  // PC5/4 を出力ピンに設定
  PORTC = 0x10;  // PC5/4 の出力をL/Hに設定

  for (;;) {
    wdt_reset();
    count++;
    if (count >= CTOP) {
      count = 0;
      PORTC |= 0x10; // PC4 の出力を H
      cmp += STEP;
      if (cmp >= CTOP) {
        cmp = 0;
      }
    }
    if (count == cmp) {
      PORTC &= ~0x10;  // PC 4 の出力を L
    }
  }
  return 0;
}
