# FB_CTD_UDINT

<img width="1411" height="282" alt="FB_CTD_UDINT" src="https://github.com/user-attachments/assets/a8aab825-6766-4328-b0cb-4b841157bc33" />
* * * * * * * * * *
## Introduction

The function block `FB_CTD_UDINT` is a down counter for unsigned 32-bit integers (UDINT). It is used to decrement a counter value on each event until it reaches zero.
![FB_CTD_UDINT](FB_CTD_UDINT.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Normal execution request. Used to trigger the counting process or the loading of a new value.

### **Event Outputs**

- **CNF**: Execution confirmation. Triggered after the request has been processed and returns the current counter value and the output state.

### **Data Inputs**

- **CD** (BOOL): Counts down when `TRUE` is active and the counter value is greater than zero.
- **LD** (BOOL): Loads the specified value (`PV`) into the counter when `TRUE` is active.
- **PV** (UDINT): Specified value loaded into the counter when `LD` is active.

### **Data Outputs**

- **Q** (BOOL): Outputs `TRUE` when the counter value is less than or equal to zero.
- **CV** (UDINT): Current counter value.

### **Adapters**

No adapters available.

## Functionality

The function block processes the input events and data as follows:

1. If `LD` is enabled (`TRUE`), the specified value (`PV`) is loaded into the counter (`CV`).
2. If `CD` is enabled (`TRUE`) and the counter value (`CV`) is greater than zero, the counter value is decremented by one.
3. The output `Q` is set to `TRUE` if the counter value (`CV`) is less than or equal to zero.
4. After processing, the output event `CNF` is triggered to confirm the new state.

## Technical Features

- The counter uses unsigned 32-bit integers (UDINT).
- The counter value is only decremented if `CD` is enabled and the current value is greater than zero.
- The output `Q` signals when the counter value reaches zero or below.

## State Overview

- **Initialization**: The counter value (`CV`) is undefined until a `LD` signal is received.
- **Loading**: When `LD` is enabled, `PV` is loaded into `CV`.
- **Countdown**: When `CD` and `CV > 0` are enabled, `CV` is decremented by one.
- **Initial State**: `Q` becomes `TRUE` when `CV <= 0` is enabled.

## Application Scenarios

- Controlling processes that require a specific number of steps or events.
- Time-controlled processes that require a countdown.
- Monitoring cycles or repetitions in automated systems.

## ⚖️ Comparison with Similar Components

- Unlike an up counter (CTU), this component decrements the counter value.
- Similar to other counter components, but specialized for unsigned 32-bit integers.

## Conclusion

The `FB_CTD_UDINT` is an efficient and simple down counter for applications requiring a counting function with unsigned 32-bit integers. Its clear interface and simple operation make it a useful component in automation technology.
