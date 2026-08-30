# E_DELAY

## 🎧 Podcast

- [E_DELAY in IEC 61499: Precise, Cancelable Time Delay in Control Systems ](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/E_DELAY-in-IEC-61499-Przise--Abbrechbare-Zeitverzgerung-in-Steuerungssystemen-e3674le)

## Introduction

The **E_DELAY** is a key functional block in the IEC 61499 standard for industrial control systems. As an event-driven timer, it enables the delayed triggering of events with a configurable duration and the option to cancel. This block is widely used in time-controlled automation processes.
![E_DELAY](E_DELAY.svg)

## Structure of the E_DELAY Block

### Interface

**Event Inputs:**

- `START`: Initializes the delay
- `STOP`: Terminates the active delay

**Event Outputs:**

- `EO` (Event Output): Triggered after the delay has elapsed

**Data Inputs:**

- `DT` (Delay Time): TIME value for the delay duration

## Functionality

1. **Delay Start:**

- On the `START` event, the timer starts with the set time `DT`
- During runtime, further `START` events ignored
1. **Delay Termination:**

- The `STOP` event immediately terminates the active delay
- No `EO` event is generated
1. **Delay Completion:**

- The `EO` event is triggered exactly after `DT`
- If DT ≤ T#0s, immediate triggering occurs without delay

## Technical Features

✔ **Precise Time Control** (millisecond-accurate delay)

✔ **Termination Function** for flexible process control

✔ **Event-driven** (no cyclical call required)

✔ **Real-time capable** for industrial applications

## Application Scenarios

- **Machine Safety**: Delayed shutdown of systems
- **Process Control**: Time-controlled process steps
- **Alarm Management**: Delayed fault messages
- **Test Automation**: Time-controlled test sequences

## ⚖️ Comparison with similar function blocks

| Feature | E_DELAY | E_CYCLE | E_PULSE |
| --------------- | --------- | --------- | --------- |
| Operating principle | Single delay | Continuous cycle | Single pulse |
| Abort option | Yes | Yes | No |
| Time parameters | DT (Delay) | DT (Cycle time) | PT (Pulse duration) |

## 🛠️ Related exercises

- [Uebung_018](../../../Uebungen/test_B/Uebungen_doc/Uebung_018.md)
- [Uebung_020b](../../../Uebungen/test_B/Uebungen_doc/Uebung_020b.md)
- [Uebung_020b_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_020b_AX.md)
- [Uebung_020d](../../../Uebungen/test_B/Uebungen_doc/Uebung_020d.md)
- [Uebung_020d_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_020d_AX.md)
- [Uebung_024](../../../Uebungen/test_B/Uebungen_doc/Uebung_024.md)
- [Uebung_025](../../../Uebungen/test_B/Uebungen_doc/Uebung_025.md)
- [Uebung_026](../../../Uebungen/test_B/Uebungen_doc/Uebung_026.md)
- [Uebung_160b](../../../Uebungen/test_B/Uebungen_doc/Uebung_160b.md)
- [Exercise_160b_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_160b_AX.md)

## Conclusion

The E_DELAY function block is an indispensable tool for time-controlled automation processes. Its main advantages are:

- Precise and flexible timing control
- Immediate response to control events
- Robust integration into distributed control architectures

Thanks to its reliable operation and compliance with IEC 61499, it is ideally suited for safety applications and complex process control in industrial environments. Its cancel function makes it particularly valuable for flexible production scenarios.
