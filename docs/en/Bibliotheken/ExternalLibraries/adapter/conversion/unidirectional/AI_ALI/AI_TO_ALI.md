# AI_TO_ALI

![AI_TO_ALI](./AI_TO_ALI.svg)

* * * * * * * * * *
## Introduction

The AI_TO_ALI function block is a composite function block that converts an AI (INT) input adapter into an ALI (LINT) output adapter. It serves as a simple conversion interface between different adapter types for unidirectional communication.
## Interface Structure

### **Event Inputs**

No dedicated event inputs. Events are transmitted via the AI_IN input adapter.

Adapter AI_IN provides event input E1.

### **Event Outputs**

No dedicated event outputs. Events are transmitted via the ALI_OUT output adapter.

Adapter ALI_OUT provides event output E1.

### **Data Inputs**

No dedicated data inputs. Data transmission occurs via the AI_IN input adapter.

Adapter AI_IN provides data input D1 (data type INT).

### **Data Outputs**

No dedicated data outputs. Data is passed through the output adapter ALI_OUT.

Adapter ALI_OUT provides data output D1 (data type LINT).

### **Adapters**

- **AI_IN** (Socket): Type `adapter::types::unidirectional::AI` – INT input interface.
- **ALI_OUT** (Plug): Type `adapter::types::unidirectional::ALI` – LINT output interface.

**Note:** The actual event and data interfaces are defined by the adapters. The function block itself does not have its own interfaces.

## Functionality

The function block operates as a simple pass-through: The event and data signal from input adapter AI_IN is forwarded directly to output adapter ALI_OUT. The INT data value is implicitly converted to a LINT value, as LINT covers a larger range of values. The conversion occurs without any additional logic or processing.

## Technical Features

- **Numeric conversion**: value-preserving cast (narrowing may truncate, widening/sign-extension is safe).

- This is a composite function block (FB) that does not implement any functionality of its own, but simply connects two adapters.
- The conversion from INT to LINT is lossless, as LINT (64-bit) covers the entire value range of INT (32-bit).
- The FB is designed for use in unidirectional communication paths where data type adaptation between adapter interfaces is required.
- The use of adapters enables loose coupling between components.

## State Overview

The FB does not have its own state machine, as its functionality is limited to the pure transmission of events and data. The internal state is irrelevant; the behavior is deterministic and reacts instantaneously to incoming events.

-
## Application Scenarios

- **Interface Adaptation:** One module returns an INT value via an AI adapter, while a subsequent module expects a LINT value via an ALI adapter.
- **Extension of Value Ranges:** If an existing INT data path needs to be converted to a larger value range, this function block (FB) can be used as an intermediary.
- **Adapter Protocol Conversion:** In heterogeneous systems where different adapter types are used, this FB serves as a simple converter.

## Comparison with Similar Function Blocks

- **AI_TO_ALI** is specific for converting from AI to ALI. Other function blocks could, for example, implement AI_TO_AL (INT to WORD) or different directions (ALI_TO_AI).
- Compared to a generic type converter (e.g., with parameterization), this FB is specialized and therefore easier to use, but less flexible.

Composite function blocks like this one offer a clear separation of responsibilities and can be stored in libraries for standard conversions.

## Conclusion

The AI_TO_ALI function block is a useful tool for adapter conversion in IEC 61499-based systems. It enables seamless integration of components with different data types at the adapter level. Its simple, pass-through nature makes it reliable and easy to understand. It is particularly well-suited for projects that rely on the adapter-based, unidirectional communication model.
