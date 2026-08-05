# AX_E_SWITCH
![AX_E_SWITCH](./AX_E_SWITCH.svg)

* * * * * * * * * *
## Introduction
The **AX_E_SWITCH** function block implements event-driven demultiplexing (switching) based on a Boolean signal. It receives an event at input **EI** and forwards it to either output **EO0** or **EO1**, depending on the value of adapter **G**. This allows event flows to be split based on states or decisions.
---
## Interface Structure

### **Event Inputs**

| Name | Type | Description |

|-------------|--------|-------------------------------|

| **EI** | Event | Event input that is switched |

### **Event Outputs**

| Name | Type | Description |

|-------------|--------|--------------------------------------------|

| **EO0** | Event | Activated when **G** = 0 |

| **EO1** | Event | Activated when **G** = 1 |

### **Data Inputs**
This function block has no separate data inputs. The switching information is provided via the **G** adapter.

### **Data Outputs**
No data outputs are available.

### **Adapter**

| Name | Type | Description |

|-------------|-----------------------------------|---------------------------------------------------------------------------|

| **G** | `adapter::types::unidirectional::AX` | Boolean interface; provides the value for switching (0 → EO0, 1 → EO1) |

---

## Functionality
The **AX_E_SWITCH** is implemented internally as an encapsulation of the standard function block **E_SWITCH**. An incoming event at **EI** is forwarded to the internal function block. The adapter **G** provides the Boolean value (via the data connection `G.D1` → `E_SWITCH.G`).

- If **G = 0**, the event is output to **EO0**.
- If **G = 1**, the event is output to **EO1**.

The function block operates deterministically and without internal state management; the switching occurs in a single execution step.

--

## Technical Features
- **Adapter Interface:** The Boolean switching value is not provided as a classic data input, but via an adapter. This enables loose coupling and reuse of standardized interfaces (type `unidirectional::AX`).
- **Reusability:** Internally, the IEC 61499 standard function block `E_SWITCH` is used, ensuring compatibility and easy traceability.
- **No Side Effects:** The function block is purely component-based and does not modify any global data or states.

---

## State Overview
The **AX_E_SWITCH** does not have its own explicit state machine. Its behavior is purely event-driven and does not differ from a simple switch. Therefore, a state overview is not required.

---

## Application Scenarios
- **Event Switch in Control Logic:** Splitting an event stream into two paths, e.g., depending on a sensor value or operating mode.
- **Quality Control:** Forwarding an event to different processing blocks depending on the test result (pass/fail).
- **Operating Mode Switching:** Controlling processes that react differently in normal or fault mode.

---

## Comparison with Similar Function Blocks
- **Standard function block `E_SWITCH`:** Has a direct Boolean data input instead of an adapter. The **AX_E_SWITCH** encapsulates this input and offers an adapter-based interface, which is preferred in modular architectures.
- **`E_DEMUX` (comparable function):** Some libraries also offer demultiplexers, but usually with multiple outputs or without adapter connectivity. The **AX_E_SWITCH** focuses on the special case of dual outputs with an adapter.

---

## Conclusion
The **AX_E_SWITCH** is a simple yet useful function block for event-based switching. Its adapter interface allows it to be seamlessly integrated into component-oriented control projects and enables a clean separation of event logic and decision data. It is particularly suitable for modular and reusable automation solutions.
