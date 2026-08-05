# AD_TO_AUDI
## Introduction
The AD_TO_AUDI function block is a specialized adapter conversion module. It is used to convert a unidirectional **AD** (DWORD) adapter socket into a unidirectional **AUDI** (UDINT) adapter plug.
Internally, the module uses the standard conversion function `F_DWORD_TO_UDINT` to ensure clean type conversion between the bit string format (DWORD) and the numeric format (UDINT).
![AD_TO_AUDI](AD_TO_AUDI.svg)
## Interface Structure

### **Adapters**
- **AD_IN** (Socket): Input adapter of type `AD` (DWORD).
- **AUDI_OUT** (Plug): Output adapter of type `AUDI` (UDINT).

## Functionality
As soon as an event (`E1`) arrives at `AD_IN` along with data (`D1`), the DWORD value is internally converted into a UDINT value. This is then immediately passed on via the `AUDI_OUT` adapter (event `E1`, data `D1`).

## Technical Features
✔ **Direct adapter-to-adapter coupling**.

✔ **Standard-compliant conversion** through the use of `F_DWORD_TO_UDINT`.

✔ **Event-driven**: Every update at the input immediately triggers an update at the output.

## Application Scenarios
- Connecting ISOBUS input blocks (which often return DWORD values) to adapter-based numerical processing logic.
- Protocol and type adaptation in complex block networks.

## 🛠️ Related Exercises
* [Exercise_011_AUDI](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_011_AUDI.md)
