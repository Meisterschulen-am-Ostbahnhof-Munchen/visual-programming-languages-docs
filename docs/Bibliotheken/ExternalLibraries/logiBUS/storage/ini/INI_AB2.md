# INI_AB2


![INI_AB2](./INI_AB2.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock `INI_AB2` dient zum Lesen und Schreiben von REAL-Werten aus oder in eine `settings.ini`-Datei. Der Zugriff erfolgt über eine Kombination aus Abschnittsnamen (Section) und Schlüsselnamen (Key). Die Kommunikation mit der Außenwelt erfolgt über einen bidirektionalen **AB2-Adapter**, der es ermöglicht, Werte aus der INI-Datei an andere Bausteine weiterzugeben oder Werte von anderen Bausteinen entgegenzunehmen und in der Datei zu speichern. Der Baustein wurde gemäß der Norm IEC 61499-2 entwickelt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ | Beschreibung |
|----------|-----|--------------|
| INIT | EInit | Initialisierungsereignis; startet den Lese- oder Schreibvorgang abhängig von der angeschlossenen Adapterlogik. Die mitgegebenen Daten legen Section, Key und einen Standardwert fest. |

### **Ereignis-Ausgänge**

| Ereignis | Typ | Beschreibung |
|----------|-----|--------------|
| INITO | EInit | Bestätigung der Initialisierung. Wird ausgelöst, nachdem der Lese-/Schreibzugriff abgeschlossen ist. |

### **Daten-Eingänge**

| Variable | Typ | Beschreibung |
|----------|-----|--------------|
| QI | BOOL | Qualifizierer für den Ereigniseingang; steuert die Ausführung. |
| SECTION | STRING | Name des Abschnitts (Section) in der `settings.ini`. |
| KEY | STRING | Name des Schlüssels (Key) innerhalb des Abschnitts. |
| DEFAULT_VALUE | REAL | Der Wert, der zurückgegeben wird, falls der Schlüssel in der `settings.ini` nicht existiert. |

### **Daten-Ausgänge**

| Variable | Typ | Beschreibung |
|----------|-----|--------------|
| QO | BOOL | Ausgangsqualifizierer; zeigt erfolgreiche Ausführung an. |
| STATUS | STRING | Statusmeldung des Dienstes (z. B. Fehlertexte oder „OK“). |

### **Adapter**

| Adapter | Typ | Beschreibung |
|---------|-----|--------------|
| VAL | adapter::types::bidirectional::AB2 | Bidirektionaler Adapter zum Austausch von REAL-Werten. Der eingehende Wert (`DO1`) wird in die INI-Datei geschrieben; der ausgehende Wert (`DI1`) wird aus der INI-Datei gelesen und weitergereicht. |

## Funktionsweise

Der `INI_AB2`-Baustein enthält intern eine Instanz des Funktionsblocks `eclipse4diac::storage::INI`. Die Kommunikation mit der `settings.ini` erfolgt ausschließlich über diese interne Instanz.

1. **Initialisierung (Lesevorgang):** Ein INIT-Ereignis am Eingang setzt die internen Parameter (Section, Key, Default-Wert) und aktiviert die interne INI-Instanz (`INI.INIT`). Nach erfolgreichem Einlesen wird der gelesene Wert über den Adapterausgang (`VAL.DI1`) an den angeschlossenen Baustein gesendet. Gleichzeitig werden die Ausgänge `INITO`, `QO` und `STATUS` aktualisiert.

2. **Schreibvorgang:** Der angeschlossene Baustein kann über den Adaptereingang (`VAL.DO1`) einen neuen Wert bereitstellen. Sobald das Ereignis `VAL.EO1` eintrifft, wird der Wert in der INI-Instanz gespeichert (`INI.SET`). Die Bestätigung (`INI.SETO`) wird über `VAL.EI1` an den Adapter zurückgegeben.

3. **Zyklisches Auslesen:** Nach jedem INIT-Vorgang wird automatisch der interne GET-Befehl ausgelöst, sodass der aktuelle Wert aus der Datei gelesen und über den Adapter ausgegeben wird.

Die Verschaltung stellt sicher, dass sowohl Lese- als auch Schreibzugriffe über den Adapter bidirektional abgewickelt werden können. Der Baustein realisiert somit eine persistente Datenhaltung mit externer Steuerung.

## Technische Besonderheiten

- **Bidirektionale Adapteranbindung:** Der AB2-Adapter erlaubt sowohl das Auslesen als auch das Beschreiben der INI-Datei über eine einzige Verbindung.
- **Standardwert:** Falls ein angegebener Schlüssel in der `settings.ini` nicht vorhanden ist, wird der über `DEFAULT_VALUE` übergebene Wert verwendet und als gelesener Wert ausgegeben.
- **Verwendung von `eclipse4diac::storage::INI`:** Der Baustein kapselt die eigentliche INI-Zugriffslogik und stellt eine robuste Fehlerbehandlung bereit (Statusausgabe).
- **IEC 61499-2 konform:** Der Baustein folgt dem Standard für Funktionsblöcke, was Interoperabilität und Wiederverwendbarkeit erhöht.

## Zustandsübersicht

Der `INI_AB2`-Baustein selbst besitzt keine expliziten Zustände (keine ECC-Zustände), da die Logik vollständig durch die interne INI-Instanz und die Ereignis-/Datenflüsse abgebildet wird. Das Zusammenspiel kann jedoch als einfacher sequenzieller Ablauf beschrieben werden:

1. **Ruhezustand** – Warten auf INIT oder Daten vom Adapter.
2. **Initialisieren** – INIT verarbeitet, interne INI wird gestartet.
3. **Lesen** – INI liest Wert, gibt ihn über Adapter aus.
4. **Schreiben** – Wert vom Adapter wird in INI gespeichert.
5. **Rückkehr** – Bestätigung über INITO oder Adapter-Ereignis.

## Anwendungsszenarien

- **Konfigurationsmanagement:** Speichern und Abrufen von Maschinenparametern (z. B. Solltemperaturen, Grenzwerte) in einer zentralen `settings.ini`.
- **Anlagenparametrierung:** Mehrere Steuerungskomponenten greifen über den AB2-Adapter auf dieselbe INI-Datei zu und können so Parameter austauschen.
- **Datenaustausch zwischen heterogenen Systemen:** Der standardisierte Adapter ermöglicht die Integration in beliebige 4diac-Architekturen.

## Vergleich mit ähnlichen Bausteinen

- **INI_AB (unidirektional):** Nutzt einen unidirektionalen Adapter, der entweder nur Lesen oder nur Schreiben erlaubt. `INI_AB2` ist durch die bidirektionale Schnittstelle flexibler.
- **INI_CFB (Composite FB):** Ein ähnlicher Baustein ohne Adapter, der direkt über Ereignisse und Daten angesprochen wird. `INI_AB2` abstrahiert die Verbindung und ermöglicht modulare Kopplung.
- **eclipse4diac::storage::INI (direkt):** Der Basisbaustein bietet keine Adapterschnittstelle; `INI_AB2` kapselt diesen und fügt die bidirektionale Kommunikation hinzu.

## Fazit

Der `INI_AB2`-Funktionsblock ist eine praktische Erweiterung für IEC 61499-basierte Automatisierungslösungen. Er vereinfacht den Zugriff auf INI-Konfigurationsdateien durch eine standardisierte Adapterschnittstelle und ermöglicht sowohl Lese- als auch Schreibvorgänge. Die einfache Handhabung und die klare Trennung von Logik und Schnittstelle machen ihn zu einem nützlichen Werkzeug für modulare und wiederverwendbare Steuerungsanwendungen.