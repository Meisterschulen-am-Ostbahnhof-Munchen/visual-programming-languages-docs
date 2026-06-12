# GET_LINT


![GET_LINT](./GET_LINT.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein **GET_LINT** dient dem Auslesen eines Wertes vom Typ **LINT** aus einer InOut-Variablen und stellt diesen Wert gepuffert an seinem Ausgang zur Verfügung. Der Baustein ist Teil der Bibliothek `logiBUS::utils::conversion::provide` und realisiert eine einfache Lese-Puffer-Funktionalität.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ    | Kommentar                  |
|------|--------|----------------------------|
| REQ  | Event  | Normaler Ausführungsauftrag |

Der Ereigniseingang REQ löst die Ausführung des Bausteins aus. Dabei wird der aktuelle Wert der InOut-Variablen **IN** gelesen und im Ausgang **OUT** zwischengespeichert.

### **Ereignis-Ausgänge**

| Name | Typ    | Kommentar                  |
|------|--------|----------------------------|
| CNF  | Event  | Bestätigung der Ausführung |

Das Ereignis CNF wird nach erfolgreicher Verarbeitung des REQ-Ereignisses gesendet. Es signalisiert, dass der Ausgang OUT den aktuellen Wert der InOut-Variablen IN enthält.

### **Daten-Eingänge**

| Name | Typ  | Kommentar                          |
|------|------|-------------------------------------|
| IN   | LINT | Quellvariable (InOut) – Initialwert: 0 |

**IN** ist als InOut-Variable deklariert. Sie kann sowohl gelesen als auch beschrieben werden, wird in diesem Baustein jedoch ausschließlich gelesen. Der übergebene Wert wird bei jedem REQ-Ereignis in den Ausgang OUT kopiert.

### **Daten-Ausgänge**

| Name | Typ  | Kommentar                          |
|------|------|-------------------------------------|
| OUT  | LINT | Gepufferter Ausgabewert – Initialwert: 0 |

Der Ausgang **OUT** hält den zuletzt von der InOut-Variablen **IN** gelesenen Wert. Er wird bei jedem REQ-Ereignis aktualisiert.

### **Adapter**

Der Baustein besitzt keine Adapter-Schnittstellen.

## Funktionsweise

Der GET_LINT-Baustein implementiert eine einfache Pufferfunktion. Er besitzt einen einzigen Eintrittszustand **REQ**, der durch ein Ereignis am gleichnamigen Eingang aktiviert wird. In diesem Zustand wird der Algorithmus `REQ` ausgeführt:

```
OUT := IN;
```

Anschließend wird das Bestätigungsereignis **CNF** gesendet. Der Ausgang **OUT** enthält danach den aktuellen Wert der InOut-Variablen **IN**. Der Baustein wartet dann auf den nächsten REQ-Impuls.

## Technische Besonderheiten

- **InOut-Variable**: Der Baustein verwendet einen InOut-Parameter (`IN`). Dies erlaubt den direkten Zugriff auf eine Variable, die sowohl gelesen als auch beschrieben werden kann. Im Falle von GET_LINT wird der Wert jedoch nur gelesen und nicht verändert.
- **Datentyp LINT**: Der Baustein arbeitet ausschließlich mit dem 64-Bit-Ganzzahltyp LINT (Long Integer). Er ist für Umgebungen gedacht, in denen große Ganzzahlwerte verarbeitet werden.
- **Einfachste Zustandsmaschine**: Es existiert nur ein Zustand mit einer direkten Aktion und einer Ausgabe. Dadurch ist der Baustein deterministisch und ressourcenschonend.
- **Keine Fehlerbehandlung**: Der Baustein enthält keinerlei Plausibilitätsprüfungen oder Timeouts. Er setzt voraus, dass die InOut-Variable gültige Daten liefert.

## Zustandsübersicht

| Zustand | Aktion                       | Ausgabe    |
|---------|------------------------------|------------|
| REQ     | Kopieren von IN nach OUT     | CNF        |

Der Baustein startet im Zustand **REQ** und kehrt nach Ausführung der Aktion und Senden von CNF in denselben Zustand zurück (Endlosschleife bei jedem Ereignis).

## Anwendungsszenarien

- **Zwischenspeicherung eines LINT-Werts**: Wenn ein LINT-Wert aus einer globalen Variablen oder einem anderen Baustein gelesen und für eine bestimmte Zeit konstant gehalten werden soll (z. B. für eine nachfolgende Verarbeitung).
- **Synchronisation**: Der Baustein kann verwendet werden, um den aktuellen Wert einer InOut-Variablen in einem bestimmten Takt zu erfassen und an andere Bausteine weiterzugeben.
- **Entkopplung**: Durch den Puffer wird der lesende Baustein von der Quelle entkoppelt – Änderungen der Quelle wirken sich erst nach dem nächsten REQ-Impuls aus.
- **Einfache Wertübernahme**: In Steuerungssystemen kann GET_LINT genutzt werden, um einen externen Messwert oder einen Parameter von einem anderen Funktionsbaustein abzuholen.

## Vergleich mit ähnlichen Bausteinen

- **GET_DINT / GET_BOOL**: Analoge Bausteine für andere Datentypen (DINT, BOOL). Die Funktionsweise ist identisch; lediglich der Datentyp unterscheidet sich.
- **MOVE (z. B. MOVE_INT)**: Ein MOVE-Baustein kopiert ebenfalls einen Wert, verwendet jedoch standardmäßig Eingangs- und Ausgangsvariablen statt InOut. InOut-Variablen erlauben eine direkte Referenz auf die Quelle ohne zusätzlichen Data-Flow.
- **LINT_READER** (fiktiv): Ein hypothetischer Baustein, der zusätzliche Funktionen wie Puffer-Timeout oder Lesesperre bietet. GET_LINT ist dagegen minimalistisch und schnell.

## Fazit

Der GET_LINT-Funktionsbaustein bietet eine schlanke und zuverlässige Methode, um einen LINT-Wert aus einer InOut-Variable zu lesen und gepuffert bereitzustellen. Dank seiner einfachen Zustandsmaschine und der klaren Schnittstelle eignet er sich hervorragend für Basis-Synchronisationsaufgaben in IEC 61499-basierten Systemen. Durch die Verwendung von InOut-Parametern bleibt die Implementierung flexibel, ohne dass zusätzliche Datenleitungen oder Protokolle erforderlich sind.