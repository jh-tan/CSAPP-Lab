/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
    /*
     *Explanation
      1. There are many ways to solve this, my soluion is by using the NOR (~x & ~y)
      2. We will first x And y and x Nor y 
      3. Then, we Nor the 2 result and get the answer.
      Demo:
      - x = 0101  y = 0011  x XOR y = 0110
      let a = x And y = 0001
      let b = x Nor y = 1000
      - We can see the pattern here already:
        XOR: 0110
          a: 0001
          b: 1000
      - We just need to make the middle part become 1
      - ~a = 1110  ~b = 0111
      - 1110
        0111
        ----
        0110
     */
    return (~(x & y) & ~(~x&~y));
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
    /*
     *Explanation
      1. Tmin = 1000 ... 000
      2. Simply left shit 1 with 31, then we can generate the pattern
     */
    return 1 << 31;

}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
    /*
     *Explanation
      1. Tmax = 0111 1111 ... 1111, we can just negate Tmin to compare, but shifting is forbid in here.
      2. So, how we done here is by +1 to the x, +x, and negate it.
      3. Why? Is because if x is Tmax, x + 1 will become Tmin, and Tmin + Tmax = -1 (1111 1111 ... 1111)
         , and negate it will become 0.
      4. Not the result, we can then generate the answer. BUT, if x is -1, it will have the exact output also.
         - 1111 1111 ... 1111 + 1 -> 0000 .... 0000 + x -> 1111 ... 1111 , negate -> 0000 ... 0000
      5. So, we need to handle the case by using xor operation.
      6. We + 1 to x , and NOT it. If x is -1, +1 will become 0, !0 = 1
       POSSIBLE CASES:
       a. x = -1 ,   1 ^ 1 = 0
       b. x = Tmax , 1 ^ 0 = 1
       c. x = other random number , 1 ^ 1 = 0
     */
    return !(~((x+1)+x))^!(x+1);
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
    /*
     *Explanation
      1. Allodd = 1010 1010 1010 1010 1010 1010 1010 1010 
      2. We cannot use big constant, so we created it by ourself
         1010 1010 0000 0000 0000 0000 0000 0000 + (0xAA << 24 )
         0000 0000 1010 1010 0000 0000 0000 0000 + (0xAA << 16 )
         0000 0000 0000 0000 1010 1010 0000 0000 + (0xAA << 8 )
         0000 0000 0000 0000 0000 0000 1010 1010 + 0xAA 
      3. odd & x to generate a 'version' that is only consists of odd bits.
       - let x = 1100 0000 1010 1010
       - let odd = 1010 1010 1010 1010 1010 1010 1010 1010
         1010 1010 1010 1010 1010 1010 1010 1010
         0000 0000 0000 0000 1100 0000 1010 1010 &
         0000 0000 0000 0000 1000 0000 1010 1010
     */
    int odd = (0xAA<<24) + (0xAA<<16) + (0xAA<<8) + 0xAA;
    return !((odd & x) ^ odd);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
    /*
     *Explanation
      1. For two-complement integer, -x === ~x + 1
     */
    return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
    /*
     *Explanation
      0x3 = 0011 , 9 = 0x1001
      1. First, split the x into two parts to compare, namely left and right.
      2. Left will use to handle to check if it is 0x3
      3. Right side will be use to check if the number is within 9. How it done is just by checking if the certain bit is set.
      4. 0000 , if the msb is set, and also second bit / third bit is set, then it will exceed 9 and it is invalid.
         POSSIBLE CASES:
         1000 - Valid (msb is set, but second or third bit is not set)
         0110 - Valid(msb is not set , and the rest of the bits are set)
         0000 - Valid (all bits are not set)
         1100 - Invalid (msb and second/third bit are both set)
      5. So, we found that the pattern is, return 0 only if both msb and second/third bits are set.
      6. xor does not work here as 0 ^ 0 = 0 , but we wanted it to be 1.
      7. What we do is, !(x&!!y)
         - x = 1 , y = 0, !(1&!!0) = !(1&0) = 1
         - x = 0 , y = 1, !(0&!!1) = !(0&0) = 1
         - x = 0 , y = 0, !(0&!!0) = !(0&0) = 1
         - x = 0 , y = 0, !(1&!!1) = !(1&1) = 0
      8. Lastly, simply left & right
     */
    int left = !((x >> 4) ^ 0x3);
    int right = !((x >> 3 & 1) & !!( x>>1 & 0x3));
    return left & right;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    /*
     *Explanation
      1. We will first convert x into boolean by using double Not. (!!123 -> !0 -> 1 / !!0 -> !1 -> 0)
      2. Make a mask from the boolean by negate it and add 1 . (~x + 1 is just finding the negative of x)
      3. So, if the boolean is 0 , -0 is still 0 but if boolean is 1, -1 is 0xFFFFFFFF which is 1111 ... 1111 , all bits are set
      4. We will then use mask / inverse mask to find the answer.
      5. If mask is all bits set , then mask & y = y , ~mask & z = 0
      6. Since, the other side is definitely 0 , we can safely to use Or operator.
     */
    int boolean = !!x;
    int mask = ~boolean + 1;
    return (mask & y) | (~mask & z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    /*
     *Explanation
      1. The main idea of this question is y - x > 0 return 1, otherwise 0.
      2. However , overflow will occur if x and y have opposite sign.
      3. So, we have to separately handle the case of x and y having different sign.
      4. !(x >> 31 ^ y >> 31) to check if x and y have the same sign.
      5. (!sameSign) & (x >> 31) to return 1 when x and y have different sign and x is negative. 
         -If x and y have different sign, and x is negative, hence, x is definitely lesser than y
      6. same = sameSign & !((y+(~x+1))>>31), if same sign and y - x > 0, return 1 else 0;
     */
    int sameSign = !(x>>31 ^ y>>31);
    int diff = (!sameSign) & (x>>31);
    int same = sameSign & !((y+(~x+1))>>31); 
    return same + diff;
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
    /*
     *Explanation
      1. Using the concept of overflow to solve this problem.
      2. We first use Or operator with x and -x and right shift 31 bits.
      3. If x is non-zero, after Or operator, it will set the most significant bit.
      4. And after we carry out arithmetic right shift, all bits will set to 1, and after we +1, overflow occur and become 0.
        - 1111 ... 1111 + 1 = 0000 ... 0000
      5. If x is zero, after Or operator, and right shift, it will still 0. Adding 1 to it become 0000 0000 ... 0001
     */
    return ((x | (~x + 1) ) >> 31) + 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
    /*
     *Explanation
      1. Concept is using binary search to calculate the number of bits.
      2. We first create a mask by right shift 31 bits, so we can use the mask to invert the x.
      3. If the x is negative , then it will invert to positive while remain unchange if x is positive.
      4. How binary search done is we first right shift x by 16/8/4/2/1 and double Not it to create a boolean
        - If the upper 16 bits consists of 1, then when we double Not it, it will generate 1.
        - Conversely, if the upper 16 bits does not consist of 1 , double Not will generate 0.
        eg:  0001 0000 1000 0000 0000 1010 0000 1111 >>  16 = 0001 0000 1000 0000, double Not non-zero will generate 1
        eg:  0000 0000 0000 0000 0000 1010 0000 1111 >>  16 = 0000 0000 0000 0000, double Not zero will generate 0
      5. After getting the boolean , we will multiple it with respectively bit number.
        - << 4 is multiplication of 2 power of 4 = 16 , << 3 is multiplication of 2 power of 3 = 8 and so on
      6. We will then right shift on x depending on the result.
        - eg: If the upper N bits does not consist of 1 , then x will shift 0 which means nothing changes, and x's bit sequence 
              will continue to be use for the next search.
        - 0000 0000 0000 0000 0000 1010 0000 1111 >>  16 = 0000 0000 0000 0000 0000 0000 0000 0000
          x >> 0 = 0000 0000 0000 0000 0000 1010 0000 1111

        - 0000 0000 0000 0000 0000 1010 0000 1111 >>  8 = 0000 0000 0000 0000 0000 0000 0000 1010 bit8 = 8
          x >> 8 = 0000 0000 0000 0000 0000 0000 0000 1010 

        - 0000 0000 0000 0000 0000 0000 0000 1010 >>  4 = 0000 0000 0000 0000 0000 0000 0000 0000
          x >> 0 = 0000 0000 0000 0000 0000 0000 0000 1010 

        - 0000 0000 0000 0000 0000 0000 0000 1010 >>  2 =  0000 0000 0000 0000 0000 0000 0000 0010 bit2 = 2
          x >> 2 = 0000 0000 0000 0000 0000 0000 0000 0010 

        - 0000 0000 0000 0000 0000 0000 0000 0010 >> 1 =  0000 0000 0000 0000 0000 0000 0000 0001 bit1 = 1
          x >> 1 = 0000 0000 0000 0000 0000 0000 0000 0001 

        - bit0 = 0000 0000 0000 0000 0000 0000 0000 0001 = 1

        bit16 + bit8 + bit4  + bit2 + bit1 + bit0 +1 = 0 + 8 + 0 + 2 + 1 + 1 + 1 = 13
      7. Once done, just sum all and + 1 to it.
     */
    int bit0, bit1, bit2, bit4, bit8, bit16;
    int mask = x >> 31;
    x = (mask & ~x) | (~mask & x);

    bit16 = !!(x>>16)<<4;
    x >>= bit16;

    bit8 = !!(x>>8)<<3;
    x >>= bit8;

    bit4 = !!(x>>4)<<2;
    x >>= bit4;

    bit2 = !!(x>>2)<<1;
    x >>= bit2;

    bit1 = !!(x>>1);
    x >>= bit1;

    bit0 = x;

    return bit16 + bit8 + bit4 + bit2 + bit1 + bit0 + 1;

}


/*
 * Don't really understand the concept of floating point yet, most of the answer 
 * below is get from the internet. The explanation is very unclear as I did not 
 * fully understand and digest the concept yet.
 */


//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
    /*
     Explanation
     | 1 sign bits | 8 exponent bits | 23 fraction bits |
     - (-1)^s  *  M  * 2^E
     - s is sign bit , M is mantissa , E is exponent
     - bias = 2^(k-1) - 1 , k = number of exponent bits, normally is 8 for single precision and 11 for double precision
     For case denorm : E = 1 - bias , M = f
     For case norm : E = e - bias , M = 1 + f (e = value represented by the exponent field)
     1. First, we have to know there are 3 cases of when representing floating point, which is special, denormalize and normalize.
     2. For case special, the exponent bits are all set , so to check it, we simply shift uf >> 23 and & with 0xFF
     3. If exp == 0xFF , we just return the arguments.
     4. For case denorm, just left shift fraction bits by one
     5. For case norm , just increase exp by 1.
     */
    int exp = uf >> 23 & 0xFF;

    if(exp == 0xFF)
        return uf;
    else if (exp == 0)
        return ((uf & 0x7FFFFF) << 1) | (uf & (1 << 31));
    return uf + (1 << 23);

}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
    /*
     Explanation
     M = 1.frac
     1. If E >= 31, after 1.frac right shift 31 bits, it will excede int max range.
     2. If E < 0, 1.frac left shift by  1 bit will become 0.1 and after convert to int , it will become 0.
     3. If 0 < E < 23, right shift 23 - E 
     4. If 23 <= E < 31, left shift E - 23
     */
    int exp = (uf >> 23) & 0xFF;
    int E = exp - 127;
    int sign = (uf >> 31) & 1;
    int frac = (uf & 0x7fffff) | 1 << 23;
    int i;
    if(E > 31)
        return 0x80000000u;
    else if (E < 0)
        return 0;
    i = E < 23 ? frac>>(23-E) : frac<<(E-23);
    return sign?-i:i;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    /*
     Explanation
     1. V = (-1)^s  *  M  * 2^E
     2. When E >=255 , means all exponent bits is set, hence infinite.
     3. For denorm case, when frac = 100 0000 0000 0000 0000, V = (-1)^s * 2^-1 * 2^-126 = 2^(-1-126) = 2^-127
       - When frac = 000 0000 0000 0000 0001, V = (-1)^s  *  2^-23  * 2^-126 = 2^(-23-126) = 2^-129
       - So, the minimum number to be represented as a denorm should -149.
     4. For norm case, just right shift E 23 bits.    
     */
    int e = x + 127;
    if (e >= 255)
        return 0xFF << 23;
    else if (x < -149)
        return 0;
    else if (x < -127)
        return 1 << (149 + x);
    else
        return e << 23;
}
