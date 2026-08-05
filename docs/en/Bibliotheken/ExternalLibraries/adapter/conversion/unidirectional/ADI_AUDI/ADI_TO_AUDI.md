# ADI_TO_AUDI
![ADI_TO_AUDI](./ADI_TO_AUDI.svg)

* * * * * * * * * *
## Introduction
The function block ADI_TO_AUDI converts an ADI (DINT) adapter to an AUDI (UDINT) adapter. It is a composite function block (FB) that uses an internal conversion block to convert the data types from signed 32-bit integer (DINT) to unsigned 32-bit integer (UDINT). The block enables the seamless integration of components that use different adapter types.
## Interface Structure

### **Event Inputs**

The function block does not have direct event inputs. Events are provided via the incoming adapter **ADI_IN**. The ADI adapter defines an event output E1, which is connected to the event input REQ of the internal conversion block.

| Label | Data Type | Description |
|-------------|----------|--------------|
| (via ADI_IN.E1) | EVENT | Trigger for Conversion |

### **Event Outputs**

This function block does not have direct event outputs. Events are passed on via the outgoing adapter **AUDI_OUT**. The internal conversion function block signals completion via CNF, which is connected to the event input E1 of the AUDI adapter.

| Name | Data Type | Description |
|-------------|-----------|--------------|
| (via AUDI_OUT.E1) | EVENT | Confirmation of Completed Conversion |

### **Data Inputs**

This function block has no direct data inputs. The DINT value to be converted is provided via the incoming adapter **ADI_IN** (output D1).

| Name | Data Type | Description |
|-------------|----------|--------------|
| (via ADI_IN.D1) | DINT | The value in DINT format to be converted to UDINT |

### **Data Outputs**

This function block has no direct data outputs. The converted UDINT value is output via the outgoing adapter **AUDI_OUT** (input D1).

| Name | Data Type | Description |
|-------------|-----------|--------------|
| (via AUDI_OUT.D1) | UDINT | The result of the conversion as UDINT |

### **Adapters**

The function block provides two adapter interfaces:

| Name | Direction | Type | Description |
|------|----------|-----|--------------|
| ADI_IN | Socket | adi (unidirectional) | Input adapter – provides DINT data and a trigger event |
| AUDI_OUT | Plug | audi (unidirectional) | Output adapter – outputs converted UDINT data and an acknowledgment event |

The adapters are unidirectional, meaning they transmit data and events in only one direction.

## Functionality

The function block operates as a pure wrapper (composite) and contains a single internal function block of type `iec61131::conversion::F_DINT_TO_UDINT`. As soon as an event arrives at input adapter E1 on the ADI_IN input, the internal function block is triggered via its REQ input. This block reads the DINT value present at ADI_IN.D1, converts it to a UDINT value, and outputs the result to its output OUT. Simultaneously, it generates an acknowledgment event at CNF, which is forwarded via the output adapter AUDI_OUT.E1. The converted value is then available at AUDI_OUT.D1.

## Technical Features
- The function block is implemented as a composite function block and does not contain any logic of its own. All functionality is provided by the internal conversion block.
- The adapters are of type "unidirectional," meaning that data and event flows are directed.
- The function block is part of the adapter conversion library and facilitates the connection of components with different adapter data types.
- The data type conversion from DINT to UDINT is typed; An overflow for negative values must be considered (e.g., -1 becomes 4294967295).

## State Overview

The function block does not have its own state machine. Its behavior results solely from the interaction of the internal block `F_DINT_TO_UDINT` and the event connections. The internal block has simple state logic: In its idle state, it waits for a REQ event, then performs the conversion and sends CNF. There are no other states.

## Application Scenarios
- **Adapter Replacement**: When an application needs to replace a DINT-based adapter (ADI) with a UDINT-based adapter (AUDI) without changing the surrounding logic.
- **System Integration**: Connecting components that use different integer types (e.g., a sensor provides DINT, an actuator expects UDINT).
- **Protocol Adaptation**: In heterogeneous control systems where adapter types are not directly compatible.

## Comparison with Similar Function Blocks
- **ADI_TO_AUDI** (this function block): Converts DINT adapters to UDINT adapters.
- **AUDI_TO_ADI**: A hypothetical counterpart that would convert UDINT to DINT (does not exist in the given XML, but is conceivable).
- **Direct Conversion with F_DINT_TO_UDINT**: Instead of using the adapter, the conversion function block could be used directly, but the adapter structure would then have to be manually recreated. ADI_TO_AUDI encapsulates this adaptation and provides a clean interface.

## Conclusion

The ADI_TO_AUDI function block provides a simple and effective solution for converting DINT to UDINT adapters. As a composite function block, it utilizes a proven standard conversion block and offers a clear, unidirectional interface via its adapters. It is particularly well-suited for system integration and adapter adaptation in IEC 61499-based automation solutions.
