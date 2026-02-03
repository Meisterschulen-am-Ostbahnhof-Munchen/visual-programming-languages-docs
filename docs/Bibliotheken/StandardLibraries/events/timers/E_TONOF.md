![E_TONOF](E_TONOF.svg)

# E_TONOF

```{index} single: E_TONOF
```

**Wichtiger Hinweis: Dieser Baustein benötigt nur ein Ereignis (Event) und keine zyklischen Aufrufe. Er besitzt keinen Ausgang ET und zeigt die verstrichene Zeit nicht an.**

## Bild

![image](https://github.com/user-attachments/assets/e09eae11-e153-429f-8eaf-6bfff456f35a)

## Text

## Beschreibung
Der Baustein **E_TONOF** ist ein standardisiertes Funktionsbaustein-Typ (FBType) gemäß der Norm **IEC 61499**, der für zeitverzögerte Schaltvorgänge in industriellen Automatisierungssystemen verwendet wird. Dieser Baustein kombiniert die Funktionen eines **On-Delay-Timers** (Einschaltverzögerung) und eines **Off-Delay-Timers** (Ausschaltverzögerung) in einem einzigen Baustein. Er ermöglicht es, sowohl das Einschalten als auch das Ausschalten eines Signals zeitlich zu verzögern.

### Allgemeine Beschreibung:
- **Name**: E_TONOF
- **Typ**: Standard Timer Function Block (On/Off-Delay Timing)
- **Zweck**: Der Baustein wird verwendet, um zeitverzögerte Schaltvorgänge in Steuerungssystemen zu realisieren. Er ist besonders nützlich in Anwendungen, bei denen eine Verzögerung beim Ein- oder Ausschalten von Signalen erforderlich ist.
- **Lizenz**: Der Baustein ist unter der Eclipse Public License 2.0 (EPL-2.0) lizenziert.

---

### Interface-Beschreibung:

#### **Eingangsereignisse (Event Inputs):**
1. **REQ** (Normal Execution Request):
   - **Typ**: Event
   - **Beschreibung**: Dieses Ereignis triggert die normale Ausführung des Bausteins. Es wird verwendet, um den Timer zu starten oder zu aktualisieren.
   - **Zugehörige Variablen**:
     - **IN**: Der Eingangswert, der den Timer startet.
     - **PT_ON**: Die vorgegebene Zeitdauer für die Einschaltverzögerung (On-Delay).
     - **PT_OFF**: Die vorgegebene Zeitdauer für die Ausschaltverzögerung (Off-Delay).

2. **R** (Reset):
   - **Typ**: Event
   - **Beschreibung**: Dieses Ereignis setzt den Timer zurück. Wenn dieses Ereignis ausgelöst wird, wird der Timer gestoppt, und alle internen Zustände werden zurückgesetzt.

#### **Ausgangsereignisse (Event Outputs):**
1. **CNF** (Execution Confirmation):
   - **Typ**: Event
   - **Beschreibung**: Dieses Ereignis bestätigt die Ausführung des Bausteins. Es wird ausgelöst, wenn der Timer abgelaufen ist oder ein Zustandswechsel stattgefunden hat.
   - **Zugehörige Variable**:
     - **Q**: Der Ausgangswert, der den Zustand des Timers anzeigt.

#### **Eingangsvariablen (Input Variables):**
1. **IN**:
   - **Typ**: BOOL
   - **Beschreibung**: Der Eingangswert, der den Timer startet. Wenn **IN** auf `TRUE` gesetzt wird, startet die Einschaltverzögerung (On-Delay). Wenn **IN** auf `FALSE` gesetzt wird, startet die Ausschaltverzögerung (Off-Delay).

2. **PT_ON**:
   - **Typ**: TIME
   - **Beschreibung**: Die vorgegebene Zeitdauer für die Einschaltverzögerung (On-Delay). Diese Zeit wird ab dem Moment gemessen, in dem **IN** auf `TRUE` gesetzt wird.

3. **PT_OFF**:
   - **Typ**: TIME
   - **Beschreibung**: Die vorgegebene Zeitdauer für die Ausschaltverzögerung (Off-Delay). Diese Zeit wird ab dem Moment gemessen, in dem **IN** auf `FALSE` gesetzt wird.

#### **Ausgangsvariablen (Output Variables):**
1. **Q**:
   - **Typ**: BOOL
   - **Beschreibung**: Der Ausgangswert, der den Zustand des Timers anzeigt. **Q** wird auf `TRUE` gesetzt, nachdem die Einschaltverzögerung (On-Delay) abgelaufen ist, und bleibt so lange auf `TRUE`, bis die Ausschaltverzögerung (Off-Delay) abgelaufen ist.

---

### Funktionsweise:
1. **Einschaltverzögerung (On-Delay)**:
   - Wenn **IN** auf `TRUE` gesetzt wird, startet der Timer für die Einschaltverzögerung (**PT_ON**).
   - Nach Ablauf von **PT_ON** wird **Q** auf `TRUE` gesetzt.

2. **Ausschaltverzögerung (Off-Delay)**:
   - Wenn **IN** auf `FALSE` gesetzt wird, startet der Timer für die Ausschaltverzögerung (**PT_OFF**).
   - **Q** bleibt so lange auf `TRUE`, bis **PT_OFF** abgelaufen ist, und wird dann auf `FALSE` zurückgesetzt.

3. **Reset**:
   - Wenn das **R**-Ereignis ausgelöst wird, wird der Timer zurückgesetzt, und **Q** wird sofort auf `FALSE` gesetzt.

---

### Anwendungsbeispiele:
- **Maschinensteuerung**: Verzögerte Reaktion auf Sensoren oder Schaltbefehle, z. B. um ein Überlasten von Motoren zu vermeiden.
- **Prozessautomatisierung**: Zeitgesteuerte Schaltvorgänge in industriellen Prozessen, z. B. in Förderbändern oder Heizungssteuerungen.

---

### Zusammenfassung:
Der **E_TONOF**-Baustein ist ein leistungsstarkes Werkzeug in der IEC 61499, um zeitverzögerte Schaltvorgänge in industriellen Automatisierungssystemen zu realisieren. Er kombiniert die Funktionen eines Ein- und Ausschaltverzögerungstimers in einem einzigen Baustein und bietet zusätzlich die Möglichkeit, den Timer über ein Reset-Ereignis zurückzusetzen. Dies macht ihn besonders flexibel und vielseitig einsetzbar in komplexen Steuerungsaufgaben.





## 🛠️ Zugehörige Übungen

* [Uebung_020g](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_020g.md)

