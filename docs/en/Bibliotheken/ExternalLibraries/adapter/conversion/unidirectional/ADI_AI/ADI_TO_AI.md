# ADI_TO_AI

![ADI_TO_AI](./ADI_TO_AI.svg)

* * * * * * * * * *
## Introduction

The function block **ADI_TO_AI** is a composite FB that converts a DINT adapter (ADI) into an INT adapter (AI). It serves as a unidirectional conversion interface between two adapter types and internally uses the block `F_DINT_TO_INT` for type conversion of the data values.
## Interface Structure

### **Event Inputs**

The FB does not have separate event inputs. Event-driven processing is handled via the **Socket ADI_IN**:

- **ADI_IN.E1** – Event to request the conversion (internally forwarded to `Convert.REQ`).

### **Event Outputs**

The FB has no separate event outputs. Result feedback is provided via the **AI_OUT** plug:

- **AI_OUT.E1** – Event triggered after successful conversion (corresponds to `Convert.CNF`).

### **Data Inputs**

The FB has no separate data inputs. Input data is provided via the **ADI_IN** socket:

- **ADI_IN.D1** – DINT value (32-bit integer) to be converted to an INT value.

### **Data Outputs**

The FB has no separate data outputs. Result data is output via the **AI_OUT** plug:

- **AI_OUT.D1** – INT value (16-bit integer), the result of the conversion.

### **Adapter**

- **Socket**: `ADI_IN` (Type `adapter::types::unidirectional::ADI`) – DINT adapter input.
- **Plug**: `AI_OUT` (Type `adapter::types::unidirectional::AI`) – INT adapter output.

## Functionality

This function block connects the adapter interfaces directly to an internal instance of the conversion function block `F_DINT_TO_INT`:

1. An event at `ADI_IN.E1` triggers `Convert.REQ`.
2. The value of `ADI_IN.D1` is passed to `Convert.IN`.

`` 3. The conversion `DINT → INT` is performed.

4. Upon completion, `Convert.CNF` signals the event to `AI_OUT.E1`, and the converted value from `Convert.OUT` is forwarded to `AI_OUT.D1`.

## Technical Features

- **No Dedicated State Machine**: The function block is a pure composite (network) without ECC. Its behavior is determined solely by the internal connection and the conversion block used.
- **Type Conversion**: The conversion from DINT to INT is performed according to IEC 61131-3 (overflow on value range exceeding is not handled; INT range: -32768 … 32767).
- **Package**: The function block (FB) is organized in the package `adapter::conversion::unidirectional`.

## State Overview

The FB does not have an explicit state machine. Its behavior is purely data flow-driven: Each incoming event results in exactly one conversion and one output.

## Application Scenarios

- **Integration of DINT-based components** into an environment that only supports INT adapters (e.g., older controllers or standardized interfaces).
- **Type adaptation** in heterogeneous automation systems that use different data widths.

## Comparison with Similar Function Blocks

- **AI_TO_ADI**: The reverse conversion (INT → DINT). While `ADI_TO_AI` reduces the value range (potential data loss), `AI_TO_ADI` extends the value range without information loss.
- **Direct Adapter Coupling**: Without conversion, the adapter types would have to match exactly. `ADI_TO_AI` enables communication between incompatible types.

## Conclusion

The `ADI_TO_AI` module is a simple yet useful converter that bridges the gap between DINT and INT adapter interfaces. Its composite structure makes it easy to understand and maintain. Using the standardized `F_DINT_TO_INT` ensures correct conversion.
