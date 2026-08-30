# F_PERCENT_TO_FRACTION

![F_PERCENT_TO_FRACTION](./F_PERCENT_TO_FRACTION.svg)

* * * * * * * * * *
## Introduction

The function block **F_PERCENT_TO_FRACTION** converts a percent value (REAL 0.0–100.0), such as one received via OPC-UA subscribe from a web client, into a fraction (REAL 0.0–1.0) as expected as input by `MyLib::sys::F_PWM_PERCENT_TO_RAW`. Values outside the valid range are clamped instead of producing an error.

## Interface Structure

### **Event Inputs**

| Event | Data Type | Comment |
|----------|----------|-----------|
| REQ | Event | Request conversion; processes the current value of `rPercent`. |

### **Event Outputs**

| Event | Data Type | Comment |
|----------|----------|-----------|
| CNF | Event | Conversion complete; `rFraction` has been updated. |

### **Data Inputs**

| Name | Data Type | Comment |
|------|----------|-----------|
| rPercent | REAL | Percent value, clamped to 0.0-100.0. |

### **Data Outputs**

| Name | Data Type | Comment |
|------|----------|-----------|
| rFraction | REAL | Fraction 0.0-1.0. |

### **Adapter**

None.

## Functionality

On each `REQ` event, the `rPercent` input is checked and clamped to the valid range:

```structuredtext
IF rPercent <= 0.0 THEN
    rFraction := 0.0;
ELSIF rPercent >= 100.0 THEN
    rFraction := 1.0;
ELSE
    rFraction := rPercent / 100.0;
END_IF;
```

- Values `<= 0.0` yield `rFraction = 0.0`, values `>= 100.0` yield `rFraction = 1.0`.
- All other values are divided linearly by 100.
- The `CNF` event is then emitted.

## Technical Details

- Implemented as a **SimpleFB** with a single execution state (`REQ`) — no multi-step state machine.
- Clamps instead of error-handling: implausible percent values (e.g. from faulty web input) do not trigger an error state but are silently limited to 0-100 %.
- Deliberately kept separate from `MyLib::sys::F_PWM_PERCENT_TO_RAW`, which converts a fraction (not percent!) into the fieldbus raw value — together, the two blocks form the complete percent → fraction → fieldbus-raw-value chain.
- License: Eclipse Public License 2.0.

## State Overview

| State | Action | Output Event |
|---------|--------|-----------------|
| REQ | Executes the **REQ** algorithm (clamping + division by 100) | CNF |

There are no further waiting or initialization states.

## Application Scenarios

- Converting a web setpoint received via OPC-UA subscribe (percent REAL) into the fraction expected by internal fieldbus conversion blocks — e.g. in the PWM training example [`RampLimitFS_TO_logiBUS_QDA_PWM_OPC`](../../../../../Bibliotheken/typelibrary/MyLib_AX/sys/RampLimitFS_TO_logiBUS_QDA_PWM_OPC.md).
- In general: any interface that communicates externally in percent while computing internally with a normalized 0.0-1.0 fraction.

## Comparison with Similar Blocks

- Its counterpart is [`F_FRACTION_TO_PERCENT`](./F_FRACTION_TO_PERCENT.md) (fraction → percent, for the reverse direction).
- Unlike the `FIELDBUS_*_TO_SIGNAL` blocks (e.g. `FIELDBUS_BYTE_TO_SIGNAL`), this block does not validate against a constant but performs a pure, clamping scale conversion.

## Conclusion

**F_PERCENT_TO_FRACTION** is a minimal, clamping scale converter that bridges the gap between the externally communicated percent value and the internally used 0.0-1.0 fraction — without any error handling of its own, since out-of-range values are simply clamped.

## 🛠️ Related Exercises

* [RampLimitFS_TO_logiBUS_QDA_PWM_OPC](../../../../../Bibliotheken/typelibrary/MyLib_AX/sys/RampLimitFS_TO_logiBUS_QDA_PWM_OPC.md)
* [InputOutputTesterButton_PWM_OPC_UA](../../../../../Uebungen/test_AX/Meins/InputOutputTester/Button_PWM_OPC_UA/InputOutputTesterButton_PWM_OPC_UA.md)

---

### 🌐 Related topic pages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
