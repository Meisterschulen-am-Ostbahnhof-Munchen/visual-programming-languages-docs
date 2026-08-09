# F_ADD_TOD_TIME

![F_ADD_TOD_TIME](https://github.com/user-attachments/assets/5fc8767d-17c3-4d6f-b876-569edafd7152)

* * * * * * * * * *
![F_ADD_TOD_TIME](F_ADD_TOD_TIME.svg)
## Introduction

The **F_ADD_TOD_TIME** function block is a specialized function module for adding time values to times of day, developed under the EPL 2.0 license. Version 1.0 enables precise time calculations using TIME_OF_DAY and TIME data types.

## Interface Structure

### **Event Inputs**

- `REQ`: Calculation request (with input values)

### **Event Outputs**

- `CNF`: Calculation confirmation (with result)

### **Data Inputs**

- `IN1` (TIME_OF_DAY): Output time (time of day)
- `IN2` (TIME): Duration for addition

### **Data Outputs**

- `OUT` (TIME_OF_DAY): Result of the addition

## Functionality

1. **Activation**:
- Triggered by the `REQ` event
- Processes TIME_OF_DAY and TIME values
2. **Calculation**:
- Adds time duration (IN2) to time of day (IN1)
- Automatically takes into account:
- Day transitions (24-hour format)
- Millisecond accuracy
3. **Result Output**:
- `CNF` event with new TIME_OF_DAY
- Format: TOD#23:59:59.999

## Technical Specifications

✔ **Precise Time of Day Calculation**
✔ **Automatic Day Transition**
✔ **IEC 61131-3 Compliant**
✔ **Millisecond Accurate Calculation**

## Application Examples

- **Shift Planning**: Working Time Calculations
- **Lighting Control**: Daylight Simulation
- **Production Processes**: Time-Controlled Sequences
- **Scheduling Systems**: Arrival Time Calculations

## Special Notes

- **Scope of Application**:
- 00:00:00.000 to 23:59:59.999
- If the limit is exceeded: Wrap-around (e.g., 25:00:00 → 01:00:00)
- **Error Cases**:
- In case of overflow: Cyclic incrementing
- In case of invalid input: OUT = IN1

## ⚖️ Comparison with similar function blocks

| Feature | F_ADD_TOD_TIME | F_ADD_DT_TIME |
----------------|----------------|---------------|
| Input Type 1 | TIME_OF_DAY | DATE_AND_TIME |
| Output Type | TIME_OF_DAY | DATE_AND_TIME |
| Range | Daily Cycle | Absolute Date |

## Conclusion

The F_ADD_TOD_TIME function block offers essential functions for calculating the time of day:

- Precise handling of time-of-day operations
- Automatic handling of day transitions
- Optimized performance for real-time applications

Ideal for control applications that require recurring time-of-day-based operations. The specialized implementation guarantees correct results in 24-hour format.
