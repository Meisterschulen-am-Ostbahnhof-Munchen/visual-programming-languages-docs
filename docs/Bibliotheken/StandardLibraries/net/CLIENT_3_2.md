# CLIENT_3_2

```{index} single: CLIENT_3_2
```

<img width="1368" height="191" alt="image" src="https://github.com/user-attachments/assets/bd26cabe-e445-4ad6-97b6-00579ab220c9" />

* * * * * * * * * *

## Einleitung
Der CLIENT_3_2 ist ein Funktionsblock für HTTP-Kommunikation, der als Client mit drei Eingängen und zwei Ausgängen konzipiert wurde. Er ermöglicht die Kommunikation mit einem Server über das HTTP-Protokoll und unterstützt sowohl das Öffnen und Schließen von Verbindungen als auch das Senden von Anfragen und Empfangen von Antworten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **INIT** (Typ: EInit) - Öffnet eine neue Verbindung (QI = TRUE) oder schließt eine Verbindung (QI = FALSE)
- **REQ** (Typ: Event) - Sendet Daten an den Server

### **Ereignis-Ausgänge**

- **INITO** (Typ: EInit) - Signalisiert, dass eine neue Verbindung aufgebaut wurde (QI = TRUE) oder eine Verbindung geschlossen wurde (QI = FALSE)
- **CNF** (Typ: Event) - Antwort vom Server

### **Daten-Eingänge**

- **QI** (BOOL) - Qualitätsindikator für INIT- und REQ-Ereignisse
- **ID** (WSTRING) - Identifikator für die Verbindung
- **SD_1** (ANY) - Token für die Authentifizierung am Server
- **SD_2** (ANY) - Parameter für die Nachricht
- **SD_3** (ANY) - Body der Nachricht

### **Daten-Ausgänge**

- **QO** (BOOL) - Qualitätsindikator für INITO- und CNF-Ereignisse
- **STATUS** (WSTRING) - Statusinformationen
- **RD_1** (ANY) - Antwortcode vom Server
- **RD_2** (ANY) - Body der Server-Antwort

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der CLIENT_3_2 Funktionsblock arbeitet in zwei Hauptphasen: Verbindungsmanagement und Datenübertragung. Über das INIT-Ereignis wird zunächst eine Verbindung zum Server aufgebaut oder geschlossen. Nach erfolgreichem Verbindungsaufbau können über das REQ-Ereignis Daten an den Server gesendet werden. Die Server-Antwort wird über das CNF-Ereignis zurückgemeldet.

## Technische Besonderheiten
- Verwendung von WSTRING für ID und STATUS für internationale Zeichensatzunterstützung
- ANY-Typ für SD_1, SD_2, SD_3, RD_1 und RD_2 ermöglicht flexible Datentypen
- Separate Qualitätsindikatoren für Eingänge (QI) und Ausgänge (QO)
- Unterstützung von Authentifizierungstokens (SD_1)

## Zustandsübersicht
1. **Initialisierungszustand**: Wartet auf INIT-Ereignis
2. **Verbindungsaufbau**: Verarbeitet INIT mit QI=TRUE
3. **Bereit**: Verbindung steht, wartet auf REQ-Ereignisse
4. **Datenübertragung**: Sendet REQ und wartet auf CNF
5. **Verbindungsabbau**: Verarbeitet INIT mit QI=FALSE

## Anwendungsszenarien
- HTTP-REST-API-Kommunikation in Automatisierungssystemen
- Web-Service-Integration in industriellen Steuerungen
- Datenaustausch mit Cloud-Diensten
- Authentifizierte Kommunikation mit Backend-Servern

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfacheren Client-Bausteinen bietet CLIENT_3_2 erweiterte Funktionalität durch drei separate Dateneingänge (SD_1-3) und zwei Datenausgänge (RD_1-2), was eine strukturierte Übertragung von Authentifizierungsdaten, Parametern und Nachrichteninhalten ermöglicht.

## Fazit
Der CLIENT_3_2 ist ein vielseitiger HTTP-Client-Funktionsblock, der durch seine flexible Datenschnittstelle und umfassende Statusrückmeldungen eine robuste Kommunikation mit HTTP-Servern in industriellen Automatisierungsumgebungen ermöglicht.