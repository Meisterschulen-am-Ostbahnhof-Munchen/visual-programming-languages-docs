# AUDI_TO_AB
![AUDI_TO_AB](./AUDI_TO_AB.svg)

* * * * * * * * * *
## Introduction
The **AUDI_TO_AB** function block is a composite function block (FB) that converts a UDINT interface (AUDI, 32-bit unsigned integer) into a BYTE interface (AB, 8-bit). It encapsulates the conversion logic and provides two unidirectional adapters: a socket for the AUDI input and a plug for the AB output. This function block is typically used to enable data communication between systems that use different data types via adapters.
## Interface Structure

### **Event Inputs**

| Name | Type | Description |
|------|-----|---------------|
| `AUDI_IN.E1` | Event (via adapter) | Trigger for data conversion – an incoming event starts the conversion of the current UDINT value to a BYTE value. |

### **Event Outputs**

| Name | Type | Description |
|------|-----|--------------|
| `AB_OUT.E1` | Event (via adapter) | Conversion confirmation – after successful conversion, an event is output that signals the new BYTE value to the downstream system. |

### **Data Inputs**

| Name | Type | Description |
|------|-----|--------------|
| `AUDI_IN.D1` | UDINT (32-bit) | The 32-bit unsigned integer value to be converted, provided via the AUDI adapter. |

### **Data Outputs**

| Name | Type | Description |
|------|-----|--------------|
| `AB_OUT.D1` | BYTE (8-bit) | The converted 8-bit value, output via the AB adapter. |

### **Adapters**

| Name | Type | Direction | Description |
|------|-----|----------|--------------|
| `AUDI_IN` | adapter::types::unidirectional::AUDI | Socket (Input) | Unidirectional adapter that provides events and data of type UDINT. |
| `AB_OUT` | adapter::types::unidirectional::AB | Plug (Output) | Unidirectional adapter that outputs events and data of type BYTE. |

## Functionality

1. An external system sends an event via the adapter `AUDI_IN` (E1).

2. This event triggers the internal conversion block `F_UDINT_TO_BYTE` (from the IEC 61131 library) via its `REQ` input.

3. Simultaneously, the current data value from `AUDI_IN.D1` is transferred to the `IN` input of the conversion module.

4. The conversion module converts the UDINT value into a BYTE value and stores the result at its `OUT` output.

5. After the conversion is complete, `F_UDINT_TO_BYTE` sends an acknowledgment event (`CNF`), which is forwarded to the `AB_OUT` adapter (E1).

6. Simultaneously, the converted BYTE value is output to `AB_OUT.D1` and is available to the receiving system.
...`` ``` ``` ``` ``` ``` ``` ``` ``` The entire processing is event-driven and without intermediate storage – each incoming event generates exactly one outgoing event.

## Technical Features
- **Composite Structure**: The function block is implemented as a network of sub-functions. It uses the predefined conversion function block `F_UDINT_TO_BYTE` from the IEC 61131 library, ensuring standardized and testable conversion.
- **Unidirectional Adapters**: Both the input and output adapters are unidirectional. This reduces coupling and enables easy integration into data flows that only require one direction.
- **No State Storage**: The function block is purely combinatorial (no internal states). It reacts to each incoming event immediately and outputs the result without delay.
- **Compatibility**: Complies with the IEC 61499-2 standard and can be used in environments that support unidirectional adapters (AUDI/AB).

## State Overview

This function block does not have an explicit state machine. It operates event-driven according to the principle "input event → conversion → output event". There are no queues or delays – processing is atomic and occurs within a single cycle.

## Application Scenarios
- **Data Adaptation in Adapter-Based Systems**: If a component or protocol delivers a UDINT value via an AUDI adapter, but the downstream function block expects a BYTE value via an AB adapter, this function block can be used for seamless coupling.
- **Transition from 32-bit to 8-bit interfaces**: For example, in sensor-actuator communication, where a sensor provides 32-bit raw data, but the actuator only processes 8-bit commands.
- **Test and simulation environments**: Allows easy replacement of adapters without having to change the entire data path logic.

## Comparison with similar function blocks

| Function block | Description | Difference to AUDI_TO_AB |
|----------|---------------|-----------------------------|
| `F_UDINT_TO_BYTE` | Direct conversion function without adapters | Expects standard event and data interfaces; AUDI_TO_AB encapsulates the conversion in adapter signatures. |
| `UDINT_TO_BYTE` (Composite with standard ports) | Similar logic, but with a SOCKET/PLUG interface | May use different adapter types or bidirectional interfaces; AUDI_TO_AB is specialized for unidirectional adapters. |

## Conclusion

The **AUDI_TO_AB** function block offers a clean, reusable solution for type conversion between UDINT and BYTE values using unidirectional adapters. Its compact composite structure, based on a standardized IEC conversion function, makes it reliable and easy to integrate. Its event-driven architecture without state storage makes it particularly suitable for time-critical data flows in automation technology.
