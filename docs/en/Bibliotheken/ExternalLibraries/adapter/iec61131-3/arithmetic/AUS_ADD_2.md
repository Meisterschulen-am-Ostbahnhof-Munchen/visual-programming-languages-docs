# AUS_ADD_2

![AUS_ADD_2](./AUS_ADD_2.svg)

*(Graphical representation of the function block not available)*

* * * * * * * * * *
## Introduction
The function block `AUS_ADD_2` is a generic function block (Generic FB) for performing arithmetic addition. It is used to add two input signals and output the result. The special feature of this block lies in the use of standardized, unidirectional adapters (`AUS`), which greatly simplifies and encapsulates the signal and data wiring within Eclipse 4diac.

## Interface Structure

### **Event Inputs**

*This function block does not have direct event inputs. Event control is handled via the adapters.*

### **Event Outputs**
*This function block does not have direct event outputs. Event control is handled via the adapters.*

### **Data Inputs**
*This function block does not have direct data inputs.*

### **Data Outputs**
*This function block does not have direct data outputs.*

### **Adapters**

#### **Sockets (Input Adapters / Jacks)**
* **IN1** (Type: `adapter::types::unidirectional::AUS`): The first addend of the addition.

* **IN2** (Type: `adapter::types::unidirectional::AUS`): The second addend of the addition.


#### **Plugs (Output Adapters)**

* **OUT** (Type: `adapter::types::unidirectional::AUS`): The result of the addition (sum of `IN1` and `IN2`).

---

## Functionality
The `AUS_ADD_2` module functions as an arithmetic adder based on adapters. As soon as a new event with a data value arrives at the input adapters `IN1` or `IN2`, the function block adds the two values:

$$ OUT = IN1 + IN2 $$

The result, along with the corresponding trigger event, is output via the output adapter `OUT`. Since these are unidirectional adapters, the data and control flow is exclusively from the inputs to the output.

---

## Technical Features
* **Generic Function Block:** The attribute `eclipse4diac::core::GenericClassName` with the value `'GEN_AUS_ADD'` defines the function block as a generic type. This allows for flexible adaptation to different data types defined by the adapter structures.


 * **Encapsulation:** By using adapters instead of individual event and data pins, the system design becomes clearer and less prone to wiring errors.

---

## State Overview
Since this component is essentially a mathematical operation, it does not have a complex internal state diagram (ECC). It reacts to incoming data at adapters `IN1` and `IN2`, calculates the sum, and forwards the result directly to `OUT`.

---

## Application Scenarios
* **Measurement Processing:** Adding two sensor values or applying an offset to a measured value, which is supplied via an adapter.

* **Setpoint Calculation:** Combining base setpoints and correction values in process automation.


* * **Structured Programming:** Used in complex control systems where data and event lines are bundled in adapters to improve clarity.

---

## Comparison with Similar Function Blocks
Compared to a standard addition function block (such as `ADD` from the IEC 61131-3 library), which has discrete data and event pins (such as `REQ`, `CNF`, `IN1`, `IN2`, `OUT`), `AUS_ADD_2` completely encapsulates these interfaces in adapters. This drastically reduces the number of visible connection lines in the 4diac editor and promotes object-oriented design.


---

## Conclusion

`AUS_ADD_2` is an efficient, generic auxiliary block for arithmetic addition in IEC 61499 applications. Its consistent use of unidirectional adapters makes it ideally suited for modern, modular software architectures in industrial automation.