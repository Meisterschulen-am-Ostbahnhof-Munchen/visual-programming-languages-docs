# AR_MUX_3

![AR_MUX_3](./AR_MUX_3.svg)

* * * * * * * * * *
## Introduction

The function block `AR_MUX_3` is a generic 3-way multiplexer for the adapter type `adapter::types::unidirectional::AR`. Based on an index `K`, it selects one of three inputs (IN1, IN2, IN3) and forwards its signal to the output OUT. The block is event-controlled and is suitable for dynamically switching data sources in IEC 61499-based controllers.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| REQ | Event | Set Index K – triggers selection |

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| CNF | Event | Confirmation of successful switching |

### **Data Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| K | UINT | Index for selection (0, 1, or 2) |

### **Data Outputs**

None (the output data is provided via the OUT adapter).

### **Adapter**

| Direction | Name | Type | Comment |
|----------|------|-----|-----------|
| Plug | OUT | adapter::types::unidirectional::AR | Output that passes the selected input |
Socket | IN1 | adapter::types::unidirectional::AR | Input 1 for index K = 0 |
Socket | IN2 | adapter::types::unidirectional::AR | Input 2 for index K = 1 |
Socket | IN3 | adapter::types::unidirectional::AR | Input 3 for index K = 2 |

## Functionality

The function block operates in an event-driven manner:

1. An incoming event at input `REQ` triggers processing.
2. The current value of index `K` is read.
3. Depending on `K`, the corresponding input (IN1, IN2, IN3) is switched to the adapter output `OUT`.
- Valid values: 0 → IN1, 1 → IN2, 2 → IN3.
- Values outside this range result in undefined behavior (no explicit error handling).
4. After successful switching, the confirmation event `CNF` is sent.

The adapters are unidirectional; data flows from the selected socket to the plug.

## Technical Features

- **Generic Function Block**: The function block is declared as a generic type (`GEN_AR_MUX`) and can be used for any `AR` adapter.
- **Adapter-based data transmission**: All inputs and outputs use adapters of type `adapter::types::unidirectional::AR`, enabling flexible coupling with other function blocks.
- **Fixed number of 3 inputs**: The function block is not parameterizable; there is no way to change the number of inputs at runtime.
- **No plausibility check**: The index `K` is not checked for valid values. Invalid indices (e.g., >2) can lead to unexpected behavior.

## State overview

The function block does not have an explicit state machine, as the logic is controlled purely by the event `REQ`. Nevertheless, the process can be described as a simple state machine:

| State | Description |
|---------|-------------|
| IDLE | Waiting for a `REQ` event |
SELECT | Select input according to index `K` |
DONE | Output switched, sending `CNF`, returning to IDLE |

## Application Scenarios

- **Signal Switching**: Switching between different sensor values or control parameters in an automation application.
- **Operating Mode Selection**: Selecting different control modes, e.g., manual/automatic operation, depending on user input.
- **Test and Diagnostic Functions**: Feeding test signals onto a common output channel.

## Comparison with Similar Function Blocks

| Function Block | Number of Inputs | Special Feature |
----------|-----------------|--------------|
AR_MUX_2 | 2 | Simpler Multiplexer for Two Sources |
AR_MUX_3 | 3 | This Module |
AR_MUX_4 | 4 | Extended Version with Four Inputs |

All multiplexers follow the same principle and differ only in the number of adapter sockets.

## Change Detection

The selected output plug (`OUT`) is only written and its adapter event only sent if the incoming value differs from the value currently held on `OUT`. If the value is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.


## Conclusion

The `AR_MUX_3` is a compact and functional module for selecting one of three adapter signals. It is particularly suitable for applications requiring simple, event-driven switching. The use of adapters ensures clean encapsulation and reusability in modular control projects.
