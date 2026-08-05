# AR_TO_AUDI
![AR_TO_AUDI](./AR_TO_AUDI.svg)

* * * * * * * * * *
## Introduction
The function block `AR_TO_AUDI` is a composite function block (FB) that receives a REAL value from a unidirectional **AR** adapter, converts it to a **UDINT** value, and outputs it via an **AUDI** adapter. It encapsulates the type conversion `REAL_TO_UDINT` and simplifies integration into adapter-based communication structures.
## Interface Structure

The function block has no dedicated event or data inputs/outputs. All communication takes place via two adapters (socket and plug).

## **Adapter (Socket – Input)**

| Name | Type | Comment |
|---|---|---|
| `AR_IN` | `adapter::types::unidirectional::AR` | Unidirectional REAL adapter as input |

The adapter `AR_IN` provides an event `E1` and a data input `D1` of type `REAL`.

### **Adapter (Plug – Output)**

| Name | Type | Comment |
|---|---|---|
| `AUDI_OUT` | `adapter::types::unidirectional::AUDI` | Unidirectional UDINT adapter as output |

The adapter `AUDI_OUT` expects an event `E1` and a data output `D1` of type `UDINT`.

## Functionality

The function block internally contains an instance of the conversion function block `F_REAL_TO_UDINT` from the library `iec61131::conversion`. The signal connections implement a simple data flow:

1. **Event from the input adapter**

The event `AR_IN.E1` triggers the conversion function block via its event input `REQ`.

2. **Data Conversion**

Simultaneously, the REAL value of `AR_IN.D1` is transferred to the data input `IN` of `F_REAL_TO_UDINT`. The conversion occurs without delay within the event cycle.

3. **Output Event and Result**

After successful conversion, `F_REAL_TO_UDINT` sends an acknowledgment event (`CNF`) to the output adapter (`AUDI_OUT.E1`). The converted UDINT value is forwarded to `AUDI_OUT.D1` via the data output `OUT`.

The conversion is synchronous: Each incoming event triggers exactly one output.

## Technical Features
- **Composite Block** – The logic is implemented entirely through an internal network; there is no standalone algorithm or state machine.
- **Unidirectional Adapters** – Both the input and output interfaces are unidirectional and transmit only one event/data channel.
- **Library Used** – Conversion is performed using the IEC 61131 block `F_REAL_TO_UDINT`, which is hardware-independent and widely used.
- **No Error Handling** – The block does not perform range or type checking; the REAL to UDINT conversion follows standard rules (rounding, delimiting).

## State Overview

Since the block does not have its own state machine, its operation is determined solely by the event network:

- **Idle** – No event is active at `AR_IN.E1`; the output adapter remains inactive.
- **Active** – An incoming event immediately triggers the conversion and produces an output event. Upon completion, the function block returns to its idle state (no internal memory).

## Application Scenarios
- **Bridging** between system components that provide REAL values (e.g., floating-point sensors) and components that process UDINT values (e.g., counters, index management).
- **Adapter-based communication** in distributed automation systems according to IEC 61499, when the interfaces are defined as unidirectional adapters.
- **Type conversion** in data preprocessing paths before values are passed to programmable logic controllers (PLCs) or visualizations.

## Comparison with Similar Function Blocks
- **REAL_TO_DINT** – converts REAL to a signed 32-bit integer; here, the conversion is to an unsigned integer (UDINT).
- **AR_TO_xx blocks** – Other variants could convert to, for example, `AR_TO_BYTE` or `AR_TO_DWORD`, but without the adapter frame.
- **Direct converter** – The internal block `F_REAL_TO_UDINT` can also be integrated directly without an adapter; `AR_TO_AUDI` offers an encapsulated, easily replaceable interface.

## Conclusion

The block `AR_TO_AUDI` provides a cleanly encapsulated, adapter-based type conversion from REAL to UDINT. It reduces wiring effort in modular IEC 61499 projects and ensures reliable, event-driven implementation. The use of standardized conversion blocks makes the solution portable and easy to understand.
