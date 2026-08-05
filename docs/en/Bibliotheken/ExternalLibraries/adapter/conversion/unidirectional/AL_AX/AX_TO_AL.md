# AX_TO_AL
![AX_TO_AL](./AX_TO_AL.svg)
* * * * * * * * * *
## Introduction
The function block **AX_TO_AL** is a composite block for bidirectional coupling of an AX adapter (BOOL) with an AL adapter (LWORD). It enables the forwarding of events and data between these two adapter interfaces without requiring the implementation of custom logic. The function block serves as a simple conversion bridge and is typically used in automation systems to connect components with different adapter formats.
## Interface Structure

### **Event Inputs**

| Name | Adapter | Description |

|------|---------|---------------|

| AX_IN.E1 | AX (BOOL) | Event input connected via the AX adapter. |

### **Event Outputs**

| Name | Adapter | Description |

|------|---------|--------------|

| AL_OUT.E1 | AL (LWORD) | Event output that passes the incoming event on unchanged. |

### **Data Inputs**

| Name | Adapter | Type | Description |

|------|---------|-----|--------------|

| AX_IN.D1 | AX (BOOL) | BOOL | Data input for a Boolean signal. |

### **Data Outputs**

| Name | Adapter | Type | Description |

|------|---------|-----|--------------|

| AL_OUT.D1 | AL (LWORD) | LWORD | Data output that represents the Boolean signal as an LWORD (64-bit memory). Type conversion is performed outside the function block. |

### **Adapter**

| Type | Name | Direction |

|-----|------|----------|

| Socket | AX_IN | Input (BOOL) |

| Plug | AL_OUT | Output (LWORD) |

## Functionality

The FB **AX_TO_AL** functions purely as a pass-through function block. Within the FB network, the event connection `AX_IN.E1 → AL_OUT.E1` and the data connection `AX_IN.D1 → AL_OUT.D1` are established directly. An incoming event at the AX socket immediately triggers the corresponding event at the AL plug. Simultaneously, the Boolean value of `AX_IN.D1` is passed to `AL_OUT.D1`.

The function block itself does not perform any value conversion; the conversion of the Boolean signal to an LWORD (e.g., 1 or 0 in a 64-bit word) is provided by the underlying adapter implementation or the host environment.

## Technical Features
- **Composite Architecture**: The function block contains no internal ECC (Execution Control Chart) or its own logic. It consists solely of two adapter connections and simple passthroughs.
- **Type Mapping**: The mapping from BOOL to LWORD is implicit. The user must ensure that the connected adapters correctly support the conversion.
- **Project Structure**: The function block is located in the package `adapter::conversion::unidirectional`, which indicates its function as a unidirectional conversion adapter.

## State Overview

The function block has no state machine and no states of its own. It operates in an event-driven manner and reacts passively to signals from the AX adapter.

## Application Scenarios
- Integrating an old Boolean interface (AX) into a system that only supports LWORD adapters (AL).
- Temporary bridging circuit during the migration of fieldbus protocols.
- Test environments where a Boolean signal needs to be interpreted as a 64-bit value.

## Comparison with Similar Function Blocks

Other conversion function blocks exist, such as... Examples include `AL_TO_AX` (reverse conversion from LWORD to BOOL) or `BOOL_TO_LWORD` (direct conversion without adapter encapsulation). Unlike these pure value converters, **AX_TO_AL** encapsulates the entire adapter interface, so the user only needs to connect the adapters.

## Conclusion

The **AX_TO_AL** function block is a lean yet useful adapter coupler. It reduces the effort required when different adapter formats need to be combined in an automation system and does not require any custom logic or state definitions. Its simple structure facilitates quick integration into existing IEC 61499 networks.