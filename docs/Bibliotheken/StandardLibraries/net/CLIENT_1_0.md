# CLIENT_1_0

* * * * * * * * * *

## Einleitung
Der CLIENT_1_0 Funktionsblock dient zur Kommunikation mit einem entsprechenden Server-Block (z.B. SERVER_0_1) über eine Netzwerkverbindung. Er ist spezialisiert auf das **Senden** von Daten an den Server, ohne Daten zu empfangen (Send Only Client).

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Öffnet eine neue Verbindung (QI = TRUE) oder schließt eine bestehende Verbindung (QI = FALSE)
- **REQ**: Sendet die an SD_1 anliegenden Daten an den Server

### **Ereignis-Ausgänge**
- **INITO**: Bestätigt das Herstellen einer neuen Verbindung (QI = TRUE) oder das Schließen einer Verbindung (QI = FALSE)
- **CNF**: Bestätigt, dass die Daten erfolgreich gesendet wurden

### **Daten-Eingänge**
- **QI** (BOOL): Steuert den Verbindungsstatus (TRUE = Verbindung öffnen, FALSE = Verbindung schließen)
- **ID** (WSTRING): Identifikator für die Verbindung
- **SD_1** (ANY): Zu sendende Daten an den Server

### **Daten-Ausgänge**
- **QO** (BOOL): Status der Verbindung (TRUE = verbunden, FALSE = getrennt)
- **STATUS** (WSTRING): Statusinformationen über die Verbindung

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der CLIENT_1_0 Block baut über INIT eine Verbindung auf. Wenn das REQ-Ereignis ausgelöst wird, sendet der Block den Wert von SD_1 an den Server. Der erfolgreiche Versand wird durch das CNF-Ereignis bestätigt. Es gibt keinen Datenausgang für Empfangsdaten.

## Technische Besonderheiten
- Unidirektionale Datenübertragung (Senden)
- Verwendung des ANY-Datentyps für SD_1 ermöglicht flexible Datentypen
- WSTRING-Datentyp für ID und STATUS

## Anwendungsszenarien
- Senden von Steuerbefehlen oder Sollwerten an ein entferntes System (ohne direkte Rückantwort als Datum)
- Logging-Clients, die Daten an einen zentralen Server pushen

## Metadaten
| Attribut | Wert |
| :--- | :--- |
| Copyright | (c) 2017, 2025 fortiss GmbH, JKU Linz |
| Lizenz | EPL-2.0 |
| Version | 3.0 (2025-19-26, Alois Zoitl) |
| 4diac-Paket | iec61499::net |
