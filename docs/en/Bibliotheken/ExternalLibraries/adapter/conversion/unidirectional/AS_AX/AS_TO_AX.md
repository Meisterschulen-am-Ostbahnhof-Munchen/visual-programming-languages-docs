# AS_TO_AX

![AS_TO_AX](./AS_TO_AX.svg)

* * * * * * * * * *
## Introduction

The **AS_TO_AX** function block is a composite function block that converts a SINT adapter (AS) into a BOOL adapter (AX). It checks the incoming SINT value for inequality to zero and outputs the result as a BOOL signal. The function block is suitable for simple signal conversion in an IEC 61499 application.
## Interface Structure

### **Event Inputs**

| Name | Type | Description |
|------|-----|--------------|
| AS_IN.E1 | Event | Receives the trigger signal from the connected AS adapter for data processing. |

### **Event Outputs**

| Name | Type | Description |
|------|-----|-------------|
| AX_OUT.E1 | Event | Sent after successful conversion; indicates that the BOOL value is present at the AX adapter. |

### **Data Inputs**

| Name | Type | Description |
|------|-----|-------------|
| AS_IN.D1 | SINT | Receives the SINT value, which is checked for inequality to zero. |

### **Data Outputs**

| Name | Type | Description |
|------|-----|-------------|
| AX_OUT.D1 | BOOL | Outputs the result of the comparison: `TRUE` if the input value is not zero, otherwise `FALSE`. |

### **Adapter**

| Name | Type | Direction | Description |
|------|-----|----------|-------------|
| AS_IN | adapter::types::unidirectional::AS | Socket (Input) | SINT adapter for the input value and its associated event. |
| AX_OUT | adapter::types::unidirectional::AX | Plug (Output) | BOOL adapter for the output value and its associated event. |

## Functionality

The function block internally uses the function block `iec61131::comparison::F_NE` (inequality check).

- When an event is received at input `AS_IN.E1`, processing of `F_NE` (input `REQ`) is started.
- `F_NE` compares the SINT value received via `AS_IN.D1` with the constant parameter `IN2` (fixed to `SINT#0`).
- The result of the comparison (`OUT`) – `TRUE` if inequality, `FALSE` if equality – is forwarded to the data output `AX_OUT.D1`.
- After the calculation is complete, the event `AX_OUT.E1` is triggered via `F_NE.CNF`, signaling the new BOOL value at the AX adapter.

## Technical Features

- **Type Conversion**: The function block implicitly converts a SINT adapter to a BOOL adapter without requiring the user to write direct type conversion logic.
- **Use of Standard Function Blocks**: Internally, the existing IEC 61131 function block `F_NE` is used, increasing reusability and testability.
- **Fixed Comparison Value**: The parameter `IN2` is preset to `SINT#0` – a change is only possible by modifying the composite function block.

## State Overview

Since this is a composite function block without its own state machine, its behavior is limited to the data and event flow according to the internal interconnection. The states result from the processing function block `F_NE`:

- **Idle**: No event is pending.
- **Processing**: An event is being processed (comparison in progress).
- **Completed**: The comparison is complete, and the result is available at the output.

## Application Scenarios

- **Threshold Check**: Conversion of a SINT counter value into a BOOL signal that indicates whether the value deviates from zero (e.g., "Motor running").
- **Adapter Bridge**: Connection of a component with an AS interface to a component with an AX interface without manual conversion.
- **Simple Status Indication**: Signal transmission indicating whether a data record exists (non-zero) or not.

## Comparison with Similar Function Blocks

- **Direct Conversion Function Blocks** (e.g., `SINT_TO_BOOL`): Convert the data type without adapter logic, but do not provide event-driven behavior via adapters.
- **Custom Composite Solution**: Offers flexibility, but requires more effort; `AS_TO_AX` cleanly encapsulates the conversion and is reusable.
- **Adapter Wrappers**: Other function blocks may use different comparison operations (e.g., `F_EQ`), specifically checking for inequality to zero.

## Conclusion

The **AS_TO_AX** function block provides a compact and reliable solution for converting a SINT adapter signal to a BOOL adapter signal. By utilizing the IEC 61131 standard function block `F_NE`, its behavior is deterministic and easily traceable. This function block is particularly suitable for applications requiring simple zero checks across adapter boundaries.
