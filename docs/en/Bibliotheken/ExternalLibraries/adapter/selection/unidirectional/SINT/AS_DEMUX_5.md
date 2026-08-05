# AS_DEMUX_5
![AS_DEMUX_5](./AS_DEMUX_5.svg)

* * * * * * * * * *
## Introduction
The function block **AS_DEMUX_5** is a generic demultiplexer for the unidirectional adapter interface `adapter::types::unidirectional::AS`. It forwards a signal (e.g., an analog measurement signal) present at its socket **IN** to one of five output adapters, **OUT1** to **OUT5**, depending on an index **K**. The block is specifically designed for use in automation technology, particularly in agricultural engineering, and can be adapted to specific applications via the attributes `GenericClassName` and `TypeHash`.
## Interface Structure
### **Event Inputs**

| Name | Type | Comment |

|------|-------|-------------------------|

| REQ | Event | Set Index K |

### **Event Outputs**

| Name | Type | Comment |

|------|-------|---------------------------------|

| CNF | Event | Confirmation of Set Index K |

### **Data Inputs**

| Name | Type | Comment |

|------|------|-----------|

| K | UINT | Index |

### **Data Outputs**
The FB has no direct data outputs. Output is handled via the adapter plugs.

### **Adapter**
**Socket (Input)**

| Name | Type | Comment |

|------|------------------------------------------|--------------------------------|
| IN | `adapter::types::unidirectional::AS` | Input Value to demultiplex |

**Plugs (outputs)**

| Name | Type | Comment |
|------|------------------------------------------|-----------|
| OUT1 | `adapter::types::unidirectional::AS` |           |
| OUT2 | `adapter::types::unidirectional::AS` |           |
| OUT3 | `adapter::types::unidirectional::AS` |           |
| OUT4 | `adapter::types::unidirectional::AS` |           |
| OUT5 | `adapter::types::unidirectional::AS` |           |

## Functionality

The FB operates according to the demultiplex principle:

1. A valid value (e.g., an analog signal) is present at socket **IN**.

2. The index (0…4) assigned to data input **K** is received via the event input **REQ**.

3. The FB then connects the incoming adapter **IN** to the corresponding output adapter **OUTx** (x = K+1).

4. After successful switching, the event **CNF** is output to confirm the operation.

The value of **K** determines the active channel:

- K=0 → OUT1
- K=1 → OUT2
- …
- K=4 → OUT5

Values outside the permissible range are ignored or do not result in any switching (implementation dependent).

## Technical Features
- **Generic Structure**: The FB can be used as a template for any number of output channels via the attribute `GenericClassName = 'GEN_AS_DEMUX'`. The instance `AS_DEMUX_5` presented here is a special version with five outputs.
- **Unidirectional Adapters**: The function block works exclusively with unidirectional `AS` adapters, which guarantees directional data transmission from input to output.
- **No Internal State Memory**: Switching is event-driven; after CNF acknowledgment, a new index can be processed immediately.

## State Overview

The FB does not have an explicit state machine (no ECC in the XML). Its behavior is strictly event-driven:

- **Idle**: Waiting for REQ.
- **Processing**: Upon REQ, K is evaluated and the adapter connection is switched.
- **Done**: Upon completion, CNF is sent, then the device returns to idle.

## Application Scenarios
- **Agricultural Control Systems**: Distribution of an analog sensor signal (e.g., torque, pressure) to various actuators or display devices.
- **Industrial Automation**: Switching between multiple measuring points or data sources in a production line.
- **Test and Verification Benches**: Selective control of different devices under test via a common signal interface.

## Comparison with Similar Function Blocks
- **AS_DEMUX_2, AS_DEMUX_3, …**: Function blocks with fewer outputs (2, 3, …). The functionality is identical; only the number of OUT plugs varies.
- **AS_SELECT (Multiplexer)**: Performs the reverse operation – multiple inputs to one output.
- **Direct Variable Switching**: Alternatively, a multiplexer could be implemented using data variables. The adapter approach, however, offers clean interface encapsulation and reusability.

## Conclusion
The **AS_DEMUX_5** function block represents a flexible and robust solution for channel-selective forwarding of adapter signals. Its generic nature allows for easy adaptation to various requirements, while the clear event interface enables reliable and traceable control. By complying with the IEC 61499 standard, it is particularly suitable for modular automation projects where reusability and type safety are paramount.
