#include "idt.h"
#include <stdint.h> // uintptr_t instead of u32 

void set_idt_gate(int n, u32 handler) {
    idt[n].low_offset = low_16(handler);
    idt[n].sel = KERNEL_CS;
    idt[n].always0 = 0;
    idt[n].flags = 0x8E; 
    idt[n].high_offset = high_16(handler);
}

void set_idt() {
//    idt_reg.base = (u32)&idt;
    idt_reg.base = (uintptr_t)&idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;
    /* Don't make the mistake of loading &idt -- always load &idt_reg */
    __asm__ __volatile__("lidt (%0)" : : "r" (&idt_reg));
}

// just analysation purpose uncomment below lines ad check : 
/*
int main() {
    // Call set_idt or other functions for testing
    set_idt();
    return 0;
}

*/
