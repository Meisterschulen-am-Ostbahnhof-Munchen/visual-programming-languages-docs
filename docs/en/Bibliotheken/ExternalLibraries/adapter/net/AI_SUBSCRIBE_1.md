# AI_SUBSCRIBE_1

![AI_SUBSCRIBE_1](./AI_SUBSCRIBE_1.svg)

* * * * * * * * * *

## Introduction

The function block **AI_SUBSCRIBE_1** is a composite function block that encapsulates the network-based `SUBSCRIBE_1` function block from the IEC 61499 standard library and maps its interface to a unidirectional **AI adapter**. It subscribes to a publish channel configured via `ID` and provides the received **INT** value, buffered via a D flip-flop (E_D_FF_ANY), at the adapter plug `OUT`. This allows for the clean integration of network communication and INT signal processing in the AI adapter environment.

## Interface Structure

### **Event Inputs**

- **INIT** (EInit): Initialization event, associated with `QI` and `ID`
- **RSP** (Event): Response event, associated with `QI`

### **Event Outputs**

- **INITO** (EInit): Initialization confirmation, associated with `QO` and `STATUS`

### **Data Inputs**

- **QI** (BOOL): Qualifier input, activates the subscription service
- **ID** (WSTRING): Identifier of the publish channel to be subscribed to

### **Data Outputs**

- **QO** (BOOL): Qualifier output, status of the Block Execution
- **STATUS** (WSTRING): Status information as a Unicode string

### **Adapter**

| Adapter | Type | Direction | Description |
|---------|------------------------------|-----------|-----------------------------------------|
| OUT | adapter::types::unidirectional::AI | Plug (Output) | Buffered received INT value |

## Functionality

1. The internal `INIT` event initializes the internal `SUBSCRIBE_1` block with `QI` and `ID`. Upon success, it returns `INITO`.
2. The internal `SUBSCRIBE_1` block monitors the configured channel. As soon as the associated `PUBLISH_1` block publishes data, it generates the indication event `IND` and places the received value at `RD_1`.
3. `IND` clocks the internal **E_D_FF_ANY** flip-flop (`CLK`), which receives the value from `RD_1` at its data input `D`.
3. 4. The stored value appears stably at output `Q` and is transferred via the data connection to `OUT.D1` of the AX plug.
5. The event `EO` of the flip-flop is transferred to the event output `OUT.E1`, so that downstream components are notified of the new information.

## Technical Features

- **Buffering with D flip-flop**: The received INT value is buffered via an internal `iec61499::events::E_D_FF_ANY` and remains stable at the output until the next value is received. `EO` only fires when `Q` changes.
- **RSP is a no-op for subscribers**: According to source code analysis of `4diac-forte` (`CCommFB::sendData()`), the `RSP` event in `SUBSCRIBE_1` (service type subscriber) does not execute any action – the branch `!= e_Subscriber` is skipped. The event input pair `INIT`/`RSP` is only executed for acknowledgment and is non-functional for acknowledgment in the subscriber case. It is nevertheless routed externally to maintain a configurable connection.
- **Encapsulation**: The original event/data interface of `SUBSCRIBE_1` (including `IND`/`RD_1`) is moved internally; only the AI adapter interface is visible externally.

## State Overview

1. **Not Initialized**: The block is waiting for the `INIT` event.
2. **Initialized**: The subscription is active; the block is waiting for data from the publisher.
3. **Data Receipt**: At `IND`, the received INT value is transferred to the internal D flip-flop and output via `OUT`.

## Application Scenarios

- **Network Coupling in AI Applications**: Receiving INT signals (e.g., switching commands or status bits) via publish/subscribe and forwarding them via AI adapters to the adapter-based logic.
- **Event Storm Avoidance**: Together with `AX_PUBLISH_1` and a true event-based `E_D_FF_ANY`, the feedback between `SUBSCRIBE_1` and `PUBLISH_1` can be decoupled (a clean fix compared to the interim fix with `AX_D_FF`).
- **Modular Control Architectures**: Integration of distributed communication into libraries that consistently rely on AI adapters.

## Comparison with Similar Building Blocks

- **SUBSCRIBE_1**: The standard building block exposes its interface as events/variables (`IND`, `RD_1`, ...). **AI_SUBSCRIBE_1** encapsulates this building block, buffers the value with a D flip-flop (`E_D_FF_ANY`), and only provides the AI adapter – making the interface significantly more compact and integrable into adapter networks.
- **AX_D_FF**: Bufferes an INT value at the adapter level but lacks network functionality. **AI_SUBSCRIBE_1** combines subscribing and buffering in a single building block.

## Conclusion

**AI_SUBSCRIBE_1** combines the publish/subscribe communication of the standard function block `SUBSCRIBE_1` with adapter-based INT processing. Internal D flip-flop buffering keeps the received value stable until new data arrives, and the simplified AI interface makes the function block ideal for end-to-end adapter-based IEC 61499 applications.
