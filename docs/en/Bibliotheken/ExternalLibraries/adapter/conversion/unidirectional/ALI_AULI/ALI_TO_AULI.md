# ALI_TO_AULI

![ALI_TO_AULI](./ALI_TO_AULI.svg)

* * * * * * * * * *
## Introduction
The function block `ALI_TO_AULI` is a composite block that implements bidirectional adapter conversion between the LINT adapter (ALI) and the ULINT adapter (AULI). It serves as a standardized interface for converting a signed 64-bit integer value (LINT) into an unsigned 64-bit integer value (ULINT). The block encapsulates the IEC 61131-3 conversion block `F_LINT_TO_ULINT` and simplifies integration into adapter-based architectures.

## Interface Structure
The block does not have its own event or data interfaces, but only two adapter connections (socket and plug). The internal logic is handled by the embedded sub-module and the direct connection of the adapter signals.

### **Event Inputs**
– None (events are received via the ALI adapter)

### **Event Outputs**
– None (events are sent via the AULI adapter)

### **Data Inputs**
– None (data is received via the ALI adapter)

### **Data Outputs**
– None (data is output via the AULI adapter)

### **Adapter**

| Adapter Type | Direction | Name | Comment |

|------------|----------|------|-----------|

| `adapter::types::unidirectional::ALI` | Socket (Input) | `ALI_IN` | LINT adapter input (provides an event and a LINT value) |

| `adapter::types::unidirectional::AULI` | Plug (output) | `AULI_OUT` | ULINT adapter output (passes on an event and a ULINT value) |

## Functionality
The module operates as a simple pass-through conversion:

1. An incoming event at socket `ALI_IN.E1` triggers the internal module `Convert` (`F_LINT_TO_ULINT`) via its event input `REQ`.

2. Simultaneously, the LINT value provided by the socket (`ALI_IN.D1`) is passed to the data input `IN` of `Convert`.

3. After successful conversion, `Convert` signals an event at its output `CNF`, which is then forwarded directly to the plug `AULI_OUT.E1`.

4. The converted ULINT value (`Convert.OUT`) is then passed in parallel to the data input `D1` of the AULI adapter.

Thus, a complete, event-driven, and data-synchronous conversion is achieved without any additional delay or logic.


## Technical Features

- **Sub-block used**: `iec61131::conversion::F_LINT_TO_ULINT` – standard-compliant type conversion according to IEC 61131-3.

- **Adapter coupling**: The block utilizes 4diac's unidirectional adapter concept and enables loose coupling between different data type interfaces.

- **No state management**: As a composite block, `ALI_TO_AULI` does not have its own internal state; all decisions are made by the sub-block.

- **Platform independence**: The block can be used in any 4diac environment that provides the IEC 61131 conversion blocks.

## State overview
The block itself does not contain a state machine. All state transitions are controlled by the internal `F_LINT_TO_ULINT`, which switches to the "convert" state after an event at input `REQ` and outputs a confirmation event upon completion. Since these states are not externally visible, a detailed description is omitted.

## Application Scenarios

- **System Integration**: Connecting an older control system that uses signed LINT values to a modern component that can only process unsigned ULINT values.

- **Data Conversion in Adapter Chains**: Embedding between two adapters, e.g., in a data preprocessing chain that requires a uniform ULINT interface.

- **Migration**: Replacing LINT-based components with ULINT equivalents without having to change the entire adapter infrastructure.

## Comparison with Similar Components
The library contains analogous converters for other data types, such as `DINT_TO_UDINT` or `REAL_TO_LREAL`. `ALI_TO_AULI` differs in its specific adapter interface and the encapsulation of the conversion component within a composite. While the pure IEC components have individual data and event interfaces, this component enables direct adapter-to-adapter conversion, which facilitates the design of modular and interchangeable components.

## Conclusion
The `ALI_TO_AULI` component offers a simple and reliable way to convert LINT adapters to ULINT adapters. It cleanly encapsulates the standard conversion in an adapter-based architecture, thus contributing to the reusability and interoperability of 4diac applications. By using the proven IEC component, the conversion is correct and platform-independent.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]