# AB_TO_AUS
![AB_TO_AUS](./AB_TO_AUS.svg)

* * * * * * * * * *
## Introduction
The function block **AB_TO_AUS** is a composite block that performs a unidirectional conversion of data from the **AB adapter** (BYTE) to the **AUS adapter** (USINT). It encapsulates the necessary type conversion and event passing, thus enabling the seamless integration of components based on different data types.
## Interface Structure

### **Event Inputs**

The function block does not have separate event inputs at the top level. The triggering event is provided via the socket adapter **AB_IN** (available there as `E1`).

### **Event Outputs**

There are no direct event outputs at the composite function block level. The resulting event is output via the plug adapter **AUS_OUT** (there as `E1`).

### **Data Inputs**

No data inputs are defined at the top level. The input data (BYTE) is received via the socket adapter **AB_IN** (there as `D1`).

### **Data Outputs**

There are no direct data outputs. The converted data (USINT) is provided via the plug adapter **AUS_OUT** (there as `D1`).

### **Adapters**

| Type | Name | Direction | Description |

|-----|------|----------|--------------|

| Socket | **AB_IN** | Input | Unidirectional adapter of type `adapter::types::unidirectional::AB`. Returns a BYTE (`D1`) and an event (`E1`). |

| Plug | **OFF_OUT** | Output | Unidirectional adapter of type `adapter::types::unidirectional::AUS`. Provides a USINT (`D1`) and an event (`E1`). |

## Functionality

1. An event at `AB_IN.E1` triggers processing.

2. The value of `AB_IN.D1` (BYTE) is passed to the internal converter **F_BYTE_TO_USINT**.

3. The converter transforms the BYTE into a USINT value. 4. The result is output to `AUS_OUT.D1` (USINT).

5. Simultaneously, an event is generated on `AUS_OUT.E1` to signal the subsequent processing.

The entire conversion is event-driven and performed in a single step.

## Technical Features
- **Unidirectional Adapter Coupling**: The function block connects two unidirectional adapters (ON → OFF) and ensures that the data flow direction is clearly defined.
- **Reusable IEC Conversion**: Internally, the standardized function block `iec61131::conversion::F_BYTE_TO_USINT` is used.
- **Composite Architecture**: The conversion logic is encapsulated and can be easily integrated into other projects or replaced by alternative converters.
- **No Internal State**: The function block does not have its own state machine; it forwards events and data directly.

## State Overview

The **AB_TO_AUS** function block does not have its own state machine. Its operation is based on a purely event-driven data conversion. The internal converter `F_BYTE_TO_USINT` also operates without state storage.

## Application Scenarios
- **System Integration**: Connecting a device that provides measured values as BYTE via the AB adapter to a controller that expects USINT data via the AUS adapter.
- **Protocol Conversion**: Converting BYTE-encoded commands to USINT-encoded values for further processing in libraries that exclusively support USINT.
- **Modular Reuse**: Encapsulating the conversion as a standalone function block to improve clarity in large automation projects.

## Comparison with Similar Function Blocks

| Function Block | Description |

|----------|--------------|

| **F_BYTE_TO_USINT** | Simple IEC converter without adapter connection. Must be manually wired with event and data connections. |

**AB_TO_AUS** | Composite function block that encapsulates the entire adapter conversion, including event forwarding, thus providing a clean, abstracted interface. |

**AUS_TO_AB** (hypothetical) | Reverse conversion from USINT to BYTE – mirrored functionality for the opposite direction. |

The **AB_TO_AUS** function block stands out due to its ease of use and direct adapter compatibility.

## Conclusion

The **AB_TO_AUS** function block offers an elegant and standardized way to convert BYTE data from an AB adapter to USINT data for an AUS adapter. Encapsulating the conversion logic in a composite block promotes reusability and simplifies system integration. It is particularly suitable for modular automation solutions based on IEC 61499.
