//
// Created by samir on 12/8/2022.
//

#ifndef C_SOLVE_BIT_MATH_H
#define C_SOLVE_BIT_MATH_H
//set the given bit i n a register
#define SET_BIT(REG,Bit_NO)     (REG) |= (1<<(Bit_NO))


#define BIT_BAND(addr,bitnum) ((addr&0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2))
#define MEM_ADDR(addr) *((volatile unsigned long *) (addr))


//clear a given bit in a register
#define CLR_BIT(REG,Bit_NO)		(REG) &=~(1<<Bit_NO)

//toggle a given bit i na register
#define TGL_BIT(REG,Bit_NO)		(REG)^=(1<<Bit_NO)

// Get The Bit number Bit_NO
#define GET_BIT(REG,Bit_NO)		((REG >> Bit_NO) & ((u32)0x1))

//Sets the high nipple in a register
#define SET_H_NIB(REG)			(REG) |=(0XF0)

// Clear The High Nibble in a Register
#define CLR_H_NIB(REG)			(REG)&=(0X0F)

// Get The hIGH Nibble in a Register
#define GET_H_NIB(REG)			(((REG) >> 4) & 0x0F)

//Toggle the high nibble in a register
#define TGL_H_NIB(REG)			(REG)^=(0X0F)

// Set The Low Nibble in a Register
#define SET_L_NIB(REG)			(REG) |=(0XF0)

// Clear The Low Nibble in a Register
#define CLR_L_NIB(REG)			(REG)&=(0XF0)

// Get The Low Nibble in a Register
#define GET_L_NIB(REG)			((((REG) << 4) & 0xF0)>>4)

// Assign a Value to a Register
#define ASSIGN_REG(REG,VALUE) 	(REG = VALUE)

// Assign The High Nibble in a Register
#define ASSIGN_H_NIB(REG,VALUE)	REG=(((REG)& 0x0F)|VALUE << 4 )

// Assign the Low Nibble in a Register
#define ASSIGN_L_NIB(REG,VALUE)	(((REG >> 4)<<4)|VALUE)

// Right Shift by No
#define RSHFT_REG(REG,NO)		(REG >> NO)

// Left Shift by NO
#define LSHFT_REG(REG,NO)		(REG << NO)

// Circular Right Shift
#define CRSHFT_REG(REG,NO)      (REG >> NO) | (REG << sizeof(REG) * CHAR_BIT - NO)

// Circular Left Shift
#define CLSHFT_REG(REG,NO)		(REG << NO) | (REG >> sizeof(REG) * CHAR_BIT - NO)



#endif //C_SOLVE_BIT_MATH_H
