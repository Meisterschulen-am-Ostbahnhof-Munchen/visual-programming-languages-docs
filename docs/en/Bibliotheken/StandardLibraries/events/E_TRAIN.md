# E_TRAIN

<img width="1139" height="202" alt="E_TRAIN" src="https://user-images.githubusercontent.com/116869307/214142742-8ce9523e-eb2b-416c-afe8-109fb601dd20.png">

* * * * * * * * * *

## Introduction
The `E_TRAIN` (Event Train) is a function block according to IEC 61499 that generates a finite sequence of events ("event train") at fixed time intervals. After starting, `N` events are generated at intervals of `DT`.

![E_TRAIN](E_TRAIN.svg)

## Interface Structure

### **Event Inputs:**

- **START**: Starts the generation of the event sequence.

- **Related Data**: `DT`, `N`
- **STOP**: Prematurely stops the ongoing generation of the event sequence.

### **Event Outputs:**

- **EO (Event Output)**: The output event that is triggered periodically.

- **Related Data**: `CV`

### **Data Inputs:**

- **DT (Delay Time)**: The time interval between each `EO` event (Data type: `TIME`).

- **N**: The total number of events to be generated (Data type: `UINT`).


### **Data Outputs:**

- **CV (Current Value)**: The counter value indicating the index of the currently triggered event (0 to N-1) (Data type: `UINT`).

## Functionality

1. **Start of the Sequence**: A `START` event triggers the function block. An internal counter is reset, and the parameters `N` (count) and `DT` (time interval) are applied. The timer for the first event is started.

2. **Event Generation**:

- After the time specified in `DT` has elapsed, the first `EO` event is triggered. The output of `CV` has the value `0`.

- Immediately afterward, the timer for the next event is restarted.

- After another time interval `DT`, the next `EO` event is triggered with `CV=1`.

3. **End of Sequence**: This cycle repeats until `N` events have been generated. After the last event (with `CV = N-1`) is triggered, the function block stops automatically.

4. **Stop**: A `STOP` event can terminate the sequence prematurely at any time.


## Technical Features

- **Pulse Generator**: Generates a fixed number of pulses at constant intervals.

- **Internal Counter**: The module uses an internal counter (`E_CTU`) to track the number of generated events.

- **Sequence Counter**: The output (`CV`) provides valuable information about the current position in the sequence.

## Application Scenarios

- **Stepper Motor Control**: Generates an exact number of steps (`N`) at a defined speed (determined by `DT`).

- **Dosing Processes**: Triggers dispensing processes (`N`) at intervals of `DT`.

- **Test Sequences**: Sending a defined number of test triggers to a device under test.

## ⚖️ Comparison with similar building blocks

| Feature | E_TRAIN | E_CYCLE | E_TABLE |

|--------------|-----------|----------|----------|

| Event Interval | Fixed (`DT`) | Fixed (`DT`) | Variable (Array `DT`) |

| Event Count | Finite (`N`) | Infinite | Finite (`N`) |

Counter Output (`CV`) | Yes | No | Yes |

## 🛠️ Related Exercises

* [Exercise_035a2](../../../Uebungen/test_B/Uebungen_doc/Uebung_035a2.md)]
* [Exercise_035a2_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_035a2_AX.md)]
* [Exercise_091](../../../Uebungen/test_B/Uebungen_doc/Uebung_091.md)]

## Conclusion
The `E_TRAIN` module is ideal for applications requiring a fixed number of events within a constant time interval. It combines the functionality of a clock (`E_CYCLE`) with a counter to generate a controlled, finite pulse sequence. The `CV` output provides useful feedback on the sequence's progress.


---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 E_CTU Event Counter module on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/event-function-blocks/e_ctu/)


```