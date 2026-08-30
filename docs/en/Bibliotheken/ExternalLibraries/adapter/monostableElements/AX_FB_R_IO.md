# AX_FB_R_IO

![AX_FB_R_IO](./AX_FB_R_IO.svg)

* * * * * * * * * *

## Introduction

The function block **AX_FB_R_IO** implements monostable, reset-dominant behavior. It has three adapter interfaces through which it forwards an input signal (IN) to the output (OUT) if no active reset signal (RESET1) is present. The block operates on the principle: **Reset has priority**.

## Interface Structure

### **Event Inputs**

None.

### **Event Outputs**

None.

### **Data Inputs**

None.

### **Data Outputs**

None.

### **Adapters**

| Name | Type | Direction | Comment |
| ------------- | ---------------------- | ---------- | ------------------------- |
| IN | unidirectional::AX | Socket | Input signal |
| RESET1 | unidirectional::AX | Socket | Reset signal (prioritized) |
| OUT | unidirectional::AX | Plug | Output signal |

The adapters of type `adapter::types::unidirectional::AX` each have an event output `E1` and a data output `D1` (of type BOOL). The adapter's data value is provided via `D1`, and processing is triggered by the event `E1`.

## Functionality

The core logic of the component is represented by a simple state machine with a single state, `REQ`. As soon as an event arrives at one of the two input adapters (`IN.E1` or `RESET1.E1`), the algorithm `REQ` is executed. This algorithm checks the reset input:

- **If `RESET1.D1 = TRUE`**: The output `OUT.D1` is set to `FALSE`, regardless of the input signal.
- **Otherwise**: The output `OUT.D1` directly receives the value of the input signal `IN.D1`.

The event at the output adapter (`OUT.E1`) is triggered with each execution of the algorithm, so that subsequent function blocks are informed of the value change.

## Technical Features

- **Reset Dominance**: The reset signal `RESET1` always takes precedence over the input signal `IN`. As long as `RESET1.D1` is active, the output `FALSE` remains active.
- **Monostable Behavior**: The function block automatically returns to the standby state (one state) after each processing operation. There is no stored state; each execution reacts immediately to the current inputs.
- **Adapter-Based Communication**: All inputs and outputs are handled via bidirectional adapters that transport both data and events. Event control is implicit via the adapter protocols.
- **Package Name**: `adapter::monostableElements` (defined in CompilerInfo).

## State Overview

The function block has exactly one state:

| State | Description |
|---------|--------------|
| REQ | Start and end state. Waits for an event from `IN` or `RESET1`. After the algorithm has finished executing, the state always returns to `REQ` (no other states). |

There are two transitions:

- From `REQ` to `REQ` upon event `IN.E1`
- From `REQ` to `REQ` upon event `RESET1.E1`

Both transitions return to the same state and trigger the execution of the algorithm.

## Application Scenarios

- **Enable circuit in automation technology**: A signal (e.g., machine start) is only passed to the output if no reset command (e.g., stop) is active.
- **Safety interlock**: In a control chain, a reset signal is given priority to reliably eliminate dangerous states.
- **Priority Signal Switch**: Two sources compete for one output – here, the reset function always takes precedence.

## Comparison with Similar Function Blocks

- **AX_FB_RS** (Set-Dominant): Unlike this function block, the set input has priority. `AX_FB_R_IO` is reset-dominant.
- **AX_FB_SR**: Set-reset flip-flop with equal inputs, often without priority (can lead to undefined states). `AX_FB_R_IO` avoids this through clear dominance.
- **AX_FB_MONOSTABLE**: Pure monostable flip-flops with time parameters; `AX_FB_R_IO` has no time behavior but reacts instantly to signals.

## Conclusion

The function block `AX_FB_R_IO` is a simple yet reliable building block for realistically implementing prioritized reset behavior. Thanks to its adapter interface, it integrates seamlessly into event-driven automation systems. Its clear reset dominance makes it particularly suitable for safety and enabling functions where a reset signal must have absolute priority.
