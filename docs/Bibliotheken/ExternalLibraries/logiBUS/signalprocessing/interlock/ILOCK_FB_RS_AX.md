# ILOCK_FB_RS_AX

## Einleitung

![ILOCK_FB_RS_AX](./ILOCK_FB_RS_AX.svg)

Der Funktionsbaustein **ILOCK_FB_RS_AX** realisiert ein bistabiles, reset-dominantes RS-Latch mit einer AX-Schnittstelle für Set- und Reset-Signale sowie einer bidirektionalen AX2-Schnittstelle zur Verkettung mehrerer Interlock-Bausteine in einer Hierarchie. Der Baustein ist für den Einsatz in sicherheitsgerichteten und verriegelungsbasierten Steuerungsumgebungen konzipiert.

## Schnittstellenstruktur

Der Baustein verfügt über keine klassischen separaten Event- oder Datenports, sondern kapselt sämtliche Signalarten über **Adapter**. Die folgende Auflistung gruppiert die Ereignisse und Daten, die über die einzelnen Adapter anliegen.

### Ereignis-Eingänge
- **SET1.E1** (über Socket-Adapter `SET1`): Set-Event, triggert die Latch-Funktion.
- **RESET.E1** (über Socket-Adapter `RESET`): Reset-Event, triggert die rücksetzende Logik.
- **ILOCK_IN.EO1** (über Socket-Adapter `ILOCK_IN`): Ereignis von einer übergeordneten oder benachbarten Interlock-Instanz (bidirektionale Seite).
- **ILOCK_OUT.EI1** (über Plug-Adapter `ILOCK_OUT`): Ereignis von einer untergeordneten Interlock-Instanz.

### Ereignis-Ausgänge
- **Q1.E1** (über Plug-Adapter `Q1`): Ausgabe-Ereignis nach jeder Aktualisierung des Latch-Zustands.
- **ILOCK_IN.EI1** (über Socket-Adapter `ILOCK_IN`): Ereignis, das an den verbundenen Partneradapter des `ILOCK_IN` gesendet wird.
- **ILOCK_OUT.EO1** (über Plug-Adapter `ILOCK_OUT`): Ereignis, das an den verbundenen Partneradapter des `ILOCK_OUT` gesendet wird.

### Daten-Eingänge
- **SET1.D1** (über Socket-Adapter `SET1`): Set-Signal (Boolescher Wert, TRUE setzt den Latch).
- **RESET.D1** (über Socket-Adapter `RESET`): Reset-Signal (Boolescher Wert, TRUE setzt den Latch zurück, dominiert über Set).
- **ILOCK_IN.DO1** (über Socket-Adapter `ILOCK_IN`): Interlock-Status von oben (Boolescher Wert, TRUE blockiert den Latch).
- **ILOCK_OUT.DI1** (über Plug-Adapter `ILOCK_OUT`): Interlock-Status von unten (Boolescher Wert, TRUE blockiert den Latch).

### Daten-Ausgänge
- **Q1.D1** (über Plug-Adapter `Q1`): Ausgangszustand des Latches (Boolescher Wert).
- **ILOCK_IN.DI1** (über Socket-Adapter `ILOCK_IN`): Weiterleitung des Reset-Signals nach oben.
- **ILOCK_OUT.DO1** (über Plug-Adapter `ILOCK_OUT`): Weiterleitung des Reset-Signals nach unten.

### Adapter
| Adapter | Typ | Richtung | Beschreibung |
|---------|-----|----------|--------------|
| `SET1` | unidirectional AX | Socket | Set-Eingang |
| `RESET` | unidirectional AX | Socket | Reset-Eingang |
| `ILOCK_IN` | bidirectional AX2 | Socket | Interlock-Eingang (von oben) |
| `Q1` | unidirectional AX | Plug | Latch-Ausgang |
| `ILOCK_OUT` | bidirectional AX2 | Plug | Interlock-Ausgang (nach unten) |

## Funktionsweise
Der Funktionsblock führt bei jedem eintreffenden Ereignis (über `SET1.E1`, `RESET.E1`, `ILOCK_IN.EO1` oder `ILOCK_OUT.EI1`) den Algorithmus `REQ` aus. Die interne Logik berechnet den neuen Ausgangswert `Q1.D1` nach der reset-dominanten Formel:

`Q1.D1 := (SET1.D1 OR Q1.D1) AND NOT (RESET.D1 OR ILOCK_IN.DO1 OR ILOCK_OUT.DI1);`

- Ist das Reset-Signal (`RESET.D1`) oder einer der Interlock-Eingänge (`ILOCK_IN.DO1` oder `ILOCK_OUT.DI1`) TRUE, wird der Latch sofort zurückgesetzt (Q = FALSE), unabhängig vom Set-Signal.
- Liegt kein Reset und keine Interlock-Blockade an, wird der Latch durch ein Set-Signal (`SET1.D1` = TRUE) gesetzt und bleibt selbsthaltend.
- Die Interlock-Signale der AX2-Schnittstelle werden propagiert:
  - `ILOCK_IN.DI1` (nach oben) = `RESET.D1 OR ILOCK_OUT.DI1`
  - `ILOCK_OUT.DO1` (nach unten) = `RESET.D1 OR ILOCK_IN.DO1`

Dadurch entsteht eine Kaskade, in der ein Reset-Signal in beide Richtungen (nach oben und nach unten) weitergegeben wird und alle untergeordneten sowie übergeordneten Latch-Bausteine blockiert.

## Technische Besonderheiten
- **Adapterbasierte Schnittstellen**: Statt einzelner Ports verwendet der Baustein standardisierte AX/AX2-Adapter, die eine modulare und wiederverwendbare Verbindung mit anderen Komponenten ermöglichen.
- **Kaskadierbare Interlock-Kette**: Über die bidirektionalen `ILOCK_IN`/`ILOCK_OUT`-Adapter können mehrere ILOCK_FB_RS_AX-Instanzen in Reihe geschaltet werden. Ein Reset-Signal wird automatisch in beide Richtungen propagiert, sodass eine gesamte Kette blockiert wird.
- **Reset-Dominanz**: Der Reset hat stets Vorrang vor dem Set-Signal. Dies entspricht typischen Anforderungen an Sicherheitsverriegelungen, die einen definierten Vorrang des Rücksetzsignals verlangen.
- **Durchgehende Ereignisverarbeitung**: Der Baustein reagiert auf jedes eingehende Ereignis (Set, Reset, Interlock oben/unten) und aktualisiert sofort alle Ausgänge. Es gibt keine Zustandswechsel im ECC (nur ein Zustand `REQ`), die Logik ist rein kombinatorisch mit Rückkopplung über den gespeicherten Latch-Wert.

## Zustandsübersicht
Der Baustein besitzt in seinem ECC nur einen Zustand `REQ`, der stets aktiv ist. Der innere Latch-Zustand wird durch den booleschen Wert `Q1.D1` repräsentiert. Die Zustandsübersicht beschreibt daher das Verhalten der internen Speicherzelle:

| Aktuelles Q | SET1.D1 | RESET.D1 | Interlock aktiv? | Nächstes Q | Beschreibung |
|-------------|---------|----------|------------------|------------|--------------|
| FALSE       | FALSE   | FALSE    | NEIN             | FALSE      | Latch bleibt zurückgesetzt |
| FALSE       | TRUE    | FALSE    | NEIN             | TRUE       | Latch wird gesetzt |
| FALSE       | TRUE    | TRUE     | JA/NEIN          | FALSE      | Reset dominiert |
| TRUE        | FALSE   | FALSE    | NEIN             | TRUE       | Latch bleibt gesetzt (Selbsthaltung) |
| TRUE        | TRUE    | FALSE    | NEIN             | TRUE       | Latch bleibt gesetzt |
| TRUE        | FALSE   | TRUE     | JA/NEIN          | FALSE      | Reset dominiert |
| TRUE        | TRUE    | TRUE     | JA/NEIN          | FALSE      | Reset dominiert |
| beliebig    | beliebig| beliebig | JA (ILOCK)       | FALSE      | Interlock-Blockade setzt oder hält Latch zurück |

## Anwendungsszenarien
- **Maschinensicherheit**: Verriegelung von Antrieben oder Werkzeugen, bei denen ein Reset-Signal (z. B. Not-Halt) Vorrang hat und zusätzlich benachbarte Module blockiert.
- **Prozesssteuerung mit Hierarchie**: In einer Kaskade von Steuerungsmodulen kann ein übergeordnetes Signal die untergeordneten Blöcke in den Grundzustand versetzen.
- **Redundante Verriegelung**: Mehrere ILOCK_FB_RS_AX-Instanzen können in einem Ring oder einer Linie angeordnet werden, um ein verteiltes Verriegelungssystem ohne zentrale Logik aufzubauen.
- **Latch mit externer Blockierung**: Über die Interlock-Adapter können externe Bedingungen (z. B. Sensorwerte oder Freigaben) den Latch blockieren, ohne die Set/Reset-Funktion zu beeinträchtigen.

## Vergleich mit ähnlichen Bausteinen
- **Standard RS-Latch (z. B. SR_FF)**: Ein typisches RS-Latch hat gleichberechtigte Set- und Reset-Eingänge. Der ILOCK_FB_RS_AX ist reset-dominant und bietet zusätzlich eine Interlock-Funktion zur Kaskadierung.
- **Reset-Dominantes Latch ohne Interlock**: Ein einfacher RS-Latch mit Reset-Dominanz hat nur Set/Reset-Ports. Der hier beschriebene Baustein erweitert dies um die bidirektionale Verriegelung über AX2-Adapter.
- **Interlock-Bausteine mit dedizierten Ports**: Manche Bibliotheken bieten Interlock-FBs mit einzelnen booleschen Eingängen für „InterlockFromAbove“ und „InterlockFromBelow“. Der ILOCK_FB_RS_AX kapselt diese Kanäle in Adaptern und vereinfacht so die Verbindung zwischen den Instanzen.

## Fazit
Der **ILOCK_FB_RS_AX** ist ein spezialisierter Funktionsbaustein für verriegelungsbasierte Steuerungsaufgaben. Seine reset-dominante Logik gewährleistet eine definierte Priorität des Rücksetzsignals. Die Verwendung von AX/AX2-Adaptern ermöglicht eine saubere modulare Struktur und die einfache Kaskadierung mehrerer Bausteine. Dadurch eignet er sich besonders für hierarchische oder verteilte Sicherheits- und Verriegelungssysteme in der Automatisierungstechnik.