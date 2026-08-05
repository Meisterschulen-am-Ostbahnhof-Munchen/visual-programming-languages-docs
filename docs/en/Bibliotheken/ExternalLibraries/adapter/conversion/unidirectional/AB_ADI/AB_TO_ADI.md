# AB_TO_ADI

![AB_TO_ADI](./AB_TO_ADI.svg)

* * * * * * * * * * *
## Introduction
The function block **AB_TO_ADI** is a composite function block (FB) that converts an incoming BYTE value from an **AB** adapter into a DINT value and outputs it via an **ADI** adapter. It serves as a simple, unidirectional conversion interface between these two adapter types.

## Interface Structure
### **Event Inputs**

None – event control is handled exclusively via the incoming adapter (`AB_IN`).

### **Event Outputs**

None – events are only passed on via the outgoing adapter (`ADI_OUT`).


### **Data Inputs**

None – the data is provided via the `AB_IN` adapter.

### **Data Outputs**

None – the converted data is output via the `ADI_OUT` adapter.

### **Adapters**

| Type | Name | Direction | Comment |

|---------|---------|----------|----------------------------------|

| Socket | `AB_IN` | Input | BYTE adapter (input) |

| Plug | `ADI_OUT` | Output | DINT adapter (output) |


## Functionality
The function block (FB) internally contains a single conversion block, `F_BYTE_TO_DINT` (from the IEC 61131 library). The incoming event `E1` from adapter `AB_IN` triggers the conversion of the data value `D1` (BYTE). The resulting DINT value is forwarded via `OUT` to the data output `D1` of adapter `ADI_OUT`. Upon completion of the conversion, the output adapter's event `E1` is triggered.

The control is purely data flow-driven: Each event at the input adapter causes a one-time conversion and forwarding.


## Technical Features

- **Composite Block** – No dedicated state logic; instead, it uses the internal function block `F_BYTE_TO_DINT`.

- **Adapter-Based** – The interfaces are defined as adapters, enabling high reusability and interchangeability with other function blocks.

- **License** – The function block is released under the **Eclipse Public License 2.0**.

- **Package** – The function block is organized in the package `adapter::conversion::unidirectional`.

## State Overview
The function block does not have its own state machine. Its functionality is derived solely from the internal circuitry of the conversion block. Processing is strictly event-driven and combinatorial.

## Application Scenarios

- Conversion of BYTE-based sensor data (e.g., digital status values) into integer DINT values for further processing by control logic.

- Connecting components using the **AB** adapter to systems that expect the **ADI** adapter.

- Use in adapter-based communication architectures where a uniform data representation is required.

## Comparison with similar modules

- **AB_TO_AI** – Converts BYTE to INT (16-bit integer).

- **AB_TO_AREAL** – Converts BYTE to REAL.

- **AB_TO_ADI** – Specifically for BYTE to DINT (32-bit integer).

All these modules follow the same principle: Input and output are defined as unidirectional adapters that internally use a standard conversion function.


## Conclusion

The FB `AB_TO_ADI` represents a minimalist and reliable solution for converting BYTE to DINT data. Its adapter interfaces enable seamless integration into modular control systems without requiring reimplementation of the underlying conversion logic. It is particularly suitable for applications that value a clear separation of communication protocols and data formats.