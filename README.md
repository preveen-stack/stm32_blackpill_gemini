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
- **Internal Temperature Sensor:** Periodically read and display the MCU's internal temperature via ADC1.
- **Multi-Channel ADC Reading:** Read all 10 available external ADC channels (PA0-PA7, PB0-PB1) and display their raw values.
- **SysTick Timer:** Used for precise millisecond delays and system uptime tracking.

## Hardware Connections

- **USART1 TX:** PA9 -> RX of USB-UART Adapter
- **USART1 RX:** PA10 -> TX of USB-UART Adapter
- **Onboard LED:** PC13 (Toggles every second as a heartbeat)

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

### Commit: 3ec8920 - Update README with Sync guide
```text
[24/04/2026 13:40:24] Heartbeat
[24/04/2026 13:40:25] Heartbeat
[24/04/2026 13:40:26] Heartbeat
```

### Commit: 29796e7 - Add Internal Temperature Sensor
```text
[24/04/2026 13:51:04] Heartbeat | CPU Temp: 33.000 C
[24/04/2026 13:51:05] Heartbeat | CPU Temp: 33.400 C
```

### Commit: a0534cc - Add Multi-Channel ADC Support
```text
[24/04/2026 13:54:20] --- System Status ---
[24/04/2026 13:54:20] CPU Temp: 33.000 C
[24/04/2026 13:54:20] ADC Pins: CH0:4095 CH1:1234 CH2:567 CH3:0 CH4:0 CH5:0 CH6:0 CH7:0 CH8:0 CH9:0
```

## Project History
This project was developed iteratively using the **Gemini CLI** interactive agent. Every commit in the history reflects a verified step in the development lifecycle, from basic blinking to complex peripheral integration.

---
*Created using gemini 0.39.1 (LLM: gemini-2.0-flash)*
