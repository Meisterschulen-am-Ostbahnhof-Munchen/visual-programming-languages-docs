# PUBLISH_1

```{index} single: PUBLISH_1
```

<img width="1376" height="304" alt="image" src="https://github.com/user-attachments/assets/7f3d2118-5ae0-42c5-9151-1387bc2aff24" />

* * * * * * * * * *

## Einleitung
Der PUBLISH_1-Funktionsblock dient zum Senden von Daten an einen oder mehrere SUBSCRIBE_1-Blöcke. Er implementiert ein Publish-Subscribe-Kommunikationsmuster, bei dem Daten unbestätigt an alle angemeldeten Empfänger verteilt werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Initialisierungsereignis mit zugehörigen Daten QI und ID
- **REQ**: Sendeanfrage für Daten (unbestätigt) mit zugehörigen Daten QI und SD_1

### **Ereignis-Ausgänge**
- **INITO**: Bestätigung der Initialisierung mit zugehörigen Daten QO und STATUS
- **CNF**: Bestätigung, dass Daten gesendet wurden mit zugehörigen Daten QO und STATUS

### **Daten-Eingänge**
- **QI** (BOOL): Qualifizierer für Initialisierung und Betrieb
- **ID** (WSTRING): Identifikator für den Publish-Kanal
- **SD_1** (ANY): Zu sendende Daten (beliebiger Datentyp)

### **Daten-Ausgänge**
- **QO** (BOOL): Qualifizierer für Ausgangsstatus
- **STATUS** (WSTRING): Statusinformationen als Unicode-String

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der PUBLISH_1-Block ermöglicht die Verteilung von Daten an mehrere Empfänger über einen Publish-Subscribe-Mechanismus. Bei Initialisierung (INIT-Ereignis) wird der Block mit einer spezifischen ID konfiguriert. Bei Empfang eines REQ-Ereignisses werden die an SD_1 übergebenen Daten an alle SUBSCRIBE_1-Blöcke mit derselben ID gesendet. Die Kommunikation erfolgt unbestätigt, d.h. es wird keine Rückmeldung von den Empfängern erwartet.

## Technische Besonderheiten
- Verwendung des ANY-Datentyps für SD_1 ermöglicht das Senden beliebiger Datenstrukturen
- WSTRING-Datentyp für ID und STATUS unterstützt internationale Zeichensätze
- Unbestätigte Kommunikation für reduzierte Latenz
- Generische Implementierung durch GenericClassName-Attribut

## Zustandsübersicht
1. **Nicht initialisiert**: Block wartet auf INIT-Ereignis
2. **Initialisiert**: Block bereit zum Empfang von REQ-Ereignissen
3. **Sendeaktiv**: Verarbeitung von REQ-Ereignissen und Datenverteilung

## Anwendungsszenarien
- Verteilung von Sensordaten an mehrere Verarbeitungsknoten
- Broadcast von Systemstatusinformationen
- Verteilen von Konfigurationsdaten an mehrere Steuerungen
- Multi-Cast-Kommunikation in verteilten Automatisierungssystemen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu bestätigten Kommunikationsblöcken bietet PUBLISH_1 reduzierte Latenz durch unbestätigte Übertragung. Gegenüber Punkt-zu-Punkt-Verbindungen ermöglicht er effiziente 1-zu-n-Kommunikation ohne explizite Verbindungsaufbauten zu jedem Empfänger.

## Fazit
Der PUBLISH_1-Block ist ein effizientes Werkzeug für unbestätigte 1-zu-n-Kommunikation in verteilten Automatisierungssystemen. Seine flexible Datentypunterstützung und einfache Konfiguration machen ihn ideal für Szenarien, in denen Daten an mehrere Empfänger verteilt werden müssen, ohne dass Bestätigungen erforderlich sind.
