# logiBUS_DI_Events_S

* * * * * * * * * *
## Introduction
The structured data type `logiBUS_DI_Events_S` is used to configure events for digital inputs (DI) within the logiBUS framework. It defines the event type that can be assigned to a specific digital input channel. This data type is an essential component for parameterizing logiBUS I/O function blocks.

## Interface Structure
This block is a pure structured type and does not have any event or adapter interfaces in the conventional sense of a function block. Its structure is used as an input or output data parameter in other function blocks.

### **Data Inputs**
Not applicable – This is a data type.

### **Data Outputs**
Not applicable – This is a data type.

### **Adapters**
Not applicable – This is a data type.

## Functionality

The data type `logiBUS_DI_Events_S` encapsulates a single variable (`EType`) that represents an event type code. The default value is set to `255`, which typically corresponds to an inactive or unconfigured state. Specific values (e.g., 0, 1, 2, ...) are used to identify specific events (such as edge transitions) that can then be processed by higher-level control logic.

## Technical Features
* **Data Type:** This is a structured data type (`STRUCT`) that is used as a complex data parameter in other function blocks.

* **Initial Value:** The contained variable `EType` is pre-initialized with the value `255`. This value likely serves as a placeholder or "invalid" indicator.

* **Base Type:** The variable `EType` is of type `USINT` (Unsigned Short Integer, 0-255), which provides a limited and efficient range of values for event codes.

## State Overview
Since this is a passive data type, there is no state machine. The "state" is the stored value of the variable `EType`.

## Application Scenarios
This structured data type is primarily used in conjunction with logiBUS I/O function blocks, for example:

* As an element in an array for configuring all digital inputs of a module.

* As a parameter to specify which physical event (e.g., rising edge) should trigger a logical event in the control program.


## ⚖️ Comparison with Similar Function Blocks

Unlike function blocks (FBs) such as `E_R_TRIG` or `F_TRIG`, which independently generate edge events, `logiBUS_DI_Events_S` is a pure configuration data type. It provides the information about *which* hardware event should be translated into such a logical edge event by a separate driver or hardware abstraction block.

## Conclusion
The `logiBUS_DI_Events_S` is a fundamental configuration block within the logiBUS architecture. It enables flexible and parameterizable mapping of hardware events at digital inputs to software-based processing routines. Its simple structure, reduced to a `USINT`, ensures efficiency and ease of use in higher-level configuration structures.