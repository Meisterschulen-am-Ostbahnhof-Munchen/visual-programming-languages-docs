# F_SUB

```{index} single: F_SUB
```

![F_SUB](https://user-images.githubusercontent.com/116869307/214143366-6c54d805-8807-48bd-b8fb-2ad08dd2f1b8.png)

* * * * * * * * * *

![F_SUB](F_SUB.svg)


## Einführung
Der **F_SUB** ist ein standardkonformer Funktionsbaustein zur Subtraktion numerischer Werte, entwickelt unter EPL-2.0 Lizenz. Version 1.0 ermöglicht die typsichere Differenzbildung verschiedener numerischer Datentypen gemäß IEC 61131-3 Standard.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Berechnungsanforderung (mit Minuend und Subtrahend)

### **Ereignis-Ausgänge**
- `CNF`: Berechnungsbestätigung (mit Ergebnis)

### **Daten-Eingänge**
- `IN1` (ANY_MAGNITUDE): Minuend (Wert, von dem subtrahiert wird)
- `IN2` (ANY_MAGNITUDE): Subtrahend (Wert, der subtrahiert wird)

### **Daten-Ausgänge**
- `OUT` (ANY_MAGNITUDE): Differenz der Subtraktion (IN1 - IN2)

## Funktionsprinzip

1. **Berechnungsauslösung**:
   - `REQ`-Ereignis mit Werten für IN1 und IN2
   - Beide Eingänge müssen vom Typ ANY_MAGNITUDE sein

2. **Subtraktion**:
   - Typenerhaltende Berechnung (IN1 - IN2)
   - Unterstützte Typen:
     - Ganzzahlen (INT, DINT)
     - Fließkommazahlen (REAL, LREAL)
     - Zeitwerte (TIME, DATE)
     - Gemischte Typen (automatische Konvertierung)

3. **Ergebnisausgabe**:
   - `CNF`-Ereignis mit berechneter Differenz
   - Ergebnis im "größten" Eingangstyp

## Technische Besonderheiten

✔ **Typsichere Subtraktion** (ANY_MAGNITUDE-Unterstützung)
✔ **Automatische Typkonvertierung**
✔ **Unterlaufschutz**
✔ **Deterministische Ausführung**

## Anwendungsszenarien

- **Prozessregelung**: Regelabweichungsberechnung
- **Datenanalyse**: Differenzbildung von Messwerten
- **Maschinensteuerung**: Positionsdifferenzen
- **Zeitsteuerung**: Zeitintervallberechnungen

## Fehlerbehandlung

- **Unterlaufbehandlung**:
  - Wrap-around bei Ganzzahlen
  - -INF bei Fließkommaunterlauf

- **Typinkompatibilität**:
  - OUT = 0
  - Keine Exception-Generierung

## ⚖️ Vergleich mit ähnlichen Bausteinen

| Feature        | F_SUB  | F_ADD  | F_MUL  |
|---------------|--------|--------|--------|
| Operation     | Subtraktion | Addition | Multiplikation |
| Eingänge      | 2      | 2      | 2      |
| Typunterstützung | ANY_MAGNITUDE | ANY_NUM | ANY_NUM |






## 🛠️ Zugehörige Übungen

* [Uebung_040](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_040.md)
* [Uebung_040_2](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_040_2.md)
* [Uebung_040_AX](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_040_AX.md)
* [Uebung_041](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_041.md)
* [Uebung_072c](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_072c.md)

## Fazit

Der F_SUB-Baustein bietet eine robuste Lösung für Subtraktionsoperationen:

- Präzise typerhaltende Berechnungen
- Flexible Eingabekombinationen
- Standardkonforme Implementierung

Besonders wertvoll für Anwendungen, die Differenzberechnungen oder relative Änderungen implementieren müssen. Die automatische Typkonvertierung macht ihn zu einem unverzichtbaren Werkzeug in industriellen Steuerungssystemen.