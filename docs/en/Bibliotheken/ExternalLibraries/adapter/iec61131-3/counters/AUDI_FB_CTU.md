# AUDI_FB_CTU
![AUDI_FB_CTU](./AUDI_FB_CTU.svg)

* * * * * * * * * *
## Introduction
The **AUDI_FB_CTU** is an up counter for the **UDINT** data type (32-bit unsigned) that connects via standard **AUDI adapters**. The function block encapsulates the IEC 61131 counting function in an adapter-based architecture and allows triggering of count pulses, reset, and preset operations via adapter events. Every counting-relevant operation (count pulse, reset, setting the preset value) necessarily triggers an output event – regardless of whether the counter value or the output value changes. If only change-based triggering is required, a downstream AX_D_FF function block must be used.
## Interface Structure

### **Event Inputs**

The module does not have traditional event inputs. Instead, the triggering events are introduced **via the adapter sockets**:

* **CU.E1** – Event from the *Count up* adapter: a rising pulse increments the counter by 1.
* **R.E1** – Event from the *Reset* adapter: resets the counter to 0.
* **PV.E1** – Event from the *Preset value* adapter: adopts the current value at the preset input as the new preset value (takes effect immediately, without changing the counter).

All three events are internally multiplexed onto the **REQ** event of the embedded IEC function block `FB_CTU_UDINT`. This means that each of these external pulses triggers processing.

### **Event Outputs**
* **CNF** – Confirmation Event (EventOutput): This event is output after each processing of an incoming event. It is connected to the output adapters so that the connected components are informed about a completed counting operation.

In addition, the following **adapter events** are triggered (via internal wiring):

* **Q.E1** – Event of the *Output* adapter (type AX): Signals the availability of a new output value Q.
* **CV.E1** – Event of the *Count value* adapter (type AUDI): Signals the availability of a new counter reading CV.

These adapter events fire **simultaneously with CNF**, meaning that all three output events are activated simultaneously for every counting-relevant event.

### **Data Inputs**
Data is also provided **via the adapter sockets**:

* **CU.D1** (UDINT, via adapter CU) – Count pulse: Only the value 0 or 1 is evaluated; a positive edge transition (0→1) results in an increment. (The adapter provides the event itself; additionally, the data value can be used, for example, as an edge-weighted signal.)
* **R.D1** (UDINT, via adapter R) – Reset signal: A value ≠ 0 resets the counter.
* **PV.D1** (UDINT, via adapter PV) – Preset value: The value present here is adopted as the new preset value upon arrival of the PV.E1 event. (The data value is only read in the event of an explicit PV event.)

### **Data Outputs**
* **Q.D1** (BOOL, via adapter Q) – Output signal: `TRUE` when the current meter reading is **≥ PV** (Preset Output).
* **CV.D1** (UDINT, via adapter CV) – Current meter reading (Count Value).

### **Adapters**

| Adapter Type | Direction | Name | Short Description |

|-------------|----------|------|------------------|

| `AX` (unidirectional) | Socket (Input) | CU | Provides the count pulse event and an edge-weighted data value. |

| `AX` (unidirectional) | Socket (Input) | R | Provides the reset event and reset switch. |

| `AUDI` (unidirectional) | Socket (Input) | PV | Provides the preset event and preset numeric value. |

| `AX` (unidirectional) | Plug (Output) | Q | Provides the output binary (Q) as an event and data value. |

| `AUDI` (unidirectional) | Plug (Output) | CV | Provides the current counter reading as an event and data value. |

## Functionality
The **AUDI_FB_CTU** delegates all its counting logic to the internal IEC block `FB_CTU_UDINT`. For each incoming event (CU.E1, R.E1, or PV.E1), its **REQ** input is activated. The internal counter then executes the following logic:

1. **Reset first**: If **R** ≠ 0, the counter is set to 0.

2. **Count pulse**: If **CU** ≠ 0 and a rising edge transition has occurred since the last call, CV is incremented by 1.

3. **Preset takeover**: If **PV.E1** has been triggered, the value at PV is stored as the new threshold (PV).

4. **Comparison**: If CV ≥ PV (stored preset value), **Q** = TRUE; otherwise, it is FALSE.

After processing, the events **CNF**, **Q.E1**, and **CV.E1** are output simultaneously, regardless of whether Q or CV has changed.

## Technical Features
* **Adapter-Based**: All inputs and outputs are implemented as standardized unidirectional adapters (`AX` for binary, `AUDI` for numeric values). This allows for flexible interconnection in adapter-oriented architectures.
* **Event Multiplexing**: The three input events (CU, R, PV) are multiplexed onto a common REQ. This simplifies internal wiring but means that a reset or preset operation also triggers the output event.
* **No On-Change Filtering**: As described in the header comment, the function block fires **always** on every processing operation. For change-only triggering, an AX_D_FF must be added (e.g., on Q and CV).
* **Data Width**: All counter and preset values are implemented as **UDINT** (32-bit unsigned).
* **State Maintenance**: The internal counter stores the current counter value and the preset threshold across multiple calls.

## State Overview
The function block does **not have its own state machine** (ECC). The state logic is entirely contained within the embedded IEC function block `FB_CTU_UDINT`. Its essential states are:

* **Idle**: Waiting for an event (CU.E1, R.E1, or PV.E1).
* **Processing** (during internal processing): Evaluating the input data (CU, R, PV), updating the counter and the Q and CV outputs.
* **Emitting**: Outputting the CNF, Q.E1, and CV.E1 events.

An explicit error state is not provided.

## Application Scenarios
* **Event counting in adapter-based automation systems** – e.g., counting workpieces on a conveyor belt, where the sensor is connected via an AX adapter.
* **Time or pulse counter with reset** – The reset adapter can, for example, be a manual push button.
* **Reaching a threshold** – The PV input allows for dynamic threshold setting; as soon as the counter reading reaches or exceeds this value, Q becomes active.
* **Integration into modular systems** – Thanks to the standardized adapters (AUDI, AX), the module can be easily integrated into existing adapter-based libraries.

## Comparison with similar modules
* **Unlike classic IEC CTU modules** (e.g.,`CTU_UDINT` (without adapter): These have direct event and data inputs but do not require adapter wrappers. The AUDI_FB_CTU offers the advantage of a standardized interface but requires specific adapter mapping.
* **Unlike CTU blocks with on-change triggering**: Blocks that only fire when there are actual value changes avoid unnecessary event floods. The AUDI_FB_CTU always fires, which can be compensated for by adding an AX_D_FF.
* **Comparison to the AUDI_FB_CTD** (down counter): The internal IEC block would then be `FB_CTD_UDINT`; interfaces and behavior are analogous, only the counting direction and the condition for Q differ (Q is active when CV ≤ 0).

## Conclusion

The **AUDI_FB_CTU** is a robust, adapter-based up counter that can be seamlessly integrated into adapter-oriented automation solutions. High interoperability is achieved through the encapsulation of a standardized IEC counter and the use of AUDI/AX adapters. The characteristic of firing on every event is acceptable for many applications or can be corrected by downstream filtering. This component is particularly suitable for modular, expandable control architectures based on adapter protocols.
