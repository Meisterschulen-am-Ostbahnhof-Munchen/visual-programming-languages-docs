# UDINT_AUI_GT

![UDINT_AUI_GT](./UDINT_AUI_GT.svg)

* * * * * * * * * *

## Introduction

The function block **UDINT_AUI_GT** implements a greater-than comparison function. It compares a directly passed input value (`IN1`) with a second value provided via an adapter (`IN2`). The result of the comparison is output via an output adapter (`OUT`). The function block is classified as a standard comparison function according to IEC 61131-3.

## Interface Structure

### **Event Inputs**

| Name | Type | Description |

|------|-----|---------------|

| `REQ` | Event | Serves as a service request to trigger the comparison. The data input `IN1` is linked to this event. |

### **Event Outputs**

No explicit event outputs are available. Events are output via the adapter `OUT`.

### **Data Inputs**

| Name | Type | Description |

|------|-----|---------------|

| `IN1` | ANY_ELEMENTARY | First value of the comparison (any elementary data type). |

### **Data Outputs**

No explicit data outputs are available. Data is output via the adapter `OUT`.


### **Adapter**

| Name | Direction | Type | Description |

|------|----------|-----|--------------|

| `IN2` | Socket (Input) | `adapter::types::unidirectional::AUI` | Provides the second comparison value. The adapter provides an event output `E1` and a data output `D1`. A new value at the adapter triggers the comparison internally. |

| `OUT` | Plug (Output) | `adapter::types::unidirectional::AX` | Outputs the comparison result. The adapter has an event input `E1` and a data input `D1`, which are controlled by the function block. |

## Functionality

The function block performs a "greater than" comparison between two values:

- The first value is provided via the data input `IN1`.

- The second value is received dynamically via the socket adapter `IN2` (its data output `D1`).

- The comparison is triggered either by an event at the input `REQ` or by an incoming event at the adapter `IN2` (via `IN2.E1`).


``` - Internally, the IEC 61131-3 function block `F_GT` (from the library `iec61131::comparison`) is used.

- The result (true/false) is output via the plug adapter `OUT`: The data output of the internal `F_GT.OUT` is set to `OUT.D1`, and the completion event `F_GT.CNF` triggers `OUT.E1`.

## Technical Features

- **Generic Data Type:** `IN1` is of type `ANY_ELEMENTARY`, allowing the function block to work with various elementary data types (e.g., INT, REAL, TIME).

- **Adapter-Based Interface:** The use of adapters for the second input value and the result enables flexible integration into various environments and protocols.

- **Internal Reuse:** The function block delegates the actual comparison to the standardized `F_GT` function block, increasing consistency and maintainability.

- **Trigger Events:** The comparison can be triggered via the `REQ` input or via an event from the `IN2` adapter – this allows for reactive logic.

## State Overview

The function block does not have its own state machine (ECC). Its behavior is entirely determined by its internal link with the `F_GT` function block. Execution occurs whenever one of the input events (`REQ` or `IN2.E1`) is received. After the comparison is complete, the result is signaled via the output adapter.

## Application Scenarios

- **Threshold Monitoring:** Comparison of a measured value (`IN1`) with a limit value obtained from a higher-level controller via an adapter.

- **Dynamic Comparison Logic:** The adapter interface is ideally suited when the second comparison value is not static but originates from another function block or data source.

- **Standardized Comparison Functions:** Use in IEC 61131-3 environments where a function block with defined interfaces for "greater than" values is required.

## Comparison with Similar Components

Simple comparison components (e.g., `GT` with two direct data inputs) offer lower complexity but do not allow dynamic changes to the second comparison variable at runtime. The `UDINT_AUI_GT` is specifically designed for use in adapter-based architectures where the second variable is supplied via a unidirectional socket. The output adapter `AX` also allows for consistent further processing of the result, independent of the rest of the system.

## Conclusion

The `UDINT_AUI_GT` is a specialized comparison component that combines the strengths of adapter-based interfaces with the robustness of standardized IEC 61131-3 functions. Its flexible triggering capabilities and generic input type make it a versatile tool for comparison tasks in complex automation solutions.