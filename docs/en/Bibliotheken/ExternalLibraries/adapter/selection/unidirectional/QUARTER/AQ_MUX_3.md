# AQ_MUX_3

![AQ_MUX_3](./AQ_MUX_3.svg)

* * * * * * * * * *
## Introduction

The **AQ_MUX_3** is a generic multiplexer for AQ adapters. It allows the selection of one of three analog inputs (IN1, IN2, IN3) and routes the selected input to the output OUT. Selection is made via the index K, which is set by an event. The function block is implemented as a generic function block (FB) and is suitable for applications requiring switching between different signal sources.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|------------|
| REQ | Event | Sets the index K and triggers the switching |

**With Variable:** K

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| CNF | Event | Confirmation that index K has been assigned |

### **Data Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| K | UINT | Index for selecting the input (0 → IN1, 1 → IN2, 2 → IN3) |

### **Data Outputs**

None – output is exclusively via the adapter output.

### **Adapter**

| Name | Type | Comment |
|------|-----|-----|-----------|
| OUT | Plug | `adapter::types::unidirectional::AQ` | Output – returns the value of the selected input (IN1 for K=0, IN2 for K=1, IN3 for K=2) |
| IN1 | Socket | `adapter::types::unidirectional::AQ` | First input (K=0) |
| IN2 | Socket | `adapter::types::unidirectional::AQ` | Second input (K=1) |
| IN3 | Socket | `adapter::types::unidirectional::AQ` | Third input (K=2) |

## Functionality

This function block operates in an event-driven manner: As soon as an event arrives at the **REQ** input, the current value of the data input **K** is evaluated. Depending on the value of the index, the corresponding adapter socket (IN1, IN2, or IN3) is switched to the output adapter **OUT**. After successful switching, the confirmation event **CNF** is output.

There is no internal state machine; switching occurs immediately upon each REQ event. The function block is therefore deterministic and has low latency.

## Technical Features

- **Generic Function Block** – The function block uses the generic class `GEN_AQ_MUX` and can therefore be used in various type configurations.
- **Adapter-Based Communication** – Inputs and outputs are implemented as AQ adapters (unidirectional), enabling loose coupling and reusability in different environments.
- **License** – The function block is provided under the **Eclipse Public License 2.0**.
- No dedicated data outputs; output data is transported via the OUT adapter.

## State Overview

No explicit ECC (Execution Control Chart) is defined in the provided XML. The behavior of the function block is therefore purely combinatorial: Every REQ event immediately sets the output and sends out CNF. There are no internal delays or wait states.

## Application Scenarios

- **Signal Switching** – Selection between different analog measured values (e.g., temperature, pressure, level) for further processing in a controller.
- **Parameter Selection** – Switching between different setpoints or configuration profiles available as AQ adapters.
- **Redundancy** – Switching between multiple redundant sensors or actuators to increase reliability.

## Comparison with Similar Function Blocks

- **AQ_MUX_2** – A multiplexer with only two inputs (IN1, IN2). The AQ_MUX_3 extends this functionality to three inputs.
- **Data-Based Multiplexer Blocks** – Unlike purely data-oriented multiplexers (e.g., `MUX` based on `ANY` data types), the AQ_MUX_3 operates exclusively via adapters, resulting in tighter coupling to the AQ adapter interface.

## Conclusion

The AQ_MUX_3 is a simple yet effective generic multiplexer for AQ adapters. It allows flexible switching between three analog inputs and is particularly well-suited for modular control architectures where loose coupling via adapters is desired. Its deterministic response and simple interface make it a reliable component in the 4diac IDE.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
