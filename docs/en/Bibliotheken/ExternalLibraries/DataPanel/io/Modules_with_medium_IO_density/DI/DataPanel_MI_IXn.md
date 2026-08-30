# DataPanel_MI_IXn

![DataPanel_MI_IXn](./DataPanel_MI_IXn.svg)

* * * * * * * * * *
## Introduction

The DataPanel_MI_IXn function block is a service-oriented input block for digital binary inputs (ground switching / NPN). It is used to read a single Boolean input signal from a DataPanel system via the MI (Module Interface) protocol. The block is typically used in the 4diac IDE to connect field devices such as switches or sensors.
## Interface Structure

### **Event Inputs**

- **INIT** (EInit): Initializes the block. The parameters QI, PARAMS, u8SAMember, and Input are passed.
- **REQ** (Event): Requests the current input value to be read. Qualified by QI.

### **Event Outputs**

- **INITO** (EInit): Confirms successful initialization. Returns QO and STATUS.
- **CNF** (Event): Acknowledges a completed request (REQ). Contains QO, STATUS, and the read value IN.
- **IND** (Event): Indicates an asynchronous change in the input signal from the resource driver. Contains QO, STATUS, and IN.

### **Data Inputs**

- **QI** (BOOL): Qualifier for the event inputs; typically set to TRUE to enable processing.
- **PARAMS** (STRING): Service-specific parameters for configuration (e.g., addressing or protocol settings).
- **u8SAMember** (USINT): Node SA (Subscriber Address) of the device in the range 224…239. Initial value: MI::MI_00.
- **Input** (DataPanel::io::MI::DI::DataPanel_MI_DI_S): Identification of the digital input (e.g., DigitalInput_5A…8B). Initial value: Invalid.

### **Data Outputs**

- **QO** (BOOL): Output qualifier; indicates whether the output data is valid.
- **STATUS** (STRING): Service status message (e.g., error or success message).
- **IN** (BOOL): The binary input value read from the connected sensor or switch.

#### **Adapters**

No adapters defined.

## Functionality

The function block communicates with a DataPanel module via the MI protocol. After startup, the function block is initialized with INIT, during which the communication parameters (PARAMS, u8SAMember, Input) are configured. Upon successful initialization, INITO is triggered. The current state of the configured digital input can then be queried using REQ. The response is provided via CNF with the value IN. Additionally, the function block can receive asynchronous events (IND) when the input state changes without an explicit request (e.g., due to hardware interrupts). The QO output indicates the validity of the data, and STATUS provides diagnostic information.

## Technical Features

- The function block is implemented as a Service Interface Function Block (SIFB) and expects a low-level hardware implementation in the 4diac runtime.
- The input configuration uses a user-defined structure type `DataPanel_MI_DI_S`, which enables precise channel assignment.
- The parameter `u8SAMember` is limited to values 224–239; this corresponds to typical SA addresses for MI-based subsystems.
- Initialization can only be performed with valid parameters. Initialization fails if the input is invalid (e.g., Invalid).

## State Overview

An explicit state machine is not defined in the XML. Typically, the function block goes through the following states:

1. **IDLE** – After startup, waits for INIT.
2. **INIT** – Initialization is performed, configuring the hardware channel.
3. **OPERATE** – Ready for REQ and receiving IND events.
4. **ERROR** – In case of failed initialization or communication errors.

Alternative states may vary depending on the communication driver implementation.

## Application Scenarios

- **Field Device Connection**: A binary proximity sensor (npn) is connected to a DataPanel input. The function block reads the switching state and makes it available in the control application.
- **Switch Monitoring**: A manually operated switch (ground switching) is monitored via the function block; Changes are reported asynchronously via IND.
- **Diagnostics**: Errors such as wire breaks or address conflicts can be detected via STATUS.

## Comparison with similar function blocks

Similar function blocks such as `DataPanel_MI_DI_Xn` (for other input groups) or `DataPanel_MI_DO_Xn` (outputs) share the same interface but differ in the number of channels or the data direction. This function block focuses on a single digital input and is suitable for precise monitoring.

## Conclusion

The `DataPanel_MI_IXn` function block provides a standardized interface for reading a binary input in DataPanel systems via the MI protocol. Its service-oriented structure (INIT/REQ/IND) allows for flexible integration into event-driven automation solutions. Configuration via dedicated parameters ensures simple and robust connectivity.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
