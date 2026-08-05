![E_TP](E_TP.svg)
# E_TP
**Important note: This function block requires only one event and no cyclic calls. It does not have an output ET and does not display the elapsed time.**
## Image
![image](https://github.com/user-attachments/assets/8d531305-da9a-42e8-b44d-afab3a955be6)
## Text

## Description

The **E_TP** function block (also known as **Pulse Generator** or **Timer Pulse**) is a standardized function block (FB) according to the **IEC 61499** (DIN EN 61499) standard. This block is used to generate a pulsating output that is activated for a specific duration when an input signal is received. It is particularly useful in control applications where time-controlled actions are required.

### Description of the E_TP Block:

#### **General Function:**
- The **E_TP** block generates a pulsating output (**Q**) that is activated for a predefined time (**PT**) as soon as an input signal (**IN**) is received.
- When the input signal **IN** is set to **TRUE**, the output **Q** is set to **TRUE** for the duration **PT**. After the time **PT** has elapsed, **Q** is reset to **FALSE**, regardless of the state of **IN**.
- The block has a reset function (**R**) that resets the timer and immediately sets the output **Q** to **FALSE**, regardless of whether the time **PT** has expired or not.

#### **Interfaces:**

1. **Event Inputs:**

- **REQ (Service Request):** This event is triggered when the timer is to be started. It is linked to the input variables **IN** and **PT**.
- **R (Reset):** This event is triggered to reset the timer. It is linked to the input variable **IN**.

2. **Output Events:**

- **CNF (Confirmation of Requested Service):** This event is triggered when the timer expires and the output **Q** is reset. It is linked to the output variable **Q**.

3. **Input Variables:**

- **IN (BOOL):** The input that starts the timer. When **IN** is set to **TRUE**, the timer starts.
- **PT (TIME):** The specified duration for which the output **Q** is activated.

4. **Output Variables:**

- **Q (BOOL):** The output that is set to **TRUE** for the duration **PT** after **IN** has been activated.

#### **Behavior:**
- When **IN** is set to **TRUE**, the output **Q** is immediately set to **TRUE** and remains active for the duration **PT**.
- After the time **PT** has elapsed, **Q** is automatically reset to **FALSE**.
- When the reset event **R** is triggered, the timer is immediately reset, and **Q** is set to **FALSE**, regardless of whether the time **PT** has elapsed or not.

#### **Application Examples:**
- **Machine Control:** This function block can be used to activate a machine for a specific time, e.g., to switch on a motor for a set duration.
- **Flashing Light Control:** This function block can be used to activate a flashing light for a specific time.
- **Delayed Actions:** In scenarios where an action should be performed after a certain delay, this function block can be used to implement the delay.

#### **Versioning:**
- **Version 1.0:** Original version of the function block, created by Franz Hoepfinger on March 4, 2024.
- **Version 1.1:** A reset function was added to allow manual resetting of the timer. This version was released on April 23, 2024.

### Summary:

The **E_TP** function block is a useful tool in IEC 61499-based control technology for implementing time-controlled actions. Its simple interface and clear behavior make it easy to integrate into various control applications. The reset function in version 1.1 increases the flexibility of the function block, as the timer can now be reset manually.

### Summary:

The **E_TP** function block is a useful tool in IEC 61499-based control technology for implementing time-controlled actions.
## 🛠️ Related exercises

* [Uebung_020f](../../../../Uebungen/test_B/Uebungen_doc/Uebung_020f.md)
* [Uebung_039b](../../../../Uebungen/test_B/Uebungen_doc/Uebung_039b.md)
* [Uebung_177](../../../../Uebungen/test_B/Uebungen_doc/Uebung_177.md)
* [Uebung_178](../../../../Uebungen/test_B/Uebungen_doc/Uebung_178.md)

