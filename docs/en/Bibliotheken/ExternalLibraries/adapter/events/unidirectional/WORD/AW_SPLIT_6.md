# AW_SPLIT_6

Image not available
![AW_SPLIT_6](./AW_SPLIT_6.svg)

* * * * * * * * * *
## Introduction

The **AW_SPLIT_6** function block is used to split an incoming unidirectional **AW** adapter into six identical output adapters. It is designed as a generic function block used in the 4diac IDE for distributing AW signals. The function block is intended for applications where a signal value—e.g., an analog or digital value—is required multiple times in parallel without the need for manual duplication of the connections.

## Interface Structure

### **Event Inputs**

None

### **Event Outputs**

None

### **Data Inputs**

None

### **Data Outputs**

None

### **Adapters**

| Type | Name | Direction | Description |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::AW` | IN | Socket | Input adapter for the AW signal to be distributed |
| `adapter::types::unidirectional::AW` | OUT1 – OUT6 | Plugs | Six output adapters, each providing an identical copy of the input signal |

## Functionality

The module receives a unidirectional **AW** signal via the **IN** socket. This signal is internally duplicated to all six output plugs (**OUT1** to **OUT6**). The signal is passed through without delay or data manipulation – the value of the incoming adapter is made directly available at each of the six outputs. The module has no state logic or event control of its own; it operates purely passively and simply passes the signal through.

# Functionality ## Technical Features

- **Generic Type**: The function block is implemented as a generic function block (`GEN_AW_SPLIT`), allowing for flexible reuse in different projects.
- **Type Hash**: The type hash property is empty, meaning that no automatic type identity check is performed during instantiation.
- **No Event or Data Ports**: All signal transmission occurs exclusively via adapters. Events are not processed; therefore, the function block is only suitable for pure data transmission without timing.

## State Overview

The function block has no internal states. It is a pure split function block without sequential logic. Its behavior is deterministic and always identical: The input signal is copied to all outputs.

## Application Scenarios

- **Distribution of an analog measured value** to multiple consumers (e.g., displays, controllers, recording systems)
- **Splitting a digital control signal** to parallel actuator or sensor interfaces
- **Star-shaped signal distribution** in modular control architectures where one source supplies multiple sinks

## Comparison with Similar Function Blocks

Compared to an **AW_SPLIT_2** or **AW_SPLIT_4**, this function block offers a higher number of outputs (6). This makes it particularly suitable for systems with many parallel receivers. Alternatively, several smaller Split function blocks could be cascaded, but this can negatively impact clarity and performance. The **AW_SPLIT_6** is optimized as a complete solution for this requirement.

## Conclusion

The **AW_SPLIT_6** is a simple yet useful function block for multiplying a unidirectional AW signal to six outputs. Due to its generic nature and adapter-based interface, it integrates seamlessly into a 4diac environment. It is recommended for all applications where a single signal is needed multiple times without any detours.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
