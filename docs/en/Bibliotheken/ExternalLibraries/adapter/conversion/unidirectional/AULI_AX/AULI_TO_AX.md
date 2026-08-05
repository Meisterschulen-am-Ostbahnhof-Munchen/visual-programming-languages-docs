# AULI_TO_AX
![AULI_TO_AX](./AULI_TO_AX.svg)
* * * * * * * * * *
## Introduction
The **AULI_TO_AX** function block serves as a composite block for converting an **AULI** adapter (data type ULINT) into an **AX** adapter (data type BOOL). It allows the connection of an unsigned integer from an adapter socket to a Boolean adapter plug, where the value 0 is interpreted as FALSE and any other value as TRUE.
## Interface Structure
### **Event Inputs**

The function block does not have direct event inputs. The triggering event is provided via the **AULI_IN** adapter:

- **AULI_IN.E1**: Event for processing the ULINT value and triggering the output on the AX adapter.

### **Event Outputs**
Event output is also handled via the adapter:

- **AX_OUT.E1**: Acknowledgement event that, after successful conversion, forwards the new BOOL value to the connected receiver.

### **Data Inputs**
All data inputs are part of the adapter socket:

- **AULI_IN.D1** (ULINT): The input value to be converted.

### **Data Outputs**
Data output is handled via the adapter plug:

- **AX_OUT.D1** (BOOL): Conversion result – TRUE if the input value is not equal to 0, otherwise FALSE.

### **Adapter**
- **AULI_IN** (Socket, Type: `adapter::types::unidirectional::AULI`): Receives the ULINT value and the associated event.
- **AX_OUT** (Plug, Type: `adapter::types::unidirectional::AX`): Provides the converted BOOL value and the output event.

## Functionality
The function block (FB) operates purely event-driven and internally uses the comparison block **F_NE** (IEC 61131-3, "not equal"). An incoming event on **AULI_IN.E1** triggers the execution of the FB **F_NE** by triggering its input **REQ**. The comparison block checks the ULINT value present at **IN1** against the constant value **ULINT#0** (parameter **IN2**). The result **OUT** (BOOL) is forwarded to the data output **AX_OUT.D1**. Once the comparison is complete, **F_NE** generates an acknowledgment event on **CNF**, which is passed to **AX_OUT.E1** to signal the availability of the new value to the connected receiver.

F_NE** is not a validation event.
## Technical Features

- **Composite Function Block**: Functionality is achieved through internal interconnection of standard function blocks – in this case, only a single comparison block.
- **Adapter Encapsulation**: Inputs and outputs are defined exclusively via adapters, enabling uniform and modular connectivity in adapter-based architectures.
- **Use of IEC 61131 Library**: The **F_NE** function block used is from the IEC 61131-3 library, promoting compatibility and reusability.
- **Constant Comparison Reference**: The limit value is fixed at 0; parameterization is not provided.

## State Overview
As a composite function block, **AULI_TO_AX** does not have its own states in the sense of a state machine. The sequence is controlled purely by event chaining:

1. **Waiting** for an event at **AULI_IN.E1**.

2. **Processing** by **F_NE** (comparison) – quasi-static, no delay.

3. **Output** of the result to **AX_OUT** (event and data).

## Application Scenarios
- **Limit Logic**: Converts a ULINT counter reading (e.g., quantity, fill level) into a simple Boolean signal indicating whether the value deviates from zero.
- **Adapter Conversion**: Replaces direct type conversion in adapter-based control architectures when only Boolean processing is required.
- **Signal Simplification**: Reduces complex numerical information to a binary state for alarm or status messages.

## Comparison with Similar Function Blocks
Unlike general comparison function blocks (e.g., **GT**, **EQ**), **AULI_TO_AX** is specifically designed for adapter conversion and does not have configurable comparison operators or variable thresholds. A direct comparison with 0 is hard-coded. Function blocks like **ULINT_TO_BOOL** (without adapters) require their own event and data connections, whereas this function block integrates all adapter handling.

## Conclusion

**AULI_TO_AX** is a compact and specialized composite function block for the simple conversion of a ULINT adapter signal to a Boolean adapter signal. It reduces wiring effort in adapter-based projects and ensures clear, maintainable structures when only the "non-zero" state needs to be evaluated. Implementation using a standardized comparison function block guarantees reliable and resource-efficient execution.
