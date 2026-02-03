# tastend_TON_5s

```{index} single: tastend_TON_5s
```

* * * * * * * * * *

## Einleitung
Diese Übung demonstriert die Verwendung eines Zeitrelais (Timer On-Delay) mit einer festen Zeitvorgabe von 5 Sekunden. Die Subapplikation dient als wiederverwendbare Komponente zur Signalverarbeitung mit Zeitverzögerung.

## Verwendete Funktionsbausteine (FBs)

### Sub-Bausteine: tastend_TON_5s
- **Typ**: SubAppType
- **Verwendete interne FBs**:
    - **AX_X_TO_BOOL**: adapter::conversion::unidirectional::AX_X_TO_BOOL
        - Parameter: Keine
        - Ereignisausgang/-eingang: CNF (Ausgang), REQ (Eingang)
        - Datenausgang/-eingang: IN (Eingang), OUT (Ausgang)
    - **E_TON**: iec61499::events::timers::E_TON
        - Parameter: PT = t#5s
        - Ereignisausgang/-eingang: CNF (Ausgang), REQ (Eingang)
        - Datenausgang/-eingang: IN (Eingang), Q (Ausgang)
    - **AX_BOOL_TO_X**: adapter::conversion::unidirectional::AX_BOOL_TO_X
        - Parameter: Keine
        - Ereignisausgang/-eingang: REQ (Eingang), CNF (Ausgang)
        - Datenausgang/-eingang: OUT (Eingang), AX_OUT (Ausgang)

- **Funktionsweise**:
    Die Subapplikation wandelt ein eingehendes Adaptersignal (IN) über AX_X_TO_BOOL in einen Booleschen Wert um, der dann an den E_TON Timer weitergeleitet wird. Der Timer wartet 5 Sekunden, bevor er das Ausgangssignal über Q aktiviert. Dieses Signal wird anschließend über AX_BOOL_TO_X zurück in ein Adaptersignal (OUT) konvertiert.

## Programmablauf und Verbindungen

**Adapterverbindungen:**
- Eingang: IN → AX_X_TO_BOOL.AX_IN
- Ausgang: AX_BOOL_TO_X.AX_OUT → OUT

**Ereignisverbindungen:**
- AX_X_TO_BOOL.CNF → E_TON.REQ
- E_TON.CNF → AX_BOOL_TO_X.REQ

**Datenverbindungen:**
- AX_X_TO_BOOL.IN → E_TON.IN
- E_TON.Q → AX_BOOL_TO_X.OUT

**Lernziele:**
- Verständnis von Timer-Funktionsbausteinen (E_TON)
- Umgang mit Adapter-Konvertierungsbausteinen
- Aufbau von wiederverwendbaren Subapplikationen
- Zeitgesteuerte Signalverarbeitung

**Schwierigkeitsgrad**: Einsteiger

**Benötigte Vorkenntnisse**: Grundlagen der 4diac-IDE, Verständnis von Funktionsbausteinen und Adaptern

**Start der Übung**: Die Subapplikation kann in größere Applikationen integriert werden, wo eine 5-Sekunden-Verzögerung benötigt wird.

## Zusammenfassung
Die Subapplikation tastend_TON_5s stellt eine kompakte Lösung für zeitverzögerte Signalverarbeitung dar. Durch die feste Zeitvorgabe von 5 Sekunden und die Verwendung standardisierter Adapter-Schnittstellen kann sie einfach in verschiedene Steuerungsanwendungen integriert werden. Die klare Struktur mit Signalwandlung, Timer-Funktionalität und Rückwandlung macht die Funktionsweise transparent und nachvollziehbar.



## 🛠️ Zugehörige Übungen

* [Uebung_103](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_103.md)
* [Uebung_103c](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_103c.md)

