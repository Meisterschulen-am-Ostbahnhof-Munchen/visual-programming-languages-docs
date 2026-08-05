# AI_TO_AULI
![AI_TO_AULI](./AI_TO_AULI.svg)

* * * * * * * * * *
## Introduction
The function block **AI_TO_AULI** serves as a composite block for converting a unidirectional adapter of type `AI` (based on the data type `INT`) into a unidirectional adapter of type `AULI` (based on `ULINT`). It enables the seamless integration of components that use different integer data types without requiring the user to implement the conversion logic.
---

## Interface Structure

The block does not have traditional event or data inputs/outputs, but only adapter interfaces (socket & plug) through which both events and data are transmitted.

### **Event Inputs**

The event input is provided via the socket adapter `AI_IN`.

| Name | Adapter | Comment |

|--------|---------|-------------------------------------|

| `E1` | `AI_IN` | Event that triggers the conversion |

### **Event Outputs**

The event output is provided via the plug adapter `AULI_OUT`.

| Name | Adapter | Comment |

|--------|-----------|----------------------------------------|

| `E1` | `AULI_OUT` | Event after successful conversion |

### **Data Inputs**

Data input is provided via the socket adapter `AI_IN`.

| Name | Adapter | Type | Comment |

|--------|---------|------|------------------------|

| `D1` | `AI_IN` | `INT` | Input data (16-bit integer) |

### **Data Outputs**

Data output is provided via the plug adapter `AULI_OUT`.

| Name | Adapter | Type | Comment |

|--------|-----------|--------|--------------------------|

| `D1` | `AULI_OUT`| `ULINT`| Output data (64-bit unsigned integer) |

### **Adapter**
- **Socket** `AI_IN` : Unidirectional adapter with the interfaces `E1` (event) and `D1` (INT).
- **Plug** `AULI_OUT`: Unidirectional adapter with the interfaces `E1` (event) and `D1` (ULINT).

---

## Functionality

This module performs a simple type conversion from `INT` to `ULINT`. Internally, the IEC 61131 module `F_INT_TO_ULINT` is used. The process is event-driven:

1. An incoming event at socket `AI_IN.E1` triggers the input `REQ` of the conversion module.

2. The data value `AI_IN.D1` (INT) is passed to the input `IN` of the conversion block.

3. The conversion is performed, and the result (ULINT) is provided at the output `OUT`.

4. After the conversion is complete, an event is generated at the output `CNF` of the conversion block, which is forwarded to the plug `AULI_OUT.E1`.

5. Simultaneously, the converted value is sent to the plug `AULI_OUT.D1`.

This ensures a complete, synchronized transfer of the event and data.

---

## Technical Features
- **Adapter-Based Communication:** The module encapsulates the conversion logic in a composite, so the connected components only need to know the respective adapter interfaces.
- **Unidirectional Data Transfer:** Both `AI` and `AULI` are designed as unidirectional adapters; reverse data transfer is not supported.
- **Type Conversion:** The internal module `F_INT_TO_ULINT` performs an extended conversion from 16-bit integer (`INT`) to 64-bit unsigned integer (`ULINT`). Negative `INT` values are converted into large positive `ULINT` values using two's complement (e.g., `-1` → `2^64-1`).
- **No Eigenstates:** The component does not have its own state machine but forwards events and data directly.

---

## State Overview

Since the component is implemented as a pure composite without its own stateful logic, there is no explicit state machine. Its behavior is determined solely by the coupling of the internal components. The functionality is purely combinatorial and event-triggered.

--- ---

## Application Scenarios
- **Adapter Converter:** Integrating sensors or actuators provided as `AI` adapters (INT) into a system that expects `AULI` adapters (ULINT).
- **System Integration:** Use in PLC or automation architectures where different data types need to be standardized.
- **Protocol Adaptation:** Converting 16-bit counter values to 64-bit counter values for extended range.

--

## Comparison with Similar Function Blocks

| Function Block | Source Type | Target Type | Adapter-Based | Custom States |

|-------------------|----------|---------|----------------|-----------------|

| `F_INT_TO_ULINT` | `INT` | `ULINT` | No (pure function block) | No |

| `AI_TO_AULI` | `AI` | `AULI` | Yes (adapter) | No |

| `ANY_TO_ANY` | variable | variable | possible | depending on implementation |

While the basic function block `F_INT_TO_ULINT` only performs data conversion, `AI_TO_AULI` encapsulates this along with event control in an adapter-compatible interface. This increases reusability in adapter-based systems.

... ---

## Conclusion

The function block `AI_TO_AULI` offers a clean, adapter-based solution for converting `INT` to `ULINT` data. It reduces manual effort and the potential for errors during type conversion and integrates seamlessly into existing 4diac projects. Thanks to its simple, event-triggered structure, it is particularly well-suited for unidirectional data flows.

--

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
