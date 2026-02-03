# GreenWhiteBackground

```{index} single: GreenWhiteBackground
```

<img width="1273" height="233" alt="image" src="https://github.com/user-attachments/assets/ec8d48e6-6d6b-4749-bbe0-e53d06b6be01" />

* * * * * * * * * *

## Einleitung
Die Übung "GreenWhiteBackground" demonstriert die Verwendung von Hintergrundfarben in einem ISOBUS-konformen System. Die Subapplikation ermöglicht das Umschalten zwischen grüner und weißer Hintergrundfarbe für ein bestimmtes Objekt basierend auf einem Selektorsignal.

## Verwendete Funktionsbausteine (FBs)

### Sub-Bausteine: GreenWhiteBackground
- **Typ**: SubAppType
- **Verwendete interne FBs**:
    - **Q_BackgroundColour**: isobus::UT::Q::Q_BackgroundColour
        - Parameter: Keine expliziten Parameter
        - Ereignisausgang/-eingang: REQ (Eingang), CNF (Ausgang)
        - Datenausgang/-eingang: u16ObjId (Eingang), u8Colour (Eingang), s16result (Ausgang), u8OldColour (Ausgang), STATUS (Ausgang)

    - **F_SEL_I**: iec61131::selection::F_SEL
        - Parameter: IN0 = COLOR_WHITE, IN1 = COLOR_GREEN
        - Ereignisausgang/-eingang: REQ (Eingang), CNF (Ausgang)
        - Datenausgang/-eingang: G (Eingang), OUT (Ausgang)

- **Funktionsweise**:
  Der F_SEL_I-Baustein wählt basierend auf dem DI1-Signal zwischen den Farben WHITE (IN0) und GREEN (IN1) aus. Die ausgewählte Farbe wird an Q_BackgroundColour übergeben, der die Hintergrundfarbe für das spezifizierte Objekt (u16ObjId) ändert.

## Programmablauf und Verbindungen

**Ereignisverbindungen:**
- REQ → F_SEL_I.REQ
- F_SEL_I.CNF → Q_BackgroundColour.REQ
- Q_BackgroundColour.CNF → CNF

**Datenverbindungen:**
- DI1 → F_SEL_I.G (Selektor-Eingang)
- u16ObjId → Q_BackgroundColour.u16ObjId (Objekt-ID)
- F_SEL_I.OUT → Q_BackgroundColour.u8Colour (ausgewählte Farbe)
- Q_BackgroundColour.s16result → result_1 (Ergebnis)
- Q_BackgroundColour.u8OldColour → u8OldColour_1 (alte Farbe)
- Q_BackgroundColour.STATUS → STATUS_1 (Statusinformation)

**Lernziele:**
- Verwendung von Selektions-Funktionsbausteinen
- Implementierung von Farbwechsel-Funktionalität
- Umgang mit ISOBUS-konformen Funktionsbausteinen
- Verarbeitung von Objekt-IDs in ISOBUS-Systemen

**Schwierigkeitsgrad**: Einfach bis Mittel

**Benötigte Vorkenntnisse**: Grundkenntnisse in IEC 61499 und ISOBUS-Standards

**Start der Übung**: Die Übung wird durch das REQ-Ereignis gestartet, wobei DI1 den Farbwechsel steuert und u16ObjId das Zielobjekt identifiziert.

## Zusammenfassung
Die GreenWhiteBackground-Übung zeigt eine praktische Anwendung zur dynamischen Änderung von Hintergrundfarben in ISOBUS-Systemen. Durch die Kombination eines Selektionsbausteins mit einem ISOBUS-spezifischen Farbsteuerungsbaustein wird ein einfacher aber effektiver Farbwechselmechanismus implementiert, der grundlegende Konzepte der Funktionsbausteinprogrammierung und ISOBUS-Kommunikation vermittelt.

## Zugehörige Übungen

* [Uebung_010c](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_010c.md)
* [Uebung_010c2](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_010c2.md)
* [Uebung_010c3_sub](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_010c3_sub.md)
* [Uebung_010c4_sub](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_010c4_sub.md)
* [Uebung_039_sub_Outputs](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_039_sub_Outputs.md)
* [Uebung_039a_sub_Outputs](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_039a_sub_Outputs.md)
