# ASSEMBLE_AL_FROM_AD
![ASSEMBLE_AL_FROM_AD](./ASSEMBLE_AL_FROM_AD.svg)

* * * * * * * * * *
## Introduction
The function block **ASSEMBLE_AL_FROM_AD** is used to combine two 32-bit values provided via AD adapters (DWORD) into a 64-bit LWORD and output this LWORD via an AL adapter. It encapsulates the combination logic and provides a buffered, event-driven interface for 64-bit data.
## Interface Structure

### **Event Inputs**
- **DWORD_00.E1** – Event from the first AD adapter that triggers the combination.
- **DWORD_01.E1** – Event from the second AD adapter that also triggers the combination.

### **Event Outputs**
- **OUT.E1** – Event at the AL adapter indicating that a new LWORD value is present at the output.

### **Data Inputs**
- **DWORD_00.D1** – First 32-bit DWORD (lower-order part).
- **DWORD_01.D1** – Second 32-bit DWORD (higher-order part).

### **Data Outputs**
- **OUT.D1** – Composite 64-bit LWORD.

### **Adapters**
- **DWORD_00** (Socket, type `adapter::types::unidirectional::AD`) – Input adapter for the first DWORD.
- **DWORD_01** (Socket, type `adapter::types::unidirectional::AD`) – Input adapter for the second DWORD.
- **OUT** (Plug, type `adapter::types::unidirectional::AL`) – Output adapter for the resulting LWORD.

## Functionality

The FB operates internally as an FB network consisting of two sub-blocks:

1. **ASSEMBLE_LWORD_FROM_DWORDS** – Combines the two DWORD inputs `DWORD_00` and `DWORD_01` into one LWORD. The function block is triggered by the event `REQ`, which can be sent by **both** AD adapters (via `DWORD_00.E1` and `DWORD_01.E1`). After the combination is complete, the event `CNF` is output.

2. **E_D_FF_ANY** – Any D flip-flop that buffers the combined LWORD. The `CNF` event clocks the flip-flop (`CLK`), with the combined value present at the data input `D`. The stored value appears at output `Q` and is passed on via `OUT.D1`. Simultaneously, the flip-flop output event `EO` is triggered as `OUT.E1`.

Thus, the LWORD is only updated when one of the two AD adapters sends an event – the flip-flop prevents multiple or unwanted outputs when the inputs remain unchanged.

## Technical Features
- **Event-driven processing** – The combination is only triggered by incoming events from the AD adapters, thus avoiding unnecessary processing load.
- **Buffered output** – The D flip-flop ensures that a calculated LWORD remains stable at the output until the next update.
- **Independence of inputs** – Each of the two DWORD adapters can send an event at any time; The combination is then performed using the currently available values.
- **No dedicated event inputs at the top level** – The function block reacts exclusively via the adapter interfaces.

## State Overview

The function block does not use an explicit ECC, but rather an internal function block network. The functional sequence is:

1. **Waiting** for an event from `DWORD_00.E1` or `DWORD_01.E1`.

2. **Combining** – ASSEMBLE_LWORD_FROM_DWORDS processes the current DWORD values and creates the LWORD.

3. **Buffering** – The flip-flop takes the LWORD and outputs it via `OUT.D1`.

4. **Signaling** – The event `OUT.E1` is triggered.

5. Return to wait state.

A simultaneous request from both inputs results in only one processing step, as both events trigger the same `REQ` function of the combination block.

## Application Scenarios
- **64-bit Data Processing** – When a system operates with 32-bit interfaces and large values (e.g., high-resolution timestamps, counter readings, physical measurements) need to be combined into a single LWORD.
- **Protocol Conversion** – In fieldbuses or controllers that deliver data in separate DWORD segments and require 64-bit processing.
- **Secure Data Combination** – The buffered output prevents intermediate values from occurring with asynchronously arriving DWORDs.

## Comparison with Similar Function Blocks
- **ASSEMBLE_DWORD_FROM_WORDS** – Combines two WORDs into one DWORD; analogous principle, but for different word widths.
- **ASSEMBLE_LWORD_FROM_DWORDS** – The internal function block that performs the pure combination without buffering; ASSEMBLE_AL_FROM_AD adds event-driven buffering and the adapter interface.
- **Direct Use of a Type Converter** – Would be possible, but without event synchronization; the present function block offers a clean, industrialized solution with adapters.

## Conclusion

The **ASSEMBLE_AL_FROM_AD** function block is a specialized but useful building block for combining two DWORDs into one LWORD. It combines event-driven processing with stable output buffering and is ideal for control systems that exchange 64-bit data via standardized adapters. The use of adapters allows for easy integration into existing model structures.
