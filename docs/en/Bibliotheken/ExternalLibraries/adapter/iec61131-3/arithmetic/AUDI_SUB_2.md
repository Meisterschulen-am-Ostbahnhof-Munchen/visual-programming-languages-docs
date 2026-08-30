# AUDI_SUB_2

![AUDI_SUB_2](./AUDI_SUB_2.svg)

* * * * * * * * * *

## Introduction

The function block (FB) `AUDI_SUB_2` is a generic function block for performing arithmetic subtraction. It is based on the generic class `GEN_AUDI_SUB` and uses unidirectional adapters of type `AUDI` for structured and event-driven data transmission. This achieves clean encapsulation of data and events, reducing the complexity of wiring in IEC 61499 applications.

## Interface Structure

Since the block is entirely based on adapters, it does not have any traditional, directly visible event or data pins at the top level. All communication is handled via the adapters.

## **Event Inputs**

*No direct event inputs are available. Event control is encapsulated within the adapters.*

### **Event Outputs**

*No direct event outputs are available. Event control is encapsulated within the adapters.*

### **Data Inputs**

*No direct data inputs are available. Data transmission occurs via the adapter interfaces.*

### **Data Outputs**

*No direct data outputs are available. Data transmission occurs via the adapter interfaces.*

### **Adapters**

#### **Sockets (Input Adapters / Sockets)**

- **IN1** (Type: `adapter::types::unidirectional::AUDI`):
- First input for subtraction (minuend).
- **IN2** (Type: `adapter::types::unidirectional::AUDI`):
- Second input for subtraction (subtrahend).

#### **Plugs (Output Adapters)**

- **OUT** (Type: `adapter::types::unidirectional::AUDI`):
- Output of the function block that provides the result of the subtraction (difference).

--

## Functionality

The function block calculates the mathematical difference between the two values provided via the input adapters according to the following principle:

$$\text{OUT} = \text{IN1} - \text{IN2}$$

As soon as values at the input adapters `IN1` or `IN2` change and a corresponding trigger event is received via the adapter, the calculation is performed internally. The result and the associated update event are then forwarded via the output adapter `OUT`.

---

## Technical Features

- **Generic Implementation:** The `eclipse4diac::core::GenericClassName = 'GEN_AUDI_SUB'` attribute makes the function block flexible. Depending on the implementation of the underlying adapter, it can support various data types.
- **Encapsulation by Adapter:** Using the unidirectional adapter `AUDI` bundles data and event lines. This significantly improves clarity in the 4diac application editor, as fewer lines need to be drawn.

--

## State Overview

The function block behaves like a stateless mathematical operator. There is no internal state loop (ECC states in the classical sense) that is maintained for an extended period. Each activation by an event at the inputs leads to a direct calculation and update of the output.

-- ---

## Application Scenarios

- **Signal Processing:** Subtraction of sensor values (e.g., offset compensation or calculation of differential pressures/temperatures) in systems that are consistently based on the `AUDI` adapter architecture.
- **Control Engineering:** Calculation of the control error ($e = w - x$) by subtracting the actual value from the setpoint.

---

## Comparison with Similar Components

- **Standard SUB Component (IEC 61131-3 / IEC 61499):** A classic `SUB` component has dedicated data inputs (`IN1`, `IN2`), a data output (`OUT`), and event inputs and outputs (e.g., `REQ` / `CNF`). The `AUDI_SUB_2`, on the other hand, bundles these signals in adapters, which improves reusability and modularity in complex architectures.
- **AUDI_ADD_2:** The counterpart for addition. Uses the same adapter interface, but adds the input values ($IN1 + IN2$).

---

## Change Detection

The result is only written to the output plug (`OUT`) and its adapter event only sent if the newly computed value differs from the value currently held on `OUT`. If the result is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.


## Conclusion

The `AUDI_SUB_2` is a specialized, yet flexible, function block for subtraction due to its generic nature. It is ideally suited for service-oriented architectures within 4diac, where a unified interface concept using unidirectional adapters is paramount.
