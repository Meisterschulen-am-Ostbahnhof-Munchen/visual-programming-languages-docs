# AW_TO_ALI

![AW_TO_ALI](./AW_TO_ALI.svg)

* * * * * * * * * *
## Introduction

The **AW_TO_ALI** function block is a composite function block that converts a unidirectional adapter of type **AW** (WORD) into an adapter of type **ALI** (LINT). It is used to convert data between different adapter interfaces without requiring the user to implement the actual conversion logic. Internally, the function block uses the IEC 61131 function block `F_WORD_TO_LINT` and provides typical event/data control via the supplied adapter interfaces.
## Interface Structure

### **Event Inputs**

An event of type **E1** is received via the **Socket AW_IN** (Type: `adapter::types::unidirectional::AW`). This event triggers the conversion of the incoming data value.

### **Event Outputs**

An event **E1** is output via the **Plug ALI_OUT** (Type: `adapter::types::unidirectional::ALI`) after successful conversion. This indicates that the converted value is available at the data output.

### **Data Inputs**

Incoming data is received via the **Socket AW_IN**:

- **D1** (Data Type: WORD) – the 16-bit value to be converted.

### **Data Outputs**

The converted data is output via the **ALI_OUT** plug:

- **D1** (Data type: LINT) – the converted 64-bit value (Long Integer).

### **Adapters**

The module has two adapter interfaces:

- **Socket AW_IN** – Unidirectional input adapter (type AW) that establishes a connection to a previous module that provides WORD data.
- **ALI_OUT** – Unidirectional output adapter (type ALI) that passes the converted LINT data to subsequent modules.

Both adapters are unidirectional, meaning they transmit events and data in only one direction (input → output).

## Functionality

The process within the composite block is strictly sequential:

1. An event **E1** at socket **AW_IN** is forwarded to the internal function block **F_WORD_TO_LINT** (instance name *Convert*) and activates its **REQ input**.
2. Simultaneously, the incoming data value **D1** (WORD) is placed at the **IN input** of the converter.
3. The converter `F_WORD_TO_LINT` performs the type conversion from WORD to LINT and provides the result at its **OUT output**.
4. After the conversion is complete, the converter generates a **CNF event**, which is passed to the **E1 input** of the output adapter **ALI_OUT**.
5. Simultaneously, the converted value (LINT) is transferred from the **OUT output** of the converter to the data output **D1** of the **ALI_OUT adapter**.

This completes the data conversion at a safe, event-driven time.

## Technical Features

- **Composite Block** – The conversion logic is completely encapsulated in an internal network consisting of only a single conversion function block. The block does not have its own ECC state machine.
- **Adapter-Based Interface** – Instead of individual event/data inputs/outputs, adapters are used. This enables a modular, reusable connection in adapter-based control architectures.
- **Package Structure** – The function block is located in the package `adapter::conversion::unidirectional` and uses the converter `iec61131::conversion::F_WORD_TO_LINT` from the IEC 61131 conversion library.
- **Unidirectional Direction** – Data flows only from the input adapter to the output adapter; reverse communication is not supported.
- **License** – The source code is licensed under the Eclipse Public License 2.0 (EPL-2.0), developed by HR Agrartechnik GmbH.

## State Overview

Since this is a composite function block without its own state machine (ECC), there are no defined states. The functionality is entirely controlled by the embedded function block `F_WORD_TO_LINT`, which performs a one-time, event-driven conversion. The function block is always ready when an event arrives at the input adapter. After the conversion, it waits for the next event.

## Application Scenarios

- **Data Conversion in Adapter Chains** – If a control system is based on unidirectional adapters and one component delivers WORD data, but a subsequent component expects LINT data, AW_TO_ALI can be inserted as an intermediary.
- **Connecting Field Devices with Different Bit Widths** – For example, integrating a sensor that delivers 16-bit measured values (WORD) into logic that works with 64-bit values (LINT) (e.g., for high-resolution counters or timestamps).
- **Type Conversion in Libraries** – Extending an existing adapter library with convenient conversion blocks to ensure compatibility between different data formats.

## Comparison with Similar Blocks

| Block | Input (adapter) | Output (adapter) | Conversion | Special Features |
|----------|-------------------|-------------------|---------------|----------------|
| **AW_TO_ALI** | AW (WORD) | ALI (LINT) | WORD → LINT | Unidirectional, Composite |
| `F_WORD_TO_LINT` (IEC 61131) | Single REQ input, IN (WORD) | Single CNF output, OUT (LINT) | WORD → LINT | Standard FB, no adapter |
| `ALI_TO_AW` (hypothetical) | ALI (LINT) | AW (WORD) | LINT → WORD | Reverse direction |

The advantage of AW_TO_ALI lies in its seamless integration into adapter-based systems, whereas the pure IEC component `F_WORD_TO_LINT` would require separate wiring. Components with adapter interfaces simplify control design because they offer standardized plugs/sockets.

## Conclusion

**AW_TO_ALI** is a compact, adapter-based conversion component for converting WORD to LINT data. By utilizing the proven IEC 61131 converter `F_WORD_TO_LINT` and encapsulating it in a composite structure, it offers a clean, event-driven interface for unidirectional adapter applications. The component is particularly suitable for use in modular automation systems where data needs to be exchanged between components with different data widths.
