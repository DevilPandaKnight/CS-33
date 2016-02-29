//A. this is not true since x can be 0x10000000 which is TMin, and the negative of this number is the same.
//so it will not hold for x<y == (-x>-y) because y can be number like 1

//B. this is true since 2's complement can do addition and multiplication in any order.

//C. true since the bit pattern will be the same.

//D. true since unsigned and signed will have same bit pattern

//E. true since right shift may kill the bit at right and left shift back will result that bit to be 0
//so after shifting the number will <= x