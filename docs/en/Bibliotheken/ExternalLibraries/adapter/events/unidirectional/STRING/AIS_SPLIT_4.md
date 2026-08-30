# AIS_SPLIT_4

![AIS_SPLIT_4](./AIS_SPLIT_4.svg)

* * * * * * * * * *
## Introduction

The function block **AIS_SPLIT_4** is used to distribute an incoming AIS adapter signal (type `adapter::types::unidirectional::AIS`) to four separate outputs. It implements a 1-to-4 split without modifying the data. The block is implemented generically and can be adapted to different signal types via the generic class name.
## Interface Structure

### **Event Inputs**

None.

### **Event Outputs**

None.

### **Data Inputs**

None.

### **Data Outputs**

None.

### **Adapters**

- **Socket (Input):** `IN` – Type `adapter::types::unidirectional::AIS`
- **Plugs (Outputs):**
- `OUT1` – Type `adapter::types::unidirectional::AIS`
- `OUT2` – Type `adapter::types::unidirectional::AIS`
- `OUT3` – Type `adapter::types::unidirectional::AIS`
- `OUT4` – Type `adapter::types::unidirectional::AIS`

## Functionality

The module forwards the adapter signal present at socket `IN` unchanged to all four output adapters. (`OUT1` … `OUT4`). No data manipulation, filtering, or buffering takes place. Each output corresponds exactly to the input signal. Distribution is asynchronous and without event control – the adapter interface handles data transmission according to its communication logic.

## Technical Features

- **Generic Type:** The function block is implemented as a generic function block. The actual signal type can be defined at creation time via the attribute `eclipse4diac::core::GenericClassName` (value `'GEN_AIS_SPLIT'`).
- **Type Hash:** An empty string (`''`) for the attribute `eclipse4diac::core::TypeHash` indicates that the function block is dynamically configured as needed.
- **Compactness:** Since there are neither event nor data inputs/outputs, the module is purely adapter-based and free of timing dependencies.

## State Overview

The module does not have a state machine – it operates continuously and without a state. There are no internal states or events that need to be switched. Its functionality is limited to passively passing through the adapter signal.

## Application Scenarios

- **Signal Distribution in Control Architectures:** An AIS signal provided by a source (e.g., a sensor) is to be made available to several downstream processing units or displays.
- **Redundant Data Transmission:** In safety-critical systems, the input signal can be routed to multiple independent paths without duplicating it.
- **Test and Debugging Environments:** A signal is routed in parallel to the actual logic and to an analysis/logging tool.

## Comparison with Similar Function Blocks

- **AIS_SPLIT_2 / AIS_SPLIT_8:** These function blocks represent variants with two and eight outputs, respectively. Their functionality is identical; only the number of output adapters differs.
- **Data-Based Splitters (e.g., SPLIT_INT):** Unlike adapter-based splitters, data-based splitters work with specific data types (e.g., integers) and usually require events for triggering. The AIS_SPLIT_4 is a pure adapter splitter and does not require explicit triggering.
- **Adapter Multiplexers (e.g., AIS_MUX):** A multiplexer selects one input from several, while the splitter distributes one input to multiple outputs.

## Change Detection

Each output plug is updated independently: the incoming value is written to a given output, and its adapter event sent, only if it differs from that output's current value. Outputs that are already in sync stay quiet, while an output that was just connected (or has drifted out of sync) still receives the update it needs.


## Conclusion

The **AIS_SPLIT_4** is a simple yet practical function block for reliably distributing an AIS signal to four identical outputs. Its generic design and pure adapter logic make it flexible and eliminate the need for additional event control. It is ideally suited for applications where a signal is needed multiple times without data processing or synchronization.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
