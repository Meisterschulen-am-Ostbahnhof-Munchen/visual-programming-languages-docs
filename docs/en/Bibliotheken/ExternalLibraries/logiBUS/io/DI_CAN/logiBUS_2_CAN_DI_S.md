# logiBUS_2_CAN_DI_S

* * * * * * * * * *
## Introduction

The function block `logiBUS_2_CAN_DI_S` is a structured data type (struct) used to configure a digital input (DI) for a logiBUS-CAN system. It defines the basic parameters required to address and use a physical input pin on a logiBUS-CAN module. This data type typically serves as input for higher-level function blocks that handle the actual communication via the CAN protocol.
## Interface Structure

This is a structured data type (struct) and therefore has no event or adapter interfaces. Its structure consists of a single data element.
## **Data Inputs**

Since it is a data type, these elements are used as input data within a higher-level function block.

| Name | Data Type | Initial Value | Comment |
|---|---|---|---|
| `Pin` | `USINT` (Unsigned Short Integer) | 255 | Defines the number of the physical input pin on the logiBUS CAN module. |

### **Data Outputs**

*(Not applicable for a structured data type)*

### **Event Inputs**

*(Not applicable for a structured data type)*

### **Event Outputs**

*(Not applicable for a structured data type)*

## **Adapters**

*(Not applicable for a structured data type)*

## Functionality

The data type `logiBUS_2_CAN_DI_S` functions as a configuration container. The value `Pin` specifies which particular digital input of a logiBUS CAN I/O module is to be addressed. The initial value `255` represents a typical invalid or unconfigured state, requiring the user to explicitly assign a valid pin number. A higher-level function block (e.g., a driver function block) reads this structure and uses the `Pin` information to generate or interpret the correct CAN telegrams that query the state (on/off) of the respective input.

## Technical Features

- **Data type `USINT`:** The use of `USINT` (0 to 255) for the pin suggests that the logiBUS hardware can theoretically address up to 256 digital inputs per configuration structure. The value 255 is reserved as the default initial value.
- **Initial value 255:** This value serves as an indicator for an inactive or undefined configuration. It should be replaced with a valid pin number in the application.
- **Package name:** The data type is organized in the package `logiBUS::io::DI_CAN`, which clearly indicates its association with logiBUS CAN input communication.
*
## State Overview

*(Not applicable for a structured data type. The "state" is simply the stored value of the `Pin` variable.)*

## Application Scenarios

This structure type is used in scenarios where digital signals (e.g., switches, limit switches, sensor contacts) are to be read into a controller (e.g., an IEC 61499-based application in 4diac) via a CAN-based logiBUS network. Typical applications include:

- Machine controllers with decentralized, CAN-networked sensors.
- Mobile applications (vehicles, robots) with a robust bus system.
- Systems where digital input signals are distributed over long distances.
*
## ⚖️ Comparison with Similar Function Blocks

Unlike direct I/O function blocks (such as `E_SR` or `E_D_FF`), which process logical states, `logiBUS_2_CAN_DI_S` is a pure **configuration data type**. It is comparable to other structured hardware configuration types in 4diac (e.g., for serial interfaces or other fieldbuses) that encapsulate parameters for hardware connectivity. Its counterpart for digital outputs would be a corresponding struct type (e.g., `logiBUS_2_CAN_DO_S`).

## Conclusion

The `logiBUS_2_CAN_DI_S` data type is an essential and streamlined configuration element for connecting digital inputs to a CAN-based logiBUS system within the 4diac IDE. By encapsulating the pin number in a structured variable, it enables clear, type-safe, and maintainable configuration of the hardware interface in higher-level control algorithms. Using a unique initial value helps to detect misconfigurations early.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
