# AUS_MUX_3

![AUS_MUX_3](./AUS_MUX_3.svg)

* * * * * * * * * *
The function block **AUS_MUX_3** is a generic multiplexer for the unidirectional OFF adapter. It selects one of three identical adapter inputs (`IN1`, `IN2`, `IN3`) based on an index `OUT` and forwards its value to the adapter output `OUT`. The selection is event-driven via the event `REQ`.

| Name | Type | Comment |
|------|-----|-----------|
| `REQ` | Event | Set Index K – triggers multiplexer selection |
| Name | Type | Comment |
|------|-----|-----------|
| `CNF` | Event | Confirmation of successful index selection |
| Name | Type | Comment |
|------|-----|-----------|
| `K` | UINT | Index for selecting the input (0, 1, or 2) |

*None.*

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

| Role | Name | Type | Comment |
|-------|------|-----|-----------|
| Plug | `OUT` | `adapter::types::unidirectional::AUS` | Output adapter that reflects the selected input |
| Socket | `IN1` | `adapter::types::unidirectional::AUS` | First input – passes through at `K = 0` |
| Socket | `IN2` | `adapter::types::unidirectional::AUS` | Second input – passes through at `K = 1` |
| Socket | `IN3` | `adapter::types::unidirectional::AUS` | Third input – is passed through on `K = 2` |

## Functionality

The function block operates in an event-driven manner:

- Upon the arrival of a `REQ` event, the current value of the data input `K` is read.
- Depending on `K`, the corresponding adapter socket is passed through to the plug adapter `OUT`:
- `K = 0` → `IN1` is routed to `OUT`.
- `K = 1` → `IN2` is assigned to `OUT`.
- `K = 2` → `IN3` is assigned to `OUT`.
- After a successful switchover, the event `CNF` is output.
- Values of `K` outside the range 0–2 do not result in a defined passthrough; the behavior is then implementation-dependent (no error handling is provided in the standard).
- The function block is declared as a **generic function block** (`GenericClassName = 'GEN_AUS_MUX'`) and can be replaced by more specific instances in the 4diac IDE.
- All adapter inputs and outputs use the type `adapter::types::unidirectional::AUS`, which enables unidirectional data transmission (e.g., for analog or digital values).
- Selection occurs **immediately** with each `REQ` – there is no internal memory or state machine.

The component **does not have an explicit state machine (ECC)**. It behaves purely event-driven and combinationally: The output `OUT` is directly determined by the current value of `K` as soon as a `REQ` arrives. Once an input is passed through, it remains active until the next `REQ` arrives.

- **Signal Switching**: Selection between three different sensors (e.g., temperature, pressure, humidity) for further processing.
- **Configuration Switching**: Switching between three predefined adapter parameters depending on a control variable.
- **Test and Simulation Environments**: Displaying various test signals on a common interface.
- **MUX_2 / MUX_4**: These function blocks typically operate with two or four inputs and often use direct data ports instead of adapters. AUS_MUX_3 is specifically designed for the **AUS adapter type** and offers clean, adapter-based signal encapsulation.
- **SELECT / SWITCH**: General selection function blocks typically work with simple data types; AUS_MUX_3, on the other hand, transmits entire adapter connections, allowing for a higher level of abstraction.

**SELECT / SWITCH**:** General selection function blocks typically work with simple data types; AUS_MUX_3, however, transmits entire adapter connections, which allows for a higher level of abstraction.

**MUX_2 / MUX_4**:**

The **AUS_MUX_3** is a compact, generic module for adapter multiplexing with three inputs. Thanks to its event-driven control and the use of the unidirectional OFF adapter, it is ideally suited for flexible signal selection in automation solutions where different data sources need to be routed to a common sink. Its generic design facilitates reuse and adaptation in various projects.

---

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de