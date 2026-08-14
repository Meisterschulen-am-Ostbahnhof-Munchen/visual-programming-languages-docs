# E_TP_RETRIG

* * * * * * * * * *
## Einleitung

Der `E_TP_RETRIG` ist die retriggerbare Variante des Standard-Timers `E_TP`: Er erzeugt bei jeder steigenden Flanke von `IN` einen `TRUE`-Impuls der Dauer `PT` an `Q` — anders als `E_TP` startet eine erneute steigende Flanke während eines laufenden Impulses diesen jedoch neu, statt ignoriert zu werden.

![E_TP_RETRIG](E_TP_RETRIG.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Prüft `IN` auf eine steigende Flanke, trägt `IN` und `PT`.
- **R**: Bricht den laufenden Impuls sofort ab.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigung, trägt `Q`.

### **Daten-Eingänge**

- **IN** (BOOL): Der auf steigende Flanken zu prüfende Eingang.
- **PT** (TIME): Dauer des Impulses.

### **Daten-Ausgänge**

- **Q** (BOOL): `TRUE` während der Impulsdauer.

## Funktionsweise

`E_R_TRIG` erkennt steigende Flanken von `IN` bei jedem `REQ`. Jede erkannte Flanke setzt `E_SR.S` (→ `Q := TRUE`) und startet gleichzeitig `E_DELAY` (mit `PT`) neu — eine erneute steigende Flanke während eines laufenden Impulses verlängert diesen also, statt ignoriert zu werden. Läuft `E_DELAY` ab, setzt es `E_SR.R` (→ `Q := FALSE`). Ein `R`-Ereignis stoppt den Timer sofort und setzt `Q` direkt zurück.

## Technische Besonderheiten

- **Retriggerbar über `IN`-Flanke statt `REQ` allein**: Im Unterschied zu [E_PULSE_RETRIG](E_PULSE_RETRIG.md), das bei *jedem* `REQ`-Ereignis retriggert, reagiert `E_TP_RETRIG` nur auf tatsächliche steigende Flanken von `IN` — wiederholte `REQ`-Ereignisse bei bereits `TRUE` gehaltenem `IN` ohne neue Flanke lösen keinen neuen Impuls aus.
- **Zusammengesetzt aus drei Standardbausteinen**: `E_R_TRIG` + `E_DELAY` + `E_SR`, keine eigene ECC.

## Zustandsübersicht

Zustandslose Verdrahtungslogik: `E_SR` hält den `Q`-Zustand, `E_DELAY` läuft bei jeder erkannten steigenden Flanke von `IN` neu an.

## Anwendungsszenarien

- **Verlängerbare Impulse ausgelöst durch Flankenwechsel**: z. B. eine Bewegungsmelder-gesteuerte Beleuchtung, bei der jede neue Bewegung (steigende Flanke von `IN`) die Leuchtdauer neu beginnen lässt.
- **Entprellte, aber verlängerbare Reaktion auf einen digitalen Eingang**, wenn nur echte Flankenwechsel und kein bloßes Wiederholen von `REQ` einen neuen Impulslauf auslösen soll.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **`E_TP`**: dieselbe Grundfunktion, aber nicht retriggerbar.
- **[E_PULSE_RETRIG](E_PULSE_RETRIG.md)**: retriggerbarer Impuls, ausgelöst über *jedes* `REQ`-Ereignis statt über eine `IN`-Flanke.
- **[E_TLIM](E_TLIM.md)**: begrenzt die Ein-Dauer von `IN` selbst, statt einen festen Impuls zu erzeugen.

## Fazit

`E_TP_RETRIG` liefert einen flankengetriggerten, verlängerbaren Impuls fester Dauer und eignet sich für Anwendungen, bei denen wiederholte echte Flankenwechsel (nicht bloße `REQ`-Wiederholungen) den Impuls am Leben halten sollen.
