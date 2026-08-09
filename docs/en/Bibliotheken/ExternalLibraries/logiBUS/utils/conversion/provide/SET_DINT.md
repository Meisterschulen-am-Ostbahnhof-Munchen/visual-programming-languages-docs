# SET_DINT

![SET_DINT](./SET_DINT.svg)

* * * * * * * * * *
## Introduction

The function block `SET_DINT` is used to write a DINT value from a data input to an InOut variable. It thus implements a simple assignment operation for the data type `DINT`. The block is triggered by an event and acknowledges successful execution with a confirmation event.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment | With Variables |
|------|-------|-------------------------------|---------------|
| REQ | Event | Normal Execution Trigger | IN, OUT |

### **Event Outputs**

| Name | Type | Comment | With Variables |
|------|-------|------------------------------|---------------|
| CNF | Event | Execution Confirmation | OUT |

### **Data Inputs**

| Name | Type | Comment | Initial Value |
|------|------|----------------------|-------------|
| IN | DINT | Value to be written | 0 |

### **Data Outputs**

This function block does not have traditional data outputs, but rather an InOut parameter (see below). The acknowledgment event `CNF` is linked to the output `OUT`, so that after execution, the updated value is available at the output.

### **Adapter**

None.

## Functionality

When an event occurs at the input `REQ`, the algorithm `REQ` is executed. This copies the current value of the data input `IN` directly into the InOut variable `OUT`. The acknowledgment event `CNF` is then sent.

The logic in Structured Text is:

OUT := IN;
Execution is atomic: The value is applied immediately and without delay.

## Technical Features

- The function block uses an **InOut variable** (`OUT`). This variable is both an input and an output and can be read and written externally. This allows the function block to overwrite the value of an existing variable in place without using an additional output.
- The function block is stateless – there is only one execution state. Every call performs the same simple assignment.
- All variables are initially predefined with `0`.

## State Overview

| State | Action | Output Event |
|---------|--------------------|-----------------|
| REQ | OUT := IN | CNF |

The function block has no other states (no wait loops, no branches). After the action, it immediately returns to standby mode for the next `REQ`.

## Application Scenarios

- **Parameter Passing:** An external value (e.g., from a configuration interface) is written to a local variable in an application.
- **Signal Routing:** A digital integer value is redirected from one signal path to another, while preserving the original value.
- **Initialization:** At system startup, a defined start value can be written to a state variable via `SET_DINT`.
- **Testing and Debugging:** Manually setting a DINT value via an HMI or a script.

## Comparison with Similar Function Blocks

- **MOVE/DINT**: Standardized function blocks such as `MOVE` from IEC 61131-3 also perform assignments. `SET_DINT` is specialized for the type `DINT` and offers a reduced interface (only one input event, no additional outputs).
- **SET_BOOL, SET_REAL, SET_SINT**: Analogous function blocks for other data types exist in the `logiBUS` library. They differ only in data type; their functionality is identical.
- **Direct Assignment in the Network**: In IEC 61499, an assignment could also be implemented without a function block via a direct data connection. The function block `SET_DINT`, however, offers explicit, event-driven encapsulation that can be monitored and triggered at runtime.

## Conclusion

SET_DINT` is a simple yet useful function block for the targeted assignment of DINT values. By using an InOut variable, the interface remains streamlined, and the block can be directly integrated into existing data flows. Its clear, stateless logic makes it reliable and easy to understand – ideal for basic transfer operations in automation projects.
