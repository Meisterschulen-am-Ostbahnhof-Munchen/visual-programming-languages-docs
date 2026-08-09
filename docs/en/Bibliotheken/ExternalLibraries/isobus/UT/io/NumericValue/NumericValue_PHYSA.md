# NumericValue_PHYSA

![NumericValue_PHYSA](./NumericValue_PHYSA.svg)

* * * * * * * * * *
## Introduction

The function block **NumericValue_PHYSA** is an input service interface function block (SIFB) according to ISO 11783-6. Its function is to provide a physical REAL value via an AR adapter (adapter type *unidirectional::AR*). Internally, it encapsulates the block `NumericValue_PHYS` and all its logic for converting and providing the value.
## Interface Structure

### **Event Inputs**

| Name | Type | Description |
|------|-----|--------------|
| INIT | Initializes the block (with parameters and object pool) |
| REQ | Event | Triggers the output of the current physical value |

### **Event Outputs**

| Name | Type | Description |
|------|-----|-------------|
| INITO | EInit | Confirmation of successful initialization |

### **Data Inputs**

| Name | Type | Description |
|------|-----|-------------|
| QI | BOOL | Input qualifier (enables/controls processing) |
| PARAMS | STRING | Parameters for the service (e.g., configuration string) |
| stObj | *NumericObjectPool_S* | Object pool properties: Object ID (UINT16), scale, offset, decimal places |

### **Data Outputs**

| Name | Type | Description |
|------|-----|-------------|
| QO | BOOL | Output qualifier (indicates successful processing) |
| STATUS| STRING | Status message (OK or error text) |

### **Adapter**

| Name | Type | Description |
|------|-----|-------------|
| rPhys | *adapter::types::unidirectional::AR* | Adapter interface for outputting the physical REAL value (event channel `E1` and data channel `D1`) |

## Functionality

This function block is implemented as a wrapper around the internal function block `NumericValue_PHYS`. All inputs and outputs are directly connected to the inner function block:

- Events `INIT` and `REQ` are forwarded directly to `NumericValue_PHYS`.
- The initialization confirmation event `INITO` of the inner function block is routed externally.
- The output event `IND` of `NumericValue_PHYS` is connected to the event input `rPhys.E1` of the adapter, so that the adapter receives an event with each new value calculation.
- Events `INIT` and `REQ` are forwarded directly to `NumericValue_PHYS`.
- The initialization confirmation event `INITO` of the inner function block is routed externally. - The data inputs (`QI`, `PARAMS`, `stObj`) are wired to the inner FB.
- The data outputs (`QO`, `STATUS`) come directly from the inner FB.
- The physical REAL value from `NumericValue_PHYS.rPhys` is placed on the data channel `rPhys.D1` of the adapter plug.

Thus, the FB is a pure connector that extends the functionality of `NumericValue_PHYS` with a standardized adapter interface, without implementing any additional logic itself.

## Technical Features

- **Data Types Used:** The physical properties of the measured value (scaling, offset, decimal places) are defined via the structured type `logiBUS::utils::conversion::phys::NumericObjectPool_S`.
- **Adapter Coupling:** The AR adapter (unidirectional) enables loose coupling to subsequent function blocks that consume the physical value.
- **Type Hash:** The function block carries an attribute `eclipse4diac::core::TypeHash` to identify the exact version.
- **No Internal State Machine:** The function block delegates all state logic to the encapsulated function block.

## State Overview

Since the FB (Function Block) does not have its own state machine, its state is entirely determined by its internal state:

1. **Initialization Phase:** After the event `INIT`, the FB is configured. It is only operational after `INITO`.
2. **Operation Phase:** With each `REQ` event, the current physical value is calculated and output via the adapter.
3. **Error State:** In case of faulty initialization or invalid parameters, `STATUS` is populated with a corresponding text message, and `QO` is set to FALSE.

## Application Scenarios

- **ISOBUS Control Units:** This function block is ideally suited for converting sensor data (e.g., speed, pressure, temperature) into a standardized adapter interface, as required in agricultural machinery according to ISO 11783-6.
- **Measurement Acquisition with Scaling:** Raw values can be converted into physical units using the parameter structure with individual offsets and scaling factors.
- **Modular Systems:** The adapter interface allows multiple output blocks to be easily connected to various consumers (e.g., visualization, logic).

## Comparison with Similar Function Blocks

- **NumericValue_PHYS** (without the "A" suffix): The pure function block without an adapter interface. It provides the physical value only as a data output (`rPhys`). This function block adds the adapter plug to enable coupling via a standardized channel.
- **NumericValue_RAW / NumericValue_SCALED** (hypothetical): These blocks would deliver raw or scaled values without reference to an object pool. In contrast, `NumericValue_PHYSA` uses the structure `NumericObjectPool_S` with explicit conversion parameters.

## Conclusion

The function block `NumericValue_PHYSA` offers a clean, adapter-based interface for outputting physical REAL values. By encapsulating all the conversion logic in `NumericValue_PHYS`, it remains lean and maintainable. Its use is recommended wherever ISO 11783-6 compliant physical measurement values need to be provided in a modular automation system.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
