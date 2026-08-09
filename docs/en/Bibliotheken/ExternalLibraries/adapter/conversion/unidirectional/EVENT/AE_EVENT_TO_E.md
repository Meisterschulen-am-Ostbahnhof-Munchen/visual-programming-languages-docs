# AE_EVENT_TO_E

<img width="1310" height="249" alt="image" src="https://github.com/user-attachments/assets/4eca9bad-6eed-4dfd-9643-3b25d2e4cfc3" />
* * * * * * * * * *
## Introduction

The AE_EVENT_TO_E function block is a composite function block used to convert events into AE adapter signals. It enables the conversion of a simple event into an adapter-based output signal, which is particularly useful when integrating various communication interfaces.
![AE_EVENT_TO_E](AE_EVENT_TO_E.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Request event to trigger adapter conversion

### **Event Outputs**

- No direct event outputs available

### **Data Inputs**

- No data inputs available

### **Data Outputs**

- No data outputs available

### **Adapter**

- **AE_OUT**: Unidirectional AE adapter output for forwarding the converted events

## Functionality

This function block acts as a simple converter that forwards incoming REQ events directly to the AE_OUT adapter. Each time a REQ event arrives, the corresponding E1 event is triggered at the AE adapter output. No data processing or transformation takes place, as the block only forwards events.

## Technical Features

- Composite function block with a simple network structure
- Uses a unidirectional AE adapter interface
- Contains no data processing components
- Direct event forwarding without delay

## State Overview

The function block has a simple state:

- **Ready**: Waits for incoming REQ events
- Upon arrival of a REQ, AE_OUT.E1 is immediately triggered, and the block returns to the ready state

## Application Scenarios

- Integration of event-based systems into adapter-based architectures
- Coupling of different communication protocols
- As a bridge between simple events and more complex adapter interfaces
- In systems requiring a standardized AE interface

## ⚖️ Comparison with Similar Blocks

Compared to other conversion blocks, AE_EVENT_TO_E is characterized by its simplicity. While other converters often perform data processing or protocol translation, this block is limited to pure event forwarding. It is specifically optimized for integration into adapter-based systems.

## Conclusion

AE_EVENT_TO_E is a specialized function block for the simple conversion of events into AE adapter signals. Its strength lies in its minimalist implementation and reliable event forwarding, making it ideal for system integrations where no data processing is required.