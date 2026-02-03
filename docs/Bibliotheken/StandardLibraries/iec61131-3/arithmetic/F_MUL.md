# F_MUL

```{index} single: F_MUL
```

![F_MUL](https://user-images.githubusercontent.com/116869307/214143289-3262368c-fae6-4fc7-bd1d-b2b445c245c9.png)

* * * * * * * * * *

![F_MUL](F_MUL.svg)


## Einführung
Der **F_MUL** ist ein standardkonformer Funktionsbaustein zur Multiplikation numerischer Werte, entwickelt unter EPL-2.0 Lizenz. Version 1.0 ermöglicht die typsichere Multiplikation verschiedener numerischer Datentypen gemäß IEC 61131-3 Standard.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Berechnungsanforderung (mit zwei Faktoren)

### **Ereignis-Ausgänge**
- `CNF`: Berechnungsbestätigung (mit Ergebnis)

### **Daten-Eingänge**
- `IN1` (ANY_NUM): Erster Faktor
- `IN2` (ANY_NUM): Zweiter Faktor

### **Daten-Ausgänge**
- `OUT` (ANY_NUM): Produkt der Multiplikation (IN1 × IN2)

## Funktionsprinzip

1. **Berechnungsauslösung**:
   - `REQ`-Ereignis mit Werten für IN1 und IN2
   - Beide Eingänge müssen vom Typ ANY_NUM sein

2. **Multiplikation**:
   - Typenerhaltende Berechnung (IN1 × IN2)
   - Unterstützte Typen:
     - Ganzzahlen (INT, DINT)
     - Fließkommazahlen (REAL, LREAL)
     - Gemischte Typen (automatische Konvertierung)

3. **Ergebnisausgabe**:
   - `CNF`-Ereignis mit berechnetem Produkt
   - Ergebnis im "größten" Eingangstyp

## Technische Besonderheiten

✔ **Typsichere Multiplikation** (ANY_NUM-Unterstützung)
✔ **Automatische Typkonvertierung**
✔ **Überlaufschutz**
✔ **Deterministische Ausführung**

## Anwendungsszenarien

- **Prozessregelung**: Skalierungsberechnungen
- **Datenanalyse**: Messwertverarbeitung
- **Maschinensteuerung**: Positionsberechnungen
- **Energiemanagement**: Leistungsberechnungen

## Fehlerbehandlung

- **Überlaufbehandlung**:
  - Wrap-around bei Ganzzahlen
  - ±INF (± unendlich) bei Fließkommaüberlauf

- **Typinkompatibilität**:
  - OUT = 0
  - Keine Exception-Generierung

## Vergleich mit ähnlichen Bausteinen

| Feature        | F_MUL  | F_ADD  | F_DIV  |
|---------------|--------|--------|--------|
| Operation     | Multiplikation | Addition | Division |
| Eingänge      | 2      | 2      | 2      |
| Typunterstützung | ANY_NUM | ANY_NUM | ANY_NUM |






## Zugehörige Übungen

* [Uebung_034b](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_034b.md)

## Fazit

Der F_MUL-Baustein bietet eine robuste Lösung für Multiplikationsoperationen:

- Präzise typerhaltende Berechnungen
- Flexible Eingabekombinationen
- Standardkonforme Implementierung

Besonders wertvoll für Anwendungen, die skalierte Berechnungen oder physikalische Formeln implementieren müssen. Die automatische Typkonvertierung macht ihn zu einem vielseitigen Werkzeug in industriellen Steuerungssystemen.