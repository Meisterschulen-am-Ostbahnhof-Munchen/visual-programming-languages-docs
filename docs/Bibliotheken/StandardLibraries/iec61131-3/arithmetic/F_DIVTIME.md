# F_DIVTIME

```{index} single: F_DIVTIME
```

![F_DIVTIME](https://github.com/user-attachments/assets/c442ada4-119c-4919-be55-9c5e0d7acb7c)

* * * * * * * * * *

![F_DIVTIME](F_DIVTIME.svg)


## Einführung
Der **F_DIVTIME** ist ein spezialisierter Funktionsbaustein zur Division von Zeitwerten durch numerische Faktoren, entwickelt unter EPL-2.0 Lizenz. Version 1.0 ermöglicht präzise Zeitberechnungen mit TIME- und ANY_NUM-Datentypen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Berechnungsanforderung (mit Eingabewerten)

### **Ereignis-Ausgänge**
- `CNF`: Berechnungsbestätigung (mit Ergebnis)

### **Daten-Eingänge**
- `IN1` (TIME): Zu dividierende Zeitdauer
- `IN2` (ANY_NUM): Divisor (numerischer Wert)

### **Daten-Ausgänge**
- `OUT` (TIME): Ergebnis der Division (IN1 / IN2)

## Funktionsweise

1. **Aktivierung**:
   - Durch `REQ`-Ereignis ausgelöst
   - Verarbeitet TIME-Werte und numerische Divisoren

2. **Berechnung**:
   - Dividiert Zeitwert (IN1) durch numerischen Wert (IN2)
   - Führt automatische Typkonvertierung durch
   - Millisekundengenaue Berechnung

3. **Ergebnisausgabe**:
   - `CNF`-Ereignis mit neuem TIME-Wert
   - Format: T#1d5h30m15s250ms

## Technische Spezifikationen

✔ **Präzise Zeitdivision**
✔ **Unterstützung für ANY_NUM-Divisoren**
✔ **Millisekundengenaue Berechnung**
✔ **Automatische Typkonvertierung**

## Anwendungsbeispiele

- **Prozessoptimierung**: Mittlere Zykluszeitberechnung
- **Produktionsplanung**: Zeitaufteilung auf Stationen
- **Robotersteuerung**: Geschwindigkeitsanpassung
- **Energiemanagement**: Verbrauchszeitberechnungen

## Fehlerbehandlung

- **Division durch Null**:
  - OUT = T#0s
  - Kein Abbruch der Ausführung

- **Typinkompatibilität**:
  - OUT = IN1 (Originalwert bleibt erhalten)
  - Keine Exception-Generierung

## Besondere Hinweise

- **Berechnungsgenauigkeit**:
  - Minimum 1 Millisekunde
  - Rundung zur nächsten Millisekunde

- **Gültigkeitsbereich**:
  - Positive Zeitwerte (T#0s bis T#106751d23h47m16s854ms)
  - Divisor muss positiv sein

## Vergleich mit Standard-F_DIV

| Merkmal        | F_DIVTIME | F_DIV       |
|----------------|-----------|-------------|
| Eingangstyp 1  | TIME      | ANY_NUM     |
| Eingangstyp 2  | ANY_NUM   | ANY_NUM     |
| Ausgangstyp    | TIME      | ANY_NUM     |

## Fazit

Der F_DIVTIME-Baustein bietet essentielle Funktionen für zeitbasierte Berechnungen:

- Präzise Division von Zeitwerten
- Flexible Eingabeparameter
- Zuverlässige Fehlerbehandlung

Besonders wertvoll für Anwendungen, die eine Aufteilung von Zeitintervallen erfordern. Die spezialisierte Implementierung garantiert korrekte Ergebnisse für alle gültigen Eingabekombinationen.