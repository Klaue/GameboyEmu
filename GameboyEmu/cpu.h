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
	unsigned long long last_step_clk;

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
			Instruction Set Implementation.
    ===============================================*/

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

	/*------------MISCELLANEOUS--------------*/
	//No operation
	void NOP();


};