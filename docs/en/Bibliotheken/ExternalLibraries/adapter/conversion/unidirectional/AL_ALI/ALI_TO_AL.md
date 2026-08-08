# ALI_TO_AL
![ALI_TO_AL](./ALI_TO_AL.svg)

* * * * * * * * * *
The **ALI_TO_AL** function block is a composite function block that converts an **ALI adapter** (data type LINT) into an **AL adapter** (data type LWORD). It serves as an interface converter between different adapter types and enables seamless data transfer in 4diac and IEC 61499 systems.

- **No direct event inputs**

Events are received exclusively via the **ALI_IN** socket adapter.

- **No direct event outputs**

Output events are sent exclusively via the **AL_OUT** plug adapter.

- **No direct data inputs**

Input data (LINT) is provided via the socket adapter **ALI_IN** (data point D1).

- **No direct data outputs**

Output data (LWORD) is provided via the plug adapter **AL_OUT** (data point D1).

### Data Outputs
### Data Inputs
### Event Outputs
### Event Inputs
## Interface Structure
## Introduction
### **Adapters**

| Adapter | Direction | Type | Description |
|---------|----------|-----|--------------|
| **ALI_IN** | Socket | `adapter::types::unidirectional::ALI` | Receives a LINT value and an event. |
| **AL_OUT** | Plug | `adapter::types::unidirectional::AL` | Sends an LWORD value and an event. |

## Functionality

The function block operates internally with a single conversion function block (FB) `F_LINT_TO_LWORD`. As soon as an event (E1) arrives at the socket adapter **ALI_IN**, it is forwarded to the internal converter (`REQ` input). Simultaneously, the LINT value (D1) provided by the adapter is passed to the converter's `IN` input.

The converter transforms the LINT value into an LWORD value and signals completion with its `CNF` output. This event is sent to the plug adapter **AL_OUT** (E1), along with the converted LWORD value (OUT) on data channel D1.

- **Composite Function Block**: The actual type conversion is performed by the embedded function block `F_LINT_TO_LWORD` from the IEC 61131 standard library.
- **Unidirectional Adapters**: The data and event flow is defined from ALI_IN to AL_OUT. Reverse communication is not supported.
- **No Internal States**: The function block does not have its own execution state (no ECC), but forwards events and data directly.


The function block has no internal states. It reacts strictly event-driven: Each incoming event at socket **ALI_IN** triggers exactly one conversion and one output at plug **AL_OUT**.

- **Adapter Bridge**: Used in systems that utilize an ALI adapter (LINT) but require an AL interface (LWORD).

- **Compatibility**: Retrofitting older components that expect LINT to an environment that uses LWORD via AL adapters.

- **AL_TO_ALI**: Performs the reverse conversion from LWORD to LINT.
- **F_LINT_TO_LWORD**: Pure conversion function block without adapter integration; direct data exchange without encapsulation.
- **Other Adapter Converters** (e.g., AL_TO_AL): Same adapter type, no type conversion.

The ALI_TO_AL function block stands out due to its simple plug-and-play capability within an adapter-based design, as it encapsulates all conversion logic and event control in a single block.


The composite function block **ALI_TO_AL** enables clean and standards-compliant conversion of LINT to LWORD data via unidirectional adapters. It is ideal for use in modular automation systems that need to integrate different adapter data types. Reliable and high-performance execution is ensured by utilizing the proven IEC 61131 conversion function.

---

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

## Technical Features
## State Overview
## Application Scenarios
## Comparison with Similar Function Blocks
## Conclusion
### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de