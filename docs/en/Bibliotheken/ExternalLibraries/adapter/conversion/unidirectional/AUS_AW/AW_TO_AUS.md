# AW_TO_AUS

![AW_TO_AUS](./AW_TO_AUS.svg)

* * * * * * * * * *
## Introduction

The composite function block `AW_TO_AUS` converts a `WORD` adapter signal into a `USINT` adapter signal. It encapsulates the IEC 61131-3 standard function `F_WORD_TO_USINT` in an adapter-coupled environment, thus enabling seamless integration between different adapter types.
## Interface Structure

The function block has no independent event or data ports at the function block interface level. All communication takes place exclusively via the two adapters.

## **Event Inputs**

None.

## **Event Outputs**

None.

### **Data Inputs**

None.

### **Data Outputs**

None.

### **Adapters**

| Direction | Name | Type | Description |
|----------|------|-----|--------------|
| Socket (Input) | `AW_IN` | `adapter::types::unidirectional::AW` | Expects a `WORD` value via data port `D1` and an event via `E1`. |
| Plug (Output) | `AUS_OUT` | `adapter::types::unidirectional::AUS` | Returns the converted `USINT` value via data port `D1` and an acknowledgment event via `E1`.

## Functionality

1. An incoming event at the adapter socket `AW_IN.E1` triggers the internal conversion module `Convert` (type `F_WORD_TO_USINT`) via its event input `REQ`.
2. Simultaneously, the data value from `AW_IN.D1` (type `WORD`) is forwarded to the data input `Convert.IN`.

3. After conversion, the result (`USINT`) is provided at data output `Convert.OUT` and transferred to data port `AUS_OUT.D1`.

4. The conversion block signals completion via its event `CNF`, which directly activates the event output `AUS_OUT.E1`.

This results in a synchronous, event-driven conversion from a `WORD` value to a `USINT` value.

## Technical Features

- **Bit-reinterpretation**, value-preserving only if the source value fits the narrower destination width (otherwise the upper bits are silently dropped).

- **Composite Pattern**: The block is implemented as a composite function block (FB) that encapsulates the existing standard function `F_WORD_TO_USINT`.
- **Adapter Coupling**: The function block simplifies integration into existing systems that rely on the adapters `AW` and `AUS` by consolidating the conversion into a single block.
- **No Own State Logic**: All logic is delegated; the function block itself has no integrated event control (ECC) and behaves purely directionally.

## State Overview

The function block does not have its own state machine. The sequence is entirely determined by the embedded function `F_WORD_TO_USINT` and the event connections. Therefore, the function block should be considered **stateless**.

## Application Scenarios

- **Adapter Conversion**: When a 4diac application uses an adapter of type `AW` (with `WORD` data), but a subsequent component expects an adapter of type `AUS` (with `USINT` data).
- **Protocol Adaptation**: Simplifies the connection of components that use different data types via their adapter interfaces.
- **Minimal Conversion Overhead**: Ideal when no additional logic is required and only a simple type conversion (e.g., from a 16-bit value to an 8-bit value) needs to be performed.

## Comparison with Similar Function Blocks

- **Direct Use of `F_WORD_TO_USINT`**: This standard function block operates at the data level but requires manual event and data connections. `AW_TO_AUS` encapsulates these connections and provides an adapter-based interface.
- **Other Adapter Converters (e.g., `AW_TO_ABOOL`)**: These differ in their target data type. The presented scheme (Socket -> Conversion Function Block -> Plug) can be implemented analogously for any data type.

## Conclusion

AW_TO_AUS` is a simple yet useful composite function block for converting `WORD` adapter signals to `USINT` adapter signals. It utilizes a proven IEC 61131-3 standard function and offers a clean, adapter-based interface. The function block requires no configuration and integrates seamlessly into event-driven processes. It is particularly suitable for applications where fast and reliable data type conversion without additional logic is desired.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
