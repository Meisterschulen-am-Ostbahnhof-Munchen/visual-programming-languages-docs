# NVS_AIS


![NVS_AIS](./NVS_AIS.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `NVS_AIS` dient zum Speichern und Laden von Zeichenketten (STRING) im nichtflüchtigen Speicher (NVS – Non‑Volatile Storage) eines ESP32‑Mikrocontrollers. Die Daten werden über einen Schlüssel (KEY) adressiert und über AIS‑Adapter (Acyclic Information Service) ausgetauscht. Der Baustein kapselt die Initialisierung des NVS sowie die grundlegenden Lese‑ und Schreiboperationen und stellt eine standardisierte Schnittstelle für die Einbindung in industrielle Steuerungsanwendungen bereit.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Typ   | Beschreibung                                            | Mitgeführte Daten |
|----------|-------|----------------------------------------------------------|-------------------|
| INIT     | EInit | **Service Initialization** – Startet den Baustein und die Kommunikation mit dem NVS. | QI, KEY, DEFAULT_VALUE |

### **Ereignis-Ausgänge**
| Ereignis | Typ   | Beschreibung                                            | Mitgeführte Daten |
|----------|-------|----------------------------------------------------------|-------------------|
| INITO    | EInit | **Initialization Confirm** – Bestätigt die erfolgreiche Initialisierung oder signalisiert einen Fehler. | QO, STATUS |

### **Daten-Eingänge**
| Name          | Datentyp | Beschreibung                                                                                     |
|---------------|----------|--------------------------------------------------------------------------------------------------|
| QI            | BOOL     | **Event Input Qualifier** – Steuert das Verhalten während der INIT‑Phase (z. B. Aktivierung).   |
| KEY           | STRING   | **Key name** – Der Schlüssel, unter dem der Wert im NVS gespeichert/abgerufen wird.              |
| DEFAULT_VALUE | STRING   | **Default value** – Wert, der gelesen wird, falls im NVS kein Eintrag zum angegebenen KEY existiert. |

### **Daten-Ausgänge**
| Name   | Datentyp | Beschreibung                                                                 |
|--------|----------|------------------------------------------------------------------------------|
| QO     | BOOL     | **Event Output Qualifier** – Gibt den Erfolg der letzten Operation an.      |
| STATUS | STRING   | **Service Status** – Rückmeldung des NVS‑Treiberstatus (z. B. Fehlertexte). |

### **Adapter**
| Adapter  | Typ                                           | Beschreibung                                                                                         |
|----------|-----------------------------------------------|------------------------------------------------------------------------------------------------------|
| AIS_IN   | `adapter::types::unidirectional::AIS` (Socket) | **Value to store (SET)** – Empfängt einen zu speichernden STRING‑Wert über das AIS‑Protokoll.        |
| AIS_OUT  | `adapter::types::unidirectional::AIS` (Plug)   | **Stored value output (GETO)** – Sendet den gelesenen STRING‑Wert aus dem NVS über das AIS‑Protokoll. |

## Funktionsweise
1. **Initialisierung**  
   Ein Ereignis am `INIT`-Eingang startet die interne Logik. Der Baustein ruft den eingebetteten `NVS`‑Funktionsblock auf, der den nichtflüchtigen Speicher vorbereitet. Die mitgelieferten Daten (`QI`, `KEY`, `DEFAULT_VALUE`) werden an den internen Baustein weitergeleitet.

2. **Lesevorgang**  
   Nach erfolgreicher INIT‑Phase (Ereignis `INITO` des internen NVS) wird automatisch der `GET`‑Ereigniseingang des internen NVS aktiviert. Der gelesene Wert (oder der `DEFAULT_VALUE`, falls kein Eintrag existiert) wird über den `AIS_OUT`‑Adapter als `E1`‑Ereignis und `D1`‑Daten ausgegeben.

3. **Schreibvorgang**  
   Über den `AIS_IN`‑Adapter kann ein neuer Wert empfangen werden. Das assoziierte `SET`‑Ereignis (E1) wird auf den internen NVS‑Baustein geleitet, der den empfangenen Wert (D1) unter dem zuvor gesetzten `KEY` speichert. Die Bestätigung (`SETO`) wird wiederum über den `AIS_OUT`‑Adapter gesendet.

4. **Rückmeldung**  
   Sowohl nach dem Lesen als auch nach dem Schreiben gibt der Baustein den Status (`QO`, `STATUS`) sowie das `INITO`-Ereignis aus. Der Status kann für Fehlerdiagnosen genutzt werden.

## Technische Besonderheiten
- **NVS für ESP32** – Der Baustein ist speziell für den nichtflüchtigen Speicher des ESP32 ausgelegt und verwendet die entsprechende Treiber‑API.
- **Adapter‑Schnittstelle** – Die Kommunikation mit der Außenwelt erfolgt ausschließlich über AIS‑Adapter (unidirektional). Dies entkoppelt den Baustein von konkreten Bus‑ oder Applikationsprotokollen.
- **Automatische Leseoperation nach INIT** – Nach der Initialisierung wird unverzüglich ein Lesevorgang gestartet, sodass der gespeicherte Wert sofort am Ausgang bereitsteht.
- **Einheitlicher Status** – Alle relevanten Zustandsinformationen werden über die Ausgänge `QO` und `STATUS` zurückgemeldet.

## Zustandsübersicht
Der Baustein `NVS_AIS` selbst besitzt keine explizite Zustandsmaschine. Sein Verhalten wird vollständig durch den eingebetteten `NVS`‑Funktionsblock gesteuert, der die typischen Zustände eines NVS‑Treibers durchläuft (z. B. Initialisierung, Bereit, Fehler). Die Ereignisse `INIT` und `INITO` bilden den Start‑Stopp‑Zyklus ab; die Adapter‑Ereignisse `E1` leiten die Schreib‑/Leseanforderungen ein.

## Anwendungsszenarien
- **Konfigurationsspeicher** – Persistentes Ablegen von Geräteeinstellungen (z. B. Netzwerk‑Parameter, Betriebsmodi) als Zeichenketten.
- **Datenaustausch mit anderen Bausteinen** – Verwendung der AIS‑Adapter zur einfachen Einbindung in eine IEC‑61499‑Anwendung, ohne direkte Bus‑ oder Speicherzugriffe programmieren zu müssen.
- **Wiederherstellung nach Neustart** – Die Kombination aus INIT, automatischem Lesen und Default‑Werten stellt sicher, dass ein defnitiert initialisierter Zustand erreicht wird.

## Vergleich mit ähnlichen Bausteinen
- **`NVS` (direkt)**: Der direkte NVS‑Baustein bietet detailliertere Steuerungsmöglichkeiten (eigene Ereignisse für GET/SET), erfordert aber eine manuelle Verbindung der Schnittstellen. `NVS_AIS` vereinfacht die Anwendung durch die Einbettung der Lese‑/Schreiblogik und die standardisierten Adapter.
- **Weitere Speicher‑Bausteine (z. B. für SD‑Karte)**: Diese arbeiten meist mit anderen Protokollen (SPI, I²C) und bieten unterschiedliche Speicherschemata. `NVS_AIS` ist auf die spezifischen Eigenschaften des ESP32‑NVS optimiert (Schlüssel‑Wert‑Paare, geringe Latenz).

## Fazit
`NVS_AIS` ist ein praktischer Funktionsblock, der das Speichern und Laden von Zeichenketten im nichtflüchtigen Speicher des ESP32 kapselt und über eine saubere Adapter‑Schnittstelle bereitstellt. Durch die automatisierte Initialisierung und die Integration von Lese‑ und Schreibvorgängen eignet er sich besonders für Anwendungen, die eine einfache, zuverlässige Persistenz von Konfigurationsdaten benötigen. Die Adapter‑Anbindung ermöglicht eine lose Kopplung mit anderen Bausteinen und erhöht die Wiederverwendbarkeit in verschiedenen IEC‑61499‑Projekten.