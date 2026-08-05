# AUDI_TO_AR
![AUDI_TO_AR](./AUDI_TO_AR.svg)
* * * * * * * * * *
## Introduction
The function block `AUDI_TO_AR` is a composite function block (FB) that converts a UDINT-sized integer received via a unidirectional AUDI adapter into a REAL value and outputs it via a unidirectional AR adapter. It encapsulates the conversion logic, thus enabling clean interface adaptation between different adapter types.
## Interface Structure

This FB has no direct event or data inputs/outputs. All communication takes place exclusively via adapter interfaces.

### **Event Inputs**

None.

### **Event Outputs**

None.

### **Data Inputs**

None.

### **Data Outputs**

None.

### **Adapters**

| Name | Type | Direction | Description |

|------|-----|----------|--------------|

| `AUDI_IN` | `adapter::types::unidirectional::AUDI` | Socket (Input) | Returns a UDINT value and an associated event. The adapter provides an internal event output `E1` and a data output `D1` (UDINT data type). |

| `AR_OUT` | `adapter::types::unidirectional::AR` | Plug (Output) | Outputs the converted REAL value. The adapter has an internal event input `E1` and a data input `D1` (data type REAL).

## Functionality

1. An external signal triggers the event `AUDI_IN.E1`.

2. This event is forwarded to the internal conversion block `F_UDINT_TO_REAL` (type `iec61131::conversion::F_UDINT_TO_REAL`) (`Convert.REQ`).

3. Simultaneously, the UDINT value of `AUDI_IN.D1` is passed to the data input `Convert.IN`.

4. The conversion block performs the conversion from UDINT to REAL.

5. Upon completion, it triggers the event `Convert.CNF`, which is passed on to the event input `AR_OUT.E1`.

6. The converted REAL value is written from `Convert.OUT` to the data input `AR_OUT.D1` and is thus available at the AR adapter.

## Technical Features
- The conversion uses an IEC 61131-3 standard function block (`F_UDINT_TO_REAL`), which is instantiated within the Composite FB.
- The adapters are implemented as unidirectional interfaces, which enforces a clear data flow direction (from the AUDI to the AR adapter).
- The Composite FB does not generate any state logic of its own, but delegates all processing to the internal conversion function block.

## State Overview

The function block does not have its own state machine. Its functionality follows the simple sequence:

- **Waiting for input event** – as long as `AUDI_IN.E1` is not active, the function block remains passive.
- **Conversion** – after `AUDI_IN.E1` arrives, the integrated `F_UDINT_TO_REAL` is executed.
- **Output** – after successful conversion, `AR_OUT.E1` is triggered and the real value is provided.

## Application Scenarios
- Connecting a UDINT-based counter (e.g., pulse counter) to a controller that expects real values for calculations or visualizations.
- Converting adapter signals between different data types in a modular, adapter-based communication architecture.
- As a building block in a library for type-safe adapter conversions.

## Comparison with similar building blocks

This function block is specifically designed for the combination of AUDI (UDINT) and AR (REAL) adapters. Comparable building blocks exist for other data types, e.g.:

- `SINT_TO_AR` (SINT → REAL)
- `AUDI_TO_AI` (UDINT → INT)

The advantage of this building block lies in its clear encapsulation and reusability within an adapter-based system design.

## Conclusion

The `AUDI_TO_AR` function block offers a simple yet effective way to convert UDINT data to REAL data via adapter interfaces. By using an IEC standard component and purely adapter-based communication, it is easy to understand, maintain and can be used in many automation projects.