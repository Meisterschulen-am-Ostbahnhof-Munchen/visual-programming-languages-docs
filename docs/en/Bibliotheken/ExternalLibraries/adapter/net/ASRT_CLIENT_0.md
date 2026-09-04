# ASRT_CLIENT_0

![ASRT_CLIENT_0](ASRT_CLIENT_0.svg)

* * * * * * * * * *

## Introduction

The **ASRT_CLIENT_0** function block is a composite function block that triggers three independent remote OPC UA **method calls** (Set, Reset, and Toggle), each via its own `CLIENT_0` block, controlled through a single unidirectional **ASRT adapter socket**. It is the variant of [ASR_CLIENT_0](ASR_CLIENT_0.md) extended with a third trigger.

## Interface Structure

### **Event Inputs**

- **INIT** (EInit): Initialization event, associated with `QI`

### **Event Outputs**

- **INITO** (EInit): Initialization confirmation, associated with `QO`, `STATUS_SET`, `STATUS_RESET`, and `STATUS_TOGGLE`
- **CNF** (Event): Confirmation that one of the method calls has been sent, associated with the same status variables

### **Data Inputs**

- **QI** (BOOL): Qualifier input, opens (TRUE) or closes (FALSE) all three connections
- **ID_SET** (WSTRING): Remote method address for the Set call
- **ID_RESET** (WSTRING): Remote method address for the Reset call
- **ID_TOGGLE** (WSTRING): Remote method address for the Toggle call

### **Data Outputs**

- **QO** (BOOL): TRUE only if `SET_CLIENT`, `RESET_CLIENT`, and `TOGGLE_CLIENT` currently all report `QO = TRUE`
- **STATUS_SET** (WSTRING): Status information from `SET_CLIENT`
- **STATUS_RESET** (WSTRING): Status information from `RESET_CLIENT`
- **STATUS_TOGGLE** (WSTRING): Status information from `TOGGLE_CLIENT`

### **Adapter**

| Adapter | Type | Direction | Description |
|---------|------|-----------|--------------|
| S_R_T | adapter::types::unidirectional::ASRT | Socket (Input) | Set/Reset/Toggle |

## Functionality

1. Via the `INIT` event, the internal `SET_CLIENT`, `RESET_CLIENT`, and `TOGGLE_CLIENT` blocks are initialized one after another (chained serially through `INIT`/`INITO`) with `QI` and their respective `ID`. After all three have confirmed, `INITO` is reported externally.
2. An event at the adapter socket `S_R_T.SET`, `S_R_T.RESET`, or `S_R_T.TOGGLE` directly triggers the corresponding `CLIENT_0` method call.
3. All three `CLIENT_0` instances confirm independently with `CNF`, which is forwarded externally in each case.
4. The `AND_QO` block (AND_BOOL_3) ANDs the `QO` outputs of all three `CLIENT_0` instances into a single `QO`.

## Technical Features

- **Three parallel CLIENT_0 instances**: Set, Reset, and Toggle are handled by separate `CLIENT_0` blocks (different `ID`s, independent connections).
- **Sequential initialization**: The three internal blocks are initialized one after another (`SET_CLIENT.INITO` → `RESET_CLIENT.INIT` → `TOGGLE_CLIENT.INIT`), since composite FBTypes must explicitly chain their `INIT`/`INITO` through each instance in series.
- **Encapsulation**: Only the ASRT adapter interface is visible externally.

## State Overview

1. **Not Initialized**: The block is waiting for the `INIT` event.
2. **Initialized**: All three connections are established, the block is ready to trigger Set, Reset, or Toggle calls.
3. **Send Active**: An event arriving at the ASRT socket triggers the corresponding remote method call.

## Application Scenarios

- Remotely triggering three independent remote actions (Set/Reset/Toggle) through a single adapter, e.g. to switch a remote actuator with an additional toggle function
- Network coupling in ASRT-adapter-based applications

## Comparison with Similar Function Blocks

- **[ASR_CLIENT_0](ASR_CLIENT_0.md)**: The same base structure with only two triggers (no Toggle).
- **[AE_CLIENT_0](AE_CLIENT_0.md)**: Reduces the same pattern to a single trigger.
- **[ASRT_AX_CLIENT_0_SUBSCRIBE_1](ASRT_AX_CLIENT_0_SUBSCRIBE_1.md)**: Combines the same three `CLIENT_0` triggers with an additional `SUBSCRIBE_1` state channel behind a bidirectional adapter.

## Conclusion

**ASRT_CLIENT_0** bundles three independent remote method calls (Set/Reset/Toggle) behind a single ASRT adapter socket, making it suitable for applications where a remote actuator is switched via three separate OPC UA methods.
