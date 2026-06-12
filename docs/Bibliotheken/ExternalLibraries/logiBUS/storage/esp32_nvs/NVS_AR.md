# NVS_AR




![NVS_AR](./NVS_AR.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock `NVS_AR` dient zum Laden und Speichern von REAL-Daten in einem nichtflüchtigen Speicher (Non-Volatile Storage, NVS) anhand eines Schlüssels (Key). Er stellt über zwei AR-Adapter-Schnittstellen eine unidirektionale Kommunikation mit anderen IEC‑61499-Bausteinen bereit. Der Baustein kapselt den internen `NVS`-Baustein und erweitert dessen Funktionalität um eine standardisierte Adapter-Anbindung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **INIT** (EInit) – Initialisiert den Baustein. Beim Eintreten dieses Ereignisses werden die Daten-Eingänge `QI`, `KEY` und `DEFAULT_VALUE` übernommen.

### **Ereignis-Ausgänge**

- **INITO** (EInit) – Bestätigt den erfolgreichen Abschluss der Initialisierung. Nach diesem Ereignis sind die Ausgänge `QO` und `STATUS` gültig.

### **Daten-Eingänge**

- **QI** (BOOL) – Eingangsqualifizierer; steuert die Ausführung der Initialisierung.
- **KEY** (STRING) – Schlüsselname, unter dem der Wert im NVS gespeichert/abgerufen wird.
- **DEFAULT_VALUE** (REAL) – Standardwert, der zurückgegeben wird, falls kein Eintrag mit dem angegebenen Schlüssel im NVS existiert.

### **Daten-Ausgänge**

- **QO** (BOOL) – Ausgangsqualifizierer; zeigt den Erfolg der Initialisierung an.
- **STATUS** (STRING) – Statusmeldung zur Fehlerdiagnose oder Bestätigung.

### **Adapter**

- **AR_IN** (Adapter vom Typ `adapter::types::unidirectional::AR`) – Empfängt einen zu speichernden Wert (SET-Ereignis und Daten).
- **AR_OUT** (Adapter vom Typ `adapter::types::unidirectional::AR`) – Stellt den gelesenen Wert für andere Bausteine bereit (GETO-Ereignis und Daten).

## Funktionsweise

Der Baustein arbeitet wie folgt:

1. **Initialisierung**: Ein Ereignis an `INIT` startet die Initialisierung des internen `NVS`-Bausteins. Die Eingänge `QI`, `KEY` und `DEFAULT_VALUE` werden an `NVS` weitergeleitet.
2. **Nach Initialisierung**: Sobald `NVS` die Initialisierung abschließt (Ereignis `INITO`), wird automatisch ein **Lesebefehl** (`GET`) an `NVS` gesendet. Der gelesene Wert (oder der Standardwert) wird anschließend über den Adapterausgang `AR_OUT` ausgegeben.
3. **Speichern**: Ein über den Adaptereingang `AR_IN` eingehendes Ereignis (`AR_IN.E1`) löst einen **Speicherbefehl** (`SET`) im internen `NVS` aus. Der zu speichernde Wert wird aus dem Adapterdatenkanal (`AR_IN.D1`) übernommen.
4. **Rückmeldung**: Sowohl nach einem Lese- als auch nach einem Speichervorgang wird das Ergebnis (Erfolg/Fehler) über das Adapterereignis `AR_OUT.E1` und über die Datenausgänge `QO`/`STATUS` zurückgemeldet.

## Technische Besonderheiten

- Der Baustein verwendet den unidirektionalen AR-Adapter, der eine lose Kopplung zwischen Funktionsblöcken ermöglicht.
- Er ist speziell für REAL-Daten ausgelegt; andere Datentypen können nicht verarbeitet werden.
- Die Implementierung basiert auf dem generischen `NVS`-Baustein der Bibliothek `logiBUS::storage::esp32_nvs`.
- Die Ereignissteuerung stellt sicher, dass nach der Initialisierung automatisch der aktuelle Wert aus dem NVS gelesen und bereitgestellt wird.

## Zustandsübersicht

Der `NVS_AR`-Baustein verfügt über keine explizite Zustandsmaschine in der XML-Definition. Das funktionale Verhalten ergibt sich aus den Ereignisverkettungen:

- **Ruhezustand**: Der Baustein wartet auf ein Ereignis an `INIT` oder `AR_IN.E1`.
- **Initialisierungsphase**: Nach `INIT` wird der interne `NVS`-Baustein gestartet. In dieser Phase sind die Ausgänge noch nicht gültig.
- **Betriebsphase**: Nach `INITO` ist der Baustein bereit, Werte zu lesen (automatisch) und über `AR_IN` gespeichert zu bekommen.

## Anwendungsszenarien

- **Konfigurationsspeicher**: Speichern und Abrufen von REAL-Konfigurationsparametern (z. B. Grenzwerte, Faktoren) in einem ESP32‑NVS.
- **Kalibrierdaten**: Hinterlegen von Kalibrierwerten für Sensorik oder Aktorik.
- **Persistente Betriebsdaten**: Ablegen von Zählwerten oder Summen, die über Netzausfälle hinweg erhalten bleiben sollen.

## Vergleich mit ähnlichen Bausteinen

| Merkmal | `NVS_AR` | Direkter `NVS`-Baustein |
|---------|-----------|-------------------------|
| Schnittstelle | AR-Adapter (unidirektional) | Standard‑Ereignis-/Dateneingänge |
| Einsatzzweck | Einfache Einbindung in adapterbasierte Netzwerke | Flexibel, aber aufwändigere Verdrahtung |
| Datentyp | REAL | Mehrere Typen (über generischen Parameter) |

Der `NVS_AR` vereinfacht die Integration, indem er die Adapter‑Anbindung standardisiert, während der reine `NVS`-Baustein eine breitere Typenunterstützung bietet.

## Fazit

Der `NVS_AR`-Funktionsblock bietet eine kompakte und adapterbasierte Lösung zum Laden und Speichern von REAL-Daten im nichtflüchtigen Speicher. Durch die Verwendung des AR-Adapters lässt er sich besonders leicht in bestehende IEC‑61499‑Netzwerke einfügen, ohne auf detaillierte Verbindungen achten zu müssen. Die automatische initiale Auslese nach der Initialisierung erleichtert die Anwendung in typischen Szenarien der Echtzeitsteuerung.