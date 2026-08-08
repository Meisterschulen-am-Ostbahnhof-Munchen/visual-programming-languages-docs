# AB_BYTE_AX_SEL_AB

![AB_BYTE_AX_SEL_AB](./AB_BYTE_AX_SEL_AB.svg)

* * * * * * * * * *
## Introduction

The function block `AB_BYTE_AX_SEL_AB` is a binary selector (multiplexer) for data of type `BYTE` in the IEC 61499 standard. It enables selection between two byte input signals based on a logical selector signal. The block uses standardized, unidirectional adapter connections to encapsulate data and events, contributing to a clean and modular design within the 4diac-ide.

## Interface Structure

### **Event Inputs**

| Event | Description | Associated Data |

| :--- | :--- | :--- |

| `EI1` | Sets or updates the value of the direct data input `IN1` | `IN1` |

### **Event Outputs**

*This function block does not have direct event outputs at the main level. Event output is encapsulated via the output adapter `OUT`.*

### **Data Inputs**

| Data Point | Data Type | Description |

| :--- | :--- | :--- |

| `IN1` | `BYTE` | Selectable input variable (Channel 1) |

### **Data Outputs**

*This function block does not have direct data outputs at the main level. Data output is encapsulated via the output adapter `OUT`.*

### **Adapter**

| Adapter Name | Type | Direction | Description |

| :--- | :--- | :--- | :--- |

| `OUT` | `adapter::types::unidirectional::AB` | Plug | The selected output (transmits the selected `BYTE` and the associated event). |

| `IN0` | `adapter::types::unidirectional::AB` | Socket | Selectable input variable (channel 0) via adapter. |

| `G` | `adapter::types::unidirectional::AX` | Socket | Selector/Gate via adapter. |

*Note: `AB` represents an adapter for transmitting a `BYTE` value, while `AX` is responsible for transmitting a Boolean state (`BOOL`/bit).*

---

## Functionality

The component operates internally as an event-driven multiplexer. The selection of the value to be passed to `OUT` is based on the logical state of the adapter `G` (selector):

1. **Buffering & Synchronization:**

* The input signals from `IN0` (adapter), `IN1` (direct input via `EI1`), and the selector `G` (adapter) are buffered internally using D flip-flops (`E_D_FF_ANY` and `E_D_FF`, respectively) upon the occurrence of the respective event.


* 2. **Selection Logic (F_SEL):**

* If the selection signal `G.D1` has the state **`FALSE`** (0), the value of `IN0` (channel 0) is passed to the output.

* If the selection signal `G.D1` has the state **`TRUE`** (1), the value of `IN1` (channel 1) is passed to the output.

3. **Output:**

* As soon as an input value or the selection signal changes, the internal function block `F_SEL` calculates the new output value. This is output via the adapter `OUT`, simultaneously triggering an output event (`OUT.E1`).

---

## Technical Features

* **Adapter-based Architecture:** The use of plugs and sockets drastically reduces the number of visible connection lines in the higher-level system, improving the clarity of complex applications.

* **Event Control:** Internal processing reacts flexibly to events from various sources (both direct events like `EI1` and adapter events from `IN0` and `G`).

* **Type Conversion and Protection:** Secure data transfer is ensured through the use of internal move blocks (`F_MOVE`).

---

## Status Overview

| State Selector `G` | Active Input | Value at `OUT` | Triggered Event at `OUT` |

:--- | :--- | :--- | :--- |

`FALSE` | `IN0` | `IN0.D1` | Yes (on value change or trigger from `IN0.E1`/`G.E1`) |

`TRUE` | `IN1` | `IN1` | Yes (upon value change or trigger of `EI1`/`G.E1`) |

---

## Application Scenarios

* **Operating Mode Switching:** Switching between a standard setpoint (e.g., automatic mode via `IN0`) and a manually specified byte value (e.g., manual operation via `IN1`).

* **Error Value Feedforward:** In normal operation, the sensor value of a byte channel (`IN0`) is passed through. Upon detection of an error, the selector `G` switches to a safe substitute value (`IN1`).

* * **Signal Routing in Bus Systems:** Dynamic routing of status or control bytes within distributed control architectures.

---

## Comparison with Similar Components

Compared to the standard IEC 61131-3 component `SEL`, this component offers direct integration into the event-driven world of IEC 61499. While the classic `SEL` component requires continuous cyclic calls and discrete wiring, `AB_BYTE_AX_SEL_AB` operates purely on an event-driven basis and utilizes the advantageous adapter concept for encapsulating signal paths.

---

## Conclusion

The `AB_BYTE_AX_SEL_AB` component is a robust, reusable, and well-structured solution for binary signal selection of byte values. Through the consistent use of adapters, it integrates perfectly into modern, service-oriented control applications and contributes to the clarity of 4diac application programs.