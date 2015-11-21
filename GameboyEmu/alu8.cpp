#include "cpu.h"

/*=================================================
8-BIT ARITHMETIC LOGIC UNIT
=================================================*/


/* ADD A,n
Adds 8-bit value n onto the accumulator.
*/
inline void CPU::ADD_A_r2(unsigned char r2)
{
    A += r2;
    F = (A ? 0 : ZERO_FLAG) | ((A & 0x0F) < (r2 & 0x0F) ? HALF_CARRY_FLAG : 0) | ((A < r2) ? CARRY_FLAG : 0);
    lastStepClk = 1;
}
#pragma region ADD_A Implementations
void CPU::ADD_A_A()
{
    ADD_A_r2(A);
}

void CPU::ADD_A_B()
{
    ADD_A_r2(B);
}

void CPU::ADD_A_C()
{
    ADD_A_r2(C);
}

void CPU::ADD_A_D()
{
    ADD_A_r2(D);
}

void CPU::ADD_A_E()
{
    ADD_A_r2(E);
}

void CPU::ADD_A_H()
{
    ADD_A_r2(H);
}

void CPU::ADD_A_L()
{
    ADD_A_r2(L);
}

void CPU::ADD_A_pHL()
{
    unsigned char r2 = mem->read8(HL);
    A += r2;
    F = (A ? 0 : ZERO_FLAG) | ((A & 0x0F) < (r2 & 0x0F) ? HALF_CARRY_FLAG : 0) | ((A < r2) ? CARRY_FLAG : 0);
    lastStepClk = 2;
}

void CPU::ADD_A_n()
{
    unsigned char r2 = mem->read8(PC++);
    A += r2;
    F = (A ? 0 : ZERO_FLAG) | ((A & 0x0F) < (r2 & 0x0F) ? HALF_CARRY_FLAG : 0) | ((A < r2) ? CARRY_FLAG : 0);
    lastStepClk = 2;
}
#pragma endregion Adding values onto the accumulator.



/* ADC A,n
Adds 8-bit value n + carry flag value to the accumulator.
*/
inline void CPU::ADC_A_r2(unsigned char r2)
{
    A += r2 + ((F & CARRY_FLAG) >> 4);
    F = (A ? 0 : ZERO_FLAG)
        | ((A & 0x0F) < r2 + (F & CARRY_FLAG & 0x0F) ? HALF_CARRY_FLAG : 0)
        | ((A < r2 + (F & CARRY_FLAG)) ? CARRY_FLAG : 0);
    lastStepClk = 1;
}
#pragma region ADC_A_r2(r2) Implementations
void CPU::ADC_A_A()
{
    ADC_A_r2(A);
}

void CPU::ADC_A_B()
{
    ADC_A_r2(B);
}

void CPU::ADC_A_C()
{
    ADC_A_r2(C);
}

void CPU::ADC_A_D()
{
    ADC_A_r2(D);
}

void CPU::ADC_A_E()
{
    ADC_A_r2(E);
}

void CPU::ADC_A_H()
{
    ADC_A_r2(H);
}

void CPU::ADC_A_L()
{
    ADC_A_r2(L);
}

void CPU::ADC_A_pHL()
{
    unsigned char r2 = mem->read8(HL);
    A += r2 + ((F & CARRY_FLAG) >> 4);
    F = (A ? 0 : ZERO_FLAG)
        | ((A & 0x0F) < r2 + (F & CARRY_FLAG & 0x0F) ? HALF_CARRY_FLAG : 0)
        | ((A < r2 + (F & CARRY_FLAG)) ? CARRY_FLAG : 0);
    lastStepClk = 2;
}

void CPU::ADC_A_n()
{
    unsigned char r2 = mem->read8(PC++);
    A += r2 + ((F & CARRY_FLAG) >> 4);
    F = (A ? 0 : ZERO_FLAG)
        | ((A & 0x0F) < r2 + (F & CARRY_FLAG & 0x0F) ? HALF_CARRY_FLAG : 0)
        | ((A < r2 + (F & CARRY_FLAG)) ? CARRY_FLAG : 0);
    lastStepClk = 2;
}
#pragma endregion Adds value plus carry flag to accumulator.



/* SUB A,n
Subtracts 8-bit value n from the accumulator.
*/
inline void CPU::SUB_A_r2(unsigned char r2)
{
    F = (A - r2 ? 0 : ZERO_FLAG)
        | SUBTRACT_FLAG
        | ((A & 0x0F) > (r2 & 0x0F) ? HALF_CARRY_FLAG : 0)
        | ((A > r2) ? CARRY_FLAG : 0);
    A -= r2;
    lastStepClk = 1;
}
#pragma region SUB_A_r2(r2) Implementations
void CPU::SUB_A_A()
{
    SUB_A_r2(A);
}

void CPU::SUB_A_B()
{
    SUB_A_r2(B);
}

void CPU::SUB_A_C()
{
    SUB_A_r2(C);
}

void CPU::SUB_A_D()
{
    SUB_A_r2(D);
}

void CPU::SUB_A_E()
{
    SUB_A_r2(E);
}

void CPU::SUB_A_H()
{
    SUB_A_r2(H);
}

void CPU::SUB_A_L()
{
    SUB_A_r2(L);
}

void CPU::SUB_A_pHL()
{
    unsigned char r2 = mem->read8(HL);
    F = (A - r2 ? 0 : ZERO_FLAG)
        | SUBTRACT_FLAG
        | ((A & 0x0F) > (r2 & 0x0F) ? HALF_CARRY_FLAG : 0)
        | ((A > r2) ? CARRY_FLAG : 0);
    A -= r2;
    lastStepClk = 2;
}

void CPU::SUB_A_n()
{
    unsigned char r2 = mem->read8(PC++);
    F = (A - r2 ? 0 : ZERO_FLAG)
        | SUBTRACT_FLAG
        | ((A & 0x0F) > (r2 & 0x0F) ? HALF_CARRY_FLAG : 0)
        | ((A > r2) ? CARRY_FLAG : 0);
    A -= r2;
    lastStepClk = 2;
}
#pragma endregion Subtracts a value from the accumulator.



/* SBC A, n
Subtracts 8-bit value plus carry flag from the accumulator.
*/
inline void CPU::SBC_A_r2(unsigned char r2)
{
    r2 = r2 + ((F & CARRY_FLAG) >> 4);
    F = (A - r2 ? 0 : ZERO_FLAG)
        | SUBTRACT_FLAG
        | ((A & 0x0F) > (r2 & 0x0F) ? HALF_CARRY_FLAG : 0)
        | ((A > r2) ? CARRY_FLAG : 0);
    A -= r2;
    lastStepClk = 1;
}
#pragma region SBC A,n implementations
void CPU::SBC_A_A()
{
    SBC_A_r2(A);
}

void CPU::SBC_A_B()
{
    SBC_A_r2(B);
}

void CPU::SBC_A_C()
{
    SBC_A_r2(C);
}

void CPU::SBC_A_D()
{
    SBC_A_r2(D);
}

void CPU::SBC_A_E()
{
    SBC_A_r2(E);
}

void CPU::SBC_A_H()
{
    SBC_A_r2(H);
}

void CPU::SBC_A_pHL()
{
    unsigned char r2 = mem->read8(HL);
    F = (A - r2 ? 0 : ZERO_FLAG)
        | SUBTRACT_FLAG
        | ((A & 0x0F) > (r2 & 0x0F) ? HALF_CARRY_FLAG : 0)
        | ((A > r2) ? CARRY_FLAG : 0);
    A -= r2;
    lastStepClk = 2;
}
//This doesn't seem to have an opcode? Is it actually supported by the gameboy?
void CPU::SBC_A_n()
{
    unsigned char r2 = mem->read8(PC++);
    F = (A - r2 ? 0 : ZERO_FLAG)
        | SUBTRACT_FLAG
        | ((A & 0x0F) > (r2 & 0x0F) ? HALF_CARRY_FLAG : 0)
        | ((A > r2) ? CARRY_FLAG : 0);
    A -= r2;
    lastStepClk = 2;
}
#pragma endregion 



/* AND n
Logically AND 8-bit value with accumulator and store result in accumulator.
*/
inline void CPU::AND_r2(unsigned char r2)
{
    A = A & r2;
    F = (A ? 0 : ZERO_FLAG) | HALF_CARRY_FLAG;
    lastStepClk = 1;
}
#pragma region AND implementations
void CPU::AND_A()
{
    AND_r2(A);
}

void CPU::AND_B()
{
    AND_r2(B);
}

void CPU::AND_C()
{
    AND_r2(C);
}

void CPU::AND_D()
{
    AND_r2(D);
}

void CPU::AND_E()
{
    AND_r2(E);
}

void CPU::AND_H()
{
    AND_r2(H);
}

void CPU::AND_L()
{
    AND_r2(L);
}

void CPU::AND_pHL()
{
    A = A & mem->read8(HL);
    F = (A ? 0 : ZERO_FLAG) | HALF_CARRY_FLAG;
    lastStepClk = 2;
}

void CPU::AND_n()
{
    A = A & mem->read8(PC++);
    F = (A ? 0 : ZERO_FLAG) | HALF_CARRY_FLAG;
    lastStepClk = 2;
}
#pragma endregion Logically AND 8-bit value with accumulator.



/* OR n
Logically OR 8-bit value with accumulator and store result in accumulator.
*/
inline void CPU::OR_r2(unsigned char r2)
{
    A = A | r2;
    F = (A ? 0 : ZERO_FLAG);
    lastStepClk = 1;
}
#pragma region OR implementations
void CPU::OR_A()
{
    OR_r2(A);
}

void CPU::OR_B()
{
    OR_r2(B);
}

void CPU::OR_C()
{
    OR_r2(C);
}

void CPU::OR_D()
{
    OR_r2(D);
}

void CPU::OR_E()
{
    OR_r2(E);
}

void CPU::OR_H()
{
    OR_r2(H);
}

void CPU::OR_L()
{
    OR_r2(L);
}

void CPU::OR_pHL()
{
    A = A | mem->read8(HL);
    F = (A ? 0 : ZERO_FLAG);
    lastStepClk = 2;
}

void CPU::OR_n()
{
    A = A | mem->read8(PC++);
    F = (A ? 0 : ZERO_FLAG);
    lastStepClk = 2;
}
#pragma endregion Logically OR 8-bit value with accumulator.



/* XOR n
Logically XOR 8-bit value with accumulator and store result in accumulator.
*/
inline void CPU::XOR_r2(unsigned char r2)
{
    A = A ^ r2;
    F = (A ? 0 : ZERO_FLAG);
    lastStepClk = 1;
}
#pragma region XOR implementations
void CPU::XOR_A()
{
    XOR_r2(A);
}

void CPU::XOR_B()
{
    XOR_r2(B);
}

void CPU::XOR_C()
{
    XOR_r2(C);
}

void CPU::XOR_D()
{
    XOR_r2(D);
}

void CPU::XOR_E()
{
    XOR_r2(E);
}

void CPU::XOR_H()
{
    XOR_r2(H);
}

void CPU::XOR_L()
{
    XOR_r2(L);
}

void CPU::XOR_pHL()
{
    A = A ^ mem->read8(HL);
    F = (A ? 0 : ZERO_FLAG);
    lastStepClk = 2;
}

void CPU::XOR_n()
{
    A = A ^ mem->read8(PC++);
    F = (A ? 0 : ZERO_FLAG);
    lastStepClk = 2;
}
#pragma endregion Logically XOR 8-bit value with accumulator



/* CP n
Compares 8-bit value with accumulator register and changes flag accordingly.
*/
inline void CPU::CP_r2(unsigned char r2)
{
    F = (A == r2 ? ZERO_FLAG : 0)
        | SUBTRACT_FLAG
        | ((A & 0x0F) > (r2 & 0x0F) ? HALF_CARRY_FLAG : 0)
        | (A < r2 ? CARRY_FLAG : 0);
    lastStepClk = 1;
}
#pragma region CP implementations
void CPU::CP_A()
{
    CP_r2(A);
}

void CPU::CP_B()
{
    CP_r2(B);
}

void CPU::CP_C()
{
    CP_r2(C);
}

void CPU::CP_D()
{
    CP_r2(D);
}

void CPU::CP_E()
{
    CP_r2(E);
}

void CPU::CP_H()
{
    CP_r2(H);
}

void CPU::CP_L()
{
    CP_r2(L);
}

void CPU::CP_pHL()
{
    unsigned char r2 = mem->read8(HL);
    F = (A == r2 ? ZERO_FLAG : 0)
        | SUBTRACT_FLAG
        | ((A & 0x0F) > (r2 & 0x0F) ? HALF_CARRY_FLAG : 0)
        | (A < r2 ? CARRY_FLAG : 0);
    lastStepClk = 2;
}

void CPU::CP_n()
{
    unsigned char r2 = mem->read8(PC++);
    F = (A == r2 ? ZERO_FLAG : 0)
        | SUBTRACT_FLAG
        | ((A & 0x0F) >(r2 & 0x0F) ? HALF_CARRY_FLAG : 0)
        | (A < r2 ? CARRY_FLAG : 0);
    lastStepClk = 2;
}
#pragma endregion Compares 8-bit value with accumulator.



/* INC r2
Increments 8-bit value by one.
*/
inline void CPU::INC_r2(unsigned char & r2)
{
    F = (r2 == 0xFF ? ZERO_FLAG : 0)
        | ((r2 & 0x0F) == 0x0F ? HALF_CARRY_FLAG : 0)
        | (F & CARRY_FLAG);
    ++r2;
    lastStepClk = 1;
}
#pragma region INC Implementations
void CPU::INC_A()
{
    INC_r2(A);
}

void CPU::INC_B()
{
    INC_r2(B);
}

void CPU::INC_C()
{
    INC_r2(C);
}

void CPU::INC_D()
{
    INC_r2(D);
}

void CPU::INC_E()
{
    INC_r2(E);
}

void CPU::INC_H()
{
    INC_r2(H);
}

void CPU::INC_L()
{
    INC_r2(L);
}

void CPU::INC_pHL()
{
    unsigned char r2 = mem->read8(HL);
    F = (r2 == 0xFF ? ZERO_FLAG : 0)
        | ((r2 & 0x0F) == 0x0F ? HALF_CARRY_FLAG : 0)
        | (F & CARRY_FLAG);
    ++r2;
    mem->write8(HL, r2);
    lastStepClk = 3;
}
#pragma endregion Increments register by one.



/* DEC r2
Decrements 8-bit value by one.
*/
inline void CPU::DEC_r2(unsigned char & r2)
{
    F = (r2 == 1 ? ZERO_FLAG : 0)
        | SUBTRACT_FLAG
        | ((r2 & 0x00FF) == 0x0000 ? 0 : HALF_CARRY_FLAG)
        | (F & CARRY_FLAG);
    --r2;
    lastStepClk = 1;
}
#pragma region DEC implementations
void CPU::DEC_A()
{
    DEC_r2(A);
}
void CPU::DEC_B()
{
    DEC_r2(B);
}
void CPU::DEC_C()
{
    DEC_r2(C);
}
void CPU::DEC_D()
{
    DEC_r2(D);
}
void CPU::DEC_E()
{
    DEC_r2(E);
}
void CPU::DEC_H()
{
    DEC_r2(H);
}
void CPU::DEC_L()
{
    DEC_r2(L);
}
void CPU::DEC_pHL()
{
    unsigned char r2 = mem->read8(HL);
    F = (r2 == 1 ? ZERO_FLAG : 0)
        | SUBTRACT_FLAG
        | ((r2 & 0x00FF) == 0x0000 ? 0 : HALF_CARRY_FLAG)
        | (F & CARRY_FLAG);
    --r2;
    mem->write8(HL, r2);
    lastStepClk = 3;
}
#pragma endregion Decrements register by one.