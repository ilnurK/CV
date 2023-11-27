# Library for working with the Decimal type  
## Decimal is suitable for financial calculations that require a large number of significant whole and fractional digits and reduce rounding errors.  

## A decimal number is a floating-point value consisting of a sign, a numeric value where each digit ranges from 0 to 9, and a scaling factor that specifies the position of the decimal point separating the integer and fractional parts of the numeric value.  

### The binary representation of Decimal consists of a 1-bit sign, a 96-bit integer, and a scale factor used to divide the 96-bit integer and indicate how much of it is a decimal. The scaling factor is implicitly equal to the number 10 raised to a power in the range from 0 to 28. Therefore, the binary representation of Decimal is ((-2^96 to 2^96) / 10^(0 to 28)), where -( 2^96-1) = -79,228,162,514,264,337,593,543,950,335 is equal to the minimum value, and 2^96-1 = 79,228,162,514,264,337,593,543,950,335 is equal to the maximum value.  

Decimal number is implemented as a four-element array of 32-bit signed integers (int bits[4]).  
bits[0], bits[1], and bits[2] contain the low, middle, and high 32 bits of a 96-bit integer, respectively.  
bits[3] contains the scale factor and sign, and consists of the following parts:  
- Bits 0 to 15, the least significant word, are not used and must be zero.
- Bits 16 to 23 must contain an exponent from 0 to 28, which specifies the power of 10 to divide the integer.
- Bits 24 to 30 are not used and must be zero.
- Bit 31 contains the sign; 0 means positive and 1 means negative.

### Arithmetic functions:
s21_add - addition  
s21_sub - subtracion  
s21_mul - multiplication  
s21_div - division  

The functions return an error code:
- 0 - OK
- 1 - the number is too large or equal to infinity
- 2 - the number is too small or equal to negative infinity
- 3 - division by 0

### Comparison operators
s21_is_less   
s21_is_less_or_equal  
s21_is_greater  
s21_is_greater_or_equal  
s21_is_equal   
s21_is_not_equal    

Return value:
- 0 - FALSE
- 1 - TRUE

### Converters

s21_from_int_to_decimal  
s21_from_float_to_decimal  
s21_from_decimal_to_int  
s21_from_decimal_to_float  

Return value - error code:
  - 0 - OK
  - 1 - conversion error

### Other features

s21_floor - Rounds the specified Decimal number to the nearest integer towards negative infinity.  
s21_round - Rounds Decimal to the nearest integer.  
s21_truncate - Returns the integer digits of the specified Decimal number; any fractional digits are discarded, including trailing zeros.  
s21_negate - Returns the result of multiplying the specified Decimal by -1.  

Return value - error code:
  - 0 - OK
  - 1 - calculation error