/* Author: D. van der Zypen
 * Last modified: 2024-12-17
 * Goal: Some experiments with a primitive non-linear feedback
 * shift register with 2 taps: one negated, one original, XOR them
 * and that's the new bit.
 *
 * Compile: gcc neg_LFSR_2_taps.c -o out 
 * Run: ./out > output.txt (to have output in file) */

#include <stdio.h>
#include <stdint.h>

char bit(uint16_t x, char pos);
void nlfsr_step(uint16_t *up, char neg_tap_idx, char pos_tap_idx);
//----------------------
char bit(uint16_t x, char pos)
  /* gives back bit number <<pos>> seen from the right
   * (least significant) bit*/
{
  return (x >> pos) & 1;
}
//----------------------
void nlfsr_step(uint16_t *up, char neg_tap_idx, char pos_tap_idx)
  /* invert bit at <<neg_tab_pos>> and XOR with bit
   * at <<tab_pos>>. Finally shift and insert new bit.
   * num_bits gives cutoff -> i.e. num_bits == 4 */

{
  char positive_bit = bit(*up, pos_tap_idx);
  char negative_bit = bit(~(*up), neg_tap_idx); // ~ negates ALL bits of *up
  char new_bit = positive_bit ^ negative_bit;
  *up = ((*up) << 1) | new_bit; // shift and insert
  return;
}
//----------------------
int main()
{
  /* Procedure: check out all combinations of tap positions
   * (index of neg. tap, index of pos. tap) to see which
   * of these pairings generate full runs for the neg-LFSR.  */
  
  char my_neg_idx= 1;
  char my_pos_idx;
  while (my_neg_idx < 15)
  {
    my_pos_idx = my_neg_idx + 1; 
                                               
    while (my_pos_idx < 16)  // start run with new tap positions
    {
      uint16_t my_uint16 = 0;
          // --> initialize my_uint16 so while loop works
      uint16_t iterations = 1;
      nlfsr_step(&my_uint16, my_neg_idx, my_pos_idx); 
            // otherwise next loop terminates
            // right away
  
      // Loop at most 2^{16} = 65536 times:
      while ((my_uint16 != 0) && (iterations != 0))
      {
        nlfsr_step(&my_uint16, my_neg_idx, my_pos_idx); 
        /*curious*/ if (my_uint16 + 1 == 0) {printf("1111111111 reached!");}
        iterations++;
      }
      printf("Tap positions neg/pos %d / %d: ", my_neg_idx, my_pos_idx);

      if (my_uint16 == 0) // YES: we circled back to 0!
      {
        printf("%d rounds\n", iterations);
      }
      else // we reached 
      {
        printf("LOOP without coming back to 0\n");
      }
      my_pos_idx++; // next sub-round; my_neg_idx stays the same
    }
    my_neg_idx++;
  }
  printf("FINISHED");
  return 0;
}

