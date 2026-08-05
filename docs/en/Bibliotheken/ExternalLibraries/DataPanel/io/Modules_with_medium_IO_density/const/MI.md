# MI
## 🎧 Podcast
![MI](./MI.svg)

* [Eclipse 4diac 3.0: ST Interpreter, FBE, and 7200 Commits – The Turbo for Distributed Automation ](https://podcasters.spotify.com/pod/show/eclipse-4diac-de/episodes/Eclipse-4diac-3-0-ST-Interpreter--FBE-und-7200-Commits--Der-Turbo-fr-verteilte-Automatisierung-e3a5cpl)
* [Industry 4.0: The Magic of Self-Configuring Systems with fortiss, IEC 61499, and Eclipse 4diac ](https://podcasters.spotify.com/pod/show/eclipse-4diac-de/episodes/Industrie-4-0-Die-Magie-selbstkonfigurierender-Systeme-mit-fortiss--IEC-61499-und-Eclipse-4diac-e368lv5)
* [From Pyramid to Plug-and-Play: The Rise of Self-Configurable Industrial Automation ](https://podcasters.spotify.com/pod/show/eclipse-4diac-en/episodes/From-Pyramid-to-Plug-and-Play-The-Rise-of-Self-Configurable-Industrial-Automation-e368lvk)
* [The E_CTU in IEC 61499: Event-Driven Counting and Why the Minimalist is Convincing in Mechanical Engineering ](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Der-E_CTU-in-der-IEC-61499-Ereignisgesteuertes-Zhlen-und-warum-der-Minimalist-im-Maschinenbau-berzeugt-e3a9qnq)
* [The E_PERMIT Block: The "Gatekeeper" for Events in IEC 61499 Systems Decoded (](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Der-E_PERMIT-Baustein-Der-Trsteher-fr-Ereignisse-in-IEC-61499-Systemen-entschlsselt-e3681m5))

## 📺 Video
* [The Great Migration (](https://www.youtube.com/watch?v=XcBu7y6ch4E))

## Introduction
The MI Global Constants represent a collection of constants for medium I/O density modules. These constant definitions are used in the 4diac IDE to provide consistent and reusable addressing information for I/O modules.

```
## Interface Structure
### **Event Inputs**
*No event inputs available*

### **Event Outputs**
*No event outputs available*

### **Data Inputs**
*No data inputs available*

### **Data Outputs**
*No data outputs available*

### **Adapters**
*No adapters available*

## Functionality
MI Global Constants are purely constant declarations without any active functionality. The constants define address ranges for 16 different I/O modules (MI_00 to MI_15), each with a unique numeric value in the range of 224 to 239.

## Technical Features
- All constants are of type USINT (Unsigned Short Integer)
- The values form a continuous range from 224 to 239
- Constants are declared as global and constant
- Package assignment: DataPanel::io::MI::const

## State Overview
*No state transitions are present, as these are static constant definitions*

## Application Scenarios
- Addressing I/O modules in control applications
- Reuse in various function blocks
- Centralized management of module addresses
- Simplified project configuration

## ⚖️ Comparison with Similar Blocks
Compared to other constant definitions, MI provides specific addresses for modules with medium I/O density. Other constant sets might cover different address ranges or module types.

## Conclusion
The MI Global Constants offer a convenient and centralized way to manage address information for I/O modules. Using these constants improves the maintainability and readability of control programs, as module address changes can be made centrally.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 E_CTU Event Counter Block on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/event-function-blocks/e_ctu/)
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

