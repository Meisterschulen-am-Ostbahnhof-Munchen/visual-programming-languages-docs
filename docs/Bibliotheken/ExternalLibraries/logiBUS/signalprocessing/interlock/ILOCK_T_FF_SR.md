# ILOCK_T_FF_SR


![ILOCK_T_FF_SR](./ILOCK_T_FF_SR.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock `ILOCK_T_FF_SR` ist ein zusammengesetzter Baustein (Composite FB), der ein verriegelbares Toggle-Flipflop mit Set- und Reset-Funktionalität realisiert. Er besitzt eine Adapter-Schnittstelle (AE2), die eine bidirektionale Kommunikation mit anderen Instanzen ermöglicht und zur Interlock-Verkettung dient. Das Flipflop schaltet seinen Ausgang `Q` bei jedem steigenden Flanke des Clock-Eingangs `CLK` um, sofern kein Reset- oder Set-Ereignis anliegt. Die Verriegelung erfolgt über die Adapter, die von externen Bausteinen gesetzt werden können.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Beschreibung |
|------|-----|-------------|
| `S`   | Event | Setzt den Ausgang `Q` auf TRUE |
| `R`   | Event | Setzt den Ausgang `Q` auf FALSE |
| `CLK` | Event | Clock-Ereignis – löst einen Toggle des Ausgangs `Q` aus |

### **Ereignis-Ausgänge**

| Name | Typ | Beschreibung |
|------|-----|-------------|
| `EO`  | Event | Wird nach jeder Änderung des internen Zustands (Set, Reset oder Toggle) ausgelöst |

### **Daten-Eingänge**

Keine.

### **Daten-Ausgänge**

| Name | Typ | Beschreibung |
|------|-----|-------------|
| `Q`   | BOOL | Aktueller Zustand des Flipflops (TRUE = gesetzt, FALSE = zurückgesetzt) |

### **Adapter**

| Name | Typ | Richtung | Beschreibung |
|------|-----|----------|-------------|
| `ILOCK_IN`  | AE2 (bidirektional) | Socket (Eingang) | Ermöglicht den Empfang von Verriegelungssignalen von vorgeschalteten Bausteinen |
| `ILOCK_OUT` | AE2 (bidirektional) | Plug (Ausgang) | Sendet Verriegelungssignale an nachgeschaltete Bausteine |

Die Adapter `ILOCK_IN` und `ILOCK_OUT` sind Typ `AE2` (allgemeiner, bidirektionaler Adapter). Sie werden verwendet, um mehrere Instanzen des Bausteins zu einer Kaskade zu verbinden, sodass ein gesetzter Zustand eines Bausteins andere Bausteine zurücksetzen kann (Interlock).

## Funktionsweise

Der Baustein basiert auf einem internen Netzwerk, das aus drei primitiven Funktionsblöcken besteht: einem `E_SR` (Set/Reset-Flipflop), einem `E_SWITCH` (ereignisgesteuerter Umschalter) und einem `E_MERGE_2` (Ereignis-Zusammenführer).

- **Setzen (`S`):** Ein Ereignis an `S` wird über `E_MERGE_2` direkt an den Set-Eingang des `E_SR` geleitet. Der Ausgang `Q` wird auf TRUE gesetzt. Gleichzeitig werden die Ereignisse über die Adapter an die verbundenen Bausteine weitergegeben.
- **Rücksetzen (`R`):** Ein Ereignis an `R` geht direkt an den Reset-Eingang des `E_SR`. Der Ausgang `Q` wird auf FALSE gesetzt. Auch von den Adaptern eingehende Reset-Signale (über `ILOCK_IN.EO1` und `ILOCK_OUT.EI1`) führen zum Rücksetzen.
- **Toggle (`CLK`):** Ein Ereignis an `CLK` wird dem `E_SWITCH` zugeführt. Dessen Steuereingang `G` ist mit dem aktuellen Ausgang `Q` verbunden.
  - Ist `Q = FALSE`, wird das Clock-Ereignis über den Ausgang `EO0` an `E_MERGE_2.EI2` weitergeleitet und von dort zum Set-Eingang des `E_SR`. Somit wird `Q` auf TRUE gesetzt.
  - Ist `Q = TRUE`, wird das Clock-Ereignis über den Ausgang `EO1` direkt an den Reset-Eingang des `E_SR` gelegt. `Q` wird auf FALSE gesetzt.
  Dadurch entsteht das Toggle-Verhalten: Jeder Clock-Impuls kehrt den aktuellen Zustand von `Q` um.

- **Verriegelung (Interlock):** Die Adapter `ILOCK_IN` und `ILOCK_OUT` sind so verschaltet, dass ein eingehendes Ereignis von `ILOCK_IN` (z.B. von einem vorherigen Baustein) den Reset-Eingang auslöst und gleichzeitig über `ILOCK_OUT` an den nächsten Baustein weitergereicht wird. So kann eine Kette von Flipflops aufgebaut werden, bei der immer nur einer aktiv sein darf.

Nach jeder Zustandsänderung wird der Ereignisausgang `EO` ausgelöst.

## Technische Besonderheiten

- **Composite FB:** Der Baustein ist als Netzwerk aus IEC 61499-Elementarmodulen realisiert. Dadurch ist das Verhalten transparent und nachvollziehbar.
- **Bidirektionale Adapter:** Die Verwendung des Adaptertyps `AE2` ermöglicht eine flexible Kopplung, sowohl als Socket (Eingang) als auch als Plug (Ausgang).
- **Konfliktbehandlung:** Wenn gleichzeitig ein Set- und ein Reset-Ereignis eintreffen (z.B. `S` und `R`), hat das Reset-Vorrang, da der Reset-Eingang des `E_SR` mehrere Quellen hat und priorisiert behandelt wird. Die genaue Priorität ergibt sich aus der E_SR-Implementierung (Standard: Reset hat Vorrang vor Set).
- **Keine Daten-Eingänge:** Der Baustein arbeitet rein ereignisgesteuert; der Zustand wird nur durch Ereignisse verändert.

## Zustandsübersicht

Das interne Flipflop `E_SR` kennt die zwei Zustände:

- **Zustand FALSE** (Q = FALSE): Der Ausgang ist zurückgesetzt. Ein Clock-Ereignis führt zum Setzen.
- **Zustand TRUE** (Q = TRUE): Der Ausgang ist gesetzt. Ein Clock-Ereignis führt zum Rücksetzen.

Ein Set-Ereignis (`S`) führt unabhängig vom aktuellen Zustand immer in den Zustand TRUE.  
Ein Reset-Ereignis (`R`) führt unabhängig vom aktuellen Zustand immer in den Zustand FALSE.

| Aktueller Zustand | Ereignis | Neuer Zustand | Ausgangsaktionen |
|-------------------|----------|---------------|------------------|
| FALSE             | `S`      | TRUE          | `EO` wird ausgelöst |
| FALSE             | `R`      | FALSE         | `EO` wird ausgelöst |
| FALSE             | `CLK`    | TRUE          | `EO` wird ausgelöst |
| TRUE              | `S`      | TRUE          | `EO` wird ausgelöst |
| TRUE              | `R`      | FALSE         | `EO` wird ausgelöst |
| TRUE              | `CLK`    | FALSE         | `EO` wird ausgelöst |

Die Adapter-Ereignisse wirken wie ein externer Reset und setzen den Zustand auf FALSE.

## Anwendungsszenarien

- **Interlock-Steuerung in Sicherheitskreisen:** Mehrere Maschinen oder Antriebe sollen sich gegenseitig verriegeln. Nur eine darf zu einem Zeitpunkt aktiv sein. Durch Verkettung mehrerer `ILOCK_T_FF_SR` kann sichergestellt werden, dass stets nur ein Flipflop gesetzt ist.
- **Zustandsmaschinen mit wechselnden Modi:** Der Baustein eignet sich als Toggle-Flipflop, das durch externe Set/Reset-Signale übersteuert werden kann, z.B. für manuelle Eingriffe.
- **Kaskadierte Schaltungen mit Rückmeldung:** Die Adapter-Schnittstelle ermöglicht das einfache Einbinden in bestehende AE2-basierte Kommunikationsstrukturen.

## Vergleich mit ähnlichen Bausteinen

- **Standard T-FF (IEC 61499 `E_T_FF`):** Bietet nur Toggle-Funktion ohne separate Set/Reset-Eingänge. Der `ILOCK_T_FF_SR` erweitert dies um die Set- und Reset-Steuerung.
- **Standard SR-FF (z.B. `E_SR`):** Hat nur Set und Reset, kein Toggle. Der vorliegende Baustein kombiniert Toggle mit SR.
- **Baustein mit Verriegelung (Interlock):** Viele herstellerspezifische Blöcke realisieren Interlock über Busse; dieser Baustein nutzt standardisierte Adapter (AE2) und ist dadurch portabler.

## Fazit

Der `ILOCK_T_FF_SR` ist ein vielseitiger Funktionsblock, der ein Toggle-Flipflop mit Set/Reset und einer Interlock-Schnittstelle vereint. Die klare Trennung zwischen Logik und Adapter-Anbindung erlaubt den Aufbau sicherer, kaskadierbarer Schaltungen. Durch die Verwendung von IEC 61499-Standardbausteinen bleibt das Verhalten nachvollziehbar und erweiterbar.