# AX_RF_TRIG

![AX_RF_TRIG](./AX_RF_TRIG.svg)

* * * * * * * * * *

## Introduction

The function block **AX_RF_TRIG** is used to detect rising and falling edges of a Boolean signal. It receives the signal value via an adapter and outputs corresponding events when an edge changes. The block encapsulates the standard logic of IEC 61499 edge detection (E_RF_TRIG) and provides it via a uniform adapter interface.

## Interface Structure

### **Event Inputs**

The block does not have direct event inputs. Edge detection is triggered by the connected adapter (see Adapter).

## **Event Outputs**

| Name | Comment |
| ------ | ----------- |
| ER | Confirmation that a rising edge (0→1) has been detected. |
| EF | Confirmation that a falling edge (1→0) has been detected. |

#### **Data Inputs**

No direct data inputs. The Boolean value to be monitored is provided via the adapter.

#### **Data Outputs**

No data outputs.

#### **Adapter**

| Name | Type | Comment |
|------|-----|-----------|
| QI | adapter::types::unidirectional::AX | Receives the Boolean value whose edges are to be monitored. The adapter provides both an event (E1) and the data value (D1). |

## Functionality

The function block internally uses the IEC 61499 standard function block **E_RF_TRIG**. The adapter **QI** queries the current Boolean data value for each incoming event. If the value changes, the internal function block generates an event:

- **ER** on a transition from *false* to *true* (rising edge).
- **EF** on a transition from *true* to *false* (falling edge).

No output events are sent without an edge change.

## Technical Features

- The function block is implemented as a pure adapter wrapper. It does not have its own state machine but delegates all logic to the standardized **E_RF_TRIG**.
- The use of an adapter type (here **AX**) enables loose coupling between the signal source and edge detection. The adapter can be reused in different contexts.
- Only event outputs are provided; the current signal value is not passed on as a data output.

## State Overview

This function block does not have an explicitly defined state machine. Its behavior corresponds to that of the internal **E_RF_TRIG**, which stores an implicit state (last value). Essentially, two phases can be distinguished:

1. **Waiting for rising edge:** the last value was *false*; if *true*, ER is triggered.
2. **Waiting for falling edge:** the last value was *true*; if *false*, EF is triggered.

## Application Scenarios

- Monitoring of binary sensor signals (e.g., limit switches, light barriers) in automation technology.
- Triggering actions upon signal changes (e.g., starting/stopping a machine).
- Event-driven processing of Boolean states in industrial control systems.

## Comparison with Similar Function Blocks

- **E_RF_TRIG:** The standard function block of IEC 61499. **AX_RF_TRIG** encapsulates this and provides an adapter interface, so the signal source does not need to be directly bound to the function block.
- **R_TRIG** / **F_TRIG:** Detect only one edge direction. **AX_RF_TRIG** detects both directions and outputs corresponding events.
- **Adapter-Based Alternatives:** Other adapter types with similar semantics can also be used for edge detection, provided they supply the Boolean value and an event.

## Conclusion

The **AX_RF_TRIG** function block represents a practical, adapter-based solution for detecting both edges of a Boolean signal. By using the standard function block **E_RF_TRIG**, the function is robust and standards-compliant. The adapter interface facilitates integration into modular systems where signal sources and processing logic need to be decoupled.
