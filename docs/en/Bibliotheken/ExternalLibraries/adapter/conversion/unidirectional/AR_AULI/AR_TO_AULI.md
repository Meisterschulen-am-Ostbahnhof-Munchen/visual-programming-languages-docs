# AR_TO_AULI

![AR_TO_AULI](./AR_TO_AULI.svg)

* * * * * * * * * *

## Introduction

The function block **AR_TO_AULI** is a composite function block that converts a REAL input adapter (AR) into a ULINT output adapter (AULI). It serves as a unidirectional interface between components that work with the REAL data type and those that expect ULINT (unsigned long integer). The function block encapsulates the necessary conversion and automatically ensures event and data forwarding.

## Interface Structure

### **Event Inputs**

- **AR_IN.E1** – Input event from the AR adapter; triggers the conversion.

### **Event Outputs**

- **AULI_OUT.E1** – Output event to the AULI adapter; signals that the converted value is available.

### **Data Inputs**

- **AR_IN.D1** – REAL value from the AR adapter to be converted.

### **Data Outputs**

- **AULI_OUT.D1** – ULINT value converted from the REAL input.

### **Adapters**

- **AR_IN** (Socket) – Unidirectional AR adapter (Type: adapter::types::unidirectional::AR) as input.
- **AULI_OUT** (Plug) – Unidirectional AULI adapter (Type: adapter::types::unidirectional::AULI) as output.

## Functionality

The function block is implemented as a composite FB and internally contains a single function block **F_REAL_TO_ULINT** from the IEC 61131 library. The operation is as follows:

1. An event at socket **AR_IN.E1** triggers the execution of the converter.
2. The data value **AR_IN.D1** is forwarded to input **Convert.IN**.
3. The converter performs the type conversion from REAL to ULINT and provides the result at output **Convert.OUT**.
4. The acknowledgment event **Convert.CNF** generates an event at plug **AULI_OUT.E1**, which informs the connected function block about the new value.
5. The converted ULINT value is output in parallel to **AULI_OUT.D1**.

The event and data connections are wired directly without additional logic, so the function block is a pure transformation module.

## Technical Features

- **Numeric conversion**: value-preserving cast (narrowing may truncate, widening/sign-extension is safe).

- **Unidirectionality:** Both the input and output adapters are unidirectional. There is no feedback or acknowledgment from the output to the input.
- **Converter Used:** The embedded function block **F_REAL_TO_ULINT** implements the standardized IEC 61131 conversion. Rounding and overflow behavior comply with IEC standards.
- **Event-Driven Execution:** The conversion is only performed when an event occurs at the input; without an event, the output remains unchanged.
- **Adapter Types:** The adapters are based on a unidirectional variant, meaning they transmit exactly one event and one data value per direction.

## State Overview

As a composite function block, **AR_TO_AULI** has no states of its own. The internal state logic is determined solely by the embedded **F_REAL_TO_ULINT**, which typically implements a simple, event-driven sequence without state storage (REQ → Processing → CNF). The function block is therefore stateless and waits for a new input event after each conversion.

## Application Scenarios

- **Interface Adaptation:** When a component (e.g., a control algorithm) delivers REAL values, but a downstream module (e.g., a counter or index logic) expects ULINT inputs.
- **Adapter Bridge:** Use in a toolchain that connects different data types via adapters without requiring the developer to perform the conversion manually.
- **Data Integration:** Integrating REAL-based sensors or parameters into a system that internally uses ULINT (e.g., for status codes or cumulative values).

## Comparison with Similar Function Blocks

- **F_REAL_TO_ULINT** – Basic function block without adapters; requires direct data and event connections. **AR_TO_AULI** is an encapsulated variant with adapters that simplifies integration into adapter-based architectures.
- **AR_TO_* blocks for other target types** – Corresponding composite blocks exist for conversions from REAL to LINT, DINT, etc. They follow the same pattern and each uses the appropriate IEC converter.
- **Direct conversion in the network** – Alternatively, the F_REAL_TO_ULINT block could be directly integrated into a function block network, but this requires more manual wiring. **AR_TO_AULI** reduces the effort and improves reusability.

## Conclusion

The **AR_TO_AULI** block is a simple yet useful encapsulation of REAL-to-ULINT conversion in an adapter-based format. It extends IEC 61131 conversion with a plug-and-play interface for unidirectional adapters and enables a clean separation of conversion logic and application communication. This component is particularly suitable for modular systems that are based on adapter concepts.
