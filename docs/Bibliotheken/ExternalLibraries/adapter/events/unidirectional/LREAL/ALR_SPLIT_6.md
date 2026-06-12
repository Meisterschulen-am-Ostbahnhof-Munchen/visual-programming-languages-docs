# ALR_SPLIT_6


![ALR_SPLIT_6](./ALR_SPLIT_6.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock ALR_SPLIT_6 ist ein generischer 1:6-Splitter für den Adaptertyp `adapter::types::unidirectional::ALR`. Er verteilt ein eingehendes ALR-Signal unverändert auf sechs Ausgänge und dient als passiver Signalverteiler ohne Datenmanipulation.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine

### **Ereignis-Ausgänge**
Keine

### **Daten-Eingänge**
Keine

### **Daten-Ausgänge**
Keine

### **Adapter**
| Name | Typ | Richtung | Beschreibung |
|------|-----|----------|--------------|
| IN | `adapter::types::unidirectional::ALR` | Socket (Eingang) | ALR-Eingangssignal, das auf alle Ausgänge kopiert wird |
| OUT1 | `adapter::types::unidirectional::ALR` | Plug (Ausgang) | Erster ALR-Ausgang |
| OUT2 | `adapter::types::unidirectional::ALR` | Plug (Ausgang) | Zweiter ALR-Ausgang |
| OUT3 | `adapter::types::unidirectional::ALR` | Plug (Ausgang) | Dritter ALR-Ausgang |
| OUT4 | `adapter::types::unidirectional::ALR` | Plug (Ausgang) | Vierter ALR-Ausgang |
| OUT5 | `adapter::types::unidirectional::ALR` | Plug (Ausgang) | Fünfter ALR-Ausgang |
| OUT6 | `adapter::types::unidirectional::ALR` | Plug (Ausgang) | Sechster ALR-Ausgang |

## Funktionsweise
Der Baustein leitet das am Socket IN anliegende Adaptersignal unverändert auf alle sechs Plugs OUT1–OUT6 weiter. Es findet keine Transformation, Verzögerung oder Auswahl statt – alle Ausgänge erhalten stets die identische Signalkopie. Der FB ist als generischer Baustein (`GEN_ALR_SPLIT`) deklariert und kann durch die Angabe des konkreten Adaptertyps typisiert werden.

## Technische Besonderheiten
- Rein passiver Splitter ohne Ereignisse, Datenports oder Zustandsautomat.
- Generische Implementierung über die Metadaten `eclipse4diac::core::GenericClassName = 'GEN_ALR_SPLIT'`.
- Alle Adapter-Schnittstellen sind unidirektional; es existieren keine Rückkanäle.
- Keine Laufzeitabhängigkeiten oder Initialisierung erforderlich.

## Zustandsübersicht
Der Baustein besitzt keinen ECC (Execution Control Chart) und keine internen Zustände. Er arbeitet kontinuierlich und gibt jedes eingehende Adaptersignal sofort an alle Ausgänge weiter.

## Anwendungsszenarien
- Vervielfältigung eines ALR-Signals für parallele Verbraucher in Steuerungsnetzwerken.
- Signalverteilung in landwirtschaftlichen Automatisierungssystemen (basierend auf dem ALR-Adapterkontext).
- Einfache Bereitstellung einer identischen Referenz für mehrere nachfolgende Logikbausteine.

## Vergleich mit ähnlichen Bausteinen
- **ALR_SPLIT_2 / ALR_SPLIT_3 / …** – gleiche Funktionsweise, aber mit weniger Ausgängen.
- **Ereignisbasierte Splitter (z. B. E_SPLIT)** – arbeiten mit Ereignis-/Datenseparierung, während ALR_SPLIT_6 ausschließlich Adapter nutzt.
- **Daten-Multiplexer** – wählen einen Ausgang aus; ALR_SPLIT_6 aktiviert immer alle Ausgänge.

## Fazit
ALR_SPLIT_6 ist ein minimalistischer und zuverlässiger Baustein zur Signalvervielfachung auf Adapterebene. Die generische Auslegung erleichtert die Wiederverwendung in verschiedenen Projekten, und der Verzicht auf komplexe Logik hält das Datenflussmodell klar und einfach.