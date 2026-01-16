# CLIENT_0

* * * * * * * * * *

## Einleitung
Der CLIENT_0 Funktionsblock dient zur Kommunikation mit einem SERVER_0 Block über eine Netzwerkverbindung. Er ermöglicht das Aufbauen und Schließen von Verbindungen. Im Gegensatz zu CLIENT_1 findet kein expliziter Datenaustausch über Daten-Ein-/Ausgänge statt, die Synchronisation erfolgt primär über Ereignisse.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Öffnet eine neue Verbindung (QI = TRUE) oder schließt eine bestehende Verbindung (QI = FALSE)
- **REQ**: Fordert eine Interaktion mit dem Server an

### **Ereignis-Ausgänge**
- **INITO**: Bestätigt das Herstellen einer neuen Verbindung (QI = TRUE) oder das Schließen einer Verbindung (QI = FALSE)
- **CNF**: Bestätigt die Ausführung der Anforderung

### **Daten-Eingänge**
- **QI** (BOOL): Steuert den Verbindungsstatus (TRUE = Verbindung öffnen, FALSE = Verbindung schließen)
- **ID** (WSTRING): Identifikator für die Verbindung

### **Daten-Ausgänge**
- **QO** (BOOL): Status der Verbindung (TRUE = verbunden, FALSE = getrennt)
- **STATUS** (WSTRING): Statusinformationen über die Verbindung

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der CLIENT_0 Block initialisiert eine Netzwerkverbindung zum SERVER_0 Block über das INIT-Ereignis. Bei erfolgreicher Verbindung wird das INITO-Ereignis mit QO=TRUE ausgelöst. Über das REQ-Ereignis kann eine Interaktion mit dem Server angestoßen werden, deren Abschluss durch CNF bestätigt wird.

## Technische Besonderheiten
- Keine Daten-Ein-/Ausgänge (SD_x, RD_x) vorhanden
- WSTRING-Datentyp für ID und STATUS
- Generische Implementierung durch GEN_CLIENT Klassennamen

## Zustandsübersicht
1. **Nicht verbunden**: Initialzustand, QO = FALSE
2. **Verbindungsaufbau**: INIT mit QI = TRUE verarbeitet
3. **Verbunden**: INITO mit QO = TRUE bestätigt
4. **Interaktion**: REQ/CNF-Zyklus
5. **Verbindungstrennung**: INIT mit QI = FALSE verarbeitet

## Anwendungsszenarien
- Reine Ereignis-Synchronisation zwischen Systemen
- "Heartbeat"-Überwachung ohne Nutzdaten
- Trigger-Signale über Netzwerk

## Metadaten
| Attribut | Wert |
| :--- | :--- |
| Copyright | (c) 2025 Monika Wenger |
| Lizenz | EPL-2.0 |
| Version | 3.0 (2025-12-05, Monika Wenger) |
| 4diac-Paket | iec61499::net |
