# ALR_TO_AUDI

![ALR_TO_AUDI](./ALR_TO_AUDI.svg)

* * * * * * * * * *

## Introduction

The ALR_TO_AUDI function block is a composite function block (FB) that converts an **ALR adapter** (LREAL) into an **AUDI adapter** (UDINT). It serves as an interface between an analog LREAL source and a digital UDINT sink in unidirectional communication paths.

## Interface Structure

### **Event Inputs**
- `ALR_IN.E1` – Event input of the ALR adapter; triggers the conversion.

### **Event Outputs**

- `AUDI_OUT.E1` – Event output of the AUDI adapter; signals the completion of the conversion.


### **Data Inputs**

- `ALR_IN.D1` – LREAL input value that is converted to a UDINT value.

### **Data Outputs**

- `AUDI_OUT.D1` – UDINT output value, result of the conversion.

### **Adapters**

- **Socket** `ALR_IN` of type `adapter::types::unidirectional::ALR` – Input interface for LREAL values with event.

- **Plug** `AUDI_OUT` of type `adapter::types::unidirectional::AUDI` – Output interface for UDINT values with event.

## Functionality

The function block internally uses the conversion function block `iec61131::conversion::F_LREAL_TO_UDINT`. The process is as follows:

1. An event on `ALR_IN.E1` is forwarded to input `REQ` of the internal converter.

2. Simultaneously, the data value from `ALR_IN.D1` is transferred to input `IN` of the converter.

3. After successful conversion, the converter sends an acknowledgment event (`CNF`) to `AUDI_OUT.E1`.

4. The converted UDINT value is at output `OUT` of the converter and is passed on to `AUDI_OUT.D1`.

Thus, the conversion is strictly event-driven and data-synchronous.


## Technical Features

- **Adapter-Based Encapsulation** – Data and events are exchanged via standardized adapters of type `unidirectional`, enabling a clean separation of interfaces and implementation.

- **Unidirectional Communication** – The function block supports only one direction of data flow (LREAL → UDINT). Feedback or error status is not provided.

- **Type Conversion** – The conversion from LREAL (64-bit floating-point) to UDINT (32-bit unsigned integer) can lead to rounding or overflow losses, but is performed according to the IEC 61131 standard.

## State Overview

The ALR_TO_AUDI does not have its own internal state machine. Its behavior is entirely determined by the included function block `F_LREAL_TO_UDINT`, which operates as a simple, event-driven conversion instance.


## Application Scenarios

- **Analog-to-Digital Conversion in Agricultural Control** – Conversion of LREAL sensor values (e.g., pressure, fill level) into integer UDINT values for displays or digital control loops.

- **Interface Adaptation** – Connecting components that rely on different adapter types (e.g., ALR from a measurement module and AUDI in a controller).

- **Protocol Conversion** – Simple conversion within adapter chains without having to implement custom logic.

## Comparison with Similar Components

- **LREAL_TO_DINT** – Converts to a signed 32-bit integer. ALR_TO_AUDI, on the other hand, uses the unsigned UDINT variant.

- **REAL_TO_UDINT** – Works with 32-bit floating-point instead of 64-bit LREAL, resulting in correspondingly lower accuracy.

- **LREAL_TO_LWORD** – Converts to a 64-bit integer, but using a different adapter type (LWORD instead of UDINT).

The ALR_TO_AUDI is specifically designed for unidirectional adapter coupling with the aforementioned types.

## Conclusion

The ALR_TO_AUDI is a specialized yet simple component for converting LREAL to UDINT values via adapter interfaces. Thanks to its clear structure and the use of a standardized IEC converter, it can be easily integrated into existing 4diac projects and contributes to the interoperability of different adapter types.

--

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]