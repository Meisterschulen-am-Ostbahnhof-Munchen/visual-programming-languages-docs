# AL_TO_ALR
![AL_TO_ALR](./AL_TO_ALR.svg)
* * * * * * * * * *
## Introduction
The function block **AL_TO_ALR** is a composite function block (FB) that converts a unidirectional AL adapter (LWORD) into a unidirectional ALR adapter (LREAL). Internally, it uses the conversion block `F_LWORD_TO_LREAL` to convert an incoming LWORD value (64-bit integer) into an LREAL value (64-bit floating-point number) and output it via the output adapter.
## Interface Structure

### **Event Inputs**

The FB does not have direct event inputs. The event required to trigger the conversion is provided via the socket **AL_IN** (type `AL`). This event (E1) is internally connected to the `REQ` input of the conversion block.

### **Event Outputs**

The function block (FB) does not have direct event outputs. The conversion completion event is output via the plug **ALR_OUT** (type `ALR`). The event (E1) of the internal block (`CNF`) is forwarded to the output adapter.

### **Data Inputs**

The function block (FB) does not have direct data inputs. The LWORD value to be converted is provided via the **AL_IN** socket (data signal D1) and passed to the `IN` input of the conversion block.

### **Data Outputs**

The function block has no direct data outputs. The converted LREAL value is output via the **ALR_OUT** plug (data signal D1); it originates from the `OUT` output of the internal block.

### **Adapters**

| Adapter | Direction | Type | Description |

|---------|----------|-----|--------------|

| **AL_IN** | Socket (Input) | `adapter::types::unidirectional::AL` | LWORD adapter that provides the input signal (LWORD) and a trigger event. |

| **ALR_OUT** | Plug (Output) | `adapter::types::unidirectional::ALR` | LREAL adapter that outputs the converted signal (LREAL) and an acknowledgment event. |

## Functionality

The function block operates in a simple event-driven sequence:

1. An incoming event at socket **AL_IN.E1** is forwarded to the `REQ` input of the internal function block `F_LWORD_TO_LREAL`.

2. Simultaneously, the data value from **AL_IN.D1** (LWORD) is passed to the `IN` input of the converter.

`` 3. The internal function block (FB) performs the conversion `LWORD → LREAL`.

4. After the conversion is complete, the event `CNF` is sent to the plug **ALR_OUT.E1**.

5. The converted LREAL value is output to **ALR_OUT.D1**.

The entire processing takes place within one clock cycle (no blocking).

## Technical Features
- **Adapter-based interface**: The FB uses only unidirectional adapters (`AL` and `ALR`). This enables loose coupling between sender and receiver and easy reuse in different system architectures.
- **Type Conversion**: The conversion from `LWORD` (64-bit unsigned integer) to `LREAL` (64-bit floating-point number according to IEEE 754) is performed without loss of precision, as long as the integer value is within the representable range of the floating-point number (max. 2⁵³‒1).
- **Pass-Through Event Control**: The function block does not execute any internal state logic; it transparently forwards events and data. The call time corresponds to the execution time of the internal converter.

## State Overview

The assembled function block itself has **no states of its own**. The processing is entirely controlled by the internally used function block `F_LWORD_TO_LREAL`, which exhibits the following minimal state behavior:

- **IDLE**: Waiting for a `REQ` event.
- **CONVERT**: Executing the conversion (immediately after `REQ`).
- **SEND**: Outputting the `CNF` event and the converted value.

Since the internal function block operates in a single execution step, the states are not externally observable.

## Application Scenarios
- **Sensor Data Processing**: A sensor delivers measured values in LWORD format (e.g., counter readings, raw data). The function block converts these values into LREAL so they can be used in floating-point algorithms (e.g., control, filtering).
- **Protocol Conversion**: In systems that exchange different data formats via adapters, `AL_TO_ALR` serves as a bridge between LWORD- and LREAL-based components.
- **Testing and Simulation**: Generation of LREAL test data from predefined LWORD values or vice versa (using corresponding counterpart function blocks).

## Comparison with Similar Function Blocks
- **`LWORD_TO_LREAL`** – A simple conversion function block without an adapter interface. `AL_TO_ALR` encapsulates this function block and integrates it into an adapter-based architecture.
- **`LINT_TO_LREAL`** – Converts signed 64-bit integers to LREAL. `AL_TO_ALR` works with unsigned LWORDs.
- **`UDINT_TO_LREAL`** – Analogous for 32-bit width. This module is designed for 64-bit and uses unidirectional adapters.

## Conclusion

AL_TO_ALR` is a specialized composite module for the formal conversion of LWORD to LREAL data via unidirectional adapters. It simplifies the integration of integer-based components into floating-point environments and, through its adapter interface, promotes a modular, reusable system architecture. Its simple, event-driven operation makes it reliable and easy to understand.
