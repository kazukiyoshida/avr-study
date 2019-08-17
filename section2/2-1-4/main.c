#include <avr/io.h>
#include <avr/wdt.h>

#define CTOP 200000UL
#define CMP  150000UL // 比較値

int main(void) {
  unsigned long count = 0;  // 32bit

  DDRC  = 0x30;  // PC5/4 を出力ピンに設定
  PORTC = 0x30;  // PC5/4 の出力をH/Hに設定

  for (;;) {
    wdt_reset();
    count++;
    if (count >= CTOP) {
      count = 0;
      PORTC ^= 0x10;
    }
    if (count == CMP) {
      PORTC ^= 0x20;
    }
  }
  return 0;
}
