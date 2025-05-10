# E_DEMUX

![E_DEMUX Diagram](https://user-images.githubusercontent.com/113907528/204897696-f71c191f-099b-40f9-b861-6e94bb89c3ff.png)

* * * * * * * * * *

## Einleitung
Der **E_DEMUX** (Event Demultiplexer) ist ein wichtiger Funktionsbaustein in der IEC 61499 Norm, der eingehende Ereignisse basierend auf Steuersignalen auf verschiedene Ausgangskanäle verteilt. Dieser Baustein ermöglicht die flexible Verzweigung von Ereignissen in komplexen Steuerungssystemen.

## Struktur des E_DEMUX-Bausteins

### Schnittstelle (Interface)

**Ereignis-Eingänge:**
- `EI` (Event Input): Haupt-Ereigniseingang
- `K` (Control Input): Steuereingang für Kanalauswahl

**Ereignis-Ausgänge:**
- `EO0...EOn`: Mehrere Ereignisausgänge (Anzahl abhängig von der Implementierung)

## Funktionsweise

1. **Ereignisverteilung:**
   - Bei Eingang eines Ereignisses an `EI` wird dieses an einen der Ausgänge weitergeleitet
   - Die Auswahl des Ausgangs erfolgt basierend auf dem Wert von `K`

2. **Kanalsteuerung:**
   - Der Steuereingang `K` bestimmt, welcher Ausgang aktiviert wird
   - Typischerweise erfolgt die Auswahl über einen Integer-Wert (0 für EO0, 1 für EO1, etc.)

3. **Exklusive Weiterleitung:**
   - Das Eingangsereignis wird immer nur an genau einen Ausgang weitergeleitet
   - Alle anderen Ausgänge bleiben inaktiv

## Technische Besonderheiten

✔ **Flexible Ereignisverteilung** mit konfigurierbarer Ausgangszahl  
✔ **Echtzeitfähige** Signalverarbeitung  
✔ **Deterministisches Verhalten** für zuverlässige Steuerungen  
✔ **Einfache Integration** in bestehende IEC 61499-Applikationen  

## Anwendungsszenarien

- **Verteilte Steuerungen**: Routing von Ereignissen zu verschiedenen Subsystemen
- **Zustandsmaschinen**: Auswahl von Zustandsübergängen
- **Prozesssteuerung**: Verteilen von Kommandos an verschiedene Aktoren
- **Fehlermanagement**: Weiterleitung von Fehlermeldungen an spezifische Handler

## Vergleich mit ähnlichen Bausteinen

| Feature        | E_DEMUX | E_MUX | E_SWITCH |
|---------------|---------|-------|----------|
| Funktionsprinzip | 1:n Verteilung | n:1 Zusammenführung | Bedingte Weiterleitung |
| Steuerung | Durch K-Wert | Durch K-Wert | Durch Bedingung |
| Ereignisfluss | Aufteilung | Zusammenführung | Bedingte Weiterleitung |

## Fazit

Der E_DEMUX-Baustein ist ein wesentliches Element für die Ereignisverwaltung in IEC 61499-Systemen. Seine Hauptvorteile sind:

- Effiziente Verteilung von Steuerereignissen
- Flexible Konfiguration der Ausgangskanäle
- Zuverlässige Integration in verteilte Architekturen

Durch seine klare Funktionsweise und Standardkonformität eignet er sich ideal für komplexe Automatisierungsanwendungen, die eine dynamische Ereignisverteilung erfordern. Die deterministische Arbeitsweise macht ihn besonders wertvoll für Echtzeit-Steuerungen.