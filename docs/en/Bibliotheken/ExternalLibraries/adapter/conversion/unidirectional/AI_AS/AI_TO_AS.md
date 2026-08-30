# AI_TO_AS

![AI_TO_AS](./AI_TO_AS.svg)

* * * * * * * * * *

## Introduction

The function block **AI_TO_AS** is a composite block that converts an adapter of type `AI` (based on `INT`) into an adapter of type `AS` (based on `SINT`). It serves as an interface converter between different data formats in the IEC 61499 architecture.

## Interface Structure

### **Event Inputs**

The function block does not have its own event inputs. Event control is handled entirely via the adapter input `AI_IN` (see section Adapter). Internally, the adapter's event `E1` is processed.

### **Event Outputs**

The function block (FB) does not have its own event outputs. The result event is provided via the adapter output `AS_OUT` (see section Adapter). After successful conversion, the event `E1` is triggered on the output adapter.

### **Data Inputs**

The FB does not have its own data inputs. The value to be converted, `INT`, is read in via the adapter input `AI_IN` (data point `D1`).

### **Data Outputs**

The FB does not have its own data outputs. The converted `SINT` value is output via the adapter output `AS_OUT` (data point `D1`).

### **Adapter**

| Adapter | Direction | Type | Description |
| --------- | ---------- | ----- | -------------- |
| `AI_IN` | Input (Socket) | `adapter::types::unidirectional::AI` | INT-based adapter input; provides the event `E1` and the data value `D1` (type `INT`). |
| `AS_OUT` | Output (Plug) | `adapter::types::unidirectional::AS` | SINT-based adapter output; receives the event `E1` and passes on the converted data value `D1` (type `SINT`). |

## Functionality

The function block performs a **type conversion from `INT` to `SINT`**.

As soon as an event `E1` arrives at the adapter input `AI_IN`, the corresponding data value `D1` (INT) is read. This value is passed to the internal function block `F_INT_TO_SINT`. The conversion is performed according to the IEC 61131-3 definition; the `INT` value is limited to the value range of `SINT` (-128...127). After successful conversion, the event `E1` is generated at the adapter output `AS_OUT`, and the converted `SINT` value is passed via `D1`.

## Technical Features

- **Numeric conversion**: value-preserving cast (narrowing may truncate, widening/sign-extension is safe).

- **Composite Structure**: The function block is implemented as a composite that uses the standard function block `F_INT_TO_SINT`. This enables easy reuse and a clear separation of the conversion logic.
- **Adapter-based interface**: The inputs and outputs are implemented as unidirectional adapters (`AI` and `AS`), allowing flexible connection to other components with compatible adapter interfaces.
- **No range check**: The underlying function block `F_INT_TO_SINT` does not perform explicit error handling when a value exceeds its range. If the value of `INT` is outside the range of `SINT`, unexpected results or overflows may occur (depending on the target platform).

## State overview

The function block does not have its own state machine. The internal logic follows the simple sequence of function block `F_INT_TO_SINT`:

| State | Description |
| --------- | -------------- |
| **Idle** | Waiting for an event at `AI_IN.E1`. |
| **Convert** | Upon arrival of `E1`, the value from `AI_IN.D1` is read, converted, and passed to `AS_OUT.D1`. Then, `AS_OUT.E1` is triggered. The function block immediately returns to the idle state. |

## Application Scenarios

- **Data Format Adaptation**: When an existing INT interface needs to be integrated into a system that processes only SINT values (e.g., older controllers or limited bus protocols).
- **Adapter Replacement**: Replacing an AI adapter with an AS adapter in an existing component structure without modifying the internal logic.
- **Prototypes/Test Setups**: Fast conversion of test signals between different data widths.

## Comparison with Similar Components

- **AI_TO_AS (INT → SINT)**: Specifically designed for converting INT to SINT using unidirectional adapters.
- **AY_TO_AS (DINT → SINT)**: Converts DINT values to SINT; essentially the same structure, but a different data type.
- **Direct Conversion Without Adapters**: Function blocks like `F_INT_TO_SINT` offer pure type conversion but require separate event and data connections. The `AI_TO_AS` encapsulates these in adapter logic.

## Conclusion

The `AI_TO_AS` function block provides a simple and compact solution for converting an INT-based adapter to a SINT-based adapter. Its composite structure and clear interface definition make it easy to integrate into IEC 61499 applications. The lack of range checking should be considered in safety-critical applications. Overall, it is a useful tool for signal conditioning in heterogeneous automation systems.
