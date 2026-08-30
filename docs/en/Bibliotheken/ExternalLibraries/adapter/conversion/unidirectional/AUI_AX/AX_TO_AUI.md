# AX_TO_AUI

![AX_TO_AUI](./AX_TO_AUI.svg)

* * * * * * * * * *
## Introduction

The AX_TO_AUI is a composite function block (FB) that converts a BOOL value from an AX adapter into a UINT value for an AUI adapter. It encapsulates the conversion logic and enables seamless integration between unidirectional adapters of different data types. The conversion is event-driven via an internal IEC 61131 conversion block.
## Interface Structure

The block has no direct event or data interfaces, but only adapter interfaces. The following list describes the signals provided or required by the adapters.

## **Event Inputs**

- **AX_IN.E1** (Event from the connected AX adapter): Triggers the conversion of the provided BOOL value.

### **Event Outputs**

- **AUI_OUT.E1** (Event for the connected AUI adapter): Signals that the converted UINT value is present.

### **Data Inputs**

- **AX_IN.D1** (BOOL): Boolean input value (e.g., 0 or 1) to be converted to a UINT value.

### **Data Outputs**

- **AUI_OUT.D1** (UINT): Integer output value (0 or 1) corresponding to the converted BOOL input.

### **Adapter**

- **AX_IN** (Socket) – Type: `adapter::types::unidirectional::AX` (BOOL)
- **AUI_OUT** (Plug) – Type: `adapter::types::unidirectional::AUI` (UINT)

## Functionality

The function block operates as a simple pipeline: An incoming event at socket AX_IN.E1 triggers the internal function block `F_BOOL_TO_UINT`. This block reads the current value from AX_IN.D1, converts it to a UINT value (BOOL FALSE → 0, BOOL TRUE → 1), and places the result at AUI_OUT.D1. Upon completion, an event is output via AUI_OUT.E1. The entire process is atomic and event-driven; there is no internal state.

## Technical Features

- **Bit-reinterpretation, value-preserving** (destination is same width or wider than the source bit-string).

- The function block is implemented as a composite function block, meaning... It consists of a network of subordinate FB instances (here only `F_BOOL_TO_UINT`).
- The conversion follows the IEC 61131-3 conversion rule: BOOL FALSE = 0, BOOL TRUE = 1.
- The use of adapters enables loose coupling between components of different domains (BOOL control and UINT communication).
- The FB does not have its own state machine; execution is purely event-driven.

## State Overview

Since this is a composite FB without its own ECC (Execution Control Chart), there are no explicit states. Its functionality is limited to the event-driven execution of the internal FB.

## Application Scenarios

- **Control Interface**: A BOOL signal (e.g., switch on/off) is converted into a numerical value to be sent to a higher-level controller via an AUI adapter.
- **Protocol Adaptation**: Connecting a BOOL-based sensor to a system that expects UINT values (e.g., for further processing in arithmetic blocks).
- **Standardization of Adapter Interfaces**: The function block acts as an adapter between two different unidirectional adapter types, avoiding redundant development.

## Comparison with Similar Function Blocks

- **AX_TO_AUI** converts BOOL to UINT.
- **AX_TO_ASI** would convert BOOL to SINT, **AX_TO_ADI** BOOL to DINT – all follow the same pattern, but with different target types.
- Unlike a generic `F_BOOL_TO_UINT`, this function block offers an encapsulated adapter interface and can be directly integrated into adapter-based architectures.

## Conclusion

The AX_TO_AUI is a small, specialized function block for converting BOOL to UINT data via adapter interfaces. It fulfills a typical integration task in IEC 61499-based systems, where different data types need to be connected via unidirectional adapters. Its composite structure makes the implementation transparent and extensible.
