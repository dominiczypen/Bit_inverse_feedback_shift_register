# Bit_inverse_feedback_shift_register
Similar to linear feedback shift register. Take bit at variable position, invert it, use it as feedback bit.
In the uint16_t version of the shift register, the bit position for the bit to be inverted and fed back starts at 0
and goes up to 14, then starts at 0 again, and so on. Really quite a simple mechanism. Results as to 
output numbers look "pseudo-random" enough, but need more analysis.

# neg_LFSR_2_taps.c
A variant of the above: 2 taps, one tap gets negated, XOR the two resulting bits and use as new bit.
