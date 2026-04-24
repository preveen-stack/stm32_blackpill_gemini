#include <stdint.h>

extern uint32_t _estack;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _la_data;
extern uint32_t _sbss;
extern uint32_t _ebss;

void Reset_Handler(void);
void Default_Handler(void);
void SysTick_Handler(void);
extern int main(void);

/* Minimal vector table */
__attribute__((section(".isr_vector")))
uint32_t vectors[] = {
    (uint32_t)&_estack,      /* 0: Stack pointer */
    (uint32_t)&Reset_Handler, /* 1: Reset handler */
    (uint32_t)&Default_Handler, /* 2: NMI */
    (uint32_t)&Default_Handler, /* 3: HardFault */
    (uint32_t)&Default_Handler, /* 4: MemManage */
    (uint32_t)&Default_Handler, /* 5: BusFault */
    (uint32_t)&Default_Handler, /* 6: UsageFault */
    0, 0, 0, 0,             /* 7-10: Reserved */
    (uint32_t)&Default_Handler, /* 11: SVCall */
    (uint32_t)&Default_Handler, /* 12: DebugMonitor */
    0,                      /* 13: Reserved */
    (uint32_t)&Default_Handler, /* 14: PendSV */
    (uint32_t)&SysTick_Handler  /* 15: SysTick */
};

void Reset_Handler(void) {
    uint32_t *pSrc = (uint32_t *)&_la_data;
    uint32_t *pDst = (uint32_t *)&_sdata;
    while (pDst < (uint32_t *)&_edata) {
        *pDst++ = *pSrc++;
    }
    pDst = (uint32_t *)&_sbss;
    while (pDst < (uint32_t *)&_ebss) {
        *pDst++ = 0;
    }

    main();
    while (1);
}

void Default_Handler(void) {
    while (1);
}
