# AW_MUX_4
![AW_MUX_4](./AW_MUX_4.svg)

* * * * * * * * * *
## Introduction
The **AW_MUX_4** function block is a generic multiplexer (MUX) for the unidirectional adapter type *AW*. It allows the selection of one of four adapter inputs (IN1–IN4) and forwards its data to the adapter output (OUT). The selection is triggered by an event-driven index specification. The function block is particularly suitable for systems that require flexible switching between different signals or data sources of type *AW*.
## Interface Structure

### **Event Inputs**

| Event | Type | Description |

|----------|-----|---------------|

| `REQ` | Event | Starts the selection of the specified index. The current value at `K` is evaluated. |

### **Event Outputs**

| Event | Type | Description |

|----------|-----|--------------|

| `CNF` | Event | Confirms successful selection. |

### **Data Inputs**

| Variable | Type | Description |

|----------|-------|--------------|

| `K` | UINT | Index for the input to be selected (valid values: 0–3). |

### **Data Outputs**

This function block does not have any independent data outputs. Output is exclusively via the adapter output.

### **Adapter**

| Direction | Name | Type | Description |

|----------|------|-----|--------------|

| Plug | `OUT` | `adapter::types::unidirectional::AW` | Output channel – contains the value of the selected input. |

| Socket | `IN1` | `adapter::types::unidirectional::AW` | First input – is passed through at `K = 0`. |

| Socket | `IN2` | `adapter::types::unidirectional::AW` | Second input – is passed through at `K = 1`. |

| Socket | `IN3` | `adapter::types::unidirectional::AW` | Third input – is passed through at `K = 2`. |

| Socket | `IN4` | `adapter::types::unidirectional::AW` | Fourth input – is passed through at `K = 3`. |

## Functionality

When the event `REQ` is received, the function block triggers a selection: Based on the current value of the data input `K` (data type `UINT`), one of the four adapter inputs `IN1`…`IN4` is selected, and its data is transferred to the adapter output `OUT`. After the switchover is complete, the event `CNF` is sent. If `K` is outside the range 0…3, the function block's behavior is unspecified – therefore, it should be ensured that only valid indices are passed.

## Technical Features
- **Generic Function Block:** The function block is declared as a generic type (`GEN_AW_MUX`), which allows its use in different contexts of the same adapter scheme.
- **Unidirectional Adapters:** The adapter type used, `adapter::types::unidirectional::AW`, is unidirectional; data flows only from the socket to the plug.
- **Licensing:** The function block is provided under the Eclipse Public License 2.0 (SPDX license identifier: EPL-2.0).
- **Type Hash:** A `TypeHash` attribute is provided to identify the exact implementation.

## State Overview

The function block has simple, event-driven state logic:

1. **Initial / Idle:** Waiting for the event `REQ`.

2. **Selection:** Upon arrival of `REQ`, the index `K` is read, and the corresponding connection between one of the four inputs and the output is established.

3. **Acknowledgement:** After successful switching, the event `CNF` is sent. The function block returns to the idle state.

A parallel state machine within the function block is not explicitly modeled – the sequence is implicitly defined by the event control.

## Application Scenarios
- **Selection of Sensor Data:** Four AW sensors are available in a machine controller. The desired sensor is selected via an index (e.g., via an HMI or a program counter), and its value is passed on to further processing (OUT).
- **Operating Mode Switching:** Four different operating modes are implemented via AW adapters – the multiplexer dynamically switches between the modes.
- **Test and Simulation Environments:** In combination with virtual AW adapter sources, various signals can be simulated and switched via the index.

## Comparison with Similar Devices

Standard IEC 61499 MUX devices typically work with pure data types (e.g., `ANY`) and have separate data inputs and outputs. The **AW_MUX_4**, on the other hand, encapsulates the data in a specific adapter type (`AW`). This allows for simpler wiring and type-safe coupling within an AW-based adapter environment. A disadvantage is the dependency on this specific adapter, which limits its reusability in environments without AW-type devices.

## Conclusion

The `AW_MUX_4` is a compact, generic multiplexer for AW adapters. It offers clear, event-driven selection between four inputs and outputs the selected signal via a single output. Its simple interface and EPL licensing make it a practical tool in AW adapter-based control applications where flexible signal switching is required.
