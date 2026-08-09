# AUI_MUL_3

![AUI_MUL_3](./AUI_MUL_3.svg)

* * * * * * * * * *

## Introduction

The function block `AUI_MUL_3` is used for the mathematical multiplication of three input values. It is a generic function block (Generic FB) based on the higher-level class `GEN_AUI_MUL`. The special feature of this block lies in the use of unidirectional adapters of type `AUI` (Adapter Unidirectional Interface), which encapsulate both the data and the associated events. This ensures a clear and modular structure within 4diac applications.

## Interface Structure

### **Event Inputs**

*This function block does not have direct, dedicated event inputs. Event control is handled entirely via the connected adapters.*

### **Event Outputs**

*This function block does not have direct, dedicated event outputs. Event forwarding is handled via the output adapter.*

### **Data Inputs**

*There are no direct data inputs. Data is transferred via the input adapters.*

### **Data Outputs**

*There are no direct data outputs. Data output is handled via the output adapter.*

### **Adapters**

#### **Sockets (Input Interfaces)**

* **IN1** (Type: `adapter::types::unidirectional::AUI`): First multiplicand.
* **IN2** (Type: `adapter::types::unidirectional::AUI`): Second multiplicand.
* **IN3** (Type: `adapter::types::unidirectional::AUI`): Third multiplicand.

#### **Plugs (Output Interface)**

* **OUT** (Type: `adapter::types::unidirectional::AUI`): Result of the multiplication ($OUT = IN1 \cdot IN2 \cdot IN3$).

---

## Functionality

As soon as a new event is signaled at one of the input adapters (`IN1`, `IN2`, or `IN3`), the function block reads the current values of the three inputs.

 The arithmetic multiplication is calculated as follows:

$$ Result = Value(IN1) \cdot Value(IN2) \cdot Value(IN3)$$

The result is passed to the output adapter `OUT`, and a corresponding output event is triggered via this adapter to inform subsequent function blocks of the update.

Since the function block is declared as generic (`GEN_AUI_MUL`), it adapts flexibly to the data types of the connected adapters (e.g., `INT`, `REAL`, `LREAL`), as long as these are supported by the adapter type used.

---

## Technical Features

* **Generic Type:** By defining it as a generic function block, it can be flexibly used for various numeric data types without having to create a separate function block for each type.
* **Encapsulation by Adapters:** The use of the unidirectional `AUI` adapters significantly reduces the number of visible connection lines in the 4diac editor, as data and trigger events are bundled in a single connection.

--

## State Overview

The function block operates purely event-driven:

1. **Wait State:** The function block waits for a trigger event on one of the sockets (`IN1`, `IN2`, `IN3`).
2. **Calculation:** After an event occurs, the data is read and multiplied.

-- 3. **Output:** The result is applied to the plug `OUT`, the plug's send event is triggered, and the function block returns to standby mode.

---

## Application Scenarios

* **Volume Calculation:** Calculation of a three-dimensional volume (length \cdot \cdot \bdot \cdot \bdot \bdot \bdot \bdot \bdot \bdot \bdot \bdot \bdot \bdot \bdot \bdot \bdot \bdot \bdot \bdot \bdot \bdot \bdot \bdot \bdot \bdot \bdot \bdot \bdot \bdot \bdot \bdot \bdot \c ... ---

## Comparison with Similar Function Blocks

Compared to a classic, non-generic IEC 61131-3 standard function block, the `MUL` offers:

* **Less Cascading:** Standard multipliers often only have two inputs. To multiply three values, two function blocks would have to be cascaded. The `AUI_MUL_3` accomplishes this in a single step.
* **Improved Overview:** While classic function blocks require separate event and data lines, the adapter concept used here significantly simplifies the visual application design in the 4diac IDE.

--

## Conclusion

The `AUI_MUL_3` is a highly efficient and reusable function block for arithmetic calculations. By combining generic data processing with modern adapter technology, it is ideally suited for clean, clear and maintainable control architectures in IEC 61499 environments.