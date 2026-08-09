# AL_TO_ADI

![AL_TO_ADI](./AL_TO_ADI.svg)

* * * * * * * * * *
The composite function block `AL_TO_ADI` serves to standardize the conversion of a unidirectional LWORD adapter (`AL`) into a unidirectional DINT adapter (`ADI`). It enables the seamless integration of components that work with different data types in a 4diac adapter landscape.

Since the function block is implemented as a composite, it does not have its own event or data interfaces outside of the adapters. All inputs and outputs are handled via the integrated adapters.

No dedicated event inputs. The event triggering the conversion is received via socket `AL_IN` (specifically via event `E1`).

No dedicated event outputs. The confirmation event after the conversion is complete is sent via plug `ADI_OUT` (specifically via event `E1`).

No dedicated data inputs. The LWORD value to be converted is provided via socket `AL_IN` (specifically via date `D1`).

No dedicated data outputs. The converted DINT value is output via plug `ADI_OUT` (specifically, via the date `D1`).

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

- **AL_IN (Socket)**

Type: `adapter::types::unidirectional::AL`

Includes a unidirectional LWORD adapter. Provides the trigger event (`E1`) and the LWORD input value (`D1`).

- **ADI_OUT (Plug)**

Type: `adapter::types::unidirectional::ADI`

Provides a unidirectional DINT adapter. Returns the confirmation event (`E1`) and the converted DINT output value (`D1`).

## Functionality

The FB is a composite function block that internally uses the IEC 61131 standard function `F_LWORD_TO_DINT`. The process is as follows:

1. An event at socket `AL_IN.E1` activates the internal converter (`Convert.REQ`).
2. The converter reads the LWORD value from `AL_IN.D1`, converts it to a DINT, and places the result at `Convert.OUT`.

`` 3. After successful conversion, an event from `Convert.CNF` is forwarded to the plug `ADI_OUT.E1`.

4. Simultaneously, the converted DINT value from `Convert.OUT` is transferred to `ADI_OUT.D1`.

This ensures a complete and timely conversion from an LWORD adapter to a DINT adapter.

- The function block uses the IEC 61131-3 function `F_LWORD_TO_DINT` – a standardized and reliable type conversion.
- This is a purely **unidirectional** conversion: Data and events flow only from the socket (`AL_IN`) to the plug (`ADI_OUT`).
- The function block (FB) is modeled as a composite, which allows for a clear separation of conversion logic and adapter interfaces and promotes reuse.
- When converting from LWORD (64-bit) to DINT (32-bit), values outside the DINT range can lead to overflows or limits – this is defined by the IEC function.

The FB does not have its own state machine (ECC) because it is implemented as a composite without sequential logic. Its functionality is implemented purely through event-driven chaining of the internal elements. A one-time conversion pass occurs with each incoming event at `AL_IN`.

- **Sensor Connection:** A sensor provides LWORD data (e.g., a time signal or a large counter variable) that must be further processed as DINT in a controller.
- **Library Extension:** Deployment as part of a collection of unidirectional type converter adapters for various IEC 61131-3 data types.

Similar converter adapters exist in 4diac, for example, for `AL_TO_UDINT`, `BYTE_TO_DINT`, or `LWORD_TO_REAL`. The `AL_TO_ADI` is specifically designed for the LWORD → DINT combination. Unlike simple function blocks that only convert data, it offers full adapter coupling with event control. Compared to bidirectional adapters, it is fixed to the data flow direction from AL to ADI. Potential data loss due to the reduction in bit width (64 → 32 bits) must be considered during the selection process.

The Composite Function Block `AL_TO_ADI` provides a clean and standardized solution for converting a unidirectional LWORD adapter to a DINT adapter. By utilizing the IEC 61131 function and embedding it within the 4diac adapter concept, it significantly simplifies the integration of heterogeneous system components. It is easy to maintain, reusable, and follows established design patterns in industrial automation.

---

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de