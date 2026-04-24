#include <stdint.h>

/* Peripheral base addresses */
#define RCC_BASE      0x40023800
#define GPIOC_BASE    0x40020800

/* Register offsets */
#define RCC_AHB1ENR   (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define GPIOC_MODER   (*(volatile uint32_t *)(GPIOC_BASE + 0x00))
#define GPIOC_ODR     (*(volatile uint32_t *)(GPIOC_BASE + 0x14))

/* Bit positions */
#define GPIOCEN       (1 << 2)
#define PIN13         (1 << 13)

void delay(uint32_t count) {
    for (volatile uint32_t i = 0; i < count; i++);
}

int main(void) {
    /* 1. Enable GPIOC clock in RCC */
    RCC_AHB1ENR |= GPIOCEN;

    /* 2. Configure PC13 as output (01 in MODER) */
    /* Clear bits 27:26 and then set bit 26 */
    GPIOC_MODER &= ~(3 << (13 * 2));
    GPIOC_MODER |=  (1 << (13 * 2));

    while (1) {
        /* Set LED OFF (PC13 = 1) */
        GPIOC_ODR |= PIN13;
        delay(2000000);
        /* Set LED ON (PC13 = 0) */
        GPIOC_ODR &= ~PIN13;
        delay(2000000);
    }

    return 0;
}
