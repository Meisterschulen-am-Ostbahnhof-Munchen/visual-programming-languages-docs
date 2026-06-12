# GET_TIME_OF_DAY


![GET_TIME_OF_DAY](./GET_TIME_OF_DAY.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `GET_TIME_OF_DAY` dient dem Auslesen eines Tageszeitwertes (Typ `TIME_OF_DAY`) aus einer InOut‑Variablen. Der gelesene Wert wird intern gepuffert und über einen Datenausgang bereitgestellt. Auf diese Weise wird eine konsistente, einmalig gelesene Tageszeit weitergereicht – auch wenn sich die Quellvariable zwischenzeitlich ändert.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| REQ      | Event    | Ausführungsanforderung; liest den aktuellen Wert von IN |

### **Ereignis-Ausgänge**
| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| CNF      | Event    | Bestätigung nach erfolgreichem Lesen und Puffern |

### **Daten-Eingänge**
Es sind keine reinen Eingänge vorhanden. Die Quelldaten werden über den InOut‑Eingang `IN` bereitgestellt.

### **Daten-Ausgänge**
| Ausgang | Datentyp   | Kommentar                     |
|---------|------------|-------------------------------|
| OUT     | TIME_OF_DAY| Gepufferter Tageszeitwert     |

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Ein Aufruf des Ereignisses `REQ` löst die interne assoziierte Aktion aus: Der aktuelle Wert der InOut‑Variable `IN` wird gelesen und in die Ausgangsvariable `OUT` kopiert. Anschließend wird das Ereignis `CNF` gesendet. Die Tageszeit steht dann bis zum nächsten `REQ` konsistent am Ausgang `OUT` zur Verfügung – unabhängig von zwischenzeitlichen Änderungen an `IN`.

## Technische Besonderheiten
- **InOut‑Variable als Quelle:** Der FB nutzt einen InOut‑Parameter, der im IEC‑61499‑Modell direkt mit einer externen Variablen verbunden ist. Dadurch kann der Baustein den Wert „von außen“ lesen, ohne selbst einen Daten‑Eingang definieren zu müssen.
- **Pufferung:** Der gelesene Wert wird in der Ausgangsvariable `OUT` zwischengespeichert, sodass nachfolgende Abfragen immer denselben Wert liefern, bis erneut `REQ` ausgelöst wird.
- **Einfacher Zustandsautomat:** Der FB besteht aus nur einem Zustand, der die Aktion ausführt und sofort das Bestätigungsereignis ausgibt.

## Zustandsübersicht
Der einfache Funktionsblock besitzt nur den Zustand `REQ`. Sobald das Ereignis `REQ` empfangen wird, wird die Aktion `REQ` ausgeführt (OUT := IN) und das Ereignis `CNF` wird gesendet. Es gibt keine weiteren Zustände oder Verzweigungen.

## Anwendungsszenarien
- **Zeitstempel in Steuerungen:** Einmalige Erfassung eines Tageszeitwertes aus einem übergeordneten Taktgeber, um z. B. Betriebsstunden oder Schaltzeitpunkte dokumentieren zu können.
- **Pufferung für asynchrone Auswertung:** Ein externer Zeitgeber (z. B. eine Systemuhr) ändert sich laufend; der FB friert seinen Wert zum Zeitpunkt des Aufrufs ein und stellt ihn einem langsameren Verbraucher oder einer Logik bereit.
- **Kommunikation über Grenzen hinweg:** In verteilten Systemen kann die aktuelle Tageszeit von einer Komponente abgerufen und lokal zwischengespeichert werden, um sie später konsistent auszugeben.

## Vergleich mit ähnlichen Bausteinen
- **Im Gegensatz zu einem reinen Datenverbinder** (z. B. MOVE oder einfache Datenkopie) verwendet `GET_TIME_OF_DAY` einen InOut‑Parameter, der eine direkte Kopplung an die Quellvariable erlaubt und so die Signalwege im IEC‑61499‑Modell sauber trennt.
- **Im Unterschied zu Zeit‑Funktionsbausteinen**, die selbstständig Ticks oder Echtzeitwerte generieren, greift dieser FB nur auf einen extern bereitgestellten Wert zu – er ist reine Lese‑ und Pufferlogik.
- **Ähnliche Bausteine** existieren für andere Datentypen (z. B. `GET_BOOL`, `GET_REAL`) und folgen dem gleichen Entwurfsmuster.

## Fazit
`GET_TIME_OF_DAY` ist ein kompakter, aber nützlicher Funktionsblock, der eine Tageszeit aus einer InOut‑Variable ausliest, puffert und kontrolliert als Ausgangswert weitergibt. Seine klare, zustandsarme Logik und die Pufferung machen ihn besonders geeignet für Aufgaben, bei denen eine einmal erfasste Zeit zu einem späteren Zeitpunkt noch in identischer Form vorliegen muss.