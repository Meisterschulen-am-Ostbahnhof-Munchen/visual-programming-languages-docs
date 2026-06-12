# E_RS_SYM_INIT


![E_RS_SYM_INIT](./E_RS_SYM_INIT.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **E_RS_SYM_INIT** ist ein ereignisgesteuerter, bistabiler Kippschalter (Flipflop) mit symmetrischem Startverhalten und expliziter Initialisierung. Er realisiert die bekannte RS-Flipflop-Logik, wobei der Ausgang **Q** bei einer Initialisierung (Ereignis **INIT**) wahlweise auf TRUE oder FALSE gesetzt werden kann – je nach Wert des Parameters **Q_INIT**. Dies ermöglicht ein definiertes Verhalten nach einem Systemstart oder einer Reinitialisierung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ | Kommentar |
|----------|-----|-----------|
| **INIT** | EInit | Initialisierungsanforderung; übernimmt die Werte von **QI** und **Q_INIT** |
| **R**    | Event | Setzt den Ausgang **Q** zurück (Reset) |
| **S**    | Event | Setzt den Ausgang **Q** (Set) |

### **Ereignis-Ausgänge**

| Ereignis | Typ | Kommentar |
|----------|-----|-----------|
| **INITO**| EInit | Bestätigung der Initialisierung; übergibt den Wert von **QO** |
| **EO**   | Event | Zeigt an, dass sich der Ausgang **Q** geändert hat |

### **Daten-Eingänge**

| Variable | Typ   | Kommentar |
|----------|-------|-----------|
| **QI**   | BOOL | Ereignisqualifizierer: Nur wenn *QI=TRUE* werden Set-/Reset-Operationen ausgeführt. Bei Initialisierung legt *QI* den Wert von **QO** fest. |
| **Q_INIT** | BOOL | Legt den Anfangswert von **Q** fest, der während der Initialisierung übernommen wird. |

### **Daten-Ausgänge**

| Variable | Typ   | Kommentar |
|----------|-------|-----------|
| **QO**   | BOOL | Ausgangsqualifizierer: Gibt an, ob eine Operation gültig war (Übernahme von **QI**). |
| **Q**    | BOOL | Der eigentliche Flipflop-Ausgang. |

### **Adapter**

Keine Adapter vorhanden.

## Funktionsweise

Der **E_RS_SYM_INIT** arbeitet als Zustandsautomat mit fünf Zuständen: **START**, **Init**, **DeInit**, **SET** und **RESET**.

*   **Startverhalten**: Nach einem initialen Ereignis **INIT** mit **QI=TRUE** wird der Block in den Zustand **Init** überführt. Abhängig vom Wert **Q_INIT** wechselt er entweder nach **SET** (**Q** = TRUE) oder nach **RESET** (**Q** = FALSE). Der Ausgangsqualifizierer **QO** übernimmt dabei den Wert von **QI** (also TRUE) und wird über **INITO** ausgegeben.
*   **Setzen und Rücksetzen**:
    *   Im Zustand **SET** führt ein **R**-Ereignis in den Zustand **RESET**; die Aktion setzt **Q** auf FALSE (wenn **QI=TRUE**).
    *   Im Zustand **RESET** führt ein **S**-Ereignis in den Zustand **SET**; die Aktion setzt **Q** auf TRUE (wenn **QI=TRUE**).
    *   Bei jeder Zustandsänderung wird **QO** auf den aktuellen Wert von **QI** gesetzt und das Ereignis **EO** ausgegeben.
*   **Deinitialisierung**: Sobald ein **INIT**-Ereignis eintritt, während **QI=FALSE** ist (z. B. Deinitialisierung), wechselt der Block aus **SET** oder **RESET** in den Zustand **DeInit**. Dort wird **QO** auf FALSE gesetzt, und der Block kehrt über **INITO** in den **START**-Zustand zurück. Das Flipflop wird dabei nicht zurückgesetzt – **Q** behält seinen bisherigen Wert.
*   **Qualifizierer QI**: Die tatsächliche Änderung von **Q** erfolgt nur, wenn **QI=TRUE** ist. Ist **QI=FALSE**, werden die Setz- und Rücksetzsignale ignoriert, aber **QO** gibt dennoch den Wert von **QI** weiter. Dies ermöglicht ein bedingtes Verhalten, z. B. für gültige/ungültige Freigaben.

## Technische Besonderheiten

*   **Symmetrisches Startverhalten**: Der initiale Zustand von **Q** wird explizit über den Parameter **Q_INIT** festgelegt. Dies unterscheidet den Baustein von einem normalen RS-Flipflop, dessen Startzustand undefiniert ist.
*   **INIT als Ereignis mit Parametern**: Der INIT-Ereigniseingang trägt gleichzeitig die Werte **QI** und **Q_INIT**, sodass Initialisierung und Deinitialisierung klar getrennt sind.
*   **QC (Event-Qualifier) wird durchgeschliffen**: Bei jeder gültigen Operation (Set, Reset oder INIT) wird **QO** auf den Wert von **QI** gesetzt, sodass die aufrufende Applikation die Gültigkeit der Operation erkennen kann.
*   **Zustandsmaschine mit fünf Zuständen**: Die Trennung von Start-, Initialisierungs- und Deinitialisierungszuständen ermöglicht ein robustes Verhalten, insbesondere in Automatisierungssystemen mit zyklischen Neustarts.

## Zustandsübersicht

| Zustand   | Beschreibung                                                                 | Aktion beim Eintritt | Ausgangsereignis |
|-----------|-----------------------------------------------------------------------------|----------------------|------------------|
| **START** | Initialer Ruhezustand nach Systemstart oder nach Deinitialisierung          | keine                | –                |
| **Init**  | Initialisierung wurde angefordert (**INIT** mit **QI=TRUE**)                 | setzt **QO** = **QI** | INITO           |
| **DeInit**| Deinitialisierung wurde angefordert (**INIT** mit **QI=FALSE**)              | setzt **QO** = FALSE | INITO           |
| **SET**   | Flipflop ist gesetzt (**Q = TRUE**)                                          | Setzen von **Q** auf TRUE (nur wenn **QI=TRUE**) | EO  |
| **RESET** | Flipflop ist zurückgesetzt (**Q = FALSE**)                                   | Setzen von **Q** auf FALSE (nur wenn **QI=TRUE**) | EO  |

**Übergänge:**

*   START → Init: INIT ∧ (QI = TRUE)
*   Init → SET: Q_INIT = TRUE
*   Init → RESET: Q_INIT = FALSE
*   SET → RESET: R
*   RESET → SET: S
*   SET → DeInit: INIT ∧ (QI = FALSE)
*   RESET → DeInit: INIT ∧ (QI = FALSE)
*   DeInit → START: 1 (immer)

## Anwendungsszenarien

*   **Steuerungen mit definiertem Einschaltverhalten**: Wenn nach einem Neustart der Automatisierungsanlage ein bestimmter Startwert für einen Merker oder ein Ausgang benötigt wird (z. B. TRUE für „Anlage läuft“ oder FALSE für „stillgelegt“), kann **Q_INIT** entsprechend gesetzt werden.
*   **Sichere Resets bei Störungen**: Durch die Deinitialisierung (INIT mit QI=FALSE) kann der Baustein in einen definierten „Ausgangszustand“ versetzt werden, ohne den aktuellen Wert von **Q** zu löschen. Dies ist nützlich, um z. B. einen „Wiederanlauf nach Störung“ zu realisieren.
*   **Qualifizierte Setz- und Rücksetzoperationen**: Über **QI** kann eine übergeordnete Bedingung (z. B. „Freigabe aktiver Betrieb“) geschaltet werden. Nur wenn **QI** = TRUE, haben Setzen und Rücksetzen tatsächlich Auswirkung auf **Q**.
*   **Initialisierung von Zustandsautomaten**: Der Baustein eignet sich hervorragend als Grundbaustein für eigene Zustandsautomaten, die bei INIT einen bestimmten Anfangszustand einnehmen sollen.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Unterschied zu E_RS_SYM_INIT |
|----------|-------------------------------|
| **E_RS** (Standard RS-Flipflop) | Kein explizites Startverhalten; bei INIT wird **Q** nicht definiert. **Q_INIT** fehlt. |
| **E_SR** (Set-Dominant-Flipflop) | Dominanz von Set über Reset; kein initialisierbarer Startzustand. |
| **E_RS_SYM** | Symmetrische RS-Logik ohne INIT-Funktion; kein Startverhalten. |
| **E_RS_SYM_INIT** (dieser) | Kombiniert symmetrische RS-Logik mit wählbarem Initialwert und Deinitialisierung. |

## Fazit

**E_RS_SYM_INIT** ist ein leistungsstarker und flexibler Funktionsblock der IEC 61499-1 für ereignisgesteuerte bistabile Kippschalter. Durch die explizite Initialisierung mit **Q_INIT** und die Möglichkeit zur Deinitialisierung unter Beibehaltung des Ausgangswertes eignet er sich besonders für sicherheitsrelevante und automatisierungstechnische Anwendungen, bei denen ein definiertes Startverhalten und eine saubere Trennung von Initialisierung und Betrieb gefordert sind. Die Berücksichtigung eines Qualifizierers **QI** ermöglicht zudem eine effiziente Einbindung in komplexe Ablaufsteuerungen.