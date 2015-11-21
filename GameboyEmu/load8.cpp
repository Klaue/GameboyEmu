#include "cpu.h"

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