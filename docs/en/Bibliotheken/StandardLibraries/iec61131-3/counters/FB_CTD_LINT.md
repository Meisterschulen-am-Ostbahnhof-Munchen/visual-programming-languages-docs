# FB_CTD_LINT

<img width="1399" height="282" alt="FB_CTD_LINT" src="https://github.com/user-attachments/assets/49df9c31-e52a-4ab3-9ab5-c17c58f2ee98" />

* * * * * * * * * *
## Introduction
The function block `FB_CTD_LINT` is a countdown counter for 64-bit integers (LINT). It allows counting down an internal counter value and provides functions for loading a predefined value. The block is particularly suitable for applications that need to work with large ranges of numbers.

![FB_CTD_LINT](FB_CTD_LINT.svg)

## Interface Structure

### **Event Inputs**

- `REQ`: Starts the normal execution of the counting process. Linked to the data `CD`, `PV`, and `LD`.


### **Event Outputs**

- `CNF`: Confirms execution and returns the current values of `Q` and `CV`.

### **Data Inputs**

- `CD` (BOOL): Signals whether the counter should be decremented.

- `LD` (BOOL): Loads the predefined value (`PV`) into the counter.

- `PV` (LINT): The predefined value that is loaded when `LD` is active.


### **Data Outputs**

- `Q` (BOOL): Signals whether the counter value (`CV`) is less than or equal to zero.

- `CV` (LINT): The current counter value.

### **Adapters**
No adapters available.

## Functionality
The function block operates according to the following logic:

1. When `LD` is active, the predefined value (`PV`) is loaded into the counter (`CV`).

2. If `CD` is active and the counter value (`CV`) has not reached the minimum 64-bit value, `CV` is decremented by 1.

3. The output `Q` is set to `TRUE` if `CV` is less than or equal to zero.

## Technical Features
- Uses the data type `LINT` (64-bit integer), which allows for a very large number range.

- The minimum value for `LINT` is taken into account to prevent overflows.


## Status Overview

- **Initialization**: No specific initialization; `CV` starts with an undefined value.

- **Loading**: When `LD` is active, `CV` is overwritten with `PV`.

- **Counting**: When `CD` is active, `CV` is decremented unless the minimum value has been reached.

- **Output**: `Q` is set based on the current value of `CV`.

## Application Scenarios

- Controlling processes with large counting ranges, e.g., in production automation.


- Monitoring of time intervals or event counts in industrial control systems.

## ⚖️ Comparison with similar components

- Similar to `FB_CTD_INT`, but with an extended number range (`LINT` instead of `INT`).

- Offers greater flexibility compared to simpler counters due to its large value range and loading function.

## Conclusion
The `FB_CTD_LINT` is a powerful down counter for applications requiring large number ranges. Its ease of use and robust implementation make it a reliable choice for complex control tasks.