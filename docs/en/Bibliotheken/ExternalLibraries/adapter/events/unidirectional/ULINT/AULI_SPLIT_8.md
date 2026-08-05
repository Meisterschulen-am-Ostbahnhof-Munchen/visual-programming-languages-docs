# AULI_SPLIT_8
![AULI_SPLIT_8](./AULI_SPLIT_8.svg)

* * * * * * * * * *
## Introduction
The function block `AULI_SPLIT_8` is used to split an incoming unidirectional AULI adapter (socket `IN`) into eight identical AULI output adapters (`OUT1` to `OUT8`). It operates as a simple distributor – the incoming signal is passed on to all outputs without delay or logic modification. The block is designed generically and can be used with various AULI types (see attribute `GenericClassName`).
## Interface Structure
### **Event Inputs**
No event inputs are available.

### **Event Outputs**
No event outputs available.

### **Data Inputs**
No data inputs available.

### **Data Outputs**
No data outputs available.

### **Adapters**

| Direction | Name | Type | Description |
|----------|------|-----|--------------|
| Socket (Input) | `IN` | `adapter::types::unidirectional::AULI` | Incoming AULI adapter, distributed to the eight outputs. |
| Plug (Output) | `OUT1` – `OUT8` | `adapter::types::unidirectional::AULI` | Eight parallel outputs that forward the identical signal of the input. |

## Functionality
The function block has no integrated control logic (no ECC) and no data processing algorithms. It connects the incoming adapter `IN` directly to all eight output adapters `OUT1` to `OUT8`. Any data exchange that occurs via the adapter `IN` (e.g., events, value changes) is passed on to all output adapters without modification. The distribution is combinatorial – there is no intermediate storage or time staggering.

## Technical Features
- **Generic Structure:** The function block is declared as a generic function block with `eclipse4diac::core::GenericClassName = 'GEN_AULI_SPLIT'`. This allows it to be parameterized for different AULI adapter types (e.g., with different data types).
- **Pure Adapter Connection:** Neither event inputs/outputs nor data elements are required at the FB level – all communication takes place via the AULI adapters.
- **No State Logic:** The FB has no ECC; its behavior is entirely determined by the adapter wiring.

## State Overview
The function block does not contain an internal state machine. There are no distinguishable operating modes or state changes – the behavior is purely combinatorial.

## Application Scenarios
- **Signal Distribution:** An AULI sensor (e.g., temperature, pressure) should forward its signal to several independent devices (controllers, displays, data loggers) simultaneously.
- **Redundancy / Broadcasting:** A command or configuration is distributed from a central instance to up to eight actuators or subsystems.
- **Test Environments:** A simulated AULI value is sent in parallel to several FB instances for validation.

## Comparison with Similar Blocks
The 4diac IDE often includes blocks such as `SPLIT_2`, `SPLIT_4`, or generic split blocks for event/data lines. `AULI_SPLIT_8` specializes in this for the AULI adapter and offers a compact 1:8 distribution without additional data type conversion. Compared to manually chaining simpler split blocks, it reduces wiring complexity and improves clarity.

## Conclusion
The `AULI_SPLIT_8` is a simple yet useful distribution block for unidirectional AULI adapters. It enables clean, generic signal distribution across up to eight outputs and is particularly suitable for broadcasting scenarios where multiple receivers require the same adapter value. Its generic nature makes it versatile and facilitates reuse in various projects.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
