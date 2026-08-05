# AI_MUX_4

![AI_MUX_4](./AI_MUX_4.svg)

* * * * * * * * * *

## Introduction

The function block **AI_MUX_4** implements a generic multiplexer for analog input signals (adapter type `AI`). It selects one of four analog inputs based on an integer index `K` and outputs its value via the output adapter `OUT`. The block is used for the flexible switching of analog measurement or control signals in automation systems.

## Interface Structure

### **Event Inputs**

| Name | Type | Comment |

|------|-------|-------------------------------|

| REQ | Event | Starts selection based on `K` |

### **Event Outputs**

| Name | Type | Comment |

|------|-------|-----------------------------------------|

| CNF | Event | Confirmation that selection has been made |

### **Data Inputs**

| Name | Type | Comment |

|------|------|----------------|

| K | UINT | Index (0..3) of the input to be selected |

### **Data Outputs**

*(none)*

### **Adapters**

**Output Adapter (Plug):**

| Name | Type | Comment |

|------|----------------------------------|---------------------------------------------------------------------------|

| OUT | adapter::types::unidirectional::AI | Output signal – corresponds to the input IN1..IN4 selected by `K` |

**Input Adapters (Sockets):**

| Name | Type | Comment |

|------|----------------------------------|------------------------------|

| IN1 | adapter::types::unidirectional::AI | Analog Input 1 (K = 0) |

| IN2 | adapter::types::unidirectional::AI | Analog Input 2 (K = 1) |

| IN3 | adapter::types::unidirectional::AI | Analog Input 3 (K = 2) |

| IN4 | adapter::types::unidirectional::AI | Analog Input 4 (K = 3) |

## Functionality

The function block processes an event `REQ`. Upon arrival of `REQ`, the value of the data input `K` is evaluated. Since `K` is of type `UINT`, only the values 0, 1, 2, or 3 are used meaningfully. The corresponding `IN` adapter (`IN1` for `K = 0`, `IN2` for `K = 1`, etc.) is switched to the output adapter `OUT`. Once the switchover is complete, the event `CNF` is triggered. Multiple processing attempts are possible at any time by resending `REQ`.

## Technical Features

- **Generic Block**: The function block is declared as a generic type (`GenericClassName = 'GEN_AI_MUX'`), which allows reuse with different specific adapter types.

- **Adapter Communication**: All interfaces (IN1..IN4, OUT) are implemented as unidirectional adapters of type `adapter::types::unidirectional::AI`. This enables loose coupling between connected blocks and a clean separation of data and event flows.

- **No Dedicated Data Outputs**: The analog signal is forwarded exclusively via the adapter `OUT`, not via separate data outputs.


## State Overview

This function block has no explicitly modeled states (no ECC description). Its behavior is purely event-driven:

1. Wait for `REQ`.

2. Upon `REQ`: Read `K`, select the appropriate input adapter value, and assign it to `OUT`.

3. Output `CNF`.

4. Return to the wait state.

## Application Scenarios

- **Analog Multiplexing**: Select one of four analog sensors (e.g., temperature, pressure, level) for further processing in a PLC or control system.

- **Control Signal Switching**: Dynamic selection between different analog control signals (e.g., setpoints) for a control system.

- **Test and Diagnostic Functions**: Switching between normal and test inputs without changing the topology.

## Comparison with Similar Function Blocks

- **AI_MUX_2**: A multiplexer with only two inputs. `AI_MUX_4` extends the number to four, making it suitable for systems with multiple analog sources.

- **DI_MUX_4**: Digital multiplexer for binary signals. This function block processes analog adapter data, which typically contains floating-point or integer values.

- **Manual Switching**: Without a multiplexer, the connection between source and sink would have to be made through program or wiring changes; this function block offers flexible, index-based selection at runtime.

## Conclusion

The **AI_MUX_4** is a compact, generic function block for selecting one of four analog signals via an index. It simplifies the switching of analog paths in 4diac-based automation solutions and can be seamlessly integrated into existing projects thanks to its adapter interfaces. The absence of a state machine description makes it particularly easy and quick to implement.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]