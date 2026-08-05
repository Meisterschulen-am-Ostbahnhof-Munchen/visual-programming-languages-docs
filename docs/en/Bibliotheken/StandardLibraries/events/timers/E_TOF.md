![E_TOF](E_TOF.svg)

# E_TOF

## 🎧 Podcast

* [E_TOF vs. FB_TOF: The event timer that doesn't tick cyclically – a revolution for automation systems? ](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/E_TOF-vs--FB_TOF-Der-Event-Timer--der-nicht-zyklisch-tickt--Revolution-fr-Automatisierungssysteme-e3673qk)

* [FB_TOF and E_TOF: Delay timers in IEC 61131-3 and 61499 ](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/FB_TOF-und-E_TOF-Verzgerungstimer-in-IEC-61131-3-und-61499-e368e2d)

## Description:

### The E_TOF function block in IEC 61499: An overview

#### Introduction

IEC 61499 is an international standard that enables the modeling of distributed industrial control systems. A central concept in this standard is the function block (FB), which serves as a fundamental component for the control logic. The **E_TOF** (Event-driven Off-Delay Timer) function block is an example of such a function block used in IEC 61499 to model a delayed shutdown function. This paper describes the structure, behavior, and application of the E_TOF function block using the provided source code. A particularly noteworthy aspect is that this function block **also functions when called non-cyclically** because it is internally based on the **E_DELAY** function block from IEC 61499.

#### Structure of the E_TOF Function Block

The E_TOF function block is a **Composite Function Block (CFB)** specified according to IEC 61499. A CFB consists of an interface and an internal network of function blocks that work together to implement the desired behavior.

##### Interface

The interface of the E_TOF block consists of:

- **Event Inputs**:

- **REQ (Request)**: This event triggers the execution of the block. It is linked to the input variables **IN** and **PT**.

- **R (Reset)**: This event resets the timer.

- **Output Event**:

- **CNF (Confirmation)**: This event is triggered when the execution of the block is complete. It is linked to the output variable **Q**.

- **Input Variables**:

- **IN (Input)**: This is a Boolean variable that controls the state of the timer. If **IN** is set to **TRUE**, the timer starts. If **IN** is set to **FALSE**, the delay time begins.

- **PT (Process Time)**: This is a time variable (TIME) that defines the delay time after which the output **Q** is set to **FALSE**.

- **Output Variable**:

- **Q (Output)**: This is a Boolean variable that indicates the timer's state. It remains **TRUE** until the delay time **PT** has elapsed.

##### Internal Network (FBNetwork)

The E_TOF block uses three function blocks internally to implement the desired behavior:

1. **E_SWITCH**: This block controls the flow of events based on the input **IN**. If **IN** is set to **TRUE**, the event is forwarded to **E_RS.S**. If **IN** is set to **FALSE**, the event is forwarded to **E_DELAY.START**.

2. **E_DELAY**: This block implements the delay time **PT**. When the **START** event occurs, the timer starts running. When the delay time has elapsed, the **EO** event is triggered.

3. **E_RS**: This block is a bistable element that stores the timer's state. When the **S** event occurs, the output **Q** is set to **TRUE**. When the **R** event occurs, the output **Q** is set to **FALSE**.

#### Behavior of the E_TOF Block

The E_TOF block behaves like an off-delay timer, implementing a delayed shutdown function. The block's behavior can be described as follows:

1. **Timer Start**: When the **REQ** event occurs and the input variable **IN** is set to **TRUE**, the timer starts. The output **Q** is set to **TRUE**.

2. **Delay Time**: When the input variable **IN** is set to **FALSE**, the delay time **PT** begins. The output **Q** remains **TRUE** until the delay time has elapsed.

3. **Delay Time Expiration**: Once the delay time **PT** has elapsed, the output **Q** is set to **FALSE**, and the **CNF** event is triggered to signal the end of the delay.

4. **Reset**: When the **R** event occurs, the timer is reset, and the output **Q** is set to **FALSE**.

#### Independence from Cyclic Calling

A key advantage of the E_TOF block is that it **does not need to be called cyclically** to function correctly. This is because the block is internally based on the **E_DELAY** block specified in IEC 61499. The **E_DELAY** block is an event-driven timer that operates independently of the cyclic call of the parent block. This means that the E_TOF block can also be used in systems that do not operate cyclically, such as event-driven or distributed control systems.

#### Application Examples

The E_TOF block can be used in various industrial control applications, especially in scenarios where a delayed shutdown function is required. Some examples are:

- **Machine Control**: The block can be used to ensure that a machine continues to run for a specific period of time after being switched off, for example, to complete processes or to implement safety precautions.

- **Lighting Control**: The block can be used in lighting systems to keep the light on for a specific period of time after the switch has been turned off.

- **Valve Control**: This function block can be used to keep a valve open for a specific period of time after it has closed, for example, to release pressure.

##

## 🛠️ Related Exercises

* [Exercise_020e](../../../../Uebungen/test_B/Uebungen_doc/Uebung_020e.md)

## Conclusion

The E_TOF function block is a versatile function block in IEC 61499 that implements a delayed shutdown function. Due to its internal use of the **E_DELAY** function block, it can function correctly **even if it is not called cyclically**. This makes it particularly suitable for event-driven and distributed control systems where cyclic calls are not always guaranteed.

The provided source code demonstrates how the E_TOF function block can be implemented in practice and provides a solid foundation for developing similar function blocks in industrial control systems. The independence from cyclical calls is a crucial advantage that makes the component suitable for a wide variety of applications.


The fact that it doesn't require cyclical calls is a key advantage.## ⚖️ Comparison of E_TOF and FB_TOF

### Chapter 1: The FB_TOF Block

The **FB_TOF** (Off-Delay Timer) is a standardized function block according to IEC 61131-3 that implements a delayed shutdown function. A key feature of this block is the **ET** (Elapsed Time) output, which displays the elapsed time since the start of the delay. This output is particularly useful for monitoring the progress of the delay time and for use in control logic.

However, a critical aspect of the FB_TOF block is that it **must be called cyclically** to function correctly. This means that the block must be executed in every cycle of the PLC program to correctly calculate the elapsed time **ET** and maintain the delay time **PT**. If the function block is not called regularly, the timer cannot function correctly, and the delay time may not be adhered to. This dependence on cyclic calling makes the FB_TOF function block ideal for traditional PLC systems that operate in fixed cycles.

### Chapter 2: The E_TOF Function Block

The **E_TOF** (Event-driven Off-Delay Timer) is a function block according to IEC 61499 that also implements a delayed shutdown function. Unlike the FB_TOF, the E_TOF **does not have an ET** output that displays the elapsed time. Instead, the E_TOF is internally based on the **E_DELAY** function block specified in IEC 61499, which provides an event-driven delay function.

A key advantage of the E_TOF function block is that it **does not need to be called cyclically** to function correctly. Since the internal **E_DELAY** block operates independently of the cyclic call of the parent block, the E_TOF block can also be used in systems that do not operate cyclically, such as event-driven or distributed control systems. This makes the E_TOF block particularly flexible and suitable for modern, distributed control architectures where cyclic calls are not always guaranteed.

In summary, the FB_TOF block, with its **ET** output, enables detailed monitoring of elapsed time but requires a cyclic call. The E_TOF block, on the other hand, does without the **ET** output but offers the flexibility to operate independently of cyclic calls, making it ideal for event-driven systems.