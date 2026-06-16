# NVS_AX2


![NVS_AX2](./NVS_AX2.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **NVS_AX2** dient dem Laden und Speichern von REAL-Daten im nichtflüchtigen Speicher (NVS) eines ESP32 über einen Adapter. Er kapselt die Initialisierung und den Zugriff auf einen einzelnen NVS-Eintrag, der über einen Schlüssel (KEY) identifiziert wird. Der FB bietet eine initialisierende Ereignisschnittstelle und eine bidirektionale Adapter-Schnittstelle, über die extern auf den gespeicherten Wert zugegriffen werden kann. Der Baustein ist nach IEC 61499 modelliert und für den Einsatz in verteilten Automatisierungssystemen optimiert.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Ereignis | Typ    | Kommentar                        | Mitgeführte Variablen     |
|----------|--------|----------------------------------|---------------------------|
| `INIT`   | EInit  | Service Initialization           | QI, KEY, DEFAULT_VALUE    |

### **Ereignis-Ausgänge**

| Ereignis | Typ    | Kommentar                        | Mitgeführte Variablen     |
|----------|--------|----------------------------------|---------------------------|
| `INITO`  | EInit  | Initialization Confirm           | QO, STATUS                |

### **Daten-Eingänge**

| Name           | Typ    | Kommentar                                               |
|----------------|--------|---------------------------------------------------------|
| `QI`           | BOOL   | Event Input Qualifier (Freigabe der Initialisierung)    |
| `KEY`          | STRING | Schlüsselname für den NVS-Eintrag                       |
| `DEFAULT_VALUE`| BOOL   | Standardwert, falls der Schlüssel im NVS nicht existiert (Voreinstellung: FALSE) |

### **Daten-Ausgänge**

| Name     | Typ    | Kommentar                        |
|----------|--------|----------------------------------|
| `QO`     | BOOL   | Event Output Qualifier           |
| `STATUS` | STRING | Dienststatus                     |

### **Adapter**

| Adapter | Typ                                       | Kommentar      |
|---------|-------------------------------------------|----------------|
| `VAL`   | `adapter::types::bidirectional::AX2` (Socket) | Wert (REAL)    |

Der Adapter **VAL** stellt eine bidirektionale Verbindung zu einem externen Baustein her. Über diesen Adapter kann der gespeicherte REAL-Wert gelesen und geschrieben werden. Der Adaptertyp AX2 definiert ein Ereignis- und Datenprotokoll für den Datentransfer.

## Funktionsweise
1. **Initialisierung**: Ein Ereignis am Eingang `INIT` löst die Initialisierung des internen NVS-Bausteins aus. Dabei werden `QI`, `KEY` und `DEFAULT_VALUE` übergeben. Nach erfolgreicher Initialisierung wird das Ereignis `INITO` am Ausgang gesendet. Gleichzeitig wird automatisch ein Lesevorgang (GET) für den angegebenen Schlüssel angestoßen.

2. **Wert auslesen**: Der gelesene Wert wird über den Adapter `VAL` als `DI1` (Datenausgang des Adapters) ausgegeben und ein Ereignis `EI1` am Adapter ausgelöst. Der Ausgang `QO` und `STATUS` spiegeln das Ergebnis des Lesevorgangs wider.

3. **Wert speichern**: Ein externer Baustein kann über den Adapter `VAL` ein Ereignis `EO1` senden, um einen neuen Wert (bereitgestellt als `DO1`) in den NVS zu schreiben. Der interne NVS-Baustein führt dann einen SET-Vorgang durch und bestätigt über `SETO`. Anschließend wird das Ereignis `EI1` am Adapter ausgelöst, um dem Sender den Abschluss zu signalisieren.

4. **Statussignalisierung**: Die Ausgänge `QO` und `STATUS` werden nach jedem Lese- oder Schreibvorgang aktualisiert und mit dem Ereignis `INITO` ausgegeben.

## Technische Besonderheiten
- **Persistenz auf ESP32**: Der FB nutzt den NVS (Non-Volatile Storage) des ESP32-Mikrocontrollers, um Daten dauerhaft zu speichern. Die Daten bleiben auch nach einem Neustart erhalten.
- **Adapter-basierte Kommunikation**: Die Schnittstelle zum Anwender erfolgt über einen bidirektionalen Adapter (AX2), der eine flexible und standardisierte Anbindung an andere Bausteine ermöglicht. Der Datentyp ist auf REAL festgelegt.
- **Fehlerbehandlung**: Über den Ausgang `STATUS` können Fehlermeldungen (z. B. NVS-Fehler, fehlender Speicherplatz) abgefragt werden. Der Ausgang `QO` zeigt den Erfolg der Operation an.
- **Standardkonformität**: Der FB ist gemäß IEC 61499 implementiert und verwendet die Bausteinklasse `logiBUS::storage::esp32_nvs::NVS`.

## Zustandsübersicht
Der FB besitzt keinen expliziten Zustandsautomaten, jedoch ergibt sich folgender logischer Ablauf:

1. **Idle**: Kein `INIT`-Ereignis empfangen.
2. **Initialisierend**: Nach `INIT` – der interne NVS-Baustein wird gestartet und ein GET ausgeführt.
3. **Bereit**: Nach `INITO` – der Baustein wartet auf Lese-/Schreibanforderungen über den Adapter.
4. **Schreibvorgang**: Ein `EO1`-Ereignis am Adapter löst einen SET-Vorgang aus.
5. **Lesen**: Ein erneutes Lesen kann nur durch erneutes `INIT` oder interne Logik erfolgen (der Baustein liest einmalig beim Start und danach nur bei Schreibvorgängen).

## Anwendungsszenarien
- **Konfigurationsspeicherung**: Speichern von Benutzereinstellungen (z. B. Sollwerte, Betriebsmodi) auf einem ESP32-Gerät.
- **Kalibrierdaten**: Dauerhafte Ablage von Kalibrierwerten für Sensoren.
- **Zustandsspeicherung**: Speichern des letzten Betriebszustands (z. B. Zählerstände, Schaltstellungen) bei Spannungsausfall.
- **Datenprotokollierung**: Gezieltes Abspeichern einzelner Messwerte über den Adapter.

## Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu einfachen Speicherbausteinen (z. B. `CTUO` oder generischen `R_TRIG`-Bausteinen) ist `NVS_AX2` speziell für die persistente Speicherung auf ESP32-Hardware ausgelegt. Während andere FBs nur flüchtige Daten verarbeiten, gewährleistet dieser Baustein einen dauerhaften Datenerhalt. Die Verwendung eines Adapters bietet mehr Flexibilität als ein fester Ein-/Ausgang, da der Datentyp und die Kommunikationsrichtung klar definiert sind. Im Vergleich zu direkten NVS-API-Aufrufen in IEC 61499 vereinfacht der FB die Integration durch die vollständig deklarative Beschreibung.

## Fazit
Der Funktionsblock `NVS_AX2` ist eine effiziente und standardkonforme Lösung zum persistenten Speichern eines REAL-Werts im NVS eines ESP32. Die klare Schnittstellenstruktur mit Ereignissteuerung und bidirektionalem Adapter erleichtert die Einbindung in komplexe Automatisierungsprojekte. Dank der integrierten Initialisierung und Fehlerprotokollierung ist der Baustein robust und für den industriellen Einsatz geeignet.