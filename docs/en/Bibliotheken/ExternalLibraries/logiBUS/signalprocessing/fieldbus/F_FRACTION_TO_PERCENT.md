# F_FRACTION_TO_PERCENT

![F_FRACTION_TO_PERCENT](./F_FRACTION_TO_PERCENT.svg)

* * * * * * * * * *

## Introduction

The function block **F_FRACTION_TO_PERCENT** is the counterpart to [`F_PERCENT_TO_FRACTION`](./F_PERCENT_TO_FRACTION.md): it converts a fraction (REAL 0.0–1.0), such as one delivered by `MyLib::sys::F_PWM_RAW_TO_PERCENT`, into a percent value (REAL 0.0–100.0), e.g. for sending to a web client via OPC-UA publish.

## Interface Structure

### **Event Inputs**

| Event | Data Type | Comment |
|----------|----------|-----------|
| REQ | Event | Request conversion; processes the current value of `rFraction`. |

### **Event Outputs**

| Event | Data Type | Comment |
|----------|----------|-----------|
| CNF | Event | Conversion complete; `rPercent` has been updated. |

### **Data Inputs**

| Name | Data Type | Comment |
|------|----------|-----------|
| rFraction | REAL | Fraction 0.0-1.0. |

### **Data Outputs**

| Name | Data Type | Comment |
|------|----------|-----------|
| rPercent | REAL | Percent value 0.0-100.0. |

### **Adapter**

None.

## Functionality

On each `REQ` event, the `rFraction` input is multiplied by 100 without clamping:

```structuredtext
rPercent := rFraction * 100.0;
```

The `CNF` event is then emitted.

## Technical Details

- Implemented as a **SimpleFB** with a single execution state (`REQ`) — no multi-step state machine.
- Unlike its counterpart `F_PERCENT_TO_FRACTION`, it does **not clamp** the input value: since `rFraction` is already bounded to 0.0-1.0 by `RampLimitFS`/`F_PWM_RAW_TO_PERCENT` earlier in the PWM chain, an additional range check is not needed here.
- Deliberately kept separate from `MyLib::sys::F_PWM_RAW_TO_PERCENT`, which converts the fieldbus raw value (not percent!) into a fraction — together, the two blocks form the complete fieldbus-raw-value → fraction → percent chain.
- License: Eclipse Public License 2.0.

## State Overview

| State | Action | Output Event |
|---------|--------|-----------------|
| REQ | Executes the **REQ** algorithm (multiplication by 100) | CNF |

There are no further waiting or initialization states.

## Application Scenarios

- Converting an internally processed fraction (0.0-1.0) back into the percent value expected by a web client via OPC-UA publish — e.g. in the PWM training example [`RampLimitFS_TO_logiBUS_QDA_PWM_OPC`](../../../../../Bibliotheken/ExternalLibraries/MyLib_AX/sys/RampLimitFS_TO_logiBUS_QDA_PWM_OPC.md).
- In general: any interface that computes internally with a normalized 0.0-1.0 fraction while communicating externally in percent.

## Comparison with Similar Blocks

- Its counterpart is [`F_PERCENT_TO_FRACTION`](./F_PERCENT_TO_FRACTION.md) (percent → fraction, for the forward direction, including clamping).
- The simplest conceivable scale converter with no range check at all, since the input is already guaranteed to arrive normalized.

## Conclusion

**F_FRACTION_TO_PERCENT** is a pure multiplication by 100 that brings the internally used 0.0-1.0 fraction to the externally communicated 0.0-100.0 percent value — without any error handling of its own, since the input is already pre-normalized.

## 🛠️ Related Exercises

- [RampLimitFS_TO_logiBUS_QDA_PWM_OPC](../../../../../Bibliotheken/ExternalLibraries/MyLib_AX/sys/RampLimitFS_TO_logiBUS_QDA_PWM_OPC.md)
- [InputOutputTesterButton_PWM_OPC_UA](../../../../../Uebungen/test_AX/Meins/InputOutputTester/Button_PWM_OPC_UA/InputOutputTesterButton_PWM_OPC_UA.md)

---

### 🌐 Related topic pages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
