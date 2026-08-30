# AR2

![AR2](./AR2.svg)

* * * * * * * * * *

## Introduction

The **AR2** adapter type provides a bidirectional interface between two function blocks. It transmits exactly one event along with a REAL value in both directions. The designation "AR2" stands for "Adapter Real 2-Way". The component is designed as a generic connector (plug/socket) within the 4diac IDE and enables clean, type-safe coupling of components.

## Interface Structure

### **Event Inputs**

| Name | Type | Comment | with data |
|------|-----|-----------|-----------|
| EI1 | Event | Request (or Indication) | DI1 |

### **Event Outputs**

| Name | Type | Comment | with data |
|------|-----|-----------|-----------|
| EO1 | Event | Indication (or Request) | DO1 |

### **Data Inputs**

| Name | Data Type | Comment |
|------|----------|-----------|
| DI1 | REAL | Request (or Indication) to Socket |

### **Data Outputs**

| Name | Data Type | Comment |
|------|----------|-----------|
| DO1 | REAL | Indication (or Request) Data from Plug |

### **Adapter**

None defined.

## Functionality

The AR2 adapter operates in an event-driven and bidirectional manner:

- When the event input **EI1** is triggered, the current REAL value at **DI1** is transmitted to the opposite end of the adapter. There, the event **EO1** appears along with the value at **DO1**.
- The same applies in the opposite direction: If the connected counterpart adapter triggers its event, this AR2 receives the event at **EI1** and makes the received value available at **DI1**.

The comments "Request (or Indication)" and "Indication (or Request)" clarify that, depending on the installation situation (plug or socket), the adapter can assume the role of a requesting or indicating channel. Therefore, AR2 is suitable for both master/slave and peer-to-peer communication.

## Technical Features

- **Typed Data Transmission:** Only the **REAL** data type is supported, which provides clear semantics for physical measured values or control variables.
- **Bidirectionality:** A single adapter enables data exchange in both directions, reducing the number of required interfaces.
- **Versioning:** The module is in version 1.0, developed by HR Agrartechnik GmbH (Copyright 2026, EPL 2.0).
- **Compiler Information:** The package is located at `adapter::types::bidirectional` and uses a type hash (`eclipse4diac::core::TypeHash`) for integrity checks.
- **No State Machine:** The adapter itself does not have its own state logic; it functions purely as a connection between two event/data pairs.

## State Overview

The AR2 adapter does not implement an explicit state machine. Data flows without delay or intermediate storage when events occur – the signals are passed directly from input to output.

## Application Scenarios

- **Sensor Value Transmission:** A function block acquires an analog sensor value (e.g., temperature, pressure) and sends it to an evaluation block via AR2. Simultaneously, the evaluation block can return a setpoint in the opposite direction.
- **Control Coupling:** In a modular control system, AR2 connects a PID controller to an actuator. The controller sends the manipulated value (REAL) and simultaneously receives the current control deviation.
- **Parameterization:** Configuration parameters (e.g., limit values) can be exchanged between an operator panel and the control logic via AR2.

## Comparison with Similar Modules

- **AR1 (Unidirectional):** An adapter that transmits data in only one direction. AR2, on the other hand, enables bidirectional exchange, which reduces cabling requirements.
- **AE2 (Adapter Event 2-Way):** Transmits two events, but no data. AR2 combines an event with a REAL value – ideal for value-based communication.
- **AR4 (Adapter Real 4-Way):** Offers four independent REAL channels. AR2 is more compact when only one value is needed.

## Conclusion

The AR2 adapter is an elegant component for the bidirectional transmission of a REAL value with its associated event. Its clear interface and ease of use make it particularly suitable for modular automation solutions where measurement data or control variables need to be exchanged between function blocks. By complying with the 61499 standard and being licensed under EPL 2.0, AR2 is open and extensible.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
