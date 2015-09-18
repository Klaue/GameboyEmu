#include "mmu.h"
#include "cpu.h"

//Combined 16-bit Registers
#define AF A << 8 | F
#define BC B << 8 | C
#define DE D << 8 | E
#define HL H << 8 | L

CPU::CPU() :
    A(0),
    B(0),
    C(0),
    D(0),
    E(0),
    F(0),
    H(0),
    L(0),
    PC(0x100),
    SP(0xFFFE),
    clk(0),
    lastStepClk(0)
{}

/*============================================
                INSTRUCTIONS
=============================================*/
/*A note on instruction implementations.
    There are a little over 500 instructions supported
    by the GameBoy's modified Z80 CPU. These are the
    things that need to be done a million times per
    second, and therefore they need to be pretty damn fast.
    The idea is to stuff these all into an array that can
    be accessed by the opcode. As such, they all need to be
    called directly with as little overhead as possible.
    Hence why they're all being written individually.
    Where a function seems logical to minimize the need for
    code, I am instead writing an inline version of that
    function and calling it within each relevant instruction.
    This should at least cut down on modification anomalies.
*/


/*=========================================== 
                8 BIT LOADS 
============================================*/


/* LD nn,n
   Loads 8-bit constant, n, into register nn.
*/

//Helper
inline void CPU::LD_nn_n(unsigned char & reg)
{
    reg = mem->read8(PC++);
    lastStepClk = 2;
}

#pragma region LD_nn_n Implementations

void CPU::LD_A_n()
{
    LD_nn_n(A);
}

void CPU::LD_B_n()
{
    LD_nn_n(B);
}

void CPU::LD_C_n()
{
    LD_nn_n(C);
}

void CPU::LD_D_n()
{
    LD_nn_n(D);
}

void CPU::LD_E_n()
{
    LD_nn_n(E);
}

void CPU::LD_H_n()
{
    LD_nn_n(H);
}

void CPU::LD_L_n()
{
    LD_nn_n(L);
}
#pragma endregion Commands to do this on each 8-bit register that isn't the accumulator or flag.




/* LD r1,r2
   Loads the contents of register r2 into register r1.
   These are 8-bit to 8-bit, but some use the 16-bit combination HL as an address
   to an byte in the address space.
*/

//Helper
//Implementation of 8-bit register to 8-bit register.
inline void CPU::LD_r1_r2(unsigned char & r1, unsigned char r2) 
{
    r1 = r2;
    lastStepClk = 1;
}

//Helper
//Loads the contents pointed to by a 16-bit register, p16, into register r1.
inline void CPU::LD_r1_p16(unsigned char & r1, uint16_t p16)
{
    r1 = mem->read8(p16);
    lastStepClk = 2;
}

//Helper
//Loads the the contents of r2 into a byte pointed to by p16.
inline void CPU::LD_p16_r2(uint16_t p16, unsigned char r2)
{
    mem->write8(p16, r2);
    lastStepClk = 2;
}

#pragma region LD_r1_r2 Implementations
void CPU::LD_A_A()
{
    LD_r1_r2(A, A);
}

void CPU::LD_A_B()
{
    LD_r1_r2(A, B);
}

void CPU::LD_A_C()
{
    LD_r1_r2(A, C);
}

void CPU::LD_A_D()
{
    LD_r1_r2(A, D);
}

void CPU::LD_A_E()
{
    LD_r1_r2(A, E);
}

void CPU::LD_A_H()
{
    LD_r1_r2(A, H);
}

void CPU::LD_A_L()
{
    LD_r1_r2(A, L);
}

void CPU::LD_A_pHL()
{
    LD_r1_p16(A, HL);
}

void CPU::LD_B_B()
{
    LD_r1_r2(B, B);
}

void CPU::LD_B_C()
{
    LD_r1_r2(B, C);
}

void CPU::LD_B_D()
{
    LD_r1_r2(B, D);
}

void CPU::LD_B_E()
{
    LD_r1_r2(B, E);
}

void CPU::LD_B_H()
{
    LD_r1_r2(B, H);
}

void CPU::LD_B_L()
{
    LD_r1_r2(B, L);
}

void CPU::LD_B_pHL()
{
    LD_r1_p16(B, HL);
}

void CPU::LD_C_B()
{
    LD_r1_r2(C, B);
}

void CPU::LD_C_C()
{
    LD_r1_r2(C, C);
}

void CPU::LD_C_D()
{
    LD_r1_r2(C, D);
}

void CPU::LD_C_E()
{
    LD_r1_r2(C, E);
}

void CPU::LD_C_H()
{
    LD_r1_r2(C, H);
}

void CPU::LD_C_L()
{
    LD_r1_r2(C, L);
}

void CPU::LD_C_pHL()
{
    LD_r1_p16(C, HL);
}

void CPU::LD_D_B()
{
    LD_r1_r2(D, B);
}

void CPU::LD_D_C()
{
    LD_r1_r2(D, C); 
}

void CPU::LD_D_D()
{
    LD_r1_r2(D, D);
}

void CPU::LD_D_E()
{
    LD_r1_r2(D, E);
}

void CPU::LD_D_H()
{
    LD_r1_r2(D, H);
}

void CPU::LD_D_L()
{
    LD_r1_r2(D, L);
}

void CPU::LD_D_pHL()
{
    LD_r1_p16(D, HL);
}

void CPU::LD_E_B()
{
    LD_r1_r2(E, B);
}

void CPU::LD_E_C()
{
    LD_r1_r2(E, C);
}

void CPU::LD_E_D()
{
    LD_r1_r2(E, D);
}

void CPU::LD_E_E()
{
    LD_r1_r2(E, E);
}

void CPU::LD_E_H()
{
    LD_r1_r2(E, H);
}

void CPU::LD_E_L()
{
    LD_r1_r2(E, L);
}

void CPU::LD_E_pHL()
{
    LD_r1_p16(E, HL);
}

void CPU::LD_H_B()
{
    LD_r1_r2(H, B);
}

void CPU::LD_H_C()
{
    LD_r1_r2(H, C);
}

void CPU::LD_H_D()
{
    LD_r1_r2(H, D);
}

void CPU::LD_H_E()
{
    LD_r1_r2(H, E);
}

void CPU::LD_H_H()
{
    LD_r1_r2(H, H);
}

void CPU::LD_H_L()
{
    LD_r1_r2(H, L);
}

void CPU::LD_H_pHL()
{
    LD_r1_p16(H, HL);
}

void CPU::LD_L_B()
{
    LD_r1_r2(L, B);
}

void CPU::LD_L_C()
{
    LD_r1_r2(L, C);
}

void CPU::LD_L_D()
{
    LD_r1_r2(L, D);
}

void CPU::LD_L_E()
{
    LD_r1_r2(L, E);
}

void CPU::LD_L_H()
{
    LD_r1_r2(L, H);
}

void CPU::LD_L_L()
{
    LD_r1_r2(L, L);
}

void CPU::LD_L_pHL()
{
    LD_r1_p16(L, HL);
}

void CPU::LD_pHL_B()
{
    LD_p16_r2(HL, B);
}

void CPU::LD_pHL_C()
{
    LD_p16_r2(HL, C);
}

void CPU::LD_pHL_D()
{
    LD_p16_r2(HL, D);
}

void CPU::LD_pHL_E()
{
    LD_p16_r2(HL, E);
}

void CPU::LD_pHL_H()
{
    LD_p16_r2(HL, H);
}

void CPU::LD_pHL_L()
{
    LD_p16_r2(HL, L);
}
#pragma endregion Commands to get a value between every combo of regs except the flag.




//Lastly, still an LD r1, r2 command, but a specific one where the memory address specified
//by the combined 16-bit register HL is written with the immediate value of this instruction.
inline void CPU::LD_pHL_n() 
{
    mem->write8(H << 8 | L, mem->read8(PC++));
    lastStepClk = 3;
}




/* LD A,n
   Loads the contents of register n into the accumulator.
   'n' in certain instructions are actually pointers to bytes in the address space.
   These are prefixed with a lowercase p.
*/
#pragma region LD_A_n Implementations
void CPU::LD_A_pBC() 
{
    LD_r1_p16(A, BC);
}

void CPU::LD_A_pDE()
{
    LD_r1_p16(A, DE);
}

//The immediate value address is little endian.
void CPU::LD_A_pnn() 
{
    A = mem->read8(mem->read8(PC + 1) << 8 | mem->read8(PC));
    PC += 2;
    lastStepClk = 4;
}

void CPU::LD_A_pCplusIO()
{
    LD_r1_p16(A, C + MMU::IO_PORTS);
}

//I feel like this instruction can be optimized.
void CPU::LDD_A_pHL()
{
    uint16_t tempHL = HL;
    F = (HL == 1 ? ZERO_FLAG : 0) | SUBTRACT_FLAG | ((HL & 0x01FF) == 0x0100 ? HALF_CARRY_FLAG : 0) | (F & CARRY_FLAG);
    A = mem->read8(tempHL--);
    H = tempHL >> 8;
    L = tempHL & 0x00FF;
    lastStepClk = 2;
}

void CPU::LDI_A_pHL()
{
    uint16_t tempHL = HL;
    F = (HL == 0xFFFF ? ZERO_FLAG : 0) | ((HL & 0x00FF) == 0x00FF ? HALF_CARRY_FLAG : 0) | (F & CARRY_FLAG);
    A = mem->read8(tempHL++);
    H = tempHL >> 8;
    L = tempHL & 0x00FF;
    lastStepClk = 2;
}

void CPU::LD_A_pnplusIO()
{
    A = mem->read8(mem->read8(PC++) + MMU::IO_PORTS);
    lastStepClk = 3;
}
#pragma endregion Operations that load value n into A




/* LD n,A
   Loads the contents of the accumulator register into register n.
   'n' in certain instructions are actually pointers to bytes in the address space.
   These are prefixed with a lowercase p.
*/
#pragma region LD_n_A Implementations
void CPU::LD_B_A()
{
    LD_r1_r2(B, A);
}

void CPU::LD_C_A()
{
    LD_r1_r2(C, A);
}

void CPU::LD_D_A()
{
    LD_r1_r2(D, A);
}

void CPU::LD_E_A()
{
    LD_r1_r2(E, A);
}

void CPU::LD_H_A()
{
    LD_r1_r2(H, A);
}

void CPU::LD_L_A()
{
    LD_r1_r2(L, A);
}

void CPU::LD_pBC_A()
{
    LD_p16_r2(BC, A);
}

void CPU::LD_pDE_A()
{
    LD_p16_r2(DE, A);
}

void CPU::LD_pHL_A()
{
    LD_p16_r2(HL, A);
}

//Again, nn is little endian
void CPU::LD_pnn_A()
{
    mem->write8(mem->read8(PC + 1) << 8 | mem->read8(PC), A);
    PC += 2;
    lastStepClk = 4;
}

//Loads A into the location specified by the contents of C plus 0xFF00.
void CPU::LD_pCplusIO_A()
{
    LD_p16_r2(C + MMU::IO_PORTS, A);
}

//Again... optimizable?
void CPU::LDD_pHL_A()
{
    uint16_t tempHL = HL;
    F = (HL == 1 ? ZERO_FLAG : 0) 
        | SUBTRACT_FLAG 
        | ((HL & 0x0FFF) == 0x0000 ? 0 : HALF_CARRY_FLAG) 
        | (F & CARRY_FLAG);
    mem->write8(tempHL--, A);
    H = tempHL >> 8;
    L = tempHL & 0x00FF;
    lastStepClk = 2;
}

void CPU::LDI_pHL_A()
{
    uint16_t tempHL = HL;
    F = (HL == 0xFFFF ? ZERO_FLAG : 0) 
        | ((HL & 0x0FFF) == 0x0FFF ? HALF_CARRY_FLAG : 0) 
        | (F & CARRY_FLAG);
    mem->write8(tempHL++, A);
    H = tempHL >> 8;
    L = tempHL & 0x00FF;
    lastStepClk = 2;
}

void CPU::LD_pnplusIO_A()
{
    mem->write8(mem->read8(PC++) + MMU::IO_PORTS, A);
    lastStepClk = 3;
}
#pragma endregion Operations that load the contents of A somewhere else.


/*=================================================
                 16-BIT LOADS
=================================================*/

/* LD n,nn (16-bit)
   Loads the immediate 16-bit value into combined 16-bit register n.
*/
//Optimizable?
inline void CPU::LD16_n_nn(unsigned char & b1, unsigned char & b2)
{
    uint16_t immediateValue = mem->read16(PC);
    b1 = immediateValue >> 8;
    b2 = immediateValue & 0x00FF;
    PC += 2;
    lastStepClk = 3;
}
#pragma region LD_n_nn(b1, b2) Implementations
void CPU::LD16_BC_nn()
{
    LD16_n_nn(B, C);
}

void CPU::LD16_DE_nn()
{
    LD16_n_nn(D, E);
}

void CPU::LD16_HL_nn()
{
    LD16_n_nn(H, L);
}

//Of course, the stack pointer is not a combined register. It is naturally 16 bits.
void CPU::LD16_SP_nn()
{
    SP = mem->read16(PC);
    PC += 2;
    lastStepClk = 3;
}
#pragma endregion Operations for loading 16-bit immediate values.

void CPU::LD_SP_HL()
{
    SP = HL;
    lastStepClk = 2;
}

void CPU::LDHL_SP_n()
{
    uint16_t temp = SP + mem->read8(PC++);
    H = temp >> 8;
    L = temp & 0x00FF;
    lastStepClk = 3;
}

void CPU::LD_nn_SP()
{
    mem->write16(mem->read16(PC), SP);
    PC += 2;
    lastStepClk = 5;
}


/* PUSH nn
   Pushes the combined 16-bit register onto the stack.
*/
inline void CPU::PUSH_nn(uint16_t nn)
{
    mem->write8(SP, nn);
    SP -= 2;
    lastStepClk = 4;
}
#pragma region Push Implementations
void CPU::PUSH_AF()
{
    PUSH_nn(AF);
}

void CPU::PUSH_BC()
{
    PUSH_nn(BC);
}

void CPU::PUSH_DE()
{
    PUSH_nn(DE);
}

void CPU::PUSH_HL()
{
    PUSH_nn(HL);
}
#pragma endregion Push 16-bit registers onto stack




/* POP nn
   Pops 16 bits off the stack into a 16-bit combined register.
*/
inline void CPU::POP_nn(unsigned char & b1, unsigned char & b2)
{
    uint16_t temp = mem->read16(SP);
    b1 = temp >> 8;
    b2 = temp & 0x00FF;
    SP += 2;
    lastStepClk = 3;
}
#pragma region Pop Implementations
void CPU::POP_AF()
{
    POP_nn(A, F);
}

void CPU::POP_BC()
{
    POP_nn(B, C);
}

void CPU::POP_DE()
{
    POP_nn(D, E);
}

void CPU::POP_HL()
{
    POP_nn(H, L);
}
#pragma endregion Pop 16 bits off the stack and store into a 16-bit combined register.

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


/*=================================================
          16-BIT ARITHMETIC LOGIC UNIT
=================================================*/

/* ADD HL,n
   Increments HL by the 16-bit value n
*/
inline void CPU::ADD16_HL_r2(uint16_t r2)
{
    uint16_t tempHL = HL;
    tempHL += r2;
    H = (tempHL & 0xFF00) >> 8;
    L = (tempHL & 0x00FF);
    F = (F & ZERO_FLAG)
        | ((r2 & 0x0FFF) > (tempHL & 0x0FFF) ? HALF_CARRY_FLAG : 0)
        | (r2 > tempHL ? CARRY_FLAG : 0);
    lastStepClk = 2;
}
#pragma region ADD_HL,n Implementations
void CPU::ADD16_HL_BC()
{
    ADD16_HL_r2(BC);
}

void CPU::ADD16_HL_DE()
{
    ADD16_HL_r2(DE);
}

void CPU::ADD16_HL_HL()
{
    ADD16_HL_r2(HL);
}

void CPU::ADD16_HL_SP()
{
    ADD16_HL_r2(SP);
}
#pragma endregion Adds 16-bit value to register_HL




/* ADD SP,n
   Adds 8-bit immediate value to stack pointer.
*/
void CPU::ADD16_SP_n()
{
    unsigned char r2 = mem->read8(PC++);
    SP += r2;
    F = ((r2 & 0x0FFF) > (SP & 0x0FFF) ? HALF_CARRY_FLAG : 0)
        | (r2 > SP ? CARRY_FLAG : 0);
    lastStepClk = 4;
}



/* INC nn
   Increments 16-bit register by one.
*/
inline void CPU::INC16_r2(unsigned char & highByte, unsigned char & lowByte)
{
    uint16_t temp = (highByte << 8) | lowByte;
    ++temp;
    highByte = (temp & 0xFF00) >> 8;
    lowByte = (temp & 0x00FF);
    lastStepClk = 2;
}
#pragma region 16-bit INC Implementation
void CPU::INC16_BC()
{
    INC16_r2(B, C);
}

void CPU::INC16_DE()
{
    INC16_r2(D, E);
}

void CPU::INC16_HL()
{
    INC16_r2(H, L);
}

void CPU::INC16_SP()
{
    ++SP;
    lastStepClk = 2;
}
#pragma endregion Increments 16-bit register by one.



/* DEC nn
   Decrements 16-bit register by one.
*/
void CPU::DEC16_r2(unsigned char & highByte, unsigned char & lowByte)
{
    uint16_t temp = (highByte << 8) | lowByte;
    --temp;
    highByte = (temp & 0xFF00) >> 8;
    lowByte = (temp & 0x00FF);
    lastStepClk = 2;
}
#pragma region 16-bit DEC Implementations
void CPU::DEC16_BC()
{
    DEC16_r2(B, C);
}

void CPU::DEC16_DE()
{
    DEC16_r2(D, E);
}

void CPU::DEC16_HL()
{
    DEC16_r2(H, L);
}

void CPU::DEC16_SP()
{
    --SP;
    lastStepClk = 2;
}
#pragma endregion Decrements 16-bit register by one.



/*=================================================
                  MISCELLANEOUS
=================================================*/