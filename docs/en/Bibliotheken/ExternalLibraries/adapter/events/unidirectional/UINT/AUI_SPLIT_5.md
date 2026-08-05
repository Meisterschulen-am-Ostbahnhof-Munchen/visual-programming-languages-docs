# AUI_SPLIT_5
![AUI_SPLIT_5](./AUI_SPLIT_5.svg)
* * * * * * * * * *
## Introduction
The function block **AUI_SPLIT_5** is a generic building block for splitting an incoming AUI adapter (Automation Unit Interface) into five separate, identical AUI outputs. It implements a 1:5 distribution in a unidirectional data direction. Designed for use in automation technology, it enables the redundant or distributed forwarding of AUI signals.
## Interface Structure
### **Event Inputs**
No event inputs available.

#### **Event Outputs**
No event outputs available.

#### **Data Inputs**
No data inputs available. Signals are transmitted exclusively via the adapter interfaces.

#### **Data Outputs**
No data outputs available.

#
# ### **Adapters**

The module features six adapter interfaces of type `adapter::types::unidirectional::AUI`:

- **IN** (Socket) – Input adapter for the AUI signal to be distributed.
- **OUT1** to **OUT5** (Plugs) – Five output adapters that mirror the incoming signal.

All adapters are unidirectional and transmit data and, optionally, associated events according to the AUI specification.

## Functionality
The module functions as a pure splitter without logic or buffering. An AUI signal present at socket **IN** is copied in parallel and unchanged to all five plugs **OUT1** to **OUT5**. The forwarding is instantaneous, i.e., without delay due to internal processing. The individual outputs are not galvanically or logically isolated – a change at the input immediately affects all outputs.

#
# Functionality ## Technical Features
- **Generic Type**: The function block (FB) is declared as a generic block (attribute `eclipse4diac::core::GenericClassName` = `'GEN_AUI_SPLIT'`). This allows for later type adaptation or instantiation with a specific AUI type.
- **No State Maintenance**: Since there are no events or data that react to changes, the FB is stateless. A state machine is not required.
- **Full Bandwidth**: The outputs provide the input signal without restriction – all data and event channels of the AUI adapter are copied 1:1.

## State Overview

The function block does not have its own states or state machines. It behaves like passive wiring. A state overview is therefore not applicable.

## Application Scenarios
- **Signal Distribution**: Splitting a central AUI data stream to multiple parallel consumers (e.g., displays, monitoring units, controllers).
- **Test and Diagnostic Setups**: Used in test benches to simultaneously send a signal to multiple measuring devices or logging systems.
- **Redundancy**: Provides identical signals for failover systems when AUI communication is unidirectional.
- **Bus Coupling**: Used as a passive splitter in AUI-based line or star topologies.

## Comparison with Similar Components
- **AUI_SPLIT_2 / AUI_SPLIT_3 / AUI_SPLIT_4**: Analog components with fewer outputs; scaling is achieved solely by selecting the appropriate split type.
- **AUI_MERGE (e.g., AUI_MERGE_5)**: Combines multiple AUI inputs into a single output – the opposite function.
- **Pure Event Splitters (E_SPLIT)**: Share only events, not data adapters. The AUI_SPLIT_5, however, distributes complete adapter interfaces.

## Conclusion

The **AUI_SPLIT_5** is a simple yet essential component for multiplying AUI signals. Its generic design and the adapter's complete passthrough make it highly versatile. It represents an optimal solution for applications requiring unidirectional 1:5 distribution while minimizing latency.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
