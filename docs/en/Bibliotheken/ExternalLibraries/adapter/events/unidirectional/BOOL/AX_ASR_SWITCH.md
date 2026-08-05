# AX_ASR_SWITCH / AX_ASR_SWITCH_X
## Introduction
These function blocks serve as a bridge between the data-oriented AX world and the event-oriented ASR world (Set/Reset). They convert a Boolean signal (encapsulated in an AX adapter) into dedicated `SET` and `RESET` events.
Since the direction of the events (which sets the state, which clears it) is hard-coded in the adapter, two variants are available.
![AX_ASR_SWITCH](AX_ASR_SWITCH.svg)
## Variants

### **AX_ASR_SWITCH** (1:1)
- Input `G = TRUE` (1) ➜ Output `SET`
- Input `G = FALSE` (0) ➜ Output `RESET`

### **AX_ASR_SWITCH_X** (Crossed)
- Input `G = TRUE` (1) ➜ Output `RESET`
- Input `G = FALSE` (0) ➜ Output `SET`

## Interface Structure

### **Adapter**
- **G** (Socket): Input adapter type `AX`.
- **Q** (Plug): Output adapter type `ASR`.

## Functionality
The modules internally use a `E_SWITCH`. Each time an event (`E1`) arrives at the input adapter `G`, the current data value (`D1`) is checked, and the corresponding event (`SET` or `RESET`) is triggered at the output adapter `Q`.

## Application Scenarios
- Controlling bistable components (flip-flops) with a `ASR` input directly from a `AX` signal flow.
- Simplifying logic circuits where events need to be generated based on a static signal state.