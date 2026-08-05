# AX_TO_AUDI

![AX_TO_AUDI](./AX_TO_AUDI.svg)

* * * * * * * * * *
## Introduction

The **AX_TO_AUDI** function block is a composite function block (FB) that converts a Boolean value (BOOL) provided via an AX adapter into an unsigned double-word value (UDINT) and outputs it via an AUDI adapter. It is used to convert signals between adapter interfaces, with the actual conversion performed by an internal IEC 61131 conversion block.

## Interface Structure

### **Event Inputs**

- **AX_IN.E1** (via socket adapter AX_IN): Event that triggers the conversion.


### **Event Outputs**

- **AUDI_OUT.E1** (via plug adapter AUDI_OUT): Confirmation event after successful conversion.

### **Data Inputs**

- **AX_IN.D1** (via socket adapter AX_IN, data type **BOOL**): The Boolean value to be converted.

### **Data Outputs**

- **AUDI_OUT.D1** (via plug adapter AUDI_OUT, data type **UDINT**): The converted integer value (0 or 1).

### **Adapters**

- **AX_IN** – Socket adapter of type `adapter::types::unidirectional::AX`

Accepts a Boolean value (and an associated event).


- **AUDI_OUT** – Plug adapter of type `adapter::types::unidirectional::AUDI`

Provides the converted UDINT value (and an acknowledgment event).

## Functionality

The function block operates in an event-driven manner:

1. An event at the event input **AX_IN.E1** triggers the internal conversion block `F_BOOL_TO_UDINT` via its event input **REQ**.

2. The data value **AX_IN.D1** (BOOL) is forwarded to the data input **IN** of the conversion block.

3. The conversion block converts the Boolean value into a UDINT (FALSE → 0, TRUE → 1) and outputs the result at its output **OUT**.

4. The result is passed to the data output **AUDI_OUT.D1**.

5. After the conversion is complete, the acknowledgment event of the conversion block (**CNF**) is passed to the event output **AUDI_OUT.E1**.

## Technical Features

- **Composite block (FB)** according to IEC 61499-2.

- Uses the internal FB `iec61131::conversion::F_BOOL_TO_UDINT` for the actual conversion.

- The adapter interfaces (`AX` and `AUDI`) enable modular and standardized integration with other blocks.

- The block is open source and licensed under the Eclipse Public License 2.0.

## State Overview

The block does not have its own state machines. The behavior is entirely determined by the sequential processing of the internal conversion block:

- **Idle**: Waiting for an event at **AX_IN.E1**.

- **Conversion active**: After receiving the event, the conversion is performed; no further events are processed during this time (single execution).

- **Completion**: The output event is sent, after which the block returns to the idle state.

## Application Scenarios

- Conversion of a digital sensor signal (e.g., limit switch) into a numerical value for further processing in a PLC.

- Adaptation between different adapter interfaces in IEC 61499-based automation systems.

- Use in systems where only Boolean values are available via an AX interface, but a UDINT interface is required (e.g., for diagnostic or counting purposes).

## Comparison with Similar Function Blocks

- **F_BOOL_TO_UDINT** (direct): Performs the same conversion but requires separate event and data connections. **AX_TO_AUDI** encapsulates this logic in an adapter-based interface.

- **AX_TO_* function blocks**: Analogous to this function block, but with different target data types (e.g., INT, DINT). This function block is based on the UDINT variant.

- **Adapter coupler**: Pure pass-through function blocks without conversion – unlike **AX_TO_AUDI**, which performs an active type conversion.


## Conclusion

The **AX_TO_AUDI** function block provides a simple yet useful bridge between Boolean and integer adapter interfaces. By encapsulating the conversion in a composite block, the design becomes clearer and reusability is increased. It is particularly suitable for standard conversion tasks in IEC 61499 projects that use modular adapter interfaces.