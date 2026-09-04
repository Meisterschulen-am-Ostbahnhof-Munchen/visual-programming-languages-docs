# ASRT_SRT_TO_3EVENTS

* * * * * * * * * *

## Einleitung

Der Funktionsblock ASRT_SRT_TO_3EVENTS ist ein Composite-Funktionsblock, der zur Konvertierung eines ASRT-Signals in drei separate Ereignisse dient. Er ermöglicht die Umwandlung eines unidirektionalen Adapter-Signals in unabhängige SET-, RESET- und TOGGLE-Ereignisse und ist die um TOGGLE erweiterte Variante von [ASR_SR_TO_2EVENTS](ASR_SR_TO_2EVENTS.md).

![ASRT_SRT_TO_3EVENTS](ASRT_SRT_TO_3EVENTS.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine direkten Ereigniseingänge vorhanden.

### **Ereignis-Ausgänge**

- **SET**: Setzen / Einschalten
- **RESET**: Rücksetzen / Ausschalten
- **TOGGLE**: Umkehren des Ausgangssignals

### **Daten-Eingänge**

Keine Dateneingänge vorhanden.

### **Daten-Ausgänge**

Keine Datenausgänge vorhanden.

### **Adapter**

- **ASRT_IN**: Adapter-Eingang vom Typ `adapter::types::unidirectional::ASRT`

## Funktionsweise

Der Funktionsblock leitet die SET-, RESET- und TOGGLE-Signale des ASRT-Adapters direkt an die entsprechenden Ereignisausgänge weiter. Dabei werden die eingehenden Adapterereignisse transparent an die Ausgänge des Funktionsblocks durchgeschleift.

## Technische Besonderheiten

- Composite-Funktionsblock ohne interne Logikverarbeitung
- Direkte Verbindung zwischen Adapterereignissen und Ausgangsereignissen
- Keine Datenverarbeitung oder Zustandsverwaltung

## Zustandsübersicht

Der Funktionsblock besitzt keinen internen Zustand und arbeitet stateless. Jedes eingehende Adapterereignis wird sofort an den entsprechenden Ausgang weitergeleitet.

## Anwendungsszenarien

- Integration von ASRT-Adaptern in Ereignis-basierte Steuerungen
- Umwandlung unidirektionaler Adapter-Signale in unabhängige Einzelereignisse
- Schnittstellenanpassung zwischen verschiedenen Kommunikationsprotokollen

## ⚖️ Vergleich mit ähnlichen Bausteinen

Im Vergleich zu [ASR_SR_TO_2EVENTS](ASR_SR_TO_2EVENTS.md) verarbeitet dieser Composite-Funktionsblock zusätzlich das TOGGLE-Signal eines ASRT- statt eines ASR-Adapters.

## Fazit

Der ASRT_SRT_TO_3EVENTS Funktionsblock stellt eine einfache und effiziente Lösung zur Konvertierung von ASRT-Adaptersignalen in separate SET-, RESET- und TOGGLE-Ereignisse dar. Seine schlanke Implementierung ohne interne Logik macht ihn zu einer zuverlässigen und performanten Komponente für Schnittstellenanpassungen.
