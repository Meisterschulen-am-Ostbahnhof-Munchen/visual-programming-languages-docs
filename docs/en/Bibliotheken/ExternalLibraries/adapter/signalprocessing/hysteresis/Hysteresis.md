# Hysteresis

![Hysteresis](./Hysteresis.svg)

* * * * * * * * * *
## Introduction
The function block `Hysteresis` serves as an analog-to-digital converter with an integrated hysteresis curve. It converts an analog input signal (`INPUT`) into a binary output signal (`OUTPUT`). By defining a threshold (`THRESHOLD`) and a hysteresis width (`HYSTERESIS`), unwanted bounce or rapid oscillation of the output with noisy input signals is effectively prevented.

* * * * * * * * * *
## Interface Structure

### **Event Inputs**

* **INIT**: Initializes the function block. Updates the output qualifier `QO` based on `QI`.

* **REQ**: Triggers a calculation of the hysteresis state based on the current input values.

### **Event Outputs**

* **INITO**: Confirms completion of initialization or deinitialization.

* **CNF**: Confirms execution of the calculation and signals that an updated output value is available.

### **Data Inputs**

* **QI** (BOOL): Input event qualifier. Controls the validity of the input data and the activation of the function block.

* **INPUT** (REAL): The analog input signal to be monitored.

* **THRESHOLD** (REAL, default value: `0.0`): The midpoint of the hysteresis band (setpoint).

* **HYSTERESIS** (REAL, default value: `0.1`): The total width of the hysteresis band.

### **Data Outputs**
* **QO** (BOOL): Output event qualifier (indicates whether the function block is active and ready for operation).

* **OUTPUT** (BOOL): The digital output signal of the hysteresis element.

### **Adapters**
*This function block does not use adapters.*

* * * * * * * * * *
## Operation
The function block operates with a symmetrical hysteresis band around the defined midpoint (`THRESHOLD`). To ensure consistent behavior even with negative hysteresis values, the absolute value (`ABS`) of the hysteresis is used internally.


The switching thresholds are calculated as follows:

* **Switch-on point:** $THRESHOLD + \frac{|HYSTERESIS|}{2.0}$
* **Switch-off point:** $THRESHOLD - \frac{|HYSTERESIS|}{2.0}$

### Switching logic:

1. If the function block is in the **sOFF** state (output is `FALSE`), the output switches to `TRUE` (**sON**) as soon as the input signal reaches or exceeds the upper threshold:

$$\text{INPUT} \ge \text{THRESHOLD} + \frac{|\text{HYSTERESIS}|}{2.0}$$

2. If the function block is in the **sON** state (output is The output (`TRUE`) only switches back to `FALSE` (**sOFF**) when the input signal falls well below the lower limit:

$$\text{INPUT} < \text{THRESHOLD} - \frac{|\text{HYSTERESIS}|}{2.0}$$

* * * * * * * * * *
## Technische Besonderheiten
*   **Schwingungsschutz:** Die Ausschaltbedingung verwendet eine strikte Ungleichung ($<$), während die Einschaltbedingung inklusiv ist ($\ge$). Dies verhindert Oszillationen exakt an den Grenzen des Hysteresebands.
*   **Sicherheitsverriegelung über QI:** Der Ausgang `OUTPUT` kann nur dann den Zustand `TRUE` annehmen, wenn der Eingangs-Qualifier `QI` auf `TRUE` gesetzt ist. Ist `QI` im Zustand `FALSE`, bleibt der Ausgang gesperrt (`FALSE`).
*   **Robustheit:** Durch die Verwendung von `ABS(HYSTERESIS)` im Algorithmus führt die Eingabe einer negativen Hysterese nicht zu einem Fehlverhalten des Bausteins.

* * * * * * * * * *
## Zustandsübersicht
Der Funktionsbaustein ist als Basic-FB mit einer Execution Control Chart (ECC) realisiert:

1.  **START**: Der Standard-Ruhezustand nach dem Systemstart.
2.  **Init**: Wird durch das Ereignis `INIT` bei gesetztem `QI = TRUE` aufgerufen. Initialisiert den Baustein und setzt den Ausgang `OUTPUT` auf `FALSE`.
3.  **sOFF**: Der Zustand, in dem die Ausschaltbedingung erfüllt ist (`OUTPUT = FALSE`).
4.  **sON**: Der Zustand, in dem die Einschaltbedingung erfüllt ist (`OUTPUT = TRUE` sofern `QI = TRUE`).
5.  **DeInit**: Wird durch `INIT` bei `QI = FALSE` aufgerufen. Setzt `QO` und `OUTPUT` zurück auf `FALSE`.

* * * * * * * * * *
## Anwendungsszenarien
*   **Zweipunktregler:** Temperaturregelung (z. B. Heizung ein bei $< 19^\circ\text{C}$, aus bei $> 21^\circ\text{C}$ with a threshold of $20^\circ\text{C}$ and a hysteresis of $2^\circ\text{C}$).

* **Level Monitoring:** Activates a pump when a maximum level is reached and deactivates it when the minimum level is reached.

* **Noise Reduction:** Digitizes noisy analog sensor signals (e.g., pressure or brightness sensors) to eliminate fluctuating signal levels at the output.


* * * * * * * * * * *
## Comparison with Similar Components

Compared to a simple comparator (e.g., `GT` or `GE`), which switches immediately upon any minimal exceedance or fall below a specified value, the `Hysteresis` component offers inherent signal stabilization through its two switching thresholds. It combines the logic of two comparators and an RS flip-flop into a single, easily accessible component.

* * * * * * * * * *
## Conclusion
The `Hysteresis` component is an essential tool in signal processing and control engineering within the IEC 61499 standard. It provides a robust, easy-to-configure solution for generating stable binary control signals from continuous analog input values.