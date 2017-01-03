# Integral-Calculator
C++ program to calculate polynomial integrals (definite or indefinite). I/O is done with text files.
To use this program, create a text file with a list of polynomials named "integrals.txt" in the same folder as the executable and run it.

Input file formatting tips:
- Use the ^ character to notate exponentiation.
	- ex. 5x^2
- Use the | character to notate integration.
- For definite integrals, use integer values before and after the pipe.
	- ex. 1|2 x dx
- For indefinite integrals, leave the pipe by itself.
	- ex. | x dx
- Use x as the variable.
- End the integral with dx.
- Use a space before the first term of the integral and before dx.
- Separate each polynomial with a newline.
- It is not necessary to write the coefficient of a term if its coefficient is 1. For example, x and 1x are functionally equivalent.
- It is not necessary to write the power of a term if its power is 1. For example, x and x^1 are functionally equivalent.
- It is not necessary to write 'x' in a term if its power is 0. For example, 4 and 4x^0 are functionally equivalent.
- It is not necessary to write the terms in order of descending power. Integral Calculator will output the terms in order of descending power, regardless of the original order.
- Terms with non-integer coefficients are not currently supported.
- Terms with a power of -1 are not currently supported.
- If multiple terms have the same power, Integral Calculator will combine those terms in the integration.

See the example_integrals.txt file for examples.