# ALR_TO_ADI
![ALR_TO_ADI](./ALR_TO_ADI.svg)
* * * * * * * * * *
## Introduction
The **ALR_TO_ADI** function block is a composite block that enables conversion between two different adapter types. It translates an **ALR adapter** (which provides LREAL data) into an **ADI adapter** (which provides DINT data). It is used in environments based on the IEC 61499 standard to standardize communication between components with different data type interfaces.
## Interface Structure
The function block does not have any independent event or data inputs/outputs at the top level. All communication takes place via the two adapter interfaces.

## **Event Inputs**
The function block does not have direct event inputs. Events are received via the **ALR_IN** socket.

### **Event Outputs**
The FB has no direct event outputs. Events are sent via the **ADI_OUT** plug.

### **Data Inputs**
The FB has no direct data inputs. Data is received via the **ALR_IN** socket.

### **Data Outputs**
The FB has no direct data outputs. Data is sent via the **ADI_OUT** plug.

### **Adapters**

| Adapter | Direction | Type | Description |

|---------|----------|-----|--------------|

| ALR_IN | Socket | adapter::types::unidirectional::ALR | Returns an event (E1) and a data value (D1) of type LREAL. |

| ADI_OUT | Plug | adapter::types::unidirectional::ADI | Expects an event (E1) and outputs a data value (D1) of type DINT. |

## Functionality
The function block is implemented as a composite and internally contains a single conversion function block: `iec61131::conversion::F_LREAL_TO_DINT`. The connection is as follows:

1. **Event Forwarding**: An event (E1) arriving at socket **ALR_IN** is directly forwarded to the `REQ` input of the conversion function block.

2. **Data Transfer**: The data value **D1** of the **ALR_IN** adapter is transferred to the `IN` input of the conversion function block.

3. **Conversion**: The function block `F_LREAL_TO_DINT` converts the LREAL value into a DINT value.

4. **Feedback**: The confirmation event (CNF) of the conversion function block triggers the event **E1** at the **ADI_OUT** plug.

5. **Data Output**: The converted DINT value from the output `OUT` of the conversion function block is transferred to the data output **D1** of the **ADI_OUT** adapter.

This results in a synchronized, event-driven conversion: Each input pulse generates an output pulse with the converted data value.

## Technical Features
- **Composite Block**: The implementation uses an internal standard function block from the IEC 61131 library, which promotes maintainability and reusability.
- **Unidirectionality**: The adapters are declared as unidirectional, meaning data flows in only one direction (ALR → ADI).
- **Package Structure**: The function block is organized in the package `adapter::conversion::unidirectional`, which allows for clear integration into a library.
- **No State Storage**: The conversion is purely combinatorial with event-driven triggering – no internal state is stored.

## State Overview
Since the function block does not have its own state diagram, the state logic is limited to that of the internal conversion function block. There are essentially two phases:

- **Waiting**: The function block waits for an event at the ALR_IN socket.
- **Converting**: After receiving the event, the conversion is performed, and the result is output at the ADI_OUT socket.

There are no delays or error handling – the conversion is instantaneous and always produces a valid DINT value (in case of overflow or invalid values, the conversion function block behaves according to IEC 61131).

## Application Scenarios
- **System Integration**: One system component provides data as LREAL (e.g., floating-point measurements), while another requires integer DINT values (e.g., for counter registers or index calculations).
- **Adapter Adaptation**: If one component only supports ALR adapters, but another component expects ADI adapters, this function block can act as an intermediary.
- **Protocol Conversion**: In standalone subsystems connected via adapters, this function block enables clean type conversion without changing the original adapter definition.
-
## Comparison with Similar Function Blocks
- **F_LREAL_TO_DINT (Direct Function Block)**: This function block performs the conversion itself but requires its own event and data interfaces and no adapters. `ALR_TO_ADI` encapsulates this function block to make it compatible with adapter-based connections.
- **ALR_TO_DINT (Hypothetical)**: A direct function block with its own input/output interface (event + data) would not use any adapters. This function block is specifically designed for use in an adapter framework.
- **Reverse Conversion (ADI_TO_ALR)**: A function block for the reverse direction (DINT → LREAL) likely exists, based on the same conversion principle.

## Conclusion
The composite function block `ALR_TO_ADI` offers an elegant solution for mediating between adapter types with different data types. By reusing a standardized conversion block, the implementation remains lean and reliable. The function block is particularly suitable for modular, adapter-based systems where type conflicts between components need to be resolved.
