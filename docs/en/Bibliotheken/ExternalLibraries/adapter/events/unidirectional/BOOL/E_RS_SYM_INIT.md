# E_RS_SYM_INIT
![E_RS_SYM_INIT](./E_RS_SYM_INIT.svg)

* * * * * * * * * *
## Introduction
The function block **E_RS_SYM_INIT** is an event-driven, bistable toggle switch (flip-flop) with symmetrical startup behavior and explicit initialization. It implements the familiar RS flip-flop logic, where the output **Q** can be set to either TRUE or FALSE during initialization (event **INIT**) – depending on the value of the parameter **Q_INIT**. This enables defined behavior after a system startup or reinitialization.
## Interface Structure

### **Event Inputs**

| Event | Type | Comment |

|----------|-----|-----------|

| **INIT** | EInit | Initialization Request; Takes the values of **QI** and **Q_INIT** |

**R** | Event | Resets output **Q** |

**S** | Event | Sets output **Q** |

### **Event Outputs**

| Event | Type | Comment |

|----------|-----|-----------|

**INITO** | EInit | Initialization confirmation; passes the value of **QO** |

**EO** | Event | Indicates that output **Q** has changed |

### **Data Inputs**

| Variable | Type | Comment |

|----------|-------|-----------|

**QI** | BOOL | Event Qualifier: Set/reset operations are only executed if *QI=TRUE*. During initialization, *QI* sets the value of **QO**. |

| **Q_INIT** | BOOL | Sets the initial value of **Q**, which is inherited during initialization. |

### **Data Outputs**

| Variable | Type | Comment |

|----------|-------|-----------|

| **QO** | BOOL | Output Qualifier: Indicates whether an operation was valid (inheritance of **QI**). |

| **Q** | BOOL | The actual flip-flop output. |

### **Adapters**

No adapters available.

## Functionality

The **E_RS_SYM_INIT** operates as a state machine with five states: **START**, **Init**, **DeInit**, **SET**, and **RESET**.

* **Start Behavior**: After an initial **INIT** event with **QI=TRUE**, the block transitions to the **Init** state. Depending on the value of **Q_INIT**, it transitions either to **SET** (**Q** = TRUE) or to **RESET** (**Q** = FALSE). The output qualifier **QO** takes the value of **QI** (i.e., TRUE) and is output via **INITO**.
* **Setting and Resetting**:
* In the **SET** state, an **R** event leads to the **RESET** state; the action sets **Q** to FALSE (if **QI=TRUE**).
* In the **RESET** state, an **S** event leads to the **SET** state; The action sets **Q** to TRUE (if **QI=TRUE**).
* On every state change, **QO** is set to the current value of **QI**, and the **EO** event is output.
* **Deinitialization**: As soon as an **INIT** event occurs while **QI=FALSE** (e.g., deinitialization), the block transitions from **SET** or **RESET** to the **DeInit** state. There, **QO** is set to FALSE, and the block returns to the **START** state via **INITO**. The flip-flop is not reset – **Q** retains its previous value.
* **Qualifier QI**: The actual change to **Q** only occurs if **QI=TRUE**. If **QI=FALSE**, the set and reset signals are ignored, but **QO** still passes the value of **QI**. This enables conditional behavior, e.g.,... B. for valid/invalid releases.

## Technical Features
* **Symmetrical Start Behavior**: The initial state of **Q** is explicitly defined via the parameter **Q_INIT**. This distinguishes the function block from a standard RS flip-flop, whose start state is undefined.
* **INIT as an Event with Parameters**: The INIT event input carries the values **QI** and **Q_INIT** simultaneously, clearly separating initialization and deinitialization.
* **QC (Event Qualifier) Passed Through**: For every valid operation (Set, Reset, or INIT), **QO** is set to the value of **QI**, allowing the calling application to verify the operation's validity.
* **Five-State Machine**: The separation of start, initialization, and deinitialization states enables robust behavior, particularly in automation systems with cyclic restarts.

## State Overview

| State | Description | Action on Entry | Exit Event |

|-----------|-----------------------------------------------------------------------------|----------------------|------------------|

| **START** | Initial sleep state after system startup or deinitialization | none | – |

| **INIT** | Initialization requested (**INIT** with **QI=TRUE**) | sets **QO** = **QI** | INITO |

| **DeInit** | Deinitialization requested (**INIT** with **QI=FALSE**) | sets **QO** = FALSE | INITO |

| **SET** | Flip-flop is set (**Q = TRUE**) | Set **Q** to TRUE (only if **QI=TRUE**) | EO |

| **RESET** | Flip-flop is reset (**Q = FALSE**) | Set **Q** to FALSE (only if **QI=TRUE**) | EO |

**Transitions:**

* START → Init: INIT ∧ (QI = TRUE)
* Init → SET: Q_INIT = TRUE
* Init → RESET: Q_INIT = FALSE
* SET → RESET: R
* RESET → SET: S
* SET → DeInit: INIT ∧ (QI = FALSE)
* RESET → DeInit: INIT ∧ (QI = FALSE)
* DeInit → START: 1 (always)

## Application Scenarios
* **Controllers with Defined Power-On Behavior**: If a specific start value is required for a flag or output after a restart of the automation system (e.g., TRUE for "system running" or FALSE for "shut down"), **Q_INIT** can be set accordingly.
* SET → DeInit: INIT ∧ (QI = FALSE)
* SET → START: 1 (always)

** Application Scenarios**

** Controllers with Defined Power-On Behavior**: If a specific start value is required for a flag or output after a restart of the automation system (e.g., TRUE for "system running" or FALSE for "shut down"), **Q_INIT** can be set accordingly.

** * **Safe Resets in Case of Faults**: By deinitializing (INIT with QI=FALSE), the function block can be reset to a defined "initial state" without clearing the current value of **Q**. This is useful, for example, to implement a "restart after a fault."

* **Qualified Set and Reset Operations**: A higher-level condition (e.g., "Enable active operation") can be controlled via **QI**. Only when **QI** = TRUE do setting and resetting actually affect **Q**.
* **Initialization of State Machines**: This function block is ideally suited as a basic building block for custom state machines that are intended to assume a specific initial state upon INIT.

## Comparison with Similar Function Blocks

| Function Block | Difference to E_RS_SYM_INIT |

|----------|-------------------------------|

| **E_RS** (Standard RS Flip-Flop) | No explicit start behavior; **Q** is not defined during INIT. **Q_INIT** is missing. |

**E_SR** (Set-Dominant Flip-Flop) | Set dominates over Reset; no initializable start state. |

**E_RS_SYM** | Symmetric RS logic without an INIT function; no start behavior. |

**E_RS_SYM**| **E_RS_SYM_INIT** (this one) | Combines symmetrical RS logic with selectable initial value and deinitialization. |

## Conclusion

**E_RS_SYM_INIT** is a powerful and flexible IEC 61499-1 function block for event-driven bistable toggle switches. Due to its explicit initialization with **Q_INIT** and the option for deinitialization while retaining the output value, it is particularly suitable for safety-related and automation applications where defined startup behavior and a clear separation of initialization and operation are required. The inclusion of a **QI** qualifier also enables efficient integration into complex sequence control systems.
