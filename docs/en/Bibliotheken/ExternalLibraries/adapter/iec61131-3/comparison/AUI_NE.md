# AUI_NE
![AUI_NE](./AUI_NE.svg)
* * * * * * * * * *
## Introduction
The function block `AUI_NE` performs a not equal comparison for two input values. It is built as a composite function block (FB) from the IEC 61131-3 comparison block `F_NE`. Communication with the environment is via standardized adapter interfaces (`AUI` for the inputs, `AX` for the output). This allows it to be seamlessly integrated into adapter-based architectures of the 4diac IDE.
## Interface Structure

### **Event Inputs**

The FB does not have direct event inputs. Events are received via the **socket adapters** `IN1` and `IN2`:

| Adapter | Event | Description |

|---------|----------|--------------|

| `IN1` | Event via adapter input E1 | Starts the comparison when the value is available at `IN1`. |

| `IN2` | Event via adapter input E1 | Starts the comparison when the value is available at `IN2`. |

Both events trigger the activation of the internal `F_NE` module.

### **Event Outputs**

The FB has no direct event outputs. The result is output via the **Plug Adapter** `OUT`:

| Adapter | Event | Description |

|---------|----------|--------------|

| `OUT` | Event via Adapter Output E1 | Indicates that the comparison is complete and the result value is valid. |

### **Data Inputs**

Data is also provided via the socket adapters:

| Adapter | Data Point | Type | Description |

|---------|------------|-----|--------------|

| `IN1` | D1 | ANY (via AUI) | First comparison value |

| `IN2` | D2 | ANY (via AUI) | Second comparison value |

The exact data types are determined by the adapter instance used (`adapter::types::unidirectional::AUI`).

### **Data Outputs**

The result value is output via the plug adapter:

| Adapter | Data Point | Type | Description |

|---------|------------|-----|--------------|

| `OUT` | D1 | BOOL (via AX) | `TRUE`, if IN1 ≠ IN2; `FALSE` other |

### **Adapter**

| Adapter | Direction | Type | Description |

|---------|----------|-----|--------------|

| `IN1` | Socket | `adapter::types::unidirectional::AUI` | Receiver adapter for the first input value. |

| `IN2` | Socket | `adapter::types::unidirectional::AUI` | Receiver adapter for the second input value. |

| `OUT` | Plug | `adapter::types::unidirectional::AX` | Output adapter for the comparison result. |

## Functionality

Each incoming event via `IN1.E1` or `IN2.E1` triggers the internal function block `F_NE` (IEC 61131-3: `NOT EQUAL`). `F_NE` compares the values at data points `IN1.D1` and `IN2.D2`. The result (BOOL) is forwarded to the output adapter `OUT.D1`, and simultaneously an event is sent to `OUT.E1` to signal the result retrieval.

The function block operates **event-driven** – a comparison is only recalculated if at least one of the two input adapters receives an event. This avoids unnecessary processing load.

## Technical Features
- **Adapter Encapsulation**: All input/output is handled via standardized adapters, allowing the function block to be integrated into complex adapter networks.
- **Reuse**: Internally, the proven IEC 61131-3 block `F_NE` is used, which implements an efficient, type-independent non-equal comparison.
- **Unidirectional Adapters**: The adapters used (`AUI`, `AX`) are unidirectional – they each support only one data and event direction, which increases the clarity of data flows.
- **No State Storage**: The function block is stateless; each event triggers a recalculation.

## State Overview

The FB `AUI_NE` itself does not have its own state machine. Its behavior is entirely determined by the internal `F_NE` block, which implements a simple functional sequence without states. The event-driven control (input → calculation → output) is strictly causal.

## Application Scenarios
- **Deviation Monitoring**: Check whether two measured values (e.g., temperature, pressure) differ from each other.
- **Threshold Violation**: Combine with other blocks to use inequality as part of a plausibility check.
- **Data Validation**: Detect whether two redundant signals provide different values (comparison of copies).
- **Event-Driven Comparisons**: Embedding in applications that only require a comparison when one of the inputs changes.

## Comparison with Similar Blocks

| Block | Comparison Function | Special Feature |

|----------|---------------------|--------------|

| `AUI_EQ` | Equal | Result `TRUE` for equal values |

| `AUI_NE` | Not equal | Result `TRUE` for different values |

| `AUI_GT` | Greater than | Result `TRUE` if IN1 > IN2 |

| `AUI_LT` | Less than | Result `TRUE` if IN1 < IN2 |

All the aforementioned components share the same adapter interface and can therefore be easily exchanged or combined.

## Conclusion

The `AUI_NE` is a simple yet reliable function block for comparing the difference between two values within an adapter-based 4diac environment. Its strengths lie in its clean encapsulation via adapters, event-driven execution, and high reusability thanks to the underlying IEC 61131-3 component. It is particularly well-suited for modular, expandable automation solutions.

--

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
