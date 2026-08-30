# AI_TO_AW

![AI_TO_AW](./AI_TO_AW.svg)

* * * * * * * * * *

## Introduction

The function block **AI_TO_AW** is a composite module for converting an INT adapter (AI) to a WORD adapter (AW). It is used to convert the interface of an AI adapter (type INT) to an AW adapter (type WORD) so that data and events can be seamlessly transferred between different adapter types.

## Interface Structure

### **Event Inputs**

- **AI_IN.E1** (via Socket AI_IN): Event input that triggers the conversion process.

### **Event Outputs**

- **AW_OUT.E1** (via Plug AW_OUT): Event output that is activated after successful conversion.

### **Data Inputs**

- **AI_IN.D1** (via Socket AI_IN): Data input of type **INT**, providing the value to be converted.

### **Data Outputs**

- **AW_OUT.D1** (via Plug AW_OUT): Data output of type **WORD**, providing the converted result.

### **Adapters**

- **AI_IN** (Socket): Expects an adapter of type `adapter::types::unidirectional::AI` (INT-based).
- **AW_OUT** (Plug): Provides an adapter of type `adapter::types::unidirectional::AW` (WORD-based).

## Functionality

The function block operates as an encapsulation of a simple type conversion function block (`F_INT_TO_WORD`) within a composite structure. The process is as follows:

1. An event at input **AI_IN.E1** is forwarded to the internal function block `F_INT_TO_WORD`.
2. Simultaneously, the value of **AI_IN.D1** (INT) is passed to input `IN` of the conversion block.
3. The internal function block performs the conversion from INT to WORD and places the result at its output `OUT`.
4. After the conversion is complete, the event **AW_OUT.E1** is sent, and the converted value (WORD) is output to **AW_OUT.D1**.

Thus, the entire adapter conversion is controlled by a single event, and the data is converted automatically.

## Technical Features

- **Stores the integer's bit pattern**, as expected for a bit-string destination (truncates if the destination is narrower than the source).

- **Composite Block**: The logic is implemented by an internal sub-block, allowing for a clear separation of conversion logic and interface adapters.
- **Reusability**: The block is based on the standard block `iec61131::conversion::F_INT_TO_WORD` and can therefore be used in any IEC 61499-compliant environment.
- **License**: The block is released under the Eclipse Public License 2.0 (EPL-2.0).
- **Naming Scheme**: The block is located in the package `adapter::conversion::unidirectional`, indicating its function as a unidirectional adapter conversion.

## State Overview

Since this is a composite block without its own state machine, the state behavior is entirely determined by the internal `F_INT_TO_WORD` block. There are essentially two states:

- **Idle**: Waiting for an event at input **AI_IN.E1**.
- **Converting**: After receiving the event, the conversion is performed. No delays or waiting times are implemented – the output occurs immediately in the same cycle.

## Application Scenarios

- **System Integration**: When a subsystem or component provides data via an INT adapter (AI), but the target component expects a WORD adapter (AW).
- **Protocol Adaptation**: In plant control systems where sensor data is delivered as INT, but the communication interface is WORD-based.
- **Type Conversion in Adapter Chains**: The function block can be used as part of an adapter chain to connect different adapter types without requiring manual conversion.

## Comparison with Similar Function Blocks

Other adapter conversion blocks exist, such as `WORD_TO_INT` or `REAL_TO_DINT` – however, `AI_TO_AW` focuses specifically on the adapter conversion from INT (AI) to WORD (AW). Unlike simple type conversion blocks (e.g., `F_INT_TO_WORD`), this block integrates the adapter interfaces directly, eliminating the need for the developer to create separate adapter instantiations.

## Conclusion

The **AI_TO_AW** function block offers a simple and robust solution for converting an INT adapter to a WORD adapter. Its composite structure keeps the logic manageable and extensible. The component is particularly suitable for scenarios in which different adapter types need to be harmonized in an IEC 61499 application, and significantly reduces the implementation effort for such conversions.
