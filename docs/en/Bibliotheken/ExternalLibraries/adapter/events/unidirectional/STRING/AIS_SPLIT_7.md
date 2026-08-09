# AIS_SPLIT_7

![AIS_SPLIT_7](./AIS_SPLIT_7.svg)

* * * * * * * * * *
## Introduction

The function block **AIS_SPLIT_7** is used to distribute an incoming AIS data stream to seven identical outputs. It is implemented as a generic block and allows the division of a unidirectional AIS adapter (Socket IN) into seven identical adapter plugs (OUT1 … OUT7). The term "AIS" here refers to an application-specific, abstract data type in the adapter context of IEC 61499.
## Interface Structure

### **Event Inputs**

None.

### **Event Outputs**

None.

### **Data Inputs**

None.

### **Data Outputs**

None.

### **Adapters**

| Direction | Name | Type | Description |
|----------|------|-----|--------------|
| Socket (Input) | IN | `adapter::types::unidirectional::AIS` | Incoming AIS data stream, distributed to all outputs. |
| Plug (Output) | OUT1 … OUT7 | `adapter::types::unidirectional::AIS` | Seven identical outputs, each forwarding the incoming AIS data stream unchanged. |

## Functionality

This module functions as a splitter for AIS adapter connections. Every incoming data or event at socket `IN` is replicated **without delay or processing** to all seven adapter plugs OUT1 to `OUT7`. The data is forwarded in parallel, meaning all outputs receive the same information simultaneously. No internal logic or state machine is required, as this is a passive, connection-oriented data transfer.

## Technical Features

- **Generic Function Block** – The function block is declared as a generic instance (`GEN_AIS_SPLIT`) and can be parameterized for any AIS type.
- **Unidirectional Adapters** – Both inputs and outputs use only unidirectional adapters, ensuring a pure flow from input to output.
- **No Event or Data Inputs/Outputs** – All communication occurs exclusively via adapters, enabling clean encapsulation and reuse.
- **Scalability** – The principle can easily be adapted to different numbers of outputs (e.g., AIS_SPLIT_2, AIS_SPLIT_8).

## State Overview

This function block does not have an explicit state machine (ECC) because it does not execute any sequential logic or delayed operations. Its function is reduced to static, continuous forwarding. Therefore, an operating state is not defined.

## Application Scenarios

- **Distribution of AIS signals** to multiple parallel processing units, e.g., in automation systems, when a sensor value needs to be simultaneously passed to several control loops, displays, or analysis tools.
- **Redundant Signal Forwarding** – Used to feed an AIS data stream into multiple independent paths for testing or monitoring purposes.
- **Modular System Architecture** – As a component in a library of generic adapter function blocks to increase the reuse and interchangeability of connections.

## Comparison with Similar Function Blocks

- **Data Splitters (e.g., SPLIT_1_to_N)** – These typically split simple data types (BOOL, INT, REAL). The AIS_SPLIT_7 is specifically designed for adapter interfaces and utilizes the adapter concept defined in IEC 61499 for complex, structured data streams.
- **Adapter Multiplexers (e.g., AIS_MERGE)** – While a splitter distributes one input to multiple outputs, a merger combines multiple inputs into one output. The AIS_SPLIT_7 is the counterpart to this.
- **Event Splitters** – These differ in their event processing capabilities; the AIS_SPLIT_7, however, operates purely on an adapter basis without separate event channels.

## Conclusion

The **AIS_SPLIT_7** is a simple yet effective functional block for distributing a unidirectional AIS data stream to seven parallel outputs. Its generic design and exclusive use of adapters make it a flexible tool in automation application development according to IEC 61499. The absence of state logic and event control makes it lightweight and ideally suited for pure distribution tasks.
