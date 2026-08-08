# ALR_ADD_4

![ALR_ADD_4](./ALR_ADD_4.svg)

* * * * * * * * * *
## Introduction

The function block (FB) **ALR_ADD_4** is a generic arithmetic block for performing an addition operation. It is classified as a standard arithmetic function according to the IEC 61131-3 standard. The block allows up to four input values, provided via unidirectional adapters of type `ALR`, to be added and the result passed to a corresponding output adapter.

## Interface Structure

### **Event Inputs**
*No direct event inputs are available. Synchronization and event control are handled implicitly via the adapters used.*

### **Event Outputs**
*No direct event outputs are available. Event forwarding is implicit via the output adapter.*

### **Data Inputs**
*No direct data inputs are available. Data is transferred entirely via the adapter interfaces.*

### **Data Outputs**
*No direct data outputs are available. Data is transferred entirely via the adapter interface.*

### **Adapters**

#### **Sockets (Input Adapters)**
* **IN1** (Type: `adapter::types::unidirectional::ALR`): First input value (addend 1) for addition.

* **IN2** (Type: `adapter::types::unidirectional::ALR`): Second input value (addend 2) for addition.

* **IN3** (Type: `adapter::types::unidirectional::ALR`): Third input value (addend 3) for addition.

* **IN4** (Type: `adapter::types::unidirectional::ALR`): Fourth input value (addend 4) for addition.

#### **Plugs (Output Adapters)**

* **OUT** (Type: `adapter::types::unidirectional::ALR`): The calculated result of the addition (sum).

## Functionality

The function block `ALR_ADD_4` functions internally as a generic adder (`GEN_ALR_ADD`). As soon as the values at the input adapters `IN1` to `IN4` change, the function block calculates the sum of the incoming values:

$$\text{OUT} = \text{IN1} + \text{IN2} + \text{IN3} + \text{IN4}$$

The result is immediately passed to the output plug `OUT`. Since this is a generic implementation, the specific data type depends on the specification of the `ALR` adapter type used.


## Technical Features

* **Generic Class:** The function block is linked to the value `'GEN_ALR_ADD'` via the attribute `GenericClassName`, giving it high flexibility in processing various compatible data types within the adapter structures.

* **Adapter-Based Coupling:** By exclusively using adapters, the number of connection lines in the 4diac IDE is drastically reduced, resulting in clearer application diagrams.

## State Overview

Since this function block performs a purely combinatorial, mathematical operation, it does not have an internal state machine (Execution Control Chart, ECC). The output directly follows changes in the inputs.

## Application Scenarios

* **Measurement Aggregation:** Summing up to four energy, flow, or power values transmitted via standardized unidirectional adapters.

* **Signal Merging:** Structured bundling of sensor signals in complex control architectures prior to further data processing.

## Comparison with Similar Components

* **Standard Add-in Component:** A classic IEC 61131-3 `ADD` component uses direct data inputs (e.g., `REAL`, `INT`) and often requires explicit event connections (`REQ` / `CNF`). `ALR_ADD_4` encapsulates this data and these events in adapters, simplifying project design.

* **Two-Way Adder (e.g., ALR_ADD_2):** Offers only two inputs. The `ALR_ADD_4` block eliminates the need to cascade multiple smaller adder blocks when summing three or four values.

## Conclusion

The `ALR_ADD_4` block is an efficient and clean solution for arithmetic addition in component- and adapter-based system architectures within 4diac. It promotes reusability and ensures a streamlined system design.