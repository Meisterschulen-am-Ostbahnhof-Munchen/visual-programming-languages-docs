# IA_WBSD


![IA_WBSD](./IA_WBSD.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **IA_WBSD** (ISOBUS Adapter for Wheel Based Speed and Distance) dient als Schnittstellen‑Wrapper für die ISOBUS‑Kommunikation radbasierter Geschwindigkeits‑ und Distanzwerte gemäß ISO 11783‑7. Er kapselt den internen Baustein `I_WBSD` und stellt dessen Funktionalität über standardisierte Adapter‑Anschlüsse bereit.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Ereignis | Typ | Kommentar |
|----------|-----|-----------|
| INIT     | EInit | Service Initialization |

### **Ereignis-Ausgänge**

| Ereignis | Typ | Kommentar |
|----------|-----|-----------|
| INITO    | EInit | Initialization Confirm |

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| QI   | BOOL | Event Input Qualifier (Initialisierungsfreigabe) |

### **Daten-Ausgänge**

| Name   | Typ   | Kommentar |
|--------|-------|-----------|
| QO     | BOOL  | Event Output Qualifier (Initialisierungsergebnis) |
| STATUS | STRING| Statusmeldung (z. B. Fehler oder Erfolg) |

### **Adapter**

| Adapter  | Typ | Kommentar |
|----------|-----|-----------|
| SPEED    | adapter::types::unidirectional::AUI | Wheel‑based machine speed (unidirektional, analoger Wert) |
| DISTANCE | adapter::types::unidirectional::AUDI | Wheel‑based machine distance (unidirektional) |
| TIMEOUT  | adapter::types::unidirectional::AX   | Timeout Status (unidirektional) |

## Funktionsweise
Der Baustein **IA_WBSD** ist ein reiner Adapter‑Wrapper. Er verbindet die externen Ereignis‑ und Datenschnittstellen sowie die drei Adapter direkt mit dem internen Funktionsblock `I_WBSD` (vom Typ `isobus::tecu::I_WBSD`).  
- Über den **INIT**‑Eingang und das Qualifier‑Signal **QI** wird die Initialisierung des ISOBUS‑Dienstes angestoßen.  
- Nach erfolgreicher Initialisierung wird **INITO** ausgelöst und **QO** auf `TRUE` gesetzt. **STATUS** enthält eine textuelle Rückmeldung.  
- Die Adapter **SPEED** und **DISTANCE** liefern die aktuellen Messwerte für radbasierte Geschwindigkeit bzw. Distanz.  
- Der Adapter **TIMEOUT** signalisiert, ob ein Timeout in der ISOBUS‑Kommunikation aufgetreten ist.

Die interne Logik (Berechnung, Timeout‑Überwachung, ISOBUS‑Frame‑Handling) wird vollständig vom inneren FB `I_WBSD` übernommen; **IA_WBSD** stellt diese nach außen als IEC‑61499‑kompatible Adapter‑Schnittstelle zur Verfügung.

## Technische Besonderheiten
- **Standard:** ISO 11783‑7 (ISOBUS) – PGN 65096  
- **Entwicklungsgeschichte:**  
  - Version 1.0: initiale Implementierung als Adapter‑Wrapper für `I_WBSD`  
  - Version 1.1: Fehlerbehebung – korrekte Verbindung zwischen internen Pins und Adapter‑Plugs durch zusätzliche Konvertierungsbausteine  
- **Compiler‑Paket:** `isobus::tecu`  
- **Lizenz:** Eclipse Public License 2.0  
- **Urheber:** - (nicht genannt)

## Zustandsübersicht
Der Baustein besitzt keine eigene explizite Zustandsmaschine. Das Verhalten wird durch den inneren FB `I_WBSD` gesteuert:
- **Ruhezustand:** Keine Initialisierung ausstehend.
- **Initialisierungslauf:** Nach **INIT** mit **QI = TRUE** wird der interne Prozess gestartet. Bei **QI = FALSE** erfolgt keine Aktion.
- **Initialisierung abgeschlossen:** **INITO** wird ausgelöst, **QO** zeigt Erfolg (`TRUE`) oder Misserfolg (`FALSE`). Danach können über die Adapter laufend Messwerte und Timeout‑Status empfangen werden.

## Anwendungsszenarien
- **Landwirtschaftliche Maschinensteuerung:** Einbindung radbasierter Geschwindigkeits‑ und Distanzsensoren in ein ISOBUS‑Steuerungssystem (z. B. für Traktoren, Erntemaschinen).  
- **Positionierung ohne GPS:** Nutzung der Radsensoren zur relativen Positionsbestimmung in Feldarbeitsanwendungen.  
- **Überwachung von Fahrzyklen:** Erfassung von Geschwindigkeits‑ und Distanzdaten für Diagnose oder Prozesssteuerung.

## Vergleich mit ähnlichen Bausteinen
- **IA_WBSD vs. direkter I_WBSD:** Der interne FB `I_WBSD` bietet die reine ISOBUS‑Implementierung, während **IA_WBSD** diese in ein IEC‑61499‑Adapter‑Interface kapselt. Dadurch wird die Wiederverwendung in verschiedenen Tools (z. B. 4diac‑IDE) und die lose Kopplung mit anderen Bausteinen erleichtert.  
- **IA_WBSD vs. andere ISOBUS‑Adapter:** Spezifisch für die PGN 65096 (Wheel Based Speed and Distance). Adapter für andere PGNs (z. B. für GPS‑Position oder Motor‑Drehzahl) haben ähnliche Struktur, unterscheiden sich aber in den Datentypen und der internen Interpretation.

## Fazit
Der **IA_WBSD** ist ein praktischer Adapter‑Wrapper für den ISOBUS‑Baustein `I_WBSD`. Er reduziert die Einbindungskomplexität radbasierter Geschwindigkeits‑ und Distanzdaten in IEC‑61499‑Projekte und stellt die Funktionalität über standardisierte unidirektionale Adapter bereit. Dank der Lizenz unter EPL 2.0 kann er frei in eigenen Projekten verwendet und angepasst werden. Die Version 1.1 stellt sicher, dass alle internen Verbindungen korrekt auf die Adapter‑Plugs geführt sind.