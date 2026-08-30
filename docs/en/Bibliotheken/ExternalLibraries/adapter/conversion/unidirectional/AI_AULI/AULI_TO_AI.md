# AULI_TO_AI

![AULI_TO_AI](./AULI_TO_AI.svg)

* * * * * * * * * *

## Introduction

The function block **AULI_TO_AI** is a composite function block (FB) that converts an incoming adapter of type **AULI** (ULINT-based) into an outgoing adapter of type **AI** (INT-based). It serves as an interface converter between components that use different data types for analog values.

## Interface Structure

### **Event Inputs**

The function block itself has no direct event inputs. Event control is handled via the connected adapters.

### **Event Outputs**

There are also no dedicated event outputs at this level; output events are passed on via the AI_OUT adapter.

### **Data Inputs**

- No direct data inputs at the block level. The data is transferred to the block via socket `AULI_IN`.

### **Data Outputs**

- No direct data outputs at the block level. The converted data is output via plug `AI_OUT`.

### **Adapters**

| Name | Direction | Type | Description |
| ----------- | ---------- | ------------------------------------------ | -------------------------------------------- |
| `AULI_IN` | Socket | `adapter::types::unidirectional::AULI` | ULINT input adapter (analog value) |
| `AI_OUT` | Plug | `adapter::types::unidirectional::AI` | INT Output Adapter (Converted Value) |

## Functionality

The function block internally uses the predefined function block `F_ULINT_TO_INT` from the IEC 61131 library. Its functionality is as follows:

1. An event from socket `AULI_IN.E1` triggers the conversion of the data value `AULI_IN.D1` (ULINT) via the internal function block `Convert`.
2. The function block `Convert` performs the type conversion from `ULINT` to `INT`.
3. After successful conversion, the output event `Convert.CNF` is triggered, which activates the event `AI_OUT.E1`.
4. The converted data value (`Convert.OUT`) is forwarded to `AI_OUT.D1`.

This enables seamless, event-driven conversion from AULI to AI adapters.

## Technical Features

- **Composition:** The function block is implemented as a composite function block, meaning it encapsulates the logic in a clear and concise block and uses a standardized conversion block.
- **Unidirectional Adapters:** Both `AULI_IN` and `AI_OUT` are unidirectional adapters that support data flow in only one direction.
- **Event-driven:** The conversion process only starts upon an incoming event, enabling efficient processing.
- **License notice:** This function block is subject to the Eclipse Public License 2.0.

## State overview

Since the function block operates purely event-driven and does not store any internal states, there is no explicit state machine. It behaves like a functional transformation: Each input event triggers a conversion and an output event.

Internal flow (simplified):

- **Idle:** Waiting for an event from `AULI_IN`.
- **Processing:** Conversion is running (instant, as it is a synchronous function block).
- **Done:** Output event is sent, return to Idle.

## Application scenarios

- **System integration:** Connecting components that use different data types for analog signals (e.g., a sensor provides ULINT, an actuator expects INT).
- **Adapter Cascades:** Extending protocol conversions in automation projects.
- **Data Type Conversion:** When a fieldbus or gateway module only provides ULINT values, but the control system requires INT.

## Comparison with Similar Function Blocks

| Function Block | Input Type | Output Type | Description |
--------------------- | ------------ | ------------ | ------------------------------------------------ |
| `AULI_TO_AI` | AULI (ULINT) | AI (INT) | Converts entire adapter interfaces. |
| `F_ULINT_TO_INT` | ULINT | INT | Data conversion only, no adapters. |
| `AI_TO_AULI` (if applicable) | AI (INT) | AULI (ULINT) | Reverse direction (not available). |

The key difference compared to pure data conversion blocks lies in the adapter input/output, which enables complete interface conversion.

## Conclusion

The `AULI_TO_AI` block offers an elegant and standardized way to perform adapter-specific type conversions between ULINT and INT-based analog interfaces. Encapsulating the conversion logic in a composite function block increases reusability and clarity. It is particularly well-suited for modular automation architectures where different protocols or data types interact.
