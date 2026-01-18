# CLIENT_1

```{index} single: CLIENT_1
```

<img width="1355" height="161" alt="image" src="https://github.com/user-attachments/assets/add0b8a4-197b-4733-b9d8-45407aae8979" />

* * * * * * * * * *

## Einleitung
Der CLIENT_1 Funktionsblock dient zur Kommunikation mit einem SERVER_1 Block über eine Netzwerkverbindung. Er ermöglicht das Aufbauen und Schließen von Verbindungen sowie den Datenaustausch zwischen Client und Server.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Öffnet eine neue Verbindung (QI = TRUE) oder schließt eine bestehende Verbindung (QI = FALSE)
- **REQ**: Sendet Daten an den Server und fordert Daten vom Server an

### **Ereignis-Ausgänge**
- **INITO**: Bestätigt das Herstellen einer neuen Verbindung (QI = TRUE) oder das Schließen einer Verbindung (QI = FALSE)
- **CNF**: Signalisiert, dass neue Daten vom Server verfügbar sind

### **Daten-Eingänge**
- **QI** (BOOL): Steuert den Verbindungsstatus (TRUE = Verbindung öffnen, FALSE = Verbindung schließen)
- **ID** (WSTRING): Identifikator für die Verbindung
- **SD_1** (ANY): Zu sendende Daten an den Server

### **Daten-Ausgänge**
- **QO** (BOOL): Status der Verbindung (TRUE = verbunden, FALSE = getrennt)
- **STATUS** (WSTRING): Statusinformationen über die Verbindung
- **RD_1** (ANY): Vom Server empfangene Daten

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der CLIENT_1 Block initialisiert eine Netzwerkverbindung zum SERVER_1 Block über das INIT-Ereignis. Bei erfolgreicher Verbindung wird das INITO-Ereignis mit QO=TRUE ausgelöst. Über das REQ-Ereignis können Daten an den Server gesendet und gleichzeitig Daten vom Server angefordert werden. Empfangene Daten werden über das CNF-Ereignis mit den entsprechenden Datenausgängen bereitgestellt.

## Technische Besonderheiten
- Verwendung des ANY-Datentyps für SD_1 und RD_1 ermöglicht flexible Datentypen
- WSTRING-Datentyp für ID und STATUS unterstützt Unicode-Zeichen
- Generische Implementierung durch GEN_CLIENT Klassennamen

## Zustandsübersicht
1. **Nicht verbunden**: Initialzustand, QO = FALSE
2. **Verbindungsaufbau**: INIT mit QI = TRUE verarbeitet
3. **Verbunden**: INITO mit QO = TRUE bestätigt
4. **Datenübertragung**: REQ/CNF-Zyklus für Datenaustausch
5. **Verbindungstrennung**: INIT mit QI = FALSE verarbeitet

## Anwendungsszenarien
- Kommunikation zwischen verteilten Steuerungssystemen
- Datenaustausch in Industrie-4.0-Anwendungen
- Client-Server-Architekturen in Automatisierungssystemen
- Vernetzte Steuerungskomponenten über TCP/IP oder andere Protokolle

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfacheren Kommunikationsblöcken bietet CLIENT_1:
- Bidirektionalen Datenaustausch in einer Transaktion
- Flexible Datentypen durch ANY-Typ
- Explizite Verbindungssteuerung
- Detaillierte Statusrückmeldungen

## Fazit
Der CLIENT_1 Funktionsblock stellt eine robuste Lösung für Client-Server-Kommunikation in verteilten Automatisierungssystemen dar. Seine flexible Schnittstelle und explizite Verbindungssteuerung machen ihn besonders geeignet für anspruchsvolle Netzwerkanwendungen in industriellen Umgebungen.