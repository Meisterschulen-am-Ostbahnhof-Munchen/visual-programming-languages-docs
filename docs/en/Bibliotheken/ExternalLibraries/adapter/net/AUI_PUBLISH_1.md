# AUI_PUBLISH_1

![AUI_PUBLISH_1](./AUI_PUBLISH_1.svg)

* * * * * * * * * *

## Introduction
The function block **AUI_PUBLISH_1** is a composite function block that encapsulates the network-based `PUBLISH_1` function block from the IEC 61499 standard library and maps its interface to a unidirectional **AUI adapter**. A **UINT** value present at the adapter socket `IN` is buffered via an internal D flip-flop (E_D_FF_ANY) and then sent to all associated `SUBSCRIBE_1` receivers via the configured publish channel.



 ## Interface Structure

### **Event Inputs**

- **INIT** (EInit): Initialization event, associated with `QI` and `ID`

### **Event Outputs**

- **INITO** (EInit): Initialization confirmation, associated with `QO` and `STATUS`

- **CNF** (Event): Confirmation that data has been sent, associated with `QO` and `STATUS`

### **Data Inputs**

- **QI** (BOOL): Qualifier input, activates the publish service

- **ID** (WSTRING): Publish channel identifier

### **Data Outputs**

- **QO** (BOOL): Qualifier output, block execution status

- **STATUS** (WSTRING): Status information as a Unicode string

### **Adapter**

| Adapter | Type | Direction | Description |

|---------|------------------------------|-----------|---------------------------------|

| IN | adapter::types::unidirectional::AUI | Socket (Input) | UINT value to be published |

## Functionality

1. The internal `PUBLISH_1` block is initialized with `QI` and `ID` via the `INIT` event. Upon success, it returns `INITO`.


 2. As soon as the AUI socket `IN` sends an event to `IN.E1`, the UINT value simultaneously present at `IN.D1` is transferred to the internal **E_D_FF_ANY** flip-flop (`CLK` or `D`).

3. The flip-flop holds the value stably at its output `Q` and generates the event `EO` when the value changes.

4. `EO` triggers the send event `REQ` of the internal `PUBLISH_1` block. The buffered value `Q` is transmitted over the data connection as `SD_1` and published on the configured channel.

5. After successful transmission, the `PUBLISH_1` block confirms with `CNF`, which is then transmitted externally.

## Technical Features
- **Buffering with D-Flip-Flop**: The UINT value to be transmitted is buffered via an internal `iec61499::events::E_D_FF_ANY`. This prevents a changing input value during processing from interfering with the transmission.

- **Event-based decoupling**: The true event-based `E_D_FF_ANY` decouples immediate feedback loops between `PUBLISH_1` and `SUBSCRIBE_1` (e.g., on the same OPC UA node) – a clean fix compared to the interim fix with `AX_D_FF`.

- **Encapsulation**: The original event/data interface of `PUBLISH_1` (including `REQ`/`SD_1`) is moved internally; only the AUI adapter interface is visible externally.


## State Overview

1. **Not Initialized**: The block is waiting for the `INIT` event.

2. **Initialized**: The block is ready to publish data via the configured channel.

3. **Send Active**: An event arriving at the AUI socket buffers the value and triggers transmission via the internal `PUBLISH_1` block.

## Application Scenarios

- **Network Coupling in AUI Applications**: Sending UINT signals (e.g., switching commands or status bits) from adapter-based logic to remote receivers via publish/subscribe.

- **Event Storm Avoidance**: Together with `AX_SUBSCRIBE_1`, feedback between your own publications and your own subscription is decoupled.

- **Modular Control Architectures**: Integration of distributed communication into libraries that consistently rely on AUI adapters.

## Comparison with Similar Blocks

- **PUBLISH_1**: The standard block exposes its interface as events/variables (`REQ`, `SD_1`, ...). **AUI_PUBLISH_1** encapsulates this block, buffers the value with a D flip-flop (`E_D_FF_ANY`), and only provides the AUI adapter – making the interface significantly more compact and integrable into adapter networks.

- **AX_D_FF**: Bufferes a UINT value at the adapter level but lacks network functionality. **AUI_PUBLISH_1** combines buffering and publishing in a single block.


## Conclusion

**AUI_PUBLISH_1** combines the publish/subscribe communication of the standard function block `PUBLISH_1` with adapter-based UINT processing. Internal D flip-flop buffering stabilizes the transmitted value and decouples feedback loops; the simplified AUI interface makes the function block ideal for fully adapter-based IEC 61499 applications.

