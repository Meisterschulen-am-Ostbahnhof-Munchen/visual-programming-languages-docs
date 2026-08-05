# UDINT_AUDI_GE
![UDINT_AUDI_GE](./UDINT_AUDI_GE.svg)

* * * * * * * * * *
## Introduction
The function block **UDINT_AUDI_GE** performs a greater-or-equals (>=) comparison for two input values. It complies with the IEC 61131-3 classification for standard comparison functions. The result is output via a directed adapter (plugs/sockets), allowing the block to be flexibly integrated into standardized adapter structures.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| REQ | Event | Service Request – triggers the comparison |

## **Event Outputs**

No direct event outputs are available. The event signal is transmitted externally via the **OUT** adapter (see Adapters).

### **Data Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| IN1 | ANY_ELEMENTARY | First comparison value |

### **Data Outputs**

No direct data outputs are available. The result value is provided via the **OUT** adapter (see Adapters).

### **Adapters**

| Direction | Name | Type | Comment |
|----------|------|-----|-----------|
| Plug | OUT | adapter::types::unidirectional::AX | Returns the comparison result (true if IN1 >= IN2) as an event and data value |
| Socket | IN2 | adapter::types::unidirectional::AUDI | Receives the second comparison value (IN2) as an event and data value |

## Functionality

This function block performs a "greater than or equal to" comparison of the two input values. The internal implementation uses the function block **F_GE** (from the library `iec61131::comparison`). The process:

1. An event at **REQ** or an incoming event from the **IN2** adapter triggers the comparison.

2. The data value **IN1** and the value provided via the **IN2** adapter are passed to **F_GE**.

3. The result (TRUE/FALSE) is output via the **OUT** adapter as an event and as a data value.

Since the second input is implemented via an adapter (socket), the source value can be dynamically provided by another function block or interface.

## Technical Features
- **Use of Unidirectional Adapters:** The function block does not rely on fixed inputs – the second operand is received via a socket (IN2). The output is via a plug (OUT), allowing the function block to be integrated into adapter-based architectures.
- **Flexible Data Types:** IN1 is declared as *ANY_ELEMENTARY*, which allows for high reusability with various numeric or elementary data types.
- **Internal Encapsulation:** The comparison logic is implemented as a sub-function (F_GE), which promotes maintainability and reusability.
- **Two Trigger Sources:** The REQ event and the event from the IN2 adapter can trigger the comparison. This enables asynchronous data provisioning.

## State Overview

The function block does not have an explicit state machine. Its functionality is purely event-driven: With each incoming event (REQ or IN2.E1), the comparison is re-executed, and the result is output via OUT.

## Application Scenarios
- **Limit Monitoring:** Comparison of measured values from various sources (e.g., sensors, databases) against a threshold value.
- **Adapter-Based Data Flows:** Integration into a component architecture where data is exchanged via standardized adapters (e.g., in automation technology or the IoT sector).
- **Configurable Comparison Function:** Thanks to the ANY_ELEMENTARY type, the function block can be used for integers, floating-point numbers, or other elementary data types.

## Comparison with Similar Function Blocks

| Function Block | Description |
|----------|---------------|
| UDINT_AUDI_GE | Greater than or equal to (>=) with adapter-based second input |
| UDINT_GT (Greater Than) | Only greater than (>), similar adapter structure |
| UDINT_EQ (Equal) | Equality (==) |
| Standard F_GE | Without adapter – both inputs as direct variables |

The key difference is the use of adapters, which allows for looser coupling and easier integration into existing adapter ecosystems.

## Conclusion

**UDINT_AUDI_GE** is a flexible comparison block for "greater than or equal to" values that shines, particularly in modular, adapter-based architectures (e.g., Eclipse 4diac), thanks to its use of unidirectional adapters. Its simple event handling and support for basic data types make it a universal tool for numerous comparison tasks in automation technology.

--

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
