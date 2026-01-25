![E_TP](E_TP.svg)

# E_TP

```{index} single: E_TP
```

**Wichtiger Hinweis: Dieser Baustein benötigt nur ein Ereignis (Event) und keine zyklischen Aufrufe. Er besitzt keinen Ausgang ET und zeigt die verstrichene Zeit nicht an.**

## Bild

![image](https://github.com/user-attachments/assets/8d531305-da9a-42e8-b44d-afab3a955be6)

## Text

## Beschreibung

Der Baustein **E_TP** (auch bekannt als **Pulsgeber** oder **Timer-Puls**) ist ein standardisiertes Funktionsbaustein (FB) nach der Norm **IEC 61499** (DIN EN 61499). Dieser Baustein wird verwendet, um einen pulsierenden Ausgang zu erzeugen, der für eine bestimmte Zeit aktiviert wird, wenn ein Eingangssignal empfangen wird. Er ist besonders nützlich in Steuerungsanwendungen, bei denen zeitgesteuerte Aktionen erforderlich sind.

### Beschreibung des Bausteins E_TP:

#### **Allgemeine Funktion:**
- Der Baustein **E_TP** generiert einen pulsierenden Ausgang (**Q**), der für eine vorgegebene Zeit (**PT**) aktiviert wird, sobald ein Eingangssignal (**IN**) empfangen wird.
- Wenn das Eingangssignal **IN** den Wert **TRUE** annimmt, wird der Ausgang **Q** für die Zeitdauer **PT** auf **TRUE** gesetzt. Nach Ablauf der Zeit **PT** wird **Q** wieder auf **FALSE** zurückgesetzt, unabhängig vom Zustand von **IN**.
- Der Baustein verfügt über eine Reset-Funktion (**R**), die den Timer zurücksetzt und den Ausgang **Q** sofort auf **FALSE** setzt, unabhängig davon, ob die Zeit **PT** abgelaufen ist oder nicht.

#### **Schnittstellen (Interface):**

1. **Eingangsereignisse (Event Inputs):**
   - **REQ (Service Request):** Dieses Ereignis wird ausgelöst, wenn der Timer gestartet werden soll. Es ist mit den Eingangsvariablen **IN** und **PT** verknüpft.
   - **R (Reset):** Dieses Ereignis wird ausgelöst, um den Timer zurückzusetzen. Es ist mit der Eingangsvariablen **IN** verknüpft.

2. **Ausgangsereignisse (Event Outputs):**
   - **CNF (Confirmation of Requested Service):** Dieses Ereignis wird ausgelöst, wenn der Timer abgelaufen ist und der Ausgang **Q** zurückgesetzt wird. Es ist mit der Ausgangsvariablen **Q** verknüpft.

3. **Eingangsvariablen (Input Variables):**
   - **IN (BOOL):** Der Eingang, der den Timer startet. Wenn **IN** den Wert **TRUE** annimmt, wird der Timer gestartet.
   - **PT (TIME):** Die vorgegebene Zeitdauer, für die der Ausgang **Q** aktiviert wird.

4. **Ausgangsvariablen (Output Variables):**
   - **Q (BOOL):** Der Ausgang, der für die Zeitdauer **PT** auf **TRUE** gesetzt wird, nachdem **IN** aktiviert wurde.

#### **Verhalten:**
- Wenn **IN** auf **TRUE** gesetzt wird, wird der Ausgang **Q** sofort auf **TRUE** gesetzt und bleibt für die Zeitdauer **PT** aktiv.
- Nach Ablauf der Zeit **PT** wird **Q** automatisch auf **FALSE** zurückgesetzt.
- Wenn das Reset-Ereignis **R** ausgelöst wird, wird der Timer sofort zurückgesetzt, und **Q** wird auf **FALSE** gesetzt, unabhängig davon, ob die Zeit **PT** abgelaufen ist oder nicht.

#### **Anwendungsbeispiele:**
- **Steuerung von Maschinen:** Der Baustein kann verwendet werden, um eine Maschine für eine bestimmte Zeit zu aktivieren, z. B. das Einschalten eines Motors für eine festgelegte Dauer.
- **Blinklichtsteuerung:** Der Baustein kann verwendet werden, um ein Blinklicht für eine bestimmte Zeit zu aktivieren.
- **Verzögerte Aktionen:** In Szenarien, in denen eine Aktion nach einer bestimmten Verzögerung ausgeführt werden soll, kann der Baustein verwendet werden, um die Verzögerung zu realisieren.

#### **Versionierung:**
- **Version 1.0:** Ursprüngliche Version des Bausteins, erstellt von Franz Hoepfinger am 04.03.2024.
- **Version 1.1:** Eine Reset-Funktion wurde hinzugefügt, um den Timer manuell zurücksetzen zu können. Diese Version wurde am 23.04.2024 veröffentlicht.

### Zusammenfassung:
Der **E_TP**-Baustein ist ein nützliches Werkzeug in der IEC 61499-basierten Steuerungstechnik, um zeitgesteuerte Aktionen zu realisieren. Durch seine einfache Schnittstelle und das klare Verhalten ist er leicht in verschiedene Steuerungsanwendungen integrierbar. Die Reset-Funktion in Version 1.1 erhöht die Flexibilität des Bausteins, da der Timer nun manuell zurückgesetzt werden kann.

## Zugehörige Übungen

* [Uebung_020f](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_020f.md)
* [Uebung_039b](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_039b.md)
