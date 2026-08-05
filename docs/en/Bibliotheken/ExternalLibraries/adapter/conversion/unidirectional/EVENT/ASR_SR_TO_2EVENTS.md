# ASR_SR_TO_2EVENTS
<img width="1211" height="249" alt="image" src="https://github.com/user-attachments/assets/ebdb5839-2d56-43bd-9764-c85bd6cdd888" />
* * * * * * * * * *
## Introduction
The ASR_SR_TO_2EVENTS function block is a composite function block used to convert an ASR signal into two separate events. It enables the conversion of a bidirectional adapter signal into independent SET and RESET events.
![ASR_SR_TO_2EVENTS](ASR_SR_TO_2EVENTS.svg)

## Interface Structure

### **Event Inputs**
No direct event inputs are available.

### **Event Outputs**
- **SET**: Set / Turn On
- **RESET**: Reset / Turn Off

#### **Data Inputs**
No data inputs are available.

### **Data Outputs**
No data outputs are available.

### **Adapter**
- **ASR_IN**: Adapter input of type `adapter::types::unidirectional::ASR`

## Functionality
The function block forwards the SET and RESET signals of the ASR adapter directly to the corresponding event outputs. The incoming adapter events are transparently passed through to the outputs of the function block.

## Technical Features
- Composite function block without internal logic processing
- Direct connection between adapter events and output events
- No data processing or state management

## State Overview
The function block has no internal state and operates stateless. Every incoming adapter event is immediately forwarded to the corresponding output.

## Application Scenarios
- Integration of ASR adapters into event-based controllers
- Conversion of bidirectional signals into independent single events
- Interface adaptation between different communication protocols

## ⚖️ Comparison with similar components

Compared to simple adapter blocks, this composite function block offers specific conversion of ASR to event signals, while generic adapters enable more general interface adaptation.

## Conclusion
The ASR_SR_TO_2EVENTS function block provides a simple and efficient solution for converting ASR adapter signals into separate SET and RESET events. Its streamlined implementation without internal logic makes it a reliable and high-performance component for interface adaptation.
