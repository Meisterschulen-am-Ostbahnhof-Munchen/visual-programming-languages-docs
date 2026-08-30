# AS_MUL_4

![AS_MUL_4](./AS_MUL_4.svg)

*(No image available)*

* * * * * * * * * *
## Introduction

The function block `AS_MUL_4` is a generic function block (Generic FB) for IEC 61499, designed for the arithmetic multiplication of four input values. Instead of traditional data and event pins, this block uses adapter connections (`AS` - unidirectional) to transmit data and the associated execution control in encapsulated form. This results in a cleaner design in the 4diac IDE, as the number of visible connection lines is drastically reduced.

## Interface Structure

### **Event Inputs**

This function block does not have direct, independent event inputs. Event control is handled entirely via the connected adapters.

### **Event Outputs**

This function block does not have direct, independent event outputs. Event control for subsequent function blocks is transmitted via the output adapter.

### **Data Inputs**

There are no direct data inputs. Data is transferred via the input adapters.

### **Data Outputs**

There are no direct data outputs. The result is provided via the output adapter.

### **Adapters**

This function block is based entirely on adapter-based communication.

#### Sockets (Inputs)

- **IN1** (Type: `adapter::types::unidirectional::AS`): First multiplicand (Input 1).
- **IN2** (Type: `adapter::types::unidirectional::AS`): Second multiplicand (Input 2).
- **IN3** (Type: `adapter::types::unidirectional::AS`): Third multiplicand (Input 3).
- **IN4** (Type: `adapter::types::unidirectional::AS`): Fourth multiplicand (Input 4).

#### Plugs (Connectors / Outputs)

- **OUT** (Type: `adapter::types::unidirectional::AS`): Result of the multiplication (`IN1 * IN2 * IN3 * IN4`).

---

## Functionality

As soon as new values or a corresponding trigger event are received via the adapter sockets, the function block performs the arithmetic multiplication of the four input values:

$$ OUT = IN1 × IN2 × IN3 × IN4

The result and the corresponding output event are then passed on to the subsequent logic elements via the adapter plug `OUT`.

 ---

## Technical Features

- **Generic Character:** By assigning it to the generic class `GEN_AS_MUL`, the function block can flexibly adapt to various numeric data types (e.g., `INT`, `REAL`, `LREAL`), provided the connected adapters of type `AS` use the same data type.
- **Unidirectional Adapters:** Using the type `adapter::types::unidirectional::AS` ensures that the data flow is clear and direct from the inputs to the output.
- **Compact Design:** Encapsulating data and event channels in adapters keeps the application diagram in 4diac clear and concise.
- ---

## State Overview

Since `AS_MUL_4` is a mathematical, stateless function block, no complex internal state diagram (ECC) exists.

- **Ready / Idle:** The block waits for incoming events at sockets `IN1` to `IN4`.
- **Calculation:** Upon receiving a trigger event, the values are updated, multiplied, and directly passed to `OUT`.

--

## Application Scenarios

- **Scaling of Measured Values:** Multiplying a sensor value by several calibration and correction factors.
- **Volume Calculations:** Calculating a volume from three dimensions (length × width × height) multiplied by a density factor.
- **Cascaded Gainers:** Calculation of total loop gains in control engineering where four different gain factors need to be multiplied.

---

## Comparison with Similar Components

- **Standard `MUL` component (IEC 61131-3):** This requires separate data lines for each value and at least one trigger event (REQ/CNF). `AS_MUL_4` simplifies this by using adapters, requiring only five connections (4 input adapters, 1 output adapter).
- **`AS_MUL_2` / `AS_MUL_3`:** Offer the same adapter-based functionality but are limited to two or three input values, respectively. `AS_MUL_4` eliminates the need for additional intermediate steps and temporary auxiliary variables when combining four factors.
- ---

## Change Detection

The result is only written to the output plug (`OUT`) and its adapter event only sent if the newly computed value differs from the value currently held on `OUT`. If the result is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.


## Conclusion

The `AS_MUL_4` is a highly efficient, clear, and modern function block for arithmetic calculations in IEC 61499. The consistent use of unidirectional adapters keeps the application design uncluttered while maintaining the full flexibility of a generic data type.
