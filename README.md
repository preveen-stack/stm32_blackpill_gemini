# STM32F411 Blackpill Bare-Metal Project

A bare-metal C project for the STM32F411CEU6 (Blackpill) development board, developed with the assistance of Gemini CLI.

## Features Implemented

- **Bare-Metal Startup:** Custom `startup.c` with vector table, memory initialization (.data and .bss), and reset handler.
- **Clock Configuration:** System clock configured to **96MHz** using the PLL, with an automatic fallback logic (HSE 25MHz crystal preferred, HSI 16MHz internal oscillator as fallback).
- **UART Logging:** Bidirectional UART communication on **USART1 (PA9 TX, PA10 RX)** at 115200 baud.
- **RTC (Real-Time Clock):** 
    - RTC enabled with **LSE (32.768kHz)** and fallback to **LSI (32kHz)**.
    - Full date and time support.
- **Timestamped Logger:** Custom `Logger_Log` function that prepends every message with an RTC-sourced datetimestamp: `[DD/MM/YYYY HH:MM:SS]`.
- **UART Time Sync:** Synchronize the RTC by sending a 15-character command over UART: `TYYYYMMDDHHMMSS` (e.g., `T20260424134500`).
- **UART System Reset:** Remotely trigger a system reboot by sending the string `RESET` over UART.
- **Internal Temperature Sensor:** Periodically read and display the MCU's internal temperature via ADC1.
- **Multi-Channel ADC with DMA:** Background scanning of 11 channels (10 external pins + 1 internal temperature) using **DMA2 Stream 0**, ensuring zero CPU overhead for data acquisition.
- **System Clock Measurement:** Accurately measure the actual CPU frequency using the RTC as a reference and log the full clock tree configuration (System Clock Source, PLL source, PLL parameters, Oscillator readiness) periodically.
- **PWM Generation:** Configured **TIM1 Channel 1 (PA8)** for 375kHz PWM output with variable duty cycle.
- **Startup Banner:** Displays a stylized ASCII banner upon system reset.
- **Hardware CRC32 Benchmarking:** Benchmark and validate the hardware CRC peripheral against a software implementation, logging processing cycles and speedup ratios.
- **Reset Reason Detection:** Detects and logs the cause of the last system reset (e.g., Pin Reset, Power-on Reset, Software Reset, Watchdog).
- **DSP Benchmarking (FPU & SIMD):** 
    - Benchmarks 32-bit floating point performance using the on-chip **FPU**.
    - Benchmarks 16-bit integer **SIMD (Single Instruction Multiple Data)** using the `SMLAD` instruction.
    - Validates results and logs processing cycles and speedup ratios.
- **SysTick Timer:** Used for precise millisecond delays and system uptime tracking.

## Hardware Connections

- **USART1 TX:** PA9 -> RX of USB-UART Adapter
- **USART1 RX:** PA10 -> TX of USB-UART Adapter
- **PWM Output:** PA8 (TIM1_CH1)
- **Onboard LED:** PC13 (Toggles every second as a heartbeat)
- **Analog Inputs:** PA0-PA7, PB0-PB1

## Building and Flashing

### Prerequisites
- `arm-none-eabi-gcc` toolchain
- `st-link` utilities (for flashing via ST-Link) or `dfu-util` (for USB flashing)

### Commands
- **Build:** `make`
- **Clean:** `make clean`
- **Flash (ST-Link):** `make flash-stlink`
- **Flash (DFU):** `make flash-dfu`

## Time Synchronization via UART

The system clock can be synchronized by sending a specific 15-character string through the UART (USART1).

**Command Format:** `TYYYYMMDDHHMMSS`
- `T`: Header character
- `YYYY`: Year (e.g., 2026)
- `MM`: Month (01-12)
- `DD`: Day (01-31)
- `HH`: Hour (00-23)
- `MM`: Minute (00-59)
- `SS`: Second (00-59)

**Example:**
To set the time to April 24, 2026, at 14:30:00, send:
`T20260424143000`

The board will respond with `RTC Sync Successful!` and the logger will reflect the new time on the next heartbeat.

## Commit Console Logs

### Commit: 6fe9553 - Add UART System Reset
```text
[27/04/2026 14:21:05] --- Periodic Status ---
[27/04/2026 14:21:05] Reset Reason: Software Reset
[27/04/2026 14:21:05] --- Clock Status ---
```

### Commit: 32912e2 - CRC Benchmarking and Validation
```text
[24/04/2026 15:43:29] --- CRC Benchmark (1KB Data) ---
[24/04/2026 15:43:29] HW CRC: 0x6E4461B2 (264 cycles)
[24/04/2026 15:43:29] SW CRC: 0x6E4461B2 (12548 cycles)
[24/04/2026 15:43:29] Speedup: 47.5 x
[24/04/2026 15:43:29] Validation: SUCCESS
```

### Commit: 0d22fc2 - Add DSP Benchmarking (FPU and SIMD)
```text
[24/04/2026 16:05:10] --- DSP Benchmark (256 elements) ---
[24/04/2026 16:05:10] F32 DotProduct: 313410 (4356 cycles)
[24/04/2026 16:05:10] I16 Standard MAC: 1374528 (5380 cycles)
[24/04/2026 16:05:10] I16 SIMD (SMLAD): 1374528 (2054 cycles)
[24/04/2026 16:05:10] SIMD Speedup: 2.6 x
[24/04/2026 16:05:10] DSP Validation: SUCCESS
```

### Commit: 61563e0 - Add Reset Reason Detection
```text
[24/04/2026 16:07:27] --- System Status ---
[24/04/2026 16:07:27] Reset Reason: Pin Reset (NRST)
[24/04/2026 16:07:27] --- Clock Status ---
[24/04/2026 16:07:27] System Clock (SWS): PLL
```

### Commit: c02119d - Detailed Clock Source Status
```text
[24/04/2026 15:04:54] --- System Status ---
[24/04/2026 15:04:54] --- Clock Status ---
[24/04/2026 15:04:54] System Clock (SWS): PLL
[24/04/2026 15:04:54] PLL Source: HSE | PLL Config: M=25 N=192 P=2
[24/04/2026 15:04:54] Oscillators Ready: HSE:1 HSI:1 LSE:1 LSI:0
[24/04/2026 15:04:55] Measured SysClock: 96.000000 MHz
```

### Commit: db40bdb - Enable periodic system clock frequency and configuration logging
```text
[24/04/2026 14:50:35] --- System Status ---
[24/04/2026 14:50:35] --- Clock Status ---
[24/04/2026 14:50:35] Source: HSE | PLL: M=25 N=192 P=2
[24/04/2026 14:50:35] Ready: HSE:1 HSI:1 LSE:1 LSI:0
[24/04/2026 14:50:36] Measured SysClock: 96.000000 MHz
```

### Commit: a9d1111 - Include PWM Frequency in UART log
```text
[24/04/2026 14:18:38] PWM Status: PA8 (TIM1_CH1) Duty: 40% | Freq: 1kHz
```

### Commit: f049529 - Increase PWM Frequency to 375kHz
```text
[24/04/2026 16:18:43] PWM Status: PA8 (TIM1_CH1) Duty: 60% | Freq: 375kHz
```

### Commit: 30f8d6c - Implement PWM generation using TIM1 on PA8
```text
[24/04/2026 14:14:38] --- System Status ---
[24/04/2026 14:14:38] CPU Temp: 32.200 C
[24/04/2026 14:14:38] ADC Pins: CH0:4095 CH1:4095 ...
[24/04/2026 14:14:38] PWM Status: PA8 (TIM1_CH1) Duty: 20%
```

### Commit: d6e5c14 - Add ADC DMA Support
```text
[24/04/2026 14:04:34] --- System Status ---
[24/04/2026 14:04:34] CPU Temp: 32.600 C
[24/04/2026 14:04:34] ADC Pins: CH0:4095 CH1:1234 CH2:567 CH3:0 CH4:0 CH5:0 CH6:0 CH7:0 CH8:0 CH9:0
```

### Commit: 3ec8920 - Update README with Sync guide
```text
[24/04/2026 13:40:24] Heartbeat
[24/04/2026 13:40:25] Heartbeat
[24/04/2026 13:40:26] Heartbeat
```

## Project History
This project was developed iteratively using the **Gemini CLI** interactive agent. Every commit in the history reflects a verified step in the development lifecycle, from basic blinking to complex peripheral integration.

---
*Created using gemini 0.39.1 (LLM: gemini-2.0-flash)*
