# AS_TO_AR
![AS_TO_AR](./AS_TO_AR.svg)
* * * * * * * * * *
## Introduction
The function block `AS_TO_AR` is a composite function block that converts a unidirectional adapter of type **AS** (SINT) to an adapter of type **AR** (REAL). It is used to establish a logical connection between components based on different data types – specifically, from a signed 8-bit integer (SINT) to a floating-point number (REAL).
## Interface Structure

### **Event Inputs**

The function block does not have its own dedicated event inputs. Events are received exclusively via the integrated adapter **AS_IN**.

- **AS_IN.E1** – Event from the connected SINT adapter.

### **Event Outputs**
Events are passed on via the integrated adapter **AR_OUT**.

- **AR_OUT.E1** – Event for the connected REAL adapter.

### **Data Inputs**
Data is provided exclusively via the adapter **AS_IN**.

- **AS_IN.D1** – Data value of type **SINT** (signed 8-bit integer).

### **Data Outputs**
Data is output exclusively via the adapter **AR_OUT**.

- **AR_OUT.D1** – Data value of type **REAL** (floating-point number).

### **Adapters**

| Type | Name | Direction | Comment |

|-----|------|----------|-----------|

| `adapter::types::unidirectional::AS` | **AS_IN** | Socket | Input adapter for SINT data |

| `adapter::types::unidirectional::AR` | **AR_OUT** | Plug | Output adapter for REAL data |

## Functionality
The `AS_TO_AR` block behaves as a pure type conversion passthrough. Within the integrated function network, the event `AS_IN.E1` is directly connected to `AR_OUT.E1`, and the data value `AS_IN.D1` is directly connected to `AR_OUT.D1`. The actual conversion from **SINT** to **REAL** is performed implicitly through the adapter definitions of the respective types. The block itself does not execute any additional logic or calculations.

## Technical Features
- **Composite Block**: Conversion is achieved solely through the interconnection of adapters in the function network. It does not have its own state machine (ECC).
- **Package Membership**: The block is included in the package `adapter::conversion::unidirectional`.
- **No Data Storage**: All values are passed on instantly; the block has no internal memory.
- **Implicit Type Conversion**: The conversion from integer (SINT) to floating-point number (REAL) takes place in the periphery of the adapter types.

## State Overview

The `AS_TO_AR` block does not have a state machine (ECC). Its behavior is purely combinatorial and is limited to the direct forwarding of events and data.

## Application Scenarios
- Connecting a sensor that provides its measured values as a SINT adapter to a processing component that expects REAL adapters.
- Transitioning between different '4diac' adapter types in heterogeneous control projects.
- Preparing values for mathematical operators or visualization components that require REAL inputs.

## Comparison with Similar Function Blocks
- **AR_TO_AS** – Performs the reverse conversion from REAL to SINT.
- **General type converters** (e.g., `INT_TO_REAL`) operate at the level of individual data ports, while `AS_TO_AR` converts entire adapter interfaces.
- This function block does not offer adjustable parameters (e.g., rounding modes); more specific conversion would have to be implemented using separate function blocks.

## Conclusion

`AS_TO_AR` is a simple yet useful composite block for adapter type conversion from SINT to REAL. It enables the lossless integration of components with different data types in continuous control sequences and is characterized by its low complexity and direct passthrough.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
