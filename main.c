#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

/* Register addresses */
#define RCC_BASE        0x40023800
#define FLASH_R_BASE    0x40023C00
#define GPIOA_BASE      0x40020000
#define GPIOB_BASE      0x40020400
#define GPIOC_BASE      0x40020800
#define USART1_BASE     0x40011000
#define PWR_BASE        0x40007000
#define RTC_BASE        0x40002800

/* RCC Registers */
#define RCC_CR          (*(volatile uint32_t *)(RCC_BASE + 0x00))
#define RCC_PLLCFGR     (*(volatile uint32_t *)(RCC_BASE + 0x04))
#define RCC_CFGR        (*(volatile uint32_t *)(RCC_BASE + 0x08))
#define RCC_AHB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define RCC_APB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x40))
#define RCC_APB2ENR     (*(volatile uint32_t *)(RCC_BASE + 0x44))
#define RCC_BDCR        (*(volatile uint32_t *)(RCC_BASE + 0x70))
#define RCC_CSR         (*(volatile uint32_t *)(RCC_BASE + 0x74))

/* PWR Registers */
#define PWR_CR          (*(volatile uint32_t *)(PWR_BASE + 0x00))

/* RTC Registers */
#define RTC_TR          (*(volatile uint32_t *)(RTC_BASE + 0x00))
#define RTC_DR          (*(volatile uint32_t *)(RTC_BASE + 0x04))
#define RTC_CR_REG      (*(volatile uint32_t *)(RTC_BASE + 0x08))
#define RTC_ISR         (*(volatile uint32_t *)(RTC_BASE + 0x0C))
#define RTC_PRER        (*(volatile uint32_t *)(RTC_BASE + 0x10))
#define RTC_WPR         (*(volatile uint32_t *)(RTC_BASE + 0x24))

#define FLASH_ACR       (*(volatile uint32_t *)(FLASH_R_BASE + 0x00))
#define GPIOA_MODER     (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_AFRH      (*(volatile uint32_t *)(GPIOA_BASE + 0x24))
#define GPIOB_MODER     (*(volatile uint32_t *)(GPIOB_BASE + 0x00))
#define GPIOC_MODER     (*(volatile uint32_t *)(GPIOC_BASE + 0x00))
#define GPIOC_ODR       (*(volatile uint32_t *)(GPIOC_BASE + 0x14))
#define USART1_SR       (*(volatile uint32_t *)(USART1_BASE + 0x00))
#define USART1_DR       (*(volatile uint32_t *)(USART1_BASE + 0x04))
#define USART1_BRR      (*(volatile uint32_t *)(USART1_BASE + 0x08))
#define USART1_CR1      (*(volatile uint32_t *)(USART1_BASE + 0x0C))

/* ADC Registers */
#define ADC1_BASE       0x40012000
#define ADC_COMMON_BASE 0x40012300
#define ADC1_SR         (*(volatile uint32_t *)(ADC1_BASE + 0x00))
#define ADC1_CR1        (*(volatile uint32_t *)(ADC1_BASE + 0x04))
#define ADC1_CR2        (*(volatile uint32_t *)(ADC1_BASE + 0x08))
#define ADC1_SMPR1      (*(volatile uint32_t *)(ADC1_BASE + 0x0C))
#define ADC1_SMPR2      (*(volatile uint32_t *)(ADC1_BASE + 0x10))
#define ADC1_SQR3       (*(volatile uint32_t *)(ADC1_BASE + 0x34))
#define ADC1_DR         (*(volatile uint32_t *)(ADC1_BASE + 0x4C))
#define ADC_CCR         (*(volatile uint32_t *)(ADC_COMMON_BASE + 0x04))

/* TIM1 Registers (Advanced Control Timer for PWM) */
#define TIM1_BASE       0x40010000
#define TIM1_CR1        (*(volatile uint32_t *)(TIM1_BASE + 0x00))
#define TIM1_CCMR1      (*(volatile uint32_t *)(TIM1_BASE + 0x18))
#define TIM1_CCER       (*(volatile uint32_t *)(TIM1_BASE + 0x20))
#define TIM1_PSC        (*(volatile uint32_t *)(TIM1_BASE + 0x28))
#define TIM1_ARR        (*(volatile uint32_t *)(TIM1_BASE + 0x2C))
#define TIM1_CCR1       (*(volatile uint32_t *)(TIM1_BASE + 0x34))
#define TIM1_BDTR       (*(volatile uint32_t *)(TIM1_BASE + 0x44))

/* CRC Registers */
#define CRC_BASE        0x40023000
#define CRC_DR          (*(volatile uint32_t *)(CRC_BASE + 0x00))
#define CRC_IDR         (*(volatile uint32_t *)(CRC_BASE + 0x04))
#define CRC_CR_PERIPH   (*(volatile uint32_t *)(CRC_BASE + 0x08))

/* DMA2 Registers */
#define DMA2_BASE       0x40026400
#define DMA2_S0CR       (*(volatile uint32_t *)(DMA2_BASE + 0x10))
#define DMA2_S0NDTR     (*(volatile uint32_t *)(DMA2_BASE + 0x14))
#define DMA2_S0PAR      (*(volatile uint32_t *)(DMA2_BASE + 0x18))
#define DMA2_S0M0AR     (*(volatile uint32_t *)(DMA2_BASE + 0x1C))
#define DMA2_LISR       (*(volatile uint32_t *)(DMA2_BASE + 0x00))
#define DMA2_LIFCR      (*(volatile uint32_t *)(DMA2_BASE + 0x08))

/* ADC SQR Registers */
#define ADC1_SQR1       (*(volatile uint32_t *)(ADC1_BASE + 0x2C))
#define ADC1_SQR2       (*(volatile uint32_t *)(ADC1_BASE + 0x30))

/* SysTick */
#define STK_CTRL        (*(volatile uint32_t *)0xE000E010)
#define STK_LOAD        (*(volatile uint32_t *)0xE000E014)
#define STK_VAL         (*(volatile uint32_t *)0xE000E018)

/* DWT Registers for Cycle Counting */
#define DWT_CTRL        (*(volatile uint32_t *)0xE0001000)
#define DWT_CYCCNT      (*(volatile uint32_t *)0xE0001004)
#define DEMCR           (*(volatile uint32_t *)0xE000EDFC)
#define CPACR           (*(volatile uint32_t *)0xE000ED88)

volatile uint32_t ms_ticks = 0;
int rtc_ready = 0;
char reset_reason[32] = "Unknown";

void Detect_ResetReason(void) {
    uint32_t csr = RCC_CSR;

    if (csr & (1 << 26)) strcpy(reset_reason, "Pin Reset (NRST)");
    else if (csr & (1 << 27)) strcpy(reset_reason, "Power-on Reset (POR)");
    else if (csr & (1 << 28)) strcpy(reset_reason, "Software Reset");
    else if (csr & (1 << 29)) strcpy(reset_reason, "IWDG Reset");
    else if (csr & (1 << 30)) strcpy(reset_reason, "WWDG Reset");
    else if (csr & (1 << 31)) strcpy(reset_reason, "Low-power Reset");
    else strcpy(reset_reason, "Other/Unknown");

    /* Clear reset flags */
    RCC_CSR |= (1 << 24); // RMVF
}

/* ADC DMA Buffer: 10 external channels + 1 internal temperature */
#define ADC_CHANNELS 11
volatile uint16_t adc_results[ADC_CHANNELS];

void SysTick_Handler(void) {
    ms_ticks++;
}

void Logger_Log(const char *fmt, ...) {
    if (rtc_ready) {
        uint32_t tr = RTC_TR;
        uint32_t dr = RTC_DR;
        int h = ((tr >> 20) & 0x3) * 10 + ((tr >> 16) & 0xF);
        int m = ((tr >> 12) & 0x7) * 10 + ((tr >> 8) & 0xF);
        int s = ((tr >> 4) & 0x7) * 10 + (tr & 0xF);
        int y = ((dr >> 20) & 0xF) * 10 + ((dr >> 16) & 0xF);
        int mon = ((dr >> 12) & 0x1) * 10 + ((dr >> 8) & 0xF);
        int d = ((dr >> 4) & 0x3) * 10 + (dr & 0xF);
        printf("[%02d/%02d/20%02d %02d:%02d:%02d] ", d, mon, y, h, m, s);
    } else {
        printf("[%lu ms] ", ms_ticks);
    }

    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf("\r\n");
}

void delay_ms(uint32_t ms) {
    uint32_t start = ms_ticks;
    while ((ms_ticks - start) < ms);
}

void DWT_Init(void) {
    DEMCR |= (1 << 24); // Enable TRCENA
    DWT_CYCCNT = 0;
    DWT_CTRL |= (1 << 0); // Enable CYCCNT
}

uint32_t Measure_SystemClock(void) {
    if (!rtc_ready) return 0;

    /* Wait for RTC second boundary */
    uint32_t start_tr = RTC_TR;
    while (RTC_TR == start_tr);
    
    uint32_t start_cycles = DWT_CYCCNT;
    
    /* Wait for next RTC second */
    start_tr = RTC_TR;
    while (RTC_TR == start_tr);
    
    uint32_t end_cycles = DWT_CYCCNT;
    return (end_cycles - start_cycles);
}

void Log_ClockConfiguration(void) {
    uint32_t pllcfgr = RCC_PLLCFGR;
    uint32_t cfgr = RCC_CFGR;
    uint32_t m = pllcfgr & 0x3F;
    uint32_t n = (pllcfgr >> 6) & 0x1FF;
    uint32_t p = (((pllcfgr >> 16) & 0x3) + 1) * 2;
    uint32_t pll_src = (pllcfgr >> 22) & 0x1;
    uint32_t sws = (cfgr >> 2) & 0x3;

    const char* sws_str = "Unknown";
    if (sws == 0) sws_str = "HSI";
    else if (sws == 1) sws_str = "HSE";
    else if (sws == 2) sws_str = "PLL";

    Logger_Log("--- Clock Status ---");
    Logger_Log("System Clock (SWS): %s", sws_str);
    Logger_Log("PLL Source: %s | PLL Config: M=%lu N=%lu P=%lu", pll_src ? "HSE" : "HSI", m, n, p);
    
    uint32_t hse_rdy = (RCC_CR >> 17) & 1;
    uint32_t hsi_rdy = (RCC_CR >> 1) & 1;
    uint32_t lse_rdy = (RCC_BDCR >> 1) & 1;
    uint32_t lsi_rdy = (RCC_CSR >> 1) & 1;
    
    Logger_Log("Oscillators Ready: HSE:%d HSI:%d LSE:%d LSI:%d", hse_rdy, hsi_rdy, lse_rdy, lsi_rdy);
    
    uint32_t freq = Measure_SystemClock();
    Logger_Log("Measured SysClock: %lu.%06lu MHz", freq / 1000000, freq % 1000000);
}

void Print_Banner(void) {
    printf("\r\n");
    printf("****************************************************\r\n");
    printf("*                                                  *\r\n");
    printf("*         STM32 BLACKPILL F411 BAREMETAL           *\r\n");
    printf("*                                                  *\r\n");
    printf("*            Created using Gemini CLI              *\r\n");
    printf("*                                                  *\r\n");
    printf("****************************************************\r\n");
    printf("\r\n");
}

static uint8_t to_bcd(uint8_t val) {
    return ((val / 10) << 4) | (val % 10);
}

void RTC_SetDateTime(uint8_t y, uint8_t mon, uint8_t d, uint8_t h, uint8_t min, uint8_t s) {
    RTC_WPR = 0xCA;
    RTC_WPR = 0x53;
    RTC_ISR |= (1 << 7); // INIT
    while (!(RTC_ISR & (1 << 6)));

    RTC_TR = (to_bcd(h) << 16) | (to_bcd(min) << 8) | to_bcd(s);
    RTC_DR = (to_bcd(y) << 16) | (to_bcd(mon) << 8) | to_bcd(d);

    RTC_ISR &= ~(1 << 7);
    RTC_WPR = 0xFF;
}

void RTC_Init(void) {
    RCC_APB1ENR |= (1 << 28);
    PWR_CR |= (1 << 8);

    RCC_BDCR |= (1 << 0);
    uint32_t timeout = 0xFFFFF;
    while (!(RCC_BDCR & (1 << 1)) && --timeout);

    uint32_t prediv_a, prediv_s;
    if (RCC_BDCR & (1 << 1)) {
        RCC_BDCR |= (1 << 8);
        prediv_a = 127;
        prediv_s = 255;
    } else {
        RCC_CSR |= (1 << 0);
        while (!(RCC_CSR & (1 << 1)));
        RCC_BDCR &= ~(3 << 8);
        RCC_BDCR |=  (2 << 8);
        prediv_a = 127;
        prediv_s = 249;
    }

    RCC_BDCR |= (1 << 15);
    RTC_WPR = 0xCA;
    RTC_WPR = 0x53;
    RTC_ISR |= (1 << 7);
    while (!(RTC_ISR & (1 << 6)));
    RTC_PRER = (prediv_a << 16) | prediv_s;
    RTC_ISR &= ~(1 << 7);
    RTC_WPR = 0xFF;
    rtc_ready = 1;
}

void ADC_Init(void) {
    RCC_AHB1ENR |= (1 << 0) | (1 << 1); // Enable GPIOA and GPIOB clocks
    RCC_AHB1ENR |= (1 << 22);           // Enable DMA2 clock
    
    /* Configure PA0-PA7 as Analog */
    GPIOA_MODER |= 0x0000FFFF;
    
    /* Configure PB0-PB1 as Analog */
    GPIOB_MODER |= 0x0000000F;

    RCC_APB2ENR |= (1 << 8);      // Enable ADC1 clock
    ADC_CCR |= (1 << 23);         // TSVREFE: Enable Temp sensor

    /* ADC Configuration: Scan Mode, Continuous Conversion */
    ADC1_CR1 |= (1 << 8);         // SCAN: Scan mode
    ADC1_CR2 |= (1 << 1);         // CONT: Continuous conversion
    ADC1_CR2 |= (1 << 8);         // DMA: Enable DMA
    ADC1_CR2 |= (1 << 9);         // DDS: DMA disable selection (keep DMA on)

    /* Sample time: 480 cycles for all channels */
    ADC1_SMPR2 = 0x3FFFFFFF;      // Channels 0-9
    ADC1_SMPR1 |= (7 << 24);      // Channel 18

    /* Sequence: CH0, CH1, CH2, CH3, CH4, CH5, CH6, CH7, CH8, CH9, CH18 */
    ADC1_SQR1 = ((ADC_CHANNELS - 1) << 20); // L = 11 conversions
    ADC1_SQR3 = (0 << 0) | (1 << 5) | (2 << 10) | (3 << 15) | (4 << 20) | (5 << 25);
    ADC1_SQR2 = (6 << 0) | (7 << 5) | (8 << 10) | (9 << 15) | (18 << 20);

    /* DMA2 Stream 0 Configuration (ADC1 is on Stream 0 Channel 0 or Stream 4 Channel 0) */
    DMA2_S0CR &= ~(1 << 0);       // Disable DMA Stream 0 to configure
    while (DMA2_S0CR & (1 << 0)); // Wait for disable

    DMA2_S0PAR = (uint32_t)&ADC1_DR;
    DMA2_S0M0AR = (uint32_t)adc_results;
    DMA2_S0NDTR = ADC_CHANNELS;

    /* Channel 0, High priority, 16-bit memory & peripheral, Memory increment, Circular mode, Enable */
    DMA2_S0CR = (0 << 25) | (2 << 16) | (1 << 13) | (1 << 11) | (1 << 10) | (1 << 8) | (1 << 0);

    ADC1_CR2 |= (1 << 0);         // ADON: Turn on ADC
    delay_ms(1);
    ADC1_CR2 |= (1 << 30);        // SWSTART: Start first conversion
}

uint32_t ADC_Read(uint8_t channel) {
    if (channel < 10) return adc_results[channel];
    if (channel == 18) return adc_results[10];
    return 0;
}

int32_t ADC_ReadTemp(void) {
    uint32_t val = ADC_Read(18);
    int32_t vsense_mv = (val * 3300) / 4095;
    int32_t temp_mc = (vsense_mv - 760) * 400 + 25000;
    return temp_mc;
}

void PWM_Init(void) {
    /* 1. Enable TIM1 and GPIOA clocks */
    RCC_APB2ENR |= (1 << 0); // TIM1EN
    RCC_AHB1ENR |= (1 << 0); // GPIOAEN

    /* 2. Configure PA8 as Alternate Function AF1 (TIM1_CH1) */
    GPIOA_MODER &= ~(3 << (8 * 2));
    GPIOA_MODER |=  (2 << (8 * 2)); // AF mode
    GPIOA_AFRH  &= ~(0xF << (0 * 4)); // Clear AF for PA8
    GPIOA_AFRH  |=  (1 << (0 * 4));   // AF1

    /* 3. Configure TIM1 for PWM */
    TIM1_PSC = 95;           // Clock = 96MHz / 96 = 1MHz
    TIM1_ARR = 1000;         // Frequency = 1MHz / 1000 = 1kHz
    TIM1_CCR1 = 0;           // Initial Duty Cycle = 0%

    /* PWM mode 1, preload enable */
    TIM1_CCMR1 = (6 << 4) | (1 << 3); 
    /* Enable output on CH1 */
    TIM1_CCER |= (1 << 0);
    /* MOE: Main Output Enable (Required for TIM1) */
    TIM1_BDTR |= (1 << 15);
    /* Enable counter */
    TIM1_CR1 |= (1 << 0);
}

void PWM_SetDutyCycle(uint16_t duty) {
    if (duty > 100) duty = 100;
    TIM1_CCR1 = (duty * 1000) / 100;
}

void CRC_Init(void) {
    RCC_AHB1ENR |= (1 << 12); // CRCEN
}

void FPU_Enable(void) {
    /* Set bits 20-23 to enable CP10 and CP11 coprocessors */
    CPACR |= ((3UL << 10*2) | (3UL << 11*2));
}

float DotProduct_F32(float *a, float *b, uint32_t len) {
    float sum = 0.0f;
    for (uint32_t i = 0; i < len; i++) {
        sum += a[i] * b[i];
    }
    return sum;
}

int32_t DotProduct_I16_Standard(int16_t *a, int16_t *b, uint32_t len) {
    int32_t sum = 0;
    for (uint32_t i = 0; i < len; i++) {
        sum += (int32_t)a[i] * (int32_t)b[i];
    }
    return sum;
}

/* Using Inline Assembly for Cortex-M4 SIMD (SMLAD) */
int32_t DotProduct_I16_SIMD(int16_t *a, int16_t *b, uint32_t len) {
    int32_t sum = 0;
    uint32_t *pA = (uint32_t *)a;
    uint32_t *pB = (uint32_t *)b;
    uint32_t num_blocks = len / 2;

    for (uint32_t i = 0; i < num_blocks; i++) {
        uint32_t valA = *pA++;
        uint32_t valB = *pB++;
        /* SMLAD sum, valA, valB, sum */
        __asm volatile ("smlad %0, %1, %2, %0" : "+r" (sum) : "r" (valA), "r" (valB));
    }
    return sum;
}

void Benchmark_DSP(void) {
    #define DSP_LEN 256
    float fa[DSP_LEN], fb[DSP_LEN];
    int16_t ia[DSP_LEN], ib[DSP_LEN];

    for (int i = 0; i < DSP_LEN; i++) {
        fa[i] = (float)i * 0.123f;
        fb[i] = (float)i * 0.456f;
        ia[i] = (int16_t)i;
        ib[i] = (int16_t)(i % 127);
    }

    Logger_Log("--- DSP Benchmark (%d elements) ---", DSP_LEN);

    /* FPU Benchmark */
    uint32_t start = DWT_CYCCNT;
    float f_res = DotProduct_F32(fa, fb, DSP_LEN);
    uint32_t f_cycles = DWT_CYCCNT - start;
    Logger_Log("F32 DotProduct: %ld (%lu cycles)", (int32_t)f_res, f_cycles);

    /* I16 Standard Benchmark */
    start = DWT_CYCCNT;
    int32_t i_res_std = DotProduct_I16_Standard(ia, ib, DSP_LEN);
    uint32_t i_cycles_std = DWT_CYCCNT - start;
    Logger_Log("I16 Standard MAC: %ld (%lu cycles)", i_res_std, i_cycles_std);

    /* I16 SIMD Benchmark */
    start = DWT_CYCCNT;
    int32_t i_res_simd = DotProduct_I16_SIMD(ia, ib, DSP_LEN);
    uint32_t i_cycles_simd = DWT_CYCCNT - start;
    Logger_Log("I16 SIMD (SMLAD): %ld (%lu cycles)", i_res_simd, i_cycles_simd);

    Logger_Log("SIMD Speedup: %lu.%lu x", i_cycles_std / i_cycles_simd, ((i_cycles_std * 10) / i_cycles_simd) % 10);
    
    if (i_res_std == i_res_simd) {
        Logger_Log("DSP Validation: SUCCESS");
    } else {
        Logger_Log("DSP Validation: FAILED!");
    }
}

uint32_t CRC_Hardware(uint32_t *data, uint32_t len) {
    CRC_CR_PERIPH = 1; // Reset CRC
    for (uint32_t i = 0; i < len; i++) {
        CRC_DR = data[i];
    }
    return CRC_DR;
}

uint32_t CRC_Software(uint32_t *data, uint32_t len) {
    uint32_t crc = 0xFFFFFFFF;
    for (uint32_t i = 0; i < len; i++) {
        crc ^= data[i];
        for (int j = 0; j < 32; j++) {
            if (crc & 0x80000000) crc = (crc << 1) ^ 0x04C11DB7;
            else crc <<= 1;
        }
    }
    return crc;
}

void Benchmark_CRC(void) {
    uint32_t test_data[256];
    for (int i = 0; i < 256; i++) test_data[i] = i * 0x12345678;

    Logger_Log("--- CRC Benchmark (1KB Data) ---");

    uint32_t start = DWT_CYCCNT;
    uint32_t hw_crc = CRC_Hardware(test_data, 256);
    uint32_t hw_cycles = DWT_CYCCNT - start;

    start = DWT_CYCCNT;
    uint32_t sw_crc = CRC_Software(test_data, 256);
    uint32_t sw_cycles = DWT_CYCCNT - start;

    Logger_Log("HW CRC: 0x%08lX (%lu cycles)", hw_crc, hw_cycles);
    Logger_Log("SW CRC: 0x%08lX (%lu cycles)", sw_crc, sw_cycles);
    Logger_Log("Speedup: %lu.%lu x", sw_cycles / hw_cycles, ((sw_cycles * 10) / hw_cycles) % 10);
    
    if (hw_crc == sw_crc) {
        Logger_Log("Validation: SUCCESS");
    } else {
        Logger_Log("Validation: FAILED!");
    }
}

void USART1_Init_Pins(void) {
    RCC_AHB1ENR |= (1 << 0);
    RCC_APB2ENR |= (1 << 4);
    
    /* PA9 (TX), PA10 (RX) -> AF7 */
    GPIOA_MODER &= ~((3 << (9 * 2)) | (3 << (10 * 2)));
    GPIOA_MODER |=  ((2 << (9 * 2)) | (2 << (10 * 2)));
    GPIOA_AFRH  &= ~((0xF << (1 * 4)) | (0xF << (2 * 4)));
    GPIOA_AFRH  |=  ((7 << (1 * 4)) | (7 << (2 * 4)));
}

void USART1_Init_16MHz(void) {
    USART1_Init_Pins();
    USART1_BRR = (8 << 4) | 11;
    USART1_CR1 = (1 << 13) | (1 << 3) | (1 << 2); // UE, TE, RE
}

void USART1_Init_96MHz(void) {
    /* 96MHz / (16 * 115200) = 52.083 -> Mantissa 52, Fraction 1 */
    USART1_BRR = (52 << 4) | 1;
    USART1_CR1 = (1 << 13) | (1 << 3) | (1 << 2); // UE, TE, RE
}

void SystemClock_Config_96MHz(void) {
    RCC_CR |= (1 << 16);
    uint32_t timeout = 0xFFFF;
    while (!(RCC_CR & (1 << 17)) && --timeout);
    int use_hse = (RCC_CR & (1 << 17));
    FLASH_ACR = (1 << 8) | (1 << 9) | (1 << 10) | 3;
    uint32_t pllm = use_hse ? 25 : 16;
    uint32_t plln = 192;
    uint32_t pllp = 0;
    RCC_PLLCFGR = (pllm << 0) | (plln << 6) | (pllp << 16) | (use_hse ? (1 << 22) : (0 << 22));
    RCC_CR |= (1 << 24);
    while (!(RCC_CR & (1 << 25)));
    RCC_CFGR |= (0 << 4) | (4 << 10) | (0 << 13);
    RCC_CFGR |= (2 << 0);
    while ((RCC_CFGR & (3 << 2)) != (2 << 2));
}

void uart_putc(char c) {
    while (!(USART1_SR & (1 << 7)));
    USART1_DR = c;
}

int _write(int file, char *ptr, int len) {
    for (int i = 0; i < len; i++) {
        uart_putc(ptr[i]);
    }
    return len;
}

char rx_buffer[32];
int rx_index = 0;

void Process_UART(void) {
    while (USART1_SR & (1 << 5)) { // RXNE
        char c = USART1_DR;
        /* Echo back for debugging */
        uart_putc(c); 
        
        if (c == '\r' || c == '\n') {
            rx_buffer[rx_index] = '\0';
            if (rx_index == 15 && rx_buffer[0] == 'T') {
                /* Format: TYYYYMMDDHHMMSS */
                int y, mon, d, h, m, s;
                char tmp[5];
                
                tmp[0] = rx_buffer[1]; tmp[1] = rx_buffer[2]; tmp[2] = rx_buffer[3]; tmp[3] = rx_buffer[4]; tmp[4] = '\0';
                y = atoi(tmp) - 2000;
                tmp[0] = rx_buffer[5]; tmp[1] = rx_buffer[6]; tmp[2] = '\0';
                mon = atoi(tmp);
                tmp[0] = rx_buffer[7]; tmp[1] = rx_buffer[8]; tmp[2] = '\0';
                d = atoi(tmp);
                tmp[0] = rx_buffer[9]; tmp[1] = rx_buffer[10]; tmp[2] = '\0';
                h = atoi(tmp);
                tmp[0] = rx_buffer[11]; tmp[1] = rx_buffer[12]; tmp[2] = '\0';
                m = atoi(tmp);
                tmp[0] = rx_buffer[13]; tmp[1] = rx_buffer[14]; tmp[2] = '\0';
                s = atoi(tmp);

                RTC_SetDateTime(y, mon, d, h, m, s);
                Logger_Log("RTC Sync Successful!");
            }
            rx_index = 0;
        } else if (rx_index < 31) {
            rx_buffer[rx_index++] = c;
        }
    }
}

int main(void) {
    Detect_ResetReason();
    FPU_Enable();
    USART1_Init_16MHz();
    Print_Banner();
    
    SystemClock_Config_96MHz();
    USART1_Init_96MHz();

    STK_LOAD = 96000000 / 1000 - 1;
    STK_VAL = 0;
    STK_CTRL = 0x07;

    RTC_Init();
    ADC_Init();
    DWT_Init();
    PWM_Init();
    CRC_Init();

    Logger_Log("System online. Send TYYYYMMDDHHMMSS to sync time.");
    Log_ClockConfiguration();
    Benchmark_CRC();
    Benchmark_DSP();

    RCC_AHB1ENR |= (1 << 2);
    GPIOC_MODER &= ~(3 << (13 * 2));
    GPIOC_MODER |=  (1 << (13 * 2));

    uint32_t last_blink = 0;
    uint16_t duty = 0;
    while (1) {
        Process_UART();
        
        if ((ms_ticks - last_blink) >= 5000) { // Benchmark every 5 seconds
            GPIOC_ODR ^= (1 << 13);
            Logger_Log("--- System Status ---");
            Logger_Log("Reset Reason: %s", reset_reason);
            Log_ClockConfiguration();
            int32_t temp_mc = ADC_ReadTemp();
            Logger_Log("CPU Temp: %ld.%03ld C", temp_mc / 1000, temp_mc % 1000);
            
            char adc_msg[128];
            char *p = adc_msg;
            p += sprintf(p, "ADC Pins: ");
            for (int i = 0; i < 10; i++) {
                uint32_t val = ADC_Read(i);
                p += sprintf(p, "CH%d:%lu ", i, val);
            }
            Logger_Log("%s", adc_msg);

            /* Vary PWM duty cycle */
            duty = (duty + 20) % 110;
            PWM_SetDutyCycle(duty);
            Logger_Log("PWM Status: PA8 (TIM1_CH1) Duty: %d%% | Freq: 1kHz", duty);

            /* Run benchmarks */
            Benchmark_CRC();
            Benchmark_DSP();
            
            last_blink = ms_ticks;
        }
    }
}
