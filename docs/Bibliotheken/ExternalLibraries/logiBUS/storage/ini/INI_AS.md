# INI_AS


![INI_AS](./INI_AS.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **INI_AS** dient dem Laden und Speichern von SINT‑Daten aus einer `settings.ini`‑Datei. Er greift über einen Abschnittsnamen (`SECTION`) und einen Schlüssel (`KEY`) auf einen Konfigurationswert zu. Über die Adapter‑Schnittstelle `AS` kann der Wert sowohl gelesen als auch geschrieben werden. Der Baustein kapselt den internen `INI`‑Funktionsblock und erweitert ihn um eine einheitliche Adapter‑Schnittstelle.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Typ  | Mit‑Vars | Beschreibung |
|----------|------|----------|--------------|
| `INIT`   | EInit | QI, SECTION, KEY, DEFAULT_VALUE | Service‑Initialisierung: Liest den Wert aus der INI‑Datei und gibt ihn über den Adapter aus. |

### **Ereignis-Ausgänge**
| Ereignis | Typ  | Mit‑Vars | Beschreibung |
|----------|------|----------|--------------|
| `INITO`  | EInit | QO, STATUS | Bestätigung der Initialisierung. |

### **Daten-Eingänge**
| Name          | Datentyp | Beschreibung |
|---------------|----------|--------------|
| `QI`          | BOOL     | Eingangsqualifikator (z. B. Freigabe). |
| `SECTION`     | STRING   | Name des Abschnitts in der INI‑Datei. |
| `KEY`         | STRING   | Name des Schlüssels innerhalb des Abschnitts. |
| `DEFAULT_VALUE` | SINT   | Wert, der zurückgegeben wird, wenn der Schlüssel in der INI‑Datei nicht vorhanden ist. |

### **Daten-Ausgänge**
| Name     | Datentyp | Beschreibung |
|----------|----------|--------------|
| `QO`     | BOOL     | Ausgangsqualifikator (zeigt erfolgreiche Operation an). |
| `STATUS` | STRING   | Statusmeldung (z. B. Fehlertexte). |

### **Adapter**
| Bezeichnung | Typ                 | Richtung | Beschreibung |
|-------------|---------------------|----------|--------------|
| `AS_IN`     | `adapter::types::unidirectional::AS` | Eingang (Socket) | Empfängt einen neuen zu speichernden Wert (SET‑Operation). |
| `AS_OUT`    | `adapter::types::unidirectional::AS` | Ausgang (Plug)  | Gibt den aktuell gelesenen oder gespeicherten Wert aus (GET‑Operation). |

## Funktionsweise
1. **Initialisierung und erstes Lesen (INIT‑Ereignis)**  
   Mit dem `INIT`‑Ereignis werden die Parameter `SECTION`, `KEY` und `DEFAULT_VALUE` übergeben. Der interne `INI`‑Baustein wird gestartet, liest den Wert aus der `settings.ini` und gibt ihn über den Adapter‑Ausgang `AS_OUT` aus. Gleichzeitig wird das `INITO`‑Ereignis ausgelöst, das den Abschluss der Initialisierung meldet.  
   Anschließend (eventuell noch im gleichen Zyklus) wird automatisch ein `GET` auf dem `INI`‑Baustein ausgeführt, sodass der gelesene Wert sofort am Adapter anliegt.

2. **Schreiben eines Wertes (über den Adapter‑Eingang)**  
   Über den Socket `AS_IN` kann ein neuer Wert (Ereignis `E1` und Daten `D1`) an den Baustein gesendet werden. Dieses Ereignis wird auf den `SET`‑Eingang des internen `INI`‑Bausteins weitergeleitet, der den Wert in der INI‑Datei speichert. Nach erfolgreichem Speichern wird das Ereignis `SETO` des `INI`‑Bausteins ausgelöst, das wiederum den Adapter‑Ausgang `AS_OUT` (Ereignis `E1`) bedient und den gespeicherten Wert über `D1` ausgibt.

3. **Rückmeldungen**  
   Der interne `INI`‑Baustein liefert die Ausgangssignale `QO` und `STATUS`, die direkt an die gleichnamigen Ausgänge des `INI_AS`‑Bausteins durchgeschliffen werden.

## Technische Besonderheiten
- **Adapter‑Schnittstelle `AS`**: Der Baustein verwendet einen unidirektionalen Adapter (`adapter::types::unidirectional::AS`). Dies ermöglicht eine standardisierte Anbindung an andere Bausteine, die denselben Adaptertyp unterstützen.
- **Datentyp SINT**: Der gelesene und gespeicherte Wert ist vom Typ „Short Integer“ (SINT, 8‑Bit). Dadurch eignet sich der Baustein besonders für kleine ganzzahlige Konfigurationswerte.
- **Wiederverwendung des `INI`‑Bausteins**: Die gesamte Logik zum Zugriff auf die INI‑Datei wird vom bewährten `eclipse4diac::storage::INI`‑Baustein übernommen. Der `INI_AS` kapselt diesen und ergänzt die Adapter‑Schnittstelle.
- **Automatischer GET nach INIT**: Nach dem Initialisieren wird sofort ein Lesevorgang gestartet, sodass der aktuelle Wert ohne separates Ereignis am Adapterausgang bereitsteht.

## Zustandsübersicht
Der Baustein besitzt keine explizite Zustandsmaschine (ECC). Das Verhalten wird rein über die Ereignisverkettung innerhalb des internen FBNetzwerks gesteuert:
- Nach `INIT` läuft die Sequenz: INIT des `INI`‑Bausteins → INITO → GET (automatisch) → VALUO am Adapterausgang.
- Nach einem SET‑Ereignis vom Adaptereingang: SET des `INI`‑Bausteins → SETO → Adapterausgang mit dem neuen Wert.

## Anwendungsszenarien
- **Persistente Konfiguration**: Speichern und Lesen von Einstellungen wie Schwellwerten, Modus‑Flags oder Geräteadressen in einer `settings.ini`.
- **Parametrisierung von Steuerungsanwendungen**: Wenn eine SPS oder ein anderes Automatisierungssystem zur Laufzeit Werte aus einer Konfigurationsdatei laden oder ändern muss.
- **Adapter‑basierte Kommunikation**: Einbindung in eine übergeordnete Adapter‑Struktur, die mehrere solche Lese‑/Schreib‑Bausteine zusammenfasst.

## Vergleich mit ähnlichen Bausteinen
- **INI_STRING, INI_INT, INI_BOOL**: Diese Bausteine verwenden ebenfalls den internen `INI`‑Baustein, unterstützen aber andere Datentypen (STRING, INT, BOOL) und haben oft eine andere Schnittstellenstruktur (keine Adapter). Der `INI_AS` bietet durch den Adapter eine einheitliche und wiederverwendbare Schnittstelle.
- **Direkter `INI`‑Baustein**: Der `INI`‑Baustein selbst hat mehrere Ereigniseingänge (INIT, GET, SET) und erfordert eine manuelle Verkabelung von Lese‑ und Schreibvorgängen. Der `INI_AS` vereinfacht die Handhabung, indem er die typische Nutzung (Lesen beim Start, Schreiben über Adapter) standardisiert.

## Fazit
Der Funktionsblock `INI_AS` ist ein komfortabler Baustein zum persistenten Lesen und Schreiben von SINT‑Werten aus einer INI‑Datei. Durch die Adapter‑Schnittstelle lässt er sich leicht in bestehende Architekturen integrieren und reduziert den Verdrahtungsaufwand. Er eignet sich besonders für Konfigurationsaufgaben, bei denen ein einzelner ganzzahliger Wert zwischengespeichert werden muss.