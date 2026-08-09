# AB_MUX_3

![AB_MUX_3](./AB_MUX_3.svg)

* * * * * * * * * *
## Introduction

The function block `AB_MUX_3` is a generic multiplexer for adapters of type `adapter::types::unidirectional::AB`. Depending on the value of the index `K` (0, 1, or 2), it selects one of three inputs (`IN1`, `IN2`, `IN3`) and passes it to the output `OUT`. The switching is triggered by the event `REQ` and acknowledged upon completion with `CNF`.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|-------|-------|--------------------------|
| `REQ` | Event | Set Index K (with Var `K`)|

### **Event Outputs**

| Name | Type | Comment |
|-------|-------|----------------------------------|
| `CNF` | Event | Confirmation of Set Index K |

### **Data Inputs**

| Name | Type | Comment |
|------|-------|--------------|
| `K` | UINT | Index (0-2) |

### **Data Outputs**

None.

### **Adapters**

| Name | Direction | Type | Comment |
|------|----------|--------------------------------------|-------------------------------|
| `OUT`| Plug | `adapter::types::unidirectional::AB` | Output – connects the selected input |
| `IN1`| Socket | `adapter::types::unidirectional::AB` | Input value 1 (when K=0) |
| `IN2`| Socket | `adapter::types::unidirectional::AB` | Input value 2 (when K=1) |
| `IN3` | Socket | `adapter::types::unidirectional::AB` | Input value 3 (when K=2) |

## Functionality

1. The function block waits for a `REQ` event.
2. Upon arrival, the value of `K` is read.
3. Depending on `K` (0, 1, or 2), the corresponding socket adapter (`IN1`, `IN2`, `IN3`) is switched to the plug adapter `OUT`.
4. After successful switching, the event `CNF` is sent.
5. The function block returns to the wait state and can be controlled again by `REQ`.

## Technical Features

- The function block is generic and is listed in the development environment as `GEN_AB_MUX` (attribute `GenericClassName`).
- All adapters are unidirectional of type `adapter::types::unidirectional::AB`.
- There are no data outputs – all data transmission is handled via the adapter `OUT`.
- The index `K` is defined as `UINT` (unsigned integer); values outside 0-2 are undefined.

## State Overview

The function block does not have an explicit state machine (ECC) in its XML definition. The implicit flow control can be represented as follows:

[Idle] → bei REQ → [Execute] → setze OUT gemäß K → sende CNF → [Idle]

- **Idle**: Waiting for a `REQ` event.
- **Execute**: Evaluating `K`, switching the adapter, sending `CNF`.

## Application Scenarios

- **Signal Switching**: Selection between three different AB adapter signals (e.g., sensor data, control commands).
- **Operating Mode Selection**: Switching between different configuration sources in an automation application.
- **Agricultural Technology**: For example, switching between different measured values (speed, temperature, pressure) to a common output.

## Comparison with Similar Function Blocks

- **Standard multiplexer blocks** (e.g., `MUX_2`, `MUX_4`) typically use simple data types (BOOL, INT) instead of adapters. `AB_MUX_3` is specifically designed for AB adapters.
- Unlike a generic multiplexer with a variable number of inputs, this block is fixed to three inputs, which simplifies handling and increases type safety.

## Conclusion

The `AB_MUX_3` is a compact and specialized function block for selecting one of three AB adapter inputs. It is particularly suitable for applications requiring reliable switching between different adapter sources without the need for additional data conversion.
