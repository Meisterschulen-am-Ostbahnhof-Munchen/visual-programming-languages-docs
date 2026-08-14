# ATM_AR_DIVTIME

![ATM_AR_DIVTIME](./ATM_AR_DIVTIME.svg)

* * * * * * * * * *
## Introduction

The function block **ATM_AR_DIVTIME** divides a time value (type TIME) by a numeric value -- the fully adapter-based variant of [AR_DIVTIME](AR_DIVTIME.md). Unlike AR_DIVTIME, the dividend (IN1) is also supplied via an adapter (type `ATM`) instead of a fixed data input. The block is classified as a standard arithmetic function according to IEC 61131-3.
## Interface Structure

### **Event Inputs**

None -- the block has no classic event inputs; triggering happens exclusively via the adapter sockets.

### **Event Outputs**

No explicit event outputs in the interface list. The result is provided via the output adapter **OUT**, which sends an event (E1) once the calculation is complete.

### **Data Inputs**

None.

### **Data Outputs**

None. The division result is output via the output adapter **OUT** as a data value (D1).

### **Adapters**

- **IN1** (Adapter, type `adapter::types::unidirectional::ATM`): Time value to be divided (dividend).
- **IN2** (Adapter, type `adapter::types::unidirectional::AR`): Divisor.
- **OUT** (Adapter, type `adapter::types::unidirectional::ATM`): Output for the division result (TIME).

## Functionality

The function block encapsulates the functionality of the internal function block **F_DIVTIME** (type `iec61131::arithmetic::F_DIVTIME`). An event at **IN1.E1** or **IN2.E1** triggers the division: the internal function block divides **IN1.D1** (TIME) by **IN2.D1** (numeric value) and outputs the result to **OUT.D1**. An event is then sent to **OUT.E1**.

## Technical Features

- **Fully adapter-based:** Unlike `AR_DIVTIME`, which expects IN1 as a classic data input, `ATM_AR_DIVTIME` implements both operands as adapter sockets (IN1 of type `ATM`, IN2 of type `AR`).
- **Standard compliance:** The function block meets the requirements of IEC 61131-3 (classification: standard arithmetic function).
- **Internal encapsulation:** The actual calculation is performed by the reusable function block F_DIVTIME.

## State Overview

The function block does not have an explicit state machine. Event-driven processing is deterministic: waiting for an event at IN1.E1 or IN2.E1, executing the division, sending the result.

## Application Scenarios

- Splitting time values where both the time value and the divisor are already available as adapter connections from upstream blocks.
- Modular networks that consistently rely on adapters instead of classic data wiring.

## Comparison with Similar Function Blocks

- **AR_DIVTIME:** The mixed variant with IN1 as a classic data input instead of an adapter socket.
- **ATM_AR_MULTIME:** Multiplies instead of dividing, otherwise structurally identical.

## Conclusion

`ATM_AR_DIVTIME` provides a fully adapter-based division of time values by numeric factors and is particularly suitable for networks that are built consistently around adapter connections.
