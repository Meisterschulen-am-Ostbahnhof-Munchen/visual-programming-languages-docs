# E_SELECT

```{index} single: E_SELECT
```

![E_SELECT Logiksymbol](https://user-images.githubusercontent.com/69573151/210802464-116ee202-5bba-4394-bb08-38411823d000.png)

* * * * * * * * * *

## Einleitung
Der **E_SELECT** ist ein grundlegender Funktionsbaustein nach IEC 61499 (Annex A), der die bedingte Weiterleitung von Ereignissen basierend auf einem Steuersignal ermöglicht. Die aktuelle Version 1.0 steht unter EPL-2.0 Lizenz.

![E_SELECT](E_SELECT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `EI0`: Eingangsereignis (wird bei G=0 weitergeleitet)
- `EI1`: Eingangsereignis (wird bei G=1 weitergeleitet)

### **Ereignis-Ausgang**
- `EO`: Ausgangsereignis (weitergeleitetes Ereignis)

### **Daten-Eingang**
- `G` (BOOL): Steuersignal für die Auswahl:
  - G=0: Weiterleitung von EI0
  - G=1: Weiterleitung von EI1

## Funktionsweise

1. **Ereignisverarbeitung**:
   - Bei Eingang von EI0 oder EI1 wird der G-Wert ausgewertet
   - Nur das zum G-Wert passende Ereignis wird weitergeleitet

2. **Zustandsautomat** (ECC):
   - **START**: Wartezustand
   - **EO**: Ausgabezustand (mit EO-Aktion)
   - Transitionen:
     - EI0 bei G=0 → EO
     - EI1 bei G=1 → EO
     - Immer Rückkehr zu START

3. **Ausführungslogik**:
   - Deterministische Ereignisauswahl
   - Keine Pufferung von Ereignissen

## Technische Besonderheiten

✔ **Boolesche Steuerung** der Ereignisauswahl
✔ **Echtzeitfähige** Verarbeitung
✔ **Zustandsbasierte** Implementierung (BasicFB)
✔ **EPL-2.0 Open-Source** Implementierung

## Anwendungsszenarien

- **Verzweigte Prozesssteuerung**: Alternative Ablaufpfade
- **Modusumschaltung**: Betriebsartenwechsel
- **Fehlerbehandlung**: Alternative Fehlerroutinen
- **Testautomation**: Umschaltung Test-/Normalbetrieb

## ⚖️ Vergleich mit ähnlichen Bausteinen

| Feature        | E_SELECT | E_SWITCH | E_MERGE |
|---------------|----------|----------|---------|
| Auswahlkriterium | Boolesch (`G`) | Boolesch (`G`) | Keines |
| Richtung      | 2:1 (Multiplexer)      | 1:2 (Demultiplexer)     | n:1 (OR-Gatter)     |
| Zustandsmodell | BasicFB  | BasicFB | BasicFB/Generic |






## 🛠️ Zugehörige Übungen

* [Uebung_095](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_095.md)

## Fazit

Der E_SELECT-Baustein bietet eine robuste Lösung für ereignisbasierte Steuerungsentscheidungen:

- Einfache aber wirkungsvolle Selektion
- Klare Zustandsmaschinen-Implementierung
- Standardkonforme Schnittstelle

Durch seine deterministische Arbeitsweise eignet er sich besonders für sicherheitskritische Anwendungen und komplexe Steuerungslogiken. Die Verwendung als BasicFB ermöglicht zudem die Integration in alle IEC 61499-konformen Entwicklungsumgebungen.

Siehe auch: [https://www.holobloc.com/doc/fb/rt/events/E_SELECT.htm](https://www.holobloc.com/doc/fb/rt/events/E_SELECT.htm)