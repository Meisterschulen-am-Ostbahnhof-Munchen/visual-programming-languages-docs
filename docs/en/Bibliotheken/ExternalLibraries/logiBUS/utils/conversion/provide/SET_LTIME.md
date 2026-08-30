# SET_LTIME

![SET_LTIME](./SET_LTIME.svg)

* * * * * * * * * *

## Introduction

The function block **SET_LTIME** is used to write an input value of type `LTIME` to a variable declared as InOut. This allows you to directly set the value of an external reference (e.g., an instance variable or another function block). Using an InOut variable allows for efficient data transfer without requiring a separate data output.

## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|------------|
| REQ | Event | Normal execution trigger. Associated with the data `IN` and `OUT`. |

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| CNF | Event | Confirmation of successful execution. Associated with data `OUT`. |

### **Data Inputs**

| Name | Type | Initial Value | Comment |
|------|-----|-------------|-----------|
| IN | LTIME | LT#0s | Value to be written to the target variable. |

### **Data Outputs**

| Name | Type | Initial Value | Comment |
|------|-----|--------------|-----------|
| OUT | LTIME | LT#0s | **InOut Variable** – Target variable that receives the passed value. The function block writes the value of `IN` to this variable. As an InOut variable, it can be both read from and written to externally. |

### **Adapter**

None.

## Functionality

When an event occurs at the **REQ** input, the algorithm `REQ` is executed:

- The value of the data input `IN` is copied directly into the InOut variable `OUT`.
- The **CNF** event is then output to signal the successful assignment.

The logic is very simple and consists of a single assignment:

OUT := IN;

## Technical Features

- The function block (FB) works exclusively with the **LTIME** data type (high-resolution time, according to IEC 61499).
- The target variable `OUT` is declared as **InOut**. This means that it is passed externally as a reference. Changes made by the FB to `OUT` immediately affect the referenced variable.
- Initially, both `IN` and `OUT` are set to `LT#0s` to prevent undefined states.
- The function block is a **simple FB** with only one state, which reacts immediately to a REQ event.

## State Overview

The FB has exactly one state:

| State | Action | Output |
| State | Action | Output | |---------|--------|---------|
| REQ | `REQ` (OUT := IN) | CNF |

There are no branches or timers. The function block is essentially combinatorial, as it reacts immediately to the input event.

## Application Scenarios

- **Setting a Central Time Base**: If multiple function blocks access a common LTIME variable, `SET_LTIME` can update this variable.
- **Runtime Configuration**: In a control application, target time values from a configuration interface can be written to the corresponding InOut parameters.
- **Testing and Simulation**: This function block is suitable for selectively writing values to an observable variable in test environments.

## Comparison with Similar Function Blocks

- **SET_TIME**: Works analogously, but with the data type `TIME` (second resolution). `SET_LTIME` offers higher time resolution (nanoseconds) and is therefore suitable for precise applications.
- **MOVE Function Blocks**: Many IEC 61499 libraries contain generic MOVE function blocks that copy values from an input to an output. `SET_LTIME` specializes in `LTIME` and uses an InOut reference instead of a separate output, which can be advantageous in certain architectures.

## Conclusion

SET_LTIME` is a minimalist yet useful function block for precisely setting an LTIME variable. Its clear interface and the use of an InOut reference make it an efficient tool in timing and configuration scenarios. The component is easy to understand and straightforward to use.
