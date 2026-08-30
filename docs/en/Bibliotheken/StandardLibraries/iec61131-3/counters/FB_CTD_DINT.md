# FB_CTD_DINT

<img width="1399" height="282" alt="FB_CTD_DINT" src="https://github.com/user-attachments/assets/a2d2a64a-c6b7-4d0e-9d5d-c1ab0452c96f" />
* * * * * * * * * *
## Introduction

The function block `FB_CTD_DINT` is a down counter for 32-bit integers (DINT). It is used to decrease a value incrementally and output a signal when a specific threshold is reached.
![FB_CTD_DINT](FB_CTD_DINT.svg)

## Interface Structure

### **Event Inputs**

- `REQ`: Normal execution request (trigger for the counting process)

### **Event Outputs**

- `CNF`: Execution confirmation (triggered after completion of the counting process)

### **Data Inputs**

- `CD` (BOOL): Count Down command
- `LD` (BOOL): Load command
- `PV` (DINT): Preset Value

### **Data Outputs**

- `Q` (BOOL): Output signal (is TRUE if CV ≤ 0)
- `CV` (DINT): Current Count Value

## Functionality

1. When the `REQ` event is triggered, the following algorithm is executed:

- If `LD` is TRUE, the counter is set to the value of `PV`
- If `CD` is TRUE and the current value (`CV`) is greater than -2147483648, `CV` is decremented by 1
1. The output signal `Q` is set to TRUE if `CV` is less than or equal to 0 is
2. Upon completion, the `CNF` event is triggered

## Technical Features

- Uses 32-bit integers (DINT) with a value range of -2147483648 to 2147483647
- The counter stops when the minimum DINT value (-2147483648) is reached
- The block is included in the IEC 61131-3 standard library under `iec61131::counters`

## State Overview

The function block has no explicit states but operates event-driven:

1. Waits for the `REQ` event
2. Performs the counting operation
3. Sends the `CNF` event

## Application Scenarios

- Down counting in production processes
- Time controls with countdown function
- Monitoring of remaining quantities or steps

## ⚖️ Comparison with similar blocks

- Unlike up counters (CTU), this block decrements the counter value
- Compared to 16-bit counters (INT), this block offers a larger value range
- Similar to timers, but for general counting purposes without a time reference

## Conclusion

The `FB_CTD_DINT` is a robust and easy-to-use down counter for 32-bit values. Its clear interface and deterministic operation make it ideal for control tasks where reliable down counting is required.
