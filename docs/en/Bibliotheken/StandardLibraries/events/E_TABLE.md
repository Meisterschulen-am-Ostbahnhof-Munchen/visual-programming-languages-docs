# E_TABLE

<img width="1139" height="202" alt="E_TABLE" src="https://user-images.githubusercontent.com/113907528/204904862-ebdcc4da-7a49-4931-b534-673c9449cf5e.png">

* * * * * * * * * *

## Introduction
The `E_TABLE` (Event Table) is a function block according to IEC 61499 that generates a finite sequence of events with individually definable time intervals. It reads the time intervals from a table (an array) and fires a specified number of events sequentially.

![E_TABLE](E_TABLE.svg)

## Interface Structure

### **Event Inputs**

- **START**: Starts the generation of the event sequence.

- **Connected Data**: `DT`, `N`

- **STOP**: Stops the sequence prematurely.

### **Event Outputs**

- **EO (Event Output)**: The output event that is triggered qzmsdocs000005 times.

- **Associated Data**: qzmsdocs000006

### **Data Inputs**

- **DT**: An array of durations (data type: `TIME`, size: 4). `DT[i]` defines the delay time *before* the qzmsdocs000009th event.

- **N**: The total number of events to be generated (data type: `UINT`, max. 4 for this function block).


### **Data Outputs**

- **CV (Current Value)**: The index of the currently triggered event (0 to N-1) (Data type: `UINT`).

## Functionality

1. **Start of the sequence**: A `START` event triggers the function block. The number of events to be generated is determined by `N`.

2. **Event generation**: The function block processes the table:

- It waits for the time interval defined in `DT[0]`. Then, the first `EO` event is triggered, and `CV` is set to `0`.


- It waits for the time interval defined in `DT[1]`. Then, the second `EO` event is triggered, and `CV` is set to `1`.

- This process repeats until `N` events have been generated.

3. **End of Sequence**: The sequence ends automatically after `N` events have been triggered.

4. **Stop**: A `STOP` event immediately terminates the sequence at any point.


**Example:**

- `N` = 3
- `DT` = `[T#2s, T#5s, T#1s]`
- After a `START` event:

1. After 2 seconds, `EO` is triggered with `CV=0`.

2. 5 seconds later, `EO` is triggered with `CV=1`.

3. 1 second later, `EO` is triggered with `CV=2`.

4. The sequence is complete.


## Technical Features
- **Table-Controlled Time Intervals**: The strength of this function block lies in its ability to define variable time intervals between events, rather than a fixed interval.

- **Sequence Counter**: The `CV` output provides valuable information about the current position in the sequence.

## Application Scenarios

- **Control of Step Sequences**: Triggering steps with varying wait or processing times.

- **Complex Control**: Controlling an actuator with a series of pulses with variable pauses.

- **Test Automation**: Generating a complex, time-defined stimulus sequence for a test object, where the `CV` output can be used for synchronization with the evaluation.

## ⚖️ Comparison with Similar Function Blocks

| Feature | E_TABLE | E_CYCLE | E_N_TABLE |

|--------------|-----------|---------|----------|

| Event Interval | Variable (Array `DT`) | Fixed (`DT`) | Variable (Array `DT`) |

| Outputs | One `EO` channel | One `EO` channel | Multiple (`EO0`..`EO3`) |

| Counter Output (`CV`) | Yes | No | No (internal) |

## 🛠️ Related Exercises

* [Exercise_093](../../../Uebungen/test_B/Uebungen_doc/Uebung_093.md)

## Conclusion
The `E_TABLE` function block is a highly flexible timer for generating complex, finite event sequences. Its ability to read variable time intervals from a table makes it ideal for non-periodic, sequential control tasks. It forms the basis for other function blocks such as `E_N_TABLE`, but unlike the latter, it provides the current counter value as useful output information.