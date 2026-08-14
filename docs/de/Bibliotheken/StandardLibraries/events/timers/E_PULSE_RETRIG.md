# E_PULSE_RETRIG

* * * * * * * * * *
## Einleitung

Der `E_PULSE_RETRIG` ist die retriggerbare Variante von `E_PULSE`: Er erzeugt einen `TRUE`-Impuls der Dauer `PT` an `Q`, startet den Impuls jedoch bei jedem erneuten `REQ`-Ereignis von vorne, statt ein laufendes Intervall zu ignorieren.

![E_PULSE_RETRIG](E_PULSE_RETRIG.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Startet (bzw. re-triggert) den Impuls, trägt `PT`.
- **R**: Bricht den laufenden Impuls sofort ab.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigung, trägt `Q`.

### **Daten-Eingänge**

- **PT** (TIME): Dauer des Impulses.

### **Daten-Ausgänge**

- **Q** (BOOL): `TRUE` während der Impulsdauer, sonst `FALSE`.

## Funktionsweise

Jedes `REQ`-Ereignis setzt gleichzeitig `E_SR.S` (→ `Q := TRUE`) und startet `E_DELAY` neu mit der Zeit `PT` — ein erneutes `REQ` während eines laufenden Impulses startet den `E_DELAY`-Timer also von vorne, statt zu warten, bis der ursprüngliche Impuls abgelaufen ist. Läuft `E_DELAY` ab, wird `E_SR.R` ausgelöst (`Q := FALSE`). Ein `R`-Ereignis stoppt den Timer sofort und setzt `Q` direkt zurück auf `FALSE`.

## Technische Besonderheiten

- **Retriggerbar**: Der entscheidende Unterschied zu `E_PULSE` (nicht retriggerbar) liegt darin, dass jedes `REQ` den `E_DELAY`-Timer neu startet — ein Impuls kann so durch wiederholte `REQ`-Ereignisse beliebig verlängert werden.
- **Zusammengesetzt aus `E_DELAY` + `E_SR`**: reine Verdrahtung, kein eigenes ECC.

## Zustandsübersicht

Zustandslose Verdrahtungslogik: `E_SR` hält den aktuellen `Q`-Zustand, `E_DELAY` läuft bei jedem `REQ` neu an.

## Anwendungsszenarien

- **Totzeit-/Watchdog-Logik**: `Q` soll `TRUE` bleiben, solange regelmäßig `REQ`-Ereignisse eintreffen (z. B. Lebenszeichen eines Sensors), und erst `FALSE` werden, wenn `PT` seit dem letzten `REQ` ohne weiteres `REQ` verstrichen ist.
- **Verlängerbare Impulse**, z. B. eine Beleuchtung, die bei jeder erneuten Bewegungserkennung (`REQ`) ihre Leuchtdauer neu beginnt, statt abzulaufen.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **`E_PULSE`**: dieselbe Grundfunktion, aber nicht retriggerbar (`REQ` während eines laufenden Impulses hat keine Wirkung).
- **[E_TP_RETRIG](E_TP_RETRIG.md)**: retriggerbarer Impuls, ausgelöst über eine steigende Flanke von `IN` statt über ein separates `REQ`-Ereignis.

## Fazit

`E_PULSE_RETRIG` liefert einen verlängerbaren `TRUE`-Impuls, dessen Dauer bei jedem `REQ`-Ereignis neu zu laufen beginnt, und eignet sich für Watchdog- und Totzeit-Anwendungen, bei denen ein laufender Impuls durch wiederholte Anfragen am Leben gehalten werden soll.
