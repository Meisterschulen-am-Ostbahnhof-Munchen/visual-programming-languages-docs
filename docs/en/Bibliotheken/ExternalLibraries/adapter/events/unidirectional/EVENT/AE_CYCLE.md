# AE_CYCLE

* * * * * * * * * *

## Introduction
The function block **AE_CYCLE** (Adapter Event Cycle) serves as a periodic event generator. It generates an output event at regular intervals, defined by a timer. Unlike the standard `E_CYCLE` block, this function block uses an adapter for signal output, making it particularly suitable for architectural patterns based on event adapters.

## Interface Structure

### **Event Inputs**
* **START**: Starts the periodic generation of events. When this event is triggered, the timer is activated.

* **STOP**: Stops the generation of events and interrupts the current cycle.

### **Event Outputs**
* *No direct event outputs are available (see adapters).*

### **Data Inputs**
* **DT** (TIME): The cycle time. This value determines the interval between two consecutive events.

### **Data Outputs**
* *No data outputs available.*

### **Adapter**
* **EO** (Plug): An adapter of type `adapter::types::unidirectional::AE`. The periodically generated event is output via this adapter (specifically via the adapter event `E1`).

## Functionality
The **AE_CYCLE** is implemented as a Composite Function Block. Internally, its logic is based on the standard block `E_DELAY`.

1. **Start**: When the `START` event occurs, the internal `E_DELAY` block is started with a duration of `DT`.


2. **Delay & Trigger**: After the time specified by `DT` has elapsed, the internal module generates an output event.

3. **Feedback (Loop)**: This internal event performs two functions:

* It is forwarded to the adapter **EO** to output the signal.

* It is fed directly back to the `START` input of the internal `E_DELAY`.

4. **Cycle**: This feedback immediately restarts the timer, creating a continuous loop.

5. **Stop**: The `STOP` event immediately interrupts the internal `E_DELAY` module and ends the loop.


## Technical Features
* **Encapsulation**: The function block encapsulates the logic of an oscillator circuit (feedback loop) and makes it available via a simplified interface.

* **Adapter Usage**: The use of the `AE` adapter (Adapter Event) enables clean separation and grouping of event flows, compatible with the `adapter::events::unidirectional` package.

## State Overview
Since this is a Composite Function Block, it does not have its own state machine (ECC). The implicit state is determined by the internal `E_DELAY`:

* **Inactive**: After initialization or `STOP`.

* **Running**: After `START`, while the timer is running or being retriggered.


## Application Scenarios

* **Heartbeat Signals**: Generating a status signal for higher-level systems or watchdogs.

* **Polling**: Periodically querying sensor data (trigger for `READ` operations).

* **Blinking**: Controlling indicator lights (in combination with toggle logic).

* **Timed Sequences**: Generating a clock signal for step sequences or periodic calculations.

## ⚖️ Comparison with Similar Function Blocks

* **E_CYCLE**: This is the direct standard counterpart from the IEC 61499 library. `E_CYCLE` offers the same functionality but uses a direct `EO` event output instead of an adapter.

* **E_DELAY**: `AE_CYCLE` is based on `E_DELAY`. While `E_DELAY` only forwards an event with a single delay, `AE_CYCLE`, due to its internal circuitry, ensures an endless repetition.

* **E_TRAIN**: Generates a limited number of pulses (pulse train), while `AE_CYCLE` runs indefinitely until stopped.

## Conclusion
The **AE_CYCLE** is a useful utility block for developers working with event adapters within the 4diac environment. It abstracts the necessary feedback logic for generating periodic signals and integrates seamlessly into adapter-based software architectures.


---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]