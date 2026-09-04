# ASR_CLIENT_0

![ASR_CLIENT_0](ASR_CLIENT_0.svg)

* * * * * * * * * *

## Introduction

The **ASR_CLIENT_0** function block is a composite function block that triggers two independent remote OPC UA **method calls** (Set and Reset), each via its own `CLIENT_0` block, controlled through a single unidirectional **ASR adapter socket**. It is the variant of [AE_CLIENT_0](AE_CLIENT_0.md) extended with a second trigger.

## Interface Structure

### **Event Inputs**

- **INIT** (EInit): Initialization event, associated with `QI`

### **Event Outputs**

- **INITO** (EInit): Initialization confirmation, associated with `QO`, `STATUS_SET`, and `STATUS_RESET`
- **CNF** (Event): Confirmation that one of the method calls has been sent, associated with `QO`, `STATUS_SET`, and `STATUS_RESET`

### **Data Inputs**

- **QI** (BOOL): Qualifier input, opens (TRUE) or closes (FALSE) both connections
- **ID_SET** (WSTRING): Remote method address for the Set call
- **ID_RESET** (WSTRING): Remote method address for the Reset call

### **Data Outputs**

- **QO** (BOOL): TRUE only if `SET_CLIENT` and `RESET_CLIENT` currently both report `QO = TRUE`
- **STATUS_SET** (WSTRING): Status information from `SET_CLIENT`
- **STATUS_RESET** (WSTRING): Status information from `RESET_CLIENT`

### **Adapter**

| Adapter | Type | Direction | Description |
|---------|------|-----------|--------------|
| S_R | adapter::types::unidirectional::ASR | Socket (Input) | Set/Reset |

## Functionality

1. Via the `INIT` event, the internal `SET_CLIENT` and `RESET_CLIENT` blocks are initialized one after another (`INIT` → `INITO` → `INIT`) with `QI` and their respective `ID`. After both have confirmed, `INITO` is reported externally.
2. An event at the adapter socket `S_R.SET` directly triggers the internal `SET_CLIENT` method call; `S_R.RESET` triggers `RESET_CLIENT` accordingly.
3. Both `CLIENT_0` instances confirm independently with `CNF`, which is forwarded externally in each case.
4. The `AND_QO` block ANDs the `QO` outputs of both `CLIENT_0` instances into a single `QO`.

## Technical Features

- **Two parallel CLIENT_0 instances**: Set and Reset are handled by separate `CLIENT_0` blocks (different `ID`s, independent connections).
- **Sequential initialization**: The two internal blocks are initialized one after another (`SET_CLIENT.INITO` → `RESET_CLIENT.INIT`), since composite FBTypes must explicitly chain their `INIT`/`INITO` through each instance in series.
- **Encapsulation**: Only the ASR adapter interface is visible externally.

## State Overview

1. **Not Initialized**: The block is waiting for the `INIT` event.
2. **Initialized**: Both connections are established, the block is ready to trigger Set or Reset calls.
3. **Send Active**: A Set or Reset event arriving at the ASR socket triggers the corresponding remote method call.

## Application Scenarios

- Remotely triggering two independent remote actions (Set/Reset) through a single adapter, e.g. to switch a remote actuator
- Network coupling in ASR-adapter-based applications

## Comparison with Similar Function Blocks

- **[AE_CLIENT_0](AE_CLIENT_0.md)**: The same base structure with only one trigger instead of two.
- **[ASRT_CLIENT_0](ASRT_CLIENT_0.md)**: Extends the same pattern with a third trigger (Toggle).
- **[ASR_AX_CLIENT_0_SUBSCRIBE_1](ASR_AX_CLIENT_0_SUBSCRIBE_1.md)**: Combines the same two `CLIENT_0` triggers with an additional `SUBSCRIBE_1` state channel behind a bidirectional adapter.

## Conclusion

**ASR_CLIENT_0** bundles two independent remote method calls (Set/Reset) behind a single ASR adapter socket, making it suitable for applications where a remote actuator is switched via two separate OPC UA methods.
