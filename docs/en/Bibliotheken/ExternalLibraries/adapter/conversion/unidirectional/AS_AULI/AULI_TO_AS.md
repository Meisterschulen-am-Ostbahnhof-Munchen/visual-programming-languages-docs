# AULI_TO_AS

![AULI_TO_AS](./AULI_TO_AS.svg)

* * * * * * * * * *
## Introduction

The **AULI_TO_AS** function block is a composite module for converting a unidirectional **AULI** adapter (ULINT) to a unidirectional **AS** adapter (SINT). It encapsulates the type conversion of unsigned 64-bit integers to signed 8-bit integers and provides seamless connectivity between components with different data type requirements in the 4diac framework.
## Interface Structure

The module does not have separate event or data ports at the top level. All communication takes place exclusively via two adapters.

## **Adapters**

| Adapter | Direction | Type | Description |
|---------|----------|-----|--------------|
| `AULI_IN` | Socket (Input) | `adapter::types::unidirectional::AULI` | Provides an event `E1` and a data value `D1` of type `ULINT`. |
| `AS_OUT` | Plug (Output) | `adapter::types::unidirectional::AS` | Provides an event `E1` and a data value `D1` of type `SINT`. |

### **Event Inputs (via adapter)**

- `AULI_IN.E1` – Starts the conversion of the incoming ULINT value.

### **Event Outputs (via adapter)**

- `AS_OUT.E1` – Confirms completion of the conversion and indicates that the new SINT value is valid.

### **Data Inputs (via adapter)**

- `AULI_IN.D1` – ULINT value to be converted (value range 0 … 2²⁴⁻¹).

### **Data Outputs (via adapter)**

- `AS_OUT.D1` – Conversion result as a SINT value (value range −128 … 127).

## Functionality

The module internally uses the IEC 61131 conversion function `F_ULINT_TO_SINT`. When the input adapter receives the event `E1`, the current value of `AULI_IN.D1` is read and converted. The result is then passed to `AS_OUT.D1`, simultaneously triggering the event `AS_OUT.E1`.

The processing is purely event-driven and occurs without intermediate storage of internal states.

## Technical Features

- **Value Range Loss:** Since `ULINT` covers a very large range of values (0 … 2⁶⁴−1), while `SINT` can only represent −128 … 127, conversion for values outside the SINT range leads to overflow or saturation (according to the IEC 61131 definition). This should be taken into account during application.
- **Unidirectional Adapters:** The block is designed for data flow in one direction – from the input to the output adapter. It cannot be used for bidirectional communication.
- **License:** The block is provided under the Eclipse Public License 2.0.

## State Overview

The block does not have an explicit state machine or internal state registers. It behaves like a purely combinatorial function triggered by an event. There is no persistent storage of values or processing states.

## Application Scenarios

- **Sensor Integration:** A sensor delivers data in ULINT format, but a downstream module expects SINT values (e.g., for a simple display or threshold logic).
- **Protocol Adaptation:** Heterogeneous automation systems where adapters use different data types can be connected using this function block in a type-compatible manner.
- **Data Reduction:** Targeted conversion of large numerical ranges into smaller formats to save memory or bus bandwidth (at the expense of accuracy).
- **Sensor Integration:**
## Comparison with Similar Function Blocks

- **`AULI_TO_INT`** – Converts to `INT` (16-bit, -32768 … 32767), larger value range than SINT, but still lossy with large numbers.
- **`AULI_TO_DINT`** – Converts to `DINT` (32-bit, -2³¹ … 2³¹−1), covers a significantly larger portion of the ULINT range and is the better choice for many applications.
- **`ULINT_TO_SINT` (direct)** – A simple function block without adapter encapsulation; `AULI_TO_AS` provides the same service in an adapter-based environment.

## Conclusion

The **AULI_TO_AS** is a lean, purpose-built converter for unidirectional adapters. It enables the easy integration of components based on the SINT data type into a ULINT-dominated system. However, due to the large difference in value ranges, users must consider potential overflow or saturation effects and, if necessary, switch to wider data types.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
