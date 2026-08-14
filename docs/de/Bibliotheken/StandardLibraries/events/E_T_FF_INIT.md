# E_T_FF_INIT

![E_T_FF_INIT_ecc](./E_T_FF_INIT_ecc.svg)

* * * * * * * * * *
## Einleitung

Der `E_T_FF_INIT` (Toggle-Flipflop mit Initialisierung) kombiniert das Umschaltverhalten eines Toggle-Flipflops (Ausgang `Q` wechselt bei jedem `CLK`-Ereignis den Zustand) mit einer expliziten `INIT`/`INITO`-Schnittstelle zum gezielten Setzen eines definierten Startwerts.

![E_T_FF_INIT](E_T_FF_INIT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **INIT**: Initialisierungsanforderung, trägt `QI` und `Q_INIT`.
- **CLK**: Taktereignis, löst einen Zustandswechsel von `Q` aus.

### **Ereignis-Ausgänge**

- **INITO**: Bestätigt die (De-)Initialisierung, trägt `QO`.
- **EO**: Wird bei jedem `CLK`-Ereignis ausgelöst, trägt `Q`.

### **Daten-Eingänge**

- **QI** (BOOL): Eingangs-Event-Qualifier — `TRUE` initialisiert, `FALSE` deinitialisiert.
- **Q_INIT** (BOOL): Der Wert, auf den `Q` beim Initialisieren gesetzt wird.

### **Daten-Ausgänge**

- **QO** (BOOL): Ausgangs-Event-Qualifier, spiegelt `QI` zurück.
- **Q** (BOOL): Der aktuelle Zustand des Flipflops.

## Funktionsweise

`INIT` mit `QI = TRUE` initialisiert `Q` über `Q_INIT` (Zustände `Init` → `SET`/`RESET`, je nach `Q_INIT`). Im laufenden Betrieb wechselt jedes `CLK`-Ereignis den Zustand: aus `SET` nach `RESET` und umgekehrt, jeweils mit `EO`-Quittierung und dem entsprechend gesetzten `Q`. `INIT` mit `QI = FALSE` deinitialisiert den Baustein (`DeInit` → `START`).

## Technische Besonderheiten

- **Toggle statt Set/Reset**: Im Gegensatz zu [E_RS_SYM_INIT](E_RS_SYM_INIT.md)/[E_SR_SYM_INIT](E_SR_SYM_INIT.md), die getrennte `S`/`R`-Eingänge besitzen, hat `E_T_FF_INIT` nur einen einzigen Takteingang `CLK`, der bei jedem Ereignis zwischen `SET` und `RESET` umschaltet.
- **Gleiche INIT/DeInit-Struktur** wie die `_SYM_INIT`-Bausteine: `QI` schaltet zwischen Initialisierung und Deinitialisierung, `Q_INIT` bestimmt den Startwert.

## Zustandsübersicht

| Zustand | Bedeutung |
|---|---|
| START | Unkonfigurierter Anfangszustand |
| Init | Initialisierung läuft, `QO := QI` |
| DeInit | Deinitialisierung läuft, `QO := FALSE` |
| SET | `Q = TRUE`, wechselt bei `CLK` nach `RESET` |
| RESET | `Q = FALSE`, wechselt bei `CLK` nach `SET` |

## Anwendungsszenarien

- **Blinklogik mit definiertem Startzustand**: Ein Signal soll bei jedem Takt umschalten, aber nach dem Systemstart mit einem bekannten Anfangswert (`Q_INIT`) beginnen, statt mit einem zufälligen Zustand.
- **Frequenzteilung**: `E_T_FF_INIT` halbiert die Ereignisfrequenz von `CLK` auf `EO` (Zustandswechsel bei jedem zweiten `CLK` wieder in denselben Zustand), mit kontrolliertem Startwert.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **`E_T_FF`**: dieselbe Toggle-Grundfunktion ohne `INIT`/`INITO`-Schnittstelle.
- **[E_RS_SYM_INIT](E_RS_SYM_INIT.md) / [E_SR_SYM_INIT](E_SR_SYM_INIT.md)**: dieselbe INIT/DeInit-Struktur, aber mit getrenntem Set-/Reset-Eingang statt eines einzelnen Takteingangs.
- **[E_T_FF_SR_SYM](../E_T_FF_SR_SYM.md) / [E_T_FF_SR_SYM_INIT](../E_T_FF_SR_SYM_INIT.md)**: kombinieren zusätzlich `S`/`R`-Eingänge mit dem Toggle-Verhalten.

## Fazit

`E_T_FF_INIT` liefert ein Toggle-Flipflop mit projektierbarem, garantiert definiertem Startwert und eignet sich für Blink- und Frequenzteilerlogik, bei der der Zustand nach dem Systemstart nicht dem Zufall überlassen werden soll.
