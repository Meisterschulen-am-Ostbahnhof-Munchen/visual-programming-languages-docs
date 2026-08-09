# E_MOVE

<!-- Hier wäre Platz für ein Bild des Funktionsblocks, falls vorhanden. -->
* * * * * * * * * *
## Introduction

The `E_MOVE` block (Event-driven Move) is a data latch that filters the transmission of data and events. It outputs a data event only if the input data value differs from the last output value. It functions like a D flip-flop for arbitrary data types (`ANY`).
![E_MOVE](E_MOVE.svg)

## Interface Structure

### **Event Inputs:**

- **REQ (Request)**: Triggers the validation and potential transmission of the input value.
- **Related Data**: `IN`

### **Event Outputs:**

- **CNF (Confirmation)**: Triggered when the input value `IN` differs from the last output value `OUT`.
- **Related Data**: `OUT`

### **Data Inputs:**

- **IN**: The input value to be compared with the output value (Data type: `ANY`).

### **Data Outputs:**

- **OUT**: The last changed value corresponding to the input value (Data type: `ANY`).

## Functionality

1. **Event Receipt**: The function block waits for an event at input `REQ`.
2. **Value Comparison**: When the `REQ` event arrives, the current value at input `IN` is compared with the internally stored value (which is also present at output `OUT`).
3. **Conditional Forwarding**:
- **If `IN` is not equal to `OUT`**: The new value of `IN` is output at `OUT`, and the `CNF` event is triggered.
- **If `IN` equals `OUT`**: Nothing happens. The `CNF` event is not triggered, and the data flow is interrupted.

This mechanism reduces the number of events in the system by reacting only to actual data changes.

## Technical Features

- **Data Change Filter**: The core function is to filter redundant data and suppress unnecessary events.
- **Generic Data Type**: The function block can be used with any data type (`ANY`) except `REAL` and `LREAL`.
- **Warning for `REAL`/`LREAL`**: Functionality is not guaranteed for the data types `REAL` and `LREAL`. Due to rounding errors and the nature of floating-point comparisons, unpredictable behavior can occur, where small, irrelevant changes are incorrectly interpreted as data modifications.

## Application Scenarios

- **Reducing System Load**: In complex networks, the number of processed events can be drastically reduced by reacting only to value changes.
- **Edge Detection for Non-Boolean Values**: Detect when an analog value or status changes.
- **Interface to Slow Systems**: Ensure that a command is sent to a subordinate system only when the target value actually changes.

## ⚖️ Comparison with Similar Building Blocks

- **`E_D_FF`**: Functionally very similar, but `E_D_FF` is specifically designed for the data type `BOOL`. `E_MOVE` is the generic `ANY` variant.
- **Direct Connection**: Unlike a direct connection of data and events that are forwarded on every execution, `E_MOVE` inserts a "change firewall."

## 🛠️ Related Exercises

* [Exercise_171](../../../Uebungen/test_B/Uebungen_doc/Uebung_171.md)

## Conclusion

The `E_MOVE` block is an extremely useful tool for optimizing IEC 61499 applications. By limiting event processing to actual data changes, it significantly contributes to reducing system load and increasing efficiency. Its generic nature makes it very flexible; however, the limitation with floating-point numbers must be taken into account.
