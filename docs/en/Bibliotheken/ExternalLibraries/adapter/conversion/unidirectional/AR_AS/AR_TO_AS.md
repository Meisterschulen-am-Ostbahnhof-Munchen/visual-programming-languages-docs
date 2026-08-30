# AR_TO_AS

![AR_TO_AS](./AR_TO_AS.svg)

* * * * * * * * * *
The function block **AR_TO_AS** is a composite block that converts a **REAL adapter** (AR) into a **SINT adapter** (AS). It enables simple and standardized conversion between the adapter types and encapsulates the necessary logic in a reusable block.
The function block does not have separate event or data ports at the IEC 61499 level. All communication takes place via the integrated adapters. The following table describes the available adapters.

No dedicated event inputs are available. Events are received via the **AS_OUT adapter** (see Adapters).

No dedicated event outputs are available. Events are sent via the **AR_IN adapter** (see Adapters).

No dedicated data inputs. Data is received via the **AS_OUT adapter** (see Adapters).

No dedicated data outputs. Data is sent via the **AR_IN adapter** (see Adapters).

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

| Adapter | Type | Direction | Description |
| --------- | ----- | ----------- | -------------- |
| `AR_IN` | `adapter::types::unidirectional::AR` | Socket (inbound) | Unidirectional REAL adapter. Returns a REAL value (D1) and an associated event (E1). |
| `AS_OUT` | `adapter::types::unidirectional::AS` | Plug (outbound) | Unidirectional SINT adapter. Receives a SINT value (D1) and an associated event (E1). |

## Functionality

The function block performs the conversion as follows:

1. An incoming event on **AR_IN.E1** triggers the internal conversion block **F_REAL_TO_SINT**.
2. The REAL value associated with the event from **AR_IN.D1** is forwarded to the input `IN` of the conversion block.
3. **F_REAL_TO_SINT** converts the REAL value into a SINT value and outputs the result to its output `OUT`. 4. After the conversion is complete, an event is sent via **AS_OUT.E1**, along with the converted SINT value to **AS_OUT.D1**.

A synchronous 1:1 conversion takes place – each incoming REAL request generates exactly one outgoing SINT response.

- **Reusability**: The function block is based on the standard FB `F_REAL_TO_SINT` from the IEC 61131 library. This ensures that the conversion logic is standards-compliant and available on many platforms.
- **Adapter Interface**: The use of adapters allows for loose coupling between function blocks and facilitates the exchange or extension of the interface.
- **Value Range**: When converting from REAL (approx. ±3.4 × 10³⁸) to SINT (−128 … 127), value range exceedances can occur. The internal function block `F_REAL_TO_SINT` behaves according to the IEC 61131 definition (overflow or use of saturation behavior). The user should limit the input values accordingly.

The **AR_TO_AS** does not have its own state machine. Since it is a pure composite function block that only establishes the connection between the incoming and outgoing adapters, there is no internal state behavior. The function block operates combinatorially at the event level.

- **Integration of REAL-based function blocks in SINT environments**: If a component provides a REAL adapter, but the subsequent function block expects a SINT adapter, **AR_TO_AS** can be used as an intermediary adapter.
- **Type-safe conversion in modular controllers**: By using adapters, the typing is preserved, and the conversion is explicitly visible in the network.
- **Library extension**: The function block can be used as part of an adapter conversion library to standardize data exchange between different numerical resolutions.

Analogous conversion adapters exist, e.g.,... B.:

- **AR_TO_INT** – REAL → INT
- **AR_TO_UDINT** – REAL → UDINT
- **AR_TO_LREAL** – REAL → LREAL

All of these modules share the use of the corresponding IEC 61131 conversion block. The difference lies in the target type and the adapter definition. **AR_TO_AS** is specifically designed for conversion to the narrow, signed 8-bit SINT type.

The **AR_TO_AS** is a simple yet effective composite module for converting a REAL adapter to a SINT adapter. It cleanly encapsulates the conversion logic and enables type-safe, event-driven communication between function blocks with different numeric interfaces. Thanks to the use of standard libraries, it is reliable and platform-independent.

## Technical Features

- **Numeric conversion**: value-preserving cast (narrowing may truncate, widening/sign-extension is safe).

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion
