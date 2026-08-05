# AIS_MUX_4

![AIS_MUX_4](./AIS_MUX_4.svg)

* * * * * * * * * *
## Introduction
The function block **AIS_MUX_4** is a generic AIS multiplexer with four inputs. It selects one of the four AIS adapter inputs (`IN1`–`IN4`) based on an index value `K` (0–3) and forwards its data via the adapter output `OUT`. The block is controlled by the event `REQ`.

## Interface Structure

### **Event Inputs**

| Name | Type | Comment |

|------|-------|-------------------------------|

| REQ | Event | Sets the index `K` and activates the selection |

### **Event Outputs**

| Name | Type | Comment |

|------|-------|-----------------------------------------------------|

| CNF | Event | Confirmation of index selection (after switching) |

### **Data Inputs**

| Name | Type | Comment |

|------|------|------------------------------|

| K | UINT | Index (0 = IN1, 1 = IN2, …) |

### **Data Outputs**
_None. The output data is provided via the adapter plugin `OUT`.

### **Adapter**

| Name | Use | Type | Comment |

|---------|------------|--------------------------------------|-------------------------------------------------------------|

| IN1 | Socket | adapter::types::unidirectional::AIS | First AIS input (for K = 0) |

| IN2 | Socket | adapter::types::unidirectional::AIS | Second AIS input (for K = 1) |

| IN3 | Socket | adapter::types::unidirectional::AIS | Third AIS input (for K = 2) |

| IN4 | Socket | adapter::types::unidirectional::AIS | Fourth AIS input (for K = 3) |

| OUT | Plug | adapter::types::unidirectional::AIS | Output: provides the data of the input selected by `K` |

## Functionality

1. An incoming event `REQ` reads the current value of the data input `K`.

2. Depending on the value of `K` (0–3), the corresponding AIS input (`IN1` for K=0, `IN2` for K=1, `IN3` for K=2, `IN4` for K=3) is routed to the adapter output `OUT`.

3. After successful selection, the event `CNF` is sent.

4. For values outside the range 0–3, the behavior is undefined (the function block relies on valid inputs).


3. ## Technical Features

- **Generic Type**: The function block is declared as a generic FB (`GenericClassName = 'GEN_AIS_MUX'`) and can be parameterized in various type instances.

- **License**: Eclipse Public License 2.0 (EPL-2.0).

- **Package Structure**: The function block is organized in the package `adapter::selection::unidirectional`.

- **AIS Adapter**: All involved inputs and outputs use the same adapter type `adapter::types::unidirectional::AIS`, ensuring a uniform data structure.

## State Overview
The function block does not have an explicit state machine. Its behavior is purely functional:

- **Idle State**: No event is processed; the output `OUT` retains its last set value.

- **Selection Execution**: After receiving `REQ`, the new index is applied and `OUT` is updated; subsequently, `CNF` is output.

## Application Scenarios

- **Data Path Switching**: Selection of one of several AIS data sources in agricultural or automation control systems.

- **Redundancy**: With multiple parallel AIS sensors, a specific source can be activated depending on the conditions.

- **Testing and Diagnostics**: Switching between different measuring points for analysis purposes.

## Comparison with Similar Components
Generic multiplexers exist in the 4diac framework (e.g., `MUX_2`, `MUX_8`). The **AIS_MUX_4** is specifically designed for the AIS adapter type and optimized for unidirectional AIS data. Unlike universal multiplexers with simple data types (e.g., `INT`, `BOOL`), it operates at the adapter level and transmits complex data structures in a single step.

## Conclusion
The `AIS_MUX_4` is a simple yet effective component for selecting one of four AIS inputs. Its generic design and clear event control make it well-suited for modular automation solutions with AIS communication.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
