# E_RESTART

![IEC 61499 Service Interface Symbol](https://user-images.githubusercontent.com/113907528/204901925-d33114a6-a86a-4a53-854d-a3f499fc8802.png)

* * * * * * * * * *

## Introduction

The **E_RESTART** is a special service interface function block according to IEC 61499 (Annex A) for controlling restart sequences in distributed automation systems. The block serves as an interface between resources and higher-level controllers.
![E_RESTART](E_RESTART.svg)

## Interface Structure

### **Event Outputs**

- `COLD`: Signals a cold start (full reset)
- `WARM`: Indicates a warm start (partial reset)
- `STOP`: Indicates an upcoming stop command

### **Service Interfaces**

- Left: E_RESTART (FB interface)
- Right: RESOURCE (Device interface)

## Functionality

1. **Cold Start Sequence**:

- Upon an external `start` command to the resource
- Triggers the `COLD` event
1. **Warm Start Sequence**:

- Upon `restart` resource command
- Generation of the `WARM` event
1. **Stop Sequence**:

- Upon receiving the `stop` signal
- Output of the `STOP` event

## Service Sequences (XML Specification)

1. **cold_restart**:

- `start` → `COLD` (Full reinitialization)
1. **warm_restart**:

- `restart` → `WARM` (State-preserving restart)
1. **stopping**:

- `stop` → `STOP` (Ordered Shutdown)

## Technical Features

✔ **Standardized Restart Control** according to IEC 61499 Annex A
✔ **Three Operating Modes** (Cold/Warm/Stop)
✔ **Cross-Resource** Consistency
✔ **EPL 2.0 Open-Source** Implementation

## Application Scenarios

- **Field Device Control**: Ordered Reinitialization
- **System Recovery**: Automatic Restart Routines
- **Energy Management**: Scheduled Shutdown
- **Safety-Critical Systems**: State-Safe Restarts

## ⚖️ Comparison with Similar Function Blocks

| Feature | E_RESTART | E_CYCLE | E_DELAY |
| --------------- | ----------- | ---------- | --------- |
| Purpose | System Control | Time Control | Event Delay |
| Event Type | Control Commands | Periodic | One-Time |
| Standard | Annex A | Core | Core |

## 🛠️ Related Exercises

- [Exercise_174](../../../Uebungen/test_B/Uebungen_doc/Uebung_174.md)

## Conclusion

The E_RESTART block offers a standards-compliant solution for critical system control tasks:

- Standardized restart management
- Separation of cold/warm start logic
- Reliable signal forwarding

It particularly enables the development of robust, fault-tolerant control systems. The clear service interface according to IEC 61499 Annex A ensures interoperability across different device platforms.
