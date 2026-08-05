# ATM
![ATM](./ATM.svg)

* * * * * * * * * *
## Introduction
The **ATM adapter** (short for "Adapter Time Message") is a unidirectional type according to IEC 61499-1 that provides an event-driven interface for transmitting a time value. It is used as an adapter to enable standardized, loosely coupled communication between function blocks (FBs). This adapter was developed by HR Agrartechnik GmbH and is available under the Eclipse Public License 2.0 (EPL-2.0).
## Interface Structure

### **Event Inputs**

The adapter has no event inputs.

#### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| E1 | Event | Indication (or request) – sent along with the data value D1 |

### **Data Inputs**

The adapter has no data inputs.

### **Data Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| D1 | TIME | Indication/Request Data from the Plug |

### **Adapter**

The module itself is of type `AdapterType`. No other adapter interfaces are included.

## Functionality

The ATM adapter operates exclusively as a unidirectional interface. It is integrated into a function block as a **plug** (or as a **socket**) and, upon occurrence of the event **E1**, transmits the corresponding time value **D1** (type `TIME`) to the connected counterpart. The transmission is unidirectional: from the sending to the receiving block. The connection is automatically resolved by the 4diac IDE environment.

## Technical Features
- **Unidirectional Adapter**: Only one data and event direction (plug → socket).
- **Simplest Implementation**: Exactly one event and one variable – minimal overhead.
- **Typing**: The transmitted variable is of the elementary type `TIME`, suitable for timestamps, delays, or time measurements.
- **License**: Released under EPL-2.0, therefore freely usable and extensible.
- No state machine or internal logic – pure interface.

## State Overview

Since the ATM adapter has no internal state machine (stateless adapter), a state overview is not required. Its functionality is limited to the pure transmission of event data.

## Application Scenarios
- **Transmission of timestamps** between different function blocks (e.g., logging, time-based control).
- **Signal for time-controlled actions**: A function block sends time information via the adapter, which is evaluated by another function block.
- **Test environments**: Simple, clearly defined interface for unit tests of function blocks that process time values.

## Comparison with similar function blocks

| Feature | ATM (this adapter) | Other unidirectional adapters (e.g., with multiple events/data) |
|---------|----------------------|----------------------------------------------------------------|
| Events | 1 (E1) | Usually multiple (e.g., INIT, REQ, IND, RSP) |
Data | 1 (TIME) | Often multiple data or different types |
Complexity | Low | Medium to high |
Application | Simple time transmission | Complex process scripts |

Compared to more general adapters, ATM is limited to the essentials – ideal when only one event with a single time value needs to be exchanged.

## Conclusion

The ATM adapter is a minimal yet practically relevant component for the unidirectional transmission of time values in IEC 61499 systems. Its clear interface and ease of use make it particularly suitable for applications that focus on time-related communication. Thanks to its open licensing, the adapter can be integrated into or extended in your own projects without restrictions.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
