# PLC01A1

<img width="1073" height="540" alt="image" src="https://github.com/user-attachments/assets/5a5bf23e-8741-4ccf-8f3d-aac2afba49b1" />

* * * * * * * * * *

## Introduction

The PLC01A1 function block serves as an interface for accessing the inputs and outputs of the PLC01A1 module. This block enables the control of 8 digital outputs and the reading of 8 digital inputs via a standardized 4diac interface.


## Interface Structure

### **Event Inputs**

- **INIT**: Service Initialization Event

- Linked to: QI, UpdateInterval, IN1-IN8, OUT1-OUT8

### **Event Outputs**

- **INITO**: Initialization Acknowledgement

- Linked to: QO, STATUS

- **IND**: Resource Indication

- Linked to: QO, STATUS

### **Data Inputs**

- **QI** (BOOL): Event Input Qualifier
- **IN1-IN8** (WSTRING): 8 Digital Inputs
- **OUT1-OUT8** (WSTRING): 8 Digital Outputs
- **UpdateInterval** (UINT): Update Interval in Hz (Initial Value: 25)

### **Data Outputs**

- **QO** (BOOL): Event Output Qualifier
- **STATUS** (WSTRING): Service Status Information

### **Adapter**

No adapter interfaces available.

## Functionality

The PLC01A1 function block initializes the hardware interface upon receiving the INIT event. After successful initialization, the INITO event is output. The block continuously monitors inputs IN1-IN8 and updates outputs OUT1-OUT8 according to the configuration. The update interval can be adjusted using the UpdateInterval parameter.


## Technical Features

- Uses WSTRING data type for all inputs/outputs
- Configurable update interval (default: 25 Hz)
- Separate initialization and operating states
- Status feedback via STATUS output

## State Overview

1. **Not Initialized**: Waits for INIT event

2. **Initialization**: Processes INIT with configuration data

3. **Operation**: Monitors inputs and controls outputs
4. **Error**: Outputs error status via STATUS

## Application Scenarios

- Connecting PLC01A1 hardware to 4diac controllers
- Digital signal processing in automation systems
- I/O management in distributed control systems
- Prototype development with PLC01A1 modules

## ⚖️ Comparison with Similar Components

Compared to generic I/O components, PLC01A1 offers specific customization for the PLC01A1 module with Eight predefined inputs and eight outputs. The use of WSTRING enables flexible data representation, but differs from typical BOOL-based I/O blocks.

## Conclusion

The PLC01A1 function block provides a reliable and configurable interface for PLC01A1 hardware in 4diac-based control systems. Thanks to the clear separation of the initialization and operating phases, as well as the configurable update rate, the block is suitable for both real-time applications and general automation tasks.

--

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]