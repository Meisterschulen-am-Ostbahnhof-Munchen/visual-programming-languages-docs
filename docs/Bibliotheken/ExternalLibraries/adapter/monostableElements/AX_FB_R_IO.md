# AX_FB_R_IO


![AX_FB_R_IO](./AX_FB_R_IO.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AX_FB_R_IO** realisiert ein monostabiles, reset-dominantes Verhalten. Er verfügt über drei Adapter-Schnittstellen, über die er ein Eingangssignal (IN) an den Ausgang (OUT) weiterleitet, sofern kein aktives Rücksetzsignal (RESET1) anliegt. Der Baustein arbeitet nach dem Prinzip: **Reset hat Priorität**.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine.

### **Ereignis-Ausgänge**

Keine.

### **Daten-Eingänge**

Keine.

### **Daten-Ausgänge**

Keine.

### **Adapter**

| Bezeichnung | Typ                  | Richtung | Kommentar              |
|-------------|----------------------|----------|------------------------|
| IN          | unidirectional::AX   | Socket   | Eingangssignal         |
| RESET1      | unidirectional::AX   | Socket   | Rücksetzsignal (priorisiert) |
| OUT         | unidirectional::AX   | Plug     | Ausgangssignal         |

Die Adapter vom Typ `adapter::types::unidirectional::AX` verfügen jeweils über einen Ereignisausgang `E1` und einen Datenausgang `D1` (vom Typ BOOL). Der Datenwert des Adapters wird über `D1` bereitgestellt, die Verarbeitung wird durch das Ereignis `E1` ausgelöst.

## Funktionsweise

Die Kernlogik des Bausteins wird durch eine einfache Zustandsmaschine mit einem einzigen Zustand `REQ` abgebildet. Sobald ein Ereignis an einem der beiden Eingangsadapter (`IN.E1` oder `RESET1.E1`) eintrifft, wird der Algorithmus `REQ` ausgeführt. Dieser Algorithmus prüft den Rücksetzeingang:

- **Wenn `RESET1.D1 = TRUE`**: Der Ausgang `OUT.D1` wird auf `FALSE` gesetzt, unabhängig vom Eingangssignal.
- **Andernfalls**: Der Ausgang `OUT.D1` erhält direkt den Wert des Eingangssignals `IN.D1`.

Das Ereignis am Ausgangsadapter (`OUT.E1`) wird bei jeder Ausführung des Algorithmus ausgelöst, sodass nachfolgende Bausteine über die Wertänderung informiert werden.

## Technische Besonderheiten

- **Reset-Dominanz**: Das Rücksetzsignal `RESET1` hat stets Vorrang vor dem Eingangssignal `IN`. Solange `RESET1.D1` aktiv ist, bleibt der Ausgang `FALSE`.
- **Monostabiles Verhalten**: Der Baustein kehrt nach jeder Verarbeitung automatisch in den Bereitschaftszustand zurück (ein Zustand). Es gibt keinen gespeicherten Zustand, jede Ausführung reagiert sofort auf die aktuellen Eingänge.
- **Adapterbasierte Kommunikation**: Sämtliche Ein- und Ausgänge erfolgen über bidirektionale Adapter, die sowohl Daten als auch Ereignisse transportieren. Die Ereignissteuerung erfolgt implizit über die Adapter-Protokolle.
- **Paketname**: `adapter::monostableElements` (definiert im CompilerInfo).

## Zustandsübersicht

Der Funktionsblock besitzt genau einen Zustand:

| Zustand | Beschreibung |
|---------|--------------|
| REQ     | Start- und Endzustand. Wartet auf ein Ereignis von `IN` oder `RESET1`. Nach Ausführung des Algorithmus kehrt der Zustand immer zu `REQ` zurück (keine weiteren Zustände). |

Es gibt zwei Transitionen:
- Von `REQ` zu `REQ` bei Ereignis `IN.E1`
- Von `REQ` zu `REQ` bei Ereignis `RESET1.E1`

Beide Transitionen führen zurück in den gleichen Zustand und lösen die Ausführung des Algorithmus aus.

## Anwendungsszenarien

- **Freigabeschaltung in der Automatisierungstechnik**: Ein Signal (z. B. Maschinenstart) wird nur dann an den Ausgang weitergegeben, wenn kein Rücksetzkommando (z. B. Stopp) aktiv ist.
- **Sicherheitsverriegelung**: In einer Steuerungskette wird ein Rücksetzsignal prioritär behandelt, um gefährliche Zustände zuverlässig zu eliminieren.
- **Signalweiche mit Priorität**: Zwei Quellen konkurrieren um einen Ausgang – hier hat die Rücksetzfunktion stets Vorrang.

## Vergleich mit ähnlichen Bausteinen

- **AX_FB_RS** (Set-Dominant): Im Gegensatz zu diesem Baustein hat dort der Set-Eingang Priorität. `AX_FB_R_IO` ist reset-dominant.
- **AX_FB_SR**: Set-Reset-Flipflop mit gleichberechtigten Eingängen, oft ohne Priorität (kann zu undefinierten Zuständen führen). `AX_FB_R_IO` vermeidet dies durch klare Dominanz.
- **AX_FB_MONOSTABLE**: Reine monostabile Kippglieder mit Zeitparametern; `AX_FB_R_IO` hat kein Zeitverhalten, sondern reagiert sofort auf Signale.

## Fazit

Der Funktionsblock `AX_FB_R_IO` ist ein einfacher, aber zuverlässiger Baustein zur realisierungsgetreuen Abbildung eines priorisierten Rücksetzverhaltens. Dank der Adapter-Schnittstelle fügt er sich nahtlos in ereignisgesteuerte Automatisierungssysteme ein. Die klare Reset-Dominanz macht ihn besonders geeignet für Sicherheits- und Freigabefunktionen, bei denen ein Rücksetzsignal unbedingten Vorrang haben muss.