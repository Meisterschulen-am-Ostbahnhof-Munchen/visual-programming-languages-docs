# F_INT_TO_UDINT

<img width="1232" height="187" alt="F_INT_TO_UDINT" src="https://github.com/user-attachments/assets/8bceda1f-dc12-42bd-a8b4-17dea9411990" />

* * * * * * * * * *
## Introduction
The function block `F_INT_TO_UDINT` converts a signed 16-bit integer value (`INT`) into an unsigned 32-bit integer value (`UDINT`). This conversion is particularly necessary in scenarios where data needs to be exchanged between systems with different data types.

![F_INT_TO_UDINT](F_INT_TO_UDINT.svg)

## Interface Structure
### **Event Inputs**

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.


### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The signed 16-bit integer value (`INT`) to be converted.

### **Data Outputs**

- **OUT**: The resulting unsigned 32-bit integer value (`UDINT`).

### **Adapters**

- No adapters are present.

## Functionality
This function block performs the conversion from `INT` to `UDINT` as soon as the event `REQ` is received. The conversion is performed using the function ``INT_TO_UDINT(IN)``, which converts the input value ``IN`` into the corresponding value ``UDINT``. After successful conversion, the event ``CNF`` is triggered, and the converted value is available at the output ``OUT``.

## Technical Features
- The conversion is performed without additional parameters or configuration.

- The function block is suitable for use in real-time systems because it operates deterministically.

## State Overview

1. **Idle State**: Waits for the event ``REQ``.

2. **Conversion State**: Performs the conversion and sets the output ``OUT``.

3. **Acknowledgement State**: Triggers the event `CNF` and returns to the idle state.

## Application Scenarios

- Data conversion in control systems that use different data types.

- Integration of sensor data in `INT` format into systems requiring `UDINT` format.

- Compatibility layer between different hardware or software components.

## ⚖️ Comparison with Similar Function Blocks

- Similar function blocks such as `F_DINT_TO_UDINT` or `F_SINT_TO_UDINT` offer conversions between other data types, but not specifically for `INT` to `UDINT`.

Unlike generic conversion blocks, `F_INT_TO_UDINT` is optimized for a specific conversion.

## Conclusion
The function block `F_INT_TO_UDINT` is a specialized and efficient tool for converting signed 16-bit integer values to unsigned 32-bit integer values. Its simple interface and deterministic operation make it ideal for use in real-time applications.