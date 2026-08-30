# ALI_GT

![ALI_GT](./ALI_GT.svg)

* * * * * * * * * *
## Introduction

The function block **ALI_GT** compares two values of type `LINT` (64-bit signed integer) and checks whether the first value (IN1) is greater than the second value (IN2). The result is provided as a Boolean value via the output adapter. The function block is event-driven and operates asynchronously. The comparison follows the usual numeric ordering.
## Interface Structure

The function block has no direct event or data inputs and outputs, but communicates exclusively via adapters.

### **Event Inputs**

- **IN1.E1**: Event input of socket adapter IN1 – triggers the comparison.
- **IN2.E1**: Event input of socket adapter IN2 – also triggers the comparison.

### **Event Outputs**

- **OUT.E1**: Event output of the plug adapter OUT – indicates that the comparison result is available at the data output.

### **Data Inputs**

- **IN1.D1**: First value to be compared (data type `LINT`, 64-bit signed integer).
- **IN2.D1**: Second value to be compared (data type same as IN1).

### **Data Outputs**

- **OUT.D1**: Boolean result of the comparison – `TRUE` if `IN1 > IN2`, otherwise `FALSE`.

### **Adapters**

| Adapter | Type | Direction | Description |
|---------|-----|----------|--------------|
| IN1 | `ALI` (Socket) | Input | Adapter for the first comparison value and its associated event |
| IN2 | `ALI` (Socket) | Input | Adapter for the second comparison value and its associated event |
| OUT | `AX` (Plug) | Output | Adapter for the comparison result and the output event |

The adapters `ALI` and `AX` are unidirectional interfaces, each providing one event channel and one data channel.

## Functionality

1. The function block waits for an event at one of the socket adapters **IN1.E1** or **IN2.E1**.
2. As soon as such an event arrives, it is forwarded to the internal function block `F_GT` (type `iec61131::comparison::F_GT`). There, the current values of `IN1.D1` and `IN2.D1` are compared.
3. The internal function block generates an output event (`CNF`) and outputs the Boolean result (`OUT`).
4. This event is propagated to the plug adapter **OUT.E1**, and the data value `OUT.D1` is set to `TRUE` or `FALSE`.
5. Output occurs only when the input values change or when another event occurs.

## Technical Features

- **Adapter-based interface**: The function block uses only adapters (`ALI`/`AX`), allowing for flexible integration into various communication contexts.
- **Asynchronous processing**: The comparison operation is triggered by an event at one of the input adapters; the output signal is delivered in response to the event.
- **Standard compliance**: The function block implements the comparison function from IEC 61131-3 ("greater than") for the `LINT` data type.
- **Comparison logic**: The comparison follows the usual numeric ordering.
- **No state machines**: The function block is purely combinational – the result is generated immediately after the event; there is no internal state.

## State Overview

This function block does not have an explicit state machine (ECC). Its internal logic consists of a direct connection between the adapters and a standardized comparison function block. Output occurs immediately upon event input.

## Application Scenarios

- **Limit Monitoring**: Checking large counter and total values against a reference or threshold value of type `LINT`.
- **Control Logic**: Triggering an action once two values of type `LINT` satisfy the "greater than" condition.
- **Data Filtering**: Selecting data records or signals that satisfy a `LINT`-based comparison condition.

## Comparison with Similar Function Blocks

- **ALI_LT**: Checks for "less than" – the inverse function of ALI_GT.
- **ALI_EQ**: Checks for equality of values.
- **ALI_GE**: Performs the "greater than or equal to" comparison – the extended version of ALI_GT that includes the equality case.

ALI_GT is the basic "greater than" component without the equality case, complemented by ALI_GE.

## Conclusion

ALI_GT is a simple yet important comparison block for IEC 61131-3 control applications using the `LINT` data type. Its adapter-oriented interface makes it versatile and allows for a clear separation of event and data paths. Due to its event-driven operation, it is particularly suitable for real-time systems where conditions must react immediately to changes in values.
