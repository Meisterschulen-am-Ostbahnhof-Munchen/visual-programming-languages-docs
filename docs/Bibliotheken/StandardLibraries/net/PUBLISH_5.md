# PUBLISH_5

```{index} single: PUBLISH_5
```

<img width="1184" height="368" alt="image" src="https://github.com/user-attachments/assets/25597a0a-65c9-425b-8b73-46c3513d9ecc" />

* * * * * * * * * *

## Einleitung
Der PUBLISH_5 Funktionsblock dient zum Veröffentlichen von Daten an einen oder mehrere SUBSCRIBE_5 Blöcke. Er ermöglicht die Übertragung von bis zu fünf verschiedenen Datenwerten über ein Publish-Subscribe-Kommunikationsmuster.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Initialisierungsereignis mit zugehörigen Daten QI und ID
- **REQ**: Anforderungsereignis zum Senden von Daten (unbestätigt) mit zugehörigen Daten QI, SD_1 bis SD_5

### **Ereignis-Ausgänge**
- **INITO**: Bestätigung der Initialisierung mit zugehörigen Daten QO und STATUS
- **CNF**: Bestätigung, dass Daten gesendet wurden mit zugehörigen Daten QO und STATUS

### **Daten-Eingänge**
- **QI** (BOOL): Qualifizierer für Initialisierung/Operation
- **ID** (WSTRING): Identifikator für den Publish-Kanal
- **SD_1** (ANY): Erster zu sendender Datenwert
- **SD_2** (ANY): Zweiter zu sendender Datenwert
- **SD_3** (ANY): Dritter zu sendender Datenwert
- **SD_4** (ANY): Vierter zu sendender Datenwert
- **SD_5** (ANY): Fünfter zu sendender Datenwert

### **Daten-Ausgänge**
- **QO** (BOOL): Qualifizierer für Ausgangsstatus
- **STATUS** (WSTRING): Statusinformation über die Operation

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der PUBLISH_5 Block initialisiert sich über das INIT-Ereignis und konfiguriert den Publish-Kanal mit der angegebenen ID. Nach erfolgreicher Initialisierung kann über das REQ-Ereignis Daten an alle verbundenen SUBSCRIBE_5 Blöcke gesendet werden. Die Daten SD_1 bis SD_5 werden dabei gleichzeitig übertragen. Jede Sendung wird durch ein CNF-Ereignis bestätigt.

## Technische Besonderheiten
- Unterstützt den Datentyp ANY für maximale Flexibilität bei den zu sendenden Daten
- Verwendet WSTRING für Statusmeldungen und Kanal-IDs
- Implementiert ein unbestätigtes Sendeverfahren (unconfirmed)
- Bietet Platz für bis zu fünf verschiedene Datenwerte pro Sendevorgang

## Zustandsübersicht
1. **Nicht initialisiert**: Block wartet auf INIT-Ereignis
2. **Initialisiert**: Block ist bereit für REQ-Ereignisse
3. **Senden**: Verarbeitet REQ und sendet Daten an Subscriber
4. **Bestätigen**: Sendet CNF nach erfolgreicher Datenübertragung

## Anwendungsszenarien
- Verteilte Systeme mit Publisher-Subscriber-Architektur
- Datenverteilung an mehrere Empfänger in Echtzeitsystemen
- Flexibles Messaging zwischen verschiedenen Steuerungskomponenten
- Systeme mit variablen Datenstrukturen (durch ANY-Typ Unterstützung)

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfacheren PUBLISH-Blöcken bietet PUBLISH_5 die Möglichkeit, bis zu fünf verschiedene Datenwerte gleichzeitig zu senden. Die Verwendung des ANY-Datentyps ermöglicht größere Flexibilität als typspezifische Publish-Blöcke.

## Fazit
Der PUBLISH_5 Funktionsblock ist eine leistungsfähige Lösung für Publish-Subscribe-Kommunikation in verteilten Automatisierungssystemen. Seine Flexibilität durch den ANY-Datentyp und die Möglichkeit, mehrere Datenwerte gleichzeitig zu senden, machen ihn besonders geeignet für komplexe Datenverteilungsaufgaben in industriellen Steuerungssystemen.