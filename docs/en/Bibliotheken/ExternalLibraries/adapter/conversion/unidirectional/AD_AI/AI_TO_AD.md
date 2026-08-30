# AI_TO_AD

![AI_TO_AD](./AI_TO_AD.svg)

* * * * * * * * * *

## Introduction

The composite function block **AI_TO_AD** converts an INT-based adapter interface (AI) to a DWORD-based adapter interface (AD). It encapsulates the type conversion from `INT` to `DWORD`, thus enabling the seamless integration of different adapter types into control applications. The block is unidirectional and event-driven.

## Interface Structure

### **Event Inputs**

The block does not have direct event inputs. Event-driven triggering occurs via the adapter **AI_IN** (socket).

- **E1 (via AI_IN)**: Trigger event for converting the incoming INTEGER value.

### **Event Outputs**

This function block has no direct event outputs. Conversion confirmation is provided via the **AD_OUT** adapter (plug).

- **E1 (via AD_OUT)**: Confirmation event after successful conversion.

### **Data Inputs**

This function block has no direct data inputs. The INTEGER value to be converted is provided via the **AI_IN** adapter.

- **D1 (via AI_IN)**: Input value of type `INT`.

### **Data Outputs**

This function block has no direct data outputs. The converted DWORD value is output via the **AD_OUT** adapter.

- **D1 (via AD_OUT)**: Output value of type `DWORD`.

### **Adapters**

- **AI_IN** (Socket) – Input adapter type `adapter::types::unidirectional::AI`. It provides an INTEGER input (D1) and a trigger event (E1).
- **AD_OUT** (Plug) – Output adapter type `adapter::types::unidirectional::AD`. It provides a DWORD output (D1) and an acknowledgement event (E1).

## Functionality

The function block is implemented as a composite. Internally, the IEC 61131-compliant function block **F_INT_TO_DWORD** is used.

Process:

1. An event at the input adapter **AI_IN.E1** triggers the data transfer.
2. The value of **AI_IN.D1** (INT) is forwarded to input `IN` of `F_INT_TO_DWORD`.
3. The internal function block performs the type conversion `INT → DWORD`.
4. The result is present at output `OUT` of `F_INT_TO_DWORD` and is passed to **AD_OUT.D1**.
5. Simultaneously, the event **AD_OUT.E1** is triggered to signal processing in the subsequent network.

## Technical Features

- **Composite Function Block**: The functionality is implemented by an embedded function block, so no separate state machine (ECC) is required.
- **Unidirectional**: Data flows exclusively from the input to the output adapter; feedback is not provided.
- **Type Conversion**: The function block uses the standardized IEC 61131 function block `F_INT_TO_DWORD`, ensuring compatibility with many automation systems.
- **Adapter Encapsulation**: The conversion logic is fully embedded in the adapter interfaces, simplifying reuse in different contexts.

## State Overview

The function block does not have its own state machine. Internal processing is entirely controlled by the embedded function block `F_INT_TO_DWORD`, which implements simple event-driven data processing without states. Error behavior and timeouts are not defined.

## Application Scenarios

- **Adapter Bridge**: When a system component provides an INTEGER adapter (AI), but the target component expects a DWORD adapter (AD).
- **Data Word Generation**: Conversion of analog values (e.g., 16-bit measured values) into a 32-bit data word for data transmission or storage.
- **Library Independence**: Encapsulation of the conversion function, so application developers do not need to directly access IEC 61131 function blocks.

## Comparison with Similar Function Blocks

- **F_INT_TO_DWORD**: The direct IEC 61131 function provides pure type conversion without adapter embedding. `AI_TO_AD` adds the adapter interfaces, thus facilitating integration into adapter-based architectures.
- **DWORD_TO_INT (inverse)**: A corresponding function block for reverse conversion would be conceivable, but is not part of this implementation.
- **Custom Adapter Wrappers**: Other function blocks could provide similar conversions for other data types (e.g., `REAL_TO_DWORD`).

## Conclusion

**AI_TO_AD** is a compact, adapter-oriented conversion function block that seamlessly integrates the conversion of INTEGER to DWORD values into existing control networks. By using standardized IEC 61131 function blocks and clearly defining interfaces via adapters, it is particularly well-suited for modular, reusable automation solutions.
