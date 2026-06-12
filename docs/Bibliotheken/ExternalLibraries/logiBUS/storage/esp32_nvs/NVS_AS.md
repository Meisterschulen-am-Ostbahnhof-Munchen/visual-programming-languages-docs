# NVS_AS


![NVS_AS](./NVS_AS.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock **NVS_AS** dient als Schnittstelle zum Lesen und Schreiben von SINT-Daten (signed integer) in einem nichtflüchtigen Speicher (Non-Volatile Storage, NVS). Die Speicherung erfolgt über einen benutzerdefinierten Schlüssel (KEY). Der Baustein erweitert den Zugriff auf den NVS um eine Adapter-Schnittstelle (unidirektionaler AS-Typ), sodass Werte über standardisierte Adapterverbindungen empfangen und gesendet werden können. Dies ermöglicht eine modulare und wiederverwendbare Anbindung an Speicherfunktionen in IEC 61499-Anwendungen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Ereignis | Beschreibung | Mitgeführte Variablen |
|----------|--------------|-----------------------|
| INIT     | Initialisiert den NVS und löst das erste Laden eines gespeicherten Werts aus. | QI, KEY, DEFAULT_VALUE |

### **Ereignis-Ausgänge**
| Ereignis | Beschreibung | Mitgeführte Variablen |
|----------|--------------|-----------------------|
| INITO    | Bestätigung der Initialisierung und des ersten Ladevorgangs. | QO, STATUS |

### **Daten-Eingänge**
| Variable | Typ    | Beschreibung |
|----------|--------|--------------|
| QI       | BOOL   | Freigabe der Initialisierung (TRUE = aktivieren). |
| KEY      | STRING | Schlüssel, unter dem der Wert im NVS gespeichert ist. |
| DEFAULT_VALUE | SINT | Standardwert, der gelesen wird, falls kein Wert unter dem Schlüssel existiert. |

### **Daten-Ausgänge**
| Variable | Typ    | Beschreibung |
|----------|--------|--------------|
| QO       | BOOL   | Bestätigt erfolgreiche Initialisierung und Betriebsbereitschaft. |
| STATUS   | STRING | Statusmeldung (z. B. „Success“ oder Fehlertext). |

### **Adapter**
| Adapter   | Typ      | Richtung | Beschreibung |
|-----------|----------|----------|--------------|
| AS_IN     | AS       | SOCKET   | Empfängt einen zu speichernden SINT-Wert über ein unidirektionales Adapterprotokoll (Event + Data). |
| AS_OUT    | AS       | PLUG     | Sendet den gelesenen SINT-Wert über ein unidirektionales Adapterprotokoll an verbundene Bausteine. |

## Funktionsweise
Der **NVS_AS**-Baustein kapselt eine Instanz des Bausteins **NVS** (aus der Bibliothek `logiBUS::storage::esp32_nvs`). Die Funktion gliedert sich in zwei Betriebsarten:

1. **Initialisierung und erster Lesevorgang**  
   Nach einem INIT-Ereignis wird der interne NVS-Baustein initialisiert. Direkt im Anschluss (automatische Verkettung von `INITO` zu `GET`) wird der unter dem angegebenen KEY gespeicherte Wert gelesen. Existiert noch kein Wert, wird `DEFAULT_VALUE` zurückgegeben. Der gelesene oder vorgegebene Wert wird über den Adapter **AS_OUT** (Ereignis `E1` und Data `D1`) an nachgeschaltete Bausteine gesendet.

2. **Schreiben und Lesen über Adapter**  
   - Ein über den Adapter **AS_IN** eingehendes Ereignis (`E1`) mit zugehörigem Datenwert (`D1`) löst einen **SET**-Vorgang im NVS aus. Der Wert wird unter dem bei INIT angegebenen KEY gespeichert.  
   - Nach erfolgreichem SET wird automatisch der gespeicherte Wert über **AS_OUT** ausgegeben (durch die Verbindung von `NVS.SETO` zu `AS_OUT.E1`).  
   - Ebenso kann ein erneutes Lesen durch ein INIT-Ereignis oder durch den internen Ablauf nach einem erfolgreichen SET angestoßen werden. Ein separates Lese-Ereignis von außen ist nicht vorgesehen; der Wert wird stets nach einer Änderung oder bei Initialisierung aktualisiert.

Der Baustein arbeitet also als **lesender und schreibender Speicherzugriff mit automatischer Rückmeldung des aktuellen Werts**.

## Technische Besonderheiten
- **Adapterbasierte Ein-/Ausgabe**  
  Die Verwendung von unidirektionalen AS-Adaptern erlaubt eine lose Kopplung: **AS_IN** empfängt Schreibaufträge, **AS_OUT** gibt den gespeicherten Wert aus. Dies entspricht einem Publisher/Subscriber- oder Client/Server-Muster auf Adapterebene.

- **Automatische Initialisierung**  
  Nach dem INIT-Ereignis wird sofort ein GET ausgeführt, sodass der Baustein nach der Initialisierung sofort den aktuellen oder den Standardwert bereitstellt.

- **Typbeschränkung auf SINT**  
  Der Baustein speichert und lädt ausschließlich SINT-Werte. Für andere Datentypen (z. B. INT, REAL, STRING) sind separate Varianten erforderlich.

- **Fehlerbehandlung**  
  Fehler während der NVS-Operationen (z. B. ungültiger KEY, Speicherfehler) werden über den STATUS-Ausgang als Fehlermeldung ausgegeben, und QO wird auf FALSE gesetzt.

## Zustandsübersicht
Der interne NVS-Baustein besitzt einen eigenen Zustandsautomaten. Für den Anwender relevant sind folgende Abläufe:

| Phase | Zustand |
|-------|---------|
| 1 | Warten auf INIT-Ereignis. |
| 2 | INIT ausgeführt → NVS initialisiert → GET gestartet. |
| 3 | GET abgeschlossen → Wert über AS_OUT gesendet → Bereit für Schreibaufträge über AS_IN. |
| 4 | Ereignis über AS_IN → SET ausgeführt → Wert gespeichert → Wert über AS_OUT gesendet → zurück zu Phase 3. |

Ein erneutes INIT-Ereignis kann jederzeit eine Neuinitialisierung erzwingen.

## Anwendungsszenarien
- **Persistente Geräteparameter**  
  Speichern von Konfigurationswerten (z. B. Helligkeit, Verzögerungszeit) im nichtflüchtigen Speicher eines ESP32, bei Neustart automatisch laden.

- **Zustandsmerker für Automatisierung**  
  Merken des letzten Zustands (z. B. Zählerstand, Produktionsparameter) auch nach Spannungsausfall.

- **Adapterbasierte Datenknoten**  
  Einbindung in eine Kette von Adaptern, bei denen ein Baustein Werte setzt und ein anderer sie ausliest.

## Vergleich mit ähnlichen Bausteinen
- **NVS (direkt)**  
  Der Baustein `NVS` bietet dieselbe Funktionalität, jedoch ohne Adapterschnittstelle. Er benötigt separate Ereignis- und Datenleitungen. `NVS_AS` vereinfacht die Einbindung in adapterorientierte Architekturen.

- **NVS_AS_REAL, NVS_AS_STRING**  
  Analoge Bausteine für andere Datentypen. Die Schnittstelle und das Verhalten sind identisch, lediglich der Datentyp variiert.

- **Retain-Werte**  
  In manchen Systemen gibt es Retain-Variablen, die ebenfalls persistent sind. `NVS_AS` setzt auf hardwarenahen NVS (z. B. auf ESP32) und ist daher plattformspezifisch, aber performanter und kapazitätsoptimiert.

## Fazit
Der Funktionsblock **NVS_AS** stellt eine praktische, adapterbasierte Kapselung des nichtflüchtigen Speichers für SINT-Werte dar. Durch die Kombination von Initialisierungslogik, automatischer Wertrückmeldung und Adapterschnittstelle eignet er sich hervorragend für modulare IEC 61499-Projekte, die eine persistente Speicherung mit minimalem Verdrahtungsaufwand benötigen. Die Beschränkung auf den Typ SINT und die automatische GET-Nach-Initiierung sind zu beachten, erleichtern aber gleichzeitig die Handhabung in vielen Standardanwendungen.