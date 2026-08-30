# SystemTickSender

![SystemTickSender_network](./SystemTickSender_network.svg)

* * * * * * * * * *
## Introduction

`SystemTickSender` combines the heartbeat counter [`System_Tick`](./System_Tick.md) with a VT numeric-field display and an OPC-UA publication: the 200 ms counter value is shown locally on the VT and also reported externally — useful for an upstream SCADA system to detect that the controller is actively cycling.

## Function Blocks Used

### Sub-blocks: SystemTickSender

- **Type**: SubAppType
- **Internal FBs used**:
    - **System_Tick** (SubApp): `MyLib::sys::System_Tick` — autonomous 200 ms heartbeat counter (see [System_Tick](./System_Tick.md)), provides the counter value as an `ADI` adapter (DINT).
    - **ADI_SPLIT_2**: `adapter::events::unidirectional::ADI_SPLIT_2` — splits the DINT adapter value into two outputs.
    - **ADI_TO_AUDI**: `adapter::conversion::unidirectional::ADI_TO_AUDI` — converts the DINT value to UDINT for the VT numeric field.
    - **Q_NumericValue_AUDI**: `isobus::UT::Q::Q_NumericValue_AUDI` — writes the counter value into the VT numeric field `u16ObjId`.
    - **ADI_PUBLISH_1**: `adapter::net::ADI_PUBLISH_1` — publishes the counter value (DINT) via OPC-UA, target address `ID_WRITE`, `QI=TRUE`.
- **Operation**: The heartbeat counter is split via `ADI_SPLIT_2`: one branch goes via `ADI_TO_AUDI` to the VT numeric field, the other directly to the OPC-UA publication.

## Program Flow and Connections

1. `u16ObjId` → `Q_NumericValue_AUDI.u16ObjId`; `ID_WRITE` → `ADI_PUBLISH_1.ID`.
2. `System_Tick.ADI_OUT` (adapter) → `ADI_SPLIT_2.IN` (adapter).
3. `ADI_SPLIT_2.OUT1` → `ADI_TO_AUDI.ADI_IN`; `ADI_TO_AUDI.AUDI_OUT` → `Q_NumericValue_AUDI.u32NewValue` (VT branch).
4. `ADI_SPLIT_2.OUT2` → `ADI_PUBLISH_1.IN` (OPC-UA branch).

## Application Scenarios

- A visible heartbeat signal for the plant operator on the VT and, at the same time, for an upstream SCADA system via OPC-UA, to confirm the controller is actively running (liveness monitoring).

## Summary

Combines the autonomous `System_Tick` heartbeat counter with VT display and OPC-UA publication into a fully visible liveness signal.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
