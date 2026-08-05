# ADI_SPLIT_9

![ADI_SPLIT_9](./ADI_SPLIT_9.svg)

* * * * * * * * * *

## Introduction

The function block `ADI_SPLIT_9` is a generic component that splits an incoming ADI signal (adapter) into nine identical output signals. It functions purely as a splitter at the adapter level.

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

- **IN** (Socket): Adapter type `adapter::types::unidirectional::ADI` – Input signal.

- **OUT1** to **OUT9** (Plugs): Nine adapters of the same type – outputs that pass the input signal on unchanged.

## Functionality

The function block forwards the ADI signal present at socket `IN` to all nine plugs `OUT1` to `OUT9`. No signal processing or conversion takes place; the distribution is purely structural via the adapter connections. Due to the unidirectional adapter type, the data flow direction from the socket to the plugs is fixed.

## Technical Features

- The function block is defined as a generic function block (attribute `eclipse4diac::core::GenericClassName` = `'GEN_ADI_SPLIT'`) and can therefore be reused in different projects.

- It has neither events nor data inputs/outputs; all functionality resides in the adapter topology.



``` - The type hash attribute is empty, indicating a simple, non-versioned execution.

## State Overview

The function block has no state machines or algorithms. It is purely passive and does not react to events.

## Application Scenarios

- Distributing an analog or digital sensor signal (as ADI) to multiple downstream function blocks.

- Splitting a control signal in an automation system to control identical actuators in parallel.

- Generating signal copies for monitoring, testing, or diagnostic purposes.

## Comparison with Similar Function Blocks

- Unlike data- or event-based splitters, `ADI_SPLIT_9` operates at the higher adapter level, enabling clean architectural separation.

- Similar function blocks exist with a variable number of outputs (e.g., `ADI_SPLIT_M`), while this function block offers a fixed number of nine outputs.


## Conclusion

`ADI_SPLIT_9` is a simple, generic function block for 1-to-9 distribution of a unidirectional ADI signal. It is suitable for applications that require multiple, identical forwarding of adapter signals without additional logic.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)


```