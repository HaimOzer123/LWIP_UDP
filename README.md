# LWip - RT UDP ARM cortex UUT [STM32F756ZG]
# Haim Ozer - ID 316063569 | 05/12/24
## Overview

The UUT LWip UDP STM32 system is designed for executing hardware tests on various peripherals through UDP communication. It provides a seamless interface for testing UART, ADC, Timer, SPI, and I2C peripherals in real time.

The system listens for commands over a UDP server, executes the specified tests, and sends results back to the client.

---

![System Block Diagram Overview](https://drive.google.com/uc?export=view&id=1wlZdoFJPnCu5fi6q38DZnlvbr0gjZuHI)

## Features

- **UDP Server**:
  - Listens on port `50007` for incoming test commands.
  - Responds with test results after execution.

- **Supported Peripherals**:
  - **UART**: Data transmission and reception tests.
  - **ADC**: Analog-to-digital conversion validation.
  - **Timer**: Timer synchronization and accuracy tests.
  - **SPI**: Serial Peripheral Interface communication tests.
  - **I2C**: Inter-Integrated Circuit communication tests.

- **Real-Time Communication**:
  - Handles incoming commands and executes tests in a continuous loop.

---

## System Configuration

### Network Settings

| Parameter      | Value               |
|----------------|---------------------|
| **IP Address** | `192.168.7.2`       |
| **Netmask**    | `255.255.255.0`     |
| **Gateway**    | `192.168.7.1`       |
| **Port**       | `50007`             |

> **Note**: The Gateway is not actively used but is required by the IDE.

### Hardware Connections

#### UART Test Connections
- **TX5 (PC_12)** → **RX2 (PD_6)**
- **RX5 (PD_2)** → **TX2 (PD_5)**

#### Timer Test
- Ensure both `TIM3` and `TIM2` are configured for periodic interrupts in CubeMX.

#### SPI Test Connections
- **SPI1 (Master)**:
  - `PA5 (SCK)` ↔ `PB10 (SCK)`
  - `PA6 (MISO)` ↔ `PC2 (MISO)`
  - `PB5 (MOSI)` ↔ `PC3 (MOSI)`
- **SPI2 (Slave)**:
  - `PB10 (SCK)` ↔ `PA5 (SCK)`
  - `PC2 (MISO)` ↔ `PA6 (MISO)`
  - `PC3 (MOSI)` ↔ `PB5 (MOSI)`

#### I2c Test Connections
 - I2C2-SDA [PF0] <--> I2C4-SDA [PF15]
 - I2C2-SCL [PF1] <--> I2C4-SCL [PF14]
---

