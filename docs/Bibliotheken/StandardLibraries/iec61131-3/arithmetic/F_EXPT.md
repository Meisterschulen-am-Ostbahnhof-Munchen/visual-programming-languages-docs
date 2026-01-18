# F_EXPT

```{index} single: F_EXPT
```

![F_EXPT](https://github.com/user-attachments/assets/0446a2d1-6283-400f-976d-18ac9c482b25)

* * * * * * * * * *

## Einführung
Der **F_EXPT** ist ein mathematischer Funktionsbaustein zur Berechnung von Potenzwerten, entwickelt unter EPL-2.0 Lizenz. Version 1.0 ermöglicht die Berechnung von Basis-Exponent-Kombinationen mit ANY_REAL-Datentypen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Berechnungsanforderung (mit Basis und Exponent)

### **Ereignis-Ausgänge**
- `CNF`: Berechnungsbestätigung (mit Ergebnis)

### **Daten-Eingänge**
- `IN1` (ANY_REAL): Basiswert
- `IN2` (ANY_REAL): Exponent

### **Daten-Ausgänge**
- `OUT` (ANY_REAL): Ergebnis der Potenzierung (IN1^IN2)

## Funktionsweise

1. **Aktivierung**:
   - Durch `REQ`-Ereignis ausgelöst
   - Verarbeitet zwei ANY_REAL-Werte

2. **Berechnung**:
   - Berechnet IN1 hoch IN2
   - Unterstützt alle REAL- und LREAL-Kombinationen
   - Automatische Typanpassung (höhere Genauigkeit)

3. **Ergebnisausgabe**:
   - `CNF`-Ereignis mit berechnetem Potenzwert
   - Ergebnis im genaueren Eingabetyp

## Technische Spezifikationen

✔ **Präzise Potenzberechnung**  
✔ **Unterstützung für REAL und LREAL**  
✔ **Automatische Typkonvertierung**  
✔ **IEC 61131-3 konform**  

## Anwendungsbeispiele

- **Physikalische Berechnungen**: Beschleunigungsformeln
- **Finanzmathematik**: Zinseszinsberechnung
- **Regelungstechnik**: Nichtlineare Kennlinien
- **Signalverarbeitung**: Exponentialfilter

## Fehlerbehandlung

- **Ungültige Eingaben**:
  - Negative Basis mit nicht-ganzzahligem Exponent: OUT = 0
  - Null hoch negativem Exponent: OUT = +INF
  - Unendlichkeitsberechnungen gemäß IEEE 754

## Besondere Hinweise

- **Genauigkeit**:
  - LREAL-Eingaben liefern LREAL-Ergebnisse
  - REAL-Eingaben liefern REAL-Ergebnisse
  - Gemischte Eingaben: LREAL-Ergebnis

- **Performance**:
  - LREAL-Berechnungen benötigen mehr Zyklen
  - Für Echtzeitanwendungen REAL bevorzugen

## Vergleich mit ähnlichen Bausteinen

| Merkmal        | F_EXPT  | F_LN    | F_POWER |
|----------------|---------|---------|---------|
| Funktion       | a^b     | ln(a)   | a^b     |
| Eingangstypen  | ANY_REAL| ANY_REAL| ANY_NUM |
| Genauigkeit    | Hoch    | Hoch    | Mittel  |

## Fazit

Der F_EXPT-Baustein bietet leistungsstarke mathematische Funktionen:

- Präzise Exponentialberechnungen
- Flexible Eingabekombinationen
- Zuverlässige Fehlerbehandlung

Unverzichtbar für fortgeschrittene Steuerungsalgorithmen, die nichtlineare Berechnungen erfordern. Die standardkonforme Implementierung ermöglicht den Einsatz in anspruchsvollen industriellen Anwendungen.
