# OFF_TO_AX

![AUS_TO_AX](./AUS_TO_AX.svg)

* * * * * * * * * *
## Introduction

The function block **OFF_TO_AX** is a composite FB for converting an **OFF** adapter (USINT data) into an **AX** adapter (BOOL data).
It compares the incoming USINT value with zero and outputs the result as a Boolean signal. This enables the simple conversion of counter or sensor data into a binary status signal.
## Interface Structure

The FB does not offer direct event or data connections, but only adapter interfaces.

### **Event Inputs**

No direct event inputs. The event signal is provided via the **OFF_IN.E1** adapter.

### **Event Outputs**

No direct event outputs. The event signal is output via the **AX_OUT.E1** adapter.

### **Data Inputs**

No direct data inputs. The data signal (USINT) is provided via the adapter **AUS\_IN.D1**.

### **Data Outputs**

No direct data outputs. The data signal (BOOL) is output via the adapter **AX\_OUT.D1**.

### **Adapters**

| Name | Direction | Type | Comment |
|------|----------|-----|-----------|
| AUS\_IN | Socket | adapter::types::unidirectional::AUS | USINT input value and event |
| AX\_OUT | Plug | adapter::types::unidirectional::AX | BOOL output value and event |

## Functionality

The function block internally uses an **F_NE** block (comparison for inequality) from the IEC 61131 library.

- An incoming event **AUS\_IN.E1** triggers the **REQ** input of **F_NE**.
- **F_NE** compares the data value **AUS\_IN.D1** (USINT) with the constant value **USINT#0**.
- The comparison result (BOOL: TRUE if not zero, otherwise FALSE) is forwarded to **AX\_OUT.D1**.
- After processing is complete, **F_NE** generates a **CNF** event, which is passed to **AX\_OUT.E1**.

## Technical Features

- **Stores the integer's bit pattern**, as expected for a bit-string destination (truncates if the destination is narrower than the source).

- The function block (FB) is implemented as a **Composite FB**, meaning its logic is represented by an internal network of standard function blocks.
- It uses the **F_NE** comparison block, which is from the **iec61131::comparison** library.

- The package organization is **adapter::conversion::unidirectional**, indicating its use as an adapter converter.

- The function block (FB) does not have its own state machines; processing is exclusively event-driven via internal connections.

## State Overview

As a composite FB, **AUS_TO_AX** does not have its own state machine.

All logic is performed by the integrated **F_NE**, which does not require stateful control.

The behavior is purely combinatorial with event-driven execution.

## Application Scenarios

- Conversion of a counter value (USINT) into a Boolean signal indicating the state "value ≠ 0" (e.g., "fill level present" or "sensor active").
- Use in **agricultural technology** – the FB originates from HR Agrartechnik GmbH – for processing sensor data via adapter interfaces.
- Simplifies cabling in 4diac IDE projects when heterogeneous adapter types need to be coordinated.

## Comparison with similar function blocks

- Direct comparison with a **NE** function block: **AUS_TO_AX** extends the basic comparison function with adapter conversion.
- While an **NE** function block typically expects two simple data inputs (e.g., ANY), this function block works exclusively with predefined adapters (AUS / AX) and hides its internal logic.
- It is therefore specifically optimized for systems with a uniform adapter concept (unidirectional interfaces).

## Conclusion

**AUS_TO_AX** is a simple yet effective adapter converter that converts a USINT value into a Boolean signal by comparing it to zero.

Its encapsulation as a composite function block with adapter connections allows for seamless integration into modular 4diac projects. The function block (FB) does not offer its own states and, due to its low complexity, is reliable and requires little maintenance.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
