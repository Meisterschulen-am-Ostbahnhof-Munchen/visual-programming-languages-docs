# AB_LT

![AB_LT](./AB_LT.svg)

* * * * * * * * * *
## Introduction

The function block **AB_LT** compares two values of type `BYTE` (8-bit bit pattern (byte)) and checks whether the first value (IN1) is less than the second value (IN2). The result is provided as a Boolean value via the output adapter. The function block is event-driven and operates asynchronously. The bit patterns are interpreted as unsigned integers and compared numerically.
## Interface Structure

The function block has no direct event or data inputs and outputs, but communicates exclusively via adapters.

### **Event Inputs**

* **IN1.E1**: Event input of socket adapter IN1 – triggers the comparison.
* **IN2.E1**: Event input of socket adapter IN2 – also triggers the comparison.

### **Event Outputs**

* **OUT.E1**: Event output of the plug adapter OUT – indicates that the comparison result is available at the data output.

### **Data Inputs**

* **IN1.D1**: First value to be compared (data type `BYTE`, 8-bit bit pattern (byte)).
* **IN2.D1**: Second value to be compared (data type same as IN1).

### **Data Outputs**

* **OUT.D1**: Boolean result of the comparison – `TRUE` if `IN1 < IN2`, otherwise `FALSE`.

### **Adapters**

| Adapter | Type | Direction | Description |
|---------|-----|----------|--------------|
| IN1 | `AB` (Socket) | Input | Adapter for the first comparison value and its associated event |
| IN2 | `AB` (Socket) | Input | Adapter for the second comparison value and its associated event |
| OUT | `AX` (Plug) | Output | Adapter for the comparison result and the output event |

The adapters `AB` and `AX` are unidirectional interfaces, each providing one event channel and one data channel.

## Functionality

1. The function block waits for an event at one of the socket adapters **IN1.E1** or **IN2.E1**.
2. As soon as such an event arrives, it is forwarded to the internal function block `F_LT` (type `iec61131::comparison::F_LT`). There, the current values of `IN1.D1` and `IN2.D1` are compared.
3. The internal function block generates an output event (`CNF`) and outputs the Boolean result (`OUT`).
4. This event is propagated to the plug adapter **OUT.E1**, and the data value `OUT.D1` is set to `TRUE` or `FALSE`.
5. Output occurs only when the input values change or when another event occurs.

## Technical Features

- **Adapter-based interface**: The function block uses only adapters (`AB`/`AX`), allowing for flexible integration into various communication contexts.
- **Asynchronous processing**: The comparison operation is triggered by an event at one of the input adapters; the output signal is delivered in response to the event.
- **Standard compliance**: The function block implements the comparison function from IEC 61131-3 ("less than") for the `BYTE` data type.
- **Comparison logic**: The bit patterns are interpreted as unsigned integers and compared numerically.
- **No state machines**: The function block is purely combinational – the result is generated immediately after the event; there is no internal state.

## State Overview

This function block does not have an explicit state machine (ECC). Its internal logic consists of a direct connection between the adapters and a standardized comparison function block. Output occurs immediately upon event input.

## Application Scenarios

- **Limit Monitoring**: Checking status register against a reference or threshold value of type `BYTE`.
- **Control Logic**: Triggering an action once two values of type `BYTE` satisfy the "less than" condition.
- **Data Filtering**: Selecting data records or signals that satisfy a `BYTE`-based comparison condition.

## Comparison with Similar Function Blocks

- **AB_GT**: Checks for "greater than" – the inverse function of AB_LT.
- **AB_EQ**: Checks for equality of values.
- **AB_LE**: Performs the "less than or equal to" comparison – the extended version of AB_LT that includes the equality case.

AB_LT is the basic "less than" component without the equality case, complemented by AB_LE.

## Conclusion

AB_LT is a simple yet important comparison block for IEC 61131-3 control applications using the `BYTE` data type. Its adapter-oriented interface makes it versatile and allows for a clear separation of event and data paths. Due to its event-driven operation, it is particularly suitable for real-time systems where conditions must react immediately to changes in values.
