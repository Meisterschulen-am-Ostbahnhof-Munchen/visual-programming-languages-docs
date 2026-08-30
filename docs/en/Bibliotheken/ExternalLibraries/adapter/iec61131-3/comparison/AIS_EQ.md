# AIS_EQ

![AIS_EQ](./AIS_EQ.svg)

* * * * * * * * * *
## Introduction

The function block **AIS_EQ** compares two values of type `STRING` (character string) and checks whether the first value (IN1) is equal to the second value (IN2). The result is provided as a Boolean value via the output adapter. The function block is event-driven and operates asynchronously. The comparison is performed lexicographically (character by character) according to the character encoding.
## Interface Structure

The function block has no direct event or data inputs and outputs, but communicates exclusively via adapters.

### **Event Inputs**

- **IN1.E1**: Event input of socket adapter IN1 – triggers the comparison.
- **IN2.E1**: Event input of socket adapter IN2 – also triggers the comparison.

### **Event Outputs**

- **OUT.E1**: Event output of the plug adapter OUT – indicates that the comparison result is available at the data output.

### **Data Inputs**

- **IN1.D1**: First value to be compared (data type `STRING`, character string).
- **IN2.D1**: Second value to be compared (data type same as IN1).

### **Data Outputs**

- **OUT.D1**: Boolean result of the comparison – `TRUE` if `IN1 = IN2`, otherwise `FALSE`.

### **Adapters**

| Adapter | Type | Direction | Description |
|---------|-----|----------|--------------|
| IN1 | `AIS` (Socket) | Input | Adapter for the first comparison value and its associated event |
| IN2 | `AIS` (Socket) | Input | Adapter for the second comparison value and its associated event |
| OUT | `AX` (Plug) | Output | Adapter for the comparison result and the output event |

The adapters `AIS` and `AX` are unidirectional interfaces, each providing one event channel and one data channel.

## Functionality

1. The function block waits for an event at one of the socket adapters **IN1.E1** or **IN2.E1**.
2. As soon as such an event arrives, it is forwarded to the internal function block `F_EQ` (type `iec61131::comparison::F_EQ`). There, the current values of `IN1.D1` and `IN2.D1` are compared.
3. The internal function block generates an output event (`CNF`) and outputs the Boolean result (`OUT`).
4. This event is propagated to the plug adapter **OUT.E1**, and the data value `OUT.D1` is set to `TRUE` or `FALSE`.
5. Output occurs only when the input values change or when another event occurs.

## Technical Features

- **Adapter-based interface**: The function block uses only adapters (`AIS`/`AX`), allowing for flexible integration into various communication contexts.
- **Asynchronous processing**: The comparison operation is triggered by an event at one of the input adapters; the output signal is delivered in response to the event.
- **Standard compliance**: The function block implements the comparison function from IEC 61131-3 ("equal to") for the `STRING` data type.
- **Comparison logic**: The comparison is performed lexicographically (character by character) according to the character encoding.
- **No state machines**: The function block is purely combinational – the result is generated immediately after the event; there is no internal state.

## State Overview

This function block does not have an explicit state machine (ECC). Its internal logic consists of a direct connection between the adapters and a standardized comparison function block. Output occurs immediately upon event input.

## Application Scenarios

- **Limit Monitoring**: Checking recipe and text identifiers against a reference or threshold value of type `STRING`.
- **Control Logic**: Triggering an action once two values of type `STRING` satisfy the "equal to" condition.
- **Data Filtering**: Selecting data records or signals that satisfy a `STRING`-based comparison condition.

## Comparison with Similar Function Blocks

- **AIS_NE**: Checks for "not equal to" – the inverse function of AIS_EQ.
- **AIS_NE**: Checks for inequality of values.

AIS_EQ is part of the complete AIS comparison family (EQ/NE/GT/GE/LT/LE) for the `STRING` data type.

## Conclusion

AIS_EQ is a simple yet important comparison block for IEC 61131-3 control applications using the `STRING` data type. Its adapter-oriented interface makes it versatile and allows for a clear separation of event and data paths. Due to its event-driven operation, it is particularly suitable for real-time systems where conditions must react immediately to changes in values.
