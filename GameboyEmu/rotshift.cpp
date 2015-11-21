#include "cpu.h"

/*=================================================
ROTATES AND SHIFTS
=================================================*/

/* RLCA
Rotates accumulator register one bit to the left.
*/
void CPU::RLCA()
{
    //Result is zero if accumulator is already zero.
    F = (A == 0 ? ZERO_FLAG : 0) | (A & 0x80 ? CARRY_FLAG : 0);
    A = ((A & 0x7F) << 1) | ((A & 0x80) >> 7);
    lastStepClk = 1;
}


/* RLA
Rotates accumulator register one bit to the left through the carry flag
*/
void CPU::RLA()
{
    //Result is zero if accumulator's bits 0-6 and carry flag are zero.
    F = (!((A & 0x7F) || F & CARRY_FLAG) ? ZERO_FLAG : 0) | (A & 0x80 ? CARRY_FLAG : 0);
    A = ((A & 0x7F) << 1) | (F & CARRY_FLAG ? 0x01 : 0);
    lastStepClk = 1;
}

/* RRCA
Rotates accumulator register 1 bit to the right
*/
void CPU::RRCA()
{
    //Result is zero if accumulator is already zero.
    F = (A == 0 ? ZERO_FLAG : 0) | (A & 0x01 ? CARRY_FLAG : 0);
    A = ((A & 0xFE) >> 1) | ((A & 0x01) << 7);
    lastStepClk = 1;
}

/* RRA
Rotates accumulator register one bit to the right through the carry flag
*/
void CPU::RRA()
{
    //Result is zero if accumulator's bits 1-7 and carry flag are zero.
    F = (!((A & 0xFE) || F & CARRY_FLAG) ? ZERO_FLAG : 0) | (A & 0x01 ? CARRY_FLAG : 0);
    A = ((A & 0xFE) >> 1) | (F & CARRY_FLAG ? 0x80 : 0);
    lastStepClk = 1;
}


/* RLC_r2
Rotates 8-bit register r2 1 bit to the left.
*/
inline void CPU::RLC_r2(unsigned char & r2)
{
    F = (r2 == 0 ? ZERO_FLAG : 0) | (r2 & 0x80 ? CARRY_FLAG : 0);
    r2 = ((r2 & 0x7F) << 1) | ((r2 & 0x80) >> 7);
    lastStepClk = 2;
}
#pragma region RLC_r2 implementations
void CPU::RLC_A()
{
    RLC_r2(A);
}

void CPU::RLC_B()
{
    RLC_r2(B);
}

void CPU::RLC_C()
{
    RLC_r2(C);
}

void CPU::RLC_D()
{
    RLC_r2(D);
}

void CPU::RLC_E()
{
    RLC_r2(E);
}

void CPU::RLC_H()
{
    RLC_r2(H);
}

void CPU::RLC_L()
{
    RLC_r2(L);
}

void CPU::RLC_pHL()
{
    unsigned char r2 = mem->read8(HL);
    F = (r2 == 0 ? ZERO_FLAG : 0) | (r2 & 0x80 ? CARRY_FLAG : 0);
    mem->write8(HL, ((r2 & 0x7F) << 1) | ((r2 & 0x80) >> 7));
    lastStepClk = 4;
}
#pragma endregion Rotates register r2 one bit to the left.


/* RL r2
Rotate register r2 one bit to the left through the carry flag.
*/
inline void CPU::RL_r2(unsigned char & r2)
{
    //Result is zero if accumulator's bits 0-6 and carry flag are zero.
    F = (!((r2 & 0x7F) || F & CARRY_FLAG) ? ZERO_FLAG : 0) | (r2 & 0x80 ? CARRY_FLAG : 0);
    r2 = ((r2 & 0x7F) << 1) | (F & CARRY_FLAG ? 0x01 : 0);
    lastStepClk = 2;
}
#pragma region RL_r2 implementations
void CPU::RL_A()
{
    RL_r2(A);
}

void CPU::RL_B()
{
    RL_r2(B);
}

void CPU::RL_C()
{
    RL_r2(C);
}

void CPU::RL_D()
{
    RL_r2(D);
}

void CPU::RL_E()
{
    RL_r2(E);
}

void CPU::RL_H()
{
    RL_r2(H);
}

void CPU::RL_L()
{
    RL_r2(L);
}

void CPU::RL_pHL()
{
    unsigned char r2 = mem->read8(HL);
    //Result is zero if accumulator's bits 0-6 and carry flag are zero.
    F = (!((r2 & 0x7F) || F & CARRY_FLAG) ? ZERO_FLAG : 0) | (r2 & 0x80 ? CARRY_FLAG : 0);
    mem->write8(HL, ((r2 & 0x7F) << 1) | (F & CARRY_FLAG ? 0x01 : 0));
    lastStepClk = 4;
}
#pragma endregion Rotate register 1 bit to the left through carry flag.


/* RRC r2
Rotate register r2 one bit to the right.
*/
inline void CPU::RRC_r2(unsigned char & r2)
{
    //Result is zero if accumulator is already zero.
    F = (r2 == 0 ? ZERO_FLAG : 0) | (r2 & 0x01 ? CARRY_FLAG : 0);
    r2 = ((r2 & 0xFE) >> 1) | ((r2 & 0x01) << 7);
    lastStepClk = 2;
}
#pragma region RRC_r2 implementation
void CPU::RRC_A()
{
    RRC_r2(A);
}
void CPU::RRC_B()
{
    RRC_r2(B);
}
void CPU::RRC_C()
{
    RRC_r2(C);
}
void CPU::RRC_D()
{
    RRC_r2(D);
}
void CPU::RRC_E()
{
    RRC_r2(E);
}
void CPU::RRC_H()
{
    RRC_r2(H);
}
void CPU::RRC_L()
{
    RRC_r2(L);
}
void CPU::RRC_pHL()
{
    unsigned char r2 = mem->read8(HL);
    //Result is zero if accumulator is already zero.
    F = (r2 == 0 ? ZERO_FLAG : 0) | (r2 & 0x01 ? CARRY_FLAG : 0);
    mem->write8(HL, ((r2 & 0xFE) >> 1) | ((r2 & 0x01) << 7));
    lastStepClk = 4;
}
#pragma endregion Rotate register 1 bit to the right.


/* RR r2
Rotate register r2 one bit to the right through the carry flag.
*/
inline void CPU::RR_r2(unsigned char & r2)
{
    //Result is zero if accumulator's bits 1-7 and carry flag are zero.
    F = (!((r2 & 0xFE) || F & CARRY_FLAG) ? ZERO_FLAG : 0) | (r2 & 0x01 ? CARRY_FLAG : 0);
    r2 = ((r2 & 0xFE) >> 1) | (F & CARRY_FLAG ? 0x80 : 0);
    lastStepClk = 2;
}
#pragma region RR_r2 implementations
void CPU::RR_A()
{
    RR_r2(A);
}

void CPU::RR_B()
{
    RR_r2(B);
}

void CPU::RR_C()
{
    RR_r2(C);
}

void CPU::RR_D()
{
    RR_r2(D);
}

void CPU::RR_E()
{
    RR_r2(E);
}

void CPU::RR_H()
{
    RR_r2(H);
}

void CPU::RR_L()
{
    RR_r2(L);
}

void CPU::RR_pHL()
{
    unsigned char r2 = mem->read8(HL);
    //Result is zero if accumulator's bits 1-7 and carry flag are zero.
    F = (!((r2 & 0xFE) || F & CARRY_FLAG) ? ZERO_FLAG : 0) | (r2 & 0x01 ? CARRY_FLAG : 0);
    mem->write8(HL, ((r2 & 0xFE) >> 1) | (F & CARRY_FLAG ? 0x80 : 0));
    lastStepClk = 4;
}
#pragma endregion Rotate register 1 bit right through carry flag.


/* SLA r2
1-bit arithmetic shift to the left on register r2 into carry flag.
*/
inline void CPU::SLA_r2(unsigned char & r2)
{
    F = ((r2 & 0x7F) ? 0 : ZERO_FLAG) | ((r2 & 0x80) ? CARRY_FLAG : 0);
    r2 <<= 1;
    lastStepClk = 2;
}
#pragma region SLA_r2 implementations
void CPU::SLA_A()
{
    SLA_r2(A);
}

void CPU::SLA_B()
{
    SLA_r2(B);
}

void CPU::SLA_C()
{
    SLA_r2(C);
}

void CPU::SLA_D()
{
    SLA_r2(D);
}

void CPU::SLA_E()
{
    SLA_r2(E);
}

void CPU::SLA_H()
{
    SLA_r2(H);
}

void CPU::SLA_L()
{
    SLA_r2(L);
}

void CPU::SLA_pHL()
{
    unsigned char r2 = mem->read8(HL);
    F = ((r2 & 0x7F) ? 0 : ZERO_FLAG) | ((r2 & 0x80) ? CARRY_FLAG : 0);
    mem->write8(HL, r2 << 1);
    lastStepClk = 4;
}
#pragma endregion Shift register one bit to the left.


/* SRA r2
1-bit arithmetic shift to the right on register r2 into carry flag.
*/
inline void CPU::SRA_r2(unsigned char & r2)
{
    F = ((r2 & 0xFE) ? 0 : ZERO_FLAG) | ((r2 & 0x01) ? CARRY_FLAG : 0);
    r2 = (r2 >> 1) | (r2 & 0x80);
    lastStepClk = 2;
}
#pragma region SRA_r2 implementations
void CPU::SRA_A()
{
    SRA_r2(A);
}

void CPU::SRA_B()
{
    SRA_r2(B);
}

void CPU::SRA_C()
{
    SRA_r2(C);
}

void CPU::SRA_D()
{
    SRA_r2(D);
}

void CPU::SRA_E()
{
    SRA_r2(E);
}

void CPU::SRA_H()
{
    SRA_r2(H);
}

void CPU::SRA_L()
{
    SRA_r2(L);
}

void CPU::SRA_pHL()
{
    unsigned char r2 = mem->read8(HL);
    F = ((r2 & 0xFE) ? 0 : ZERO_FLAG) | ((r2 & 0x01) ? CARRY_FLAG : 0);
    mem->write8(HL, (r2 >> 1) | (r2 & 0x80));
    lastStepClk = 4;
}
#pragma endregion 1 bit arithmetic shift to the right.


/* SRL r2
1-bit logical shift to the right on register r2 into carry flag.
*/
inline void CPU::SRL_r2(unsigned char & r2)
{
    F = ((r2 & 0xFE) ? 0 : ZERO_FLAG) | ((r2 & 0x01) ? CARRY_FLAG : 0);
    r2 >>= 1;
    lastStepClk = 2;
}
#pragma region SRL_r2 implementations
void CPU::SRL_A()
{
    SRL_r2(A);
}

void CPU::SRL_B()
{
    SRL_r2(B);
}

void CPU::SRL_C()
{
    SRL_r2(C);
}

void CPU::SRL_D()
{
    SRL_r2(D);
}

void CPU::SRL_E()
{
    SRL_r2(E);
}

void CPU::SRL_H()
{
    SRL_r2(H);
}

void CPU::SRL_L()
{
    SRL_r2(L);
}

void CPU::SRL_pHL()
{
    unsigned char r2 = mem->read8(HL);
    F = ((r2 & 0xFE) ? 0 : ZERO_FLAG) | ((r2 & 0x01) ? CARRY_FLAG : 0);
    mem->write8(HL, r2 >> 1);
    lastStepClk = 4;
}
#pragma endregion 1 bit logical shift to the right.
