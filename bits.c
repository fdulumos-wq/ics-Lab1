/* 
 * CS:APP Data Lab 
 * 
 * <卢天姿 fdulumos-wq>
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
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


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
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000) 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
// 函数即返回一个32位整数只有最高位是1，其余都是0（就是十六进制表达下的0x80000000）；
// 转化为题目要求的表达，就是二进制下的1左移31位
int signMask(void) {
  return 1 << 31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
//题目含义用~位反（全取反）and&位与（相同位为本身）实现位异或^（相同位为0）
int bitXor(int x, int y) {
  int result1 = x & y; //1的位置标记都是11，0的位置标记01、10、00
  int result2 = (~x) & (~y);//1的位置标记都是00，0的位置标记01、10、11
  int result =  (~result1) & (~result2);//取反求交集得出1的位置标记的是10，和01两者不同的情况；
	return result;
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
//实现正整数都返回0，负数都取相反数
int negativePart(int x){
  int a = x >> 31;//先确定最高符号位正负，通过右移补齐符号位能判断正负
  int b = ~x +1; //取反+1得到相反数
  return a & b;//如果x为正，a=00……0，a&b一定=0；如果x为负，a=11……1，对b而言无影响
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
//将第src字节copy到第dst位置上，且不改变其余位置的字节
int copyByteWithin(int x, int src, int dst) {
  int srcShift = src << 3;
  int dstShift = dst << 3;//先把字节编号转化为位移

  int a = (x >> srcShift) & 0xFF;//复制出变量的第src字节放到最后一位，其余位置为0
  int move = a << dstShift;//把保留下来的字节挪到对应要替换的位置，其余位置为0
  int b = 0xFF << dstShift;//把要替换的位置全变成1
  int cleared = x & ~b; // x和他的反做位与，这样其余位置都不变，要替换的位置都是0了

  return cleared | move;//两者做位或，把对应部分就拼好了
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
//其实就是向右移n位，然后前面补0；但是负数要单独处理
int logicalShift(int x, int n) {
  int a = x>>n;//先是正常右移
  int b = 1 << 31;//接下来要为负数单独构造一个能够把前面补的1变成0的步骤
  int m = ~((b >> n)<<1);//构造出与右移后补1对齐的m,然后取反（1变0，0变1）,注意不能用减号！
  return m & a;

}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
//交换数字里每个字节的前四位与最后四位
int swapNibblePairs(int x) {
  int mask = 0x0F | (0x0F << 8);//最小的单元是0x0F，要给他复制到四个字节都有的
  mask = mask | (mask << 16);//构造一个能够提取每个字节后四位的掩码

  int low = (x & mask) << 4;//提取每个字节的后四位，并且挪到高四位
  int high = (x >> 4) & mask;//把高四位挪到低四位位置上，然后提取出来高四位且保持在低四位位置上

  return low | high;//把挪好低四位的low和挪好高四位的high合并
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
//从最低位向最高位寻找第二个0所在位置对应的掩码
int secondLowestZeroBit(int x) {
  int a = ~x;//找0不太好找，但是1&1=1其余都是0就能定位对应位置了
  int b = a & (a + ~0);//因为只要第二个0，所以要去掉最后一位1,但是不能用-，所以+～0
  int result = b & (~b + 1);//因为要去掉其他的1，所以要构造相反数来去掉其他的1（前面能保证都取反，同样现在最低的1后面都是0.所以相反数能保证最低的1不变，且后面依旧是0）
  return result;
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
//如果十进制数x的二进制表达有偶数个1返回1，有奇数个1返回0；和异或是一个概念！只不过取返
int oddParity(int x) {
  int a = x ^ (x >> 16);//对半一直让自己的高低位一直异或
  int b = a ^ (a >> 8);
  int c = b ^ (b >> 4);
  int d = c ^ (c >> 2);
  int e = d ^ (d >> 1);
  int result = !(e & 1);//只用关心最后一位即可，记得取反
  return result;
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
//逻辑右移，但是需要注意有几位要绕回到前面来
int rotateRightBits(int x, int n) {
  int s = n & 31;              // 得到实际右移位数
  int t = (~s + 1) & 31;       // 得到绕回部分需要左移的位数
  int a = x >> s;              // 先执行普通右移，此时负数左侧可能补 1
  int b = 1 << 31;             // 构造只有最高位为 1 的数
  int m = ~((b >> s) << 1);    // 构造最高 s 位为 0、其他位为 1 的掩码
  int right = a & m;           // 清除普通右移补出来的 1，得到逻辑右移部分
  int left = x << t;           // 把被右移挤出的低 s 位移动到最高位
  return right | left;         // 将右移部分和绕回部分拼起来
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
//算出x附近最近的2的n次幂的倍数，如果处于中点的话，/2n下方商为偶数不进位，商为奇数进位
int roundEvenPow2(int x, int n) {
  int a = 1 << n;//先确定2的n次幂是谁
  int mask = a + ~0;//标记最低n位
  int half = a >> 1;//确定中点
  int p = (x >> n) & 1;//取商的最低位，判断商的奇偶性
  int bias = half + ~0 + p;//看看商是偶数还是奇数，判断是否进位
  return (x + bias) & ~mask;//清除其余最低n位，得到真正要的倍数
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
//求两个数的平均数，然后如果不整除的话，就选靠近前面的数进行进位
int midpointTowardFirst(int x, int y) {
  int d = x ^ y; // 记录x和y中不同的位
  int mid = (x & y) + (d >> 1);  // 求平均向下取整
  int half = d & 1;// 奇偶不同表示平均是小数

  int sx = x >> 31; // x非负时为0，负数时为全1
  int sy = y >> 31; // y非负时为0，负数时为全1
  int sign = sx ^ sy; // 异号时为全1，同号时为0

  int diff = y + (~x + 1); // 计算y-x
  int diffSign = diff >> 31;// 判断y与x大小

  int Diff = sign & ~sx; // 异号时：自动判断大小
  int Same = ~sign & diffSign;// 同号时结合diffsign判断大小                                
  int res = Diff | Same; // 合并两个分支                              
  int add = half & res;  // 决定是否需要修正，半整数且x>y时加1，否则加0

  return mid + add;
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
//如果x是落在a到b范围区间内部（包含端点），则返回1
int isBetweenEitherOrder(int x, int a, int b) {
  int sa = a >> 31; // a非负为0，负数为全1
  int sb = b >> 31;  // b非负为0，负数为全1
  int s = sa ^ sb;  // a、b异号为全1，同号为0

  int diff = a + (~b + 1); // 计算a-b
  int ds = diff >> 31; //判断大小
  int order = (s & sa) | (~s & ds); 

  int reverse = ~order; // 与order相反的选择掩码
  int low = (a & order) | (b & reverse);// 取a、b中较小的数
  int high = (b & order) | (a & reverse);// 取a、b中较大的数

  int sx = x >> 31; // x的符号
  int sl = low >> 31;// low的符号
  int sh = high >> 31;// high的符号
  int diffxl = x + (~low + 1); // 计算x-low
  int dxls = diffxl >> 31;// 同号时，x-low为负说明x<low
  int slx = sl ^ sx;// low和x是否异号
  int left = (slx & sl) | (~slx & ~dxls); // low<=x时为全1，否则为0

  int diffhx = high + (~x + 1); // 计算high-x
  int dhxs = diffhx >> 31;// 同号时，high-x为负说明high<x
  int sxh = sx ^ sh;// x和high是否异号
  int right = (sxh & sx) | (~sxh & ~dhxs);// x<=high时为全1，否则为0

  return !!(left & right); // 两边都满足则返回1，否则返回0
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
//返回5x，如果正溢出要返回对应的max，负数溢出返回min
int mul5Sat(int x) {
  int limit = (0x19 << 24) | (0x99 << 16);
  limit = limit | (0x99 << 8) | 0x99;//先判断x对应的上下界（也就是5x就到临界了）

  int sign = x >> 31;//判断x的符号
  int magnitude = (x ^ sign) + (sign & 1);

  int diff = limit + (~magnitude + 1);//计算x是否会溢出
  int overflow = diff >> 31;

  int result = (x << 2) + x;//正常计算五倍

  int tmin = 1 << 31;//下限
  int tmax = ~tmin;//上限
  int sat = (sign & tmin) | (~sign & tmax);//根据符号选择对应的上下限

  return (overflow & sat) | (~overflow & result);
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
//算出x+y+z的总和，如果正数溢出返回1，负数溢出返回-1，其他情况都是0
//主要是要考虑中间加法过程会溢出，但是最后总和正负抵消不溢出的情况
//因为都是int定义，所以本身都不会溢出，那么溢出
int classifyAdd3(int x, int y, int z) {
  int sum1 = x + y;
  int sx = x >> 31;
  int sy = y >> 31;
  int ss1 = sum1 >> 31;//先看x+y是否产生溢出，标记符号

  int pos1 = ~sx & ~sy & ss1;//正溢出
  int neg1 = sx & sy & ~ss1;//负溢出
  int over1 = (pos1 & 1) | neg1;//// 正溢出记为1，负溢出记为-1，无溢出记为0

  int sum2 = sum1 + z;
  int sz = z >> 31;
  int ss2 = sum2 >> 31;//再加上z

  int pos2 = ~ss1 & ~sz & ss2;//如果sum1和z同号，但是结果异号，那就是溢出了
  int neg2 = ss1 & sz & ~ss2;
  int over2 = (pos2 & 1) | neg2;//判断是否溢出

  int overflow = over1 + over2;//两次溢出的方向相加，正负溢出可以互相抵消
  return (overflow >> 31) | (!!overflow);//// over<0返回-1，over>0返回1，over=0返回0
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
//输入uf单精度浮点数，计算乘以 3/2 后，按照单精度规则得到的编码
unsigned floatScaleThreeHalves(unsigned uf) {
  unsigned sign = uf & 0x80000000;//取出符号位
  unsigned exp = (uf >> 23) & 0xFF;//取出8位阶码
  unsigned frac = uf & 0x7FFFFF;//取出23位尾数

  unsigned product;
  unsigned round;
  unsigned shift;
  unsigned remainder;
  unsigned half;

  if (exp == 0xFF) {//NaN或者无穷，直接返回原来的位模式
    return uf;
  }

  if (exp == 0) {//处理0和非规格化数，此时没有隐藏的最高位1
    product = frac * 3;//尾数先乘3
    round = product >> 1;//再除以2

    if ((product & 1) && (round & 1)) {//正好在中点且当前结果为奇数
      round = round + 1;//向上舍入，使最终结果为偶数
    }

    return sign | round;//保留符号位，也能保留+0和-0
  }

  product = (frac | 0x800000) * 3;//规格化数补上隐藏位1，再乘3

  shift = 1 + (product >= 0x2000000);//正常除以2，过大时除以4
  exp = exp + shift - 1;//除以4时需要将阶码增加1

  round = product >> shift;//得到舍入前的有效数字
  remainder = product & ((1 << shift) - 1);//取出除法丢弃的低位
  half = 1 << (shift - 1);//得到舍入中点

  if (remainder > half ||
      (remainder == half && (round & 1))) {//超过中点，或中点时结果为奇数
    round = round + 1;//执行最近偶数舍入
  }

  if (round >= 0x1000000) {//舍入后有效数字产生进位
    round = round >> 1;//重新规格化有效数字
    exp = exp + 1;//阶码相应增加1
  }

  if (exp >= 0xFF) {//结果超过最大有限浮点数
    return sign | 0x7F800000;//根据原符号返回正无穷或负无穷
  }

  return sign | (exp << 23) | (round & 0x7FFFFF);//重新拼接符号、阶码和尾数
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
//把浮点数表示成离着最近的整数，并仍以浮点数位级形式返回，如果恰好是一半那就返回偶数。如果NaN或无限不变。
unsigned floatRoundEven(unsigned uf) {
  unsigned sign = uf & 0x80000000;//取出符号位
  unsigned exp = (uf >> 23) & 0xFF;//取出8位阶码
  unsigned frac = uf & 0x7FFFFF;//取出23位尾数

  unsigned shift;
  unsigned significand;
  unsigned mask;
  unsigned remainder;
  unsigned halfway;
  unsigned integer;
  unsigned rounded;

  if (exp == 0xFF) {//NaN或无穷，直接返回原来的位模式
    return uf;
  }

  if (exp < 0x7E) {//绝对值小于0.5，舍入为带原符号的0
    return sign;
  }

  if (exp == 0x7E) {//绝对值位于0.5到1之间
    if (frac == 0) {//正好是0.5，中点取偶，选择0
      return sign;
    }

    return sign | 0x3F800000;//大于0.5，舍入为正负1.0
  }

  if (exp >= 0x96) {//指数不小于23，已经没有小数位
    return uf;
  }

  significand = frac | 0x800000;//补上规格化数隐藏的最高位1
  shift = 0x96 - exp;//计算尾数中有多少位属于小数部分

  mask = (1 << shift) - 1;//构造小数部分的掩码
  remainder = significand & mask;//取出要舍弃的小数部分
  halfway = 1 << (shift - 1);//得到舍入中点
  integer = significand >> shift;//得到舍入前的整数部分
  rounded = significand & ~mask;//先直接清除全部小数位

  if (remainder > halfway ||
      (remainder == halfway && (integer & 1))) {//超过中点，或中点时整数为奇数
    rounded = rounded + (1 << shift);//向上舍入，使中点结果为偶数
  }

  if (rounded >= 0x1000000) {//舍入导致有效数字进位
    rounded = rounded >> 1;//重新规格化
    exp = exp + 1;//阶码增加1
  }

  return sign | (exp << 23) | (rounded & 0x7FFFFF);//重新拼接浮点位模式
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
//将整数x转换成单精度浮点数，并返回浮点数的位级表示。
unsigned float_i2f(int x) {
  unsigned sign = 0;//保存符号位
  unsigned mag = x;//保存x的绝对值
  unsigned exp;
  unsigned mant;
  unsigned shift;
  unsigned mask;
  unsigned rem;
  unsigned half;

  int pos = 31;//最高有效位的位置

  if (x == 0) {//0直接转换为浮点0
    return 0;
  }

  if (x < 0) {//负数保存符号，并求绝对值
    sign = 0x80000000;
    mag = ~mag + 1;
  }

  while (((mag >> pos) & 1) == 0) {//寻找最高有效位
    pos = pos - 1;
  }

  exp = pos + 127;//计算浮点数的阶码

  if (pos <= 23) {//有效位不超过24位，不需要舍入
    mant = mag << (23 - pos);//将最高有效位移动到隐藏位位置

    return sign | (exp << 23) | (mant & 0x7FFFFF);//去掉隐藏位并拼接结果
  }

  shift = pos - 23;//计算需要舍弃的位数
  mant = mag >> shift;//保留最高24个有效位

  mask = (1 << shift) - 1;//构造低位掩码
  rem = mag & mask;//取出被舍弃的低位
  half = 1 << (shift - 1);//得到舍入中点

  if (rem > half ||
      (rem == half && (mant & 1))) {//执行最近偶数舍入
    mant = mant + 1;
  }

  if (mant >= 0x1000000) {//舍入后发生进位
    mant = mant >> 1;
    exp = exp + 1;
  }

  return sign | (exp << 23) | (mant & 0x7FFFFF);//拼接符号、阶码和尾数
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
// 计算一下x的二级制表达有多少个1
//原本可以遍历32个位并逐个相加，但整数题不能使用循环
//所以将所有位分组，并行统计每组中1的数量
int bitCount(int x) {
  int mask1 = 0x55 | (0x55 << 8);//构造01010101重复的掩码
  int mask2 = 0x33 | (0x33 << 8);//构造00110011重复的掩码
  int mask4 = 0x0F | (0x0F << 8);//构造00001111重复的掩码
  int mask8 = 0xFF | (0xFF << 16);//保留每16位中的低8位

  mask1 = mask1 | (mask1 << 16);
  mask2 = mask2 | (mask2 << 16);
  mask4 = mask4 | (mask4 << 16);

  x = (x & mask1) + ((x >> 1) & mask1);//每2位中分别有几个1
  x = (x & mask2) + ((x >> 2) & mask2);//每4位中分别有几个1
  x = (x & mask4) + ((x >> 4) & mask4);//每8位中分别有几个1
  x = (x & mask8) + ((x >> 8) & mask8);//每16位中分别有几个1
  x = (x & 0xFF) + ((x >> 16) & 0xFF);//合并两个16位的结果

  return x;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
//反转x内部每一位32字节表示（类似于倒叙，颠倒排序）
int bitReverse(int x) {
  int mask16 = (0xFF << 8) | 0xFF;//构造低16位为1的掩码
  int mask8 = mask16 ^ (mask16 << 8);//构造每组低8位为1的掩码
  int mask4 = mask8 ^ (mask8 << 4);//构造每组低4位为1的掩码
  int mask2 = mask4 ^ (mask4 << 2);//构造每组低2位为1的掩码
  int mask1 = mask2 ^ (mask2 << 1);//构造每组低1位为1的掩码

  x = ((x >> 1) & mask1) | ((x & mask1) << 1);//交换相邻的1位
  x = ((x >> 2) & mask2) | ((x & mask2) << 2);//交换相邻的2位
  x = ((x >> 4) & mask4) | ((x & mask4) << 4);//交换相邻的4位
  x = ((x >> 8) & mask8) | ((x & mask8) << 8);//交换相邻的8位
  x = ((x >> 16) & mask16) | (x << 16);//交换高低16位

  return x;
}