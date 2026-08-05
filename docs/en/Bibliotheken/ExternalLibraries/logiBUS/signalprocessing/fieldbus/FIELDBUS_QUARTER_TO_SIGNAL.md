# FIELDBUS_QUARTER_TO_SIGNAL
![FIELDBUS_QUARTER_TO_SIGNAL](./FIELDBUS_QUARTER_TO_SIGNAL.svg)
* * * * * * * * * *
## Introduction
The function block `FIELDBUS_QUARTER_TO_SIGNAL` serves as a signal validation and pass-through block. It checks whether an incoming BYTE value `IN` is within a valid range and, if so, passes it unchanged to `OUT`. Additionally, a Boolean signal `VALID` is set, indicating the validity status of the output. This block is suitable for filtering fieldbus signals where certain values are marked as invalid or "don't care".
## Interface Structure

### **Event Inputs**

| Name | Type | Comment | With Variables |

|--------|-------|------------------------------|---------------|

| `REQ` | Event | Normal Execution Order | `IN` |

### **Event Outputs**

| Name | Type | Comment | With Variables |

|-------|-------|-----------------------------|-------------------|

| `CNF` | Event | Execution Confirmation | `OUT`, `VALID` |

### **Data Inputs**

| Name | Type | Comment | Initial Value |

|------|--------|--------------------|--------------------------------|

| `IN` | `BYTE` | Input Signal | `NOT_AVAILABLE_2bit` (Imported Constant) |

### **Data Outputs**

| Name | Type | Comment | Initial Value |

|---------|--------|---------------------------------|-------------|

| `OUT` | `BYTE` | Filtered Output Signal | `16#00` |

| `VALID` | `BOOL` | `TRUE`, if the signal is valid | `FALSE` |

### **Adapter**

No adapters available.

## Functionality

When an event occurs at input `REQ`, the algorithm `REQ` is executed:

1. The incoming value `IN` is compared to the imported constant `DONT_CARE_2bit`.

2. If `IN` is less than `DONT_CARE_2bit`, the value is considered valid:

- `OUT` receives the value of `IN`.
- `VALID` is set to `TRUE`.

3. Otherwise (if `IN` is greater than or equal to `DONT_CARE_2bit`), the signal is classified as invalid:

- `OUT` is reset to `BYTE#0`.
- `VALID` is set to `FALSE`.

4. After processing, the event `CNF` is triggered.

The comparison uses the semantics of the imported constants:

DONT_CARE_2bit` defines the threshold above which values are considered "irrelevant" or invalid. The initial value of `IN` is set to `NOT_AVAILABLE_2bit`, which is typically above this threshold, so the function block outputs a defined invalid state upon startup.

## Technical Features
- **Constant Import**: The values `DONT_CARE_2bit` and `NOT_AVAILABLE_2bit` are imported from a higher-level signal processing package. They must be defined in the target system and represent meaningful threshold values (e.g., `16#FC` for "don't care").
- **Simple State Logic**: The function block has only a single EC state, `REQ`. Every event immediately triggers a calculation and output.
- **Compatibility**: Designed according to IEC 61499-1, usable in the 4diac IDE and other compliant runtime environments.

## State Overview

Only one state exists:

| State | Description | Output Event | Output Actions |

|---------|--------------------------------------------------|----------------|--------------------------|

| `REQ` | Processes the input and updates outputs | `CNF` | Set `OUT` and `VALID` |

## Application Scenarios
- **Fieldbus Monitoring**: A sensor delivers 8-bit data on a fieldbus (e.g., CANopen, PROFIBUS), where certain values are coded as "not available" or "error." The function block extracts the valid measured values and displays their validity.
- **Signal Preprocessing**: Before further processing in a controller, invalid telegram segments are filtered out, so that subsequent blocks only work with plausible data.
- **Gateway Between Bus Systems**: Translation of a bus's "don't care" conventions into a uniform validity signal for the target system.

## Comparison with Similar Function Blocks
- **`FIELDBUS_QUARTER_TO_SIGNAL`** specializes in distinguishing between valid and invalid values using a fixed threshold.
- A general **value filter** (e.g., `F_BAND`) could, on the other hand, query a lower and upper limit.
- A **validation checker** (e.g., `VALIDITY_CHECK`) often additionally sets Quality of Service flags.

This function block impresses with its simple logic, tailored to fieldbus types.

## Conclusion

FIELDBUS_QUARTER_TO_SIGNAL` is a compact, efficient function block for validating 8-bit fieldbus signals. It reliably separates valid measured values from those marked as invalid and provides the validity as a separate Boolean signal. Thanks to its streamlined state logic and the use of imported constants, it can be flexibly integrated into various signal processing chains.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
