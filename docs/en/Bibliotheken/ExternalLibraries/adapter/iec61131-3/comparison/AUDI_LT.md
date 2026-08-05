# AUDI_LT

![AUDI_LT](./AUDI_LT.svg)

* * * * * * * * * *
## Introduction
The function block `AUDI_LT` performs a "less than" comparison between two input values. It is frequently used in automation technology to monitor thresholds or make logical decisions. The block is classified as a "standard comparison function" according to IEC 61131-3 and uses adapters for flexible connection of different data types.

## Interface Structure
### **Event Inputs**
Events are forwarded to the function block from external sources via the adapter sockets:

* `IN1.E1` – Event that triggers the comparison operation as soon as a new value is present at `IN1`.

* `IN2.E1` – Event that also triggers the comparison operation as soon as a new value is present at `IN2`.

### **Event Outputs**

* `OUT.E1` – Event that is output after the comparison is complete and signals that the result at data output `OUT.D1` is valid.

### **Data Inputs**

* `IN1.D1` – First value to be compared (data of the adapter type `AUDI`).

* `IN2.D1` – Second value to be compared (data of the adapter type `AUDI`).


### **Data Outputs**

* `OUT.D1` – Comparison result: `TRUE` if `IN1 < IN2`, otherwise `FALSE` (data of the adapter type `AX`).

### **Adapters**

* `IN1` – Socket (input) of type `adapter::types::unidirectional::AUDI`. Sends an event (`E1`) and a data value (`D1`) to the FB.

* `IN2` – Socket (input) of the same type as `AUDI`. Provides the second input value.

* `OUT` – Plug (output) of type `adapter::types::unidirectional::AX`. Receives the result event (`E1`) and the result data value (`D1`) for passing to subsequent function blocks.

## Functionality
This function block performs a numerical comparison of the two data points at `IN1` and `IN2`. As soon as one of the two events (`IN1.E1` or `IN2.E1`) occurs, the internal function block `F_LT` (Less Than) is called. This function reads the current values of `IN1` and `IN2` and calculates their relative size. The result (`TRUE` / `FALSE`) is provided at the data output `OUT.D1`, and the event `OUT.E1` is triggered simultaneously. Since both event inputs are connected to the same `REQ` input of the internal function block, the comparison is performed again whenever either value changes.

## Technical Features
- **Adapter-Based Interfaces** – The use of the adapters `AUDI` and `AX` enables universal coupling to various data types without requiring the function block itself to be typed. The actual type adaptation takes place in the adapter definitions.

- **Asynchronous Triggering** – The comparison is always started when an event arrives at `IN1` or `IN2`. This allows the function block to react immediately to changes in either of the two inputs.

- **Stateless** – The function block has no internal state; the output signal depends solely on the current input values.

## State Overview
The function block is purely functional and does not require its own state machine. It performs a one-time comparison operation after each event and then returns to an empty wait state.

## Application Scenarios

- **Limit Monitoring** – e.g., checking whether a temperature falls below a threshold.

- **Range Check** – Combination with other comparison blocks (e.g., `AUDI_GT`) to implement "inside" or "outside" logic.

- **Control Logic** – Boolean decisions depending on two analog or digital variables.

## Comparison with Similar Blocks

- **`AUDI_EQ`** – Checks for equality (`IN1 = IN2`).

- **`AUDI_GT`** – Checks for greater than (`IN1 > IN2`).

- **`AUDI_LT`** – Checks for less than (`IN1 < IN2`). All three blocks have identical interfaces and differ only in their comparison operation. They can be easily interchanged to adapt the logic.


## Conclusion

The `AUDI_LT` is a simple yet robust comparison module that can be flexibly integrated into a wide variety of automation environments thanks to its adapter interfaces. Its asynchronous operation and the clear separation of events and data make it a fundamental tool for value comparison tasks in control engineering.