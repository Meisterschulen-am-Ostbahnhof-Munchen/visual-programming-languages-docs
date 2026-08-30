# AUS_TO_AUI

![AUS_TO_AUI](./AUS_TO_AUI.svg)

* * * * * * * * * *
## Introduction

The **AUS_TO_AUI** function block is a composite component that performs an interface conversion from an AUS adapter (USINT data type) to an AUI adapter (UINT data type). It serves as a simple passthrough, where both the event and the data value are transferred directly from the input to the output adapter. The implicit type conversion from USINT (8-bit unsigned) to UINT (16-bit unsigned) is performed automatically by the runtime environment.
## Interface Structure

### **Event Inputs**

| Name | Data Type | Description |
|-------------|-----------|--------------|
| E1 | Event | Event input of the AUS adapter; passed unchanged to the output. |

### **Event Outputs**

| Name | Data Type | Description |
|-------------|----------|--------------|
| E1 | Event | Event output of the AUI adapter; receives the event from the input. |

### **Data Inputs**

| Name | Data Type | Description |
|-------------|----------|--------------|
| D1 | USINT | Data value (8-bit) from the AUS adapter; converted to UINT and passed on. |

### **Data Outputs**

| Name | Data Type | Description |
|-------------|----------|--------------|
| D1 | UINT | Data value (16-bit) of the AUI adapter; contains the converted USINT value. |

### **Adapter**

| Type | Name | Direction | Description |
|-----|------|----------|--------------|
| adapter::types::unidirectional::AUS | AUS_IN | Socket (Input) | Out adapter with USINT data and one event. |
| adapter::types::unidirectional::AUI | AUI_OUT | Plug (Output) | AUI adapter with UINT data and one event. |

## Functionality

The function block operates as a simple passthrough:

- An incoming event at `AUS_IN.E1` is passed directly to `AUI_OUT.E1`.
- The incoming data value from `AUS_IN.D1` (USINT) is passed to `AUI_OUT.D1` without any additional logic. The type conversion from USINT to UINT is performed automatically by the 4diac IDE or the target platform.

There are no internal function blocks or algorithms that manipulate the signal.

## Technical Features

- **Composite Function Block**: It does not contain its own function block instances, but simply connects the adapter ports directly.
- **Implicit Type Conversion**: The conversion from USINT to UINT is not explicitly implemented in the function block, but is supported by the runtime system. The 8-bit value is transferred to the less significant part of the 16-bit word.
- **Unidirectional Adapters**: Both AUS and AUI are defined as unidirectional adapters, meaning data flows are only intended to occur in one direction.

## State Overview

The function block has no states of its own, as it contains no internal logic or state machines. It reacts exclusively to input events and forwards them immediately.

## Application Scenarios

- **System Integration**: When a control system (e.g., field devices) delivers data in USINT format, but a downstream module expects UINT.
- **Adapter Switching**: In a PLC or distributed control environment, standard adapters of different types can be coupled using such a conversion function block.
- **Prototyping**: Rapid adaptation of interfaces during the development phase without changing the underlying adapters.

## Comparison with Similar Function Blocks

- **INT_TO_UINT**: Converts an integer data type to an unsigned integer – also available as a composite or basic function block.
- **AUS_TO_AUI** is specifically designed for the adapter types AUS (USINT) and AUI (UINT). Other function blocks, such as `SINT_TO_USINT`, use analogous passthroughs for other data types.
- Unlike function blocks with arithmetic or logical processing, this function block is limited to pure conversion and event forwarding.

## Conclusion

The **AUS_TO_AUI** function block is a streamlined tool for adapting adapter interfaces between USINT and UINT. Its simple passthrough structure makes it performant and easy to understand. It is particularly suitable for integration tasks where existing components with different data widths need to be connected. Due to the lack of internal logic, it is robust and requires no parameterization.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
