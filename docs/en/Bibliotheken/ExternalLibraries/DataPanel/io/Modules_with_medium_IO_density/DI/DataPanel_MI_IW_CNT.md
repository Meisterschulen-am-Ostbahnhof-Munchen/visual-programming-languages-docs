# DataPanel_MI_IW_CNT
![DataPanel_MI_IW_CNT](./DataPanel_MI_IW_CNT.svg)
* * * * * * * * * *
## Introduction
The **DataPanel_MI_IW_CNT** is a service interface function block from the DataPanel family of HR Agrartechnik GmbH. It is used to acquire **pulse counter data** via the dedicated hardware inputs 7A and 8A of the underlying bus system. The block encapsulates the initialization, cyclic querying, and event-driven output of the counter values. Typical applications include agricultural machinery where pulse generators (e.g., speed, flow, or position sensors) need to be evaluated. The function block is designed for the IEC 61499-compliant 4diac IDE and uses the service interface patterns defined therein.
## Interface Structure

### **Event Inputs**

| Event | Type | Description |

|--------|-------|---------------------------------------------------|

| INIT | EInit | Initializes the channel (sets hardware parameters) |

| REQ | Event | Requests a current counter value |

### **Event Outputs**

| Event | Type | Description |

|-------|-------|-----------------------------------------------------------|

| INITO | EInit | Acknowledges successful initialization |

| CNF | Event | Confirmation of a requested REQ operation |

| IND | Event | Asynchronous indication (triggered by pulse or time interval) |

### **Data Inputs**

| Name | Type | Description |

|---------------|----------|-----------------------------------------------------------------------------|

| QI | BOOL | Qualifies the INIT/REQ event |

| PARAMS | STRING | Service parameter (vendor-dependent configuration) |

| u8SAMember | USINT | Node SA (224..239); Default = `MI::MI_00` |

| Input | DataPanel_MI_DI_S | Input identification (must be "7A" or "8A"); Default = `Invalid` |

| ImpulseDelta | WORD | Pulse threshold for asynchronous IND triggering (number of pulses) |

| TimeDelta | DWORD | Time threshold for asynchronous IND triggering (in ms) |

### **Data Outputs**

| Name | Type | Description |

|--------|--------|----------------------------------------------|

| QO | BOOL | Qualifies the event outputs |

| STATUS | STRING | Status message (e.g., "OK" or error code) |

| IN | WORD | Current 16-bit counter value (pulse counter) |

### **Adapters**

No adapter interfaces defined.

## Functionality

The **DataPanel_MI_IW_CNT** operates as a service interface function block and communicates directly with the hardware interface of the DataPanel system. After startup, the channel must be initialized via the **INIT** event. The parameters (SA address, input number, pulse and time configuration) are passed during this process. The function block attempts to allocate and provide the corresponding hardware channel.

After successful initialization (signaled by **INITO**), the counter value can be queried via the **REQ** event. The response is provided via **CNF**: `IN` contains the current counter value, and `STATUS` contains the operating status.

Additionally, the function block can asynchronously output an **IND** indication when either the set number of pulses (`ImpulseDelta`) has been reached or the time interval (`TimeDelta`) has elapsed. This allows for event-driven processing without cyclical queries.

Error handling is provided via the `STATUS` output and the `QO` flag. If an error occurs (e.g., invalid input configuration, hardware unreachable), `QO` is set to `FALSE`, and a corresponding error message is output in `STATUS`.

## Technical Features
- **Input Identification:** The parameter `Input` must be set to a valid DataPanel input type (7A or 8A). The default value `Invalid` prevents incorrect initialization.
- **Node SA (`u8SAMember`):** Defines the slave address of the DataPanel participant. Valid values are 224 to 239. The predefined value `MI::MI_00` represents the first slave.
- **Asynchronous Indication:** The function block can independently generate **IND** events using `ImpulseDelta` and `TimeDelta`. Both thresholds can be active independently. If either value exceeds the configured threshold, an IND event is triggered. This reduces the bus load compared to cyclic polling.
- **Data Format:** The counter value `IN` is a 16-bit word and allows values from 0 to 65535. The counter is reset to 0 upon overflow.
- **Copyright & Version:** This function block is published under version 1.0 for the year 2026 by HR Agrartechnik GmbH.

## Status Overview

The FB (Function Block) cycles through classic service interface states:

| State | Description |

|-------------|-----------------------------------------------------------------|

| **IDLE** | Waiting for INIT or REQ. Hardware is not yet assigned. |

| **INIT** | INIT received – Parameterization and hardware reservation are in progress. |

| **ACTIVE** | Initialization successful – Channel is ready for operation. |

| **REQUEST** | REQ received – Querying the current counter value. |

| **INDICATE** | Asynchronous condition met – Sending an IND event. |

| **ERROR** | Error occurred (e.g., incorrect parameter, hardware error). |

After an error, only a new INIT can return the FB to the IDLE state.

## Application Scenarios

1. **Speed Measurement:** A radar sensor or magnetic pulse generator delivers rectangular pulses. The module counts the pulses and outputs the value as CNF or IND. `TimeDelta` can be used for time-based speed calculation.

2. **Flow Measurement:** Pulse flow meters (e.g., Hall effect) are used in agricultural irrigation systems. `ImpulseDelta`Generates an event after each defined quantity of liquid.

3. **Position Detection:** Distances are measured using an incremental encoder. By combining pulse and time monitoring, both position and speed can be determined.

## Comparison with Similar Function Blocks
- **DataPanel_MI_DI:** A purely digital input function block (status 0/1) without a counting function. The IW_CNT extends it with pulse counting and asynchronous event triggering.
- **DataPanel_MI_AI:** An analog input function block for voltage or current signals. In contrast, the IW_CNT processes only pulses (discrete) and not a continuous value.
- **CTUD** (IEC 61499 standard counter): This standard function block can count forwards/backwards but does not require low-level initialization. The DataPanel_MI_IW_CNT is specifically connected to the DataPanel hardware and offers the IND function, which is often missing in standard function blocks.

```## Conclusion

The **DataPanel_MI_IW_CNT** is a powerful service interface function block for the flexible acquisition of pulse counter data in agricultural control systems. Its integrated asynchronous indication based on pulse or time thresholds reduces response time and relieves the load on the control system. Thanks to its clearly structured interface and specific configuration options (SA address, input selection), it can be seamlessly integrated into the DataPanel ecosystem. It thus represents a reliable component for applications that require precise pulse evaluation at the system level.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]