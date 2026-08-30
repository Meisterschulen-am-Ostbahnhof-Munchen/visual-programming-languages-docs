# OFFSET

<img width="1417" height="209" alt="image" src="https://github.com/user-attachments/assets/95399eba-9583-4cfe-af8d-3c4314a23cc2" />
* * * * * * * * * *
## Introduction

The OFFSET function block is used to determine and apply an offset value. When an event with a non-zero input value is first processed, this value is stored as a reference point (`FIRST`). On each subsequent call, the block calculates the difference between the current input value and this stored reference value. This block is useful for measuring relative changes compared to an initial starting value.
![OFFSET](OFFSET.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the normal execution of the block. Linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the calculation. Linked to the data outputs `OUT` and `FIRST`.

### **Data Inputs**

- **IN** (DINT): The input value. On the first call where this value is greater than 0, it is stored as the reference value (`FIRST`). Initial value is 0.

### **Data Outputs**

- **OUT** (DINT): The result of the calculation `IN - FIRST`. Initial value is 0.
- **FIRST** (DINT): The reference value stored on the first relevant call. Initial value is 0.

### **Adapters**

This function block does not use any adapters.

## Functionality

The OFFSET block is a simple function block with a single state (`REQ`) and an algorithm of the same name.

Upon each occurrence of a `REQ` event, the algorithm `REQ` is executed:

1. **Checking and Setting the Reference Value:** The algorithm checks whether the output `FIRST` still has its initial value of 0. If so, **and** the current input value `IN` is greater than 0, `FIRST` is set to the value of `IN`. This condition (`IN > 0`) is implicitly included in the algorithm's logic, since `FIRST` is only changed from 0 to another value during the first processing of a `IN > 0` event.
2. **Offset Calculation:** Regardless of the previous step, the output `OUT` is calculated as the difference between the current input `IN` and the stored reference value `FIRST` (`OUT := IN - FIRST`).
3. **Confirmation:** After the calculation, the `CNF` event is triggered, including the current values of `OUT` and `FIRST`.

## Technical Features

- The reference value `FIRST` is set exactly once, specifically during the first `REQ` event where the data input `IN` has a value greater than 0. As long as `IN` is 0 or less during the initial calls, `FIRST` remains 0.
- Once `FIRST` has been set, it remains unchanged for the entire duration of the function block's runtime.
- The calculation `OUT = IN - FIRST` occurs with *every* call, even if `FIRST` is still 0. This means that `OUT` remains identical to `IN` until the reference value is set.

## State Overview

The function block has a single, eponymous state:

- **REQ:** This state is always active. Every incoming `REQ` event triggers the execution of the associated algorithm and immediately triggers the `CNF` event. There are no internal state transitions.

## Application Scenarios

- **Incremental Path or Position Measurement:** Setting a zero point (`FIRST`) after a reference run and subsequent measurement of the relative movement (`OUT`).
- **Compensation for Base Loads or Zero Deviations:** Capture an initial base value (e.g., sensor base load) and calculate the pure change relative to this base value.
- **Relative Time Measurement:** Store a start time and calculate the elapsed time since that start.

## ⚖️ Comparison with Similar Function Blocks

- **SUB / DINT_SUB:** A simple subtractor always calculates the difference between two current input values. OFFSET, on the other hand, stores one of the values internally as a constant reference point.
- **DELAY / TON:** Time delay functions operate on the time axis. OFFSET works with data values and has no time-based behavior.
- **SR / RS:** Memory functions (Set/Reset) hold a binary state. OFFSET stores an integer value (`DINT`) and uses it for an arithmetic operation.

## Conclusion

The OFFSET function block is a specialized and simple function block for determining a relative offset. Its strength lies in the one-time, automatic acquisition of a starting or reference value and the continuous calculation of the deviation from it. It is particularly suitable for applications where a system must be initially "zeroed" and only subsequent changes are relevant.
