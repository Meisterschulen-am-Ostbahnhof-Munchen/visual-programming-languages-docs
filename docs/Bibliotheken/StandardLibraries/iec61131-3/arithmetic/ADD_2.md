# ADD_2

```{index} single: ADD_2
```

![ADD_2](https://user-images.githubusercontent.com/116869307/214142966-3facb074-7909-40e0-a9c9-4588e1bfc938.png)

* * * * * * * * * *

## Einleitung
Der **ADD_2** ist ein generischer Funktionsbaustein zur Addition zweier Werte, entwickelt unter EPL-2.0 Lizenz. Die Version 1.0 unterstützt verschiedene numerische Datentypen gemäß IEC 61131-3 Standard.

![ADD_2](ADD_2.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Berechnungsanforderung (mit Eingabewerten)

### **Ereignis-Ausgänge**
- `CNF`: Berechnungsbestätigung (mit Ergebnis)

### **Daten-Eingänge**
- `IN1` (ANY_MAGNITUDE): Erster Summand
- `IN2` (ANY_MAGNITUDE): Zweiter Summand

### **Daten-Ausgänge**
- `OUT` (ANY_MAGNITUDE): Summen-Ergebnis

## Funktionsweise

1. **Berechnungsanforderung**:
   - `REQ`-Ereignis mit Werten für IN1 und IN2

2. **Addition**:
   - Typenerhaltende Berechnung (IN1 + IN2)
   - Unterstützte Typen: INT, DINT, REAL, LREAL etc.

3. **Ergebnisausgabe**:
   - `CNF`-Ereignis mit berechnetem OUT-Wert
   - Automatische Typanpassung

## Technische Besonderheiten

✔ **Generische Implementierung** (GEN_ADD)
✔ **Typflexible** Eingänge/Ausgänge
✔ **IEC 61131-3 konform**
✔ **Deterministische** Berechnung

## Unterstützte Datentypen

| Typ      | Beispiel           |
|----------|--------------------|
| INT      | 123 + 456 = 579    |
| REAL     | 1.23 + 4.56 = 5.79 |
| TIME     | T#1s + T#2s = T#3s |
| LREAL    | 1.23e10 + 4.56e10  |

## Anwendungsszenarien

- **Prozessregelung**: Signalverarbeitung
- **Datenanalyse**: Messwertaggregation
- **Maschinensteuerung**: Positionsberechnung
- **Energiemanagement**: Verbrauchssummierung

## ⚖️ Vergleich mit ähnlichen Bausteinen

| Feature        | ADD_2  | ADD_4  | MUL_2  |
|---------------|--------|--------|--------|
| Operation     | Addition | Addition | Multiplikation |
| Eingänge      | 2      | 4      | 2      |
| Typunterstützung | ANY_MAG | ANY_MAG | ANY_MAG |

## Fehlerbehandlung

- Typinkompatibilität führt zu:
  - OUT = 0 (für numerische Typen)
  - Leerer Wert (für andere Typen)
  - Keine Exception-Generierung






## 🛠️ Zugehörige Übungen

* [Uebung_000](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_000.md)
* [Uebung_000_AX](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_000_AX.md)
* [Uebung_110](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_110.md)
* [Uebung_111](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_111.md)

## Fazit

Der ADD_2-Baustein bietet eine flexible Lösung für arithmetische Operationen:

- Einfache aber mächtige Addition
- Breite Typunterstützung
- Standardkonforme Implementierung

Besonders wertvoll für Anwendungen, die typsichere Berechnungen mit variablen Eingangsgrößen erfordern. Die generische Implementierung ermöglicht Wiederverwendung in unterschiedlichsten Steuerungskontexten.