# logiBUS_IBA


![logiBUS_IBA](./logiBUS_IBA.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **logiBUS_IBA** ist ein zusammengesetzter Baustein (Composite FB) zur Verarbeitung von Byte-Eingabedaten über das logiBUS-Protokoll. Er kapselt die Initialisierung, Konfiguration und Ereignissteuerung eines logiBUS-Eingangsbausteins und stellt die Daten über einen Adapter zur Verfügung. Der Baustein ist für den Einsatz in Steuerungssystemen der Agrartechnik konzipiert.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Ereignis | Typ | Beschreibung |
|----------|-----|--------------|
| INIT | EInit | Service-Initialisierung; übernimmt die Konfigurationsparameter (QI, PARAMS, Input, InputEvent) |
| REQ | Event | Service-Anforderung zur Ausführung einer Funktion (abhängig von QI) |

### **Ereignis-Ausgänge**

| Ereignis | Typ | Beschreibung |
|----------|-----|--------------|
| INITO | EInit | Initialisierungsbestätigung; signalisiert erfolgreiche oder fehlgeschlagene Initialisierung (QO, STATUS) |

### **Daten-Eingänge**

| Variable | Typ | Beschreibung |
|----------|-----|--------------|
| QI | BOOL | Qualifizierer für Ereigniseingänge; steuert die Aktivierung der Ereignisverarbeitung |
| PARAMS | STRING | Service-Parameter (z. B. Konfigurationsdaten für den logiBUS-Treiber) |
| Input | logiBUS::io::DI::logiBUS_DI_S | Auswahl des physischen Eingangs (z. B. Input_I1..I8); Standardwert: `logiBUS_DI::Invalid` |
| InputEvent | logiBUS::io::DI::logiBUS_DI_Events_S | Auswahl des Ereignistyps (derzeit nur `REPEAT` unterstützt); Standardwert: `logiBUS_DI_Events::Invalid` |

### **Daten-Ausgänge**

| Variable | Typ | Beschreibung |
|----------|-----|--------------|
| QO | BOOL | Qualifizierer für Ereignisausgänge; zeigt den Erfolg der Operation an |
| STATUS | STRING | Statusmeldung (z. B. Fehler- oder Erfolgsmeldung) |

### **Adapter**

| Adapter | Typ | Beschreibung |
|---------|-----|--------------|
| IN | adapter::types::unidirectional::AB | Unidirektionaler Adapter zur Bereitstellung der Eingabedaten an die übergeordnete Ressource |

## Funktionsweise
Der Baustein **logiBUS_IBA** arbeitet intern mit einer Instanz des Bausteins **logiBUS_IB** (aus der Bibliothek `logiBUS::io::DI`). Die Ereignis- und Datenpfade sind wie folgt verknüpft:

- Beim **INIT**-Ereignis werden die Eingänge `QI`, `PARAMS`, `Input` und `InputEvent` an die entsprechende Initialisierung des internen Bausteins weitergeleitet. Nach Abschluss der Initialisierung wird das Ausgangsereignis **INITO** gesetzt und die Ausgänge `QO` und `STATUS` aktualisiert.
- Beim **REQ**-Ereignis wird der interne Baustein zur Verarbeitung eines Service-Requests angestoßen. Die Verarbeitung hängt vom aktuellen Zustand und den Eingangsparametern ab.
- Die vom logiBUS-Eingang gelesenen Daten werden über die Adapterverbindung (`IN.E1` und `IN.D1`) an den Ausgangsadapter **IN** übergeben. Der Adapter stellt die Daten einem übergeordneten Baustein oder der Ressource bereit.
- Fehler- und Statussignale werden über `QO` und `STATUS` rückgemeldet.

## Technische Besonderheiten
- **Composite FB:** Der Baustein kapselt die komplexe Initialisierung und Datenbereitstellung eines logiBUS-Eingangs in einer einheitlichen Schnittstelle.
- **Adapterbasierte Datenausgabe:** Die Eingabedaten werden nicht über separate Datenausgänge, sondern über einen **unidirektionalen Adapter** (Typ `AB`) ausgegeben. Dies ermöglicht eine flexible Kopplung mit anderen Bausteinen.
- **Konfigurierbare Eingänge:** Über die Parameter `Input` und `InputEvent` können der physische Eingang (I1..I8) und das Ereignisverhalten (z. B. Wiederholung) ausgewählt werden.
- **Lizenz und Herkunft:** Der Baustein wird unter der **Eclipse Public License 2.0** bereitgestellt und ist für den Einsatz in der Agrartechnik optimiert.

## Zustandsübersicht
Der Baustein besitzt keine explizit dargestellte Zustandsmaschine, da es sich um einen Composite FB handelt. Das interne Verhalten wird durch den enthaltenen Baustein **logiBUS_IB** bestimmt, der typischerweise folgende Zustände implementiert:
- **IDLE** – Warten auf INIT oder REQ
- **INIT** – Initialisierung mit Parametern
- **RUN** – Betriebsbereit, Datenverarbeitung aktiv
- **ERROR** – Fehlerzustand (Statusmeldung über STATUS)

## Anwendungsszenarien
- **Landwirtschaftliche Steuerungen:** Erfassung digitaler Eingangssignale (z. B. Sensoren, Schalter) über logiBUS und Weiterleitung an eine Steuerung.
- **Eingabemodule in Feldbus-Systemen:** Der Baustein dient als standardisierte Schnittstelle für logiBUS-Eingänge in IEC 61499-2-Anwendungen.
- **Prototypen und Testaufbauten:** Dank der Konfigurierbarkeit kann der Baustein schnell an verschiedene Eingangskonfigurationen angepasst werden.

## Vergleich mit ähnlichen Bausteinen
- **logiBUS_IB:** Der innere Baustein ist ein reiner Basic FB; **logiBUS_IBA** fügt eine Adapter-Ausgabe und eine vereinfachte Ereignissteuerung hinzu.
- **SYNC/D_SYNC:** Diese Bausteine aus der Sync-Bibliothek bieten ähnliche Eingangskonfiguration, jedoch ohne spezifische logiBUS-Protokollunterstützung.
- **Eingangsadapter generisch:** Im Vergleich zu generischen Adaptern bietet **logiBUS_IBA** eine vordefinierte logiBUS-Konfiguration, was den Entwicklungsaufwand reduziert.

## Fazit
Der **logiBUS_IBA** ist ein praktischer Composite-FB für die Integration von logiBUS-Eingängen in IEC 61499-basierte Automatisierungssysteme. Durch die Kombination von Initialisierung, Parameterkonfiguration und Adapter-basierter Datenausgabe wird eine saubere und wiederverwendbare Schnittstelle geschaffen. Er eignet sich besonders für Anwendungen in der Agrartechnik, die auf das logiBUS-Protokoll setzen.