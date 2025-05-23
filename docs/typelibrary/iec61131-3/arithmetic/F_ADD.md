# F_ADD

![Additionsbaustein](https://github.com/user-attachments/assets/3173760a-3b67-48dc-b078-43bcfc56423a)

* * * * * * * * * *

## Einführung
Der **F_ADD** ist ein standardkonformer arithmetischer Funktionsbaustein nach IEC 61131-3, entwickelt von der TU Wien ACIN unter EPL-2.0 Lizenz. Version 1.0 ermöglicht eine typsichere Addition von Werten (ANY_MAGNITUDE) für industrielle Steuerungsanwendungen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Berechnungsanforderung (mit Eingabewerten)

### **Ereignis-Ausgänge**
- `CNF`: Berechnungsbestätigung (mit Ergebnis)

### **Daten-Eingänge**
- `IN1` (ANY_MAGNITUDE): Erster Operand
- `IN2` (ANY_MAGNITUDE): Zweiter Operand

### **Daten-Ausgänge**
- `OUT` (ANY_MAGNITUDE): Summe von IN1 und IN2

## Funktionsweise

1. **Aktivierung**:
   - Durch `REQ`-Ereignis ausgelöst
   - Verarbeitet beide Eingabewerte gleichzeitig

2. **Typenbehandlung**:
   - Unterstützt alle ANY_MAGNITUDE-Typen:
     - Numerische Typen (INT, DINT, REAL, LREAL)
     - Zeittypen (TIME, LTIME)
   - Automatische Typkonvertierung

3. **Berechnung**:
   - Führt IN1 + IN2 aus
   - Behält höchste Eingabegenauigkeit bei

4. **Ergebnisausgabe**:
   - `CNF`-Ereignis mit Berechnungsergebnis
   - Latenz: Ein Ausführungszyklus

## Technische Spezifikationen

✔ **Generische Typunterstützung** (ANY_MAGNITUDE)  
✔ **Deterministische Ausführung**  
✔ **Überlaufschutz**  
✔ **IEC 61131-3 konform**  

## Unterstützte Datentypen

| Kategorie       | Beispiele                |
|-----------------|--------------------------|
| Ganzzahlen      | INT, DINT, UINT, UDINT   |
| Fließkomma      | REAL, LREAL              |
| Zeit            | TIME, LTIME              |
| Gemischt        | INT + REAL → REAL        |

## Anwendungsbeispiele

- **Prozessregelung**: Signalaufbereitung
- **Messsysteme**: Sensorwertaggregation
- **Bewegungssteuerung**: Positionsberechnungen
- **Energiemanagement**: Verbrauchssummierung

## Vergleich mit ähnlichen Bausteinen

| Merkmal       | F_ADD   | F_SUB   | F_MUL   |
|--------------|---------|---------|---------|
| Operation    | Addition| Subtraktion| Multiplikation|
| Eingangstypen| ANY_MAGNITUDE | ANY_MAGNITUDE | ANY_NUM |
| Ausgangstyp  | Entspricht Eingangstyp | Gleich | Gleich |

## Fehlerbehandlung

- **Überlauf**: Wrap-around bei Ganzzahlen, ±INF bei Fließkomma
- **Typenkonflikt**: Automatische Typanpassung
- **Ungültige Eingaben**: Gibt 0/Standardwert zurück

## Besondere Hinweise

- Für Zeitberechnungen: TIME + TIME → TIME
- Gemischte Operationen verwenden "höheren" Typ
- Keine implizite Skalierung (z.B. 100ms + 1s = 1100ms)

## Fazit

Der F_ADD-Baustein bietet wesentliche Rechenfunktionen:

- Robuste typsichere Addition
- Konsistentes Verhalten über alle Datentypen
- Nahtlose Integration in Steuerungsalgorithmen

Die standardisierte Implementierung macht ihn zu einer zuverlässigen Komponente für Industrieautomatisierungssysteme, die präzise Rechenoperationen mit verschiedenen Datentypen erfordern.
