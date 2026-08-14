# E_T_FF_SR_SYM

![E_T_FF_SR_SYM_ecc](./E_T_FF_SR_SYM_ecc.svg)

* * * * * * * * * *
## Einleitung

Der `E_T_FF_SR_SYM` vereint in einem Baustein die Funktionalität von [E_RS_SYM](E_RS_SYM.md) (bistabiles Set/Reset mit symmetrischem Start-Up) und eines Toggle-Flipflops: Zusätzlich zu den Eingängen `S` und `R` besitzt er einen Takteingang `CLK`, der den Ausgang `Q` unabhängig von `S`/`R` umschaltet.

![E_T_FF_SR_SYM](E_T_FF_SR_SYM.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **S (Set)**: Setzt `Q` auf `TRUE`.
- **R (Reset)**: Setzt `Q` auf `FALSE`.
- **CLK**: Kehrt den aktuellen Zustand von `Q` um (Toggle).

### **Ereignis-Ausgänge**

- **EO**: Wird nach jedem `S`-, `R`- oder `CLK`-Ereignis ausgelöst, trägt `Q`.

### **Daten-Ausgänge**

- **Q** (BOOL): Der aktuelle Zustand.

## Funktionsweise

Aus dem Anfangszustand `START` führen `S`, `R` **und** `CLK` zu einem definierten Folgezustand (`CLK` führt dabei nach `SET`) — das symmetrische Start-Up-Verhalten von `E_RS_SYM` gilt hier für alle drei Ereignisse. Im laufenden Betrieb (Zustände `SET`/`RESET`) schaltet `S` nach `SET`, `R` nach `RESET`, und `CLK` schaltet jeweils in den *entgegengesetzten* Zustand (Toggle) — unabhängig vom vorherigen `S`/`R`-Aufruf. Jeder Übergang setzt `Q` entsprechend und löst `EO` aus.

## Technische Besonderheiten

- **Kombiniertes Set/Reset/Toggle-Verhalten**: Anders als `E_T_FF`, das ausschließlich toggelt, kann `Q` hier sowohl gezielt über `S`/`R` gesetzt als auch über `CLK` umgeschaltet werden.
- **Symmetrisches Start-Up für alle drei Eingänge**: `START` reagiert auf `S`, `R` und `CLK` gleichermaßen definiert.
- **Kein Init-Mechanismus**: Für eine projektierbare Startwert-Initialisierung siehe [E_T_FF_SR_SYM_INIT](E_T_FF_SR_SYM_INIT.md).

## Zustandsübersicht

| Zustand | Bedeutung |
|---|---|
| START | Anfangszustand, reagiert symmetrisch auf `S`, `R`, `CLK` |
| SET | `Q = TRUE`; `R`→RESET, `CLK`→RESET |
| RESET | `Q = FALSE`; `S`→SET, `CLK`→SET |

## Anwendungsszenarien

- **Handbetrieb mit Taktumschaltung**: Ein Zustand kann sowohl gezielt gesetzt/rückgesetzt (`S`/`R`, z. B. durch einen Bediener) als auch getaktet umgeschaltet werden (`CLK`, z. B. durch einen Timer), ohne zwei getrennte Bausteine zu benötigen.
- **Blinklogik mit Override**: Ein Blinksignal (`CLK`) kann jederzeit durch ein explizites `S`/`R` überschrieben werden.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **[E_RS_SYM](E_RS_SYM.md)**: dieselbe Set/Reset-Logik, aber ohne `CLK`-Toggle-Eingang.
- **`E_T_FF`**: reiner Toggle-Baustein ohne `S`/`R`.
- **[E_T_FF_SR_SYM_INIT](E_T_FF_SR_SYM_INIT.md)**: dieselbe Funktion, erweitert um `INIT`/`INITO`.

## Fazit

`E_T_FF_SR_SYM` kombiniert gezieltes Set/Reset mit Toggle-Funktionalität in einem Baustein mit garantiert definiertem Startverhalten und eignet sich überall dort, wo beide Bedienarten gleichzeitig benötigt werden.
