# SERVER_1_2

```{index} single: SERVER_1_2
```

<img width="1411" height="176" alt="image" src="https://github.com/user-attachments/assets/244f332f-3155-4f3f-abb2-209e12652030" />

* * * * * * * * * *

## Einleitung
Der SERVER_1_2 Funktionsblock dient zur Kommunikation mit einem CLIENT_2_1 Block und ermöglicht die Erstellung einer Server-Client-Verbindung. Der Block kann Daten empfangen und senden sowie die Verbindung initialisieren und beenden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Initialisiert den Server für eine Client-Verbindung (QI = TRUE) oder schließt den Server (QI = FALSE)
- **RSP**: Sendet Daten an den Client

### **Ereignis-Ausgänge**
- **INITO**: Signalisiert Bereitschaft für Client-Verbindung (QI = TRUE) oder geschlossenen Zustand (QI = FALSE)
- **IND**: Zeigt neue verfügbare Daten vom Client an

### **Daten-Eingänge**
- **QI** (BOOL): Qualifizierer für INIT-Ereignis (TRUE = aktivieren, FALSE = deaktivieren)
- **ID** (WSTRING): Identifikationsstring für die Server-Instanz
- **SD_1** (ANY): Zu sendende Daten an den Client

### **Daten-Ausgänge**
- **QO** (BOOL): Statusausgabe (TRUE = aktiv, FALSE = inaktiv)
- **STATUS** (WSTRING): Statusinformationen als Zeichenkette
- **RD_1** (ANY): Empfangene Daten vom Client (Kanal 1)
- **RD_2** (ANY): Empfangene Daten vom Client (Kanal 2)

## Funktionsweise
Der SERVER_1_2 Block arbeitet als Server in einer Client-Server-Architektur. Bei Initialisierung (INIT mit QI=TRUE) wird der Server für eingehende Verbindungen bereitgestellt. Bei eingehenden Daten vom Client wird das IND-Ereignis ausgelöst und die empfangenen Daten über RD_1 und RD_2 bereitgestellt. Über das RSP-Ereignis können Daten zurück an den Client gesendet werden.

## Technische Besonderheiten
- Unterstützt den Datentyp ANY für flexible Datenübertragung
- Verwendet WSTRING für Statusmeldungen und Identifikation
- Bietet zwei separate Datenkanäle für den Empfang (RD_1 und RD_2)
- Implementiert als generischer Server-Baustein

## Zustandsübersicht
- **Inaktiv**: Server nicht initialisiert (QO = FALSE)
- **Aktiv**: Server bereit für Client-Verbindungen (QO = TRUE)
- **Datenempfang**: Neue Daten vom Client verfügbar (IND-Ereignis)
- **Datensendung**: Daten werden an Client gesendet (RSP-Ereignis)

## Anwendungsszenarien
- Netzwerkkommunikation in verteilten Automatisierungssystemen
- Datenaustausch zwischen verschiedenen Steuerungskomponenten
- Implementierung von Server-Diensten in IEC 61499-basierten Systemen
- Bidirektionale Kommunikation in industriellen Netzwerken

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfacheren Kommunikationsbausteinen bietet SERVER_1_2 eine vollständige Server-Implementierung mit Initialisierungs- und Statusmanagement. Die zwei separaten Empfangskanäle ermöglichen eine strukturierte Datenverarbeitung.

## Fazit
Der SERVER_1_2 Funktionsblock stellt eine robuste Lösung für Server-basierte Kommunikation in IEC 61499-Systemen dar. Durch die flexible Datentypunterstützung und klare Zustandsverwaltung eignet er sich ideal für verschiedene industrielle Kommunikationsszenarien.
