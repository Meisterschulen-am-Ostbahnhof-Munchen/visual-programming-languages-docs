# Rastend

```{index} single: Rastend
```

<img width="666" height="233" alt="image" src="https://github.com/user-attachments/assets/b3bfdaca-bb42-428f-a91a-2e367b347faf" />

* * * * * * * * * *

## Einleitung
Diese Übung implementiert eine rastende Schaltfunktion, die beim Loslassen eines Signals gestartet wird. Die Subapplikation verwendet Adapter für die Signalverarbeitung und Ereignissteuerung, um eine zuverlässige Rastfunktionalität zu realisieren.

## Verwendete Funktionsbausteine (FBs)

### Sub-Bausteine: rastend
- **Typ**: SubAppType
- **Verwendete interne FBs**:
    - **E_T_FF**: iec61499::events::E_T_FF
        - Ereigniseingang: CLK
        - Ereignisausgang: EO
        - Datenausgang: Q
    - **E_SWITCH**: iec61499::events::E_SWITCH
        - Ereigniseingang: EI
        - Ereignisausgang: EO0
        - Dateneingang: G
    - **AX_X_TO_BOOL**: adapter::conversion::unidirectional::AX_X_TO_BOOL
        - Adaptereingang: AX_IN
        - Ereignisausgang: CNF
        - Dateneingang: IN
    - **AX_BOOL_TO_X**: adapter::conversion::unidirectional::AX_BOOL_TO_X
        - Ereigniseingang: REQ
        - Adapterausgang: AX_OUT
        - Dateneingang: OUT

- **Funktionsweise**: Die Subapplikation wandelt eingehende AX-Signale in boolesche Werte um, verarbeitet diese über einen Toggle-Flipflop mit Schalterfunktion und gibt das Ergebnis wieder als AX-Signal aus.

## Programmablauf und Verbindungen

Der Programmablauf folgt dieser Signalverarbeitungskette:

1. **Eingangssignalverarbeitung**: Das eingehende AX-Signal wird über den Adapter IN an AX_X_TO_BOOL weitergeleitet
2. **Signalumwandlung**: AX_X_TO_BOOL konvertiert das AX-Signal in einen booleschen Wert
3. **Schaltersteuerung**: Der boolesche Wert steuert den E_SWITCH, der Ereignisse an den Toggle-Flipflop weiterleitet
4. **Rastfunktion**: E_T_FF realisiert die eigentliche Rastfunktion und speichert den Zustand
5. **Ausgangssignalgenerierung**: AX_BOOL_TO_X wandelt den booleschen Ausgangswert zurück in ein AX-Signal

**Verbindungen im Detail**:
- Ereignisverbindungen: E_SWITCH.EO0 → E_T_FF.CLK, E_T_FF.EO → AX_BOOL_TO_X.REQ, AX_X_TO_BOOL.CNF → E_SWITCH.EI
- Datenverbindungen: E_T_FF.Q → AX_BOOL_TO_X.OUT, AX_X_TO_BOOL.IN → E_SWITCH.G
- Adapterverbindungen: IN → AX_X_TO_BOOL.AX_IN, AX_BOOL_TO_X.AX_OUT → OUT

## Zusammenfassung
Diese Übung demonstriert die Implementierung einer rastenden Schaltfunktion mit Adaptern für Signalumwandlung. Sie zeigt die Verwendung von Toggle-Flipflops für Zustandsspeicherung und die strukturierte Signalverarbeitung über verschiedene Funktionsbausteine. Die Lösung ist besonders geeignet für Anwendungen, bei denen ein Signal nach dem Loslassen aktiv bleiben soll.



## 🛠️ Zugehörige Übungen

* [Uebung_103](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_103.md)
* [Uebung_103c](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_103c.md)
* [Uebung_103c2](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_103c2.md)

