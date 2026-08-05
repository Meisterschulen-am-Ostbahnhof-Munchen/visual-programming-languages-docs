# ATM_MUX_4

![ATM_MUX_4](./ATM_MUX_4.svg)

* * * * * * * * * *
## Introduction
The function block `ATM_MUX_4` is a generic multiplexer that switches one of four ATM adapter inputs to an output adapter. Selection is made via an index `K`. The block is designed for use in agricultural control systems (according to IEC 61499) and can be renamed application-specifically using `GenericClassName`.

## Interface Structure
### **Event Inputs**

| Name | Type | Comment |

|------|-------|-----------------------|

| REQ | Event | Set Index K (Select Input) |


The event input `REQ` triggers the multiplexer function. It is linked to the data input variable `K`.

### **Event Outputs**

| Name | Type | Comment |

|------|-------|----------------------------------|

| CNF | Event | Confirmation of Set Index K |

After successful switching of the output to the input determined by `K`, the event `CNF` is output.

### **Data Inputs**

| Name | Type | Comment |

|------|------|-----------|

| K | UINT | index |


This integer value determines which of the four ATM adapter inputs is routed to the output. Valid values: 0, 1, 2, 3.

### **Data Outputs**
The module does not have its own data outputs. Data is transmitted exclusively via the adapters.

### **Adapters**

| Name | Type | Comment |

|------|-----------------------------------------|---------------------------------------------|

| IN1 | `adapter::types::unidirectional::ATM` | Input value 1 (K = 0) |

| IN2 | `adapter::types::unidirectional::ATM` | Input value 2 (K = 1) |

| IN3 | `adapter::types::unidirectional::ATM` | Input value 3 (K = 2) |

| IN4 | `adapter::types::unidirectional::ATM` | Input value 4 (K = 3) |

| OUT | `adapter::types::unidirectional::ATM` | IN1 for K=0, IN2 for K=1, IN3 for K=2, IN4 for K=3 |

**Note:** The designation "IN" in the output comment refers to the source adapters – the output forwards the data stream of the corresponding input.

## Functionality
1. At the time of the event `REQ`, the current value (0…3) at `K` is read.

2. The module connects the output adapter `OUT` to the input adapter corresponding to the following index:

- `K = 0` → `IN1`

- `K = 1` → `IN2`

- `K = 2` → `IN3`

- `K = 3` → `IN4`

3. After a successful connection, the acknowledgment event `CNF` is sent.

The adapters are typed as unidirectional ATM interfaces. The multiplexer operates purely event-driven – a change to `K` without `REQ` is ignored.

## Technical Features

- **Generic Block** – The function block can be given any name in the IDE (e.g., Eclipse 4diac) via the attribute `eclipse4diac::core::GenericClassName`, e.g., `GEN_ATM_MUX`. This facilitates reuse in different projects.

- No separate state diagram is required – the logic is reduced to simple switching.

- The adapters are of type `unidirectional::ATM`, meaning data flows only in one direction (from input to output).

## State Overview
The `ATM_MUX_4` does not have an explicitly modeled state machine. The behavior is limited to:

- **Waiting for REQ**: The output is connected to the last set input.

- **Execution on REQ**: The output is switched to the input specified by `K`, and `CNF` is output.

An incorrect index specification (values outside 0…3) is ignored – the function block relies on correct inputs.

## Application Scenarios

- **Agricultural Control**: Switching between different ATM data sources (e.g., sensors, actuators) in control systems according to IEC 61499.

- **Data Stream Selection**: Selecting one of four ATM signals for further processing in higher-level logic.

- **Test and Simulation Environments**: Creating targeted connections between virtual components.


## Comparison with Similar Components

- **Standard multiplexer components (e.g., MUX2, MUX4)** typically work with elementary data types (INT, BOOL). The `ATM_MUX_4` is specifically designed for the "ATM" adapter type, allowing direct, protocol-compliant forwarding without data conversion.

- **Adapter-based multiplexers** are less common than data multiplexers. This component encapsulates all switching logic within a single function block, improving network clarity.

## Conclusion

The `ATM_MUX_4` is a compact, generic function block for selecting one of four ATM adapter inputs. It is particularly suitable for event-driven applications in agricultural control systems where unidirectional ATM data streams need to be switched. The ability to rename generically and the clear, event-based interface make it highly versatile.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]