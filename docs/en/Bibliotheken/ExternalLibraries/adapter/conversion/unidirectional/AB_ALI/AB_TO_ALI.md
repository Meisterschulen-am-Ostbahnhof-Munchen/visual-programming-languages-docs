# AB_TO_ALI

![AB_TO_ALI](./AB_TO_ALI.svg)

* * * * * * * * * *
## Introduction

The function block `AB_TO_ALI` is a composite function block that performs conversion from a BYTE adapter (`AB`) to a LINT adapter (`ALI`). It enables seamless integration between interfaces based on different data types and provides data transfer via standardized adapters.
## Interface Structure

### **Event Inputs**

The function block has no direct event inputs. Events are received via the socket adapter `AB_IN`.

#### **Event Outputs**

The function block has no direct event outputs. Events are output via the plug adapter `ALI_OUT`.

### **Data Inputs**

No direct data inputs for the function block. Data is received via the socket adapter `AB_IN`.

### **Data Outputs**

No direct data outputs for the function block. Data is output via the plug adapter `ALI_OUT`.

### **Adapters**

- **Socket `AB_IN`** (Type: `adapter::types::unidirectional::AB`)

Receives a BYTE signal (via data port `D1`) and an event (via event port `E1`).

- **Plug `ALI_OUT`** (Type: `adapter::types::unidirectional::ALI`)

Sends a LINT signal (via data port `D1`) and an event (via event port `E1`).

## Functionality

The function block operates as a pure data conversion loop:

1. An incoming event at socket `AB_IN` (port `E1`) triggers the internal conversion module `F_BYTE_TO_LINT`.
2. The BYTE value (`D1`), also present at the socket, is passed to the input `IN` of the converter.

3. The converter transforms the BYTE value into a LINT value and makes it available at its output `OUT`.

4. The converter's acknowledgment event (`CNF`) is forwarded to the plug `ALI_OUT` (port `E1`), and the converted LINT value is output on the plug's data port `D1`.

## Technical Features

- This is a **composite function block** that internally uses the standard function block `iec61131::conversion::F_BYTE_TO_LINT`.
- The conversion is **event-driven** – any change at the input triggers processing.
- The function block is designed for unidirectional adapters and does not support reverse conversion.

- The adapter type information (`AB` and `ALI`) is defined as unidirectional interfaces and each contains one event port and one data port.

## State Overview

The function block does not have its own state machine. The conversion is **stateless** – with each incoming event, the current value is immediately converted and output. There is no delay, buffering, or internal state.

## Application Scenarios

- **Integration of fieldbus systems** or sensors that deliver BYTE data into a control environment that expects LINT values (e.g., for further processing in counters or long integer operations).
- **Adapter conversion** in modular function block networks where the interfaces use different data types (e.g., in agricultural or automation technology).
- **Bridging** between older BYTE-based modules and modern LINT-based components.

## Comparison with Similar Function Blocks

- `AB_TO_ALI` is specifically for converting **BYTE** to **LINT**. Analogous function blocks exist for other data type combinations (e.g., `WORD_TO_DINT`, `BYTE_TO_INT`).
- Unlike generic converters or scaling blocks, this function block is optimized for a fixed type conversion and requires no parameterization.
- The use of adapters instead of direct input/output ports enables greater reusability and a clean separation of interfaces.

## Conclusion

The `AB_TO_ALI` function block offers a simple and reliable way to convert BYTE data to LINT data via an adapter. By using standard conversion modules and a clear event-driven architecture, it is ideally suited for modular automation systems that require consistent data conversion between different adapter types.
