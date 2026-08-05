# F_ADD_DT_TIME
![Zeitadditionssymbol](https://github.com/user-attachments/assets/1fda9baa-1d7c-4fa6-8c87-608436deefa8)
* * * * * * * * * *
![F_ADD_DT_TIME](F_ADD_DT_TIME.svg)
## Introduction
The **F_ADD_DT_TIME** function block is a specialized function module for adding time values to date/time values, developed under the EPL 2.0 license. Version 1.0 enables precise time calculations using DATE_AND_TIME and TIME data types.

## Interface Structure

### **Event Inputs**
- `REQ`: Calculation request (with input values)

### **Event Outputs**
- `CNF`: Calculation confirmation (with result)

### **Data Inputs**
- `IN1` (DATE_AND_TIME): Output date/time
- `IN2` (TIME): Duration for addition

### **Data Outputs**
- `OUT` (DATE_AND_TIME): Result of the addition

## Functionality

1. **Activation**:

- Triggered by the `REQ` event
- Processes DATE_AND_TIME and TIME values

2. **Calculation**:

- Adds time duration (IN2) to timestamp (IN1)
- Automatically takes into account:
- Leap years
- Month lengths
- Time zones (if configured)

3. **Result output**:

- `CNF` event with new DATE_AND_TIME
- Format: DT#2023-12-31-23:59:59

## Technical Specifications

✔ **Precise time/date arithmetic**
✔ **Automatic calendar calculation**

✔ **IEC 61131-3 compliant**
✔ **Deterministic execution**

## Application examples
- **Process control**: Due date calculations
- **Production planning**: Scheduling adjustments
- **Maintenance systems**: Maintenance interval calculation
- **Data logging**: Timestamp corrections

## Special notes
- **Scope of validity**:
- Supports date range 1970-2099
- Time resolution: 1 millisecond
- **Error cases**:
- In case of overflow: Wrap-around within the valid range
- In case of invalid input: OUT = IN1

## ⚖️ Comparison with standard F_ADD

| Feature | F_ADD_DT_TIME | F_ADD |

|----------------|---------------|-------------|

| Input type 1 | DATE_AND_TIME | ANY_MAGNITUDE |

| Input type 2 | TIME | ANY_MAGNITUDE |

| Operation | Specialized time addition | Generic addition |

## Conclusion

The F_ADD_DT_TIME function block offers essential functions for time calculations:

- Precise handling of date/time operations
- Automatic calendar corrections
- Reliable integration into control systems

Particularly valuable for applications requiring complex time calculations with automatic consideration of calendar rules. The specialized implementation guarantees correct results for all valid input values.