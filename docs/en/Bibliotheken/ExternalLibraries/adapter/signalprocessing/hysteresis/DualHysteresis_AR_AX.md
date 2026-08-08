# DualHysteresis_AR_AX

![DualHysteresis_AR_AX](./DualHysteresis_AR_AX.svg)

*(No image available)*

* * * * * * * * * *
## Introduction
The function block `DualHysteresis_AR_AX` performs dual analog-to-digital conversion with hysteresis. It compares an analog input signal with a defined midpoint (`MI`) to output control commands via two separate digital outputs (UP and DOWN). This corresponds to the operation of a classic three-position controller with deadband and hysteresis thresholds. The block is designed for signal processing in control and regulation applications and uses adapters for structured signal coupling.


 ## Interface Structure
### **Event Inputs**

* `INIT` (Type: `EInit`): Initialization request. Starts or stops the function block depending on the data input `QI`.

### **Event Outputs**

* `INITO` (Type: `EInit`): Initialization confirmation. Signals the successful transition to the initialized or deinitialized state.

### **Data Inputs**

* `QI` (Type: `BOOL`): Input event qualifier. Determines whether the function block should operate actively (`TRUE`) or be placed in the safe deinitialization state (`FALSE`).

### **Data Outputs**

* `QO` (Type: `BOOL`): Output event qualifier. Reflects the current status and operational readiness of the function block.

### **Adapters**

* **Plugs:**

* `DO_UP` (Type: `adapter::types::unidirectional::AX`): Output adapter for the upward movement/upper threshold (UP).

* `DO_DOWN` (Type: `adapter::types::unidirectional::AX`): Output adapter for downward movement/lower threshold (DOWN).

* **Sockets:**

* `INPUT` (Type: `adapter::types::unidirectional::AR`): The current analog measurement or input value.

* `MI` (Type: `adapter::types::unidirectional::AR`): The center point or setpoint of the control (e.g., `0.5` for 50%).

* `DEAD` (Type: `adapter::types::unidirectional::AR`): The deadband around the center point (absolute value). Defines the cutoff points.

* `DEAD` (Type: `adapter::types::unidirectional::AR`): The deadband around the center point (absolute value). Defines the cutoff points.

* `DEAD` (Type: `adapter::types::unidirectional::AR`): The deadband around the center point (absolute value). Defines the cutoff points. * `HYSTERESIS` (Type: `adapter::types::unidirectional::AR`): The hysteresis (absolute value). Together with the deadband, it defines the switch-on points.

---

## Functionality
The state switching is event-driven via the input `INPUT.E1`. The mathematical evaluation ensures that negative parameter inputs for the deadband (`DEAD`) and the hysteresis (`HYSTERESIS`) are handled by using absolute values (`ABS`).

The logical thresholds behave as follows:

* **Switch to UP (switch to UP):**

$$INPUT \ge MI + |DEAD| + |HYSTERESIS|$$

*(Outputs: `DO_UP.D1` = `TRUE`, `DO_DOWN.D1` = `FALSE`)*

* **Switch UP (Return to Neutral):**

$$INPUT < MI + |DEAD|$$
    *(Ausgänge: `DO_UP.D1` = `FALSE`, `DO_DOWN.D1` = `FALSE`)*

*   **Einschalten DOWN (Wechsel nach DOWN):**
    $$INPUT \le MI - |DEAD| - |HYSTERESIS|$$
    *(Ausgänge: `DO_UP.D1` = `FALSE`, `DO_DOWN.D1` = `TRUE`)*

*   **Ausschalten DOWN (Wechsel zurück nach Neutral):**
    $$INPUT > MI - |DEAD|$$

*(Outputs: `DO_UP.D1` = `FALSE`, `DO_DOWN.D1` = `FALSE`)*

---

## Technical Features
* **Error Safety through Absolute Values:** The threshold calculations explicitly use the `ABS` function for the Parameters `DEAD` and `HYSTERESIS` prevent malfunctions caused by accidentally set negative values.

**Safe State:** In the deinitialized state (`QI` = `FALSE`) or in the state `Neutral`, both digital outputs (`DO_UP.D1` and `DO_DOWN.D1`) are forcibly set to `FALSE`.


**Safe State:** In the deinitialized state (`QI` = `FALSE`) or in the state `Neutral`, both digital outputs (`DO_UP.D1` and `DO_DOWN.D1`) are forcibly set to `FALSE`. * **Adapter Connection:** The use of `AR` (Analog Receiver) and `AX` (Digital Actuator) adapters ensures standardized, clean encapsulation of the signal paths within the 4diac IDE.

---

## State Overview
The module is based on a state machine (ECC) with the following states:

1. `START`: Idle state before initialization.

2. `Init`: Initialization phase. Sets the outputs to a safe state.

3. `Neutral`: The input value is within the permissible range. Both outputs are inactive.

4. `UP`: The upper turn-on point has been exceeded. Output `DO_UP` is active.

5. `DOWN`: The lower activation point has been reached. Output `DO_DOWN` is active.

6. `DeInit`: Transition state for deactivating the function block.

---

## Application Scenarios

* **Three-point controller:** Temperature control (e.g., heating / neutral / cooling) or level control (e.g., open inlet valve / neutral / open outlet valve).

* **Track Guidance and Steering Systems:** Automatic steering systems in agricultural or logistics where deviations from the track center (`MI`) to the left (`DOWN`) or right (`UP`) need to be corrected.

* **Setpoint Band Monitoring:** Monitoring of physical quantities where an actuator should only be activated when there are significant deviations (deadband + hysteresis) to prevent constant actuator "flutter."

---

## Comparison with Similar Components
Classic hysteresis components (e.g., two-point controllers) only control a single digital output. The `DualHysteresis_AR_AX` combines two opposing hysteresis loops in a single component (three-point behavior). Furthermore, compared to standard function blocks with elementary data types, it is distinguished by the use of unidirectional adapters (`AR` and `AX`), which simplifies wiring in complex applications.

---

## Conclusion
The `DualHysteresis_AR_AX` is a robust and flexible function block for implementing three-point control. Thanks to the mathematical validation of the limit values and the clearly defined state behavior, it is ideally suited for demanding control tasks where actuators must be controlled gently and without chatter.