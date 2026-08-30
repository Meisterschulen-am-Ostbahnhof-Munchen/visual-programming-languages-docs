# Button_IXA_TO_logiBUS_QXA_BG_OPC

![Button_IXA_TO_logiBUS_QXA_BG_OPC_network](./Button_IXA_TO_logiBUS_QXA_BG_OPC_network.svg)

* * * * * * * * * *
## Introduction

`Button_IXA_TO_logiBUS_QXA_BG_OPC` is the reusable block for **a single digital output** that can be switched both via a VT button and via OPC-UA (web client) — including a VT status display. It is instantiated 12 times with different parameters in [`InputOutputTesterButton_DIDO_OPC_UA`](../../../../Uebungen/test_AX/Meins/InputOutputTester/Button_DIDO_OPC_UA/InputOutputTesterButton_DIDO_OPC_UA.md).

## Function Blocks (FBs) Used

### Sub-blocks: Button_IXA_TO_logiBUS_QXA_BG_OPC

- **Type**: SubAppType
- **Internal FBs used**:
    - **Button_IXA**: `isobus::UT::io::Button::Button_IXA` — VT button, `QI=TRUE`, `u16ObjId` identifies the VT button.
    - **AX_RF_TRIG_BT** / **AX_RF_TRIG_OPC**: each `adapter::events::unidirectional::AX_RF_TRIG` — detect real edge changes (rising `ER`/falling `EF`) on the VT button and on the OPC-UA subscribe value respectively, instead of blindly passing every value through.
    - **AX_SR**: `adapter::events::unidirectional::AX_SR` — shared set/reset flip-flop for both sources; decouples the feedback loop between publish and subscribe (see Technical Details).
    - **AX_SPLIT_3**: `adapter::events::unidirectional::AX_SPLIT_3` — distributes the flip-flop's output to three destinations.
    - **logiBUS_QXA**: `logiBUS::io::DQ::logiBUS_QXA` — physical digital output, `QI=TRUE`.
    - **GreenWhiteBackground1_AX** (SubApp, `MyLib::sys`): VT background color matching the output state.
    - **AX_SUBSCRIBE_1** / **AX_PUBLISH_1**: `adapter::net::AX_SUBSCRIBE_1`/`AX_PUBLISH_1` — OPC-UA read/write access, both `QI=TRUE`.
- **Functionality**: Two independent switching sources (VT button, OPC-UA write) are each routed through edge detection into a shared set/reset flip-flop, whose output simultaneously feeds the physical output, the VT status color, and the OPC-UA echo.

## Program Flow and Connections

1. **VT button path**: `Button_IXA.IN` (adapter) → `AX_RF_TRIG_BT.QI` → `AX_RF_TRIG_BT.ER`/`.EF` → `AX_SR.S`/`.R`.
2. **OPC-UA path**: `AX_SUBSCRIBE_1.OUT` (adapter, web write) → `AX_RF_TRIG_OPC.QI` → `AX_RF_TRIG_OPC.ER`/`.EF` → `AX_SR.S`/`.R`.
3. **Shared state**: `AX_SR.Q` → `AX_SPLIT_3.IN` → `AX_SPLIT_3.OUT1` → `logiBUS_QXA.OUT` (physical output), `AX_SPLIT_3.OUT2` → `GreenWhiteBackground1_AX.DI1` (VT status color), `AX_SPLIT_3.OUT3` → `AX_PUBLISH_1.IN` (OPC-UA echo to the web client).
4. **Initialization chain**: `AX_SUBSCRIBE_1.INITO` → `AX_PUBLISH_1.INIT` (hidden connection) — ensures the publish adapter is only initialized after the subscribe adapter is ready.
5. **Parameters**: `u16ObjId` → `Button_IXA.u16ObjId` and `GreenWhiteBackground1_AX.u16ObjId`; `Output` → `logiBUS_QXA.Output`; `ID_READ` → `AX_SUBSCRIBE_1.ID`; `ID_WRITE` → `AX_PUBLISH_1.ID`.

## Technical Details

- **Edge detection instead of value pass-through**: `AX_RF_TRIG` ensures that only real state changes (not every write with the same value) trigger the flip-flop — important so repeated OPC-UA writes with an unchanged value don't accidentally toggle the output.
- **⚠️ Avoiding an OPC-UA feedback loop**: `AX_PUBLISH_1` and `AX_SUBSCRIBE_1` serve the same OPC-UA node. A naive wiring (passing the subscribe value directly to publish) would create an event storm: every own publish looks like an external change to the own subscribe and triggers another indication. The `AX_SR` flip-flop breaks this loop by only reacting to real set/reset edge events, not to the value passing through.
- **`AX_SUBSCRIBE_1`'s `RSP` event is a no-op**: verified in FORTE source (`CCommFB::sendData()`, `commfb.cpp`) — for the *Subscriber* service type, the `RSP` branch is a complete no-op; the `INIT`/`RSP` event pair only exists because `CCommFB` is the shared base class for all "responder"-style service FBs (e.g. `SERVER`, where `RSP` does trigger something real).
- **Boot order**: `AX_SUBSCRIBE_1.INITO` triggers `AX_PUBLISH_1.INIT` to avoid race conditions at deployment (compare the same pattern in the PWM example's `RampLimitFS_TO_logiBUS_QDA_PWM_OPC`).

## Application Scenarios

- Any digital output that needs to be switchable both locally (VT button) and remotely (web/OPC-UA), without the two control paths interfering with each other or creating a feedback loop.

## Comparison with Similar Function Blocks

Compared to its input counterpart [`logiBUS_IXA_BG_OPC`](./logiBUS_IXA_BG_OPC.md), this block adds the second write source (OPC-UA subscribe) as well as the edge-detection/flip-flop chain for feedback-loop avoidance — an input has only one data source (the physical hardware) and doesn't need this decoupling.

## Summary

`Button_IXA_TO_logiBUS_QXA_BG_OPC` solves the fundamental problem of bidirectionally connecting a digital output via OPC-UA: two competing write sources (VT button, web) are routed through edge detection into a shared flip-flop, whose state is then safely — without a feedback loop — distributed to hardware, VT display, and OPC-UA echo. This pattern is the template for every later bidirectionally connected block in this training system.

## 🛠️ Related Exercises

* [InputOutputTesterButton_DIDO_OPC_UA](../../../../Uebungen/test_AX/Meins/InputOutputTester/Button_DIDO_OPC_UA/InputOutputTesterButton_DIDO_OPC_UA.md)

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
