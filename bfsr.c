/* Author: Dominic van der Zypen
 * Bitwise Shift register: invert bit at variable bit positions
 * and use it as feedback bit. In the uint16_t shift register version
 * the bit positions go from 0 up to 14, starting from 0 again, and so on.
 */

#include <stdio.h>
#include <stdint.h> // for using uint16_t

char bit(uint16_t x, char pos);
void bfsr(uint16_t* xp, char* pos_p);
void print_uint16_bin(uint16_t x);
void print_uint16_hex(uint16_t x);
//--------------------------------
char bit(uint16_t x, char pos)
{
  return ((x >> pos) & 1);
}
//--------------------------------
void bfsr(uint16_t* xp, char* pos_p)
     // invert bit at position *pos_p and use this as new bit.
     // *pos_p goes from 0 to 14 then gets set back to 0, etc.
{
  char new_bit;
  new_bit = !bit(*xp, *pos_p);

  // update *pos_p branch-free
  *pos_p  = ((*pos_p) < 14)*(*pos_p + 1); 
          // increase if < 14, set back to 0 otherwise
  
  // update *xp
  *xp = ((*xp) >> 1) | (new_bit << 15);
}
//--------------------------------
void print_uint16_bin(uint16_t x)
{
  char i = 0;
  char mybit;
  while (i < 16)
  {
    mybit = (x & (1 << 15)) >> 15;
    printf("%d", mybit);
    x = x << 1;
    i++;
    if (!(i & 3)) {printf(" ");} // formatting
  }
  printf("\n");
}
//-------------------------------
void print_uint16_hex(uint16_t x)
{
  char i = 0;
  char myhex;
  printf("0x");
  while (i < 4)
  {
    myhex = (x & (0xf << 12)) >> 12;
    printf("%x", myhex);
    x = x << 4;
    i++;
  }
  printf(" : ");
}
//-------------------------------
int main()
{
  uint16_t x = 0;
  char pos = 0;
  int i = 0;
  bfsr(&x, &pos); // pos gets updated in bfsr()
  while (i < 80)
  {
    print_uint16_hex(x);
    print_uint16_bin(x); 
    bfsr(&x, &pos); // pos gets updated in bfsr()
    i++;
  }
  return 0;
}
