# E_CTUD

![E_CTUD Diagram](https://user-images.githubusercontent.com/113907528/204895474-3f88876a-7ce5-406e-8f44-765c1b97226c.png)

* * * * * * * * * *

## Einleitung
Der **E_CTUD** (Event-Driven Up-Down Counter) ist ein zentraler Funktionsbaustein der IEC 61499 Norm für industrielle Steuerungssysteme. Als bidirektionaler Zähler ermöglicht er sowohl Aufwärts- als auch Abwärtszählungen und bietet damit vielfältige Einsatzmöglichkeiten in Automatisierungslösungen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `CU` (Count Up): Erhöht den Zählerstand
- `CD` (Count Down): Verringert den Zählerstand
- `R` (Reset): Setzt den Zähler zurück
- `LD` (Load): Lädt einen vordefinierten Wert

### **Ereignis-Ausgänge**
- `CO` (Count Output): Signalisiert Zähleraktivität
- `RO` (Reset Output): Bestätigt Reset-Vorgang

### **Daten-Ein-/Ausgänge**
| Port | Typ | Beschreibung |
|------|-----|-------------|
| PV   | INT | Preset Value (Vorgabewert) |
| CV   | INT | Current Value (aktueller Zählerstand) |
| QU   | BOOL | True wenn CV ≥ PV |
| QD   | BOOL | True wenn CV ≤ 0 |

## Funktionsweise

1. **Zähloperationen**
   - `CU`-Ereignis: Inkrementiert CV um 1
   - `CD`-Ereignis: Dekrementiert CV um 1

2. **Steuerfunktionen**
   - `R`-Ereignis: Setzt CV auf 0 (löst RO aus)
   - `LD`-Ereignis: Lädt PV in CV

3. **Statusüberwachung**
   - QU wird aktiv bei CV ≥ PV
   - QD wird aktiv bei CV ≤ 0

## Technische Besonderheiten

✔ **Bidirektionale Zählung** (Auf- und Abwärts)
✔ **Flexible Wertvorgabe** via PV
✔ **Echtzeit-Statusüberwachung** (QU/QD)
✔ **Ereignisgesteuerte Architektur**

## Anwendungsszenarien

- **Produktionszählung**: Teilezählung in beiden Richtungen
- **Lagerverwaltung**: Ein- und Ausgangskontrolle
- **Prozesssteuerung**: Zyklische Operationen

## Vergleich mit ähnlichen Bausteinen

| Feature | E_CTUD | E_CTU | E_CTD |
|---------|--------|-------|-------|
| Richtung | Auf/Ab | Auf | Ab |
| Reset | R | R | - |
| Load | LD | - | LD |
| Status | QU/QD | Q | Q |

## Fazit

Der E_CTUD-Baustein stellt eine leistungsfähige Zähllösung für industrielle Steuerungen dar, die durch seine bidirektionale Funktionalität und flexible Steuerbarkeit besticht. Besondere Stärken sind:

- Komplette Ereignissteuerung
- Sofortige Statusrückmeldung
- Einfache Integration in IEC 61499-Systeme

Durch die Kombination aus Zählfunktion und Statusüberwachung eignet er sich ideal für komplexe Steuerungsaufgaben in automatisierten Produktionsumgebungen. Die strikte Einhaltung der IEC 61499-Standards gewährleistet zudem problemlose Interoperabilität mit anderen Funktionsbausteinen.