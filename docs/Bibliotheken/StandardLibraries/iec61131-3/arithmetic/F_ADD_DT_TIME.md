# F_ADD_DT_TIME

```{index} single: F_ADD_DT_TIME
```

![Zeitadditionssymbol](https://github.com/user-attachments/assets/1fda9baa-1d7c-4fa6-8c87-608436deefa8)

* * * * * * * * * *

## Einführung
Der **F_ADD_DT_TIME** ist ein spezialisierter Funktionsbaustein zur Addition von Zeitwerten zu Datums-/Zeitangaben, entwickelt unter EPL-2.0 Lizenz. Version 1.0 ermöglicht präzise Zeitberechnungen mit DATE_AND_TIME und TIME-Datentypen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Berechnungsanforderung (mit Eingabewerten)

### **Ereignis-Ausgänge**
- `CNF`: Berechnungsbestätigung (mit Ergebnis)

### **Daten-Eingänge**
- `IN1` (DATE_AND_TIME): Ausgangsdatum/-zeit
- `IN2` (TIME): Zeitdauer für Addition

### **Daten-Ausgänge**
- `OUT` (DATE_AND_TIME): Ergebnis der Addition

## Funktionsweise

1. **Aktivierung**:
   - Durch `REQ`-Ereignis ausgelöst
   - Verarbeitet DATE_AND_TIME und TIME-Werte

2. **Berechnung**:
   - Addiert Zeitdauer (IN2) zum Zeitstempel (IN1)
   - Berücksichtigt automatisch:
     - Schaltjahre
     - Monatslängen
     - Zeitzonen (falls konfiguriert)

3. **Ergebnisausgabe**:
   - `CNF`-Ereignis mit neuem DATE_AND_TIME
   - Format: DT#2023-12-31-23:59:59

## Technische Spezifikationen

✔ **Präzise Zeit-/Datumsarithmetik**  
✔ **Automatische Kalenderberechnung**  
✔ **IEC 61131-3 konform**  
✔ **Deterministische Ausführung**  

## Anwendungsbeispiele

- **Prozesssteuerung**: Fälligkeitsberechnungen
- **Produktionsplanung**: Terminverschiebungen
- **Wartungssysteme**: Wartungsintervallberechnung
- **Datenprotokollierung**: Zeitstempelkorrekturen

## Besondere Hinweise

- **Gültigkeitsbereich**: 
  - Unterstützt Datumsbereich 1970-2099
  - Zeitauflösung: 1 Millisekunde

- **Fehlerfälle**:
  - Bei Überlauf: Wrap-around im gültigen Bereich
  - Bei ungültigen Eingaben: OUT = IN1

## Vergleich mit Standard-F_ADD

| Merkmal        | F_ADD_DT_TIME | F_ADD       |
|----------------|---------------|-------------|
| Eingangstyp 1  | DATE_AND_TIME | ANY_MAGNITUDE |
| Eingangstyp 2  | TIME          | ANY_MAGNITUDE |
| Operation      | Spezialisierte Zeitaddition | Generische Addition |

## Fazit

Der F_ADD_DT_TIME-Baustein bietet essentielle Funktionen für Zeitberechnungen:

- Präzise Handhabung von Datum/Zeit-Operationen
- Automatische Kalenderkorrekturen
- Zuverlässige Integration in Steuerungssysteme

Besonders wertvoll für Anwendungen, die komplexe Zeitberechnungen mit automatischer Berücksichtigung von Kalenderregeln erfordern. Die spezialisierte Implementierung garantiert korrekte Ergebnisse für alle gültigen Eingabewerte.
