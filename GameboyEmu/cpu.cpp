#include "mmu.h"
#include "cpu.h"

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
    lastStepClk(0),
    IME(true),
    IMETransitionCounter(-1),
    halted(false),
    stopped(false)
{}


