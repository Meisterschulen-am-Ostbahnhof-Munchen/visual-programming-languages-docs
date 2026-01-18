# E_TON

```{index} single: E_TON
```

**Wichtiger Hinweis: Dieser Baustein benötigt nur ein Ereignis (Event) und keine zyklischen Aufrufe. Er besitzt keinen Ausgang ET und zeigt die verstrichene Zeit nicht an.**

## Bild

![image](https://github.com/user-attachments/assets/cc035168-0f10-4159-bbe5-941ec9919630)

## Text 

Der Baustein **E_TON** ist ein standardisierter Funktionsbaustein-Typ (FBType) gemäß der Norm **IEC 61499**, der für **On-Delay-Timer** (Einschaltverzögerung) in industriellen Automatisierungssystemen verwendet wird. Dieser Baustein ermöglicht es, ein Signal zeitlich verzögert einzuschalten, was in vielen Steuerungsanwendungen erforderlich ist, um beispielsweise Maschinen oder Prozesse sicher zu steuern.

### Allgemeine Beschreibung:
- **Name**: E_TON
- **Typ**: Standard Timer Function Block (On-Delay Timing)
- **Zweck**: Der Baustein wird verwendet, um eine zeitverzögerte Einschaltfunktion zu realisieren. Er ist besonders nützlich in Anwendungen, bei denen eine Verzögerung beim Einschalten eines Signals erforderlich ist.
- **Lizenz**: Der Baustein ist unter der Eclipse Public License 2.0 (EPL-2.0) lizenziert.

---

### Interface-Beschreibung:

#### **Eingangsereignisse (Event Inputs):**
1. **REQ** (Normal Execution Request):
   - **Typ**: Event
   - **Beschreibung**: Dieses Ereignis triggert die normale Ausführung des Bausteins. Es wird verwendet, um den Timer zu starten oder zu aktualisieren.
   - **Zugehörige Variablen**:
     - **IN**: Der Eingangswert, der den Timer startet.
     - **PT**: Die vorgegebene Zeitdauer für die Einschaltverzögerung (On-Delay).

#### **Ausgangsereignisse (Event Outputs):**
1. **CNF** (Execution Confirmation):
   - **Typ**: Event
   - **Beschreibung**: Dieses Ereignis bestätigt die Ausführung des Bausteins. Es wird ausgelöst, wenn der Timer abgelaufen ist oder ein Zustandswechsel stattgefunden hat.
   - **Zugehörige Variable**:
     - **Q**: Der Ausgangswert, der den Zustand des Timers anzeigt.

#### **Eingangsvariablen (Input Variables):**
1. **IN**:
   - **Typ**: BOOL
   - **Beschreibung**: Der Eingangswert, der den Timer startet. Wenn **IN** auf `TRUE` gesetzt wird, startet die Einschaltverzögerung (**PT**). Der Ausgang **Q** wird erst nach Ablauf der Zeit **PT** auf `TRUE` gesetzt.

2. **PT**:
   - **Typ**: TIME
   - **Beschreibung**: Die vorgegebene Zeitdauer für die Einschaltverzögerung (On-Delay). Diese Zeit wird ab dem Moment gemessen, in dem **IN** auf `TRUE` gesetzt wird.

#### **Ausgangsvariablen (Output Variables):**
1. **Q**:
   - **Typ**: BOOL
   - **Beschreibung**: Der Ausgangswert, der den Zustand des Timers anzeigt. **Q** wird auf `TRUE` gesetzt, nachdem die Einschaltverzögerung (**PT**) abgelaufen ist.

---

### Funktionsweise:
1. **Einschaltverzögerung (On-Delay)**:
   - Wenn **IN** auf `TRUE` gesetzt wird, startet der Timer für die Einschaltverzögerung (**PT**).
   - Nach Ablauf von **PT** wird **Q** auf `TRUE` gesetzt.
   - Wenn **IN** während des Timers auf `FALSE` gesetzt wird, wird der Timer gestoppt, und **Q** bleibt auf `FALSE`.

2. **Bestätigung der Ausführung (CNF)**:
   - Das Ereignis **CNF** wird ausgelöst, wenn der Timer abgelaufen ist und **Q** auf `TRUE` gesetzt wird.

---

### Anwendungsbeispiele:
- **Maschinensteuerung**: Verzögerte Reaktion auf Sensoren oder Schaltbefehle, z. B. um ein Überlasten von Motoren zu vermeiden.
- **Prozessautomatisierung**: Zeitgesteuerte Schaltvorgänge in industriellen Prozessen, z. B. in Förderbändern oder Heizungssteuerungen.

---

### Zusammenfassung:
Der **E_TON**-Baustein ist ein einfaches, aber leistungsstarkes Werkzeug in der IEC 61499, um zeitverzögerte Einschaltvorgänge in industriellen Automatisierungssystemen zu realisieren. Er bietet eine zuverlässige Möglichkeit, Signale mit einer definierten Verzögerung einzuschalten, was in vielen Steuerungsanwendungen unerlässlich ist. Der Baustein ist einfach zu konfigurieren und kann in einer Vielzahl von Szenarien eingesetzt werden, bei denen eine zeitliche Verzögerung erforderlich ist.
