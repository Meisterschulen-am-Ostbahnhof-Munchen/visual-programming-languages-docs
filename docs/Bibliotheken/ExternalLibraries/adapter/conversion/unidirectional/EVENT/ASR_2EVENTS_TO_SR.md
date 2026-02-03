# ASR_2EVENTS_TO_SR

```{index} single: ASR_2EVENTS_TO_SR
```

<img width="1224" height="249" alt="image" src="https://github.com/user-attachments/assets/67d010cb-b034-4855-bc18-d9a6b1015a81" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock ASR_2EVENTS_TO_SR ist ein Composite-Funktionsblock, der zwei separate Ereignisse in ein ASR-Signal (Set-Reset) umwandelt. Er dient als Brücke zwischen ereignisbasierten Steuerungssignalen und dem ASR-Adapterformat.

![ASR_2EVENTS_TO_SR](ASR_2EVENTS_TO_SR.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **SET**: Setzt das Ausgangssignal (Einschalten)
- **RESET**: Rücksetzt das Ausgangssignal (Ausschalten)

### **Ereignis-Ausgänge**
Keine direkten Ereignis-Ausgänge vorhanden

### **Daten-Eingänge**
Keine Daten-Eingänge vorhanden

### **Daten-Ausgänge**
Keine Daten-Ausgänge vorhanden

### **Adapter**
- **ASR_OUT**: Unidirektionaler ASR-Adapter-Ausgang

## Funktionsweise
Der Funktionsblock leitet die eingehenden SET- und RESET-Ereignisse direkt an den ASR-Adapter weiter. Bei einem SET-Ereignis wird das entsprechende SET-Signal am ASR-Adapter aktiviert, bei einem RESET-Ereignis das RESET-Signal.

## Technische Besonderheiten
- Composite-Funktionsblock ohne interne Logikverarbeitung
- Direkte Durchleitung der Ereignisse an den Adapter
- Verwendet unidirektionale ASR-Adapter-Technologie

## Zustandsübersicht
Der Funktionsblock besitzt keinen internen Zustand. Er fungiert als reiner Signalweiterleiter zwischen den Ereigniseingängen und dem ASR-Adapter.

## Anwendungsszenarien
- Integration von ereignisbasierten Steuerungssystemen in ASR-kompatible Umgebungen
- Verbindung zwischen verschiedenen Steuerungsebenen
- Protokollumsetzung in Automatisierungssystemen

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen Ereignis-Funktionsblöcken bietet ASR_2EVENTS_TO_SR eine spezifische Schnittstelle zum ASR-Adapter, während andere Blöcke möglicherweise direkte Datenausgänge verwenden.




## 🛠️ Zugehörige Übungen

* [Uebung_171_AX](../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_171_AX.md)

## Fazit
ASR_2EVENTS_TO_SR ist ein spezialisierter Funktionsblock für die Konvertierung von zwei separaten Ereignissen in das ASR-Adapterformat. Seine einfache und direkte Funktionsweise macht ihn zu einer zuverlässigen Lösung für Systemintegrationen.