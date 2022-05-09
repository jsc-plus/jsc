
declare namespace jsc {

    namespace Math {

        /** 
         * The mathematical constant e. This is Euler's jsc.float64, the base of natural logarithms. 
         * @value 2.718281828459045 
         */
        const E: jsc.float64;
        /** 
         * The natural logarithm of 10. 
         * @value 2.302585092994046
         */
        const LN10: jsc.float64;
        /** 
         * The natural logarithm of 2. 
         * @value 0.6931471805599453
         */
        const LN2: jsc.float64;
        /** 
         * The base-2 logarithm of e. 
         * @value 1.4426950408889634
         */
        const LOG2E: jsc.float64;
        /** 
         * The base-10 logarithm of e. 
         * @value 0.4342944819032518
         */
        const LOG10E: jsc.float64;
        /** 
         * Pi. This is the ratio of the circumference of a circle to its diameter. 
         * @value 3.141592653589793
         */
        const PI: jsc.float64;
        /** 
         * The square root of 0.5, or, equivalently, one divided by the square root of 2. 
         * @value 0.7071067811865476
         */
        const SQRT1_2: jsc.float64;
        /** 
         * The square root of 2. 
         * @value 1.4142135623730951
         */
        const SQRT2: jsc.float64;
        /**
         * Returns the absolute value of a jsc.float64 (the value without regard to whether it is positive or negative).
         * For example, the absolute value of -5 is the same as the absolute value of 5.
         * @param x A numeric expression for which the absolute value is needed.
         */
        function abs(x: jsc.float64): jsc.float64;
        /**
         * Returns the arc cosine (or inverse cosine) of a jsc.float64.
         * @param x A numeric expression.
         */
        function acos(x: jsc.float64): jsc.float64;
        /**
         * Returns the arcsine of a jsc.float64.
         * @param x A numeric expression.
         */
        function asin(x: jsc.float64): jsc.float64;
        /**
         * Returns the arctangent of a jsc.float64.
         * @param x A numeric expression for which the arctangent is needed.
         */
        function atan(x: jsc.float64): jsc.float64;
        /**
         * Returns the angle (in radians) from the X axis to a point.
         * @param y A numeric expression representing the cartesian y-coordinate.
         * @param x A numeric expression representing the cartesian x-coordinate.
         */
        function atan2(y: jsc.float64, x: jsc.float64): jsc.float64;
        /**
         * Returns the smallest integer greater than or equal to its numeric argument.
         * @param x A numeric expression.
         */
        function ceil(x: jsc.float64): jsc.float64;
        /**
         * Returns the cosine of a jsc.float64.
         * @param x A numeric expression that contains an angle measured in radians.
         */
        function cos(x: jsc.float64): jsc.float64;
        /**
         * Returns e (the base of natural logarithms) raised to a power.
         * @param x A numeric expression representing the power of e.
         */
        function exp(x: jsc.float64): jsc.float64;
        /**
         * Returns the greatest integer less than or equal to its numeric argument.
         * @param x A numeric expression.
         */
        function floor(x: jsc.float64): jsc.int;
        /**
         * Returns the natural logarithm (base e) of a jsc.float64.
         * @param x A numeric expression.
         */
        function log(x: jsc.float64): jsc.float64;
        /**
         * Returns the larger of a set of supplied numeric expressions.
         */
        function max(a: jsc.float64, b: jsc.float64): jsc.float64;
        /**
         * Returns the smaller of a set of supplied numeric expressions.
         */
        function min(a: jsc.float64, b: jsc.float64): jsc.float64;
        /**
         * Returns the value of a base expression taken to a specified power.
         * @param x The base value of the expression.
         * @param y The exponent value of the expression.
         */
        function pow(x: jsc.float64, y: jsc.float64): jsc.float64;
        /** Returns a pseudorandom jsc.float64 between 0 and 1. */
        function random(): jsc.float64;
        /**
         * Returns a supplied numeric expression rounded to the nearest integer.
         * @param x The value to be rounded to the nearest integer.
         */
        function round(x: jsc.float64): jsc.int;
        /**
         * Returns the sine of a jsc.float64.
         * @param x A numeric expression that contains an angle measured in radians.
         */
        function sin(x: jsc.float64): jsc.float64;
        /**
         * Returns the square root of a jsc.float64.
         * @param x A numeric expression.
         */
        function sqrt(x: jsc.float64): jsc.float64;
        /**
         * Returns the tangent of a jsc.float64.
         * @param x A numeric expression that contains an angle measured in radians.
         */
        function tan(x: jsc.float64): jsc.float64;
    }
}