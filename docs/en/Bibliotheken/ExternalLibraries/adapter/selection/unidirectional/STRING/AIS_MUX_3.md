# AIS_MUX_3
![AIS_MUX_3](./AIS_MUX_3.svg)

* * * * * * * * * *
## Introduction
The function block **AIS_MUX_3** is a generic multiplexer for AIS data. It selects one of three AIS input adapters (`IN1`, `IN2`, `IN3`) based on an index `K` and connects its signals to the output adapter `OUT`. An event `REQ` triggers the selection and is acknowledged with `CNF` after successful switching.
## Interface Structure
### **Event Inputs**

| Event | Description |

|----------|--------------|

| REQ | Starts the multiplex operation: The value of `K` determines which input is connected to the output. |

### **Event Outputs**

| Event | Description |

|----------|--------------|

| CNF | Acknowledges the successful selection of the input according to `K`. |

### **Data Inputs**

| Name | Type | Description |

|------|------|---------------|

| K | UINT | Index for selecting the input (0 = IN1, 1 = IN2, 2 = IN3). |

### **Data Outputs**
No direct data outputs are available. Output data is provided via the adapter `OUT`.

### **Adapters**

| Name | Type | Description |

|------|----------------------------------------|---------------|

| OUT | adapter::types::unidirectional::AIS | Output adapter that reflects the selected input. |

| IN1 | adapter::types::unidirectional::AIS | First input adapter (index 0). |

| IN2 | adapter::types::unidirectional::AIS | Second input adapter (index 1). |

| IN3 | adapter::types::unidirectional::AIS | Third input adapter (index 2). |

## Functionality

1. The module expects three different AIS data sources at the input adapters `IN1`, `IN2`, and `IN3`.

2. An incoming event at `REQ` transmits the current value of the data input `K` to the internal logic.

3. Depending on `K` (valid values: 0, 1, 2), the corresponding input adapter is switched to the output adapter `OUT`.

4. After the switchover, the event `CNF` is sent to confirm processing.

Note: For invalid values of `K` (e.g., greater than 2), the behavior may vary depending on the implementation; typically, the last valid state or an undefined state is returned.

## Technical Features
- **Generic Type**: The function block uses the attribute `eclipse4diac::core::GenericClassName = 'GEN_AIS_MUX'`, indicating that it was created as a generic function block in the 4diac IDE and can be used with any AIS adapter with the same interface.
- **No State Engine**: The function block does not have an explicit Execution Control Chart (ECC) in its XML definition; the multiplexing functionality is likely implemented through the underlying adapter architecture or simple event propagation.
- **Adapter-Based Communication**: Both inputs and outputs are defined as adapters of type `adapter::types::unidirectional::AIS`. This enables loose coupling and flexible reuse in AIS-based data streams.

## State Overview
The function block (FB) does not have documented state machine control. Only a basic sequence can be derived from the interface description:

1. **IDLE**: Waiting for a `REQ` event.

2. **MUX**: Processing the index `K` and switching the corresponding input to the output – without intermediate states.

3. Upon completion, **CNF** is output, and the function block returns to the **IDLE** state.

## Application Scenarios
- **Agricultural Sensors**: Selection of one of three AIS-compatible sensors (e.g., soil moisture, temperature, GPS) for uniform processing.
- **Data Source Switching**: In a controller that uses different AIS data sources depending on the operating mode or schedule.
- **Redundancy and Testing**: Switching between multiple AIS signal sources for validation or error detection.

## Comparison with Similar Function Blocks

| Function Block | Number of Inputs | Special Feature |

|----------|-----------------|--------------|

| AIS_MUX_2 | 2 | Simple two-channel multiplexer for AIS adapters. |

| AIS_MUX_3 | 3 | Extended to three channels; ideal for systems with three data sources. |

| AIS_MUX_4 | 4 | Higher channel count, but less specific to three-channel scenarios. |

Compared to a general-purpose MUX function block (e.g., MUX from IEC 61499 standard libraries), AIS_MUX_3 uses only AIS adapters, providing a clear data structure and type safety within an AIS-based framework.

## Conclusion

The function block **AIS_MUX_3** enables simple and efficient switching between three AIS data sources. Thanks to its generic definition and adapter interface, it can be flexibly used in AIS applications in agricultural technology as well as in other industries. Its clear event control and limited complexity make it a robust building block for multiplexing tasks.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
