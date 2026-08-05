# AE_E_TO_EVENT
<img width="1231" height="221" alt="image" src="https://github.com/user-attachments/assets/2194d39b-b5e1-4ac1-a0ec-3cc874a94b26" />
* * * * * * * * * *
## Introduction
The AE_E_TO_EVENT function block is a composite function block used to convert adapter events into standard events. It enables the conversion of adapter signals into generally usable event outputs and serves as a bridge between adapter interfaces and standardized event-based communication structures.
![AE_E_TO_EVENT](AE_E_TO_EVENT.svg)

## Interface Structure

### **Event Inputs**
*No direct event inputs available*

### **Event Outputs**
- **CNF** - Acknowledge event from the adapter

### **Data Inputs**
*No data inputs available*

### **Data Outputs**
*No data outputs available*

### **Adapter**
- **AE_IN** - Adapter input of type `adapter::types::unidirectional::AE`

## Functionality
The function block forwards the E1 event from the adapter input AE_IN directly to the CNF output. This is a simple pass-through functionality where adapter events are converted into standardized function block events.

## Technical Features
- Unidirectional signal processing
- No data processing or conversion
- Direct event forwarding without delay
- Positioning of the CNF output at Y position 46

## State Overview
The function block has a simple state:

- **Ready**: Waiting for an E1 event from the adapter
- Upon arrival of E1, CNF is triggered immediately

## Application Scenarios
- Integration of adapter interfaces into existing function block networks
- Coupling of different communication protocols
- Extension of systems with specific adapter requirements
- Protocol implementation in distributed automation systems

## ⚖️ Comparison with Similar Blocks
Compared to other conversion blocks, AE_E_TO_EVENT is characterized by its simplicity. While other converters often offer additional data processing or signal conditioning, this block is limited to pure event forwarding.

## Conclusion

The AE_E_TO_EVENT function block represents a streamlined and efficient solution for adapter integration. Its simplicity makes it reliable and easy to understand, while simultaneously fulfilling the necessary bridging function between adapter interfaces and standardized event systems.