# FB_CTU_ULINT
<img width="1408" height="271" alt="FB_CTU_ULINT" src="https://github.com/user-attachments/assets/fb1bdbf1-e57f-4efd-8953-c3e697ae3f39" />
* * * * * * * * * *
## Introduction
The function block `FB_CTU_ULINT` is an up counter for the data type `ULINT` (Unsigned Long Integer). It increments with each counting event and can be reset to a predefined value. This block is particularly suitable for applications requiring large counting ranges.
![FB_CTU_ULINT](FB_CTU_ULINT.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Normal execution request. Used to trigger the counting process. Linked to the data `CU` and `R`.

### **Event Outputs**
- **CNF**: Execution Confirmation. Triggered after processing the counting operation. Linked to the data `Q` and `CV`.

### **Data Inputs**
- **CU** (BOOL): Count Request. Increments the counter when `TRUE` is active, unless `R` is active.
- **R** (BOOL): Reset. Resets the counter value (`CV`) to `0` when `TRUE` is active.
- **PV** (ULINT): Preset Value. Defines the threshold at which the output `Q` is activated.

### **Data Outputs**
- **Q** (BOOL): Output. Outputs `TRUE` when the counter value (`CV`) reaches or exceeds the preset value (`PV`).
- **CV** (ULINT): Current Counter Value. Returns the current counter value.

## Functionality
This function block increments the counter value (`CV`) by 1 when the input `CU` is activated (`TRUE`) and the counter value has not reached the maximum value (`18446744073709551615`). When the input `R` is enabled (`TRUE`), the counter value is reset to `0`. The output `Q` is set to `TRUE` as soon as the counter value (`CV`) reaches or exceeds the preset value (`PV`).

## Technical Features
- The counter value (`CV`) is of type `ULINT`, which allows for a very large counting range (0 to 18446744073709551615).
- The block is deterministic and suitable for real-time applications.

## Status Overview
- **Reset State**: `CV = 0` (if `R = TRUE`).
- **Count State**: `CV` is incremented by 1 (if `CU = TRUE` and `R = FALSE`).
- **Threshold Reached**: `Q = TRUE` (if `CV >= PV`).

## Application Scenarios
- Counting production units in high-speed systems.
- Monitoring events in long-running systems.
- Controlling processes with large counting ranges.

## ⚖️ Comparison with Similar Function Blocks
- Compared to `FB_CTU_INT` or `FB_CTU_DINT`, `FB_CTU_ULINT` offers a significantly larger counting range.
- Similar to `FB_CTU`, but specialized for the `ULINT` data type.

## Conclusion
The `FB_CTU_ULINT` is a powerful increment counter for applications requiring large counting ranges. Its ease of use and deterministic operation make it a reliable choice for industrial control applications.