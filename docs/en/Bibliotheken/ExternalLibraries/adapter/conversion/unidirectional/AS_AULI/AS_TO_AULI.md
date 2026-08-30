# AS_TO_AULI

---

## Introduction

![AS_TO_AULI](./AS_TO_AULI.svg)
The composite function block `AS_TO_AULI` converts an **AS (SINT) adapter** to an **AULI (ULINT) adapter**. Internally, it uses the IEC 61131 conversion block `F_SINT_TO_ULINT` to perform the actual type conversion from SINT to ULINT. The block is designed as part of a unidirectional adapter library for communication between different data types
---

## Interface Structure

### **Event Inputs**

The block has **no direct event inputs**. Events are received via the **Socket adapter `AS_IN`**:

- **`AS_IN.E1`** – Event input via the AS adapter, which triggers the data conversion.

### **Event Outputs**

This function block has **no direct event outputs**. Events are output via the **Plug adapter `AULI_OUT`**:

- **`AULI_OUT.E1`** – Event output via the AULI adapter, which is activated after the conversion is complete.

### **Data Inputs**

This function block has **no direct data inputs**. Data input is via the **Socket adapter `AS_IN`**:

- **`AS_IN.D1`** – Data input of type **SINT**, which provides the value to be converted.

### **Data Outputs**

The module has **no direct data outputs**. Data output is via the **Plug adapter `AULI_OUT`**:

- **`AULI_OUT.D1`** – Data output of type **ULINT**, which provides the converted value.

### **Adapters**

| Adapter | Type | Direction | Description |
| --------- | ----- | ----------- | -------------- |
| `AS_IN` | `adapter::types::unidirectional::AS` (Socket) | Input | Receives SINT values and trigger event `E1`. |
| `AULI_OUT` | `adapter::types::unidirectional::AULI` (Plug) | Output | Sends ULINT values and acknowledgment event `E1`. |

---

## Functionality

1. The function block expects an event at the socket adapter `AS_IN.E1`. Simultaneously, the data value `AS_IN.D1` (type SINT) must be present.
... 2. The event is forwarded to the internal function block `F_SINT_TO_ULINT` (as `REQ`).

2. The internal function block performs the conversion **SINT → ULINT**.
3. After successful conversion, `F_SINT_TO_ULINT` sends an acknowledgment event (`CNF`) to the plug adapter `AULI_OUT.E1`.
4. The converted value (type ULINT) is output via `AULI_OUT.D1`.

The conversion is performed according to the IEC 61131-3 standard: The SINT value (8-bit signed) is converted into an unsigned 64-bit value (ULINT). Negative SINT values result in a negative ULINT representation (two's complement conversion to 64 bits).

---

## Technical Specifications

- **Standard Compliance**: The component is specified according to IEC 61499-2.
- **License**: Eclipse Public License 2.0 (EPL-2.0).
- **Dependency**: Imports the IEC 61131 component `F_SINT_TO_ULINT` from the package `iec61131::conversion`.
- **Type Safety**: The adapters `AS` and `AULI` ensure type-safe connections; direct cabling from SINT to ULINT without conversion is not possible.
- **Unidirectional Data Flow**: The function block operates purely unidirectionally – it receives data and events and outputs converted data and acknowledgments.

---

## State Overview

The function block does **not have its own state machine**. It functions purely as an interconnect for the inner `F_SINT_TO_ULINT` function block. Its behavior is strictly event-driven:

- **Waiting** (Initial State) → Event sent to `AS_IN.E1` → Transition to **Conversion**.
- **Conversion** → Internal function block operates asynchronously → After completion → Event sent to `AULI_OUT.E1` → Return to **Waiting**.

Error handling is not explicitly modeled; the inner function block outputs a defined result (e.g., 0) for invalid inputs (e.g., outside the value range).

---

## Application Scenarios

- **Integration into Adapter Chains**: If an upstream function block provides a SINT value, but subsequent components only process ULINT, `AS_TO_AULI` can be used as an intermediate adapter.
- **Sensor Connection**: Sensors with 8-bit output (e.g., rotary encoders, simple switches) can be connected to a 64-bit bus.
- **Legacy Systems**: This adapter makes legacy systems with SINT interfaces compatible with modern ULINT-based controllers.

--

## Comparison with Similar Function Blocks

| Function Block | Target Type | Source Type | Special Feature |
| ---------- | --------- | ----------- | ------------- |
| `AS_TO_AULI` | ULINT | SINT | SINT to ULINT conversion |
| AS_TO_AUDI` | UDINT | SINT | SINT to UDINT conversion (32-bit) |
| AS_TO_AWORD` | WORD | SINT | SINT to WORD conversion (16-bit) |
| AULI_TO_AS` | SINT | ULINT | ULINT to SINT conversion (with overflow limitation) |

This function block covers the conversion from an 8-bit signed type to a 64-bit unsigned type and is particularly suitable for applications requiring a large output range.

---

## Conclusion

AS_TO_AULI` is a simple yet important composite module for type conversion between SINT and ULINT adapters. It encapsulates the IEC 61131 conversion and enables type-safe, event-driven integration into automation systems. Its clear interface structure and use of standard libraries make it maintainable, reusable, and easily integrated into existing 4diac IDE projects.

--

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
