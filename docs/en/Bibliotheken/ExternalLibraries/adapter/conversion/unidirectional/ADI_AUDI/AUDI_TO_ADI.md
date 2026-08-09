# AUDI_TO_ADI

![AUDI_TO_ADI](./AUDI_TO_ADI.svg)

* * * * * * * * * *
## Introduction

The **AUDI_TO_ADI** function block is a composite block that converts a unidirectional AUDI adapter (UDINT) into an ADI adapter (DINT). It serves as a bridge between components that use different data types via adapter interfaces. The conversion is performed by the inner block `iec61131::conversion::F_UDINT_TO_DINT`.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| AUDI_IN.E1 | EVENT | Event input via the AUDI adapter; triggers the conversion |

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| ADI_OUT.E1 | EVENT | Event output via the ADI adapter; signals completion of conversion |

### **Data Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| AUDI_IN.D1 | UDINT | Unsigned 32-bit value converted to a signed DINT |

### **Data Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| ADI_OUT.D1 | DINT | Converted signed 32-bit value |

### **Adapter**

| Name | Type | Direction | Comment |
|------|-----|----------|-----------|
| AUDI_IN | adapter::types::unidirectional::AUDI | Socket (Input) | UDINT Adapter Interface |
| ADI_OUT | adapter::types::unidirectional::ADI | Plug (Output) | DINT Adapter Interface |

## Functionality

The function block receives a UDINT value via socket `AUDI_IN` along with an event at input `E1`. This event triggers the conversion of the incoming UDINT value to a DINT value. The conversion is performed internally by the function block `F_UDINT_TO_DINT`. After successful conversion, the converted DINT value is provided via the plug `ADI_OUT`, and an event is sent at the output `E1`.

## Technical Features

- The block is a composite function block and does not contain its own algorithm – all logic is delegated to the embedded `F_UDINT_TO_DINT`.
- The conversion follows the IEC 61131-3 definition of `UDINT_TO_DINT`, meaning that values outside the DINT range (−2147483648 … 2147483647) are clamped to the nearest valid value.
- Event forwarding is strictly causal: the output event is only activated after the conversion is complete.

## State Overview

The function block has no internal states of its own. Its behavior is purely reactive:

An input event is always followed by an output event – provided the data is valid. A dedicated state machine does not exist.

## Application Scenarios

- Connecting a UDINT-providing sensor (e.g., counter or position value) to an actuator that expects a DINT adapter.
- Integrating PLC components that use different adapter data types without requiring the user to manually program the conversion.
- A unified adapter interface in a control architecture that works partly with signed and partly with unsigned values.

## Comparison with Similar Function Blocks

- **DINT_TO_AUDI**: Performs the reverse conversion (DINT → UDINT).
- **F_UDINT_TO_DINT**: Direct use of the conversion function block without adapter encapsulation.

This function block encapsulates the data type conversion in an adapter context, thus simplifying the interconnection of components that rely on adapter interfaces.

## Conclusion

**AUDI_TO_ADI** offers a clean, compact solution for converting UDINT adapter data to DINT adapter data. The use of a standardized conversion function block ensures reliable and easily traceable functionality. The composite approach reduces complexity in the higher-level system and facilitates the reusability of the adapter logic.
