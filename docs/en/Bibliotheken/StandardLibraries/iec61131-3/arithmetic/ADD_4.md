# ADD_4
![ADD_4](https://user-images.githubusercontent.com/116869307/214143055-ad68b786-ea59-490e-9e7b-c43c007e0ae7.png)

* * * * * * * * * *
## Introduction
The **ADD_4** is a powerful function block for summing four values, developed under the EPL-2.0 license. As part of the GEN_ADD class, version 1.0 offers a type-safe implementation according to the IEC 61131-3 standard.
![ADD_4](ADD_4.svg)

## Interface Structure

### **Event Inputs**
- `REQ`: Calculation request (with four input values)

### **Event Outputs**
- `CNF`: Calculation confirmation (with total result)

### **Data Inputs**
- `IN1` (ANY_MAGNITUDE): First addend
- `IN2` (ANY_MAGNITUDE): Second addend
- `IN3` (ANY_MAGNITUDE): Third addend
- `IN4` (ANY_MAGNITUDE): Fourth addend

### **Data Outputs**
- `OUT` (ANY_MAGNITUDE): Result of addition (IN1+IN2+IN3+IN4)

## Functional Features

1. **Calculation Triggering**:

- A single `REQ` event processes all four inputs
- Parallel value acquisition

2. **Type Handling**:

- Automatic type conversion for mixed inputs
- Result in the "largest" input type

3. **Calculation Order**:

- Mathematically associative (IN1+(IN2+(IN3+IN4)))
- Guaranteed reproducible results

## Technical Specifications

✔ **Four-input addition** in one operation
✔ **Full ANY_MAGNITUDE support**

✔ **Optimized calculation performance**
✔ **Deterministic behavior**

## Supported Data Types

| Category | Examples |
----------------|-------------------------|
Integers | INT, DINT, UDINT |
Floating Point | REAL, LREAL |
Time Values | TIME, LTIME |
Special Types | DATE_AND_TIME |

## Application Scenarios
- **Energy Monitoring**: Summing of Consumers
- **Production Control**: Quantity Measurement of Multiple Lines
- **Measurement Data Analysis**: Aggregation of Sensor Values
- **Robot Control**: Multidimensional Position Calculation

## ⚖️ Comparison with Other Adders

| Function Block | Inputs | Advantages |
|----------|----------|----------|
| ADD_2 | 2 | Simplest Variant |
| ADD_3 | 3 | Compromise |
| ADD_4 | 4 | Maximum Integration |

## Error Management
- **Type Conflicts**: Result 0 in case of incompatibility
- **Overflow**: Wrap-around depending on data type
- **Status Feedback**: Via accompanying logic

## Conclusion

The ADD_4 block offers maximum efficiency for summation tasks:

- Compact quadruple calculation
- Broadest type support
- Optimized performance

Ideal for complex control applications with multiple values to be aggregated. The generic implementation as GEN_ADD enables maximum flexibility with type-safe execution.
