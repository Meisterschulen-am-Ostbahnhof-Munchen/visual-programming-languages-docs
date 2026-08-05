# ASR2_4EVENTS_TO_SR2
<img width="1146" height="210" alt="image" src="https://github.com/user-attachments/assets/73199e82-fa67-457f-b043-7f54b3d02af7" />
* * * * * * * * * *
## Introduction
The function block ASR2_4EVENTS_TO_SR2 is a composite function block used to convert four events into the ASR2 adapter format. It enables bidirectional conversion between individual set/reset events and the standardized ASR2 adapter.
![ASR2_4EVENTS_TO_SR2](ASR2_4EVENTS_TO_SR2.svg)

## Interface Structure

### **Event Inputs**
- **EI_SET**: Set Event (Power On)
- **EI_RESET**: Reset Event (Power Off)

### **Event Outputs**
- **EO_SET**: Set Event (Power On)
- **EO_RESET**: Reset Event (Power Off)

### **Adapters**
- **ASR_OUT**: ASR2 Adapter Output (bidirectional)

## Functionality
This function block acts as a bridge between individual events and the ASR2 adapter. It forwards incoming set and reset events to the ASR2 adapter and simultaneously passes corresponding events from the ASR2 adapter to the outputs. This enables seamless integration of individual events into systems that use the ASR2 adapter format.

## Technical Features
- Bidirectional signal transmission
- Direct event forwarding without data processing
- Compatible with the ASR2 adapter standard
- Composite function block implementation

## State Overview
The function block has no internal state, as it functions solely as a pass-through element. All events are forwarded directly and without delay.

## Application Scenarios
- Integration of single-event systems into ASR2-based architectures
- Protocol conversion between different control systems
- Adapter solutions for existing automation systems
- Bidirectional communication between different event formats

## ⚖️ Comparison with similar blocks
Compared to simple event blocks, ASR2_4EVENTS_TO_SR2 offers specific adapter functionality for the ASR2 format. While standard blocks typically only offer unidirectional signal processing, this block enables bidirectional communication with ASR2-compatible systems.

## Conclusion

The ASR2_4EVENTS_TO_SR2 function block represents an efficient solution for integrating individual events into ASR2-based systems. Its bidirectional functionality and direct event forwarding make it a valuable component for system integration and protocol conversion in automated control systems.