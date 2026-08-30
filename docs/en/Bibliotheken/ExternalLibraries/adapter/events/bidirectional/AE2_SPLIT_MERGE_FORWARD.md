# AE2_SPLIT_MERGE_FORWARD

<img width="1208" height="217" alt="image" src="https://github.com/user-attachments/assets/68ee26f9-debb-44fc-8735-e765847cdb6f" />
* * * * * * * * * *
## Introduction

The AE2_SPLIT_MERGE_FORWARD function block is a bidirectional splitter and merger with bidirectional forwarding. It serves as a universal distributor and collector for events in 4diac systems and enables the flexible distribution of events across various interfaces.
![AE2_SPLIT_MERGE_FORWARD](AE2_SPLIT_MERGE_FORWARD.svg)

## Interface Structure

### **Event Inputs**

- **EI**: Input Event

### **Event Outputs**

- **EO**: Output Event

### **Adapters**

- **PLUG**: Bidirectional AE2 Adapter
- **SOCKET**: Bidirectional AE2 Adapter

## Functionality

The function block operates according to the following principles:

1. **Event Distribution**: Every event received at the EI input is simultaneously forwarded to both adapters (PLUG and SOCKET).
2. **Event Merging**: Events received via either adapter (PLUG or SOCKET) are output at the EO output.
3. **Bidirectional Forwarding**: Events are forwarded bidirectionally between the two adapters, allowing PLUG and SOCKET events to be exchanged.

## Technical Features

- Uses the bidirectional AE2 adapter type
- Enables parallel event distribution
- Provides full bidirectional communication between all interfaces
- No data connections – purely event-based

## State Overview

The function block has no internal states and operates purely combinatorially. All event processing occurs immediately upon the arrival of an event.

## Application Scenarios

- Distributor for control events in complex automation networks
- Interface adapters between different system components
- Event routing in modular control architectures
- Bidirectional communication bridges between function blocks

## ⚖️ Comparison with similar modules

Compared to simple splitter blocks, AE2_SPLIT_MERGE_FORWARD additionally offers:

- Bidirectional functionality
- Adapter-based interfaces
- Event merging
- Direct communication between adapters

## Conclusion

The AE2_SPLIT_MERGE_FORWARD is a versatile function block for complex event distribution and collection tasks in 4diac systems. Its bidirectional nature and adapter interfaces make it particularly suitable for modular and expandable automation solutions.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
