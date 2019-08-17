#include <avr/io.h>
#include <avr/wdt.h>

#define CTOP 200000UL

int main(void) {
  unsigned long count = 0;  // 32bit

  DDRD  = 0x08;  // PD3 を出力ピンに設定

  for (;;) {
    wdt_reset();
    count++;
    if (count >= CTOP) {
      count = 0;
      PORTD ^= 0x08;
    }
  }
  return 0;
}
