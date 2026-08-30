# SystemTickSender

![SystemTickSender_network](./SystemTickSender_network.svg)

* * * * * * * * * *
## Introduction

`SystemTickSender` provides a cyclically incrementing "heartbeat" for the VT and web client — a simple, immediately visible confirmation that the controller is running and processing events. The block is used in several training examples in this system, including [`InputOutputTesterButton_DIDO_OPC_UA`](../../../../Uebungen/test_AX/Meins/InputOutputTester/Button_DIDO_OPC_UA/InputOutputTesterButton_DIDO_OPC_UA.md) and [`InputOutputTesterButton_PWM_OPC_UA`](../../../../Uebungen/test_AX/Meins/InputOutputTester/Button_PWM_OPC_UA/InputOutputTesterButton_PWM_OPC_UA.md).

## Function Blocks (FBs) Used

### Sub-blocks: SystemTickSender

- **Type**: SubAppType
- **Internal FBs used**:
    - **System_Tick** (SubApp, `MyLib::sys`): provides a cyclically incrementing value as an `ADI` adapter (DINT).
    - **ADI_SPLIT_2**: `adapter::events::unidirectional::ADI_SPLIT_2` — splits the counter adapter into two directions.
    - **ADI_TO_AUDI**: `adapter::conversion::unidirectional::ADI_TO_AUDI` — converts a DINT adapter to a UDINT adapter (numerically correct, see [Numeric vs. bitwise](../../../../Bibliotheken/ExternalLibraries/adapter/conversion/unidirectional/Numeric_vs_Bitwise.md): `ANY_INT`→`ANY_INT` is a safe cast).
    - **Q_NumericValue_AUDI**: `isobus::UT::Q::Q_NumericValue_AUDI` — writes the counter value into a VT number field.
    - **ADI_PUBLISH_1**: `adapter::net::ADI_PUBLISH_1` — OPC-UA publish of the raw DINT counter value to the web client.
- **Functionality**: The internally generated counter is used once for the VT display (via a UDINT intermediate step, since `Q_NumericValue_AUDI` expects that type) and once raw as DINT for OPC-UA publish.

## Program Flow and Connections

1. `System_Tick.ADI_OUT` → `ADI_SPLIT_2.IN`.
2. `ADI_SPLIT_2.OUT1` → `ADI_TO_AUDI.ADI_IN` → `ADI_TO_AUDI.AUDI_OUT` → `Q_NumericValue_AUDI.u32NewValue` (VT display).
3. `ADI_SPLIT_2.OUT2` → `ADI_PUBLISH_1.IN` (OPC-UA publish).
4. Parameters: `u16ObjId` → `Q_NumericValue_AUDI.u16ObjId`; `ID_WRITE` → `ADI_PUBLISH_1.ID`.

## Technical Details

- **Two parallel uses of the same counter**: VT display (via `ADI_TO_AUDI`, since `Q_NumericValue_AUDI` expects a UDINT adapter) and OPC-UA publish (directly as DINT) run independently via `ADI_SPLIT_2`.
- **Numerically correct conversion**: `ADI_TO_AUDI` (DINT→UDINT) is an `ANY_INT`→`ANY_INT` cast, not a bit-reinterpretation trap like e.g. [`AD_TO_AR`](../../../../Bibliotheken/ExternalLibraries/adapter/conversion/unidirectional/AD_AR/AD_TO_AR.md).

## Application Scenarios

- "Heartbeat" display on the VT and web UI to show at a glance that the controller is active and hasn't crashed or frozen.

## Summary

`SystemTickSender` is a simple but widely reused block across almost every training example in this system, distributing a cyclic counter value in parallel to a VT number field and an OPC-UA web client — a minimal but effective heartbeat for the controller.

## 🛠️ Related Exercises

* [InputOutputTesterButton_DIDO_OPC_UA](../../../../Uebungen/test_AX/Meins/InputOutputTester/Button_DIDO_OPC_UA/InputOutputTesterButton_DIDO_OPC_UA.md)
* [InputOutputTesterButton_PWM_OPC_UA](../../../../Uebungen/test_AX/Meins/InputOutputTester/Button_PWM_OPC_UA/InputOutputTesterButton_PWM_OPC_UA.md)

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
