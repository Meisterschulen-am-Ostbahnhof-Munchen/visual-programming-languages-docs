# AX_T_FF_SR_SYM


![AX_T_FF_SR_SYM](./AX_T_FF_SR_SYM.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock AX_T_FF_SR_SYM ist ein ereignisgesteuerter bistabiler Kippschalter mit zusätzlicher Toggle-Funktion und symmetrischem Startverhalten. Er kombiniert die Eigenschaften eines SR-Flipflops (Setzen und Rücksetzen) mit denen eines T-Flipflops (Umschalten bei jedem Taktsignal). Das Verhalten nach dem Einschalten ist symmetrisch ausgelegt, d.h. der Baustein befindet sich zunächst in einem neutralen Startzustand und geht erst durch ein Ereignis in einen definierten Zustand über.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **S** – Set: Setzt den Ausgang Q auf TRUE.
- **R** – Reset: Setzt den Ausgang Q auf FALSE.
- **CLK** – Clock: Schaltet (toggelt) den Ausgang Q um (TRUE → FALSE oder FALSE → TRUE).

### **Ereignis-Ausgänge**
Keine direkten Ereignis-Ausgänge. Die Ausgabe des Zustands erfolgt über den Adapter Q. Der Adapter löst bei Zustandsänderung das Ereignis Q.E1 aus.

### **Daten-Eingänge**
Keine.

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge. Der aktuelle Wert wird über den Adapter Q bereitgestellt (Q.D1).

### **Adapter**
- **Q**: Adapter vom Typ `adapter::types::unidirectional::AX` (unidirektional). Stellt den aktuellen Zustand des Flipflops als booleschen Wert (TRUE/FALSE) zur Verfügung. Der Adapter löst nach jeder Zustandsänderung das Ereignis Q.E1 aus.

## Funktionsweise
Der FB besitzt drei Ereignis-Eingänge und eine Zustandsmaschine mit drei Zuständen: `START`, `SET` und `RESET`.

- **START** ist der initiale Zustand nach dem Einschalten. In diesem Zustand ist kein Algorithmus aktiv, und der Ausgangswert ist undefiniert.
  - Bei Eintreffen von `S` oder `CLK` wechselt der FB in den Zustand `SET`.
  - Bei Eintreffen von `R` wechselt er in den Zustand `RESET`.

- Im Zustand **SET** wird der Algorithmus `SET` ausgeführt: `Q.D1 := TRUE`. Anschließend wird das Ereignis `Q.E1` ausgelöst.
  - Bei `R` oder `CLK` wechselt der FB in den Zustand `RESET`.

- Im Zustand **RESET** wird der Algorithmus `RESET` ausgeführt: `Q.D1 := FALSE`. Anschließend wird `Q.E1` ausgelöst.
  - Bei `S` oder `CLK` wechselt der FB zurück in den Zustand `SET`.

Die Toggle-Funktion wird durch die `CLK`-Transitionen realisiert: unabhängig vom aktuellen Zustand führt `CLK` zum jeweils anderen Zustand.

## Technische Besonderheiten
- **Symmetrisches Startverhalten**: Nach dem Einschalten befindet sich der FB im neutralen `START`-Zustand. Erst das erste Ereignis legt den Anfangszustand fest. Dadurch kann das System definiert initialisiert werden.
- **Adapter-basierte Ausgabe**: Statt eines direkten Datenausgangs wird der Zustand über einen Adapter (`AX`) bereitgestellt. Dies ermöglicht eine flexible Kopplung mit anderen Bausteinen und eine einfache Ereignisweitergabe.
- **Kombination von SR- und T-Flipflop**: Der Baustein vereint Setzen, Rücksetzen und Toggeln in einer kompakten Einheit.

## Zustandsübersicht
| Zustand | Beschreibung | Ausgang Q.D1 | Ereignis nach Algorithmus |
|---------|--------------|--------------|---------------------------|
| START   | Initialzustand, kein definierter Wert | undefiniert | - |
| SET     | Ausgang wird auf TRUE gesetzt | TRUE | Q.E1 |
| RESET   | Ausgang wird auf FALSE gesetzt | FALSE | Q.E1 |

Übergänge (Ereignis → Zielzustand):
- START → SET: `S`, `CLK`
- START → RESET: `R`
- SET → RESET: `R`, `CLK`
- RESET → SET: `S`, `CLK`

## Anwendungsszenarien
- **Steuerung von binären Ausgängen**: Ein Ausgang kann sowohl gesetzt, zurückgesetzt als auch umgeschaltet werden (z.B. manuelle Bedienung mit Set/Reset und automatischem Toggle durch einen Takt).
- **Hin- und Herschalten**: Ein Prozess, der bei jedem Taktsignal seinen Zustand wechselt, aber auch explizit gesetzt oder zurückgesetzt werden kann.
- **Definierte Startsequenzen**: Das symmetrische Startverhalten stellt sicher, dass der Baustein nach dem Einschalten noch keinen Ausgangswert ausgibt, bis ein Befehl eintrifft.

## Vergleich mit ähnlichen Bausteinen
- **E_SR (reines SR-Flipflop)**: Hat nur Set- und Reset-Eingänge, keine Toggle-Funktion. Nach dem Start ist der Ausgang üblicherweise FALSE.
- **E_T (Toggle-Flipflop)**: Nur Toggle-Eingang, kein Set/Reset.
- **AX_T_FF_SR_SYM**: Vereint alle drei Funktionen und bietet zusätzlich einen neutralen Startzustand, der eine flexible Initialisierung erlaubt.

## Fazit
Der AX_T_FF_SR_SYM ist ein vielseitiger Funktionsblock für binäre Zustandslogik. Die Kombination aus Set, Reset und Toggle sowie das symmetrische Startverhalten machen ihn besonders geeignet für Anwendungen, die sowohl manuelle Steuerung als auch automatisches Umschalten erfordern. Die Adapter-Schnittstelle erleichtert die Einbindung in modulare Systeme wie IEC 61499.