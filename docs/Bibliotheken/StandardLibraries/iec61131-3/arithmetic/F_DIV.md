# F_DIV

```{index} single: F_DIV
```

![F_DIV](https://user-images.githubusercontent.com/116869307/214143200-dff8deec-3ba6-4ac9-aad3-6418b42506c1.png)

* * * * * * * * * *

## Einleitung
Der **F_DIV** ist ein standardkonformer Funktionsbaustein zur Division numerischer Werte, entwickelt unter EPL-2.0 Lizenz. Version 1.0 ermöglicht die typsichere Division verschiedener numerischer Datentypen gemäß IEC 61131-3 Standard.

![F_DIV](F_DIV.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Berechnungsanforderung (mit Dividend und Divisor)

### **Ereignis-Ausgänge**
- `CNF`: Berechnungsbestätigung (mit Divisionsergebnis)

### **Daten-Eingänge**
- `IN1` (ANY_NUM): Dividend (Zähler)
- `IN2` (ANY_NUM): Divisor (Nenner)

### **Daten-Ausgänge**
- `OUT` (ANY_NUM): Ergebnis der Division (IN1 / IN2)

## Funktionsprinzip

1. **Berechnungsauslösung**:
   - `REQ`-Ereignis mit Werten für IN1 und IN2
   - Beide Eingänge müssen vom Typ ANY_NUM sein

2. **Division**:
   - Typenerhaltende Berechnung (IN1 / IN2)
   - Unterstützte Typen:
     - Ganzzahlen (INT, DINT)
     - Fließkommazahlen (REAL, LREAL)
     - Gemischte Typen (automatische Konvertierung)

3. **Ergebnisausgabe**:
   - `CNF`-Ereignis mit berechnetem OUT-Wert
   - Fließkommaergebnis bei Ganzzahldivision

## Technische Besonderheiten

✔ **Typsichere Division** (ANY_NUM-Unterstützung)
✔ **Automatische Typkonvertierung**
✔ **IEC 61131-3 konform**
✔ **Deterministische Ausführung**

## Fehlerbehandlung

- **Division durch Null**:
  - OUT = 0 (für Ganzzahlen)
  - OUT = INF/NAN (für Fließkommazahlen)
  - Kein Abbruch der Ausführung

- **Typinkompatibilität**:
  - OUT = 0
  - Keine Exception-Generierung

## Anwendungsszenarien

- **Prozessregelung**: Regelabweichungsberechnung
- **Datenanalyse**: Normalisierung von Messwerten
- **Maschinensteuerung**: Geschwindigkeitsberechnungen
- **Energiemanagement**: Wirkungsgradberechnungen

## ⚖️ Vergleich mit ähnlichen Bausteinen

| Feature        | F_DIV  | F_MUL  | F_ADD  |
|---------------|--------|--------|--------|
| Operation     | Division | Multiplikation | Addition |
| Eingänge      | 2      | 2      | 2      |
| Typunterstützung | ANY_NUM | ANY_NUM | ANY_NUM |

## Unterstützte Datentypen

| Kategorie      | Beispiele               |
|----------------|-------------------------|
| Ganzzahlen     | INT, DINT, UDINT       |
| Fließkomma     | REAL, LREAL            |
| Typkombination | INT/REAL, DINT/LREAL   |






## 🛠️ Zugehörige Übungen

* [Uebung_111](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_111.md)

## Fazit

Der F_DIV-Baustein bietet eine robuste Lösung für Divisionsoperationen:

- Typsichere Berechnung
- Flexible Eingangskombinationen
- Standardkonforme Implementierung

Besonders wertvoll für Anwendungen, die präzise Berechnungen mit variablen Eingangsgrößen erfordern. Die automatische Typkonvertierung und Fehlerbehandlung machen ihn zu einem zuverlässigen Baustein in industriellen Steuerungssystemen.