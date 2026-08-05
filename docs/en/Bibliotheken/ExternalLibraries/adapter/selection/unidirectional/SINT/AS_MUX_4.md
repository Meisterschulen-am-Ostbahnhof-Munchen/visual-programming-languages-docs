# AS_MUX_4

![AS_MUX_4](./AS_MUX_4.svg)

* * * * * * * * * *

## Introduction

The function block **AS_MUX_4** is a generic multiplexer for unidirectional AS data streams. It allows the selection of one of four AS inputs (IN1…IN4) and provides the selected data stream to the AS output (OUT). Selection is made via an index K, which is evaluated upon the arrival of the REQ event. The block is used in the 4diac IDE and is stored as a generic FB with the class name `GEN_AS_MUX`.

## Interface Structure

### **Event Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| REQ | Event | Set Index K |


The **REQ** input triggers the multiplexing operation. With each event, the current value of **K** is read, and the corresponding AS input is switched to the output.

### **Event Outputs**

| Name | Type | Comment |

|------|-----|-----------|

| CNF | Event | Confirmation of Set Index K |

After a successful switchover, the **CNF** event is output. It confirms that the connection defined by the index **K** has been established.

### **Data Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| K | UINT | Index (0…3) |

The **K** data input defines the path to be selected. Valid values are 0 to 3 for inputs IN1 to IN4.


### **Data Outputs**

No explicit data outputs, as the output is implemented as an AS adapter (plug).

### **Adapter**

| Name | Type | Direction | Comment |

|------|-----|----------|-----------|

| OUT | adapter::types::unidirectional::AS | Plug | AS output: provides the data stream of the selected input |

| IN1 | adapter::types::unidirectional::AS | Socket | AS input 1 (Index 0) |

| IN2 | adapter::types::unidirectional::AS | Socket | AS input 2 (Index 1) |

| IN3 | adapter::types::unidirectional::AS | Socket | AS input 3 (Index 2) |

| IN4 | adapter::types::unidirectional::AS | Socket | AS Input 4 (Index 3) |

The adapters are of type `adapter::types::unidirectional::AS`. The **OUT** plug is connected to the selected socket; all unselected sockets remain inactive.

## Functionality

The function block operates in an event-driven manner:

1. An event at the **REQ** input triggers processing.

2. The current value of the **K** data input is read.

3. Depending on **K** (0, 1, 2, or 3), the corresponding AS input (**IN1**, **IN2**, **IN3**, or **IN4**) is switched to the AS output **OUT**.

4. After the switch, the confirmation event **CNF** is output.

The block has no internal data storage or state machine; the switch occurs anew with each REQ event.


## Technical Features

- **Generic Implementation:** The function block is declared as a generic block (`GEN_AS_MUX`), which allows for easy reuse and adaptation in different projects.

- **Adapter-Based Communication:** All data flow occurs via AS adapters, not via individual data ports. This simplifies the connection with other AS-compatible blocks.

- **Restricted Index Range:** The index **K** must be within the range 0…3; values outside this range result in undefined behavior. The application is responsible for validating the index.

- **No Internal State:** The function block has no ECC (Execution Control Chart) – processing occurs directly and without delay with each REQ.

## State Overview

The function block has **no explicit state machine**. There is only an implicit state, "Ready," in which it waits for a REQ event. Upon receipt of REQ, the switching is executed and CNF is immediately sent. No error state is defined.

## Application Scenarios

- **Sensor Data Selection:** Selection of one of four analog or digital sensor values provided via AS adapters.

- **Parameterization:** Switching between different parameter sets in a control logic.

- **Signal Routing:** Selective switching of AS data streams depending on a control index.

- **Test and Simulation Environments:** Targeted selection of test signals for testing purposes.

## Comparison with Similar Function Blocks

- **AS_MUX_2:** A multiplexer with only two inputs. This function block extends the flexibility to four inputs.

- **Standard MUX Function Blocks:** Often implemented with single data ports (e.g., INT, BOOL). The function block shown here, however, works exclusively with AS adapters, enabling consistent data transmission in AS-based systems.

- **Decomposition into multiple AS_MUX_2:** In principle possible, but less efficient and clear.

## Conclusion

The **AS_MUX_4** function block offers an elegant and flexible way to select one of four AS data sources. Thanks to its adapter-based interface, it integrates seamlessly into the 4diac IDE and AS communication structures. Its simple, event-driven operation makes it a fundamental building block for selection tasks in automation technology. Its generic design allows for easy integration into a wide variety of projects.

--

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]