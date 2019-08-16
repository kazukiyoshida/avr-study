#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>

volatile unsigned char move_left = 1;

ISR(TIMER1_COMPA_vect)
{
  unsigned char sw;

  sw = (~PINC >> 4) & 3;
  if (sw == 1) {
    move_left = 1;
  }
  if (sw == 2) {
    move_left = 0;
  }

  // ブザー
  TCCR2A ^= 0x10; // コンペアマッチ出力のON/OFF

  // マトリクスLED の表示更新、音程の変更
  if (move_left) {
    PORTB = (PORTB << 1) | ((PORTB >> 7 ) & 1);
    OCR2A++;
  }
  else {
    PORTB = (PORTB >> 1) | ((PORTB & 1) << 7);
    OCR2A--;
  }
}

int main() {
  // ポートB, C, D の入出力方向を設定する
  DDRB = 0xFF;
  DDRC = 0x0F;
  DDRD = 0xFE;

  // ポートB, C, D の出力値やプルアップの設定
  PORTB = 0x07;
  PORTC = 0x30;
  PORTD = 0x00;

  // タイマ2の設定
  TCNT2 = 0;
  OCR2A = 150;
  TCCR2A = 0x12;
  TCCR2B = 0x04;

  // タイマ1の設定
  TCNT1 = 0;
  OCR1A = 390;
  TCCR1A = 0x00;
  TCCR1B = 0x0D;
  TIMSK1 = _BV(OCIE1A); // タイマ割り込み有効化

  sei();

  for (;;) {
    wdt_reset();
  }
  return 0;
}
