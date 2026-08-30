# ADI_TO_AD

![ADI_TO_AD](./ADI_TO_AD.svg)

* * * * * * * * * *
## Introduction

The **ADI_TO_AD** function block is a composite block that performs interface conversion from an **ADI** adapter (DINT-based) to an **AD** adapter (DWORD-based). It functions as a unidirectional converter and enables seamless integration of components with different data adapter types in the 4diac IDE.
## Interface Structure

### **Event Inputs**

The function block does not have its own dedicated event inputs at the interface level. Event control is handled exclusively via the connected **ADI_IN** socket adapter:

- **ADI_IN.E1** – Event that triggers the data conversion.

### **Event Outputs**

There are no separate event outputs at this level either. The output is provided via the **AD_OUT** plug adapter:

- **AD_OUT.E1** – Event triggered after successful conversion.

### **Data Inputs**

- **ADI_IN.D1** – Input of the DINT value to be converted (source adapter).

### **Data Outputs**

- **AD_OUT.D1** – Output of the converted DWORD value (destination adapter).

### **Adapters**

- **ADI_IN** (Socket) – of type `adapter::types::unidirectional::ADI` (DINT data).
- **AD_OUT** (Plug) – of type `adapter::types::unidirectional::AD` (DWORD data).

Both adapters are unidirectional (one event channel and one data channel each).

## Functionality

The function block contains an internal block `F_DINT_TO_DWORD` from the IEC 61131 library, which performs the actual type conversion. The sequence of operations is as follows:

1. An incoming event at **ADI_IN.E1** triggers the **Convert.REQ** input of the internal converter.
2. The converter converts the DINT value received at **ADI_IN.D1** into a DWORD value.
3. After the conversion is complete, **Convert.CNF** signals successful completion and fires the event at **AD_OUT.E1**, while simultaneously outputting the converted value to **AD_OUT.D1**.

This enables transparent, event-driven conversion between the adapter types.

## Technical Features

- **Stores the integer's bit pattern**, as expected for a bit-string destination (truncates if the destination is narrower than the source).

- **Type Conversion**: The actual conversion is performed using the standardized IEC 61131 function block `F_DINT_TO_DWORD`, which ensures bit-perfect transfer of the integer value to the DWORD space (no logical interpretation, only type conversion).
- **Unidirectionality**: The function block is strictly unidirectional and expects exactly one input and one output adapter. Reverse conversion is not supported.
- **Package Structure**: The function block is organized in the package `adapter::conversion::unidirectional` and imports the corresponding IEC library.

## State Overview

As a composite function block, **ADI_TO_AD** has no explicit states of its own. Its behavior is entirely determined by the internal converter:

- **Idle**: Waits for an event at the ADI_IN.

**Idle }: Waits for an event at the ADI_IN. - **Conversion active**: When `Convert.REQ` is set.

- **Completion**: After `Convert.CNF`, the result is provided at the output.

## Application Scenarios

- **Interface adaptation**: When a component provides a DINT adapter, but a downstream module expects a DWORD adapter (e.g., when integrating controllers with different data widths).
- **System modernization**: Older DINT-based sensors or actuators (via ADI) are to be connected to new DWORD-enabled bus systems (via AD).
- **Prototypical development**: Rapid switching between adapter variants without changing the application logic.

## Comparison with Similar Function Blocks

- **Direct Converter Function Blocks**: Unlike pure type converters (such as `F_DINT_TO_DWORD`), **ADI_TO_AD** operates at the adapter level and integrates event control and interface adaptation into a single function block.
- **Bidirectional Adapters**: Function blocks also exist that offer conversion in both directions (e.g., ADI_TO_AD and AD_TO_ADI combined). This function block is specialized for one direction and is therefore more streamlined.
- **Manual Wiring**: Without this function block, the adapters would have to be wired manually internally, and the event signals routed separately – the composite function block encapsulates this complexity.

## Conclusion

The **ADI_TO_AD** function block is a useful and clearly structured composite function block for easy adaptation between DINT- and DWORD-based adapters. It reduces manual wiring effort, utilizes proven IEC conversion logic, and integrates seamlessly into unidirectional data flows. Ideal for developers who need to switch quickly and cleanly between adapter types without delving deeply into internal signal processing.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
