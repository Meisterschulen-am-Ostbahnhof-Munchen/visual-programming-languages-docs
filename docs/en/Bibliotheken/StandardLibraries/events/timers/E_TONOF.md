![E_TONOF](E_TONOF.svg)

# E_TONOF

**Important note: This function block requires only one event and no cyclic calls. It does not have an output ET and does not display the elapsed time.**

## Image

![image](https://github.com/user-attachments/assets/e09eae11-e153-429f-8eaf-6bfff456f35a)

## Text

## Description

The **E_TONOF** function block is a standardized function block type (FBType) according to the **IEC 61499** standard, used for time-delayed switching operations in industrial automation systems. This function block combines the functions of an **On-Delay Timer** and an **Off-Delay Timer** in a single block. It allows for the time delay of both the switching on and off of a signal.


### General Description:

- **Name**: E_TONOF

- **Type**: Standard Timer Function Block (On/Off Delay Timing)

- **Purpose**: This function block is used to implement time-delayed switching operations in control systems. It is particularly useful in applications where a delay is required when switching signals on or off.

- **License**: This function block is licensed under the Eclipse Public License 2.0 (EPL-2.0).

---

### Interface Description:

#### **Event Inputs:**

1. **REQ** (Normal Execution Request):

- **Type**: Event

- **Description**: This event triggers the normal execution of the function block. It is used to start or update the timer.

- **Associated Variables**:

- **IN**: The input value that starts the timer.

- **PT_ON**: The preset duration for the on-delay.

- **PT_OFF**: The preset duration for the off-delay.

2. **R** (Reset):

- **Type**: Event

- **Description**: This event resets the timer. When this event is triggered, the timer is stopped, and all internal states are reset.

#### **Event Outputs**:

1. **CNF** (Execution Confirmation):

- **Type**: Event

- **Description**: This event confirms the execution of the function block. It is triggered when the timer has expired or a state change has occurred.

- **Associated Variable**:

- **Q**: The output value indicating the timer's state.

#### **Input Variables:**

1. **IN**:

- **Type**: BOOL

- **Description**: The input value that starts the timer. When **IN** is set to `TRUE`, the on-delay starts. When **IN** is set to `FALSE`, the off-delay starts.

2. **PT_ON**:

- **Type**: TIME

- **Description**: The preset duration for the on-delay. This time is measured from the moment **IN** is set to `TRUE`.

3. **PT_OFF**:

- **Type**: TIME

- **Description**: The preset duration for the off-delay. This time is measured from the moment **IN** is set to `FALSE`.

#### **Output Variables:**

1. **Q**:

- **Type**: BOOL

- **Description**: The output value that indicates the timer's state. **Q** is set to `TRUE` after the On-Delay has elapsed and remains at `TRUE` until the Off-Delay has elapsed.

--

### Functionality:

1. **On-Delay**:

- When **IN** is set to `TRUE`, the On-Delay timer (**PT_ON**) starts.

- After **PT_ON** expires, **Q** is set to `TRUE`.

2. **Off-Delay**:

- When **IN** is set to `FALSE`, the off-delay timer (**PT_OFF**) starts.

- **Q** remains at `TRUE` until **PT_OFF** expires, and is then reset to `FALSE`.

3. **Reset**:

- When the **R** event is triggered, the timer is reset, and **Q** is immediately set to `FALSE`.

--

### Application Examples:

- **Machine Control**: Delayed response to sensors or switching commands, e.g. B. to prevent motor overload.

- **Process Automation**: Time-controlled switching operations in industrial processes, e.g., in conveyor belts or heating controls.

---

### Summary:

The **E_TONOF** block is a powerful tool in IEC 61499 for implementing time-delayed switching operations in industrial automation systems. It combines the functions of a switch-on and switch-off delay timer in a single block and also offers the option of resetting the timer via a reset event. This makes it particularly flexible and versatile for use in complex control tasks.

## 🛠️ Related Exercises

* [Exercise_020g](../../../../Uebungen/test_B/Uebungen_doc/Uebung_020g.md)


```