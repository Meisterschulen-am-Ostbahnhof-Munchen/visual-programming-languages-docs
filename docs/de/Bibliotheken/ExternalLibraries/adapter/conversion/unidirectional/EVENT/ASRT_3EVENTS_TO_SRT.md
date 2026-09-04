# ASRT_3EVENTS_TO_SRT

* * * * * * * * * *

## Einleitung

Der Funktionsblock ASRT_3EVENTS_TO_SRT ist ein Composite-Funktionsblock, der drei separate Ereignisse (Set/Reset/Toggle) in ein ASRT-Signal umwandelt. Er dient als Brücke zwischen ereignisbasierten Steuerungssignalen und dem ASRT-Adapterformat und ist die um TOGGLE erweiterte Variante von [ASR_2EVENTS_TO_SR](ASR_2EVENTS_TO_SR.md).

![ASRT_3EVENTS_TO_SRT](ASRT_3EVENTS_TO_SRT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **SET**: Setzt das Ausgangssignal (Einschalten)
- **RESET**: Rücksetzt das Ausgangssignal (Ausschalten)
- **TOGGLE**: Kehrt das Ausgangssignal um

### **Ereignis-Ausgänge**

Keine direkten Ereignis-Ausgänge vorhanden

### **Daten-Eingänge**

Keine Daten-Eingänge vorhanden

### **Daten-Ausgänge**

Keine Daten-Ausgänge vorhanden

### **Adapter**

- **ASRT_OUT**: Unidirektionaler ASRT-Adapter-Ausgang

## Funktionsweise

Der Funktionsblock leitet die eingehenden SET-, RESET- und TOGGLE-Ereignisse direkt an den ASRT-Adapter weiter. Bei einem SET-Ereignis wird das entsprechende SET-Signal am ASRT-Adapter aktiviert, bei RESET das RESET-Signal und bei TOGGLE das TOGGLE-Signal.

## Technische Besonderheiten

- Composite-Funktionsblock ohne interne Logikverarbeitung
- Direkte Durchleitung der Ereignisse an den Adapter
- Verwendet unidirektionale ASRT-Adapter-Technologie

## Zustandsübersicht

Der Funktionsblock besitzt keinen internen Zustand. Er fungiert als reiner Signalweiterleiter zwischen den Ereigniseingängen und dem ASRT-Adapter.

## Anwendungsszenarien

- Integration von ereignisbasierten Steuerungssystemen in ASRT-kompatible Umgebungen
- Verbindung zwischen verschiedenen Steuerungsebenen
- Protokollumsetzung in Automatisierungssystemen

## ⚖️ Vergleich mit ähnlichen Bausteinen

Im Vergleich zu [ASR_2EVENTS_TO_SR](ASR_2EVENTS_TO_SR.md) bietet ASRT_3EVENTS_TO_SRT zusätzlich das TOGGLE-Ereignis und speist damit einen ASRT- statt einen ASR-Adapter.

## Fazit

ASRT_3EVENTS_TO_SRT ist ein spezialisierter Funktionsblock für die Konvertierung von drei separaten Ereignissen (Set/Reset/Toggle) in das ASRT-Adapterformat. Seine einfache und direkte Funktionsweise macht ihn zu einer zuverlässigen Lösung für Systemintegrationen.
