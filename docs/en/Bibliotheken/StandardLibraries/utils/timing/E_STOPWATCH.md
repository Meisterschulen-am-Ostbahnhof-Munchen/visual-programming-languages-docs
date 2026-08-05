# E_STOPWATCH
![E_STOPWATCH](https://user-images.githubusercontent.com/116869307/214154982-af9a1e9b-6839-43e1-8191-1eca65a4308c.png)
* * * * * * * * * *
## Introduction
The **E_STOPWATCH** function block is a high-precision timing module compliant with the IEC 61499-2 standard, developed under the EPL 2.0 license.
The module enables millisecond-accurate timing measurements between events in real-time systems.

![E_STOPWATCH](E_STOPWATCH.svg)

## Interface Structure

### **Event Inputs**
- `START`: Starts timing
- `ET`: Triggers intermediate output of the measured time
- `STOP`: Ends timing and outputs the result
- `RESET`: Resets the stopwatch

### **Event Outputs**
- `EO`: Outputs time difference after STOP
- `ETO`: Outputs time difference after ET trigger
- `RESETO`: Confirms the reset operation

### **Data Outputs**

| Parameter | Type | Description | Accuracy |

|-----------|-----|---------------|-------------|

| `TD` | TIME | Measured time difference | 1 ms |

## Functionality

1. **Start Phase**:

- `START` initializes the time measurement
- Monotone system time is recorded (`NOW_MONOTONIC`)

2. **Measurement Phase**:

- `ET` delivers intermediate results without stopping the measurement
- Multiple triggers are possible

3. **Closing Phase**:

- `STOP` ends the measurement and outputs the final result
- `RESET` resets all values

## Technical Features

✔ **IEC 61499-2 compliant**
✔ **Monotone time measurement** (no system time adjustments)
✔ **Millisecond accuracy**
✔ **Multiple triggers possible** during the measurement
✔ **Eclipse 4diac integration** (Package: eclipse4diac::utils::timing)

## State Machine (ECC)

```mermaid
stateDiagram-v2
[*] --> START
START --> Measure: START
Measure --> STOP: STOP
Measure --> Trig: ET
Measure --> RESET: RESET
Trig --> Trig: ET
Trig --> STOP: STOP
Trig --> RESET: RESET
STOP --> START
RESET --> START
START --> RESET: RESET
## Application Scenarios
- **Performance Measurement**: Algorithm Runtimes
- **Process Control**: Time-Critical Processes
- **System Diagnostics**: Response Times
- **Production**: Cycle Time Measurement

## Example Values

| Operation | Result (TD) |

|-----------|---------------|

| START -> STOP after 1.5s | T#1s500ms |

| START -> ET after 750ms -> STOP after 1.5s | T#750ms (ETO), T#1s500ms (EO) |

| RESET during measurement | T#0s |

## ⚖️ Comparison with Similar Components

| Feature | E_STOPWATCH | Standard Timer | High-Res Timer |

|---------|-------------|----------------|----------------|

| Accuracy | 1 ms | 10 ms | 1 µs |

| Trigger during run | Yes | No | Yes |

| Monotonous timer | Yes | No | Yes |

| Reset function | Yes | Partially | Yes |

``` ## 🛠️ Related Exercises

* [Exercise_020i](../../../../Uebungen/test_B/Uebungen_doc/Uebung_020i.md)]
* [Exercise_020i_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020i_AX.md)]

## Conclusion

The E_STOPWATCH module is the precise instrument for time measurements:

- **Reliable**: Monotonous time base prevents measurement errors
- **Flexible**: Intermediate outputs without interrupting the measurement
- **Simple**: Intuitive operation with Start/Stop/Reset

Ideal for:

- Performance optimizations
- Real-time systems
- Process analyses
- Benchmark tests

*The precise stopwatch for industrial control systems*

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
