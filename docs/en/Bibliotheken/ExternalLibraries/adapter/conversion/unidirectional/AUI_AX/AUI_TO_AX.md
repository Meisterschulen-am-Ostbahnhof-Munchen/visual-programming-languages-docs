# AUI_TO_AX
![AUI_TO_AX](./AUI_TO_AX.svg)

* * * * * * * * * *
## Introduction
The **AUI_TO_AX** function block is a composite block that converts an AUI adapter (type *AUI* with a UINT value) into an AX adapter (type *AX* with a BOOL value). It serves as a bidirectional conversion interface between two different adapter types and is typically used to provide digital comparison results for further processing in BOOL-based adapters.
## Interface Structure
### **Event Inputs**
No direct event inputs. Event control is handled exclusively via the **AUI_IN** socket adapter.

### **Event Outputs**
No direct event outputs. The result event is passed on via the **AX_OUT** plug adapter.

### **Data Inputs**
No direct data inputs. The UINT value to be processed is provided via the socket adapter **AUI_IN**.

### **Data Outputs**
No direct data outputs. The BOOL result is output via the plug adapter **AX_OUT**.

### **Adapter**
- **AUX_IN (Socket)** – Type: *adapter::types::unidirectional::AUI*
- Event: E1 (triggering event for the comparison)
- Data: D1 (UINT value compared to 0)
- **AX_OUT (Plug)** – Type: *adapter::types::unidirectional::AX*
- Event: E1 (confirmation event after successful comparison)
- Data: D1 (BOOL result: TRUE if D1 ≠ 0, otherwise FALSE)

## Functionality
The function block internally contains an instance of the comparison function block *iec61131::comparison::F_NE* (inequality). The process is as follows:

1. An event on socket **AUI_IN.E1** triggers the input **REQ** of the F_NE function block.

2. The UINT value supplied by the socket via **AUI_IN.D1** is compared to the constant *UINT#0*.

3. The comparison result (BOOL) is provided at output **F_NE.OUT**.

4. The result event **F_NE.CNF** is forwarded to plug **AX_OUT.E1**.

5. The BOOL result is simultaneously transmitted to **AX_OUT.D1** via the data connection.

Therefore:

- AUI_IN.D1 = 0 → AX_OUT.D1 = FALSE
- AUI_IN.D1 ≠ 0 → AX_OUT.D1 = TRUE

## Technical Specifications
- **License:** Eclipse Public License 2.0 (EPL-2.0)
- **Author:** Franz Höpfinger, HR Agrartechnik GmbH
- **Package:** `adapter::conversion::unidirectional`
- **Internal Block:** `iec61131::comparison::F_NE` with parameter `IN2 = UINT#0`
- The block is a pure composite and does not contain its own state machine. All logic is implemented by the embedded F_NE.

## State Overview
Since this is a composite block without its own ECC (Execution Control Chart), there is no explicit state machine. The behavior is entirely determined by the internal F_NE block, which performs a simple comparison without intermediate storage. The block is therefore stateless.

## Application Scenarios
- **Threshold Detection:** Converting an analog (UINT) sensor value into a digital signal (BOOL), e.g., "non-zero value" as an alarm or control signal.
- **Adapter Conversion:** Use in systems that employ different adapter standards (AUI ↔ AX) to ensure compatibility between components.
- **Simple Logic Chaining:** Use as a binary decision stage in larger composite function blocks.

## Comparison with Similar Blocks

| Block | Input Type | Output Type | Function |

|----------|------------|------------|-----------|

| **AUI_TO_AX** | AUI (UINT) | AX (BOOL) | Inequality with Zero |

*AUI_TO_AX_INV* (hypothetical) | AUI (UINT) | AX (BOOL) | Equality with Zero (inverted) |

*CONV_UINT_TO_BOOL* (direct) | UINT (Data) | BOOL (Data) | Direct data converter, no adapter |

This function block stands out from simple data converters due to its full adapter compliance and integrated event handling.

## Conclusion
**AUI_TO_AX** is a compact, purpose-built composite function block for converting a UINT-based AUI adapter into a BOOL-based AX adapter. Thanks to the use of the standardized F_NE comparison, the function is reliable and easy to understand. The component is particularly suitable for integration into adapter-based automation architectures where a simple zero comparison needs to be elevated to the signal level.
