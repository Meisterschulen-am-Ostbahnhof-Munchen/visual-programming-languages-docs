# AS_TO_AUDI

![AS_TO_AUDI](./AS_TO_AUDI.svg)

* * * * * * * * * *
## Introduction

The AS_TO_AUDI function block is a composite function block that performs a conversion from a SINT adapter (AS) to a UDINT adapter (AUDI). It serves as a bridge between two different adapter types and enables the seamless integration of components that use different data types.
## Interface Structure

### **Event Inputs**

Not present. Event control is handled via the adapter socket **AS_IN**.

### **Event Outputs**

Not present. Event output is handled via the adapter plug **AUDI_OUT**.

### **Data Inputs**

Not present. Data acquisition is handled via the adapter socket **AS_IN**.

### **Data Outputs**

Not present. Data output is provided via the adapter plug **AUDI_OUT**.

### **Adapter**

| Name | Type | Direction | Description |
|------|-----|----------|--------------|
| **AS_IN** | `adapter::types::unidirectional::AS` | Socket (Input) | SINT adapter that provides an input value (SINT) and a corresponding event. |
| **AUDI_OUT** | `adapter::types::unidirectional::AUDI` | Plug (Output) | UDINT adapter that outputs the converted value (UDINT) and an event. |

The adapters each contain one data element and one event element:

- **AS_IN**: Data `D1` (SINT), Event `E1`.
- **AUDI_OUT**: Data `D1` (UDINT), Event `E1`.

## Functionality

The module internally uses the IEC 61131 function `F_SINT_TO_UDINT` to convert the incoming SINT value into a UDINT value. The process is event-driven:

1. An event at element `E1` of socket **AS_IN** (e.g., from an upstream function block) is forwarded to input `REQ` of the internal conversion function block `Convert`.
2. The conversion function block reads the current value of `AS_IN.D1` and converts it into a UDINT value.
3. After successful conversion, the converter's output event `CNF` is triggered, which in turn activates the event at element `E1` of plug **AUDI_OUT**.
...3. The output event is triggered by the converter, which in turn activates the event at element `E1` of plug **AUDI_OUT**.

4. The output event is triggered by an event at element `E1` of plug **AUDI_OUT**.
5. The output event is triggered by an event at element `E1` of plug **AUDI_OUT**.
6. The event is forwarded to the input `Convert` of the internal conversion function block `Convert`.
7. The event at element qzmsdocs00008qz of socket **AS_IN** (e 4. Simultaneously, the converted value is written from `Convert.OUT` to `AUDI_OUT.D1`.

This ensures that the converted UDINT value is only available at the output when the corresponding event is signaled.

## Technical Features

- **Numeric conversion**: value-preserving cast (narrowing may truncate, widening/sign-extension is safe).

- **Composite Pattern**: The function block is implemented as a composite (composed functional block) that encapsulates a single conversion function block. This results in a reusable and encapsulated unit.
- **Use of IEC 61131 Function Blocks**: The conversion utilizes the standardized function `F_SINT_TO_UDINT`, which promotes portability and traceability.
- **Unidirectional Adapters**: Both the input and output adapters are unidirectional (no feedback). This simplifies the data flow direction.

## State Overview

The composite block does not have its own state machine (ECC). The entire sequence control is defined by the event chaining of the internal network. Therefore, there are no defined states or state transitions.

## Application Scenarios

- **System Integration**: When a subsystem provides data in SINT format via an adapter, but a subsequent subsystem expects UDINT data via an adapter.
- **Protocol Adaptation**: In heterogeneous automation systems where different data types are exchanged via adapters, this block can serve as a universal converter.
- **Network Structure Simplification**: Instead of performing the conversion directly in the application blocks, it is encapsulated in a separate composite, which improves maintainability.

## Comparison with Similar Blocks

Similar blocks exist for other data type conversions, e.g.,... For example, `AS_TO_ABOOL` (SINT to BOOL) or `AUINT_TO_AUDI` (UINT to UDINT). The present function block differs in its specific combination of SINT input and UDINT output. It adds another conversion option to the library and follows the same design pattern (composite with an internal IEC 61131 converter).

## Conclusion

The function block `AS_TO_AUDI` offers an elegant solution for converting SINT adapter data to UDINT adapter data. Encapsulating it in a composite function block improves the reusability and clarity of the overall system. The use of standardized conversion functions ensures that the conversion is correct and efficient.
