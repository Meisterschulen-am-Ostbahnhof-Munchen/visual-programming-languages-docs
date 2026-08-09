# ADI_TO_AX

![ADI_TO_AX](./ADI_TO_AX.svg)

* * * * * * * * * *
## Introduction

The **ADI_TO_AX** function block is a composite module that performs a simple signal conversion between two adapter types. It converts a DINT value (type: *adapter::types::unidirectional::ADI*) received via the **ADI_IN** socket into a BOOL value and outputs it via the **AX_OUT** plug (type: *adapter::types::unidirectional::AX*). The conversion is performed by comparing the received DINT value with the constant value 0. If the value is not equal to 0, the BOOL output is set to TRUE; if they are equal, it is set to FALSE. This module is particularly suitable for connecting digital signal sources encoded as integers to Boolean interfaces.
## Interface Structure

### **Event Inputs**

| Name | Description |
|---|---|
| (No explicit event inputs)* | The function block (FB) uses only the events connected via the ADI_IN adapter. In fact, the event `E1` of the ADI_IN adapter is internally forwarded to the function block `F_NE`. |

### **Event Outputs**

| Name | Description |
|---|---|
| (No explicit event outputs)* | The output is via the AX_OUT adapter; the event `E1` of the AX_OUT adapter is sent after successful processing of the `F_NE` call. |

### **Data Inputs**

| Name | Type | Description |
|---|---|---|
| *(via ADI_IN adapter)* | `DINT` | The DINT value (e.g., measured value or status code) connected via the adapter socket is received as input `D1` of the ADI_IN adapter. |

### **Data Outputs**

| Name | Type | Description |
|---|---|---|
| *(via AX_OUT adapter)* | `BOOL` | The output value is provided as `D1` of the AX_OUT adapter. TRUE if the received DINT value is not 0; otherwise FALSE. |

### **Adapter**

| Adapter | Name | Direction | Type | Description |
|---|---|---|---|---|
| Socket | ADI_IN | Input | `adapter::types::unidirectional::ADI` | Receives a DINT value (with associated event). |
| Plug | AX_OUT | Output | `adapter::types::unidirectional::AX` | Passes on the resulting BOOL value (with associated event). |

## Functionality

Internally, the function block consists of a single function block **F_NE** of type `iec61131::comparison::F_NE`. This implements the IEC 61131 function "Not Equal" (NE). Behavior:

1. An incoming event **E1** from the ADI_IN adapter is forwarded to the **REQ** input of **F_NE**.

`` 2. The data value **D1** of the ADI_IN adapter is applied to the **IN1** input of the **F_NE**. The second comparison value, **IN2**, is fixed to the value `DINT#0`.

3. The **F_NE** compares `IN1 != IN2`. The result (BOOL) is output at the **OUT** output.
4. After processing is complete, **F_NE.CNF** signals completion. This event is sent to the **E1** input of the AX_OUT adapter, which then passes the output value (also the **OUT** signal) to **D1** of the AX_OUT adapter.

Thus, the function block implements a simple threshold logic: Any non-zero DINT value is interpreted as logically "true". The function block operates strictly event-driven – each incoming event triggers exactly one comparison and output action.

## Technical Features

- **Adapter Coupling:** The function block is designed as a composite block that connects two unidirectional adapters. It can therefore be seamlessly integrated into an adapter-based communication architecture.
- **No Internal States:** Since the function block has no internal state variables or timers, its behavior is purely combinatorial and deterministic.
- **Direct Impedance:** The function block used, `F_NE` from the IEC 61131 library, is high-performance and does not require dynamic memory management.
- **Type Safety:** The constant `DINT#0` is explicitly declared as a DINT, so no implicit type conversions occur.
- **License Notice:** This function block is subject to the Eclipse Public License 2.0 (EPL-2.0), Copyright 2026 HR Agrartechnik GmbH.

## State Overview

This function block has no states of its own, as it is entirely based on the internal functional block **F_NE**. Therefore, its behavior requires no delays or storage. The sequence is as follows:

- **Waiting for Event:** Inactive until an event arrives via the ADI_IN adapter.
- **Processing:** Upon receiving an event, the comparison is performed; the output is updated immediately. After the comparison, the output event is sent.

## Application Scenarios

- **Digitization of Analog Values:** In automation, DINT values (e.g., counter readings, error codes) are often interpreted as Boolean signals. This function block is suitable for converting non-zero conditions into binary signals.
- **Adapter Bridging:** If a component only provides an ADI adapter, but the downstream logic only accepts AX adapters, this function block can be used as a lossless converter.
- **Simple Switching Thresholds:** With minimal effort, it's possible to determine whether a value deviates from zero – useful, for example, for monitoring counting pulses or limit violations.

## Comparison with Similar Function Blocks

| Function Block | Type | Function |
|---|---|---|
| **ADI_TO_AX** (this function block) | Composite | DINT ≠ 0 → BOOL |
| `BOOL_TO_DINT` (Standard Library) | Function | Direct conversion from BOOL to DINT (e.g., TRUE → 1) |
| `F_NE` (IEC 61131) | Function | General Non-Equal Comparison of Arbitrary Data Types |
**Custom Adapter Converter** | – | Can be easily extended with other comparison functions (F_EQ, F_GT, etc.) |

Compared to a pure BOOL-to-DINT conversion, **ADI_TO_AX** offers the advantage that the DINT value is retained exactly (e.g., 42 → TRUE), whereas a Boolean conversion can only distinguish between TRUE/FALSE and 1/0.

## Conclusion

The **ADI_TO_AX** function block is a lean and robust adapter converter for unidirectional interfaces. It utilizes the proven IEC 61131 comparison block `F_NE` and thus implements a simple yet useful logic: "Any non-zero value is true." The function block is particularly suitable for use in modular automation systems where different adapter standards need to be coordinated. Thanks to its composite structure, it can be easily integrated into existing networks and expanded as needed.
