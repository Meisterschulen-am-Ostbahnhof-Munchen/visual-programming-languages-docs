# AL_TO_AX
![AL_TO_AX](./AL_TO_AX.svg)

* * * * * * * * * *
## Introduction
The function block `AL_TO_AX` is a composite function block that performs a unidirectional adapter conversion from a `AL` adapter (data type `LWORD`) to a `AX` adapter (data type `BOOL`). It enables the simple conversion of an LWORD signal into a Boolean signal, which is then typically passed to subsequent BOOL-based adapters or function blocks. The function block checks whether the incoming LWORD value is non-zero and returns `TRUE` if so.
## Interface Structure

The function block does not have its own event or data inputs/outputs, but uses only adapter interfaces:

* **Socket (Input):** `AL_IN` – Receives a `AL` adapter (contains an LWORD and an event).
* **Plug (Output):** `AX_OUT` – Provides a `AX` adapter (contains a BOOL and an event).

Internal connections are handled via the adapter elements:

### **Event Inputs**

(via the AL_IN adapter)

* **`AL_IN.E1`** – Event input; triggers the conversion.

### **Event Outputs**

(via the AX_OUT adapter)

* **`AX_OUT.E1`** – Event output; signals the completion of the conversion.

### **Data Inputs**

(via the AL_IN adapter)

* **`AL_IN.D1`** (`LWORD`) – The LWORD value to be converted.

### **Data Outputs**

(via the AX_OUT adapter)

* **`AX_OUT.D1`** (`BOOL`) – The result of the conversion: `TRUE` if `AL_IN.D1 ≠ 0`; otherwise `FALSE`.

### **Adapter**
- **AL_IN** – Socket for the `adapter::types::unidirectional::AL` adapter (LWORD-based)
- **AX_OUT** – Plug for the `adapter::types::unidirectional::AX` adapter (BOOL-based)

## Functionality
The function block internally uses the function block `F_NE` ("not equal") from the IEC 61131 library. This compares the incoming LWORD value (`AL_IN.D1`) with the constant value `LWORD#0`. If the values are not equal, `F_NE.OUT` returns the value `TRUE`; otherwise, it returns `FALSE`.

`` The event-driven sequence is as follows:

1. An event at `AL_IN.E1` triggers the input `F_NE.REQ`.

2. `F_NE` performs the comparison and places the result at `F_NE.OUT`.

3. Upon completion, `F_NE` sends an event to `F_NE.CNF`, which is connected to `AX_OUT.E1`.

4. Simultaneously, the result `F_NE.OUT` is transferred to `AX_OUT.D1`.

Thus, with each event at the input, an updated Boolean output is provided at the output.

## Technical Features
- **Type Conversion:** The function block converts an LWORD value not bitwise, but as an integer into a BOOL value. Any non-zero LWORD results in `TRUE`.
- **Adapter-Based:** By using the standardized unidirectional adapters (`AL` and `AX`), the function block can be used in any 4diac network that supports these adapter types.
- **Latency:** Processing occurs synchronously with the input event. The output is updated in the same execution cycle.
- **No State Storage:** The function block is purely combinatorial; it does not store any values between calls.

## State Overview
The `AL_TO_AX` function block does not have its own state machine. Its behavior is purely data flow-driven by the incoming event. Therefore, a state overview is not available.

## Application Scenarios
- **Threshold Detection:** Conversion of an LWORD sensor signal (e.g., counter reading, bitmask) into a Boolean signal that indicates whether a non-zero value is present.
- **Coupling of LWORD and BOOL Adapters:** In heterogeneous systems where one functional block provides an LWORD-based adapter, but the next block expects a BOOL adapter.
- **Error Detection:** An LWORD error register (e.g., 0 = no error, ≠0 = error) is translated into a simple BOOL signal "error present".

## Comparison with Similar Components
- **Direct Converters (e.g., `LWORD_TO_BOOL`):** These usually only convert the least significant bit or define a fixed bit. The `AL_TO_AX` block, on the other hand, uses zero comparison, so any set bit or non-zero value is interpreted as `TRUE`.
- **Adapter Converters:** Generic adapter converters exist that handle various data types (e.g., `ANY_TO_BOOL`). The specialized `AL_TO_AX` block is tailored to the aforementioned adapter combination and requires no external parameterization.

## Conclusion
The `AL_TO_AX` function block offers a simple and reliable way to convert a unidirectional LWORD-based adapter into a BOOL-based adapter. The use of zero comparison ensures unambiguous interpretation. Integration into existing 4diac networks is straightforward thanks to the standardized adapter interfaces. This component is particularly well-suited for fast, event-driven conversions without requiring additional memory and is a practical addition to adapter conversion in industrial automation.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
