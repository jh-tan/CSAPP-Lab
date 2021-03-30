# Personal notes / Understanding

This lab is required to implement simple logical, two's complement, and floating point functions, but using only bitwise operation and limited number of operations. The notes below is just my personal notes, the answer can get it from datalab/bits.c 

# Instruction
 1. ' ./make clean ' everytime after finish edit
 2. ' ./make ' to rebuild the file.
 3. ' ./dlc bits.c' to check the syntax of the soluion.
 4. ' ./driver.pl '  or './btest bits.c' to evaluate and grade the solution.

## 1. bitXor
1. There are many ways to solve this, my soluion is by using the NOR (~x & ~y)
 2. We will first x And y and x Nor y 
 3. Then, we Nor the 2 result and get the answer.
      Demo:
     - x = 0101  y = 0011  x XOR y = 0110
          let a = x And y = 0001
          let b = x Nor y = 1000
          - We can slightly see the pattern here already:
            XOR: 0110   a: 0001  b: 1000
          - We just need to make the middle part become 1
          - ~a = 1110  ~b = 0111
          
           1110
           0111 &
	       -------
           0110


## 2. Tmin
  1. Tmin = 1000 0000 ... 0000
  2. Simply left shift 1 with 31, then we can generate the pattern


## 3. isTmax

 1. Tmax = 0111 1111 ... 1111, we can just negate Tmin to compare, but shifting is forbid in here.
 2. So, how we done here is by +1 to the x, +x, and negate it.
 3. Why? Is because if x is Tmax, x + 1 will become Tmin, and Tmin + Tmax = -1 (1111 1111 ... 1111), and negate it will become 0.
 4. Not ops ( ! ) the result, we can then generate the answer. BUT, if x is -1, it will have the exact output also.
 
		  1111 1111 ... 1111 + 1 -> 0000 .... 0000 + x 
		  -> 1111 ... 1111 , negate -> 0000 ... 0000
   5. So, we need to handle the case by using xor operation.
   6. We + 1 to x , and NOT it. If x is -1, +1 will become 0, !0 = 1
        POSSIBLE CASES:
        a. x = -1 ,   1 ^ 1 = 0
        b. x = Tmax , 1 ^ 0 = 1
        c. x = other random number , 1 ^ 1 = 0


## 4. allOddBits

 1. Allodd = 1010 1010 1010 1010 1010 1010 1010 1010 
 2. We cannot use big constant, so we created it by ourself

>       1010 1010 0000 0000 0000 0000 0000 0000 + (0xAA << 24 )
>       0000 0000 1010 1010 0000 0000 0000 0000 + (0xAA << 16 )
>       0000 0000 0000 0000 1010 1010 0000 0000 + (0xAA << 8  )
>       0000 0000 0000 0000 0000 0000 1010 1010 + 0xAA
>       -------------------------------------------------------
>       1010 1010 1010 1010 1010 1010 1010 1010
 3. odd & x to generate a 'version' that is only consists of odd bits.
         - let x = 1100 0000 1010 1010
         - let odd = 1010 1010 1010 1010 1010 1010 1010 1010
           1010 1010 1010 1010 1010 1010 1010 1010
           0000 0000 0000 0000 1100 0000 1010 1010 &
           ----------------------------------------------------------
           0000 0000 0000 0000 1000 0000 1010 1010

## 5. Negate

1. For two - complement integer , -x === ~x + 1


## 6. isAsciiDigit

>   0x3 = 0011 , 9 = 0x1001
1. First, split the x into two parts to compare, namely left and right.
2. Left will use to handle to check if it is 0x3
3. Right side will be use to check if the number is within 9. How it done is just by checking if the certain bit is set.
4. 0000 , if the msb is set, and also second bit / third bit is set, then it will exceed 9 and it is invalid.
> POSSIBLE CASES: 
> **1000** - Valid (msb is set, but second or third bit is not set) 
> **0110** - Valid(msb is not set , and the rest of the bits are set) 
> **0000** - Valid (all bits are not set) 
> **1100** - Invalid (msb and second/third bit are both set)

5. So, we found that the pattern is, it is invalid only if both msb and second/third bits are set.
6. xor does not work here as 0 ^ 0 = 0 , but we wanted it to be 1.
7. What we do is, !(x&!!y)

	>   x = 1 , y = 0, !(1&!!0) = !(1&0) = 1
	>   x = 0 , y = 1, !(0&!!1) = !(0&0) = 1    
	>   x = 0 , y = 0, !(0&!!0) = !(0&0) = 1    
	>   x = 0 , y = 0, !(1&!!1) = !(1&1) = 0

8. Lastly, simply left & right


## 7. Conditional

1. We will first convert x into boolean by using double Not. 
(!!123 -> !0 -> 1 / !!0 -> !1 -> 0)
2. Make a mask from the boolean by negate it and add 1 . (~x + 1 is just finding the negative of x)
3. So, if the boolean is 0 , -0 is still 0 but if boolean is 1, -1 is 0xFFFFFFFF which is 1111 ... 1111 , all bits are set
4. We will then use mask / inverse mask to find the answer.
5. If mask is all bits set , then mask & y = y , ~mask & z = 0
6. Since, the other side is definitely 0 , we can safely to use Or operator.


## 8. isLessOrEqual

   1. The main idea of this question is y - x > 0 return 1, otherwise 0.
   2. However , overflow will occur if x and y have opposite sign.
   3. So, we have to separately handle the case of x and y having different sign.
   4. !(x >> 31 ^ y >> 31) to check if x and y have the same sign.
   5. (!sameSign) & (x >> 31) to return 1 when x and y have different sign and x 				is negative.    
>  If x and y have different sign, and x is negative, hence, x is definitely lesser 	   than y

   6. same = sameSign & !((y+(~x+1))>>31), if same sign and y - x > 0, return 1 else 0;


## 9. logicalNeg
 1. Using the concept of overflow to solve this problem.
 2. We first use Or operator with x and -x and right shift 31 bits.
 3. If x is non-zero, after Or operator, it will set the most significant bit.
 4. And after we carry out arithmetic right shift, all bits will set to 1, and after 	 we +1, overflow occur and become 0.
   > 1111 ... 1111 + 1 = 0000 ... 0000
 5. If x is zero, after Or operator, and right shift, it will still 0. Adding 1 to it become 0000 0000 ... 0001



## 10. howManyBits
1. Concept is using binary search to calculate the number of bits.
2. We first create a mask by right shift 31 bits, so we can use the mask to invert the x.
3. If the x is negative , then it will invert to positive while remain unchange if x is positive.
4. How binary search done is we first right shift x by 16/8/4/2/1 and double Not it to create a boolean

	> If the upper 16 bits consists of 1, then when we double Not it, it will generate 1. 
	> 
	> Conversely, if the upper 16 bits does not consist of 1 , double Not will generate 0. 
	> 
	> eg:  0001 0000 1000 0000 0000 1010 0000 1111 >>  16 = 
	 0001 0000 1000 0000, double Not non-zero will generate 1 
	 >
	> eg:  0000 0000 0000 0000 0000 1010 0000 1111 >>  16 = 
	 0000 0000 0000 0000, double Not zero will generate 0

5. After getting the boolean , we will multiple it with respectively bit number.
  

>   << 4 is multiplication of 2 power of 4 = 16 , << 3 is multiplication
> of 2 power of 3 = 8 and so on

6. We will then right shift on x depending on the result.
- eg: If the upper N bits does not consist of 1 , then x will shift 0 which means nothing changes, and x's bit sequence will continue to be use for the next search.
**DEMO**

> 0000 0000 0000 0000 0000 1010 0000 1111 >>  16 
 = 0000 0000 0000 0000 0000 0000 0000 0000

- x >> 0 = 0000 0000 0000 0000 0000 1010 0000 1111

> 0000 0000 0000 0000 0000 1010 0000 1111 >>  8 
> = 0000 0000 0000 0000 0000 0000 0000 1010 ( bit8 = 8 )

- x >> 8 = 0000 0000 0000 0000 0000 0000 0000 1010 

> 0000 0000 0000 0000 0000 0000 0000 1010 >>  4 
> = 0000 0000 0000 0000 0000 0000 0000 0000

- x >> 0 = 0000 0000 0000 0000 0000 0000 0000 1010 

> 0000 0000 0000 0000 0000 0000 0000 1010 >>  2 
> =  0000 0000 0000 0000 0000 0000 0000 0010 ( bit2 = 2 )

- x >> 2 = 0000 0000 0000 0000 0000 0000 0000 0010 

> 0000 0000 0000 0000 0000 0000 0000 0010 >> 1 
> = 0000 0000 0000 0000 0000 0000 0000 0001 ( bit1 = 1 )

- x >> 1 = 0000 0000 0000 0000 0000 0000 0000 0001 

bit0 = 0000 0000 0000 0000 0000 0000 0000 0001 = 1

7. Once done, just sum all and + 1 to it.

> bit16 + bit8 + bit4  + bit2 + bit1 + bit0 +1 = 0 + 8 + 0 + 2 + 1 + 1 + 1 = 13

---
>For the floating point's part, I don't really quite understand the concept yet, hence most of the answer below is refer from the internet. My explaination is very unclear as I did not fully udnerstand and digest the concept yet.

# 11. floatScale2
> | 1 sign bits | 8 exponent bits | 23 fraction bits |
   (-1)^s  *  M  * 2^E
   >
>   s is sign bit , M is mantissa , E is exponent
>   
>   bias = 2^(k-1) - 1 , k = number of exponent bits, normally is 8 for single precision and 11 for double precision
>   
>  For case denorm : E = 1 - bias , M = f
>  
>  For case norm : E = e - bias , M = 1 + f (e = value represented by the exponent field)
   
   1. First, we have to know there are 3 cases of when representing floating point, which is special, denormalize and normalize.
   2. For case special, the exponent bits are all set , so to check it, we simply shift uf >> 23 and & with 0xFF
   3. If exp == 0xFF , we just return the arguments.
   4. For case denorm, just left shift fraction bits by one
   5. For case norm , just increase exp by 1.


## 12. floatFloat2Int
	M = 1.frac
1. If E >= 31, after 1.frac right shift 31 bits, it will excede int max range.
2. If E < 0, 1.frac left shift by  1 bit will become 0.1 and after convert to int , it will become 0.
3. If 0 < E < 23, right shift 23 - E 
4. If 23 <= E < 31, left shift E - 23

## 13.floatPower2

1. V = (-1)^s  *  M  * 2^E
2. When E >=255 , means all exponent bits is set, hence infinite.
3. For denorm case, when frac = 100 0000 0000 0000 0000, 
V = (-1)^s * 2^-1 * 2^-126 = 2^(-1-126) = 2^-127
   - When frac = 000 0000 0000 0000 0001,
   -  V = (-1)^s  *  2^-23  * 2^-126 = 2^(-23-126) = 2^-129
   - So, the minimum number to be represented as a denorm should -149.
 4. For norm case, just right shift E 23 bits.  
