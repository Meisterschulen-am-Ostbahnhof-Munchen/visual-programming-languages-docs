# PUBLISH_7

<img width="1180" height="416" alt="image" src="https://github.com/user-attachments/assets/f4ddc744-e21c-430b-979c-1cdd0463adf6" />

* * * * * * * * * *

## Einleitung
Der PUBLISH_7 Funktionsblock dient zum Verteilen von Daten an einen oder mehrere SUBSCRIBE_7 Blöcke. Er ermöglicht die unbestätigte Übertragung von bis zu sieben verschiedenen Datenwerten über eine Publish-Subscribe-Architektur.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Initialisierungsereignis mit zugehörigen Daten QI und ID
- **REQ**: Sendeanforderung für Daten (unbestätigt) mit sieben Datenvariablen

### **Ereignis-Ausgänge**
- **INITO**: Bestätigung der Initialisierung mit QO und STATUS
- **CNF**: Bestätigung, dass Daten gesendet wurden mit QO und STATUS

### **Daten-Eingänge**
- **QI** (BOOL): Qualitätsindikator für Initialisierung
- **ID** (WSTRING): Identifikator für den Publish-Kanal
- **SD_1** bis **SD_7** (ANY): Sieben verschiedene Datenwerte beliebigen Typs

### **Daten-Ausgänge**
- **QO** (BOOL): Qualitätsindikator für Ausgangszustand
- **STATUS** (WSTRING): Statusinformationen als Unicode-String

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der PUBLISH_7 Block initialisiert sich über das INIT-Ereignis mit einem spezifischen Kanal-ID. Nach erfolgreicher Initialisierung können über das REQ-Ereignis bis zu sieben Datenwerte (SD_1 bis SD_7) gleichzeitig an alle angeschlossenen SUBSCRIBE_7 Blöcke verteilt werden. Die Datenübertragung erfolgt unbestätigt, wobei der CNF-Ausgang lediglich bestätigt, dass die Daten gesendet wurden, nicht jedoch, dass sie empfangen wurden.

## Technische Besonderheiten
- Unterstützt den ANY-Datentyp für maximale Flexibilität
- Verwendet WSTRING für ID und STATUS für internationale Zeichensatzunterstützung
- Bietet sieben unabhängige Datenkanäle
- Implementiert nach IEC 61499-2 Standard
- Verwendet GenericClassName 'GEN_PUBLISH' für generische Implementierung

## Zustandsübersicht
1. **Nicht initialisiert**: Block wartet auf INIT-Ereignis
2. **Initialisiert**: Block bereit für REQ-Ereignisse
3. **Sendebereit**: Verarbeitet REQ-Ereignisse und verteilt Daten

## Anwendungsszenarien
- Verteilung von Sensordaten an mehrere Verbraucher
- Broadcast-Kommunikation in verteilten Systemen
- Datenverteilung in Produktionsanlagen
- Messwertverteilung in Überwachungssystemen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfacheren PUBLISH-Blöcken bietet PUBLISH_7 die Möglichkeit, sieben verschiedene Datenwerte parallel zu verteilen, während einfachere Varianten typischerweise nur einen oder wenige Datenkanäle unterstützen.

## Fazit
Der PUBLISH_7 Funktionsblock ist eine leistungsstarke Lösung für Publish-Subscribe-Kommunikation in IEC 61499-Systemen, die durch ihre sieben parallelen Datenkanäle und Flexibilität bei den Datentypen besonders für komplexe Datenverteilungsaufgaben geeignet ist.
