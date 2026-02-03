# F_MULTIME

```{index} single: F_MULTIME
```

![F_MULTIME](https://github.com/user-attachments/assets/89982d6d-aa50-4897-b32c-6d280da63b1a)

* * * * * * * * * *

![F_MULTIME](F_MULTIME.svg)


## Einführung
Der **F_MULTIME** ist ein standardkonformer Funktionsbaustein zur Multiplikation von Zeitwerten mit numerischen Faktoren, entwickelt unter EPL-2.0 Lizenz. Version 1.0 ermöglicht die typsichere Skalierung von Zeitintervallen gemäß IEC 61131-3 Standard.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Berechnungsanforderung (mit Zeitwert und Multiplikator)

### **Ereignis-Ausgänge**
- `CNF`: Berechnungsbestätigung (mit skaliertem Zeitwert)

### **Daten-Eingänge**
- `IN1` (TIME): Zeitwert (Basiswert)
- `IN2` (ANY_NUM): Skalierungsfaktor

### **Daten-Ausgänge**
- `OUT` (TIME): Skalierter Zeitwert (IN1 × IN2)

## Funktionsprinzip

1. **Berechnungsauslösung**:
   - `REQ`-Ereignis mit Zeitwert (IN1) und Faktor (IN2)
   - IN1 muss TIME-Typ, IN2 muss ANY_NUM-Typ sein

2. **Multiplikation**:
   - Zeitwert wird in Nanosekunden konvertiert
   - Multiplikation mit numerischem Faktor
   - Rückkonvertierung in TIME-Datentyp

3. **Ergebnisausgabe**:
   - `CNF`-Ereignis mit skaliertem Zeitwert
   - Ergebnis immer vom Typ TIME

## Technische Besonderheiten

✔ **Typsichere Zeitwertverarbeitung**
✔ **Präzise Nanosekundenberechnung**
✔ **Automatische Typkonvertierung** (ANY_NUM → REAL)
✔ **Überlaufschutz** (Begrenzung auf TIME-Maximalwert)

## Anwendungsszenarien

- **Zykluszeit-Anpassung**: Skalierung von Zeitintervallen
- **Prozesssteuerung**: Verlängerung/Verkürzung von Timeouts
- **Bewegungssteuerung**: Geschwindigkeitsanpassungen
- **Zeitplanung**: Dynamische Zeitplan-Skalierung

## Fehlerbehandlung

- **Überlaufbehandlung**:
  - Begrenzung auf T#24d20h31m23s647ms (Maximum)
  - Keine Wrap-around bei Zeitwerten

- **Typinkompatibilität**:
  - OUT = T#0s
  - Keine Exception-Generierung

## ⚖️ Vergleich mit ähnlichen Bausteinen

| Feature        | F_MULTIME | F_MUL  | F_DIVTIME |
|---------------|-----------|--------|-----------|
| Operation     | Zeitmultiplikation | Numerische Multiplikation | Zeitdivision |
| Eingänge      | TIME × ANY_NUM | ANY_NUM × ANY_NUM | TIME ÷ ANY_NUM |
| Ausgangstyp   | TIME      | ANY_NUM | TIME      |






## 🛠️ Zugehörige Übungen

* [Uebung_020c2](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_020c2.md)

## Fazit

Der F_MULTIME-Baustein bietet eine spezialisierte Lösung für die Skalierung von Zeitwerten:

- Industrietaugliche Präzision (Nanosekundenbasis)
- Sichere Typkonvertierung
- Robuste Überlaufbehandlung

Unverzichtbar für Anwendungen mit dynamisch anpassbaren Zeitparametern und zyklischen Steuerungsprozessen.