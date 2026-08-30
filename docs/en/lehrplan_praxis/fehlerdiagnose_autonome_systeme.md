# 🔍 Fault Diagnosis in Automated & Autonomous Systems

> 📌 **Source & Legal Basis:**
> **Source:** *Framework Curriculum for the Preparation for the Master Craftsman Examination in Agricultural and Construction Machinery Mechatronics*
> **Publisher:** German Association of Agricultural and Construction Machinery Mechatronics Technicians (LandBauTechnik-Bundesverband e. V.), Alfredstraße 102, 45131 Essen (as of February 25, 2025)
> **Regulation:** *Master Craftsman Examination Regulation (LandBauMechMstrV)* of September 9, 2024 (Federal Law Gazette 2024 I No. 277, effective August 1, 2025)
---
**Framework Curriculum Category:** Part I LE 2.6 (20 teaching units) | Part II LE 1.3 (100 hours)

**Core Area:** Systematic troubleshooting in visual control architectures.

--

## 1. Online Debugging & Signal Monitoring (Watchpoints)

### Diagnostic Strategy in the 4diac IDE

- **Monitoring Mode:** Connecting the development environment to the running runtime (FORTE / ESP32).
- **Visualization of Signal Flow:** Color-coded highlighting of active event paths and real-time display of all data variables.
- **Setting Watchpoints:** Monitoring of critical states (e.g., emergency stop triggering, LiDAR obstacle detection).

--

## 2. State Machines (Execution Control Chart - ECC) Analysis

### Troubleshooting in ECCs

- **State Checks:** Is the state machine stuck in an incomplete transition?
- **Condition Checking:** Verification of logical conditions (e.g., `Sensor_OK AND Safety_Interlock`).
- **Error Logging:** Evaluation of diagnostic events and sending of error PGNs via the CAN bus.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
- [🌐 ESP32 & ESP32-S3 DevKit on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/mikroelektronik/esp32/esp32-s3-devkit/)
