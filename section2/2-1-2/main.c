#include <avr/io.h>
#include <avr/wdt.h>

#define CTOP 200000UL

int main(void) {
  unsigned long cnt = 0;  // 32bit
  unsigned long p = 0;

  DDRC = 0x30;  // PC5/4 を出力ピンに設定
  PORTC = 0x30; // PC5/4 の出力をH/Hに設定

  for (;;) {
    wdt_reset();
    p++;
    if (p==4) {
      p = 0;
      cnt++;
    }
    if (cnt >= CTOP) {
      cnt = 0;
      PORTC ^= 0x10;
    }
  }
  return 0;
}
