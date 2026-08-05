# SET_USINT

![SET_USINT](./SET_USINT.svg)

* * * * * * * * * *

## Introduction

The function block **SET_USINT** is used to write a value of type **USINT**, provided via the data input **IN**, directly into the variable **OUT**, which is declared as InOut. The block performs a simple assignment and confirms execution with the **CNF** event.

## Interface Structure

### **Event Inputs**

| Event | Description |

|----------|--------------|

| **REQ** | Normal execution request – takes the value from **IN** to **OUT** and sends **CNF**. |

### **Event Outputs**

| Event | Description |

|----------|--------------|

| **CNF** | Confirmation of successful execution (sent after assignment). |

### **Data Inputs**

| Name | Data Type | Initial Value | Description |

|------|----------|-------------|-------------|

| **IN** | USINT | 0 | Value to be written to the target variable. |

### **Data Outputs**

| Name | Data Type | Initial Value | Description |

|------|----------|-------------|--------------|

| **OUT** | USINT (InOut) | 0 | Target variable (declared as InOut, meaning it can be both read and written). After execution, **OUT** contains the value of **IN**. |

### **Adapter**

None.

## Functionality

When the **REQ** event is received, the function block executes the **REQ** algorithm. This assigns the current value of the **IN** input to the **OUT** variable (`OUT := IN;`). The **CNF** event is then sent to signal the completion of the operation. The function block operates without delay or further conditions.

## Technical Features

- The use of an **InOut** variable allows **OUT** to be used as both a target (output) and a source (input) in other function blocks.

- The function block is fixed to the **USINT** data type (8-bit unsigned integer) – direct conversion is not supported.

- Only one state exists; the function block is **event-driven** and performs exactly one assignment per **REQ**.

## State Overview

| State | Action | Output Event |

|---------|--------|------------------|

| **REQ** | Execute the **REQ** (`OUT := IN;`) algorithm | **CNF** |

The FB has no explicit start state – it waits for an event in the **REQ** state.

## Application Scenarios

- **Initializing** variables or peripherals that require a specific USINT value.

- **Parameterizing** devices or function blocks via an InOut variable.

- **Simply setting a value** in control logic when no calculation or condition is required.

## Comparison with Similar Function Blocks

- **MOVE (ANY)**: A more general function block for copying arbitrary data types, often without InOut capability.


- **SET_INT**, **SET_BYTE**, etc.: Analogous function blocks for other integer types – SET_USINT is specialized for USINT.

- Unlike **LATCH** or **SR flip-flops**, SET_USINT does not store state but performs a one-time assignment.

## Conclusion

**SET_USINT** is a minimalist and reliable function block for directly assigning a value to an InOut variable of type USINT. Its simple structure is particularly suitable for clear, sequential control tasks where a value must be set without side effects.