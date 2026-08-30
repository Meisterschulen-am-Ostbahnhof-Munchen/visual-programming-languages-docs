# AL_TO_AW

![AL_TO_AW](./AL_TO_AW.svg)

* * * * * * * * * *
## Introduction

The AL_TO_AW function block is a composite module that converts an LWORD input adapter of type AL (unidirectional) into a WORD output adapter of type AW (unidirectional). It encapsulates the conversion function and provides a simple interface for converting 64-bit data to 16-bit data in the 4diac IDE.
## Interface Structure

The module has no discrete event or data ports, but only adapter interfaces (socket/plug). The following overview shows the available adapters:

### **Event Inputs**

No separate event inputs. The event signal is routed via the AL_IN adapter (socket).

### **Event Outputs**

No separate event outputs. The event signal is output via the AW_OUT adapter (Plug).

### **Data Inputs**

No separate data inputs. Data is read via the AL_IN adapter.

### **Data Outputs**

No separate data outputs. Data is output via the AW_OUT adapter.

### **Adapters**

- **AL_IN** (Socket) – Type: `adapter::types::unidirectional::AL`

LWORD input adapter; contains one event signal and one data signal (E1, D1).

- **AW_OUT** (Plug) – Type: `adapter::types::unidirectional::AW`

WORD output adapter; Contains one event signal and one data signal (E1, D1).

## Functionality

The function block operates in an event-driven manner:

1. An event at socket **AL_IN** (E1) triggers the internal conversion function block `F_LWORD_TO_WORD`.
2. Simultaneously, the LWORD data (D1) is forwarded from the input adapter to the `IN` input of the conversion function block.
3. The conversion function block performs the conversion from LWORD (64-bit) to WORD (16-bit).
4. After successful conversion, an event is generated at the `CNF` output of the conversion function block, which is then passed to the output adapter **AW_OUT** (E1).
5. The converted WORD data (16 bits) is retrieved from the `OUT` output of the conversion function block and passed to the data output of the adapter (D1).

The entire logic consists of a direct connection chain without intermediate states or delays.

## Technical Features

- **Bit-reinterpretation** (structural copy between bit-string types; truncates on narrowing, zero-extends on widening).

- **Use of standardized IEC 61131 conversion** – Internally, the function block `F_LWORD_TO_WORD` from the IEC 61131 library is used.
- **Adapter-based interface** – The function block is fully integrated into 4diac's adapter concepts and can be easily integrated into existing systems with unidirectional AL and AW adapters.
- **No side effects** – The conversion occurs without storage or buffering; each incoming event triggers exactly one output.
- **Compatibility** – Suitable for applications where 64-bit LWORD data signals need to be reduced to 16-bit WORD signals (e.g., when connecting older controllers or fieldbuses).

## State Overview

The function block has no internal states. It is a purely combinational transformation without sequential logic or state machines.

## Application Scenarios

- **Protocol Conversion** – In automation systems that use different data word widths (e.g., converting 64-bit measured values to 16-bit outputs).
- **Interface Adaptation** – When a system provides LWORD data, but a downstream adapter only processes WORD data.
- **Testing and Simulation Tasks** – For easily converting test data between different adapter types.

## Comparison with Similar Function Blocks

- **F_LWORD_TO_WORD** (direct function block) – Offers the same conversion, but without adapter encapsulation. AL_TO_AW integrates this conversion directly into an adapter-based environment.
- **Other Adapter Conversions** – Similar function blocks exist for other data type pairs (e.g., DWORD_TO_WORD). AL_TO_AW is specifically designed for the LWORD↔WORD combination.
- **Custom Composite Function Blocks** – This function block demonstrates how to efficiently implement recurring conversion tasks in the 4diac IDE through encapsulation.

## Conclusion

AL_TO_AW is a compact and clearly structured composite function block for converting an LWORD adapter to a WORD adapter. It utilizes the proven IEC conversion function, offers an adapter-compliant interface, and is ideally suited for integration into 4diac projects that require clean separation of data word widths.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
