#pragma once
/*  @author  Thomas Mitchell
    I have no affiliation with Nintendo. This project is for my own personal education
    and amusement and not for any commercial purpose.

    Implementation of the Gameboy's Z80 processor according to the specifications found 
    at http://marc.rawer.de/Gameboy/Docs/GBCPUman.pdf
    A big thank you to them for compiling that.

    Also, a big thank you to Imran Nazar for having done this in Javascript already and
    providing a guide for when I lose my way on this project. I'm trying to use his work
    as little as possible, mostly just a double check for when an instruction specification
    is not clear to me.
    http://imrannazar.com/GameBoy-Emulation-in-JavaScript:-The-CPU
*/
#include <cstdint>
#include "mmu.h"

//Combined 16-bit Registers
#define AF (A << 8) | F
#define BC (B << 8) | C
#define DE (D << 8) | E
#define HL (H << 8) | L

class CPU {
public:
    //Constructor
    CPU();
    //Destructor
    ~CPU() {}


private:
    /*==============================================
                Connected Machine Components
    ================================================*/
    MMU * mem;

    /*==============================================
                        Clock
    ================================================*/

    //This is the number of machine cycles. 4 clock cycles in one of these.
    unsigned long long clk;
    //The number of machine cycles required by the last instruction.
    unsigned long long lastStepClk;

    /*==============================================
                       Registers
    ===============================================*/
    //A is accumulator. F is flag register.
    unsigned char A, B, C, D, E, F, H, L;
    //Program counter
    uint16_t PC;
    //Stack pointer.
    uint16_t SP;
    
    /*==============================================
               Additional Machine State
    ===============================================*/
    // Interrupt master enable
    bool IME;
    // -1 means no transition in progress.
    // 0 means transition on this step.
    // 1 means transition after next step.
    char IMETransitionCounter;
    // True if setting to enable on transition.
    // False if setting to disable on transition.
    bool setToEnable;
    bool halted;
    bool stopped;

    /*==============================================
                       Constants
    ===============================================*/
    //Set if math operation yields zero or if CP instruction has matching values.
    static const unsigned char ZERO_FLAG = 0x80;
    //Set if last math instruction was a subtraction
    static const unsigned char SUBTRACT_FLAG = 0x40;
    //Set if last math instruction carried out of the least significant nybble
    static const unsigned char HALF_CARRY_FLAG = 0x20;
    //Set if last instruction overflowed.
    static const unsigned char CARRY_FLAG = 0x10;

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


    /*----------------8-BIT LOADS------------------*/
    
    /* LD nn,n
    ---- Loads the 8-bit immediate value n into register nn.
    */
    
    // Generic version. Inlined.
    // @param reg  reference to register to take value n.
    // The value n is the value currently pointed to by the program counter.
    void LD_nn_n(unsigned char & reg); 

#pragma region LD_nn_n ops
    //Specific operations using LD_nn_n
    void LD_B_n();
    void LD_C_n();
    void LD_D_n();
    void LD_E_n();
    void LD_H_n();
    void LD_L_n();
#pragma endregion Commands to load immediate values into each register.
    
    /* LD r1,r2
    ---- Load the contents of register r2 into register r1
    */

    // Generic version. Inlined.
    // @param r1  reference to 8-bit register to take on new value.
    // @param r2  8-bit register to copy value from.
    void LD_r1_r2(unsigned char & r1, unsigned char r2); 

    // Generic version. Inlined.
    // @param r1  reference to 8-bit register to take on new value.
    // @param p16  16-bit register pointing to location to retrieve new value.
    void LD_r1_p16(unsigned char & r1, uint16_t p16);

    // Generic version. Inlined.
    // @param p16  16-bit address of byte to take on new value.
    // @param r2   register from which to retrieve new value.
    void LD_p16_r2(uint16_t p16, unsigned char r2);

#pragma region LD_r1_r2 ops
    //All names in the format "LD_<target register>_<source register>"
    //A lowercase 'p' signifies that the contents of that register are a pointer.
    void LD_A_A();
    void LD_A_B();
    void LD_A_C();
    void LD_A_D();
    void LD_A_E();
    void LD_A_H();
    void LD_A_L();
    void LD_A_pHL();
    void LD_B_B();
    void LD_B_C();
    void LD_B_D();
    void LD_B_E();
    void LD_B_H();
    void LD_B_L();
    void LD_B_pHL();
    void LD_C_B();
    void LD_C_C();
    void LD_C_D();
    void LD_C_E();
    void LD_C_H();
    void LD_C_L();
    void LD_C_pHL();
    void LD_D_B();
    void LD_D_C();
    void LD_D_D();
    void LD_D_E();
    void LD_D_H();
    void LD_D_L();
    void LD_D_pHL();
    void LD_E_B();
    void LD_E_C();
    void LD_E_D();
    void LD_E_E();
    void LD_E_H();
    void LD_E_L();
    void LD_E_pHL();
    void LD_H_B();
    void LD_H_C();
    void LD_H_D();
    void LD_H_E();
    void LD_H_H();
    void LD_H_L();
    void LD_H_pHL();
    void LD_L_B();
    void LD_L_C();
    void LD_L_D();
    void LD_L_E();
    void LD_L_H();
    void LD_L_L();
    void LD_L_pHL();
    void LD_pHL_B();
    void LD_pHL_C();
    void LD_pHL_D();
    void LD_pHL_E();
    void LD_pHL_H();
    void LD_pHL_L();
    void LD_pHL_n();
#pragma endregion Specific operations using LD_r1_r2(r1, r2);


    /* LD A,n 
    ---- Loads value n into A
    */
    
    // Some of these types of commands were handled in earlier groups and so don't
    // appear here.
    // What remains is the loading of 8-bit values referenced by the addresses
    // found in each 16-bit combined register that isn't HL, loading the byte pointed
    // to by an immediate value, and loading an immediate value itself.
#pragma region LD_A_n ops
    void LD_A_pBC();
    void LD_A_pDE();
    void LD_A_pnn();
    void LD_A_n();
    void LD_A_pCplusIO();
    //Loads the value pointed to by HL into A and decrements HL.
    void LDD_A_pHL();
    //Loads the value pointed to by HL into A and increments HL.
    void LDI_A_pHL();
    //Loads A with the value at (immediate value + 0xFF00)
    void LD_A_pnplusIO();
#pragma endregion Additional operations for putting values into the accumulator.

#pragma region LD_n_A ops
    void LD_B_A();
    void LD_C_A();
    void LD_D_A();
    void LD_E_A();
    void LD_H_A();
    void LD_L_A();
    void LD_pBC_A();
    void LD_pDE_A();
    void LD_pHL_A();
    void LD_pnn_A();
    void LD_pCplusIO_A();
    //Decrements HL after putting value of A at address pointed to by HL.
    void LDD_pHL_A();
    //Increments HL after putting value of A at address pointed to by HL.
    void LDI_pHL_A();
    //Load A into (8-bit immediate + 0xFF00)
    void LD_pnplusIO_A();
#pragma endregion Operations to load the contents of the accumulator somewhere else.


    /*----------------16-BIT LOADS-----------------*/

    /*
    ---- Loads 16-bit immediate value nn into combined 16-bit register nn.
    */

    // Generic version. Inlined.
    // Loads 16-bit immediate value into the combined 16-bit register
    // specified by the registers b1 and b2.
    // @pre  Program counter is pointing to first byte of immediate value.
    // @param b1  reference to most significant register of the combined 16-bit.
    // @param1b2  reference to least significant register of the combined 16-bit
    // @post  Program counter is advanced 2 bytes. Value is split between b1 and b2.
    void LD16_n_nn(unsigned char & b1, unsigned char & b2);
#pragma region LD16_n_nn ops
    void LD16_BC_nn();
    void LD16_DE_nn();
    void LD16_HL_nn();
    void LD16_SP_nn();
#pragma endregion Operations for loading 16-bit immediate values.


    void LD_SP_HL();
    void LDHL_SP_n();
    void LD_nn_SP();

    // Generic version. Inlined.
    // Pushes 16-bit combined register nn onto the stack.
    // @param nn  Combined 16-bit register with value to push.
    // @post  Stack pointer is decremented by 2.
    void PUSH_nn(uint16_t nn);
#pragma region Push ops
    void PUSH_AF();
    void PUSH_BC();
    void PUSH_DE();
    void PUSH_HL();
#pragma endregion Push certain register pairs onto the stack.

    // Generic version. Inlined.
    // Pops 16 bits off the stack and stores it in the registers specified.
    // @param b1  Register to hold most significant byte.
    // @param b2  Register to hold least significant byte.
    // @post  Stack pointer is incremented by 2.
    void POP_nn(unsigned char & b1, unsigned char & b2);
#pragma region Pop ops
    void POP_AF();
    void POP_BC();
    void POP_DE();
    void POP_HL();
#pragma endregion Pop 2 bytes off the stack and store into a 16-bit combined register.


    /*------8-BIT ARITHMETIC LOGIC UNIT------*/

    // Generic version. Inlined.
    // Adds contents of r2 to the accumulator.
    // @param r2  An 8-bit register to add to A.
    // @post  Flag register is set accordingly.
    void ADD_A_r2(unsigned char r2);
#pragma region Add ops
    void ADD_A_A();
    void ADD_A_B();
    void ADD_A_C();
    void ADD_A_D();
    void ADD_A_E();
    void ADD_A_H();
    void ADD_A_L();
    void ADD_A_pHL();
    void ADD_A_n();
#pragma endregion Adds a value to the accumulator.

    // Generic version. Inlined.
    // Adds contents of r2 plus the value of the carry flag
    // to the accumulator.
    // @param r2  An 8-bit register to add to A.
    // @post  Flag register is set accordingly.
    void ADC_A_r2(unsigned char r2);
#pragma region Add-Carry ops
    void ADC_A_A();
    void ADC_A_B();
    void ADC_A_C();
    void ADC_A_D();
    void ADC_A_E();
    void ADC_A_H();
    void ADC_A_L();
    void ADC_A_pHL();
    void ADC_A_n();
#pragma endregion Adds a value plus the carry flag to the accumulator.

    // Generic version. Inlined.
    // Subtracts contents of r2 from the accumulator
    // @param r2  An 8-bit register to subtract from A
    // @post  Flag register is set accordingly.
    void SUB_A_r2(unsigned char r2);
#pragma region Sub ops
    void SUB_A_A();
    void SUB_A_B();
    void SUB_A_C();
    void SUB_A_D();
    void SUB_A_E();
    void SUB_A_H();
    void SUB_A_L();
    void SUB_A_pHL();
    void SUB_A_n();
#pragma endregion Subtracts a value from the accumulator.

    // Generic version. Inlined.
    // Subtracts contents of r2 plus carry flag from
    // the accumulator.
    // @param r2  An 8-bit register
    // @post  Flag register is set accordingly.
    void SBC_A_r2(unsigned char r2);
#pragma region Sub-Carry ops
    void SBC_A_A();
    void SBC_A_B();
    void SBC_A_C();
    void SBC_A_D();
    void SBC_A_E();
    void SBC_A_H();
    void SBC_A_pHL();
    void SBC_A_n();
#pragma endregion Subtract value + carry from the accumulator.

    // Generic version. Inlined.
    // Logically ANDs r2 with A. Stores result in A.
    // @param r2  Register to logically AND with accumulator.
    // @post  Zero flag set if result is zero. Half Carry flag set.
    //          Other flags reset.
    void AND_r2(unsigned char r2);
#pragma region AND ops
    void AND_A();
    void AND_B();
    void AND_C();
    void AND_D();
    void AND_E();
    void AND_H();
    void AND_L();
    void AND_pHL();
    void AND_n();
#pragma endregion Logically AND 8-bit value with accumulator.

    // Generic version. Inlined.
    // Logically ORs r2 with A. Stores result in A.
    // @param r2  register to logically OR with accumulator.
    // @post  Zero flag set if result is zero. Other flags reset.
    void OR_r2(unsigned char r2);
#pragma region OR ops
    void OR_A();
    void OR_B();
    void OR_C();
    void OR_D();
    void OR_E();
    void OR_H();
    void OR_L();
    void OR_pHL();
    void OR_n();
#pragma endregion Logically OR 8-bit value with accumulator

    // Generic version. Inlined.
    // Logically XORs r2 with A. Stores result in A.
    // @param r2  register to logically XOR with accumulator.
    // @post  Zero flag set if result is zero. Other flags reset.
    void XOR_r2(unsigned char r2);
#pragma region XOR ops
    void XOR_A();
    void XOR_B();
    void XOR_C();
    void XOR_D();
    void XOR_E();
    void XOR_H();
    void XOR_L();
    void XOR_pHL();
    void XOR_n();
#pragma endregion Logically XOR 8-bit value with accumulator

    // Generic version. Inlined.
    // Compares r2 with A. Results found in flag register.
    // @param r2  Register to compare with accumulator.
    // @post  Zero flag set if values are equivalent.
    //          Subtraction flag is set. Half-carry flag
    //          set as if subtraction. Carry flag set if
    //          value in accumulator is less than r2.
    void CP_r2(unsigned char r2);
#pragma region CP ops
    void CP_A();
    void CP_B();
    void CP_C();
    void CP_D();
    void CP_E();
    void CP_H();
    void CP_L();
    void CP_pHL();
    void CP_n();
#pragma endregion Compares 8-bit value with accumulator.

    // Generic version. Inlined.
    // Increments the value in the register by one.
    // @param r2  The register to increment
    // @post  Zero flag set if result is zero. Subtraction
    //          flag reset.  Half carry set if carry from bit 3.
    //          Carry flag remains the same.
    void INC_r2(unsigned char & r2);
#pragma region INC ops
    void INC_A();
    void INC_B();
    void INC_C();
    void INC_D();
    void INC_E();
    void INC_H();
    void INC_L();
    void INC_pHL();
#pragma endregion Increments register by one.

    // Generic version. Inlined.
    // Decrements the value in the register by one.
    // @param r2  The register to decrement
    // @post  Zero flag set if result is zero. Subtraction
    //          flag set.  Half carry set if no borrow from bit 4.
    //          Carry flag remains the same.
    void DEC_r2(unsigned char & r2);
#pragma region DEC ops
    void DEC_A();
    void DEC_B();
    void DEC_C();
    void DEC_D();
    void DEC_E();
    void DEC_H();
    void DEC_L();
    void DEC_pHL();
#pragma endregion Decrements register by one.


    /*------16-BIT ARITHMETIC LOGIC UNIT------*/

    // Generic version. Inlined.
    // Adds the given 16-bit value to combined 16-bit register HL.
    // @param r2  The 16-bit register to add to HL
    // @post  Zero flag remains the same. Subtraction flag is reset.
    //          Half carry set if carry from bit 11. Carry flag set if
    //          carry from bit 15.
    void ADD16_HL_r2(uint16_t r2);
#pragma region ADD HL ops
    void ADD16_HL_BC();
    void ADD16_HL_DE();
    void ADD16_HL_HL();
    void ADD16_HL_SP();
#pragma endregion Adds 16-bit value to HL

    // Adds an 8-bit immediate value to the stack pointer.
    // @post  Zero flag and subtraction flag reset. Half-carry set if
    //          carry from bit 11. Carry set if overflow.
    void ADD16_SP_n();

    // Generic version. Inlined.
    // Increments combined 16-bit register by one.
    // @param r2  A combined 16-bit register to increment.
    void INC16_r2(unsigned char & highByte, unsigned char & lowByte);
#pragma region 16-bit INC ops
    void INC16_BC();
    void INC16_DE();
    void INC16_HL();
    void INC16_SP();
#pragma endregion Increments 16-bit register by one.

    //Generic version. Inlined.
    // Decrements combined 16-bit register by one.
    // @param r2  A combined 16-bit register to decrement.
    void DEC16_r2(unsigned char & highByte, unsigned char & lowByte);
#pragma region 16-bit DEC ops
    void DEC16_BC();
    void DEC16_DE();
    void DEC16_HL();
    void DEC16_SP();
#pragma endregion Decrements 16-bit value by one.


    /*------------MISCELLANEOUS--------------*/

    //Generic version. Inlined.
    // Swaps top and lower nybbles of 8-bit register.
    // @param r  An 8-bit register to swap around
    // @post  Zero flag set if result is zero. All other flags reset.
    void SWAP_r(unsigned char & r);
#pragma region SWAP ops
    void SWAP_A();
    void SWAP_B();
    void SWAP_C();
    void SWAP_D();
    void SWAP_E();
    void SWAP_H();
    void SWAP_L();
    void SWAP_pHL();
#pragma endregion Swaps lower and upper nybbles of register.

    // Adjusts register A into BCD. If either nybble > 9, then
    // 6 is added to that nybble. The lower or upper nybble will
    // also be added to if the HALF_CARRY or CARRY flag is set, respectively.
    // @post The carry flag is set if the upper nybble was added to. Half-carry is
    //          reset. Zero flag set if result is zero. Subtract flag is maintained.
    void DAA();

    // Complements accumulator (flips all the bits).
    // @post  Subtract flag and half carry flag are set. Other flags are maintained.
    void CPL();

    // Complements carry flag.
    // @post  Subtract flag and half-carry flag are reset. Zero flag is maintained.
    //          Carry flag is obviously flipped.
    void CCL();

    // Sets the carry flag.
    // @post  Subtract flag and half-carry flag are reset. Zero flag is maintained.
    //          Carry flag is... obviously... set...
    void SCF();

    //Eats a machine cycle and nothing more.
    void NOP();

    // If interrupts are enabled, this will suspend the CPU until the next interrupt
    // occurs. If they are disabled the CPU is not suspended, and the model is not 
    // a Gameboy Color, the next instruction is skipped.
    void HALT();

    // Stops the CPU until a button is pressed. This should also affect the display in
    // a machine dependent way... maybe I'll implement that later.
    void STOP();

    // Disables master interrupt flag following the next instruction
    void DI();

    // Enables master interrupt flag following the next instruction
    void EI();

    /*----------ROTATES AND SHIFTS------------*/
    
    // Rotates accumulator register 1 bit to the left.
    // @post  Previous bit-7 goes into carry flag. Zero flag set
    //        if result is zero. Other flags are reset.
    void RLCA();

    // Rotates accumulator register 1 bit to the left through
    // the carry flag.
    // @post Previous bit-7 goes into carry flag. Zero flag set
    //       if result is zero.
    void RLA();

    // Rotates accumulator register 1 bit to the right.
    // @post Previous bit-0 goes into carry flag. Zero flag set
    //       if result is zero. Other flags are reset.
    void RRCA();

    // Rotates accumulator register 1 bit to the right through
    // the carry flag.
    // @post Previous bit-0 goes into carry flag. Zero flag set
    //       if result is zero. Other flags are reset.
    void RRA();

    // Inline function.
    // Rotates 8-bit register r2 1 bit to the left.
    // @post Previous bit-7 goes into carry flag. Zero flag set
    //       if the result is zero. Other flags are reset.
    void RLC_r2(unsigned char & r2);
#pragma region RLC_r2 ops
    void RLC_A();
    void RLC_B();
    void RLC_C();
    void RLC_D();
    void RLC_E();
    void RLC_H();
    void RLC_L();
    void RLC_pHL();
#pragma endregion Rotates register r2 one bit to the left.

    // Inline function. 
    // Rotates 8-bit register r2 1 bit to the left through carry flag.
    // @post Previous bit-7 goes into carry flag. Zero flag set
    //       if the result is zero. Other flags are reset.
    void RL_r2(unsigned char & r2);
#pragma region RL_r2 ops
    void RL_A();
    void RL_B();
    void RL_C();
    void RL_D();
    void RL_E();
    void RL_H();
    void RL_L();
    void RL_pHL();
#pragma endregion Rotates register r2 one bit to the left through carry flag.

    // Inline function.
    // Rotates 8-bit register r2 1 bit to the right.
    // @post Previous bit-0 goes into carry flag. Zero flag set
    //       if the result is zero. Other flags are reset.
    void RRC_r2(unsigned char & r2);
#pragma region RRC_r2 ops
    void RRC_A();
    void RRC_B();
    void RRC_C();
    void RRC_D();
    void RRC_E();
    void RRC_H();
    void RRC_L();
    void RRC_pHL();
#pragma endregion Rotates register r2 one bit to the right.

    // Rotates 8-bit register r2 1 bit to the right through carry flag.
    // @post Previous bit-0 goes into carry flag. Zero flag set
    //       if the result is zero. Other flags are reset.
    void RR_r2(unsigned char & r2);
#pragma region RR_r2 ops
    void RR_A();
    void RR_B();
    void RR_C();
    void RR_D();
    void RR_E();
    void RR_H();
    void RR_L();
    void RR_pHL();
#pragma endregion Rotates register r2 one bit to the right through carry flag.

    // Performs a 1-bit arithmetic left-shift on 8-bit register r2
    // @post Previous bit-7 goes into carry flag. Zero flag set
    //       if the result is zero. Other flags are reset.
    void SLA_r2(unsigned char & r2);
#pragma region SLA_r2 ops
    void SLA_A();
    void SLA_B();
    void SLA_C();
    void SLA_D();
    void SLA_E();
    void SLA_H();
    void SLA_L();
    void SLA_pHL();
#pragma endregion Shifts register r2 one bit to the left.

    // Performs a 1-bit arithmetic right-shift on 8-bit register r2
    // (the most significant bit is preserved).
    // @post Previous bit-7 goes into carry flag. Zero flag set
    //       if the result is zero. Other flags are reset.
    void SRA_r2(unsigned char & r2);
#pragma region SLA_r2 ops
    void SRA_A();
    void SRA_B();
    void SRA_C();
    void SRA_D();
    void SRA_E();
    void SRA_H();
    void SRA_L();
    void SRA_pHL();
#pragma endregion Shifts register r2 one bit to the right, preserving MSB.

    // Performs a 1-bit logical right-shift on 8-bit register r2
    // (the most significant bit is zeroed).
    // @post Previous bit-7 goes into carry flag. Zero flag set
    //       if the result is zero. Other flags are reset.
    void SRL_r2(unsigned char & r2);
#pragma region SLA_r2 ops
    void SRL_A();
    void SRL_B();
    void SRL_C();
    void SRL_D();
    void SRL_E();
    void SRL_H();
    void SRL_L();
    void SRL_pHL();
#pragma endregion Shifts register r2 one bit to the right, filling MSB with 0.


    /*--------------BIT TESTS-------------*/
    
    // All of the following test a specific bit in a specific register.
    // @post  Zero flag is set if the tested bit is 0.
    //        The subtraction flag is reset.
    //        The The half-carry flag is set.
    //        The carry flag is preserved.

    //Inlined function for bit 0.
    void BIT_r_0(unsigned char r);
#pragma region Bit 0 Test ops
    void BIT_A_0();
    void BIT_B_0();
    void BIT_C_0();
    void BIT_D_0();
    void BIT_E_0();
    void BIT_H_0();
    void BIT_L_0();
    void BIT_pHL_0();
#pragma endregion Tests bit zero of given register.

    //Inlined function for bit 1.
    void BIT_r_1(unsigned char r);
#pragma region Bit 1 Test ops
    void BIT_A_1();
    void BIT_B_1();
    void BIT_C_1();
    void BIT_D_1();
    void BIT_E_1();
    void BIT_H_1();
    void BIT_L_1();
    void BIT_pHL_1();
#pragma endregion Tests bit one of given register.

    //Inlined function for bit 2.
    void BIT_r_2(unsigned char r);
#pragma region Bit 2 Test ops
    void BIT_A_2();
    void BIT_B_2();
    void BIT_C_2();
    void BIT_D_2();
    void BIT_E_2();
    void BIT_H_2();
    void BIT_L_2();
    void BIT_pHL_2();
#pragma endregion Tests bit two of given register.

    //Inlined function for bit 3.
    void BIT_r_3(unsigned char r);
#pragma region Bit 3 Test ops
    void BIT_A_3();
    void BIT_B_3();
    void BIT_C_3();
    void BIT_D_3();
    void BIT_E_3();
    void BIT_H_3();
    void BIT_L_3();
    void BIT_pHL_3();
#pragma endregion Tests bit three of given register.

    //Inlined function for bit 4.
    void BIT_r_4(unsigned char r);
#pragma region Bit 3 Test ops
    void BIT_A_4();
    void BIT_B_4();
    void BIT_C_4();
    void BIT_D_4();
    void BIT_E_4();
    void BIT_H_4();
    void BIT_L_4();
    void BIT_pHL_4();
#pragma endregion Tests bit four of given register.

    //Inlined function for bit 5.
    void BIT_r_5(unsigned char r);
#pragma region Bit 5 Test ops
    void BIT_A_5();
    void BIT_B_5();
    void BIT_C_5();
    void BIT_D_5();
    void BIT_E_5();
    void BIT_H_5();
    void BIT_L_5();
    void BIT_pHL_5();
#pragma endregion Tests bit five of given register.

    //Inlined function for bit 6.
    void BIT_r_6(unsigned char r);
#pragma region Bit 6 Test ops
    void BIT_A_6();
    void BIT_B_6();
    void BIT_C_6();
    void BIT_D_6();
    void BIT_E_6();
    void BIT_H_6();
    void BIT_L_6();
    void BIT_pHL_6();
#pragma endregion Tests bit six of given register.

    //Inlined function for bit 7.
    void BIT_r_7(unsigned char r);
#pragma region Bit 7 Test ops
    void BIT_A_7();
    void BIT_B_7();
    void BIT_C_7();
    void BIT_D_7();
    void BIT_E_7();
    void BIT_H_7();
    void BIT_L_7();
    void BIT_pHL_7();
#pragma endregion Tests bit seven of given register.

};