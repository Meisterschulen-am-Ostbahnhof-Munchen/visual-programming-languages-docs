# CLIENT_2_1

```{index} single: CLIENT_2_1
```

<img width="1295" height="167" alt="image" src="https://github.com/user-attachments/assets/988495a6-1be4-41f0-9d85-c324b87e7290" />

* * * * * * * * * *

## Einleitung
Der CLIENT_2_1 Funktionsblock dient zur Kommunikation mit einem SERVER_1_2 Block über eine Netzwerkverbindung. Er ermöglicht das Aufbauen und Trennen von Verbindungen sowie den Datenaustausch zwischen Client und Server.

![CLIENT_2_1](CLIENT_2_1.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Initialisierungsereignis zum Öffnen (QI = TRUE) oder Schließen (QI = FALSE) einer Verbindung
- **REQ**: Anforderungsereignis zum Senden von Daten an den Server und Anfordern von Daten vom Server

### **Ereignis-Ausgänge**
- **INITO**: Bestätigungsereignis für Verbindungsaufbau (QI = TRUE) oder Verbindungstrennung (QI = FALSE)
- **CNF**: Bestätigungsereignis bei neu verfügbaren Daten vom Server

### **Daten-Eingänge**
- **QI** (BOOL): Qualitätsindikator für INIT-Ereignis (TRUE = Verbindung öffnen, FALSE = Verbindung schließen)
- **ID** (WSTRING): Identifikator für die Verbindung
- **SD_1** (ANY): Erster Sendeblock für Daten an den Server
- **SD_2** (ANY): Zweiter Sendeblock für Daten an den Server

### **Daten-Ausgänge**
- **QO** (BOOL): Qualitätsindikator für Ausgangsereignisse
- **STATUS** (WSTRING): Statusinformation über die Verbindung oder Operation
- **RD_1** (ANY): Empfangener Datenblock vom Server

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der CLIENT_2_1 Block verwaltet die gesamte Client-Seite einer Client-Server-Kommunikation. Bei INIT mit QI=TRUE wird eine neue Verbindung zum angegebenen Server aufgebaut. Mit INIT und QI=FALSE wird eine bestehende Verbindung geschlossen. Das REQ-Ereignis löst gleichzeitig das Senden der Daten SD_1 und SD_2 an den Server sowie das Anfordern von Daten vom Server aus. Bei erfolgreicher Operation werden die empfangenen Daten über RD_1 ausgegeben.

## Technische Besonderheiten
- Unterstützt den Datentyp ANY für flexible Datenübertragung
- Verwendet WSTRING für Statusmeldungen und Verbindungs-IDs
- Bietet bidirektionalen Datenaustausch in einer einzigen Operation
- Implementiert vollständige Verbindungsverwaltung (Aufbau/Trennung)

## Zustandsübersicht
Der Block kann folgende Zustände annehmen:
- Nicht verbunden (initialer Zustand)
- Verbindungsaufbau läuft
- Verbunden und betriebsbereit
- Verbindungstrennung läuft

## Anwendungsszenarien
- Industrielle Automatisierungssysteme mit verteilter Steuerung
- IoT-Anwendungen mit Client-Server-Architektur
- Datenaustausch zwischen verschiedenen Steuerungsebenen
- Remote-Überwachung und -Steuerung von Geräten

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfacheren Client-Blöcken bietet CLIENT_2_1 die Möglichkeit, zwei verschiedene Datenblöcke gleichzeitig zu senden und einen Datenblock zu empfangen. Die Integration von Verbindungsmanagement und Datenaustausch in einem Block vereinfacht die Anwendungslogik.

## Fazit
Der CLIENT_2_1 Funktionsblock stellt eine leistungsfähige Lösung für Client-Server-Kommunikation in verteilten Automatisierungssystemen dar. Durch die Kombination von Verbindungsmanagement und bidirektionalem Datenaustausch in einem einzigen Block ermöglicht er effiziente und übersichtliche Netzwerkanwendungen.