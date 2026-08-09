# AR_MUX_2

![AR_MUX_2](./AR_MUX_2.svg)

* * * * * * * * * *
## Introduction

The **AR_MUX_2** is a generic 2-to-1 multiplexer (MUX) that operates via adapter interfaces (type `AR`, unidirectional). It selects one of two adapter inputs (`IN1`, `IN2`) based on an index value `K` and forwards its signal to the adapter output `OUT`. The function block is controlled by the event `REQ` and acknowledges the selection with `CNF`.
## Interface Structure

### **Event Inputs**

| Event | Comment |
|----------|-------------------------------------------|
| `REQ` | Triggers the selection of index `K` |

### **Event Outputs**

| Event | Comment |
|----------|-------------------------------------------|
| `CNF` | Confirms successful switching |

### **Data Inputs**

| Name | Type | Comment |
|------|--------|--------------------|
| `K` | `UINT` | Index (0 → IN1, 1 → IN2) |

### **Data Outputs**

*(none)*

### **Adapter**

| Direction | Name | Type | Comment |
|----------|------|---------------------------------------|-----------------------------------|
| **Plug** (Output) | `OUT` | `adapter::types::unidirectional::AR` | Output signal (as selected) |
| **Socket** (Input) | `IN1` | `adapter::types::unidirectional::AR` | Input value for `K = 0` |
| **Socket** (Input) | `IN2` | `adapter::types::unidirectional::AR` | Input value for `K = 1` |

## Functionality

1. The function block waits for a `REQ` event.
2. Upon arrival of `REQ`, the current value of index `K` is evaluated:
- `K = 0` → The signal from adapter `IN1` is passed through to adapter `OUT`.
- `K = 1` → The signal from adapter `IN2` is passed through to adapter `OUT`.
- *(For other values of `K`, the behavior is undefined; in the context of a 2-to-1 MUX, only 0 or 1 makes sense.)*
3. After the pass-through, the event `CNF` is sent to signal the successful selection.

## Technical Features

- **Generic Implementation:** The component is declared as a generic type (`GenericClassName = 'GEN_AR_MUX'`), which allows for flexible instantiation in different contexts.
- **Adapter-based communication:** All signals (inputs and outputs) are transmitted via the unidirectional adapter type `AR` – typical for applications requiring loose coupling between devices.
- **No data outputs:** This selection applies exclusively to the adapter interface; no numeric or Boolean data outputs are used.
- **Standard compliance:** The device complies with the IEC 61499-2 standard and can be used as part of an ECLIPSE 4diac project.

## State overview

The device does not have an explicit ECC algorithm but operates in an event-driven manner. An implicit state machine can be assumed:

- **IDLE:** Waiting for a `REQ` event.
- **PROCESSING:** Evaluate `K` and switch the corresponding adapter input to `OUT`.
- **DONE:** Send `CNF` and return to the IDLE state.

## Application Scenarios

- **Signal Channel Switching:** Selection between two different sensor or actuator signals in a control application.
- **Configurable Data Paths:** Dynamic selection of different data sources, e.g., in agricultural machinery control (copyright notice indicates application in agricultural technology).
- **Redundancy Management:** Switch to a backup input if the primary signal fails.

## Comparison with Similar Function Blocks

| Function Block | Number of Inputs | Properties |
|------------|-----------------|---------------------------------------------------------|
| `AR_MUX_2` | 2 | Simple 2-to-1 MUX, adapter-based, one index `K` |
| `AR_MUX_4` | 4 | Extended version with four inputs and a 2-bit index |
| `SEL` (Standard) | 2 (Bool) | Standard IEC selector block, operates with Boolean signals |

The `AR_MUX_2` is specifically optimized for use with unidirectional AR adapters and offers a clear, event-driven interface, unlike general selectors.

## Conclusion

The AR_MUX_2 is a compact, generic multiplexer for adapter signals that enables reliable and fast switching between two inputs. Its event-driven operation and standards-compliant interface make it a useful component in modular automation solutions, especially in agricultural technology.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
