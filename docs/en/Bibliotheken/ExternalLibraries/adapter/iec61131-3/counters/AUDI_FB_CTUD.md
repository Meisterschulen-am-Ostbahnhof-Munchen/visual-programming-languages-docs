# AUDI_FB_CTUD

![AUDI_FB_CTUD](./AUDI_FB_CTUD.svg)

* * * * * * * * * *
## Introduction

The **AUDI_FB_CTUD** is an up/down counter with a value range for unsigned 32-bit integers (UDINT). It is implemented as a pure adapter version, meaning all inputs and outputs are provided via adapter interfaces. The function block encapsulates the standardized IEC 61131 function block `FB_CTUD_UDINT` and extends its functionality with an adapter-based interface. All output adapters are cyclically updated upon each triggering event (CU, CD, R, LD, or PV). If change-triggered (edge-sensitive) triggering is required, the use of a `AX_D_FF` as a filter block is recommended.
## Interface Structure

### **Event Inputs**

The function block has no discrete event inputs at the top level. All events are transmitted via the incoming adapter interfaces (sockets) of type `AX`.

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| `CNF` | `Event` | Execution acknowledgment – is output each time an incoming event is processed. |

Events are also sent via the outgoing adapters (plugs).

### **Data Inputs**

There are no direct data inputs at the top level. All data values are provided via sockets `CU.D1`, `CD.D1`, `R.D1`, `LD.D1`, and `PV.D1`.

### **Data Outputs**

There are no direct data outputs at the top level. The result data is output via plugs `QU.D1`, `QD.D1`, and `CV.D1`.

### **Adapters**

| Direction | Name | Type | Comment |
|----------|------|-----|-----------|
| **Socket (Input)** | `CU` | `adapter::types::unidirectional::AX` | Count up – Event and data (BOOL) for counting up |
**Socket (Input)** | `CD` | `adapter::types::unidirectional::AX` | Count down – Event and data (BOOL) for counting down |
**Socket (Input)** | `R` | `adapter::types::unidirectional::AX` | Reset – Event and data (BOOL) for resetting the counter |
**Socket (Input)** | `LD` | `adapter::types::unidirectional::AX` | Load – Event and data (BOOL) for loading the preset value |
**Socket (Input)** | `PV` | `adapter::types::unidirectional::AUDI` | Preset value – Event and data (UDINT) for the default value |
**Plug (Output)** | `QU` | `adapter::types::unidirectional::AX` | Output Up – Event and data (BOOL), active when the current count reaches 0 |
**Plug (Output)** | `QD` | `adapter::types::unidirectional::AX` | Output Down – Event and data (BOOL), active when the current count reaches >= PV |
**Plug (Output)** | `CV` | `adapter::types::unidirectional::AUDI` | Count value – Event and data (UDINT) with the current count value |

## Functionality

The `AUDI_FB_CTUD` internally uses the `FB_CTUD_UDINT` function block from the IEC 61131 library. All events received via the sockets (from `CU`, `CD`, `R`, `LD`, and `PV`) are routed to the `REQ` input of the internal function block. The corresponding data is routed to the appropriate inputs (`CU`, `CD`, `R`, `LD`, `PV`). The internal function block processes the request and updates its outputs. Upon successful processing, the event `CNF` is triggered, and simultaneously, the output adapters `QU`, `QD`, and `CV` are supplied with their new data and events.

The internal function block processes the request and updates its outputs. **Important:** This function block fires the output events (`QU.E1`, `QD.E1`, `CV.E1`) during **every** processing of an incoming event. No edge detection is performed.

## Technical Features

- **Pure Adapter Interface:** This function block has no traditional inputs/outputs, but only adapters (sockets and plugs). This enables flexible integration into adapter-based automation architectures.
- **Use of Unidirectional Adapters:** The adapters `AX` and `AUDI` are defined as unidirectional. This ensures a clear direction for data and event flows.
- **Encapsulation of the IEC 61131 standard:** The counting logic conforms to the standardized `CTUD` function block, which increases portability and maintainability.
- **Range:** The counter value is implemented as `UDINT` (unsigned, 0…2³²−1).

## State Overview

The internal `FB_CTUD_UDINT` cycles through the following states, depending on the incoming commands:

| Condition | Action |
|-----------|--------|
| `CU` = TRUE (rising edge) and `CD` = FALSE | Counter increments by 1 |
| `CD` = TRUE (rising edge) and `CU` = FALSE | Counter decreases by 1 |
| `R` = TRUE (rising edge) | Counter is reset to 0 |
| `LD` = TRUE (rising edge) | Counter is set to the value of `PV` |
| Simultaneous `CU` and `CD` edges | Counter value remains unchanged (priority: none) |
| `QU` = TRUE | Current value = 0 |
| `QD` = TRUE | Current value ≥ `PV` |

## Application Scenarios

- **Piece Counter in Production Plants:** Recording of products on a conveyor line, using `CU` and `CD` for accurate counting during forward and reverse movements.
- **Inventory Management:** Counting inbound and outbound shipments, with reset during inventory and load for target values.
- **Event Counter in Building Automation:** Recording of passenger flows (e.g., in elevators) with an additional reset function.
- **Adapter-based systems:** Integration into distributed control environments based on the adapter concept of the 4diac IDE (e.g., AUTOSAR-like communication).

## Comparison with similar components

| Feature | `AUDI_FB_CTUD` | Standard `CTUD` (IEC 61131) |
---------|----------------|----------------------------|
| **Interface** | Pure adapters (sockets/plugs) | Direct event and data inputs/outputs |
| **Data format** | UDINT (via AUDI adapter) | UDINT (direct) |
| **Event behavior** | Every incoming event triggers all outputs | Event is only output when relevant changes occur |
| **Flexibility** | Higher through adapter-based cabling | Lower, but simpler in classic PLC environments |
**Recommended filter** | Additional `AX_D_FF` for edge-triggered output | No filter needed, as it is edge-sensitive |

## Conclusion

The `AUDI_FB_CTUD`is a high-performance up/down counter whose adapter-based interface makes it particularly suitable for modern, modular automation solutions. It combines the proven IEC 61131 counting logic with the flexibility of 4diac adapter technology. Users should note, however, that output events are triggered with every processing operation, not just changes – a downstream edge filter may be necessary. With its clear structure and standardized data types, it represents a robust component for counting tasks in industrial control systems.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
