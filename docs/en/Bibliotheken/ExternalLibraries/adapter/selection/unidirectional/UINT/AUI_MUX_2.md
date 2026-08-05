# AUI_MUX_2

![AUI_MUX_2](./AUI_MUX_2.svg)

* * * * * * * * * *

## Introduction
The function block **AUI_MUX_2** is a generic multiplexer for AUI adapters (unidirectional interface). It selects one of two inputs based on an index parameter and forwards it to the output. The block implements a 2-to-1 selection for AUI data streams.

## Interface Structure
### **Event Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| REQ | Event | Set Index K; takes the value of K |

### **Event Outputs**

| Name | Type | Comment |

|------|-----|-----------|

| CNF | Event | Confirmation that index K has been set |

### **Data Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| K | UINT | Index for selection (0 = IN1, 1 = IN2) |

### **Data Outputs**
*None*

### **Adapters**

| Direction | Name | Type | Comment |

|----------|------|-----|-----------|

| Socket | IN1 | `adapter::types::unidirectional::AUI` | First input value |

| Socket | IN2 | `adapter::types::unidirectional::AUI` | Second input value |

| Plug | OUT | `adapter::types::unidirectional::AUI` | Output: IN1 for K = 0, IN2 for K = 1 |

## Functionality
An event at the **REQ** input takes the current value of the data input **K** and selects the corresponding adapter input:

- If **K = 0**, the AUI data stream present at **IN1** is forwarded to the **OUT** output.

- If **K = 1**, the AUI data stream present at **IN2** is forwarded to the **OUT** output.

- For other values of K, the behavior is undefined (no valid output is set).

After a successful switchover, an event is output at the **CNF** output.

The function block is designed generically and uses the type-hash mechanics of Eclipse 4diac to enable efficient code generation.

## Technical Features

- **Generic Function Block**: The FB is declared as a generic function block (`GenericClassName = 'GEN_AUI_MUX'`), allowing it to be used with various AUI adapter variants with different data widths or types.

- **Type Hash**: The attribute `eclipse4diac::core::TypeHash` provides a unique hash checksum for the generated code, optimizing reuse and compilation.

- **Package Structure**: The FB belongs to the package `adapter::selection::unidirectional`, indicating clear modularization.

## State Overview
The function block does not have an explicit state machine. Processing is event-driven: With each **REQ** event, the output is switched according to the current **K** value. Therefore, the block should be considered purely combinational or a simple switching circuit without an internal state.

## Application Scenarios

- **Selection between two AUI data sources**: e.g., switching between two sensors or control signals in automation technology.

- **Redundancy switching**: Fallback to a second AUI path if the first one fails.

- **Configurable signal switch**: In modular control systems, different AUI adapters can be dynamically switched to a common output.

## Comparison with similar components

- **MUX_2 (Standard IEC 61499)**: A general-purpose 2-to-1 multiplexer that works with simple data types (e.g., ANY). In contrast, AUI_MUX_2 is specifically designed for the AUI adapter interface and uses adapter-based communication.

- **AUI_MUX_4 or AUI_MUX_8**: Extended versions with more inputs; AUI_MUX_2 offers a minimalist, intuitive 2-channel selection.

- **AUI_MERGE**: A function block that combines multiple AUI streams (data-driven) – this is an active selection, not a merge operation.

## Conclusion
The **AUI_MUX_2** is a compact, generic multiplexer for unidirectional AUI interfaces. It enables clean, event-driven switching between two input adapters and is ideal for all applications requiring simple 2-to-1 selection at the AUI level. Thanks to its generic design, it can be flexibly adapted to various AUI data types.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]