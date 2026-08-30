# AD_TO_ADI

![AD_TO_ADI](./AD_TO_ADI.svg)

* * * * * * * * * *
## Introduction

The **AD_TO_ADI** function block is a composite module for converting a DWORD adapter (AD) to a DINT adapter (ADI). It enables the seamless integration of components with different data types into an IEC 61499 application without requiring the user to implement the conversion logic themselves.
## Interface Structure

### **Event Inputs**

No direct event inputs. Event control is handled via the socket adapter `AD_IN`.

### **Event Outputs**

No direct event outputs. Event output is handled via the plug adapter `ADI_OUT`.

### **Data Inputs**

No direct data inputs. Data is transferred via the socket adapter `AD_IN`.

### **Data Outputs**

No direct data outputs. Data is transferred via the plug adapter `ADI_OUT`.

### **Adapters**

| Name | Type | Direction | Comment |
|-------------|-----|-----------|-----------|
| `AD_IN` | `adapter::types::unidirectional::AD` | Socket (Input) | DWORD Adapter Input – returns a DWORD date and an event |
| `ADI_OUT` | `adapter::types::unidirectional::ADI` | Plug (Output) | DINT Adapter Output – Returns a Converted DINT Data and an Event |

## Functionality

This function block encapsulates a call to the IEC 61131-3 conversion function `F_DWORD_TO_DINT`. The process is as follows:

1. An event at socket `AD_IN.E1` triggers the conversion function block `Convert` (event `REQ`).
2. Simultaneously, the DWORD data `AD_IN.D1` is passed to input `Convert.IN`.
3. The conversion function block converts the value into a DINT and signals completion via the event `CNF`.

4. This event is forwarded to plug `ADI_OUT.E1`, and the converted DINT value (`Convert.OUT`) is placed in `ADI_OUT.D1`.

As a result, from the application's perspective, the composite function block behaves like a direct adapter converter without any side effects.

## Technical Features

- **Bit-reinterpretation, value-preserving** (destination is same width or wider than the source bit-string).

- **IEC 61131-3 Compatibility** – The conversion is performed via the standardized library function `F_DWORD_TO_DINT`, which is available for common PLC systems.
- **Unidirectional Adapters** – Both the input and output adapters are unidirectional; feedback or reverse-direction data is not supported.
- **No State Information** – The composite itself has no internal state variables; each conversion is atomic and time-independent.
- **Autonomy** – The function block can be used in a network configuration without manually integrating other function blocks.

## State Overview

The composite function block does not have its own state machine. Its behavior results purely from the sequential processing of its internal connections:

- **Waiting for Event** – No activity occurs as long as no event is present at `AD_IN.E1`.
- **Conversion** – After an event is received, the result is converted once and output.
- **Completion** – The function block is immediately ready for the next event.

## Application Scenarios

- **Gateway between systems with different data widths** – e.g., connecting a DWORD sensor value to DINT-based control logic.
- **Adapter Bridge in IEC 61499 Architectures** – When components need to communicate via standardized unidirectional adapters (AD/ADI).
- **Encapsulation of plausibility checks** – the DWORD value can be validated in upstream logic before conversion to the DINT format.

## Comparison with similar function blocks

- **AD_TO_ADI** specializes in converting DWORD to DINT and follows a strict unidirectional adapter profile.
- Similar function blocks such as `AD_TO_AI` (DWORD to INT) or `ADI_TO_AD` (reverse conversion) exist for other data types but share the same design pattern.
- Unlike a generic conversion function block (e.g., `F_DWORD_TO_DINT` alone), the composite function block offers direct adapter integration, eliminating the need for users to create manual adapter interfaces.

## Conclusion

The composite function block **AD_TO_ADI** provides a simple, robust, and standards-compliant solution for converting DWORD to DINT adapter data. It reduces configuration effort within IEC 61499 networks and increases the reusability of function blocks from different sources. Thanks to its purely functional implementation without state issues, it is particularly suitable for time-critical and safety-related applications.
