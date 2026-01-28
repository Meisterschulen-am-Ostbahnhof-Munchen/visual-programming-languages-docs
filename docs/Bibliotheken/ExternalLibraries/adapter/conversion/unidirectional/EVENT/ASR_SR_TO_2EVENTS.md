# ASR_SR_TO_2EVENTS

```{index} single: ASR_SR_TO_2EVENTS
```

<img width="1211" height="249" alt="image" src="https://github.com/user-attachments/assets/ebdb5839-2d56-43bd-9764-c85bd6cdd888" />

* * * * * * * * * *

## Einleitung
Der Funktionsblock ASR_SR_TO_2EVENTS ist ein Composite-Funktionsblock, der zur Konvertierung eines ASR-Signals in zwei separate Ereignisse dient. Er ermöglicht die Umwandlung eines bidirektionalen Adapter-Signals in unabhängige SET- und RESET-Ereignisse.

![ASR_SR_TO_2EVENTS](ASR_SR_TO_2EVENTS.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine direkten Ereigniseingänge vorhanden.

### **Ereignis-Ausgänge**
- **SET**: Setzen / Einschalten
- **RESET**: Rücksetzen / Ausschalten

### **Daten-Eingänge**
Keine Dateneingänge vorhanden.

### **Daten-Ausgänge**
Keine Datenausgänge vorhanden.

### **Adapter**
- **ASR_IN**: Adapter-Eingang vom Typ `adapter::types::unidirectional::ASR`

## Funktionsweise
Der Funktionsblock leitet die SET- und RESET-Signale des ASR-Adapters direkt an die entsprechenden Ereignisausgänge weiter. Dabei werden die eingehenden Adapterereignisse transparent an die Ausgänge des Funktionsblocks durchgeschleift.

## Technische Besonderheiten
- Composite-Funktionsblock ohne interne Logikverarbeitung
- Direkte Verbindung zwischen Adapterereignissen und Ausgangsereignissen
- Keine Datenverarbeitung oder Zustandsverwaltung

## Zustandsübersicht
Der Funktionsblock besitzt keinen internen Zustand und arbeitet stateless. Jedes eingehende Adapterereignis wird sofort an den entsprechenden Ausgang weitergeleitet.

## Anwendungsszenarien
- Integration von ASR-Adaptern in Ereignis-basierte Steuerungen
- Umwandlung bidirektionaler Signale in unabhängige Einzelereignisse
- Schnittstellenanpassung zwischen verschiedenen Kommunikationsprotokollen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen Adapter-Blöcken bietet dieser Composite-Funktionsblock eine spezifische Konvertierung von ASR- zu Ereignissignalen, während generische Adapter eine allgemeinere Schnittstellenanpassung ermöglichen.

## Fazit
Der ASR_SR_TO_2EVENTS Funktionsblock stellt eine einfache und effiziente Lösung zur Konvertierung von ASR-Adaptersignalen in separate SET- und RESET-Ereignisse dar. Seine schlanke Implementierung ohne interne Logik macht ihn zu einer zuverlässigen und performanten Komponente für Schnittstellenanpassungen.