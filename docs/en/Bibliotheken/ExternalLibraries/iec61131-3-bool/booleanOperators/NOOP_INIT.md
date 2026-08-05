# NOOP_INIT
![NOOP_INIT](./NOOP_INIT.svg)

* * * * * * * * * *
## Introduction
The function block **NOOP_INIT** (No Operation with INIT) serves as a simple pass-through or placeholder block. It enables the initialization and normal data transmission of a Boolean signal from an input to an output. Its special feature lies in the additional handling of the INIT event, which triggers both an acknowledgment (INITO) and data transmission.
## Interface Structure
### **Event Inputs**

| Name | Type | Comment |

|------|-----|------------|

| INIT | EInit | Initialization Request |

| REQ | Event | Normal Execution Request (connected to IN) |

### **Event Outputs**

| Name | Type | Comment |

|------|-----|-----------|

| INITO | EInit | Initialization Acknowledgement |

| CNF | Event | Execution Acknowledgement (connected to OUT) |

### **Data Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| IN | BOOL | Input Signal |

### **Data Outputs**

| Name | Type | Comment |

|------|-----|-----------|

| OUT | BOOL | Output Signal (corresponds to IN after one iteration) |

### **Adapters**
No adapters available.

## Functionality

The function block processes incoming events as follows:

1. **INIT Event**:

- An **INITO** event is immediately triggered.
- Simultaneously, the `F_MOVE` function block is triggered internally, which copies the value from `IN` to `OUT`. Upon completion of this copy operation, the **CNF** event is triggered.

2. **REQ Event**:

- The same `F_MOVE` function block is activated, which transfers `IN` to `OUT`. Upon completion, **CNF** is triggered.

As a result, data is transferred during both INIT and REQ, and an acknowledgment event is generated in each case. The data output `OUT` always corresponds to the last received value of the input `IN`.

## Technical Features
- The function block internally uses an instance of the standard FB `iec61131::selection::F_MOVE` for data copying.
- The INIT process is twofold: It immediately acknowledges with `INITO` and simultaneously executes the data transfer. This can be useful for initialization sequences where the system should start working after the first input of a start value.
- There are no internal states or timings; the response is event-driven.

## State Overview
The FB does not have an explicit state machine; its behavior is purely event-driven:

- In the idle state (no event), the inputs wait.
- Data copying is started on **INIT** or **REQ**; Upon completion, `CNF` is sent. Upon INIT, `INITO` is also immediately emitted.

## Application Scenarios
- **Placeholder** in the development phase: Instead of a complex function block, NOOP_INIT is inserted to test data flows.
- **Debugging**: The explicit INIT event can be used to set an initial value and simultaneously receive confirmation.
- **Signal coupling**: When a signal needs to be passed on unchanged, but the INIT interface of a subsequent function block needs to be accessed.
- **Testing initialization sequences**: Simulation of a start routine that sets a value and acknowledges it.

## Comparison with similar function blocks
- **NOOP (without INIT)**: Simple pass-through function block without an initialization event. NOOP_INIT extends this with the INIT/INITO pairing.

**NOOP (without INIT)**: Simple pass-through function block without an initialization event. - **MOVE (direct)**: A pure data copier without event handling; NOOP_INIT offers an event-driven version with acknowledgments.

- **E_CYCLE or E_PERMIT**: These blocks control events but do not transfer data. NOOP_INIT combines data transfer with event forwarding.

## Conclusion
The **NOOP_INIT** function block is a simple yet flexible utility block for event-driven data transfer. Its combination of INIT and REQ events makes it particularly suitable for initialization processes and test environments. Its internal structure makes it easy to understand and integrates well into existing 4diac networks.

--

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
