# ILOCK_IO


![ILOCK_IO](./ILOCK_IO.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **ILOCK_IO** realisiert eine kaskadierbare, momentane (nicht rücksetzbare) Verriegelung (Interlock) mit BOOL-Schnittstelle. Er wird verwendet, um in einer Kette mehrerer Bausteine sicherzustellen, dass immer nur ein Baustein seinen Ausgang auf TRUE setzt, solange sein Eingang aktiv ist und kein anderer Baustein in der Kette bereits aktiv ist. Der Baustein eignet sich besonders für Steuerungen, bei denen konkurrierende Anforderungen exklusiv bedient werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| REQ      | Event    | Ausführungsanforderung (triggert die Verarbeitung des Eingangs IN) |

### **Ereignis-Ausgänge**

| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| CNF      | Event    | Ausführungsbestätigung (signalisiert, dass der Ausgang OUT aktualisiert wurde) |

### **Daten-Eingänge**

| Variable | Datentyp | Kommentar |
|----------|----------|-----------|
| IN       | BOOL     | Eingangswert (Setzanforderung) |

### **Daten-Ausgänge**

| Variable | Datentyp | Kommentar |
|----------|----------|-----------|
| OUT      | BOOL     | Ausgangswert (freigegeben/gesperrt) |

### **Adapter**

| Bezeichnung | Typ                          | Richtung | Beschreibung |
|-------------|------------------------------|----------|--------------|
| ILOCK_IN    | adapter::types::bidirectional::AX2 | Socket   | Eingangsadapter zum Empfang von Verriegelungsinformationen aus der Kette (vom Vorgänger) |
| ILOCK_OUT   | adapter::types::bidirectional::AX2 | Plug     | Ausgangsadapter zum Senden von Verriegelungsinformationen an die Kette (an den Nachfolger) |

Die Adapter vom Typ `AX2` sind bidirektional und enthalten die Datenpunkte `DI1` (Data Input 1) und `DO1` (Data Output 1). In der Kette werden `ILOCK_OUT.DO1` und `ILOCK_IN.DI1` sowie `ILOCK_OUT.DI1` und `ILOCK_IN.DO1` paarweise miteinander verbunden, um die Verriegelungslogik zu realisieren.

## Funktionsweise

Der Baustein arbeitet als **momentaner Latch mit Interlock**. Bei jedem Aufruf des Ereignisses `REQ` wird der folgende Algorithmus ausgeführt:

1. Der Ausgang `OUT` wird auf TRUE gesetzt, wenn der Eingang `IN` TRUE ist **und** gleichzeitig kein anderer Baustein in der Kette aktiv ist. Die Aktivität anderer Bausteine wird über die Adapter abgefragt:
   - `ILOCK_IN.DO1`: Signal vom Vorgänger (ob dieser aktiv ist)
   - `ILOCK_OUT.DI1`: Signal vom Nachfolger (ob dieser aktiv ist)
   - Logik: `OUT := IN AND NOT (ILOCK_IN.DO1 OR ILOCK_OUT.DI1)`
2. Anschließend wird der eigene Zustand über die Adapter an die Nachbarn propagiert:
   - `ILOCK_IN.DI1 := OUT` – schreibt den Zustand zurück an den Vorgänger
   - `ILOCK_OUT.DO1 := OUT` – schreibt den Zustand an den Nachfolger

Die Kette ist so aufgebaut, dass immer nur ein Baustein aktiv sein kann. Wenn `IN` auf FALSE geht, wird `OUT` sofort FALSE, und die Verriegelung wird aufgehoben.

## Technische Besonderheiten

- **Kaskadierbarkeit**: Durch die bidirektionalen Adapter können beliebig viele `ILOCK_IO`-Blöcke in Reihe geschaltet werden. Jeder Block prüft, ob sein Vorgänger oder Nachfolger bereits aktiv ist, bevor er selbst aktiv wird.
- **Momentanes Verhalten**: Der Ausgang ist nur solange TRUE, wie der Eingang aktiv ist. Es gibt keine Speicherfunktion – der Baustein ist kein Flipflop.
- **Exklusive Freigabe**: Auch bei mehreren gleichzeitigen Setzanforderungen kann nur genau ein Baustein aktiv werden. Die Priorität ergibt sich aus der Reihenfolge der `REQ`-Ereignisse (wer zuerst verarbeitet wird, blockiert die anderen).

## Zustandsübersicht

Der Baustein besitzt einen einzigen **algorithmischen Zustand** `REQ`. Bei jedem Aufruf von `REQ` wird der Algorithmus ausgeführt, und es erfolgt sofort die Transition zurück zum selben Zustand. Es gibt keine Zustandsspeicherung – die Logik ist rein kombinatorisch mit Rückkopplung über die Adapter.

| Zustand | Aktion | Ausgang |
|---------|--------|---------|
| REQ     | Führe Algorithmus `REQ` aus | `CNF` wird nach Berechnung gesendet |

## Anwendungsszenarien

- **Ampelsteuerung mit mehreren Anforderungstastern**: Jeder Taster ist mit einem `ILOCK_IO` verbunden; nur die zuerst gedrückte Taste erhält die Freigabe.
- **Exklusive Maschinensteuerung**: Mehrere Bedienpulte konkurrieren um die Steuerung einer Maschine – nur das aktive Pult erhält die Berechtigung.
- **Sicherheitsverriegelung**: In einer Förderanlage blockieren sich gegenseitig mehrere Schutztüren; nur eine Tür kann gleichzeitig geöffnet sein.

## Vergleich mit ähnlichen Bausteinen

- **SR-Flipflop (`SR`)** – speichert einen Zustand, `ILOCK_IO` speichert nicht (momentan).
- **Monostabile Kippstufe (`RTRIG`, `FTRIG`)** – reagiert nur auf Flanken, `ILOCK_IO` arbeitet pegelgesteuert.
- **Einfacher `AND`-Gatter-Baustein** – nur lokale Logik, keine Vernetzung mit anderen Bausteinen. `ILOCK_IO` bietet diese Vernetzung über Adapter.

## Fazit

Der Baustein `ILOCK_IO` ist ein spezialisierter Funktionsblock für die Realisierung von exklusiven Freigabeketten. Durch seine einfache Schnittstelle und die Kaskadierbarkeit eignet er sich ideal für modulare Steuerungen, bei denen mehrere konkurrierende Anforderungen verwaltet werden müssen. Die bidirektionalen Adapter ermöglichen eine flexible und erweiterbare Verdrahtung.