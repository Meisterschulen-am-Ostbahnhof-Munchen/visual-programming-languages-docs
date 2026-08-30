# AIS

![AIS](./AIS.svg)
**Unidirectional Adapter for 1 Event and 1 String**

* * * * * * * * * *

## Introduction

The **AIS** (Adapter Interface String) adapter provides a unidirectional interface through which exactly one event (E1) along with its associated string (D1) can be transmitted from a plug instance to a socket instance. It is used to implement simple, directed data flows where no feedback or additional control is required.

## Interface Structure

### **Event Inputs**

None.

### **Event Outputs**

| Name | Type | Comment |
|------|-------|-----------|
| E1 | Event | Indication (or Request) – the event is triggered when the data is sent. |

### **Data Inputs**

None.

### **Data Outputs**

| Name | Type | Comment |
|------|--------|-----------|
| D1 | STRING | The data (string) associated with the event. |

### **Adapter**

This component is itself an adapter. It has no other internal adapters.

## Functionality

The adapter operates on the principle of a unidirectional "plug-socket" connection.

- The **plug** instance sends an event to E1 and simultaneously stores the data on D1.
- The **socket** instance receives this event and can read the value from D1.

Communication in the opposite direction is not supported.

## Technical Features

- **Minimal Resource Consumption**: The adapter requires only one event and one string – ideal for resource-constrained controllers.
- **Type Safety**: The data type is fixed to STRING; the adapter can be used directly in applications that require precisely this signature.
- **Easy Reuse**: The strict separation between plug and socket allows for easy encapsulation and replacement of modules.

## State Overview

The adapter does not have an internal state machine. It behaves **stateless**: Every incoming event on the plug side is immediately forwarded as an output event on the socket side. The data value D1 is transferred at the time of the event.

## Application Scenarios

- **Sensor Connection**: Transfer of a single measured value (e.g., scrolling text from an RFID reader) to a processing unit.
- **Monitor Interface**: Output of a status string from a controller to a display element.
- **Debugging**: Easy extraction of diagnostic information from a function block.

## Comparison with Similar Blocks

- **More complex adapters**, such as adapters with multiple events and mixed data types, offer greater flexibility but also require more configuration effort.
- **Bidirectional adapters** (e.g., with one event in each direction) allow feedback; the AIS adapter deliberately omits this to keep the interface as simple as possible.
- The AIS is specifically optimized for **exactly one event + one string** – other adapters with the same signature but a different name could be functionally identical.

## Conclusion

The **AIS** adapter is a lean, stateless block for the unidirectional transmission of an event along with a string. It is ideally suited for all cases where simple, clear signal transmission without additional logic or a feedback channel is required. The minimal interface keeps the application clear and easy to understand.
