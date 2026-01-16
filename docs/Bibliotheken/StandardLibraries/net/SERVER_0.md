# SERVER_0

* * * * * * * * * *

## Einleitung
Der SERVER_0 Funktionsblock dient als Gegenstelle zu einem CLIENT_0 Block. Er ermöglicht die Einrichtung einer Server-Client-Verbindung ohne Austausch von Nutzdaten über Daten-Ein-/Ausgänge.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT** (Typ: Event) - Aktiviert den Server für eine Client-Verbindung (QI = TRUE) oder schließt den Server (QI = FALSE)
- **RSP** (Typ: Event) - Sendet eine Antwort/Bestätigung an den Client

### **Ereignis-Ausgänge**
- **INITO** (Typ: Event) - Signalisiert Bereitschaft für Client-Verbindung (QI = TRUE) oder geschlossenen Zustand (QI = FALSE)
- **IND** (Typ: Event) - Zeigt an, dass eine Anfrage vom Client eingegangen ist

### **Daten-Eingänge**
- **QI** (BOOL) - Qualifizierer für INIT-Operation
- **ID** (WSTRING) - Identifikator für die Server-Instanz

### **Daten-Ausgänge**
- **QO** (BOOL) - Qualifizierer für Statusausgabe
- **STATUS** (WSTRING) - Statusinformationen

## Funktionsweise
Der SERVER_0 Block verwaltet die Verbindung.
1. **Initialisierung**: Aktivierung über INIT.
2. **Synchronisation**: 
   - Wenn der Client eine Anfrage sendet (REQ), wird am Server das IND-Ereignis ausgelöst.
   - Der Server kann daraufhin mit RSP antworten, was beim Client zum CNF-Ereignis führt.
   Es werden dabei keine Nutzdaten (SD_x, RD_x) übertragen.

## Technische Besonderheiten
- Keine Daten-Ein-/Ausgänge vorhanden
- WSTRING-Typ für ID und STATUS
- Generische Implementierung durch 'GEN_SERVER' Klassenattribut

## Zustandsübersicht
- **Nicht initialisiert**: Server inaktiv
- **Initialisiert**: Server bereit
- **Indication (IND)**: Client hat angefragt
- **Response (RSP)**: Server antwortet

## Anwendungsszenarien
- Ereignis-Synchronisation
- Signalisierung von Zuständen ohne Dateninhalt

## Metadaten
| Attribut | Wert |
| :--- | :--- |
| Copyright | (c) 2025 Monika Wenger |
| Lizenz | EPL-2.0 |
| Version | 3.0 (2025-12-05, Monika Wenger) |
| 4diac-Paket | iec61499::net |
