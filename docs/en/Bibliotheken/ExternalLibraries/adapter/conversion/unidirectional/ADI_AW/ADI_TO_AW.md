# ADI_TO_AW
![ADI_TO_AW](./ADI_TO_AW.svg)

* * * * * * * * * *
## Introduction
The function block **ADI_TO_AW** is a composite module that converts a DINT value into a WORD value. It acts as a unidirectional converter between an **ADI** adapter (DINT input) and an **AW** adapter (WORD output). The function block encapsulates the conversion logic and provides a standardized interface for data exchange at the adapter level.
## Interface Structure

The function block has no direct event or data inputs/outputs. All communication takes place via adapters:

### **Adapter**

| Type | Name | Direction | Description |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::ADI` | `ADI_IN` | Socket (Input) | DINT adapter providing the value to be converted |
| `adapter::types::unidirectional::AW` | `AW_OUT` | Plug (Output) | WORD adapter outputting the converted value |

The internal event and data connections of the composite function block result from the adapter interfaces used:

### **Event Inputs** (via ADI_IN)

| Event | Description |
|----------|--------------|
| `E1` | Trigger for converting the DINT value |

### **Event Outputs** (via AW_OUT)

| Event | Description |
|----------|--------------|
| `E1` | Confirmation of successful conversion and output of the WORD value |

### **Data Inputs** (via ADI_IN)

| Identifier | Type | Description |
|------------|-----|--------------|
| `D1` | `DINT` | The integer value to be converted |

### **Data Outputs** (via AW_OUT)

| Identifier | Type | Description |
|------------|-----|--------------|
| `D1` | `WORD` | The converted bit pattern value (16 bits) |

## Functionality

The function block operates in an event-driven manner:

1. An incoming event at `ADI_IN.E1` is internally forwarded to the conversion block `F_DINT_TO_WORD` (via its `REQ` input).

2. Simultaneously, the data value from `ADI_IN.D1` is transferred as `DINT` to the `IN` input of the conversion function.

`` 3. The function block `F_DINT_TO_WORD` converts the `DINT` value to a `WORD` value (according to IEC 61131-3).

4. After the conversion is complete, the converter's output event (`CNF`) is sent.

5. This event is forwarded to `AW_OUT.E1`, and the converted `WORD` value (from `OUT`) is passed to `AW_OUT.D1`.

Thus, the entire conversion occurs in a strict event/data flow without any additional states.

## Technical Features
- **Adapter-Based Encapsulation:** The function block (FB) uses adapters exclusively for input and output, enabling modular and reusable integration in 4diac projects.
- **Unidirectional Conversion:** Data conversion only occurs from socket to plug; reverse conversion is not supported.
- **Use of IEC 61131 Libraries:** The core function `F_DINT_TO_WORD` is derived from the `iec61131::conversion` package, ensuring standards-compliant and high-performance conversion.
- **No Internal States:** The FB does not have an internal state diagram; its logic is determined solely by the behavior of the contained block.

## State Overview

Since this is a purely structured composite FB without its own Execution Control Chart (ECC), there is no explicit state model. The behavior is purely data stream-driven and corresponds to that of the internal conversion block (IDLE → REQ → CNF → IDLE).

## Application Scenarios
- **PLC Coupling:** Connecting a DINT-based sensor (e.g., encoder) to a subsystem that expects WORD values.
- **Data Format Conversion in Adapter Chains:** Use in a 4diac application where different adapter types need to be harmonized.
- **Interface Standardization:** Implementing a standardized WORD interface for downstream logic blocks, while the source is in DINT format.

## Comparison with Similar Blocks

| Block | Function | Difference |
|----------|----------|-------------|
| `F_DINT_TO_WORD` | Direct DINT to Word conversion | No adapter encapsulation; must be manually integrated into a network |
ADI_TO_AW` | Adapter-based encapsulation of the same conversion | Provides ready-to-use adapter interfaces; simplifies reuse |
WORD_TO_DINT` | Reverse conversion | Other direction; requires a custom adapter type |

The `ADI_TO_AW` is specifically optimized for environments where adapters are required as standardized interfaces.

## Conclusion

The function block `ADI_TO_AW` provides a reusable, adapter-based solution for converting `DINT` to `WORD`. It cleanly encapsulates the conversion logic and enables easy integration into 4diac architectures based on the adapter concept. The use of standard libraries ensures reliability and adherence to specifications. This component is particularly suitable for scenarios where different data formats need to be connected via adapter bridges.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
