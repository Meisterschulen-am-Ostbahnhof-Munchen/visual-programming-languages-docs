# ALI_MUX_3

![ALI_MUX_3](./ALI_MUX_3.svg)

* * * * * * * * * *
The function block **ALI_MUX_3** is a generic multiplexer for ALI data streams. It selects one of three unidirectional ALI inputs (IN1, IN2, IN3) and outputs it via the ALI output (OUT). The selection is made using the index K, which is set via the event input REQ. The block is provided as a generic FB and can be used in Eclipse 4diac.

| Name | Type | Comment |
|------|-----|------------|
| REQ | Event | Sets the index K and starts the multiplexer function. Used with the data input K (With). |
| Name | Type | Comment |
|------|-----|-----------|
| CNF | Event | Confirms that index K has been set and the output updated. |
| Name | Type | Comment |
|------|-----|-----------|
| K | UINT | Selection index for the multiplexer. Valid values: 0 (IN1), 1 (IN2), 2 (IN3). |

*No direct data outputs available.* Output is provided via the adapter output.

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapter**

| Type | Name | Direction | Comment |
| Name | Type | Comment |
|-----|------|----------|-----------|
| **adapter::types::unidirectional::ALI** | IN1 | Socket | First input (switches on when K = 0) |
| **adapter::types::unidirectional::ALI** | IN2 | Socket | Second input (switches on when K = 1) |
| **adapter::types::unidirectional::ALI** | IN3 | Socket | Third input (switches on when K = 2) |
| **adapter::types::unidirectional::ALI** | OUT | Plug | Output that passes the selected input |

## Functionality

The function block operates in an event-driven manner. A valid event at the REQ input triggers the following steps:

1. The current value of the data input K is read.
2. Depending on K, one of the three socket adapters (IN1 for K=0, IN2 for K=1, IN3 for K=2) is connected to the plug adapter OUT.
3. After successful connection, the event output CNF is displayed.

The function block is unidirectional – data flows only from the inputs to the output. The index K must be present before the REQ event, as it is associated with the event (With).

- **Generic Function Block:** The function block is declared as a generic type (GenericClassName `GEN_ALI_MUX`) and can be implemented with different implementations or instances.
- **Adapter-Based:** All inputs and outputs use the same adapter type (`adapter::types::unidirectional::ALI`). This enables flexible and type-safe connectivity with other ALI components.
- **Type Hash:** The function block contains an attribute `eclipse4diac::core::TypeHash`, which can be used at runtime for unique type identification.
- **Only One Event Input:** All control logic is handled via the single REQ event. There are no separate events for each input or for setting the index.

The function block does not have an explicit state machine (ECC) in its XML definition. Its behavior is event-driven and follows a simple sequence:

| State | Description |
|---------|--------------|
| **Idle** | Waiting for a REQ event. |
| **Processing** | After REQ: Input is selected based on K, and the output is passed through. |
| **Done** | Output of CNF, return to Idle. |

Since no detailed ECC is available, the implementation is assumed to be a deterministic, non-blocking algorithm.

- **Sensor Selection:** In agricultural technology (see metadata), various sensors (e.g., temperature, humidity, rotational speed) can be connected via ALI interfaces. The multiplexer selects the required sensor value.
- **Configuration Switching:** In machine control systems, the function block can be used to switch between several preconfigured ALI data paths.
- **Redundancy:** If one of the inputs fails, the multiplexer can switch to another to maintain operation.
- **ALI_MUX_2:** A multiplexer with only two inputs. ALI_MUX_3 offers an additional selection option (index 0–2).
- **Standard MUX (e.g., IEC 61499 MUX):** A general-purpose multiplexer typically works with simple data types (INT, REAL) and events. ALI_MUX_3 is specifically designed for the ALI adapter type.
- **ALI_SELECT:** A function block that selects between two ALI sources using a Boolean signal. ALI_MUX_3 allows selection from three sources using a UINT index.

The **ALI_MUX_3** is a compact and flexible multiplexer for three unidirectional ALI data streams. It is particularly suitable for applications where multiple ALI sources need to be selected via an index. The generic definition facilitates adaptation to specific implementations, and the pure adapter interface ensures clean, typed communication. This function block is a fundamental element in ALI-based control systems.

---

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de