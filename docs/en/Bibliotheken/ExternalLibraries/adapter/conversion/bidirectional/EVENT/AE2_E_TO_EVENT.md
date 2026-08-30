# AE2_E_TO_EVENT

<img width="1172" height="190" alt="image" src="https://github.com/user-attachments/assets/02b7c06e-111f-4166-ac20-aebdf89c9956" />
* * * * * * * * * *
## Introduction

The AE2_E_TO_EVENT function block is a composite function block used to convert AE2 adapter signals into events. It enables bidirectional communication between adapter-based components and event-driven function blocks.
![AE2_E_TO_EVENT](AE2_E_TO_EVENT.svg)

## Interface Structure

### **Event Inputs**

- **REQ** (Request to Adapter): Starts the conversion and sends a request to the adapter

### **Event Outputs**

- **CNF** (Confirmation from Adapter): Confirms successful completion of the conversion

### **Data Inputs**

*No data inputs available*

### **Data Outputs**

*No data outputs available*

### **Adapter**

- **AE2_IN** (Adapter Input): Bidirectional AE2 adapter input for communication with AE2-compatible components

## Functionality

This function block acts as a simple converter between the AE2 adapter protocol and the standard 4diac event system. Upon receiving a REQ event, a request is sent via the AE2 adapter. The adapter's response is received via the EO1 signal and output as a CNF event.

## Technical Features

- Implemented as a composite function block
- Uses bidirectional AE2 adapter communication
- Simple event forwarding without data manipulation
- The CNF output position is fixed at Y position 46

## State Overview

The function block has two main states:

1. **Wait State**: No active conversion
2. **Active State**: Conversion in progress (from REQ input to CNF output)

## Application Scenarios

- Integration of AE2-compatible devices into 4diac controllers
- Bridge functionality between different communication protocols
- Simple event conversion in automation systems
- Protocol conversion in distributed control systems

## ⚖️ Comparison with Similar Blocks

Compared to other adapter converters, AE2_E_TO_EVENT stands out due to its specific focus on the AE2 adapter protocol. While general adapter converters support various protocols, this module is specifically optimized for bidirectional AE2 communication.

## Conclusion

The AE2_E_TO_EVENT function block offers a reliable and simple solution for integrating AE2 adapters into event-driven 4diac systems. Its clear interface definition and straightforward functionality make it a practical tool for protocol conversions in industrial automation applications.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
