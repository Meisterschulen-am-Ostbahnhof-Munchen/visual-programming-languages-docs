# INI_AUI


![INI_AUI](./INI_AUI.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `INI_AUI` dient zum Lesen und Speichern von **UINT-Daten** (genauer: `UDINT`-Werte) aus einer `settings.ini`-Datei. Die Parameter **Abschnitt (SECTION)** und **Schlüssel (KEY)** bestimmen, welcher Wert ausgelesen wird. Zusätzlich kann ein **Standardwert (DEFAULT_VALUE)** angegeben werden, falls kein Eintrag in der INI-Datei existiert. Der FB bietet sowohl einen direkten Zugriff über seine Eingänge als auch eine **Adapter-Schnittstelle (AUI)** für die unidirektionale Kommunikation mit anderen Bausteinen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ   | Kurzbeschreibung                                               |
|----------|-------|---------------------------------------------------------------|
| INIT     | EInit | Service-Initialisierung: Löst das Laden des Wertes aus der INI-Datei aus |

### **Ereignis-Ausgänge**

| Ereignis | Typ   | Kurzbeschreibung                                               |
|----------|-------|---------------------------------------------------------------|
| INITO    | EInit | Bestätigung der Initialisierung (wird nach Abschluss von Lese-/Schreiboperationen gesendet) |

### **Daten-Eingänge**

| Name          | Typ    | Kurzbeschreibung                                               |
|---------------|--------|---------------------------------------------------------------|
| QI            | BOOL   | Qualifizierer für den Ereigniseingang (aktiviert die Verarbeitung) |
| SECTION       | STRING | Name des Abschnitts in der `settings.ini` (z. B. `[MySection]`) |
| KEY           | STRING | Schlüsselname innerhalb des Abschnitts                         |
| DEFAULT_VALUE | UDINT  | Wert, der zurückgegeben wird, wenn kein Eintrag existiert      |

### **Daten-Ausgänge**

| Name   | Typ    | Kurzbeschreibung                                               |
|--------|--------|---------------------------------------------------------------|
| QO     | BOOL   | Qualifizierer für den Ereignisausgang (zeigt erfolgreiche Ausführung an) |
| STATUS | STRING | Statusmeldung (z. B. Fehler oder Erfolg)                       |

### **Adapter**

| Richtung  | Adaptertyp                          | Kurzbeschreibung                                                                 |
|-----------|-------------------------------------|---------------------------------------------------------------------------------|
| Plug      | `adapter::types::unidirectional::AUI` | **Ausgang (OUT):** Stellt den gelesenen/geschriebenen Wert über den Adapter bereit |
| Socket    | `adapter::types::unidirectional::AUI` | **Eingang (IN):** Nimmt den zu speichernden Wert über den Adapter entgegen       |

## Funktionsweise

Der `INI_AUI`-FB kapselt einen internen `INI`-Funktionsblock (`eclipse4diac::storage::INI`). Die wesentlichen Abläufe sind:

1. **Lesen eines Wertes**  
   - Ein **INIT**-Ereignis am Eingang löst den internen `INI.INIT` aus.  
   - Die Daten `QI`, `SECTION`, `KEY` und `DEFAULT_VALUE` werden an den `INI`-FB weitergeleitet.  
   - Nach erfolgreicher Verarbeitung sendet `INI.INITO` das Bestätigungsereignis und löst intern `INI.GET` aus, um den Wert aus der Datei zu laden.  
   - Der gelesene Wert erscheint an `INI.VALUEO` und wird über den **AUI_OUT**-Adapter (Plug) als `D1` ausgegeben.  
   - Gleichzeitig werden `QO` und `STATUS` vom internen FB übernommen.

2. **Schreiben eines Wertes**  
   - Ein Ereignis am **AUI_IN.Socket** (über den Eingangsadapter) löst den internen `INI.SET` aus.  
   - Der über den Adapter (D1) bereitgestellte Wert wird an `INI.VALUE` übergeben und in die `settings.ini` geschrieben.  
   - Nach dem Schreiben sendet `INI.SETO` das Bestätigungsereignis, das über den **AUI_OUT.Plug** als `E1` ausgegeben wird.  
   - Auch hier werden die Ausgänge `QO` und `STATUS` aktualisiert.

> **Hinweis:** Der Adapter **AUI_IN** dient als Socket (entgegennehmend), **AUI_OUT** als Plug (bereitstellend). Beide verwenden den gleichen unidirektionalen AUI-Typ.

## Technische Besonderheiten

- **Adapterbasierte Kommunikation:** Der FB ermöglicht den Austausch von Konfigurationsdaten über einen unidirektionalen Adapter (AUI), ohne dass direkte Datenverbindungen nötig sind. Dies vereinfacht die Modulkommunikation in verteilten Systemen.  
- **Dualer Betrieb:** Der Wert kann sowohl über die klassischen Dateneingänge (`SECTION`, `KEY`, `DEFAULT_VALUE`) als auch über den Adapter (`AUI_IN.D1`) festgelegt werden.  
- **Standardwert:** Fehlt ein Eintrag in der INI-Datei, wird `DEFAULT_VALUE` verwendet – dies verhindert undefinierte Zustände.  
- **Statusinformation:** Über `STATUS` und `QO` kann der Anwender den Erfolg jeder Operation prüfen.  

## Zustandsübersicht

Der Funktionsblock `INI_AUI` besitzt **keinen eigenen Zustandsautomaten**. Die gesamte Ablaufsteuerung wird durch den integrierten `INI`-FB und die definierten Ereignisverbindungen (z. B. INIT → INI.INIT, INI.INITO → INITO, INI.INITO → INI.GET) realisiert. Der FB arbeitet daher streng ereignisgesteuert und führt die Lese-/Schreiboperationen sequenziell aus.

## Anwendungsszenarien

- **Parameterverwaltung** in modularen Automatisierungssystemen, bei denen mehrere Komponenten über einen Adapter auf gemeinsame Konfigurationsdaten zugreifen.  
- **Initialisierung** von Steuerungsfunktionen mit einem Standardwert, der bei Bedarf aus einer INI-Datei überschrieben wird.  
- **Austausch von Einstellungen** zwischen verschiedenen Funktionsblöcken, die über den AUI-Adapter verbunden sind (z. B. ein übergeordneter Manager-Baustein und mehrere Worker-Bausteine).  

## Vergleich mit ähnlichen Bausteinen

- **`INI` (Basisfunktionsblock):** Der `INI_AUI` erweitert den einfachen `INI`-FB um eine standardisierte Adapterschnittstelle. Während der `INI` nur direkte Ein-/Ausgänge besitzt, erlaubt `INI_AUI` die lose Kopplung über AUI.  
- **Andere Speicherbausteine (z. B. `Memory`, `Persist`):** Diese arbeiten meist mit internen Variablen oder Dateien, bieten aber oft keine Adapterschnittstelle und keine spezielle `settings.ini`-Integration.  

## Fazit

Der `INI_AUI`-Funktionsblock ist eine flexible Lösung zum Lesen und Speichern von Konfigurationswerten in einer `settings.ini`-Datei. Durch die Kombination von direkten Dateneingängen und einer unidirektionalen AUI-Adapter-Schnittstelle eignet er sich hervorragend sowohl für einfache Initialisierungsaufgaben als auch für modulare, adapterbasierte Systemarchitekturen. Die Integration eines Standardwerts und die klare Statusrückmeldung erhöhen die Robustheit und Wartbarkeit der Steuerungssoftware.