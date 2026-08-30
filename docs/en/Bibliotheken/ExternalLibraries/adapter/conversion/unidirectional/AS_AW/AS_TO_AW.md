# AS_TO_AW

![AS_TO_AW](./AS_TO_AW.svg)

* * * * * * * * * *
## Introduction

The function block **AS_TO_AW** is a composite block that converts a unidirectional **SINT** adapter (AS) into a unidirectional **WORD** adapter (AW). It serves as a bridge between different adapter types and enables the further processing of SINT signals as WORD data in a 4diac environment.
## Interface Structure

### **Event Inputs**

*No direct event inputs.*

The block has a **socket** of type `AS`, which indirectly provides an event input:

- **AS_IN.E1** – Event input via the socket; an incoming event triggers the conversion.

### **Event Outputs**

*No direct event outputs.*

The function block has a **plug** of type `AW`, which indirectly provides an event output:

- **AW_OUT.E1** – Event output via the plug; an event is sent after successful conversion.

### **Data Inputs**

- **AS_IN.D1** (`SINT`) – Input data value of the AS socket; the SINT value to be converted.

### **Data Outputs**

- **AW_OUT.D1** (`WORD`) – Output data value of the AW plug; the converted WORD value.

### **Adapter**

| Type | Name | Direction | Comment |
|------|------|----------|-----------|
| `AS` (unidirectional) | **AS_IN** | Socket (input) | SINT Adapter input |
| `AW` (unidirectional) | **AW_OUT** | Plug (output) | WORD Adapter output |

## Functionality

The function block contains an internal instance of the conversion function block `iec61131::conversion::F_SINT_TO_WORD`.

Processing is event-driven:

1. An event at **AS_IN.E1** (socket) triggers the internal function block via its `REQ` input.
2. Simultaneously, the value of **AS_IN.D1** (`SINT`) is forwarded to the `IN` input of the converter.
3. The converter `F_SINT_TO_WORD` performs the type conversion and signals its completion via its `CNF` output.
4. This event is passed to **AW_OUT.E1** (Plug), and the converted `WORD` value is available at **AW_OUT.D1**.

Thus, a reliable, one-time conversion is performed upon each event arrival.

## Technical Features

- **Composite FB**: The function block utilizes 4diac's composite functionality to integrate an existing conversion function block (`F_SINT_TO_WORD`) into an adapter package.
- **Unidirectional Adapters**: Both the input and output adapters are unidirectional, meaning only one data and event direction is supported.
- **IEC 61131-3 Conversion**: The actual type conversion is performed according to the IEC 61131-3 standard, which facilitates compatibility with other systems.
- **Copyright Notice**: The function block includes a copyright notice (EPL 2.0) that governs its use and distribution.

## State Overview

Since the function block consists of an internal FB with REQ/CNF handshake, the process can be described as follows:

| State | Description |
** |---------|--------------|
| **Idle** | Waiting for an event at AS_IN.E1 |
| **Busy** | Conversion in progress (internal FB active) |
| **Done** | Conversion complete, event sent to AW_OUT.E1 |

The function block is not stateful in the sense of a state machine – the internal FB implements the state logic.

## Application Scenarios

- **Signal Conversion**: A sensor delivers data as a SINT (e.g., an 8-bit value), but the downstream system expects a WORD (16-bit). The AS_TO_AW function block handles the conversion.
- **Adapter Integration**: In a heterogeneous control system, different adapter types must be connected. The function block acts as a "translator" between AS and AW interfaces.
- **Test and Simulation Environments**: For bridging adapter incompatibilities during development or when testing function blocks.

## Comparison with Similar Blocks

| Block | Function | Difference |
|----------|----------|-------------|
| **AS_TO_AW** | SINT → WORD | Specific conversion for unidirectional adapters |
| **General Converters** (e.g., `F_SINT_TO_WORD`) | Pure data conversion without adapter encapsulation | AS_TO_AW provides a ready-made adapter interface and can be used directly in adapter-based networks |
| **Other Adapter Converters** (e.g., `BOOL_TO_BYTE`) | Other data types | AS_TO_AW specializes in SINT ↔ WORD |

## Conclusion

The **AS_TO_AW** is a useful, compact conversion module that seamlessly integrates the conversion from a SINT adapter (AS) to a WORD adapter (AW) into the 4diac IDE. By using the standardized IEC 61131-3 converter and unidirectional adapter technology, it enables flexible and reliable signal conversion in automation projects.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
