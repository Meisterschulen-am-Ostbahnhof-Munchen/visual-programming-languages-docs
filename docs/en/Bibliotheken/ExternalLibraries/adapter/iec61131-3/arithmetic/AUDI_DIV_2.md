# AUDI_DIV_2

![AUDI_DIV_2](./AUDI_DIV_2.svg)

* * * * * * * * * *
## Introduction

The function block (FB) **AUDI_DIV_2** is used to perform arithmetic division. It is a generic function block (`GEN_AUDI_DIV`) that can flexibly work with various data types within the adapter structure. Unlike classic mathematical function blocks, which have dedicated data inputs, this block uses adapter connections to encapsulate signals and control flows.

## Interface Structure

The function block does not have any direct, classic event or data inputs on its surface. All communication is handled via adapters.

         +---------------------------------------+
|              AUDI_DIV_2               |
|                                       |
  [IN1] =|======================================>|=[OUT]
| (unidirectional::AUDI)  (unidirect..) |
[IN2] =|======================================>|
| (unidirectional::AUDI)                |

### **Event Inputs**

*No direct event inputs are available. Event control is handled via the adapters.*

### **Event Outputs**

*No direct event outputs are available. Event control is handled via the adapters.*

### **Data Inputs**

*No direct data inputs are available.*

### **Data Outputs**

*No direct data outputs are available.*

### **Adapters**

| Type | Name | Adapter Type | Description |
| :--- | :--- | :--- | :--- |
| **Socket** (Female) | `IN1` | `adapter::types::unidirectional::AUDI` | First input value for division (dividend). |
| **Socket** (Female) | `IN2` | `adapter::types::unidirectional::AUDI` | Second input value for the division (divisor). |
| **Plug** (connector) | `OUT` | `adapter::types::unidirectional::AUDI` | Result of the division (quotient). |

---

## Functionality

The function block calculates the quotient of the values provided via the adapters `IN1` and `IN2`:

$$\text{OUT} = \frac{\text{IN1}}{\text{IN2}}$$

Since the interfaces are implemented as unidirectional `AUDI` adapters, an update of the input values at `IN1` or `IN2` (via the event channels integrated into the adapter) triggers the calculation in the function block. The result is then immediately signaled via the event encapsulated in the `OUT` adapter and passed on to subsequent function blocks.

---

## Technical Features

* **Generic Type:** The function block is declared as `GEN_AUDI_DIV` via the attribute `eclipse4diac::core::GenericClassName`. This enables automatic type adaptation to the specific data structures used within the `AUDI` adapters.
* **Clean Wiring:** Encapsulating data and event signals in adapters minimizes the visual "spaghetti code" problem in 4diac-ide.
* **Error Handling (Division by Zero):** Since this is a generic division, the underlying runtime environment (e.g., forte) catches division by zero to prevent the controller from crashing. In such a case, the output is typically set to a default value (e.g., `0` or `NaN`/`Infinity`, depending on the data type).

---

## State Overview

Execution follows a simple, event-driven pattern:

[Ereignis an IN1 oder IN2]
          │
          ▼
┌────────────────────────────────────────┐
│ Werte aus IN1 und IN2 einlesen         │
└────────────────────────────────────────┘
          │
          ▼
│ Ist IN2 == 0?                          │
└──────────────────┬─────────────────────┘
                   │
         ┌─────────┴─────────┐
      JA │                NEIN
         ▼                   ▼
┌──────────────────┐ ┌───────────────────┐
│ Fehlerbehandlung │ │ OUT = IN1 / IN2   │
│ (z.B. OUT = 0)   │ └───────────────────┘
└────────┬─────────┘         │
         │                   │
         └─────────┬─────────┘
                   │
                   ▼
│ Aktualisiere Daten im OUT-Adapter      │
          │
          ▼
[Sende Aktualisierungs-Event über OUT]

---

## Application Scenarios

* **Scaling and Normalization Tasks:** Division of measured values transmitted in standardized `AUDI` data structures.
* **Ratio Calculations:** Determining ratios in the process industry (e.g., flow ratios of two media).
* **Signal Processing:** Modular use in control architectures where strict separation through adapter structures is required.

---

## Comparison with Similar Components

| Component Type | Interface Type | Wiring Effort | Flexibility |
| :--- | :--- | :--- | :--- |
| **Standard `DIV`** | Individual Pins (REQ, IN1, IN2, OUT, CNF) | High (many lines) | Low (fixed data types per instance) |
| **`AUDI_DIV_2`** | Adapter (`IN1`, `IN2`, `OUT`) | Very low | High (generic adaptation via adapter) |

---

## Change Detection

The result is only written to the output plug (`OUT`) and its adapter event only sent if the newly computed value differs from the value currently held on `OUT`. If the result is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.


## Conclusion

The `AUDI_DIV_2` is a modern, adapter-based function block for IEC 61499. It is ideally suited for complex projects in the 4diac-ide where clarity, encapsulation, and easy maintainability of the application diagram are paramount.