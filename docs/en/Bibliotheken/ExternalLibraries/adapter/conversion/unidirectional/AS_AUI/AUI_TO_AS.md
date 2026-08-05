# AUI_TO_AS

![AUI_TO_AS](./AUI_TO_AS.svg)

* * * * * * * * * *

## Introduction

The function block `AUI_TO_AS` is a composite block that enables the conversion of an **AUI (UINT)** adapter to an **AS (SINT)** adapter.

It encapsulates the necessary signal and data conversion in a reusable unit and provides the converted values via a single adapter output.

## Interface Structure

### **Event Inputs**

The block has **no direct event inputs** at its top level.

The triggering event is provided via socket `AUI_IN` (adapter `adapter::types::unidirectional::AUI`). This event (labeled `E1`) starts the conversion internally.

### **Event Outputs**
At the top level, there are **no direct event outputs**.

The conversion completion event is output externally via plug `AS_OUT` (adapter `adapter::types::unidirectional::AS`) as event `E1`.

### **Data Inputs**
There are **no direct data inputs**.

The input data (data type `UINT`) is fed into the function block via socket `AUI_IN` (channel `D1`).

### **Data Outputs**
There are also **no direct data outputs**. The converted data (data type `SINT`) exits the module via plug `AS_OUT` (channel `D1`).

### **Adapter**

| Direction | Name | Type | Description |

|----------|--------|----------------------------------------|----------------------------------|

| Socket | AUI_IN | `adapter::types::unidirectional::AUI` | Input adapter (UINT data) |

| Plug | AS_OUT | `adapter::types::unidirectional::AS` | Output adapter (SINT data) |


## Functionality

The function block functions as a pure encapsulation of a conversion process:

1. An incoming event via `AUI_IN.E1` triggers the internal function block `Convert` (of type `iec61131::conversion::F_UINT_TO_SINT`).

2. Simultaneously, the data value from `AUI_IN.D1` (of type `UINT`) is forwarded to the input `Convert.IN`.

3. After the conversion is complete, `Convert.CNF` sends an event to `AS_OUT.E1`.

4. The converted value (`SINT`) is transferred from `Convert.OUT` to `AS_OUT.D1`.

This enables end-to-end, event-driven conversion from a UINT adapter to a SINT adapter, without requiring the user to implement the conversion details themselves.

## Technical Features

- **Composite Block:** All connections are encapsulated within a network. The internal logic remains hidden from the calling environment.

- **Use of the Standard Conversion Function:** The actual conversion is performed by the IEC 61131 block `F_UINT_TO_SINT`. This block is externally referenced and imported as a library block.

- **Unidirectional Adapters:** Both the input and output adapters are unidirectional, meaning data flows in only one direction (from input to output).

- **No Own States:** Because this is a composite device, it does not have its own Execution Control Chart (ECC). Its behavior is determined solely by its internal connections.

## State Overview

This device does **not have its own state machine**.

Its operation is purely data flow and event-driven through the interconnection of its constituent elements. There are no defined states such as IDLE, BUSY, or ERROR.

## Application Scenarios

- **Adapter Bridging:** If an application uses adapters with different data types (e.g., AUI with `UINT` and AS with `SINT`), this device can be used as a converter between the adapter interfaces.

- **System Integration:** In heterogeneous control systems where components use different data types, this function block facilitates integration without manual type conversion.

- **Reuse:** The composite function block can be used multiple times in different projects or networks to always provide the same conversion logic.

## Comparison with Similar Function Blocks

- **Other Conversion Adapters:** Similar function blocks exist, such as `SINT_TO_UINT_AS` or generic type converters. The difference lies in the specific type combination (UINT → SINT) and the use of adapters instead of direct event/data inputs.

- **Direct Conversion Without Adapters:** Instead of an adapter-based function block, one could also use the function `F_UINT_TO_SINT` directly and wire the adapter interfaces separately. The composite function block simplifies this through encapsulation.

## Conclusion

The function block `AUI_TO_AS` offers a simple, encapsulated solution for converting a unidirectional UINT adapter to a SINT adapter. By utilizing a standardized IEC 61131 conversion function and clear event handling, it integrates seamlessly into 4diac IDE projects. It is particularly suitable for scenarios where adapters of different data types need to be connected without requiring the user to implement the conversion logic themselves.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)


```