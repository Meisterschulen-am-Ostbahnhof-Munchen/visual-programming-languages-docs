# ASRT_SRT_TO_3EVENTS

* * * * * * * * * *

## Introduction

The ASRT_SRT_TO_3EVENTS function block is a composite function block used to convert an ASRT signal into three separate events. It enables the conversion of a unidirectional adapter signal into independent SET, RESET, and TOGGLE events, and is the TOGGLE-extended variant of [ASR_SR_TO_2EVENTS](ASR_SR_TO_2EVENTS.md).

![ASRT_SRT_TO_3EVENTS](ASRT_SRT_TO_3EVENTS.svg)

## Interface Structure

### **Event Inputs**

No direct event inputs available.

### **Event Outputs**

- **SET**: Set / power on
- **RESET**: Reset / power off
- **TOGGLE**: Inverts the output signal

### **Data Inputs**

No data inputs available.

### **Data Outputs**

No data outputs available.

### **Adapter**

- **ASRT_IN**: Adapter input of type `adapter::types::unidirectional::ASRT`

## Functionality

This function block forwards the SET, RESET, and TOGGLE signals of the ASRT adapter directly to the corresponding event outputs. The incoming adapter events are passed through transparently to the outputs of the function block.

## Technical Features

- Composite function block without internal logic processing
- Direct connection between adapter events and output events
- No data processing or state management

## State Overview

The function block has no internal state and operates statelessly. Every incoming adapter event is immediately forwarded to the corresponding output.

## Application Scenarios

- Integration of ASRT adapters into event-based controls
- Conversion of unidirectional adapter signals into independent individual events
- Interface adaptation between different communication protocols

## ⚖️ Comparison with Similar Blocks

Compared to [ASR_SR_TO_2EVENTS](ASR_SR_TO_2EVENTS.md), this composite function block additionally handles the TOGGLE signal of an ASRT adapter instead of an ASR adapter.

## Conclusion

The ASRT_SRT_TO_3EVENTS function block provides a simple and efficient solution for converting ASRT adapter signals into separate SET, RESET, and TOGGLE events. Its lean implementation without internal logic makes it a reliable and efficient component for interface adaptation.
