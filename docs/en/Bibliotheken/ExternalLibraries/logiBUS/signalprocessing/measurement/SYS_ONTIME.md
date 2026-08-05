# SYS_ONTIME
<img width="1639" height="206" alt="image" src="https://github.com/user-attachments/assets/08d09491-2560-44d8-be18-94d431bac08b" />
* * * * * * * * * *
## Introduction
The function block `SYS_ONTIME` is a Service Interface Function Block (SIFB). Its main task is to read and provide the uptime (ontime) of the resource in which it is executed. It serves as a standardized interface between the application logic and the system-level services of the runtime environment.
![SYS_ONTIME](SYS_ONTIME.svg)
## Interface Structure

### **Event Inputs**
* **`INIT`**: This event initializes the function block. It must be triggered before the block can begin its service.

### **Event Outputs**
* **`INITO`**: This event confirms the successful initialization of the function block. It is triggered along with the first valid `ONTIME` value.
* **`IND`**: This event signals that a new, updated `ONTIME` value has been provided by the system resource manager.

### **Data Inputs**
* This function block has no data inputs.

### **Data Outputs**
* **`ONTIME` (UINT)**: This output provides the cumulative uptime of the resource. The unit is "decimal minutes," which is equal to 0.01 hours (e.g., a value of 150 equals 1.5 hours).

### **Adapters**
* This function block does not use adapters.

## Functionality
The `SYS_ONTIME` block acts as a client for an internal system service. After receiving the `INIT` event, it registers with the resource manager to gain access to the uptime data. Once initialization is complete, the `INITO` event is triggered along with the current uptime value.

The block then continuously monitors the system resource. As soon as the uptime changes (typically due to a system tick or similar mechanism), the resource manager triggers an indication. The `SYS_ONTIME` block receives this, updates its internal `ONTIME` value, and forwards the `IND` event, along with the new value, to the connected application logic.

The block then continuously monitors the system resource. As soon as the uptime changes (typically due to a system tick or similar mechanism), the resource manager triggers an indication.
## Technical Features
* **Service Interface FB**: As a SIFB, its implementation is specific to the respective 4diac runtime (FORTE) and the underlying hardware/platform. The exact method of time measurement (e.g., based on processor startup time or the runtime environment) is runtime-defined.
* **Unit**: The operating time is provided in the unusual but practical unit for control tasks: the decimal minute (1/100 of an hour). This facilitates calculations in the decimal system, e.g., for maintenance intervals or energy consumption estimates.
* **Read-Only Access**: The block provides read-only access to an internal system value. Resetting the operating time is not possible via this interface.

## Status Overview

1. **Inactive**: The block has been created but not yet initialized. No communication with the system resource is taking place.

2. **Initialized**: After receiving `INIT`, the block is registered with the resource manager and awaits data. The state changes immediately after successful initialization, followed by the output of `INITO`.

3. **Ready**: The block has received the first `ONTIME` value and is ready for operation. It now awaits indication events (`IND`) from the system to output updated values.

## Application Scenarios
* **Predictive Maintenance**: Monitoring the operating time of machines or plant components to trigger maintenance intervals based on actual usage.
* **Energy Management**: Recording the operating hours of consumers (e.g., motors, heaters) to calculate energy consumption or for load profiles.
* **Production Data Acquisition (PDA)**: Logging of production or machine runtimes for Overall Equipment Effectiveness (OEE) analysis.
* **Lifetime Monitoring**: Checking whether critical components have reached or exceeded their specified lifespan (in operating hours).

## ⚖️ Comparison with similar modules
* **`E_CYCLE` / `E_DELAY`**: These modules themselves generate periodic events or delays. `SYS_ONTIME`, on the other hand, *reads* a passively existing, cumulative time value from the system.
* **`E_SR` (Set-Reset) with counter**: A manually configured counter for power-on processes could provide similar data, but would be implemented application-side and not persistent system-wide. `SYS_ONTIME` provides a reliable, system-maintained value that is usually persistent even after a restart.
* **Other SYS_* blocks** (such as `SYS_TIME`): While `SYS_TIME` provides the current time and date, `SYS_ONTIME` specifically provides the pure uptime of a resource.

## 🛠️ Related Exercises
* [Exercise_140](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_140.md)

## Conclusion
The `SYS_ONTIME` function block is an essential tool for all applications that rely on recording and analyzing uptime. As a standardized service interface, it abstracts away the platform-specific implementation and provides application logic with simple, reliable access to this important system metric. Its use is particularly recommended in the areas of maintenance, energy efficiency, and operational data acquisition.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
