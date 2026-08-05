# Overview of Visual Programming Languages
Visual programming languages (VPLs) allow programs to be created by graphically manipulating elements instead of writing text. In the world of technology and computer science, there are many different approaches, which vary depending on the target group and use case.
## 1. Educational and General Languages
These languages often serve as an introduction to the logic of programming. They abstract complex syntax rules into colored blocks that are assembled like puzzle pieces.

* **Scratch:** Probably the best-known language for children and teenagers. It playfully teaches concepts such as loops, conditions, and variables.
* **Blockly (Google):** A library that translates visual blocks into textual code (e.g., Python or JavaScript).
* **M5Stack / UIFlow:** An industrial application of Blockly. Here, microcontrollers (ESP32) are programmed visually, which greatly accelerates prototyping.
* ---

## 2. Visual Modeling in Computer Science
Before writing code, computer scientists often use graphical models to plan architectures.

* **UML (Unified Modeling Language):** A standard for visualizing software systems. Class diagrams and state diagrams are the most well-known tools.

--

## 3. Engineering Languages (Data Flow)
In measurement and control engineering, visual languages play a dominant role because they intuitively represent the flow of signals and data.

* **LabVIEW (National Instruments):** A powerful environment in which "Virtual Instruments" (VIs) are created by wiring up functional blocks. It is used worldwide in laboratories and test benches.

--

## 4. Automation Technology (Industrial Standard)
Visual programming has been standard practice in industry for decades, as it originates directly from the traditions of electrical engineering (circuit diagrams) and process engineering (flowcharts).

### The Languages of IEC 61131-3

This standard defines three essential visual languages for programmable logic controllers (PLCs):

| Abbreviation | Name (DE/EN) | Characteristics | Application |

| :--- | :--- | :--- | :--- |

| **LAD** | Ladder Diagram | Looks like a circuit diagram. | Simple logic, interlocks. |

| **FBD** | Function Block Diagram | Logic gates and function blocks are connected. | Complex control systems, mathematical calculations. |

| **SFC** | Sequential Function Chart | Modeling of steps and transitions. | Machine sequences, batch processes (similar to GRAFCET). |

### The Evolution: IEC 61499
IEC 61499 builds on the concepts of IEC 61131-3, but introduces crucial innovations:

1. **Function Blocks (FB):** Programming is similar to the Function Block Diagram (FBD), but is strictly event-driven. A block is only activated when an event occurs.

2. **Execution Control Chart (ECC):** Within a block, a state machine controls which algorithm is executed for each event. This allows for much more precise control over system behavior than in classic PLC cycles.

---

## Why Visual Programming in Industry?

The automation pyramid shows that real-time capability and clear diagnostics are crucial at the lower levels (field and control levels). Visual programs can often be "read" and debugged faster in case of errors than thousands of lines of text code. They bridge the gap between the electrician's circuit diagram and the programmer's logic.

### Further Resources
* [Video: IEC 61131 vs. IEC 61499 (IEEE Webinar)]
* [Wikipedia: Visual Programming Language]
* [M5Stack UIFlow Documentation]

---

### 🌐 Related Topic Subpages on ms-muc-docs.de
* [🌐 ESP32 & ESP32-S3 DevKit on ms-muc-docs.de]
* [🌐 MCU vs. MPU Comparison Guide on ms-muc-docs.de]

*
