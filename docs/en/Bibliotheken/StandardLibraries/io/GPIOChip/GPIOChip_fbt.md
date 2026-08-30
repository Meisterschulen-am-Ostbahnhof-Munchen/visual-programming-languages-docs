# GPIOChip

<img width="1343" height="245" alt="image" src="https://github.com/user-attachments/assets/612f184c-bce3-4376-bb09-9881ec2162c0" />
* * * * * * * * * *
## Introduction

The GPIOChip function block is a service interface function block for controlling GPIO chips under Linux systems. It enables access to GPIO lines via the Linux GPIO Character Device Interface (/dev/gpiochipX) and supports various operating modes for reading and writing GPIO signals.

## Interface Structure

### **Event Inputs**

- **INIT**: Service initialization event with the associated data QI, VALUE, ChipNumber, LineNumber, ReadWriteMode, BiasMode, and ActiveLow

### **Event Outputs**

- **INITO**: Initialization confirmation with QO and STATUS
- **IND**: Resource indication with QO and STATUS

### **Data Inputs**

- **QI** (BOOL): Event Input Qualifier
- **VALUE** (WSTRING): Receiver IX/QX block name
- **ChipNumber** (UINT): ID of the /dev/gpiochipX device (initial value: 0)
- **LineNumber** (UINT): ID of the GPIO line within the selected chip (initial value: 0)
- **ReadWriteMode** (UINT): Read/write mode of the line (0=read, 1=write) push/pull, 2=open drain, 3=open source) (Initial value: 0)
- **BiasMode** (UINT): Bias mode of the line (0=none, 1=pull up, 2=pull down) (Initial value: 0)
- **ActiveLow** (BOOL): True when logic 1 corresponds to low voltage (Initial value: 0)

### **Data Outputs**

- **QO** (BOOL): Event Output Qualifier
- **STATUS** (WSTRING): Service Status

### **Adapter**

No adapter interfaces available.

## Functionality

Upon receiving the INIT event, the GPIOChip FB initializes a connection to a specific GPIO chip and a defined GPIO line. The configuration includes the operating mode (read/write), the bias mode, and the polarity setting (ActiveLow). After successful initialization, the block confirms with INITO+; in case of errors, it confirms with INITO- and a corresponding STATUS.
...

## Technical Features

- Supports various GPIO operating modes: Read, Write (Push/Pull), Open Drain, and Open Source
- Configurable bias settings: None, Pull-Up, Pull-Down
- Active-Low mode for inverted logic
- Linux GPIO Character Device Interface based
- Automatic error handling with status feedback

## State Overview

The function block goes through the following states:

1. **Not Initialized**: Initial state before INIT
2. **Initialization**: During GPIO chip configuration
3. **Ready**: After successful initialization (INITO+)
4. **Error**: In case of initialization errors (INITO-)

## Application Scenarios

- Controlling GPIO pins in embedded Linux systems
- Low-level I/O operations in automation systems
- Interface to external sensors and actuators
- Prototyping and development of IoT devices
- Industrial control applications

## ⚖️ Comparison with similar Building Blocks

Compared to simple digital I/O blocks, GPIOChip offers advanced features such as configurable bias modes, various write modes, and direct access to the Linux GPIO subsystem. It is specifically designed for Linux systems with GPIOChip support.

## Conclusion

The GPIOChip functional block provides a powerful interface for GPIO hardware control under Linux. Its extensive configurability and standardized service interface make it ideal for demanding embedded applications that require direct hardware access.
