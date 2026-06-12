# INI_AUDI


![INI_AUDI](./INI_AUDI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **INI_AUDI** ermöglicht das Lesen und Speichern von UDINT-Daten aus einer `settings.ini`-Datei. Dabei wird der Zugriff auf die Datei über einen internen `INI`-Baustein realisiert. Die Kommunikation mit der Umgebung erfolgt über zwei **AUDI-Adapter** (unidirektional), die als Plug (`AUDI_OUT`) und Socket (`AUDI_IN`) ausgeführt sind. Dies erlaubt eine modulare Anbindung an andere Bausteine, die über denselben Adaptertyp verfügen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Name  | Typ   | Kommentar                         |
|-------|-------|-----------------------------------|
| INIT  | EInit | Service Initialization            |

### **Ereignis-Ausgänge**
| Name  | Typ   | Kommentar                        |
|-------|-------|----------------------------------|
| INITO | EInit | Initialization Confirm           |

### **Daten-Eingänge**
| Name           | Typ    | Kommentar                                           |
|----------------|--------|-----------------------------------------------------|
| QI             | BOOL   | Event Input Qualifier                               |
| SECTION        | STRING | Section name in der settings.ini                    |
| KEY            | STRING | Key name in der settings.ini                        |
| DEFAULT_VALUE  | UDINT  | Rückfallwert, falls der Schlüssel nicht gefunden wird |

### **Daten-Ausgänge**
| Name   | Typ    | Kommentar        |
|--------|--------|------------------|
| QO     | BOOL   | Output Qualifier |
| STATUS | STRING | Service Status   |

### **Adapter**
| Name     | Typ      | Richtung       | Kommentar                       |
|----------|----------|----------------|---------------------------------|
| AUDI_OUT | AUDI     | Plug (Ausgang) | Ausgabe des gelesenen Werts     |
| AUDI_IN  | AUDI     | Socket (Eingang)| Eingang des zu speichernden Werts |

## Funktionsweise
Der Baustein arbeitet mit dem internen `INI`-Funktionsblock zusammen. Die grundlegende Abfolge ist:

1. **Initialisierung (`INIT`-Ereignis)**  
   - Die mit `INIT` verbundenen Eingabedaten (`QI`, `SECTION`, `KEY`, `DEFAULT_VALUE`) werden an den internen `INI`-Baustein weitergeleitet.
   - `INI` wird gestartet und bestätigt mit `INITO`.

2. **Lesen eines Werts**  
   - Nach der INIT-Bestätigung wird automatisch der `GET`-Befehl des `INI`-Bausteins ausgelöst.
   - Der gelesene Wert (oder der `DEFAULT_VALUE`) wird über `INI.VALUEO` an den Adapter `AUDI_OUT.D1` ausgegeben.
   - Gleichzeitig wird das Ereignis `AUDI_OUT.E1` gesendet, um den angeschlossenen Baustein zu benachrichtigen.

3. **Schreiben eines Werts**  
   - Wird über den Adapter `AUDI_IN` ein Ereignis `E1` mit einem Datenwert `D1` empfangen, so leitet `INI_AUDI` diesen an den `INI`-Baustein als `SET`-Befehl weiter.
   - Der interne `INI`-Baustein speichert den Wert in der INI-Datei unter der angegebenen Section und Key und quittiert mit `SETO`.
   - Das Quittungsereignis wird über `AUDI_OUT.E1` ausgegeben.

4. **Rückmeldung**  
   - Die Statusausgänge `QO` und `STATUS` werden vom internen `INI`-Baustein direkt übernommen und stehen am Ausgang zur Verfügung.

## Technische Besonderheiten
- Der Baustein verwendet den **Adapter `adapter::types::unidirectional::AUDI`**, der speziell für die gerichtete Kommunikation von Werten und Ereignissen ausgelegt ist.
- Die Daten werden als **UDINT (Unsigned Double Integer)** verarbeitet, was eine effiziente Speicherung und Übertragung ermöglicht.
- Der interne `INI`-Baustein stammt aus der Bibliothek `eclipse4diac::storage` und unterstützt die Standard-INI-Dateiformate.
- Der Fallback-Mechanismus über `DEFAULT_VALUE` stellt sicher, dass auch bei fehlenden Einträgen in der INI-Datei ein definierter Wert zurückgegeben wird.

## Zustandsübersicht
Da der Baustein ereignisgesteuert arbeitet, ergeben sich folgende logische Zustände:

- **Idle**: Warten auf ein `INIT`-Ereignis.
- **Initialisieren**: Nach `INIT` – interne Weiterleitung an den INI-Baustein.
- **Lesen** (automatisch nach `INITO`): Der `INI`-Baustein führt einen GET-Befehl aus.
- **Schreiben**: Bei Empfang eines Ereignisses über `AUDI_IN.E1`.
- **Bestätigen**: Ausgabe des entsprechenden OUT-Ereignisses und Aktualisierung der Status-Ausgänge.

Der Baustein ist zustandslos im Sinne eines kontinuierlichen Datenflusses; jede Aktion wird durch ein Ereignis getriggert und synchron beendet.

## Anwendungsszenarien
- **Konfigurationsverwaltung** in Automatisierungssystemen: Lesen von Einstellungen (z. B. Grenzwerte, Parameter) aus einer zentralen `settings.ini` und Zurückschreiben geänderter Werte.
- **Adapterbasierte Sensor-/Aktor-Kopplung**: Anbindung eines Bausteins, der über den AUDI-Adapter Werte liest oder setzt, ohne die Dateizugriffslogik selbst implementieren zu müssen.
- **Persistente Datenspeicherung**: Speichern von Zählerständen oder Maschinenzuständen in einer INI-Datei bei gleichzeitiger Kommunikation über standardisierte Adapter.

## Vergleich mit ähnlichen Bausteinen
- **Gegenüber reinem `INI`-Baustein**: `INI_AUDI` kapselt die Adapter-Kommunikation und bietet eine höhere Abstraktion. Der Anwender muss nicht direkt mit Ereignissen und Datenverbindungen zwischen mehreren Komponenten hantieren.
- **Gegenüber Bausteinen mit anderen Datentypen**: Der vorliegende Baustein ist auf `UDINT` spezialisiert. Für andere Datentypen (z. B. `STRING`, `REAL`) sind separate Varianten erforderlich. Die grundlegende Struktur bleibt jedoch gleich.
- **Vorteil**: Durch die Verwendung von Adaptern (AUDI) kann der Baustein leicht gegen andere Schnittstellen ausgetauscht werden, sofern diese denselben Adaptertyp implementieren.

## Fazit
Der `INI_AUDI`-Funktionsblock stellt eine kompakte und wiederverwendbare Lösung dar, um UDINT-Werte aus einer INI-Datei zu lesen und zu schreiben, wobei die Ankopplung an die Umgebung über standardisierte AUDI-Adapter erfolgt. Durch die klare Trennung von Initialisierung, Lesen und Schreiben sowie die Einbindung eines Fallback-Werts eignet er sich besonders für robuste Konfigurations- und Datenspeicherungsaufgaben in Automatisierungsumgebungen. Die einfache Struktur erleichtert die Integration in komplexe 4diac-Netzwerke.