# AE2_EVENT_TO_E

<img width="1172" height="190" alt="image" src="https://github.com/user-attachments/assets/5d62029b-f8de-45fd-a75c-34b753c1edc3" />
* * * * * * * * * *
## Introduction

The AE2_EVENT_TO_E function block is a composite function block used to convert EVENT signals into the AE2 adapter format. It enables bidirectional communication between standard events and the specific AE2 adapter.
![AE2_EVENT_TO_E](AE2_EVENT_TO_E.svg)

## Interface Structure

### **Event Inputs**

- **REQ** (Request to Adapter): Starts the conversion and sends a request to the AE2 output adapter

### **Event Outputs**

- **CNF** (Confirmation from Adapter): Confirms the successful completion of the conversion and receipt of the response from the AE2 adapter

### **Data Inputs**

No data inputs available

### **Data Outputs**

No data outputs available

### **Adapters**

- **AE2_OUT** (Adapter Output): Bidirectional AE2 output adapter for communication with AE2-compatible systems

## Functionality

This function block forwards incoming REQ events directly to the AE2_OUT adapter (EO1 port). Simultaneously, incoming acknowledgments from the AE2 adapter (EI1 port) are output as CNF events. This enables transparent conversion between the standard EVENT format and the specific AE2 adapter protocol.

## Technical Features

- Implemented as a composite function block
- Supports bidirectional communication
- Uses the AE2 adapter type from the adapter::types::bidirectional package
- Positioned adapter interface for optimized visualization

## State Overview

The function block features a simple state machine:

1. **Idle State**: Waits for a REQ event
2. **Request State**: After REQ input, sends to AE2_OUT.EO1
3. **Confirmation State**: After receiving AE2_OUT.EI1, outputs CNF

## Application Scenarios

- Integration of EVENT-based systems into AE2-compatible environments
- Protocol conversion in distributed automation systems
- Bidirectional communication bridges between different automation components
- Adapter-based system integration

## ⚖️ Comparison with Similar Blocks

Compared to simple EVENT converters, this offers AE2_EVENT_TO_E provides specific AE2 adapter support with bidirectional communication. While standard converters often operate only unidirectionally, this block enables complete request-response cycles with the AE2 protocol.

## Conclusion

The AE2_EVENT_TO_E function block offers a reliable solution for converting between standard event signals and the AE2 adapter protocol. Its bidirectional functionality and ease of integration make it particularly suitable for systems requiring seamless communication between different protocol environments.
