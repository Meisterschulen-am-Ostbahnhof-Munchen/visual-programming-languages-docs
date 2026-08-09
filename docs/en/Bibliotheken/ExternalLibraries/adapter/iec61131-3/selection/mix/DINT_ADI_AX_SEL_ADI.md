# DINT_ADI_AX_SEL_ADI

![DINT_ADI_AX_SEL_ADI](./DINT_ADI_AX_SEL_ADI.svg)

* * * * * * * * * *
## Introduction

The function block `DINT_ADI_AX_SEL_ADI` serves as a binary selector (multiplexer) for `DINT` (double integer) data structures within an IEC 61499 network. It enables dynamic selection between a local data input (`IN0`) and a signal fed in via an adapter (`IN1`) based on the state of a selector adapter (`G`). The selected signal is then passed to an output adapter (`OUT`).

 This module is particularly suitable for modular control architectures where signals need to be routed flexibly and event-driven via standardized adapter interfaces.

## Interface Structure

### **Event Inputs**

| Name | Type | Description |
| :--- | :--- | :--- |
| **EI0** | Event | Signals the update of the local data input `IN0`. |

### **Event Outputs**

*This module does not have direct event outputs on the main interface. Events are only output via the output adapter (`OUT.E1`).*

### **Data Inputs**

| Name | Type | Description |
| :--- | :--- | :--- |
| **IN0** | DINT | Selectable local data input (double integer). |

### **Data Outputs**

*This function block does not have direct data outputs on the main interface. Data is transmitted exclusively via the output adapter (`OUT.D1`).*

### **Adapter**

| Name | Direction | Type | Description |
| :--- | :--- | :--- | :--- |
| **OUT** | Plug | `adapter::types::unidirectional::ADI` | The selected output (contains data `D1` and the associated event `E1`). |
| **IN1** | Socket | `adapter::types::unidirectional::ADI` | Selectable adapter input (provides data `D1` and event `E1`). |
**G** | Socket | `adapter::types::unidirectional::AX` | Selector adapter for controlling selection (provides selection signal `D1` and event `E1`). |

 ## Functionality

The module's internal network combines classic IEC 61131-3 selection logic (`F_SEL`) with event-driven processing according to IEC 61499.

1. **Data Storage and Synchronization:**
* When an event arrives at one of the inputs (`EI0`, `IN1.E1`, or `G.E1`), the corresponding value (`IN0`, `IN1.D1`, or `G.D1`) is temporarily stored using internal D flip-flops (`E_D_FF` / `E_D_FF_ANY`).
* An internal data move (`F_MOVE_IN0` / `F_MOVE_IN1`) ensures that the values are passed consistently to the actual selector.
2. **Selection Logic:**
* The internal function block `F_SEL` evaluates the signal from selector `G.D1`:
* If `G.D1` is **FALSE (0)**, the value of `IN0` is selected.
* If `G.D1` is **TRUE (1)**, the value of `IN1.D1` is selected.
3. **Output:**
* The selected value is passed to the output adapter `OUT`.
* Simultaneously, the event `OUT.E1` is triggered to inform subsequent program components about the data change.

## Technical Features

* **Hybrid Interface:** This function block bridges the gap between classic direct data connection (`IN0` as a direct input to `DINT`) and modern adapter-based communication (`IN1` and `OUT`).
* * **Data Consistency:** The use of internal edge and memory blocks (`E_D_FF_ANY`, `F_MOVE`) ensures that no data is lost or inconsistent intermediate states are passed on, even with asynchronously arriving events.

## State Overview

| Selector State (`G.D1`) | Active Channel | Output Value (`OUT.D1`) | Triggering Event at Output (`OUT.E1`) |
| :---: | :---: | :---: | :---: |
| **FALSE** | `IN0` | Value of `IN0` | On every event on `EI0` or `G.E1` |
| **TRUE** | `IN1` | Value of `IN1.D1` | On every event on `IN1.E1` or `G.E1` |

## Application Scenarios

* **Setpoint Switching:** Switching between a manually specified default value (via the local input `IN0`) and an automatically calculated value supplied via an adapter network (`IN1`).

**TRUE** * **Signal Bypass:** Implementation of test or bridging functions where the adapter path is used during normal operation, but a safe replacement value on `IN0` can be used in case of an error.

* **Modular Machine Control:** Coupling of subsystems where the control interfaces are coupled via standardized `ADI` and `AX` adapters.

## Comparison with Similar Function Blocks

* **Standard `F_SEL`:** The standard selection block operates purely data-oriented and has no integrated event control or adapter compatibility. `DINT_ADI_AX_SEL_ADI` encapsulates this logic and makes it directly available for modern, adapter-based applications.
* **Pure Adapter Multiplexer:** Unlike multiplexers that only switch adapters, this component allows the direct input of a local `DINT` value without the overhead of an additional input adapter.

## Conclusion

The `DINT_ADI_AX_SEL_ADI` is a robust and versatile auxiliary component. It significantly simplifies signal routing in complex IEC 61499 systems by implementing event-driven selection directly at the adapter level while simultaneously guaranteeing high data integrity.