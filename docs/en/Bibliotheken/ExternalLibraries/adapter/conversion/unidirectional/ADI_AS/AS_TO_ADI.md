# AS_TO_ADI
![AS_TO_ADI](./AS_TO_ADI.svg)

* * * * * * * * * *
## Introduction
The **AS_TO_ADI** function block converts a SINT adapter (AS) into a DINT adapter (ADI). It is a composite function block that establishes a unidirectional, type-converting connection between the two different data adapters.
## Interface Structure

### **Event Inputs**
None

### **Event Outputs**
None

### **Data Inputs**
None

### **Data Outputs**
None

### **Adapter**

| Type | Direction | Name | Description |
|-----|----------|------|--------------|
| Socket | Input | AS_IN | Adapter type `AS` (SINT, 8-bit signed integer) – receives the SINT signal. |
| Plug | Output | ADI_OUT | Adapter type `ADI` (DINT, 32-bit signed integer) – outputs the converted DINT signal. |

## Functionality

The module internally links the event and data lines of the two adapters directly:

- The incoming event `E1` of socket `AS_IN` is transferred unchanged to the output plug `ADI_OUT` at its event `E1`.

`` - The data value `D1` from the SINT adapter (`AS_IN.D1`) is forwarded to data port `D1` of the DINT adapter (`ADI_OUT.D1`).

Since the data types are different (SINT → DINT), implicit value preservation occurs: The SINT value (value range -128 … 127) is copied into a signed 32-bit value (sign extension). The function block itself does not execute its own conversion logic but relies on the type conversion defined by the adapter interfaces.

## Technical Features
- **Composite Function Block**: The function block does not have its own behavior model (ECC) but only an internal function block network that connects the adapters.
- **Type Conversion**: The conversion from SINT to DINT is handled system-wide by the runtime environment (type compatibility for data connections).
- **Package**: The function block is located in the package `adapter::conversion::unidirectional`.
- **Fully Predefined**: The internal wiring is fixed; the adapters must each have an event port and a data port (`E1`, `D1`).

## State Overview

Since this is a composite function block without its own state machine, there are no states or steps. The function block operates purely data-flow synchronously – every incoming event immediately triggers the forwarding.

## Application Scenarios
- **Sensor Connection**: A SINT adapter (e.g., from an 8-bit sensor) is to be connected to a controller that expects a DINT adapter as its interface.
- **System Integration**: In systems where different accuracy levels (8-bit vs. 32-bit) are used, this function block enables simple, standardized conversion.
- **Protocol Adaptation**: As part of an adapter cascade to switch from a simple data interface standard to a more powerful one.

## Comparison with Similar Function Blocks
- **AS_TO_UDI** – Converts SINT to UINT (unsigned 16-bit integer), different value range interpretation.
- **ADI_TO_AS** – Backward conversion from DINT to SINT (with potential overflow risks).
- **DIRECT_LINK** – Pure passthrough without type conversion, usable only with identical adapter types.

Unlike universal converters (e.g., using `MATH` function blocks), `AS_TO_ADI` offers a specialized, compact solution without additional parameterization.

## Conclusion

The **AS_TO_ADI** function block enables fast and reliable type conversion between SINT and DINT adapters. Its simple, composite-based structure makes it ideal for standardized adapter conversions in automation technology where unidirectional 8-bit to 32-bit conversion is required.
