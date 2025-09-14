#ifndef __KERNEL_ISR_H_
#define __KERNEL_ISR_H_

#include <stdint.h>

#define ISR_GATE_INT	0xE
#define ISR_GATE_TRAP	0xF
#define ISR_DPL_R0	0x0
#define ISR_DPL_R3	0x3
#define ISR_NO_IST	0x0
#define ISR_IST_DF	0x1

struct registers {
    // General purpose registers (pushed first)
    uint64_t rax, rbx, rcx, rdx, rsi, rdi, rbp;
    uint64_t r8, r9, r10, r11, r12, r13, r14, r15;
    
    // Segment registers (pushed next)
    uint64_t ds, es, fs, gs;
    
    // Interrupt number and error code (pushed by ISR)
    uint64_t int_no, err_code;
    
    // CPU automatically pushes these on interrupt
    uint64_t rip, cs, rflags, rsp, ss;
};

void init_isr(void);

#endif
