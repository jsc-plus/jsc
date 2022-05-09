#include "jsc_type.h"
#include "jsc_class.h"
#include "jsc_String.h"
#include "jsc_variant.h"
#include "jsc_buffer.h"
#include "jsc_Math.h"
#include "jsc_Math.inc"
#include <math.h>

/* class implemented */

/* function implemented */
jsc_float64_t jsc_Math_abs(jsc_float64_t x) {
	return fabs(x);
}
jsc_float64_t jsc_Math_acos(jsc_float64_t x) {
	return acos(x);
}
jsc_float64_t jsc_Math_asin(jsc_float64_t x) {
	return asin(x);
}
jsc_float64_t jsc_Math_atan(jsc_float64_t x) {
	return atan(x);
}
jsc_float64_t jsc_Math_atan2(jsc_float64_t y, jsc_float64_t x) {
	return atan2(y,x);
}
jsc_float64_t jsc_Math_ceil(jsc_float64_t x) {
	return ceil(x);
}
jsc_float64_t jsc_Math_cos(jsc_float64_t x) {
	return cos(x);
}
jsc_float64_t jsc_Math_exp(jsc_float64_t x) {
	return exp(x);
}
jsc_int64_t jsc_Math_floor(jsc_float64_t x) {
	return (jsc_int64_t) floor(x);
}
jsc_float64_t jsc_Math_log(jsc_float64_t x) {
	return log(x);
}
jsc_float64_t jsc_Math_max(jsc_float64_t a, jsc_float64_t b) {
	return MAX(a, b);
}
jsc_float64_t jsc_Math_min(jsc_float64_t a, jsc_float64_t b) {
	return MIN(a,b);
}
jsc_float64_t jsc_Math_pow(jsc_float64_t x, jsc_float64_t y) {
	return pow(x,y);
}
jsc_float64_t jsc_Math_random() {
	return random();
}
jsc_int64_t jsc_Math_round(jsc_float64_t x) {
	return (jsc_int64_t) round(x);
}
jsc_float64_t jsc_Math_sin(jsc_float64_t x) {
	return sin(x);
}
jsc_float64_t jsc_Math_sqrt(jsc_float64_t x) {
	return sqrt(x);
}
jsc_float64_t jsc_Math_tan(jsc_float64_t x) {
	return tan(x);
}
