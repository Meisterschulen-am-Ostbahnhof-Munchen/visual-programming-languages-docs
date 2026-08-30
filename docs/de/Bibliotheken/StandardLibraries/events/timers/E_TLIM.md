# E_TLIM

* * * * * * * * * *

## Einleitung

Der `E_TLIM` (Time-Limiting) begrenzt, wie lange `Q` maximal `TRUE` bleiben kann: Sobald `IN` auf `TRUE` wechselt, wird `Q` ebenfalls `TRUE`; bleibt `IN` länger als `PT` auf `TRUE`, schaltet `Q` nach Ablauf von `PT` automatisch auf `FALSE` (Timeout). Fällt `IN` vor Ablauf von `PT` bereits zurück auf `FALSE`, folgt `Q` sofort.

![E_TLIM](E_TLIM.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Auslösung, trägt `IN` und `PT`.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigung, trägt `Q`.

### **Daten-Eingänge**

- **IN** (BOOL): Der zu überwachende Eingangszustand.
- **PT** (TIME): Maximale Zeit, die `Q` nach einer steigenden Flanke von `IN` `TRUE` bleiben darf.

### **Daten-Ausgänge**

- **Q** (BOOL): `TRUE`, solange `IN` `TRUE` ist und `PT` noch nicht abgelaufen ist.

## Funktionsweise

`E_RF_TRIG` erkennt Flankenwechsel von `IN`: Eine steigende Flanke (`ER`) startet `E_DELAY` (mit `PT`) und setzt `E_SR.S` (→ `Q := TRUE`). Eine fallende Flanke (`EF`) stoppt `E_DELAY` sofort und setzt `E_SR.R` (→ `Q := FALSE`) — `IN` gewinnt also immer gegenüber dem Timeout. Läuft stattdessen `E_DELAY` vollständig ab (weil `IN` länger als `PT` `TRUE` blieb), löst dies ebenfalls `E_SR.R` aus, wodurch `Q` auch ohne fallende Flanke von `IN` auf `FALSE` zurückfällt (Timeout-Fall).

## Technische Besonderheiten

- **Zwei Wege zu `Q := FALSE`**: entweder durch eine fallende Flanke von `IN` (regulärer Fall) oder durch Ablauf von `PT` (Timeout-Fall) — beide führen über `E_SR.R`.
- **Zusammengesetzt aus drei Standardbausteinen**: `E_RF_TRIG` (Flankenerkennung) + `E_DELAY` (Timeout-Timer) + `E_SR` (Zustandsspeicher), keine eigene ECC.

## Zustandsübersicht

| Zustand (implizit über `E_SR`/`E_DELAY`) | Bedeutung |
| --- | --- |
| Q = FALSE, Timer inaktiv | Ruhezustand, `IN = FALSE` |
| Q = TRUE, Timer läuft | `IN` ist `TRUE`, `PT` noch nicht abgelaufen |
| Q = FALSE (Timeout) | `IN` war länger als `PT` `TRUE`, automatisch zurückgesetzt |

## Anwendungsszenarien

- **Überwachung von Maximaldauern**: Ein Signal darf höchstens `PT` lang aktiv sein (z. B. maximale Einschaltdauer eines Aktors als Sicherheitsbegrenzung); bleibt `IN` länger aktiv, wird `Q` automatisch zurückgesetzt.
- **Timeout-Überwachung von Prozessschritten**: `IN` markiert den laufenden Schritt, `Q` zeigt an, ob der Schritt noch innerhalb der zulässigen Zeit `PT` liegt.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **`E_TON`/`E_TOF`** (Standard-IEC-61131-3-Timer): verzögern das *Einschalten* bzw. *Ausschalten* von `Q` relativ zu `IN`, begrenzen aber nicht dessen maximale Ein-Dauer.
- **[E_PULSE_RETRIG](E_PULSE_RETRIG.md) / [E_TP_RETRIG](E_TP_RETRIG.md)**: erzeugen einen Impuls fester Dauer, unabhängig davon, wie lange `IN`/`REQ` tatsächlich aktiv bleibt.
- **`E_RF_TRIG`**: die intern verwendete Flankenerkennung.

## Fazit

`E_TLIM` begrenzt die maximale Ein-Dauer eines `BOOL`-Signals und eignet sich als einfache Zeitüberwachung für Aktoren oder Prozessschritte, bei denen ein zu langes Verweilen im `TRUE`-Zustand automatisch beendet werden soll.
