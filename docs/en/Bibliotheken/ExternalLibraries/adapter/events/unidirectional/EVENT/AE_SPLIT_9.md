# AE_SPLIT_9

![AE_SPLIT_9](./AE_SPLIT_9.svg)

* * * * * * * * * *
## Introduction
The AE_SPLIT_9 function block is used to split an incoming unidirectional adapter event (AE) into nine identical outputs. It is implemented as a generic function block and allows events to be distributed to multiple downstream function blocks.

## Interface Structure
### **Event Inputs**
None.

### **Event Outputs**
None.

### **Data Inputs**
None.

### **Data Outputs**
None.


### **Adapter**

- **IN** (Socket): Unidirectional AE adapter (input)

- **OUT1 … OUT9** (Plugs): Unidirectional AE adapters (outputs)

## Functionality
The function block receives an adapter event via the "IN" socket. Each incoming event is duplicated to all nine plug outputs (OUT1 to OUT9) without delay or further logic. Thus, the function block behaves like a 1:9 splitter for AE signals.

## Technical Features
- The function block is implemented as a generic function block (GenericClassName = 'GEN_AE_SPLIT'), which allows for flexible reuse in different contexts.

- No data is processed; only the adapter interface is passed through.

- The outputs are independent of each other; a fault on one output does not affect the others.

## State Overview
The function block has no internal state. It operates purely combinatorially: An event at the input immediately triggers events at all outputs.

## Application Scenarios
- Distribution of a sensor event to multiple control logics.

- Broadcast of an alarm to various monitoring units.

- Splitting a trigger signal for parallel processing paths.

## Comparison with Similar Function Blocks
- AE_SPLIT_2, AE_SPLIT_4: same functionality with fewer outputs.

- Unlike data splitters (e.g., SPLIT_INT), this function block only replicates events (without data).

## Conclusion

AE_SPLIT_9 is a simple yet useful function block for event distribution in IEC 61499 systems. Its generic nature and clear 1:9 split make it ideal for applications requiring a wide distribution of adapter events.