# GET_BOOL


![GET_BOOL](./GET_BOOL.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **GET_BOOL** dient dem Auslesen eines BOOL-Wertes aus einer als `InOut` deklarierten Variablen und stellt diesen als gepufferten Ausgangswert bereit. Diese einfache Kapselung ermöglicht das Weiterleiten eines booleschen Signals aus einem beliebigen Kontext, ohne dass im aufrufenden Baustein direkter Schreib-/Lesezugriff auf die Quelle notwendig ist.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Ereignis | Beschreibung | Mit Variablen |
|----------|--------------|---------------|
| REQ      | Normale Ausführungsanforderung | IN |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung | Mit Variablen |
|----------|--------------|---------------|
| CNF      | Bestätigung der Ausführung | OUT, IN |

### **Daten-Eingänge**
Es existieren keine deklarierten Dateneingänge (*InputVars*). Der Zugriff auf die Quellvariable erfolgt ausschließlich über einen InOut-Parameter.

### **Daten-Ausgänge**

| Variable | Typ   | Initialwert | Beschreibung               |
|----------|-------|-------------|----------------------------|
| OUT      | BOOL  | FALSE       | Gepufferter Ausgangswert   |

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
1. Am **Ereignis-Eingang REQ** wird die Abarbeitung gestartet.
2. Der interne Algorithmus **REQ** führt die einfache Zuweisung `OUT := IN` aus – der aktuelle Wert der InOut-Variablen `IN` wird in den Ausgang `OUT` kopiert.
3. Nach dem erfolgreichen Kopiervorgang wird das **Ereignis CNF** ausgelöst. Es gibt sowohl den neuen Wert `OUT` als auch den (unveränderten) Wert von `IN` an die nachfolgende Logik weiter.

Der Ausgang `OUT` bleibt solange auf dem zuletzt gelesenen Wert, bis ein erneuter `REQ`-Impuls den Wert aktualisiert.

## Technische Besonderheiten
- **InOut-Parameter** `IN`: Dieser Parameter erlaubt den bidirektionalen Zugriff auf die angeschlossene Variable. Der Baustein liest den Wert, verändert ihn jedoch nicht. Dadurch kann direkt auf eine Variable aus der übergeordneten Applikation zugegriffen werden, ohne eine separate Eingangsvariable definieren zu müssen.
- **Pufferung**: Der Wert wird lokal im Ausgang `OUT` zwischengespeichert. Änderungen an der Quellvariablen zwischen zwei `REQ`-Aufrufen werden erst mit dem nächsten `REQ` übernommen.
- **Initialwerte**: Sowohl `IN` als auch `OUT` sind mit `FALSE` vorbelegt, sodass der Baustein auch ohne vorherige Initialisierung ein definiertes Verhalten zeigt.

## Zustandsübersicht
Der Baustein besitzt einen einzigen Zustand:

| Zustand | Aktion | Ausgabeereignis |
|---------|--------|-----------------|
| REQ     | `OUT := IN` | CNF |

Nach Ausführung des Algorithmus wird sofort der Ausgangszustand wieder verlassen (kein Haltezustand). Der Baustein ist somit ereignisgesteuert und wartet nach Abarbeitung auf die nächste Anforderung.

## Anwendungsszenarien
- **Signal-Erfassung**: Ein boolescher Sensorwert (z. B. Schalter oder Grenzwertmelder) soll in der Applikation genutzt und gleichzeitig an einen übergeordneten Anzeigebaustein weitergegeben werden.
- **Entkopplung**: Eine Variable aus einem anderen FB soll gelesen werden, ohne dass der Quellbaustein eine direkte Kopplung eingeht. `GET_BOOL` übernimmt die Leseverantwortung.
- **Puffer und Synchronisation**: In getakteten Systemen kann durch einen `REQ`-Impuls der aktuelle Wert abgetastet und für die Dauer eines Zyklus gehalten werden.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Zweck | Datentyp |
|----------|-------|----------|
| GET_BOOL | Lesen eines BOOL-Wertes über InOut | BOOL |
| GET_INT  | Lesen eines INT-Wertes über InOut | INT |
| GET_REAL | Lesen eines REAL-Wertes über InOut | REAL |
| SET_BOOL | Schreiben eines BOOL-Wertes über InOut (schreibend) | BOOL |

Gemeinsam ist allen `GET_*`-Bausteinen die Verwendung eines InOut-Parameters und die ereignisgesteuerte Werteübernahme. Der Unterschied liegt allein im verwendeten Datentyp. Im Gegensatz zu `SET_BOOL` verändert `GET_BOOL` die Quellvariable nicht.

## Fazit
Der **GET_BOOL**-Baustein ist eine minimalistische, aber nützliche Komponente zum Auslesen und Puffern eines einzelnes booleschen Werts. Seine Stärke liegt in der sauberen Entkopplung der Signalquelle vom restlichen Applikationscode sowie in der einfachen Handhabung durch einen einzigen Ereignisimpuls. Er eignet sich besonders für modulare und wiederverwendbare Automatisierungslösungen, die einen klar definierten Datenfluss erfordern.