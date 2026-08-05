# A2X_SPLIT_9
![A2X_SPLIT_9](./A2X_SPLIT_9.svg)
* * * * * * * * * *
## Introduction
The **A2X_SPLIT_9** is a generic function block that splits one incoming A2X adapter (socket) into nine separate A2X output adapters (plugs). It enables the star topology distribution of an A2X signal to up to nine independent receivers without requiring any dedicated logic or state machines.
## Interface Structure
### **Event Inputs**
None

### **Event Outputs**
None

### **Data Inputs**
None

#### **Data Outputs**
None

#### **Adapters**

| Type | Name | Direction | Description |

|-----|------|----------|--------------|

| Socket | IN | Input | Incoming A2X adapter, whose signals are distributed to the nine outputs. |

| Plug | OUT1 … OUT9 | Output | Nine identical A2X output adapters that forward the input data. |

## Functionality
This function block has no internal logic or state machines. It functions purely as a "wiring aid" in the 4diac IDE: The A2X adapter connected to socket **IN** is passed unchanged and in parallel to all nine plugs **OUT1** to **OUT9**. Thus, all connected receivers receive identical signals to the input.

```
## Technical Features

- **Generic Function Block**: The function block is declared as generic (attribute `GenericClassName` = `'GEN_A2X_SPLIT'`). It can be parameterized for various specific A2X adapter types in the IDE.
- **No Runtime Logic**: The function block contains no ECC (Execution Control Chart) and no algorithms – all functionality is implemented through the internal connection of the adapters.
- **Unidirectional Adapters**: The adapters used, `adapter::types::unidirectional::A2X`, only allow data flow in one direction (from the socket to the plugs).

## State Overview
A state overview is not required, as the function block has no internal state. Data flow is continuous and uncontrolled by events.

## Application Scenarios
- **Signal Distribution in Automation**: Distributing an analog or binary A2X signal to multiple actuators or higher-level controllers.
- **Test and Simulation Setups**: Feeding a reference signal into multiple parallel test paths.
- **Topology Implementation**: Star-shaped cabling in the graphical configuration to utilize a central data point multiple times.

## Comparison with Similar Function Blocks
- **A2X_SPLIT_N**: A configurable splitter with a variable number of outputs, e.g., 2, 4, or 8. The **A2X_SPLIT_9** is fixed to nine outputs.
- **A2X_MERGE**: The reverse function block that combines multiple inputs into one output (e.g., for bus topologies).
- **Event-Based Splitters**: Function blocks like `SPLIT` or `E_SPLIT` operate with event signals and require control logic – the **A2X_SPLIT_9** does not require events.

## Conclusion

The **A2X_SPLIT_9** is a simple yet effective function block for distributing an A2X signal to nine identical outputs. Its generic nature and lack of internal logic make it lightweight and ideal for pure wiring scenarios in the 4diac IDE. It is particularly well-suited for applications where a signal is needed multiple times without requiring additional programming.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
