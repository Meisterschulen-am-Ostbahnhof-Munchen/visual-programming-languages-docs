# logiBUS_AI_Calibrate_IDA_OPC

![logiBUS_AI_Calibrate_IDA_OPC_network](./logiBUS_AI_Calibrate_IDA_OPC_network.svg)

* * * * * * * * * *

## Introduction

`logiBUS_AI_Calibrate_IDA_OPC` connects a physical analog input (`logiBUS_AI_IDA`) to a full VT- and OPC-UA-backed 2-point calibration (`AR_CALIBRATE_SQ_REF`) - used by the [AI_Calibrate training sample](../../../../Uebungen/test_AX/Meins/InputOutputTester/Button_AI_Calibrate_OPC_UA/InputOutputTesterButton_AI_Calibrate_OPC_UA.md). The input's raw value is converted into a physically scaled value through the calibration adapter chain; zero point (`ZERO`) and span (`SPAN`) are adjustable both via the VT and via OPC-UA, and are persisted in an INI file.

## Function blocks used

- **logiBUS_AI_IDA** (`logiBUS::io::AI::logiBUS_AI_IDA`): physical analog input, provides the raw value as an adapter.
- **AR_CALIBRATE_SQ_REF** (adapter composite): 2-point calibration (zero/span) with reference-value support - converts the raw value into the physically scaled, calibrated value.
- **VT and OPC-UA bridges** (analogous to [`NumericValue_TO_AR2_OPC`](./NumericValue_TO_AR2_OPC.md)/[`OPC_TO_AR2`](./OPC_TO_AR2.md) and [`INI_IN_AND_STORE_AR2`](./INI_IN_AND_STORE_AR2.md)): expose `ZERO`/`SPAN` both via VT input fields and via OPC-UA, and persist the calibration values in an INI file.

## Summary

Complete calibration block for a physical analog input: raw-value acquisition, 2-point calibration, VT display/input, and OPC-UA connectivity in one composite - the core block of the AI_Calibrate sample.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
