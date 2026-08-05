# BYPASS_AX_AX
![BYPASS_AX_AX](./BYPASS_AX_AX.svg)

* * * * * * * * * *
## Introduction
The function block **BYPASS_AX_AX** is used for forwarding and parallel bypass processing of AX signals. It combines a direct pass from input **IN** to output **OUT** with a Boolean OR operation on the incoming data, which is passed to the bypass output **BY_OUT** via an edge-triggered D flip-flop.
```
## Interface Structure
### **Event Inputs**
- **IN.E1** – Signal Input Event
- **BY_IN.E1** – Bypass Input Event

### **Event Outputs**
- **OUT.E1** – Signal Output Event
- **BY_OUT.E1** – Bypass Output Event

### **Data Inputs**
- **IN.D1** – Signal Input Data Value (Type depends on the AX adapter used)
- **BY_IN.D1** – Bypass Input Data Value (same type)

### **Data Outputs**
- **OUT.D1** – Signal Output Data Value (identical to IN.D1)
- **BY_OUT.D1** – Bypass Output Data Value (Result of the OR operation, stored in the flip-flop)

### **Adapters**
The function block uses four adapters of type `adapter::types::unidirectional::AX`:

- **IN** (Socket) – Signal input
- **BY_IN** (Socket) – Bypass input
- **OUT** (Plug) – Signal output
- **BY_OUT** (Plug) – Bypass output

Each AX adapter transmits one event/data pair (E1/D1) in one direction.

## Functionality
The function block implements two parallel paths:

1. **Direct Path:**

An event on **IN.E1** is passed directly to **OUT.E1**, as is the corresponding data value **IN.D1** to **OUT.D1**. This represents a 1:1 pass-through of the signal.

2. **Bypass Path:**

An event on both **IN.E1** and **BY_IN.E1** triggers processing in the function block `OR_2_BOOL`. This block performs a Boolean operation on the data values **IN.D1** and **BY_IN.D1** – a logical OR operation on the two binary inputs.

The result of the operation is applied to the data input **D** of the D flip-flop (`E_D_FF`). The flip-flop's clock is triggered by the feedback signal `OR_2_BOOL.CNF`, i.e., after the OR operation is complete.

The flip-flop's output **Q** is set to **BY_OUT.D1**, and the corresponding event **BY_OUT.E1** is triggered by the flip-flop's output **EO**.

## Technical Features
- **Boolean OR Operation:** The data is not added or mixed, but rather logically ORed. Therefore, the data values are considered Boolean (TRUE/FALSE).
- **Edge-Triggered Flip-Flops:** The bypass value is updated whenever at least one of the two inputs (IN or BY_IN) provides an event. The flip-flop stores the last calculated OR value.
- **Independent Event Propagation:** The direct path is asynchronous – every event on IN is immediately passed to OUT without waiting for the bypass path.

## State Overview
The FB itself does not have its own state machine; however, a binary state is implemented using the internal D flip-flop:

- **State 0:** Flip-flop output Q = FALSE → BY_OUT.D1 = FALSE
- **State 1:** Flip-flop output Q = TRUE → BY_OUT.D1 = TRUE

The state changes to the current D value on each rising edge of the clock (`OR_2_BOOL.CNF`). The initial state is undefined and may need to be initialized externally.

## Application Scenarios
- **Bypass Circuit in Controllers:** A normal signal (IN → OUT) is to be passed through unchanged, while simultaneously creating an OR gate between the normal signal and an additional bypass signal for monitoring purposes.

**State 0:** - **Emergency Activation:** The bypass input can be used for manual override (e.g., "manual operation") while automatic operation continues at the main output.

- **Logical Signal Tracing:** The separate outputs allow both the original signal and the applied logic to be evaluated in parallel.

## Comparison with Similar Function Blocks
- **Simple Pass-Through Function Block (e.g., MOVE_AX):** Passes the signal through 1:1 but does not generate a bypass output. BYPASS_AX_AX additionally offers the logic gate and a second output.
- **OR Function Block without Flip-Flop:** A simple OR gate would continuously update the bypass output without buffering. The integrated flip-flop provides edge-triggered updates, which is advantageous for cyclical control or time-decoupled events.
- **Adapter-based solution with two separate function blocks:** While it would be possible to wire an OR function block and a flip-flop function block separately, BYPASS_AX_AX encapsulates this functionality in a single compact block, reducing the number of connections and simplifying handling.

## Conclusion
The **BYPASS_AX_AX** is a useful function block for applications requiring both direct signal forwarding and a logical OR operation with a stored output. Combining the pass-through and bypass paths in a single block keeps the network structure clear. The use of unidirectional AX adapters makes it compatible with typical industrial communication protocols based on the IEC 61499 standard.
