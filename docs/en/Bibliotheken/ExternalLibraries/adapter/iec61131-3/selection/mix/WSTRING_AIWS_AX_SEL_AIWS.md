# WSTRING_AIWS_AX_SEL_AIWS

![WSTRING_AIWS_AX_SEL_AIWS](./WSTRING_AIWS_AX_SEL_AIWS.svg)

**********


The function block `WSTRING_AIWS_AX_SEL_AIWS` is a composite function block for IEC 61499 systems. Its main function is binary multiplexing between two string inputs (WSTRING). Based on a logical selection signal, it allows either a directly applied string or a signal received via an adapter to be forwarded to an output adapter.

Thanks to the use of adapters, this function block can be seamlessly integrated into modern, service-oriented control architectures within the 4diac IDE.



| Event | Description | Linked Data |

| :--- | :--- | :--- |

| `EI0` | Triggers the acquisition and processing of the data input `IN0`. | `IN0` |


*There are no direct event outputs at the block level. Event forwarding is coupled via the output adapter `OUT`.*


| Data Point | Data Type | Description |

| :--- | :--- | :--- |

| `IN0` | `WSTRING` | Directly connected, selectable string input. |


*There are no direct data outputs at the block level. Data forwarding occurs via the output adapter `OUT`.*

### Data Outputs
### Data Inputs
### Event Outputs
### Event Inputs
## Interface Structure
## Introduction
### **Adapter**

| Adapter Name | Type | Direction (Plug/Socket) | Description |

| :--- | :--- | :--- | :--- |

| `OUT` | `adapter::types::unidirectional::AIWS` | Plug | The selected output (string and event output). |

| `IN1` | `adapter::types::unidirectional::AIWS` | Socket | The second selectable input (as an adapter). |

| `G` | `adapter::types::unidirectional::AX` | Socket | The selector input. Controls which signal is passed through. |

## Functionality

The function block's internal network connects the adapter's event and data streams to classic IEC 61131 selection and copy functions (`F_SEL`, `F_MOVE`).

1. **Input Channel 0 (`IN0`):** An event at `EI0` buffers the value of `IN0` via the flip-flop `E_D_FF_ANY_IN0` and writes it via `F_MOVE_IN0` to the selector `F_SEL` (input `IN0`).


 2. **Input Channel 1 (`IN1`):** An incoming event at adapter `IN1.E1` buffers the data `IN1.D1` via the flip-flop `E_D_FF_ANY_IN1` and writes it via `F_MOVE_IN1` to the selector `F_SEL` (input `IN1`).


**Input Channel 1 (`IN1`):** 3. **Selection Signal (`G`):** An event at the selector adapter `G.E1` takes the state of `G.D1` (Boolean) via the flip-flop `E_D_FF_G` and applies it to the control input `G` of `F_SEL`.

4. **Selection Process (`F_SEL`):**

* If the selection signal `G` is **FALSE**, the value of `IN0` is passed to the output.


* * If the selection signal `G` is **TRUE**, the value of `IN1` is passed to the output.

5. **Output (`OUT`):** Any change or activation at the inputs triggers an update at the selection element. The result is copied using `F_MOVE_OUT`, stabilized via `E_D_FF_ANY_OUT`, and provided as event `OUT.E1` with the data `OUT.D1` at the output adapter.


5. **Output (`OUT`):** Any change or activation at the inputs results in an update at the selection element. The result is copied using `F_MOVE_OUT`, stabilized via `E_D_FF_ANY_OUT`, and made available as event `OUT.E1` with the data `OUT.D1`.```
                  +-------------------------+
                  |  WSTRING_AIWS_AX_SEL_AIWS|
                  |                         |
      [IN0] ----->|---\                     |
   (WSTRING)      |    \   +-----------+    |
                  |     -->|   F_SEL   |    |
   [IN1.D1] ----->|------->|           |    |
    (AIWS)        |        |           |--->|-----> [OUT.D1]
                  |     -->|           |    |       (AIWS)
    [G.D1] ------>|----/   +-----------+    |
     (AX)         |                         |
                  +-------------------------+


* **Data Type Consistency:** The function block is internally parameterized for the data type `WSTRING` (Wide Character String). This also allows the processing of Unicode strings.

* **Event-Driven Latch Behavior:** The use of event D flip-flops (`E_D_FF_ANY` and `E_D_FF`) ensures that the data is only updated when a corresponding trigger input event occurs. This prevents uncontrolled data changes ("race conditions").

* **Unidirectional Adapters:** The interface adapters used (`AIWS` and `AX`) operate purely unidirectionally, which keeps the data flow clear and deterministic.


* ## State Overview

Since this is a Composite Function Block (CFB) without its own internal Execution Control Chart (ECC), its behavior is directly determined by the interaction of its internal components:

* **Inactive / Idle State:** No events are present at the inputs. The outputs retain their last stable values.

* **Input Update 0:** `EI0` triggers -> `IN0` is reread -> `F_SEL` is recalculated -> If `G` = `FALSE`, the output is updated and `OUT.E1` is fired.

* **Input Update 1:** `IN1.E1` triggers -> `IN1.D1` is reread -> `F_SEL` is recalculated -> If `G` = `TRUE`, the output is updated and `OUT.E1` is fired.

* **Switching:** `G.E1` triggers -> Selector state changes -> `F_SEL` switches the corresponding path -> The output is updated with the newly selected value and `OUT.E1` is fired.



* **Dynamic Text and Speech Switching:** Switching between user interface texts or system messages from a default value (`IN0`) and a dynamically received text resource (`IN1`).

* **Error and Status Message Selection:** Selecting a specific status message when an alarm is pending (controlled by the selection signal `G`).

* **Signal Multiplexing in Adapter Structures:** Integration into modularized plant control systems where data streams are bundled and flexibly routed using adapters.


* ## Comparison with Similar Components

* **Standard `F_SEL` (IEC 61131-3):** The classic `F_SEL` operates purely data-driven and has no integrated event control or adapter compatibility. `WSTRING_AIWS_AX_SEL_AIWS` extends this functionality with the event interface required by IEC 61499 and packages the signals in standardized adapters.

* **Type-Independent Selectors:** Compared to generic selection components, this component is type-safe and ready for immediate use due to the hardwiring of `WSTRING` types and specific adapters (`AIWS`, `AX`), without requiring any data type assignments.


* **Type-Independent Selectors:** ## Conclusion

The `WSTRING_AIWS_AX_SEL_AIWS` function block offers a robust and ready-to-use solution for signal- and event-driven selection of wide-character strings. By encapsulating complex flip-flop and conversion logic, it simplifies the design of clear and maintainable control applications in the 4diac IDE.
## Technical Features
## State Overview
## Application Scenarios
## Comparison with Similar Function Blocks
## Conclusion