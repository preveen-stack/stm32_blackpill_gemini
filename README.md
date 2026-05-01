# STM32F411 Blackpill Bare-Metal Project

A bare-metal C project for the STM32F411CEU6 (Blackpill) development board, developed with the assistance of Gemini CLI.

## New Feature: Command-Driven Serial Interface

The system now features a robust, case-insensitive command-line interface over USART1 (115200 baud).

### Available Commands

- **HELP**: Displays the help menu with all available commands.
- **STATUS**: Shows a complete system report (Clock, Temp, ADC).
- **CLOCK**: Displays detailed clock configuration and measured frequency in Hz.
- **TEMP**: Reads and displays the MCU internal temperature.
- **ADC**: Shows a formatted 2x5 table of current ADC readings.
- **I2C**: Displays I2C1 pin info and bus frequency.
- **I2C DETECT**: Scans the I2C1 bus for connected devices.
- **I2C FREQ <hz>**: Sets I2C frequency (e.g., `100000` or `400000`).
- **I2C AUTO**: Automatically selects the best bus speed.
- **MCP DUMP <addr>**: Dumps all 22 registers of an MCP23017 I/O expander.
- **LSM INIT/ACC/MAG/ROLL**: Full control for LSM303 accelerometer and magnetometer.
- **SPI INIT/CS/XFER**: Direct control over the SPI1 peripheral.
- **I2S INIT/TONE <f>**: Initialize I2S2 and generate audio test tones.
- **PWM INIT/SET/FREQ**: Control PA8 PWM output (TIM1_CH1).
- **ROLL**: Toggle periodic 5-second system status updates.
- **RESET**: Perform a standard software reboot.
- **HARDRESET**: Mimic a power cycle by clearing the RTC/Backup Domain and resetting.

## Hardware Support

- **USART1:** PA9 (TX), PA10 (RX) @ 115200 8N1.
- **I2C1:** PB6 (SCL), PB7 (SDA) - Includes detection and sensor drivers.
- **SPI1:** PA5 (SCK), PA6 (MISO), PA7 (MOSI), PA4 (CS).
- **I2S2:** PB12 (WS), PB13 (CK), PB15 (SD) - 44.1kHz / 16-bit audio.
- **PWM:** PA8 (TIM1_CH1) - Adjustable frequency and duty cycle.
- **LED:** PC13 - Heartbeat and status indicator.

## Commit Console Logs (Recent Samples)

### Commit: de3b7ec - Command Interface
```text
[01/01/2000 00:00:10] --- System Status ---
  System Clock: PLL | Measured: 96000123 Hz
  CPU Temp: 33.400 C
  ADC Channels:
  CH0:1152  CH1:1030  CH2:984   CH3:1004  CH4:1031  
  CH5:1000  CH6:1028  CH7:976   CH8:991   CH9:1030 
Type 'HELP' for available commands.
```

### Commit: a9f5d1b - MCP23017 Support
```text
[01/01/2000 00:00:25] --- MCP23017 Registers at 0x20 ---
  0x00 (IODIRA): 0xff
  0x01 (IODIRB): 0xff
  ...
  0x12 (GPIOA ): 0x00
  0x13 (GPIOB ): 0x00
```

### Commit: c22bd20 - LSM303 Support
```text
[01/01/2000 00:00:45] [0x19] LSM303 Accel: X=-124 Y=42 Z=16380
[01/01/2000 00:00:46] [0x1E] LSM303 Mag: X=342 Y=-120 Z=55
```

### Commit: 2eb6930 - I2S Audio Tone
```text
[01/01/2000 00:01:05] Generating 440 Hz Square Wave (5s)...
[01/01/2000 00:01:10] Tone finished.
```

## Project History
This project was developed iteratively using the **Gemini CLI** interactive agent. Every feature, from the initial bare-metal startup to the complex I2S and command parsing, was implemented and verified through a structured development lifecycle.

---
*Created using gemini 0.39.1 (LLM: gemini-2.0-flash)*
