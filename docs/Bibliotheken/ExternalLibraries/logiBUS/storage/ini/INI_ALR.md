# INI_ALR


![INI_ALR](./INI_ALR.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **INI_ALR** dient dem Lesen und Speichern von Gleitkommawerten des Typs LREAL aus bzw. in eine `settings.ini`-Datei. Er greift dabei auf eine Konfigurationsdatei zu, die über einen Abschnittsnamen (Section) und einen Schlüssel (Key) parametriert wird. Der Baustein kapselt die Nutzung des internen `INI`-Funktionsblocks und stellt zusätzlich eine standardisierte **ALR**-Adapter-Schnittstelle (unidirektional) zur Verfügung, über die Werte sowohl gesetzt als auch gelesen werden können.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ   | Kommentar                                    | Mit Variablen                        |
|----------|-------|----------------------------------------------|--------------------------------------|
| INIT     | EInit | Initialisiert den Baustein und löst Lesen aus| QI, SECTION, KEY, DEFAULT_VALUE      |

### **Ereignis-Ausgänge**

| Ereignis | Typ   | Kommentar                       | Mit Variablen |
|----------|-------|---------------------------------|---------------|
| INITO    | EInit | Bestätigt die Initialisierung   | QO, STATUS    |

### **Daten-Eingänge**

| Name          | Typ    | Kommentar                                                 |
|---------------|--------|-----------------------------------------------------------|
| QI            | BOOL   | Event‑Eingangs‑Qualifizierer (Freigabe)                   |
| SECTION       | STRING | Abschnittsname in der INI‑Datei                           |
| KEY           | STRING | Schlüsselname innerhalb des Abschnitts                    |
| DEFAULT_VALUE | LREAL  | Rückfallwert, falls der Schlüssel in der INI‑Datei fehlt  |

### **Daten-Ausgänge**

| Name   | Typ    | Kommentar                        |
|--------|--------|----------------------------------|
| QO     | BOOL   | Event‑Ausgangs‑Qualifizierer     |
| STATUS | STRING | Statusmeldung (z. B. Fehlertext) |

### **Adapter**

| Adapter  | Typ                               | Kommentar                                              |
|----------|-----------------------------------|--------------------------------------------------------|
| ALR_IN   | adapter::types::unidirectional::ALR| Socket – Wert zum Speichern (SET)                     |
| ALR_OUT  | adapter::types::unidirectional::ALR| Plug – gelesener Wert (GET)/Bestätigung               |

## Funktionsweise

1. **Initialisierung und erstes Lesen**  
   Ein Ereignis am Eingang `INIT` triggert die Initialisierung des internen `INI`-Bausteins. Die Parameter `QI`, `SECTION`, `KEY` und `DEFAULT_VALUE` werden an den `INI`‑Baustein weitergeleitet. Nach dessen Quittierung (`INITO`) wird automatisch der GET‑Vorgang des `INI`-Bausteins ausgelöst. Der gelesene Wert erscheint am Datenausgang des Adapters `ALR_OUT.D1` und wird gleichzeitig über das Ereignis `ALR_OUT.E1` signalisiert. Die Ausgänge `QO` und `STATUS` des `INI`-Bausteins werden direkt an die gleichnamigen Ausgänge des `INI_ALR` durchgereicht.

2. **Schreiben über ALR-IN**  
   Ein Set‑Ereignis am Adapter‑Socket `ALR_IN.E1` wird an den SET-Eingang des internen `INI`-Bausteins weitergeleitet. Der zu speichernde Wert liegt an `ALR_IN.D1` und wird über `INI.VALUE` gesetzt. Nach erfolgreichem Schreiben quittiert der `INI`-Baustein mit `SETO`, was wiederum `ALR_OUT.E1` auslöst.

3. **Lesen über ALR-IN** (implizit)  
   Über die initiale GET‑Sequenz und die Weiterleitung von `GETO` steht stets der aktuell gelesene Wert am Ausgang `ALR_OUT` zur Verfügung. Ein erneutes Lesen kann durch einen erneuten `INIT`‑Impuls angestoßen werden.

## Technische Besonderheiten

- **Wiederverwendung** des standardisierten `INI`-Bausteins (`eclipse4diac::storage::INI`) für den Dateizugriff.
- **ALR-Adapter‑Schnittstelle** – erlaubt die unidirektionale Kopplung mit anderen Bausteinen, die denselben Adaptertyp verwenden. Dies vereinfacht die Integration in modulare Steuerungsapplikationen.
- **Asynchrone Verarbeitung**: Lese‑ und Schreibvorgänge werden ereignisgesteuert und asynchron durchgeführt; die Quittierung erfolgt über die entsprechenden Ereignisausgänge.
- **Konform zum Standard IEC 61499‑2** – alle Ein‑ und Ausgänge sind mit Standardtypen definiert.
- **Fehlerbehandlung** erfolgt über den STATUS‑Ausgang (z. B. bei fehlender Datei oder fehlerhaften Daten).

## Zustandsübersicht

Der `INI_ALR` selbst besitzt keine eigenen Zustandsautomaten. Die Zustandsverwaltung wird vollständig durch den internen `INI`-Baustein realisiert. Typische Phasen sind:
- **Idle** – Warten auf ein INIT-Ereignis.
- **Initialize** – Verarbeitung von INIT, Datenweiterleitung an `INI`.
- **Ready/Lese‑Bereit** – nach erfolgreicher INIT‑Quittierung ist ein Lese‑Ergebnis verfügbar.
- **Schreib‑Vorgang** – ausgelöst durch `ALR_IN.E1`.
- **Fehlerzustand** – bei fehlerhaften INI‑Zugriffen wird STATUS entsprechend gesetzt.

## Anwendungsszenarien

- **Maschinenkonfiguration** – Laden von Parametern (z. B. Maximalgeschwindigkeit, Grenzwerte) aus einer zentralen INI‑Konfigurationsdatei.
- **Kalibrierwerte** – Speichern und Auslesen von Kalibrierdaten in der Automatisierungstechnik.
- **Schnittstelle zu ALR‑basierten Komponenten** – wenn ein Baustein einen LREAL‑Wert über einen ALR‑Adapter bereitstellt oder erwartet, kann `INI_ALR` als Bindeglied zur persistenten Speicherung eingesetzt werden.

## Vergleich mit ähnlichen Bausteinen

| Baustein   | Beschreibung                                                       | Vorteil von INI_ALR                            |
|------------|--------------------------------------------------------------------|-------------------------------------------------|
| `INI`      | Direkter Zugriff auf INI‑Dateien (ohne ALR)                        | Fehlende Adapter‑Schnittstelle, manuelle Kopplung nötig |
| `INI_ALR`  | Kapselt `INI` und stellt ALR‑Adapter‑Schnittstelle bereit          | Einfache Integration in ALR‑basierte Architekturen |

Der `INI_ALR` kombiniert die bewährte INI‑Datei‑Funktionalität mit einer standardisierten Adapter‑Schnittstelle und reduziert dadurch den Aufwand für die Einbindung in ein diensteorientiertes Steuerungssystem.

## Fazit

Der `INI_ALR` ist ein praxisorientierter Funktionsblock, der den Zugriff auf `settings.ini` für LREAL‑Daten um eine flexible Adapter‑Schnittstelle erweitert. Er eignet sich besonders für Anwendungen, die eine einheitliche ALR‑basierte Kommunikation erfordern und gleichzeitig eine einfache, dateibasierte Persistenz benötigen. Durch die Kapselung des komplexen `INI`‑Bausteins und die automatische Verkettung von Ereignis‑ und Datenflüssen wird der Entwicklungsaufwand reduziert und die Wiederverwendbarkeit erhöht.