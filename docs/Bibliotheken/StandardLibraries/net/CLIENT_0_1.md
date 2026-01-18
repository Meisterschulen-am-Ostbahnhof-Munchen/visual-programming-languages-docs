# CLIENT_0_1

```{index} single: CLIENT_0_1
```

* * * * * * * * * *

## Einleitung
Der CLIENT_0_1 Funktionsblock dient zur Kommunikation mit einem entsprechenden Server-Block (z.B. SERVER_1_0) über eine Netzwerkverbindung. Er ist spezialisiert auf den **Empfang** von Daten vom Server, ohne selbst Daten zu senden (Receive Only Client).

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Öffnet eine neue Verbindung (QI = TRUE) oder schließt eine bestehende Verbindung (QI = FALSE)
- **REQ**: Fordert Daten vom Server an

### **Ereignis-Ausgänge**
- **INITO**: Bestätigt das Herstellen einer neuen Verbindung (QI = TRUE) oder das Schließen einer Verbindung (QI = FALSE)
- **CNF**: Signalisiert, dass neue Daten vom Server empfangen wurden und an RD_1 bereitstehen

### **Daten-Eingänge**
- **QI** (BOOL): Steuert den Verbindungsstatus (TRUE = Verbindung öffnen, FALSE = Verbindung schließen)
- **ID** (WSTRING): Identifikator für die Verbindung

### **Daten-Ausgänge**
- **QO** (BOOL): Status der Verbindung (TRUE = verbunden, FALSE = getrennt)
- **STATUS** (WSTRING): Statusinformationen über die Verbindung
- **RD_1** (ANY): Vom Server empfangene Daten

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der CLIENT_0_1 Block baut über INIT eine Verbindung auf. Mit dem REQ-Ereignis fordert er Daten vom Server an. Wenn der Server antwortet, werden die Daten am Ausgang RD_1 bereitgestellt und das CNF-Ereignis ausgelöst. Es gibt keinen Dateneingang zum Senden von Nutzdaten.

## Technische Besonderheiten
- Unidirektionale Datenübertragung (Empfang)
- Verwendung des ANY-Datentyps für RD_1 ermöglicht flexible Datentypen
- WSTRING-Datentyp für ID und STATUS

## Anwendungsszenarien
- Abfragen von Sensorwerten oder Statusinformationen von einem entfernten System
- Überwachungssysteme (Monitoring), die nur Daten lesen

## Metadaten
| Attribut | Wert |
| :--- | :--- |
| Copyright | (c) 2017, 2025 fortiss GmbH, JKU Linz |
| Lizenz | EPL-2.0 |
| Version | 3.0 (2025-19-26, Alois Zoitl) |
| 4diac-Paket | iec61499::net |
