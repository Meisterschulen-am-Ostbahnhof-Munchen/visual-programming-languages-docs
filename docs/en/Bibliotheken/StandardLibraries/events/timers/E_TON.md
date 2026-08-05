![E_TON](E_TON.svg)

# E_TON

## 🎧 Podcast

* [E_TON in Industrial Automation: How a Simple Timer Creates Safety and Stability ](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/E_TON-in-der-Industrieautomation-Wie-ein-simpler-Timer-Sicherheit-und-Stabilitt-schafft-e3672u9)

## Image

![image](https://github.com/user-attachments/assets/cc035168-0f10-4159-bbe5-941ec9919630)

## Text

The **E_TON** function block is a standardized function block type (FBType) according to the **IEC 61499** standard, used for **On-Delay Timers** in industrial automation systems. This function block allows a signal to be switched on with a time delay, which is required in many control applications, for example, to safely control machines or processes.


### General Description:

- **Name**: E_TON

- **Type**: Standard Timer Function Block (On-Delay Timing)

- **Purpose**: This function block is used to implement a time-delayed turn-on function. It is particularly useful in applications where a delay is required when a signal is switched on.

- **License**: This function block is licensed under the Eclipse Public License 2.0 (EPL-2.0).

---

### Interface Description:

#### **Event Inputs:**

1. **REQ** (Normal Execution Request):

- **Type**: Event

- **Description**: This event triggers the normal execution of the function block. It is used to start or update the timer.

- **Associated Variables**:

- **IN**: The input value that starts the timer.

- **PT**: The specified duration for the on-delay.


#### **Event Outputs:**

1. **CNF** (Execution Confirmation):

- **Type**: Event

- **Description**: This event confirms the execution of the function block. It is triggered when the timer expires or a state change occurs.

- **Associated Variable**:

- **Q**: The output value indicating the timer's state.

#### **Input Variables:**

1. **IN**:

- **Type**: BOOL

- **Description**: The input value that starts the timer. When **IN** is set to `TRUE`, the turn-on delay (**PT**) starts. The output **Q** is only set to `TRUE` after the **PT** time has elapsed.


2. **PT**:

- **Type**: TIME

- **Description**: The preset duration for the on-delay. This time is measured from the moment **IN** is set to `TRUE`.

#### **Output Variables:**

1. **Q**:

- **Type**: BOOL

- **Description**: The output value that indicates the timer's state. **Q** is set to `TRUE` after the on-delay (**PT**) has elapsed.

--

### Functionality:

1. **On-Delay**:

- When **IN** is set to `TRUE`, the on-delay timer (**PT**) starts.

- After **PT** expires, **Q** is set to `TRUE`.

- If **IN** is set to `FALSE` during the timer, the timer stops, and **Q** remains at `FALSE`.

2. **Confirmation of Execution (CNF)**:

- The **CNF** event is triggered when the timer expires and **Q** is set to `TRUE`.

--

### Application Examples:

- **Machine Control**: Delayed response to sensors or switching commands, e.g., to prevent motor overload.

- **Process Automation**: Time-controlled switching operations in industrial processes, e.g., in conveyor belts or heating controls.


---

### Summary:

The **E_TON** function block is a simple yet powerful tool in IEC 61499 for implementing time-delayed turn-on operations in industrial automation systems. It provides a reliable way to turn on signals with a defined delay, which is essential in many control applications. The function block is easy to configure and can be used in a variety of scenarios where a time delay is required.

## 🛠️ Related Exercises

* [Exercise_020c](../../../../Uebungen/test_B/Uebungen_doc/Uebung_020c.md)]
* [Exercise_020c2](../../../../Uebungen/test_B/Uebungen_doc/Uebung_020c2.md)]
* [Exercise_039b](../../../../Uebungen/test_B/Uebungen_doc/Uebung_039b.md)]
* [Exercise_160b2](../../../../Uebungen/test_B/Uebungen_doc/Uebung_160b2.md)]


