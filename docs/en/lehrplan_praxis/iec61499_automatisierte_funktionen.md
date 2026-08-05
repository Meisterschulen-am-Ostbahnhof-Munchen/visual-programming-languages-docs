# ⚡ Automated Functions with IEC 61499
> 📌 **Source & Legal Basis:**
> **Source:** *Framework Curriculum for Preparation for the Master Craftsman Examination in Agricultural and Construction Machinery Mechatronics*
> **Publisher:** German Association of Agricultural and Construction Machinery Mechatronics Engineers (LandBauTechnik-Bundesverband e. V.), Alfredstraße 102, 45131 Essen (as of February 25, 2025)
> **Regulation:** *Master Craftsman Examination Regulation (LandBauMechMstrV)* of September 9, 2024 (Federal Law Gazette 2024 I No. 277, effective August 1, 2025)
---
**Framework Curriculum Category:** Part I LE 1.4 (40 teaching units) | Part II LE 1.1 (160 hours)

**Core Area:** Graphical Function Development for Networked Mechatronic Systems.

--

## 1. Event-Driven Architecture (Events & Data)

### Difference to Classic PLC Languages (IEC 61131-3)
- **Classic (Cyclic):** The program is continuously executed in a fixed loop.
- **IEC 61499 (Event-Driven):** The execution of a function block (FB) is triggered exclusively by explicit **events**. This drastically reduces the bus and processor load and enables true distributability.

### Structure of an IEC 61499 Function Block
- **Event Inputs (`INIT`, `REQ`):** Start the internal processing.
- **Event Outputs (`INITO`, `CNF`):** Signal the completion of processing to downstream modules.
- **Data Inputs & Outputs (`WITH` linking):** Link events to data values (e.g., sensor values, setpoints).

---

## 2. Practical Implementation in the Master Craftsman's Examination Project

### Application Example: Automatic Valve Positioning & Lift Control

1. **Sensor Module:** Detects the current pressure ($p$) and position ($s$).

2. **Controller Module (PID / Hysteresis):** Graphically connected in the 4diac IDE.

3. **Actuator Module (PWM / CAN Output):** Controls the proportional valve.

4. **Visualization (ISOBUS VT / ISO Designer):** Events and values are passed directly to the VT objects.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
* [🌐 The PWM Signal & Infographic on ms-muc-docs.de](https://www.ms-muc-docs.de/automatisierung/das-pwm-signal-die-kunst-spannung-zu-zerhacken/das-pwm-signal-die-kunst-spannung-zu-zerhacken-website/)

