# F_TRUNC

```{index} single: F_TRUNC
```

![F_TRUNC](https://github.com/user-attachments/assets/b944edcb-c90b-41d8-98e6-3c3b81e50e9f)

* * * * * * * * * *

![F_TRUNC](F_TRUNC.svg)


## Einführung
Der **F_TRUNC** ist ein standardkonformer Funktionsbaustein zur Abrundung von Fließkommazahlen in Richtung Null (truncation toward zero), entwickelt unter EPL-2.0 Lizenz. Version 1.0 ermöglicht die typsichere Konvertierung gemäß IEC 61131-3 Standard.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Berechnungsanforderung (mit Eingabewert)

### **Ereignis-Ausgänge**
- `CNF`: Berechnungsbestätigung (mit abgerundetem Wert)

### **Daten-Eingänge**
- `IN` (ANY_REAL): Eingabewert (Fließkommazahl)

### **Daten-Ausgänge**
- `OUT` (ANY_INT): Abgerundeter Ganzzahlwert

## Funktionsprinzip

1. **Berechnungsauslösung**:
   - `REQ`-Ereignis mit einem ANY_REAL-Wert
   - Unterstützte Typen: REAL, LREAL

2. **Trunkierungsoperation**:
   - Entfernt Nachkommastellen ohne Rundung
   - Beispiel: 3.9 → 3, -2.7 → -2
   - Keine mathematische Rundung (≠ F_ROUND)

3. **Ergebnisausgabe**:
   - `CNF`-Ereignis mit ganzzahligem Ergebnis
   - Automatische Typanpassung (INT, DINT, etc.)

## Technische Besonderheiten

✔ **Verlustfreie Typkonvertierung**
✔ **Konsistente Null-Richtung** (truncation toward zero)
✔ **Deterministische Ausführung**
✔ **Keine Überlaufausnahmen**

## Anwendungsszenarien

- **Datenvorverarbeitung**: Indexberechnungen
- **Messwertverarbeitung**: Diskretisierung
- **Steuerungslogik**: Ganzzahlige Positionsberechnungen
- **Finanzberechnungen**: Währungsumrechnungen

## Fehlerbehandlung

- **Wertebereichsüberschreitung**:
  - Bei zu großen Werten: Begrenzung auf Zieltyp-Maximum
  - Keine Exception-Generierung

- **Sonderfälle**:
  - NaN → 0
  ±INF → Maximalwert des Zieltyps

## ⚖️ Vergleich mit ähnlichen Bausteinen

| Feature        | F_TRUNC  | F_ROUND  | F_FLOOR  |
|---------------|----------|----------|----------|
| Operation     | Richtung Null | Mathematisch | Abrunden |
| Beispiel      | 3.9 → 3  | 3.9 → 4  | 3.9 → 3  |
| Beispiel    | -2.7 → -2 | -2.7 → -3 | -2.7 → -3 |

## Fazit

Der F_TRUNC-Baustein bietet eine präzise Lösung für die Ganzzahlkonvertierung:

- Vorhersagbares Verhalten (truncation toward zero)
- Typsichere Fließkomma-zu-Ganzzahl Konvertierung
- Robuste Behandlung von Extremwerten

Unverzichtbar für alle Anwendungen mit exakten Bereichsgrenzen und Indexberechnungen.