# AL_SPLIT_6

![AL_SPLIT_6](./AL_SPLIT_6.svg)

* * * * * * * * * *
## Introduction

The function block **AL_SPLIT_6** is used to split a single unidirectional AL adapter input (socket) into six identical AL adapter outputs (plugs). It enables simple signal distribution within a 4diac application without requiring additional logic or a state machine.
## Interface Structure

### **Event Inputs**

No event inputs available.

### **Event Outputs**

No event outputs available.

### **Data Inputs**

No data inputs available.

### **Data Outputs**

No data outputs available.

### **Adapters**

| Direction | Identifier | Type | Description |
|----------|------------|-------------------------------|---------------------------------------------------|
| In | IN | adapter::types::unidirectional::AL | Unidirectional AL adapter as input signal. |
| Out | OUT1 | adapter::types::unidirectional::AL | First output channel (identical to IN). |
| Out | OUT2 | adapter::types::unidirectional::AL | Second output channel. |
| Out | OUT3 | adapter::types::unidirectional::AL | Third output channel. |
| Out | OUT4 | adapter::types::unidirectional::AL | Fourth output channel. |
| Out | OUT5 | adapter::types::unidirectional::AL | Fifth output channel. |
| Out | OUT6 | adapter::types::unidirectional::AL | Sixth output channel. |

## Functionality

This function block has no internal logic or state machine. It forwards the AL signal arriving at socket **IN** unchanged to all six plugs **OUT1** … **OUT6**. Any change or event at the input is thus transmitted simultaneously to all outputs. The function block operates purely structurally as a splitter and does not require event activation.

## Technical Features

- **Generic Function Block:** The function block uses the attribute `eclipse4diac::core::GenericClassName` with the value `GEN_AL_SPLIT`. This allows it to be treated as a generic type in the 4diac IDE and enables clean type system integration.
- **No Data/Event Interface:** Distribution occurs exclusively via the adapter interface. No additional data or event ports are required.
- **No Runtime Dependencies:** Since no algorithms or states exist, the function block is resource-efficient and requires no specific initialization.

## State Overview

The function block has no state machine (no ECC) and therefore no defined state machine. Its behavior is entirely determined by the interface structure and the simple forwarding of the adapter signal.

## Application Scenarios

- **Signal Distribution in Agricultural Engineering or Automation:** A central AL adapter (e.g., a control command) is to be sent to several downstream components simultaneously.
- **Tests and Simulations:** A test signal can be distributed in parallel to different modules to verify system behavior.
- **Redundant Paths:** The same AL adapter can be routed to different processing units via multiple channels.

## Comparison with Similar Function Blocks

- **AL_SPLIT_2, AL_SPLIT_4** … **AL_SPLIT_N**: These function blocks differ only in the number of output channels. The functionality is identical – a simple 1:N split.
- **Other split blocks with events or data:** Unlike these, **AL_SPLIT_6** has no data or event interfaces, but works purely via adapters. This simplifies configuration but limits the variety of types.

## Change Detection

Each output plug is updated independently: the incoming value is written to a given output, and its adapter event sent, only if it differs from that output's current value. Outputs that are already in sync stay quiet, while an output that was just connected (or has drifted out of sync) still receives the update it needs.


## Conclusion

The **AL_SPLIT_6** is a compact and efficient function block for multiplying a unidirectional AL adapter signal. Due to its generic nature and simple structure, it is ideally suited for all applications where an input signal needs to be distributed to multiple outputs without additional logic or event control.

--

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
