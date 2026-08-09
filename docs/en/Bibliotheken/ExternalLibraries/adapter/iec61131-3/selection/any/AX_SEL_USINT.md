# AX_SEL_USINT

![AX_SEL_USINT](./AX_SEL_USINT.svg)

* * * * * * * * * *
## Introduction

The function block `AX_SEL_USINT` is used for binary selection (multiplexing) between two input values of the data type `USINT` (Unsigned Short Integer). Which of the two inputs is passed through to the output is controlled by a specialized coupling adapter (`G`). The block is based on the selection concepts of the IEC 61131-3 standard (SEL function) and is optimized for use in distributed control systems according to IEC 61499.

## Interface Structure

### **Event Inputs**

| Event | Description | Associated Data |
| :--- | :--- | :--- |
| **EI0** | Updates and adopts the value at input `IN0` | `IN0` |
**EI1** | Updates and adopts the value at input `IN1` | `IN1` |

### **Event Outputs**

| Event | Description | Associated Data |
| :--- | :--- | :--- |
**CNF** | Acknowledge event. Signals that a newly selected value is available at the output. | `OUT` |

### **Data Inputs**

| Variable | Data Type | Description |
| :--- | :--- | :--- |
**IN0** | USINT | First selectable input value (selected if the selector is `FALSE`). |
| **IN1** | USINT | Second selectable input value (selected if the selector is `TRUE`). |

### **Data Outputs**

| Variable | Data Type | Description |
| :--- | :--- | :--- |
| **OUT** | USINT | The currently selected output value. |

### **Adapter**

| Socket | Adapter Type | Description |
| :--- | :--- | :--- |
| **G** | `adapter::types::unidirectional::AX` | Unidirectional adapter that provides the selection signal (`G.D1`) and the associated trigger event (`G.E1`). |

---

## Functionality

The `AX_SEL_USINT` module encapsulates an internal network of event and selection modules:

1. **Data Acquisition:** The analog input values `IN0` and `IN1` are temporarily stored via edge-triggered flip-flops (`E_D_FF_ANY`) upon the arrival of the respective events `EI0` and `EI1`, respectively.
2. **Selection via Adapter:** The control signal for selection is fed in via the adapter `G`. As soon as the event `G.E1` is present at the adapter, an internal D flip-flop takes over the state of the data channel `G.D1`.
3. **Selection Process:** The internal core component `F_SEL` switches based on the state of the selector:
- If the state of `G` is **FALSE** (0), the value of `IN0` is passed to the output `OUT`.
- If the state of `G` is **TRUE** (1), the value of `IN1` is forwarded to output `OUT`.
4. **Event Generation:** An output event at output `CNF` is primarily generated when the state of selector `G` changes or the resulting output value modifies.

--

## Technical Features

- **Event Filtering:** The internal use of `E_D_FF_ANY` blocks at the output ensures efficient control of the acknowledgment event `CNF`. An output event is specifically generated when the state of selection adapter `G` changes.
- **Adapter Coupling:** Outsourcing the selection signal to an adapter drastically reduces the wiring effort in the higher-level function block diagram (FB network) and increases modularity.

---

## State Overview

| Selector State (G.D1) | Enabled Input | Output Value (OUT) |
| :---: | :---: | :---: |
| **FALSE** | IN0 | Value of `IN0` |
| **TRUE** | IN1 | Value of `IN1` |

---

## Application Scenarios

- **Setpoint Switching:** Dynamic switching between two different target values (e.g., standby value vs. operating value) in a machine control system.
- **Manual/Automatic Switching:** Signal routing where, in manual mode, a manually specified `USINT` value is passed to a controller, and in automatic mode, a calculated value is passed.
- **Recipe Control:** Selection between two predefined configuration parameters via a central control signal.

---

## Comparison with Similar Function Blocks

- **Standard SEL Function Block (IEC 61131-3):** The classic `SEL` function block requires discrete hardware pins for the selection signal and does not have integrated event control for distributed systems. `AX_SEL_USINT` elegantly solves this via the `G` adapter and IEC 61499 event connections.

**AX_SEL Variants for Other Data Types:** Analogous function blocks exist for types such as `INT` or `REAL`. `AX_SEL_USINT` is specifically optimized for the unsigned 8-bit data type (`USINT`) to maintain memory space and data type consistency across the network.

---

## Conclusion

The `AX_SEL_USINT` is a reliable and highly modular auxiliary function block for signal flow control in IEC 61499 applications. By using the `AX` adapter, it integrates seamlessly into modern, event-driven control architectures and ensures a clean separation of control logic and data paths.