# InputOutputTesterButton_DIDO_OPC_UA: DIDO Tester (OPC-UA)

![InputOutputTesterButton_DIDO_OPC_UA_network](./InputOutputTesterButton_DIDO_OPC_UA_network.svg)

* * * * * * * * * *

## Introduction

`InputOutputTesterButton_DIDO_OPC_UA` is the foundational training example for **8 digital inputs and 12 digital outputs**, controllable both via the ISOBUS Virtual Terminal and via OPC-UA (web client). It is the purely digital counterpart to the later PWM example [`InputOutputTesterButton_PWM_OPC_UA`](../Button_PWM_OPC_UA/InputOutputTesterButton_PWM_OPC_UA.md) — whose 8 inputs were carried over unchanged from this DIDO example, while its 12 purely digital outputs are replaced there by 12 PWM channels.

The exercise is a pure top-level composite: it instantiates 8 input blocks, 12 output blocks, and one `SystemTickSender`, without containing any logic of its own — the actual wiring (VT display, OPC-UA publish/subscribe, feedback-loop decoupling) lives entirely in the reusable sub-blocks.

## Function Blocks (FBs) Used

| SubApp instance | Type | Purpose |
|---|---|---|
| `Input_I1` … `Input_I8` | `MyLib::sys::logiBUS_IXA_BG_OPC` | Digital input with VT status display (green/white) and OPC-UA publish |
| `Output_Q1` … `Output_Q12` | `MyLib::sys::Button_IXA_TO_logiBUS_QXA_BG_OPC` | Digital output, switchable bidirectionally via VT button AND OPC-UA |
| `SystemTickSender` | `MyLib::sys::SystemTickSender` | Cyclic counter feeding the VT status display (`OutputNumber_Tick`) |

### Sub-block: [logiBUS_IXA_BG_OPC](../../../../../Bibliotheken/ExternalLibraries/MyLib_AX/sys/logiBUS_IXA_BG_OPC.md) (inputs)

- **Type**: SubAppType (`MyLib::sys`)
- **Functionality**: Reads a physical digital input (`logiBUS_IXA`) and splits the adapter signal via `AX_SPLIT_2` into two directions: to `GreenWhiteBackground1_AX` (VT background color green/white based on state) and to `AX_PUBLISH_1` (OPC-UA publish to the web client). Purely one-way data flow physical → VT/web, no write-back path from the web (inputs cannot be set externally).

### Sub-block: [Button_IXA_TO_logiBUS_QXA_BG_OPC](../../../../../Bibliotheken/ExternalLibraries/MyLib_AX/sys/Button_IXA_TO_logiBUS_QXA_BG_OPC.md) (outputs)

- **Type**: SubAppType (`MyLib::sys`)
- **Functionality**: Unlike the inputs, an output can be switched **from two sides** — via a VT button (`Button_IXA`) or via an OPC-UA write (`AX_SUBSCRIBE_1`). Both sources run through their own `AX_RF_TRIG` (edge detection) into a shared `AX_SR` flip-flop (set/reset), whose output is distributed three ways via `AX_SPLIT_3`: to the physical output (`logiBUS_QXA`), to the VT status color (`GreenWhiteBackground1_AX`), and back to `AX_PUBLISH_1` (OPC-UA echo, so the web client sees the actual state).
- **Known pitfall in the OPC-UA feedback loop**: Since `AX_PUBLISH_1` and `AX_SUBSCRIBE_1` serve the same OPC-UA node, a naive wiring would create an event storm (every own publish looks like an external change to the own subscribe). The `AX_SR` flip-flop decouples this feedback by only forwarding real state changes (set/reset instead of a direct pass-through). See `NOTIZ_RSP_und_EventStorm.md` in the source repository for details — including the finding that `SUBSCRIBE_1`'s `RSP` event input is a complete no-op from FORTE's source-code perspective (only inherited from the shared `CCommFB` base class, but never effective for the *Subscriber* service type).

## OPC-UA Address Space

Unlike the later, nested PWM address space, DIDO uses flat nodes separated by signal type:

| Node path | Node ID | Meaning |
|---|---|---|
| `/Objects/DigitalInput/In` | `s=In` | Input n (n=1–8), publish only (read-only for the client) |
| `/Objects/DigitalOutput/Qnn` | `s=Qnn` | Output nn (nn=01–12), read (subscribe) + write (publish/echo) |

## Program Flow and Connections

The exercise itself contains **no connections** (`SubAppNetwork` consists only of SubApp instances with parameters) — as with the PWM example, all logic lives in the sub-blocks:

1. **8 inputs**: `Input_I1`…`Input_I8` read `Input_I1`…`Input_I8` and mirror them via VT status color and OPC-UA publish (`I1_WRITE`…`I8_WRITE`).
2. **12 outputs**: `Output_Q1`…`Output_Q12` each connect one physical output (`Output_Q1`…`Output_Q12`) to a VT button, VT status color, and bidirectional OPC-UA access (`Q01_READ`…`Q12_READ` for web writes, `Q01_WRITE`…`Q12_WRITE` as echo).
3. **Tick generator**: `SystemTickSender` counts up cyclically and feeds the VT number field `OutputNumber_Tick` as well as the OPC-UA node `Tick_WRITE`.

**Registration in the training system**: As with all exercises in this system, no dedicated `Application` element is needed — selected via "Change Type" in the 4diac IDE on the system's single `Control` slot.

## Learning Objectives

- Basic pattern for digital inputs/outputs with **both** VT and OPC-UA connectivity, before analog channels (PWM) are added.
- Difference between pure publish (inputs, a single data source) and bidirectional subscribe/publish (outputs, two competing write sources: VT button and web).
- Avoiding OPC-UA feedback loops when publish and subscribe serve the same node — a pattern that recurs in every bidirectionally connected block in this training system (compare `RampLimitFS_TO_logiBUS_QDA_PWM_OPC` in the PWM example, which solves the same challenge for the channel switch).

**Difficulty**: Beginner to intermediate
**Prerequisites**: Basics of the logiBUS digital I/O blocks (`logiBUS_IXA`, `logiBUS_QXA`), OPC-UA adapters (`AX_SUBSCRIBE_1`/`AX_PUBLISH_1`).

## Summary

`InputOutputTesterButton_DIDO_OPC_UA` demonstrates the basic pattern for digital I/O with parallel VT and OPC-UA control: inputs as a pure publish path, outputs as a bidirectional subscribe/publish path with clean feedback-loop decoupling via a set/reset flip-flop. This pattern — especially the feedback-loop avoidance — is the template for all later, more complex training examples in this system (DIDO → PWM → AI).

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
