#ifndef jsc_Math_h
#define jsc_Math_h

#ifdef __cplusplus
extern "C" {
#endif

	/**
	 * The mathematical constant e. This is Euler's jsc.float64, the base of natural logarithms.
	 * @value 2.718281828459045
	 */
	extern jsc_float64_t jsc_Math_E;
	/**
	 * The natural logarithm of 10.
	 * @value 2.302585092994046
	 */
	extern jsc_float64_t jsc_Math_LN10;
	/**
	 * The natural logarithm of 2.
	 * @value 0.6931471805599453
	 */
	extern jsc_float64_t jsc_Math_LN2;
	/**
	 * The base-2 logarithm of e.
	 * @value 1.4426950408889634
	 */
	extern jsc_float64_t jsc_Math_LOG2E;
	/**
	 * The base-10 logarithm of e.
	 * @value 0.4342944819032518
	 */
	extern jsc_float64_t jsc_Math_LOG10E;
	/**
	 * Pi. This is the ratio of the circumference of a circle to its diameter.
	 * @value 3.141592653589793
	 */
	extern jsc_float64_t jsc_Math_PI;
	/**
	 * The square root of 0.5, or, equivalently, one divided by the square root of 2.
	 * @value 0.7071067811865476
	 */
	extern jsc_float64_t jsc_Math_SQRT1_2;
	/**
	 * The square root of 2.
	 * @value 1.4142135623730951
	 */
	extern jsc_float64_t jsc_Math_SQRT2;
	/**
	 * Returns the absolute value of a jsc.float64 (the value without regard to whether it is positive or negative).
	 * For example, the absolute value of -5 is the same as the absolute value of 5.
	 * @param x   A numeric expression for which the absolute value is needed.
	 */
	jsc_float64_t jsc_Math_abs(jsc_float64_t x);
	/**
	 * Returns the arc cosine (or inverse cosine) of a jsc.float64.
	 * @param x   A numeric expression.
	 */
	jsc_float64_t jsc_Math_acos(jsc_float64_t x);
	/**
	 * Returns the arcsine of a jsc.float64.
	 * @param x   A numeric expression.
	 */
	jsc_float64_t jsc_Math_asin(jsc_float64_t x);
	/**
	 * Returns the arctangent of a jsc.float64.
	 * @param x   A numeric expression for which the arctangent is needed.
	 */
	jsc_float64_t jsc_Math_atan(jsc_float64_t x);
	/**
	 * Returns the angle (in radians) from the X axis to a point.
	 * @param y   A numeric expression representing the cartesian y-coordinate.
	 * @param x   A numeric expression representing the cartesian x-coordinate.
	 */
	jsc_float64_t jsc_Math_atan2(jsc_float64_t y, jsc_float64_t x);
	/**
	 * Returns the smallest integer greater than or equal to its numeric argument.
	 * @param x   A numeric expression.
	 */
	jsc_float64_t jsc_Math_ceil(jsc_float64_t x);
	/**
	 * Returns the cosine of a jsc.float64.
	 * @param x   A numeric expression that contains an angle measured in radians.
	 */
	jsc_float64_t jsc_Math_cos(jsc_float64_t x);
	/**
	 * Returns e (the base of natural logarithms) raised to a power.
	 * @param x   A numeric expression representing the power of e.
	 */
	jsc_float64_t jsc_Math_exp(jsc_float64_t x);
	/**
	 * Returns the greatest integer less than or equal to its numeric argument.
	 * @param x   A numeric expression.
	 */
	jsc_int64_t jsc_Math_floor(jsc_float64_t x);
	/**
	 * Returns the natural logarithm (base e) of a jsc.float64.
	 * @param x   A numeric expression.
	 */
	jsc_float64_t jsc_Math_log(jsc_float64_t x);
	/**
	 * Returns the larger of a set of supplied numeric expressions.
	 */
	jsc_float64_t jsc_Math_max(jsc_float64_t a, jsc_float64_t b);
	/**
	 * Returns the smaller of a set of supplied numeric expressions.
	 */
	jsc_float64_t jsc_Math_min(jsc_float64_t a, jsc_float64_t b);
	/**
	 * Returns the value of a base expression taken to a specified power.
	 * @param x   The base value of the expression.
	 * @param y   The exponent value of the expression.
	 */
	jsc_float64_t jsc_Math_pow(jsc_float64_t x, jsc_float64_t y);
	/**
	 * Returns a pseudorandom jsc.float64 between 0 and 1.
	 */
	jsc_float64_t jsc_Math_random(void);
	/**
	 * Returns a supplied numeric expression rounded to the nearest integer.
	 * @param x   The value to be rounded to the nearest integer.
	 */
	jsc_int64_t jsc_Math_round(jsc_float64_t x);
	/**
	 * Returns the sine of a jsc.float64.
	 * @param x   A numeric expression that contains an angle measured in radians.
	 */
	jsc_float64_t jsc_Math_sin(jsc_float64_t x);
	/**
	 * Returns the square root of a jsc.float64.
	 * @param x   A numeric expression.
	 */
	jsc_float64_t jsc_Math_sqrt(jsc_float64_t x);
	/**
	 * Returns the tangent of a jsc.float64.
	 * @param x   A numeric expression that contains an angle measured in radians.
	 */
	jsc_float64_t jsc_Math_tan(jsc_float64_t x);

#ifdef __cplusplus
}
#endif

#endif

