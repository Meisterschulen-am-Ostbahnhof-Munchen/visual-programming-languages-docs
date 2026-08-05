# 🔌 IORevPiCore
<img width="1374" height="243" alt="image" src="https://github.com/user-attachments/assets/482b592e-e1f6-4624-bb90-2a332f3aa7df" />
* * * * * * * * * *
## Introduction
The IORevPiCore function block serves as the core module for the Revolution Pi hardware from KUNBUS GmbH. It enables basic communication and configuration of the Revolution Pi I/O modules within a 4diac-based control application.
![IORevPiCore](IORevPiCore.svg)

## Interface Structure

### **Event Inputs**
- **INIT**: Initialization event to activate the function block

### **Event Outputs**
- **INITO**: Confirmation of successful initialization
- **IND**: Indication event for status changes of resources

### **Data Inputs**
- **QI** (BOOL): Event input qualifier
- **UpdateInterval** (UINT): Update interval in Hz (default: 25)

### **Data Outputs**
- **QO** (BOOL): Event output qualifier
- **STATUS** (WSTRING): Service status as a Unicode string

### **Adapters**
- **BusAdapterOut**: Output adapter for Revolution Pi bus communication (Type: eclipse4diac::io::revpi::IORevPiBusAdapter)

## Functionality
The The IORevPiCore block initiates communication with the Revolution Pi hardware upon receiving the INIT event. After successful initialization, INITO is output with the corresponding status. The block continuously monitors the hardware state and outputs IND events when changes occur. The UpdateInterval determines the sampling rate for hardware monitoring.

```
## Technical Features
- Standard update interval of 25 Hz
- Unicode string output for status information
- Integration via a specific bus adapter for Revolution Pi hardware
- Automatic hardware detection and initialization

## State Overview

1. **Inactive**: Block awaits INIT event

2. **Initialization**: Processing configuration parameters

3. **Active**: Monitoring Revolution Pi hardware and outputting IND events upon status changes

## Application Scenarios
- Controlling Revolution Pi I/O modules in industrial automation solutions
- Integrating Revolution Pi hardware into 4diac-based control systems
- Monitoring and diagnostics of Revolution Pi components

## ⚖️ Comparison with Similar Blocks
Compared to generic I/O blocks, IORevPiCore offers specific optimizations for the Revolution Pi hardware platform, including specialized bus communication and hardware-level configuration parameters.

## Conclusion

The IORevPiCore function block provides a reliable and easy-to-configure interface for integrating Revolution Pi hardware into 4diac-based automation solutions. Its standardized interface and flexible configuration options enable efficient integration of industrial I/O components.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
