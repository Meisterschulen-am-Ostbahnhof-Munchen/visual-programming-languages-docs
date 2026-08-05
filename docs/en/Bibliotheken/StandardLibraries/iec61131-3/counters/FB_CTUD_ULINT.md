# FB_CTUD_ULINT

<img width="1423" height="340" alt="FB_CTUD_ULINT" src="https://github.com/user-attachments/assets/dbd0e935-fff7-4ac2-b484-178aa62809f7" />

* * * * * * * * * *
## Introduction
The function block `FB_CTUD_ULINT` is a counter with up and down counting functionality for the data type `ULINT` (unsigned 64-bit integer). It offers additional functions such as reset, loading a default value, and status outputs for the counting direction.

![FB_CTUD_ULINT](FB_CTUD_ULINT.svg)

## Interface Structure

### **Event Inputs**

- `REQ`: Starts the normal execution of the counting process. Linked to the data inputs `CU`, `CD`, `R`, `LD`, and `PV`.

### **Event Outputs**

- `CNF`: Confirms execution and provides the current counter values via the data outputs `QU`, `QD`, and `CV`.


### **Data Inputs**

- `CU` (BOOL): Count Up Signal
- `CD` (BOOL): Count Down Signal
- `R` (BOOL): Reset Signal (sets the counter to 0)
- `LD` (BOOL): Load Signal (loads the preset value `PV` into the counter)
- `PV` (ULINT): Preset Value (default value for the counter)

### **Data Outputs**

- `QU` (BOOL): Signals whether the counter value is greater than or equal to the preset value

- `QD` (BOOL): Signals whether the counter value is less than or equal to 0

- `CV` (ULINT): Current counter value

## Functionality
The counter performs the following operations on the `REQ` event:

1. When `R` (Reset) is active, the counter is reset to 0.

2. When `LD` (Load) is active, the default value `PV` is loaded into the counter.

3. If neither Reset nor Load is active:

- When `CU` is active (and not simultaneously `CD`), the counter is incremented (up to the maximum value). 18446744073709551615)

- When `CD` is active (and not simultaneously `CU`), the counter counts down (to the minimum value of 0).

4. The outputs `QU` and `QD` are updated according to the current counter value.

## Technical Features
- Uses the 64-bit unsigned integer data type (ULINT)

- Maximum counter value: 18446744073709551615
- Special handling for the simultaneous activation of `CU` and `CD` (no counting operation)

- Status outputs for exceeding/falling below the limit

## Application Scenarios

- Industrial counting tasks with large Number ranges
- Position detection in large systems
- Material flow monitoring with high production volumes
- General control tasks with up/down counting function

## ⚖️ Comparison with similar function blocks

- Compared to simple counters, this function block offers both counting directions

- Compared to smaller data types (e.g., INT), ULINT enables extremely large counting ranges

- Integrated status outputs (`QU`, `QD`) simplify monitoring

## Conclusion
The `FB_CTUD_ULINT` is a powerful counter function block for applications requiring large number ranges and flexible counting functions. Its combined up/down counting function and additional control and status options make it suitable for complex counting tasks in industrial control systems.