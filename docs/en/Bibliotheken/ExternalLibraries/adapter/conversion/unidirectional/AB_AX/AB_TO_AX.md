# AB_TO_AX
![AB_TO_AX](./AB_TO_AX.svg)

* * * * * * * * * *
## Introduction
The function block **AB_TO_AX** is a composite function block (FB) for converting a BYTE signal (via the AB adapter) into a BOOL signal (via the AX adapter). It serves as a converter between two different adapter types of the unidirectional adapter family.
## Interface Structure
### **Adapter (Input)**
- **AB_IN** (Type: `adapter::types::unidirectional::AB`):

Accepts a BYTE value and an associated event. The adapter provides the data via the internal channels D1 (BYTE) and E1 (event).

### **Adapter (Output)**
- **AX_OUT** (Type: `adapter::types::unidirectional::AX`):

Outputs a BOOL value and a triggering event. The adapter provides the result via D1 (BOOL) and E1 (event).

## Functionality
The function block internally uses a `F_NE` comparison block (not equal to). The incoming BYTE signal (AB_IN.D1) is compared to the constant value `BYTE#0`.

- If the BYTE value is not equal to 0, the comparison returns `TRUE`.
- If the BYTE value is equal to 0, the comparison returns `FALSE`.

The process is started by the event `AB_IN.E1`. This triggers the `F_NE` function block. After the comparison is complete, the event `AX_OUT.E1` is triggered, and the result (BOOL) is output via `AX_OUT.D1`.

## Technical Features
- The function block is implemented as a composite, meaning its functionality results from the interconnection of standard function blocks (here, `F_NE`).
- It is designed for use in the 4diac IDE with the IEC 61499-2 specification.
- The adapters `AB` and `AX` are unidirectional, ensuring a clear separation of data and event flows.
- The internal comparison is binary: Each non-zero BYTE value is interpreted as `TRUE`.

## State Overview
The function block does not have its own state machine. All processing is event-driven via internal connections. The `F_NE` function block operates deterministically without intermediate states.

## Application Scenarios
- **Signal Conversion**: A digital sensor provides a byte value (e.g., counter reading or status). AB_TO_AX converts this into a Boolean signal, which, for example, triggers an alarm as soon as the value is not zero.
- **Adapter Bridge**: An AB adapter is used in a control component, but the downstream logic expects an AX adapter. The function block acts as a simple translator.
- **Threshold Replacement**: Replaces an explicit comparison block with a compact adapter converter.

## Comparison with Similar Function Blocks
Other converter function blocks, such as `BOOL_TO_BYTE` or `BYTE_TO_BOOL`, exist as simple data converters, but usually operate at the data level without an adapter. AB_TO_AX integrates the adapter interface, thus enabling seamless integration into adapter-based architectures. Unlike a general comparison function block (`F_NE`), this function block encapsulates the specific conversion logic and offers a clean interface.

## Conclusion
The **AB_TO_AX** function block provides a clean and simple method for converting a BYTE signal from an AB adapter into a BOOL signal for an AX adapter. By using the standard comparison `Ungleich Null`, it is particularly suitable for binary threshold decisions and simplifies reuse in adapter-oriented control projects.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
