/***************************************************************************/
//            Hardware: RadioShack Tricolor LED Strip
//            Arduino IDE: Atmega328p with 16Mhz Crystal
//            Date:      March 12, 2019
//            Author: Matthew Martin
//
//  Derived from Tricolor-LED-Strip.ino
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, see <http://www.gnu.org/licenses/>
//
/*****************************************************************************/

#include <avr/pgmspace.h>
#include <util/delay.h>

#define DATA_1 (PORTC |= 0x01) //switch high
#define DATA_0 (PORTC &= 0xFE) //switch low
#define STRIP_PINOUT (DDRC |= (1 << PC0))

//Light all lights red
//Store in program memeory
PROGMEM const unsigned long pattern_test_red[10] =
  {0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000,
    0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000};

//Declare functions
void reset_strip();
void send_1M_pattern(const unsigned long data[10], int pattern_no, int frame_rate);
void send_strip(uint32_t data);

int main(void){
  STRIP_PINOUT;
  reset_strip()

  while(1){
    send_1M_pattern(pattern_test_red, 10, 500);
  }
}

//Reset strip by holding PC0 low
void	reset_strip()
{
  DATA_0;
  _delay_us(20);
}

void send_1M_pattern(const unsigned long data[10], int pattern_no, int frame_rate)
{
  int r=0;
  int c=0;
  uint32_t temp_data;

  for (r = 0;r < pattern_no; r++)
  {
    noInterrupts();
    for (c=0;c<10;c++)
    {
      temp_data=pgm_read_dword_near(&data[i][j]);
      send_strip(temp_data);
    }
    interrupts();
    delay(frame_rate);
  }
}

void send_strip(uint32_t data)
{
  int i;
  unsigned long j=0x800000;
  for (i=0;i<24;i++) {
    if (data & j){
      DATA_1;
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");

/*----------------------------*/
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
/*----------------------------*/
      DATA_0;
    }
    else
    {
      DATA_1;
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      DATA_0;
/*----------------------------*/
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
/*----------------------------*/
    }
    //shift to next bit
    j>>=1;
  }
}
