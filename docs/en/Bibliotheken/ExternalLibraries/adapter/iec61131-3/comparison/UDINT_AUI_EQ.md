# UDINT_AUI_EQ

![UDINT_AUI_EQ](./UDINT_AUI_EQ.svg)

* * * * * * * * * *
## Introduction

The function block **UDINT_AUI_EQ** is used to compare two values for equality. It is designed as a generic comparison block that accepts two input values via a socket adapter (IN2) and a direct data input (IN1) and outputs the result via a plug adapter (OUT). The name suggests an original use with integer data types (UDINT), but the actual implementation works with the generic type `ANY_ELEMENTARY`.
## Interface Structure

### **Event Inputs**

| Name | Type | With Variables | Comment |
|------|-----|----------------|-----------|
| REQ | Event | IN1 | Serves as the trigger for the comparison. The value of IN1 is processed at the REQ input when an event occurs. |

### **Event Outputs**

No direct event outputs are available. The result is signaled via the adapter output (OUT).

### **Data Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| IN1 | ANY_ELEMENTARY | First value to be compared. The data type can be any elementary type (e.g., BOOL, INT, REAL, UDINT). |

### **Data Outputs**

No direct data outputs. The comparison result is provided via the adapter output (OUT).

### **Adapter**

| Name | Type | Direction | Comment |
|------|-----|----------|-----------|
| IN2 | adapter::types::unidirectional::AUI | Socket (Input) | Second value to be compared; provided via the adapter as an event and data value. |
| OUT | adapter::types::unidirectional::AX | Plug (Output) | Outputs the result of the comparison (TRUE if equal, otherwise FALSE) as an event and data value. |

## Functionality

The function block performs an equality comparison between the values supplied to IN1 and those supplied via the IN2 adapter. The processing proceeds as follows:

1. An event can be received either directly at the **REQ** input or via the **IN2** adapter (its event input "E1"). Both events are internally routed to the input of the comparison function block **F_EQ**.

2. Simultaneously, the data values from **IN1** and **IN2.D1** are passed to the corresponding inputs of **F_EQ**.

3. The internal function block **F_EQ** (type *iec61131::comparison::F_EQ*) performs the actual comparison and outputs the Boolean result at its output **OUT**.
4. This result is forwarded to the **OUT** adapter, which passes both the event **E1** and the data value **D1** to the subsequent logic.

The function block operates purely event-driven – a comparison is only performed upon an incoming event.

## Technical Features

- **Generic Data Type**: Input IN1 is declared as `ANY_ELEMENTARY`, allowing the function block to work with almost all elementary data types (BOOL, BYTE, WORD, DWORD, SINT, INT, DINT, LINT, USINT, UINT, UDINT, ULINT, REAL, LREAL).
- **Adapter-Based Interface**: Instead of classic inputs/outputs, adapters (socket/plug) are used. This enables flexible coupling to other function blocks with compatible adapter types.
- **No State Machine**: The function block does not have its own ECC (Execution Control Chart), but implements its functionality purely via the included subnetwork with the function block F_EQ.
- **Event Passing**: Both the event from REQ and that from IN2 are passed to the same internal REQ input of F_EQ. This can lead to conflicts with parallel events (the last event takes precedence), which must be considered during application.

## State Overview

The function block does not have an explicit finite state machine. Its behavior corresponds to that of the included F_EQ function block, which operates as a pure function without state memory.

## Application Scenarios

- **Sensor Data Comparison**: A measured value (IN1) is compared with a reference value (via IN2) to determine equality (e.g., for limit monitoring).
- **Identity Check**: In control engineering, it can be checked whether two input signals are identical before an action is triggered.
- **Adapter-Based Architectures**: Use in modular systems where data is to be exchanged via standardized adapters (e.g., in IEC 61499-based distributed systems).

## Comparison with Similar Function Blocks

- **IEC 61131 EQ**: The standard equality function block (e.g., `EQ` in IEC 61131) has classic inputs/outputs without adapters. *UDINT_AUI_EQ* encapsulates the equality functionality and adds an adapter-based interface.
- **Direct F_EQ**: The internal function block *F_EQ* also operates on the same comparison logic, but expects both values at its data inputs and directly outputs a Boolean value. *UDINT_AUI_EQ* extends this with separate event control via adapters.
- **Inequality Comparisons**: Transform blocks like `NE`, `GT`, and `LT` use similar structures but differ in their comparison operator.

## Conclusion

The **UDINT_AUI_EQ** is a useful block for equality comparisons in environments that rely on adapter communication. Its generic data type makes it suitable for many applications, while the adapter-based interface allows for a clean separation of event and data flow. The absence of a dedicated state machine keeps the implementation simple and efficient. When using it, potential event conflicts due to duplicate event signaling should be considered.
