# INI_AR


![INI_AR](./INI_AR.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock INI_AR dient zum Laden und Speichern von REAL-Daten aus einer settings.ini-Datei. Er greift über einen Sektions- und Schlüsselnamen auf die Konfigurationsdatei zu und stellt die gelesenen bzw. zu speichernden Werte über einen unidirektionalen Adapter zur Verfügung. Dies ermöglicht eine flexible Einbindung in modulare Speicher- und Steuerungsarchitekturen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- `INIT` (EInit): Service-Initialisierung. Löst das Laden des aktuellen Wertes aus und verarbeitet die zugehörigen Daten-Eingänge.

### **Ereignis-Ausgänge**
- `INITO` (EInit): Bestätigung der Initialisierung. Wird nach erfolgreichem Lese- oder Schreibvorgang gesendet.

### **Daten-Eingänge**
- `QI` (BOOL): Qualifizierer für den Ereignis-Eingang.
- `SECTION` (STRING): Name des Abschnitts in der INI-Datei.
- `KEY` (STRING): Name des Schlüssels innerhalb des Abschnitts.
- `DEFAULT_VALUE` (REAL): Wert, der verwendet wird, falls kein Eintrag in der settings.ini gefunden wird.

### **Daten-Ausgänge**
- `QO` (BOOL): Qualifizierer für den Ereignis-Ausgang.
- `STATUS` (STRING): Statusmeldung des Dienstes (z. B. Erfolg, Fehler).

### **Adapter**
- **AR_OUT** (Plug, Typ `adapter::types::unidirectional::AR`): Adapter-Ausgang, über den der gelesene Wert (GETO) an andere Bausteine gesendet wird.
- **AR_IN** (Socket, Typ `adapter::types::unidirectional::AR`): Adapter-Eingang, über den ein zu speichernder Wert (SET) empfangen werden kann.

## Funktionsweise
Nach einem INIT-Impuls wird der im Inneren liegende Baustein `INI` (vom Typ `eclipse4diac::storage::INI`) angestoßen. Dieser liest den aktuellen Wert aus der angegebenen Sektion und dem Schlüssel aus der settings.ini-Datei. Falls kein Eintrag existiert, wird `DEFAULT_VALUE` verwendet. Nach Abschluss des Lesevorgangs wird das Ereignis GET ausgelöst, und der gelesene Wert wird über den Adapter-Ausgang `AR_OUT` (Ereignis GETO, Daten VALUEO) weitergegeben.

Gleichzeitig kann über den Adapter-Eingang `AR_IN` ein neuer Wert (Ereignis E1, Daten D1) empfangen werden. Dieser löst im INI-Baustein das Ereignis SET aus, wodurch der Wert in die INI-Datei geschrieben wird. Nach dem Schreiben erfolgt eine Bestätigung über `SETO`, die ebenfalls an den Adapter-Ausgang weitergeleitet wird. Die Ereignisse GETO und SETO sind auf demselben Ausgangs-Event `AR_OUT.E1` zusammengeführt. Der qualifizierte Ausgang `QO` und `STATUS` werden direkt vom internen INI-Baustein übernommen.

## Technische Besonderheiten
- Der Baustein verwendet den internen INI-Funktionsblock aus der Bibliothek `eclipse4diac::storage`.
- Die Adapter `AR_IN` und `AR_OUT` müssen dem Typ `adapter::types::unidirectional::AR` entsprechen.
- Der Baustein ist unter der Eclipse Public License 2.0 (EPL-2.0) lizenziert.
- Autor: Franz Höpfinger, Version 1.0, Stand: 24.04.2026.

## Zustandsübersicht
Der Baustein besitzt keinen expliziten Zustandsautomaten. Die Logik wird vollständig über die Ereignisverkettung des internen INI-Bausteins gesteuert:
- Nach `INIT` wird der Wert gelesen (GET).
- Jeder `SET`-Impuls über `AR_IN` schreibt einen neuen Wert in die INI-Datei.

## Anwendungsszenarien
- Persistente Speicherung von Konfigurationsparametern (REAL) in einer INI-Datei für Automatisierungsprojekte.
- Austausch von Laufzeitparametern zwischen verschiedenen Funktionsblöcken über die Adapter-Schnittstelle.
- Initialisieren von Anlagenparametern aus einer zentralen Konfigurationsdatei.

## Vergleich mit ähnlichen Bausteinen
- **Standard INI-Baustein** (`INI`): Bietet direkten Lese-/Schreibzugriff auf INI-Dateien über Daten-Eingänge und -Ausgänge ohne Adapter.
- **INI_AR** ergänzt diesen um die Adapter-Schnittstelle, sodass Werte modular über Ereignisse und Daten an andere Bausteine weitergegeben werden können, ohne dass die gesamte Logik in einem Block zusammengefasst werden muss.
- Für andere Datenformate (JSON, XML) existieren analoge Bausteine, die jedoch andere Bibliotheken nutzen.

## Fazit
Der Funktionsblock INI_AR kapselt den Zugriff auf eine INI-Datei für REAL-Werte und bietet gleichzeitig eine standardisierte Adapter-Schnittstelle zur Integration in verteilte Steuerungsnetzwerke. Er vereinfacht das Speichern und Laden von Konfigurationsdaten und erlaubt eine klare Trennung zwischen Speicherlogik und Datenflüssen.