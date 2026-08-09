# ALR_TO_AUS

![ALR_TO_AUS](./ALR_TO_AUS.svg)

* * * * * * * * * *
## Introduction

The composite function block **ALR_TO_AUS** serves as a universal converter between two unidirectional adapter protocols. It converts an LREAL value (64-bit floating-point) into a USINT value (8-bit unsigned integer). The block was developed for use in IEC 61499-based automation systems and internally uses the standard function block `F_LREAL_TO_USINT` from the library `iec61131::conversion`.
## Interface Structure

Since this is a composite block, all inputs and outputs are implemented via adapters.

## **Event Inputs**

- No direct event inputs at the top level.

The adapter connected via the **Socket ALR_IN** has an event input **E1** that triggers the conversion.

### **Event Outputs**

- No direct event outputs at the top level.

The adapter connected via the **Plug AUS_OUT** provides the event output **E1**, which signals the completion of the conversion.

### **Data Inputs**

- No direct data inputs at the top level.

The **ALR_IN** adapter provides the data input **D1** (type: LREAL), which supplies the floating-point value to be converted.

### **Data Outputs**

- No direct data outputs at the top level.

The **AUS_OUT** adapter provides the data output **D1** (type: USINT), which outputs the converted integer result.

### **Adapters**

| Name | Type | Direction | Comment |
|-----------|----------------------------------------------|----------|---------------------------------|
| `ALR_IN` | `adapter::types::unidirectional::ALR` | Socket | Unidirectional LREAL input |
| `AUS_OUT` | `adapter::types::unidirectional::AUS` | Plug | Unidirectional USINT output |

## Functionality

The function block operates in an event-driven manner:

1. An incoming event at the adapter input `ALR_IN.E1` is internally connected to the **REQ** input of the conversion block `F_LREAL_TO_USINT`.
2. Simultaneously, the data value `ALR_IN.D1` is transferred to the data input `IN` of the conversion block.
3. The converter performs the conversion from LREAL to USINT. The floating-point value is rounded or truncated to the nearest USINT integer value (0–255) according to IEC 61131-3.
4. After successful conversion, the converter generates the event `CNF`, which is forwarded directly to the adapter output `AUS_OUT.E1`.
5. The converter's result `OUT` is transferred to the data output `AUS_OUT.D1`.

This enables synchronous, data-driven conversion without any additional delay.

## Technical Features

- **Composite Structure**: The block encapsulates the conversion logic in a reusable unit and utilizes the standardized adapter types `ALR` and `AUS`. This allows for seamless integration into existing unidirectional communication protocols.
- **Standard-Compliant Conversion**: The actual conversion is performed by the IEC 61131 block `F_LREAL_TO_USINT`, which guarantees defined behavior (e.g., rounding or capping) according to the standard.
- **EPL 2.0 License**: The block is released under the Eclipse Public License 2.0, which allows unrestricted use in proprietary and open-source projects.
- **No State Machine**: As a composite, the block does not have its own state machine; the internal control is handled entirely by the converter block.

## State Overview

The block itself does not have an explicit state machine. The embedded function block `F_LREAL_TO_USINT` typically implements the states **IDLE**, **BUSY**, and **ERROR** during this conversion. For invalid inputs (e.g., USINT overflow), the converter can trigger an error, which, however, is not passed on to the adapter outputs in this version.

## Application Scenarios

- **Sensor/Actuator Connection**: When a floating-point sensor value (e.g., pressure, temperature) needs to be converted into an 8-bit signal for a simple actuator (e.g., switch position, brightness).
- **Protocol Adaptation**: In systems that mediate between different adapter types for data transmission, such as in fieldbus couplers or gateway functions.
- **Testing and Simulation**: For the easy conversion of LREAL test data to USINT formats to test the functionality of downstream components.

## Comparison with Similar Components

- **LREAL_TO_INT / LREAL_TO_DWORD**: These components provide different output types (INT, DWORD) and are therefore suitable for target platforms with wider or signed integers.
- **REAL_TO_USINT**: A corresponding variant is available for 32-bit floating-point numbers (REAL). However, this component uses the more precise LREAL type.
- **Scaling with Arithmetic Blocks**: Manual conversion using `MUL` and `ADD` would be possible, but less standardized and more prone to errors. The `ALR_TO_AUS` block offers a tested, standards-compliant solution.

## Conclusion

The **ALR_TO_AUS** function block is a specialized but indispensable tool for converting LREAL to USINT data in IEC 61499 applications. Its composite design allows for a clean separation of the conversion logic and easy integration via standardized adapters. It is particularly suitable for scenarios where precise floating-point values need to be mapped to a narrow integer range.
