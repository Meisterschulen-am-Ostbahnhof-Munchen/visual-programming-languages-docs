# AX_NOT_INIT
![AX_NOT_INIT](./AX_NOT_INIT.svg)

* * * * * * * * * *
## Introduction
The function block **AX_NOT_INIT** implements a Boolean negation (NOT function) based on an adapter type. Unlike classic NOT blocks, it operates via a standardized adapter interface and is specifically designed for use in modular automation systems. Initialization occurs via the INIT event input, which triggers the first calculation.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |

|-------|-------|-------------------------|

| INIT | EInit | Initialization Request |

### **Event Outputs**

| Name | Type | Comment |

|-------|-------|---------------------------|

| INITO | EInit | Initialization Confirmation |

### **Data Inputs**

This function block has no direct data inputs. Input data is obtained via the **IN** adapter.

### **Data Outputs**

This function block has no direct data outputs. Output data is provided via the **OUT** adapter.

### **Adapters**

| Name | Type | Comment | Direction |

|------|--------------------------------------------------|----------------------|----------|

| IN | adapter::types::unidirectional::AX | Input Value | Socket |

| OUT | adapter::types::unidirectional::AX | Output Value (Negated) | Plug |

## Functionality

The function block performs a bitwise negation of the value provided via the **IN** adapter and outputs the result via the **OUT** adapter. Processing is initiated by an event at **IN.E1** (an event from the IN adapter) or by the INIT event. Internal steps:

1. An event at **INIT** or **IN.E1** activates the embedded function block **F_NOT_BOOL**.

2. **F_NOT_BOOL** retrieves the value from **IN.D1**, inverts it, and writes the result to **OUT.D1**.

3. Upon completion, an event is output via **OUT.E1** (to the OUT adapter) as well as **INITO**.

If the INIT event is received, **INITO** and **OUT.E1** are triggered immediately – the first negation occurs without a prior input event.

## Technical Features
- **Adapter-Based Communication**: The function block uses exclusively unidirectional adapters of type `AX`, which modularly encapsulates the data and event interfaces. This facilitates communication between components using standardized protocols.
- **Initialization Behavior**: The INIT input performs an immediate initial calculation and outputs an acknowledgment event, which is useful for initial value settings or reset processes.
- **Reuse**: Internally, the IEC 61131-3 function block `F_NOT_BOOL` is used, which implements simple negation on Boolean values.

## State Overview

The function block does not have an explicit state machine – it reacts event-driven. Simplified process:

Ereignis (INIT oder IN.E1)
→ Erfasse IN.D1
→ Berechne NOT
→ Setze OUT.D1
→ Sende INITO und/oder OUT.E1
The function block is **stateless**, meaning that each new request is processed independently of previous values.

## Application Scenarios
- **Signal Negation in Modular Systems**: If inputs and outputs are defined via adapters, the function block can be used as a universal NOT gate, e.g., for inverting actuator or sensor values.
- **Initialization Logic**: The INIT input ensures that the output provides a defined negated value at startup.
- **Adapter Compatibility**: In systems using the `AX` adapter protocol, the function block serves as a basic functional building block for logic operations.

## Comparison with Similar Function Blocks
- **F_NOT_BOOL**: Standard IEC 61131-3 NOT function without an adapter. **AX_NOT_INIT** encapsulates this functionality in an adapter interface and adds initialization behavior.
- **AX_AND / AX_OR**: Analog adapter blocks for AND and OR, respectively. **AX_NOT_INIT** is specific for negation and has only one input.
- **F_TRIG / R_TRIG**: Edge detection that also uses events but does not perform logical negation.

## Conclusion

The **AX_NOT_INIT** function block offers an efficient and standardized way to negate Boolean values via the `AX` adapter. By integrating initialization logic, it is particularly suitable for systems that require a defined initial state at startup. It complements the family of adapter-based logic blocks and simplifies the modular structuring of automation solutions.
