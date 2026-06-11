# IA_VP1


![IA_VP1](./IA_VP1.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **IA_VP1** ist ein ISOBUS-Adapter für die Vehicle Position 1 (VP1) gemäß ISO 11783-7 (PGN 65267). Er kapselt die Kommunikation zur Fahrzeugposition und stellt die empfangenen Daten über unidirektionale Adapter-Schnittstellen für die weitere Verarbeitung in der 4diac-IDE bereit.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Typ | Kommentar |
|----------|-----|-----------|
| INIT | EInit | Service Initialization |

### **Ereignis-Ausgänge**
| Ereignis | Typ | Kommentar |
|----------|-----|-----------|
| INITO | EInit | Initialization Confirm |

### **Daten-Eingänge**
| Variable | Typ | Kommentar |
|----------|-----|-----------|
| QI | BOOL | Event Input Qualifier |

### **Daten-Ausgänge**
| Variable | Typ | Kommentar |
|----------|-----|-----------|
| QO | BOOL | Event Output Qualifier |
| STATUS | STRING | Statusinformation |

### **Adapter**
| Adapter | Typ | Kommentar |
|---------|-----|-----------|
| LAT | adapter::types::unidirectional::AR | Latitude |
| LON | adapter::types::unidirectional::AR | Longitude |
| TIMEOUT | adapter::types::unidirectional::AX | Timeout Status |

## Funktionsweise
Der Baustein enthält intern eine Instanz des Funktionsblocks `I_VP1` aus der Bibliothek `isobus::tecu`. Beim Eintreffen des INIT-Ereignisses wird die Initialisierung angestoßen – der Qualifier `QI` bestimmt, ob die Initialisierung aktiv erfolgt. Nach erfolgreicher Initialisierung wird das INITO-Ereignis ausgelöst, begleitet von den Ausgangsdaten `QO` und `STATUS`.

Die eigentlichen Positionsdaten (Breitengrad und Längengrad) sowie der Timeout-Status werden über die unidirektionalen Adapter ausgegeben. Jeder Adapter wird durch ein Ereignis (z. B. `IND` vom Kernbaustein) getriggert und stellt den zugehörigen Datenwert (`D1`) an der Adapter-Schnittstelle bereit.

## Technische Besonderheiten
- **Unidirektionale Adapter:** Die Schnittstellen LAT und LON verwenden den Typ `AR`, der nur einen Ausgangs-Datenwert liefert. Der TIMEOUT-Adapter verwendet den Typ `AX` für einen booleschen Timeout-Status.
- **ISOBUS-Konformität:** Der Baustein implementiert das Vehicle Position 1 (VP1)-Nachrichtenformat gemäß ISO 11783-7.
- **Latitude-/Longitude-Bereitstellung:** Die Werte werden direkt vom internen Kernbaustein durchgereicht und sind als Gleitkommazahlen im Adapter verfügbar.
- **Timeout-Überwachung:** Der TIME
OUT-Adapter signalisiert, ob die Positionsdaten innerhalb einer erwarteten Zeit eingetroffen sind.

## Zustandsübersicht
Der Baustein besitzt keine explizit dargestellte Zustandsmaschine. Das Verhalten ist ereignisgesteuert:
- **Inaktiv:** Vor dem INIT-Ereignis liegt keine Initialisierung vor.
- **Initialisierung:** Sobald INIT mit `QI=TRUE` eintrifft, wird die Initialisierungssequenz gestartet.
- **Aktiv:** Nach erfolgreichem INITO stehen die Positions- und Timeout-Daten an den Adaptern zur Verfügung. Die Daten werden mit jedem neuen internen Ereignis (getriggert durch den Kern) aktualisiert.
- **Fehlerfall:** Der Status-String und `QO` geben Aufschluss über Fehler oder Timeout.

## Anwendungsszenarien
- **Landwirtschaftliche Fahrzeuge:** Auslesen der aktuellen GPS-Position (Breite/Länge) über den ISOBUS-Bordcomputer.
- **Präzisionslandwirtschaft:** Verwendung der Positionsdaten zur Steuerung von Teilbreitenschaltungen, variabler Ausbringung oder Spurführung.
- **Dokumentation und Telemetrie:** Aufzeichnung von Fahrzeugbewegungen und Positionsdaten für Flottenmanagement.

## Vergleich mit ähnlichen Bausteinen
- **IA_VP0, IA_GP, IA_PD:** Andere ISOBUS-Positions- und Datenadapter (z. B. für Geschwindigkeit, Maschinenposition). Im Gegensatz dazu fokussiert IA_VP1 auf die reine Vehicle Position (Breitengrad, Längengrad) und den Timeout-Status. Die Daten werden hier als unidirektionale Adapter und nicht als einfache Datenausgänge bereitgestellt.
- **I_VP1 (Kernbaustein):** Der interne Kernbaustein bietet dieselbe Funktionalität, jedoch ohne die Adapter-Kapselung. IA_VP1 macht die Schnittstellen für die modulare 4diac-Umgebung zugänglicher.

## Fazit
Der Funktionsblock **IA_VP1** ist ein praktischer und normgerechter Baustein, um die Fahrzeugposition aus dem ISOBUS in die 4diac-Welt zu integrieren. Die Verwendung von unidirektionalen Adaptern ermöglicht eine saubere Trennung und einfache Einbindung in größere Automatisierungsnetzwerke. Dank der Standardkonformität und der einfachen Initialisierung eignet er sich hervorragend für landwirtschaftliche Steuerungen und IoT-Anwendungen.