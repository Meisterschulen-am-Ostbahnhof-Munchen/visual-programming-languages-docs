# AS_MUX_5

![AS_MUX_5](./AS_MUX_5.svg)

* * * * * * * * * *
## Introduction

The function block **AS_MUX_5** implements a generic multiplexer for the adapter interface `adapter::types::unidirectional::AS`. It selects one of the five input adapters (`IN1` to `IN5`) based on an integer index `K` (values 0–4) and forwards its data connection to the output adapter `OUT`. The block is controlled by the event `REQ` and acknowledges the switchover with `CNF`.

## Interface Structure

### **Event Inputs**

| Name | Type | Comment |

|------|-------|------------------------------|

| REQ | Event | Set Index K |

### **Event Outputs**

| Name | Type | Comment |

|------|-------|-------------------------------------|

| CNF | Event | Confirmation of Set Index K |

### **Data Inputs**

| Name | Type | Comment |

|------|------|-----------|

| K | UINT | index |

### **Data Outputs**

None.

### **Adapters**

**Plug (Output):**

| Name | Type | Comment |

|------|-----------------------------------------|----------------------------------------------------------------|
| OUT | adapter::types::unidirectional::AS | IN1 for K = 0, IN2 for K = 1, IN3 for K = 2, IN4 for K = 3, IN5 for K = 4 |

**Sockets (inputs):**

| Name | Type | Comment |
|------|-----------------------------------------|--------|
| IN1 | adapter::types::unidirectional::AS | Input value 1 |
| IN2 | adapter::types::unidirectional::AS | Input value 2 |
| IN3 | adapter::types::unidirectional::AS | Input value 3 |
| IN4 | adapter::types::unidirectional::AS | Input value 4 |

| IN5 | adapter::types::unidirectional::AS | Input value 5 |

## Functionality

This function block operates as a 1-out-of-5 multiplexer at the adapter level. An internal selector evaluates the index (0 to 4) present at the data input `K`. Upon arrival of the event `REQ`, the connection between the selected socket (IN1…IN5) and the plug `OUT` is established. After successful switching, the event `CNF` is output. Each socket and the plug are of type `adapter::types::unidirectional::AS`, so only unidirectional data flows via the adapter interface are supported.


## Technical Features

- **Generic Function Block:** The function block is declared as a generic multiplexer (`eclipse4diac::core::GenericClassName = 'GEN_AS_MUX'`). It can be reused in different projects with the same adapter type.

- **No Own Data Outputs:** The selected adapter connection transports all data directly; the function block itself does not process or buffer any data values.

- **Index Limitation:** The index `K` should be within the valid range 0…4. Values outside this range lead to undefined behavior (no error handling in the XML definition).

- **Copyright Notice:** The function block is licensed under the Eclipse Public License 2.0 and was developed by HR Agrartechnik GmbH.

## State Overview

The function block does not have an explicit state machine in its XML representation. The behavior is event-driven:

- In idle mode, the current connection remains active.

- Upon `REQ`, the new connection is activated according to `K`, and subsequently `CNF` is sent.

## Application Scenarios

- **Sensor Selection:** In a controller with five identical sensors (e.g., distance sensors), the desired sensor can be dynamically switched to the evaluation unit using `AS_MUX_5`.

- **Configurable Signal Sources:** In automation systems that need to switch between different measuring points.

- **Test and Simulation Environments:** Easy switching between different test datasets or simulation models connected via adapters.


## Comparison with Similar Components

- **Standard Multiplexers (e.g., MUX – Data Multiplexer):** These typically operate with data inputs (BOOL, INT, REAL) and output a single data value. `AS_MUX_5`, on the other hand, operates at the adapter level and selects entire connections.

- **Adapter Selector Components:** Similar components exist for other adapter types (e.g., bidirectional). `AS_MUX_5` is specialized for the unidirectional type `AS` and is limited to five inputs.

- **Generic Variants:** The use of the `GenericClassName` attribute allows for easy adaptation to other adapter types by reusing the same logic.


## Conclusion

`AS_MUX_5` is a specialized multiplexer for unidirectional adapter connections of type `AS`. It enables flexible and clean switching between five sources without data conversion. Due to its generic nature and simple event control, it is particularly suitable for modular automation solutions where the selection of different sensor or actuator connections at runtime is required.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]