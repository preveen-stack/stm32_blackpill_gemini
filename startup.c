#include <stdint.h>

extern uint32_t _estack;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _la_data;
extern uint32_t _sbss;
extern uint32_t _ebss;

void Reset_Handler(void);
void Default_Handler(void);
extern int main(void);

/* Minimal vector table */
__attribute__((section(".isr_vector")))
uint32_t vectors[] = {
    (uint32_t)&_estack,      /* Stack pointer */
    (uint32_t)&Reset_Handler /* Reset handler */
};

void Reset_Handler(void) {
    /* Copy .data from Flash to RAM */
    uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
    uint8_t *pDst = (uint8_t *)&_sdata;
    uint8_t *pSrc = (uint8_t *)&_la_data;
    for (uint32_t i = 0; i < size; i++) {
        *pDst++ = *pSrc++;
    }

    /* Initialize .bss with zero */
    size = (uint32_t)&_ebss - (uint32_t)&_sbss;
    pDst = (uint8_t *)&_sbss;
    for (uint32_t i = 0; i < size; i++) {
        *pDst++ = 0;
    }

    /* Call main */
    main();

    /* Infinite loop if main returns */
    while (1);
}

void Default_Handler(void) {
    while (1);
}
