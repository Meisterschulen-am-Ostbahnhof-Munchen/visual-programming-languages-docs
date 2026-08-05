# AB_DEMUX_5
![AB_DEMUX_5](./AB_DEMUX_5.svg)

* * * * * * * * * *
## Introduction
The function block **AB_DEMUX_5** is a generic AB demultiplexer with five outputs. It receives a data value via a single AB adapter socket and forwards it to one of the five AB adapter plugs. The target output is selected via an index, which is set via the event input **REQ** together with the data value **K**.
## Interface Structure
### **Event Inputs**

| Event | Description |

|----------|--------------|

| REQ | Triggers the demultiplex operation; takes the index **K** and forwards the value to the corresponding output adapter. |

### **Event Outputs**

| Event | Description |
|----------|--------------|

CNF | Confirms successful completion of the demultiplex operation. |

### **Data Inputs**

| Name | Data Type | Description |

|------|----------|--------------|

K | UINT | Index that specifies the destination output (1–5). |

### **Data Outputs**
No direct data outputs – output is provided via the adapter plugs.

### **Adapters**
**Socket (Input):**

| Name | Adapter Type | Description |

|------|------------|--------------|

IN | adapter::types::unidirectional::AB | Value to be demultiplexed. |

**Plugs (Outputs):**

| Name | Adapter Type | Description |

|------|------------|--------------|

| OUT1 | adapter::types::unidirectional::AB | Target output at K = 1 |

| OUT2 | adapter::types::unidirectional::AB | Target output at K = 2 |

| OUT3 | adapter::types::unidirectional::AB | Target output at K = 3 |

| OUT4 | adapter::types::unidirectional::AB | Target output at K = 4 |

| OUT5 | adapter::types::unidirectional::AB | Target output at K = 5 |

## Functionality
1. The function block expects a valid value from the AB adapter at socket **IN**.

2. As soon as the **REQ** event arrives, the index at input **K** is evaluated.

3. The value of **IN** is transferred to plug **OUTX** (X = K). For K = 1, OUT1 is used; for K = 2, OUT2, and so on.

4. After successful forwarding, the **CNF** event is output.

5. If K is outside the range 1–5, the behavior is unspecified – typically, no output is updated, and CNF is not generated.

## Technical Features
- **Generic Function Block**: The function block is declared as a generic type (see attribute `GenericClassName = 'GEN_AB_DEMUX'`) and can be instantiated for various AB adapter variants.
- **Adapter-based**: Data exchange occurs exclusively via adapters (unidirectional AB type), not via traditional data ports.
- **No ECC implemented**: The logic is implicit – the function block performs the demultiplex operation immediately upon each REQ, without an explicit state machine.
- **Simple index scheme**: The index K is interpreted directly as the 1-based number of the outputs.

## State overview
The function block does not have an exposed state machine. Its internal behavior can be described as follows:

- **Ready**: Waiting for REQ.
- **Processing**: After REQ, K is read and the value is passed from IN to the corresponding OUT.
- **Acknowledge**: Sending CNF.

Possible error states (invalid index) are not defined; this should be avoided by the caller.

## Application Scenarios
- **Actuator Selection**: A sensor value (e.g., AB data) is to be selectively transferred to one of five machines.
- **Signal Routing**: In a controller with multiple parallel communication paths, the demultiplexer can be used to direct a data stream to one of five branches.
- **Test Environments**: Simulation of multiplexing/demultiplexing operations in conjunction with corresponding counterpart blocks.

## Comparison with Similar Blocks
- **AB_DEMUX_5 vs. AB_MUX_5**: While the multiplexer combines multiple inputs into one output, the demultiplexer distributes one input across multiple outputs.
- **AB_DEMUX_5 vs. AB_DEMUX_3**: The number of outputs is the key difference; the demultiplexer with three outputs only has plugs OUT1–OUT3.

**AB_DEMUX_5 vs. AB_DEMUX_3**:** The number of outputs is the key difference; the demultiplexer with three outputs only has plugs OUT1–OUT3. - **Generic Variants**: The generic declaration allows the same function block to be reused in different adapter contexts (e.g., with different data formats).

## Conclusion
The AB_DEMUX_5 is a compact, generic demultiplexer for unidirectional AB adapters. It enables clean and flexible data forwarding to up to five destinations based on an index and is particularly suitable for modular control architectures where a communication interface needs to be distributed across multiple actuators.
