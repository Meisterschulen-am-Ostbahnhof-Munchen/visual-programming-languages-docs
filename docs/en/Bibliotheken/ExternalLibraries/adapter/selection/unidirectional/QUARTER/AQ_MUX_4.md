# AQ_MUX_4

![AQ_MUX_4](./AQ_MUX_4.svg)

* * * * * * * * * *
## Introduction

The function block `AQ_MUX_4` acts as a multiplexer for adapters of type `AQ`. It selects one of four available adapter inputs (IN1–IN4) and forwards its signal to the adapter output OUT. The selection is made using a numerical index `K`, which is set via the event input `REQ`. The block is declared as a generic function block and can be adapted to the number of inputs in the development environment if necessary.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-------|---------------------------------|
| REQ | Event | Sets the index `K` and triggers the switchover. |

### **Event Outputs**

| Name | Type | Comment |
|------|-------|----------------------------------------|
| CNF | Event | Confirmation of the switchover (acknowledgment). |

### **Data Inputs**

| Name | Type | Comment |
|------|------|-------------------------------|
| K | UINT | Index of the desired input (0–3). |

### **Data Outputs**

No dedicated data outputs – output is via the adapter output `OUT`.

### **Adapter**

| Direction | Name | Type | Comment |
|----------|------|----------------------------------------------|---------------------------------------------------------------|
| Plug | OUT | `adapter::types::unidirectional::AQ` | Output: Signal of the selected input (IN1–IN4). |
| Socket | IN1 | `adapter::types::unidirectional::AQ` | First input (becomes active for K=0). |
| Socket | IN2 | `adapter::types::unidirectional::AQ` | Second input (becomes active for K=1). |
| Socket | IN3 | `adapter::types::unidirectional::AQ` | Third input (becomes active for K=2). |
| Socket | IN4 | `adapter::types::unidirectional::AQ` | Fourth input (becomes active for K=3). |

All adapters are of type `adapter::types::unidirectional::AQ` – a unidirectional adapter for analog output values (e.g., voltage or current signals).

## Functionality

The `AQ_MUX_4` operates in an event-driven manner:

1. An event at the `REQ` input triggers processing.
2. The current value of the `K` data input is read.
3. Depending on the value of `K` (0, 1, 2, or 3), the corresponding adapter input is switched to the adapter output `OUT`:
- `K = 0` → OUT receives the data from IN1
- `K = 1` → OUT receives the data from IN2
- `K = 2` → OUT receives the data from IN3
- `K = 3` → OUT receives the data from IN4
4. After a successful switch, the confirmation event `CNF` is sent.

If an index outside the valid range (0–3) is passed, the behavior is undefined – typically, no input is activated, or an unintended forwarding occurs.

## Technical Features

- **Generic Function Block**: The `AQ_MUX_4` is defined as a generic block (`GenericClassName = 'GEN_AQ_MUX'`). Therefore, in the 4diac IDE, it can be used as a template for multiplexers with a different number of inputs (e.g., 2, 8) without having to recreate the internal logic.
- **Adapter-Based Interface**: Unlike classic multiplexers with data types such as `INT` or `REAL`, this block uses adapters, allowing entire signal packets (e.g., values, quality flags) to be transmitted.
- **No Range Check**: The validity of `K` is not checked. In case of an incorrect operation (value > 3), the system behavior is undefined – this must be handled appropriately in the application.
- **No State Storage**: The block has no internal state other than the current connection. Every `REQ` event immediately triggers a reconfiguration.

## State Overview

The `AQ_MUX_4` block does not have an explicit state machine. The process can be described as a simple transaction:

IDLE → [REQ] → Auswerten von K → Verbindung umschalten → [CNF] → IDLE
The time interval between `REQ` and `CNF` is determined solely by the execution time of the surrounding control system.

## Application Scenarios

- **Switching between multiple analog setpoints** in a machine control system (e.g., agriculture, drive technology).
- **Operating mode selection** for actuators where different signal sources (manual, automatic, emergency) need to be actively switched.
- **Redundancy switching** between multiple analog measurement or control signals.

## Comparison with Similar Function Blocks

| Function Block | Interface | Number of Inputs | Special Feature |
|-------------|-------------------------------------|-----------------|--------------------------------------------------|
| `AQ_MUX_4` | Adapter (unidirectional, `AQ`) | 4 | Generic, optimized for analog output signals |
| `MUX` | Data types (e.g., `ANY`) | Configurable | Standard multiplexer from IEC 61499 libraries |
| `SEL` | Data types (two inputs) | 2 | Simple selection between two values |

The `AQ_MUX_4` stands out due to its use of adapters, which allow complex signals to be transmitted over a single connection, and its generic basis, which enables easy reuse in various configurations.

## Conclusion

The `AQ_MUX_4` is a practical component for dynamically selecting an analog output signal from up to four sources. Its adapter-based interface makes it particularly suitable for modular control architectures where signals are exchanged not only as individual values but also as structured data packets. The generic declaration also facilitates adaptation to varying requirements.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
