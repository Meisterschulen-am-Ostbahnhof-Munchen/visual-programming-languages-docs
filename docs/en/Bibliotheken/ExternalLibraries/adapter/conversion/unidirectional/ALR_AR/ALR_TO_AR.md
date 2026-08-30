# ALR_TO_AR

![ALR_TO_AR](./ALR_TO_AR.svg)
*No image available*

* * * * * * * * * *
## Introduction

The **ALR_TO_AR** function block is a composite block that converts an LREAL adapter (ALR) into a REAL adapter (AR). It serves as a link between control components operating with different floating-point accuracies and enables clean, event-driven data conversion within an IEC 61499 network.

## Interface Structure

### **Event Inputs**

- **E1** (via socket `ALR_IN`): Starts the conversion of the incoming LREAL value.

### **Event Outputs**

- **E1** (via plug `AR_OUT`): Signals that the converted REAL value at the output is valid.

### **Data Inputs**

- **D1** (via socket `ALR_IN`): LREAL input value (64-bit floating point).

### **Data Outputs**

- **D1** (via plug `AR_OUT`): REAL output value (32-bit floating point).

### **Adapters**

- **ALR_IN** (socket): Adapter type `adapter::types::unidirectional::ALR` – accepts LREAL data.
- **AR_OUT** (Plug): Adapter type `adapter::types::unidirectional::AR` – provides REAL data.

## Functionality

1. An event at input **E1** (of the ALR_IN socket) triggers the internal block `F_LREAL_TO_REAL`.
2. Simultaneously, the LREAL value from **D1** (ALR_IN) is passed directly to the conversion block.
3. The conversion block converts the 64-bit value into a 32-bit REAL value.
4. After the conversion is complete, an event is generated at output **E1** (AR_OUT), and the REAL value is passed to **D1** (AR_OUT).

Transmission is strictly sequential: first the event, then the data flow – the internal connection ensures reliable synchronization.

## Technical Features

- **Composite Block**: The ALR_TO_AR encapsulates the conversion logic and simplifies reuse in different projects.
- **IEC 61131 Function**: The actual type conversion is based on the standardized library function `F_LREAL_TO_REAL`.
- **Adapter Types**: Both adapters are unidirectional and allow a clear separation of input and output sides.
- **No State Machine**: The block operates purely event-driven without an internal state memory.

## State Overview

Since this is a composite block without its own state machine, there are no explicit states. The internal process is deterministic:

- **Ready / Idle** – waits for an input event.
- **Conversion active** – from event input until the output event is generated (typically takes one cycle).

Latency is minimal and determined by the execution order of the underlying IEC 61499 runtime system.

## Application Scenarios

- **Sensor Integration**: A field device provides LREAL measured values, but downstream logic expects REAL values (e.g., PLC communication).
- **Adapter Coupling**: Connecting two modules that use different adapter interfaces without requiring the developer to manually program the conversion.
- **Data Consistency**: Enforces a clean separation of 64-bit and 32-bit data paths and avoids implicit type conversions.

## Comparison with Similar Components

- **F_LREAL_TO_REAL** (direct): Offers the same conversion but requires separate event and data connections. ALR_TO_AR encapsulates these connections and provides a unified adapter interface.
- **LINT_TO_INT** (adapter variant): Analog logic for integer types with different bit widths. The basic structure is identical but tailored to different data types.
- **Custom Composite Converters**: ALR_TO_AR reduces the overhead of recurring adapter conversions and improves network readability.

## Conclusion

The **ALR_TO_AR** is a simple yet effective composite component that bridges the gap between LREAL and REAL adapter interfaces. It offers clean, event-driven conversion without unnecessary overhead and integrates easily into existing 4diac projects. Thanks to the use of standard library functions, the conversion remains performant and reliable.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
