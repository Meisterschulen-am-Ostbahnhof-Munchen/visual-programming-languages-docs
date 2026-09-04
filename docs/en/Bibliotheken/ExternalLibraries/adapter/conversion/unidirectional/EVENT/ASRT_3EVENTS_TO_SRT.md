# ASRT_3EVENTS_TO_SRT

* * * * * * * * * *

## Introduction

The ASRT_3EVENTS_TO_SRT function block is a composite function block that converts three separate events (Set/Reset/Toggle) into an ASRT signal. It serves as a bridge between event-based control signals and the ASRT adapter format, and is the TOGGLE-extended variant of [ASR_2EVENTS_TO_SR](ASR_2EVENTS_TO_SR.md).

![ASRT_3EVENTS_TO_SRT](ASRT_3EVENTS_TO_SRT.svg)

## Interface Structure

### **Event Inputs**

- **SET**: Sets the output signal (power on)
- **RESET**: Resets the output signal (power off)
- **TOGGLE**: Inverts the output signal

### **Event Outputs**

No direct event outputs available

### **Data Inputs**

No data inputs available

### **Data Outputs**

No data outputs available

### **Adapter**

- **ASRT_OUT**: Unidirectional ASRT adapter output

## Functionality

This function block forwards incoming SET, RESET, and TOGGLE events directly to the ASRT adapter. A SET event activates the corresponding SET signal on the ASRT adapter, a RESET event activates the RESET signal, and a TOGGLE event activates the TOGGLE signal.

## Technical Features

- Composite function block without internal logic processing
- Direct event pass-through to the adapter
- Uses unidirectional ASRT adapter technology

## State Overview

The function block has no internal state. It acts purely as a signal relay between the event inputs and the ASRT adapter.

## Application Scenarios

- Integration of event-based control systems into ASRT-compatible environments
- Connection between different control levels
- Protocol implementation in automation systems

## ⚖️ Comparison with Similar Blocks

Compared to [ASR_2EVENTS_TO_SR](ASR_2EVENTS_TO_SR.md), ASRT_3EVENTS_TO_SRT additionally provides the TOGGLE event and therefore feeds an ASRT adapter instead of an ASR adapter.

## Conclusion

ASRT_3EVENTS_TO_SRT is a specialized function block for converting three separate events (Set/Reset/Toggle) into the ASRT adapter format. Its simple and straightforward operation makes it a reliable solution for system integrations.
