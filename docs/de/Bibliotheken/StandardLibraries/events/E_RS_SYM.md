# E_RS_SYM

![E_RS_SYM_ecc](./E_RS_SYM_ecc.svg)

* * * * * * * * * *

## Einleitung

Der `E_RS_SYM` (Event-driven RS Flip-Flop, symmetrisches Start-Up-Verhalten) ist ein ereignisgesteuertes, bistabiles Speicherelement nach IEC 61499. Er verhält sich funktional wie [E_RS](../E_RS.md)/[E_SR](../E_SR.md), unterscheidet sich aber im Startzustand: Während `E_RS`/`E_SR` erst nach dem ersten `S`- oder `R`-Ereignis einen definierten Ausgang liefern, reagiert `E_RS_SYM` bereits im Anfangszustand `START` symmetrisch auf beide Ereignisse und wechselt sofort in den passenden `SET`- bzw. `RESET`-Zustand.

![E_RS_SYM](E_RS_SYM.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **S (Set)**: Setzt den Ausgang `Q` auf `TRUE`.
- **R (Reset)**: Setzt den Ausgang `Q` auf `FALSE`.

### **Ereignis-Ausgänge**

- **EO (Event Output)**: Wird nach jedem `S`- oder `R`-Ereignis ausgelöst.
    - **Verbundene Daten**: `Q`

### **Daten-Ausgänge**

- **Q**: Der aktuelle Zustand des Flip-Flops (Datentyp: `BOOL`).

## Funktionsweise

Die ECC besitzt drei Zustände: `START`, `SET` und `RESET`. Aus `START` führt sowohl ein `S`- als auch ein `R`-Ereignis zu einem definierten Folgezustand (`SET` bzw. `RESET`) — im Gegensatz zu `E_RS`, bei dem `START` nur auf eines der beiden Ereignisse reagiert und das andere zunächst wirkungslos verpufft. Aus `SET` und `RESET` heraus verhält sich der Baustein wie das klassische RS-Flipflop: `R` schaltet von `SET` nach `RESET`, `S` von `RESET` nach `SET`. Jeder Zustandswechsel führt die Algorithmen `SET` (`Q := TRUE`) bzw. `RESET` (`Q := FALSE`) aus und löst `EO` aus.

## Technische Besonderheiten

- **Symmetrisches Start-Up-Verhalten**: Der entscheidende Unterschied zu `E_RS`/`E_SR` liegt im Zustand `START`: Beide Eingangsereignisse (`S` und `R`) führen dort zu einem definierten Übergang, sodass unabhängig davon, welches Ereignis nach dem Start zuerst eintrifft, ein korrekter `Q`-Wert gesetzt wird.
- **Kein Init-Mechanismus**: Anders als [E_RS_SYM_INIT](E_RS_SYM_INIT.md) besitzt dieser Baustein keine `INIT`/`INITO`-Schnittstelle; der Startzustand ergibt sich ausschließlich aus dem ersten eintreffenden `S`- oder `R`-Ereignis.

## Zustandsübersicht

| Zustand | Bedeutung |
| --- | --- |
| START | Anfangszustand, wartet symmetrisch auf `S` oder `R` |
| SET | `Q = TRUE`, erreichbar aus `START` (via `S`) oder `RESET` (via `S`) |
| RESET | `Q = FALSE`, erreichbar aus `START` (via `R`) oder `SET` (via `R`) |

## Anwendungsszenarien

- **Start/Stopp-Logik mit garantiertem Erstzustand**: Überall dort, wo nach einem Neustart der Applikation nicht vorhersehbar ist, ob zuerst ein Set- oder ein Reset-Signal eintrifft, aber trotzdem sofort ein korrekter `Q`-Wert benötigt wird.
- **Fehlerspeicherung**: Wie bei `E_RS`, jedoch mit der zusätzlichen Garantie, dass auch ein erstes `R`-Ereignis (z. B. eine Quittierung vor dem ersten Fehler) korrekt zu `Q = FALSE` führt.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **[E_RS](../E_RS.md) / [E_SR](../E_SR.md)**: funktional nahezu identisch, aber ohne symmetrisches Start-Up-Verhalten — im Anfangszustand reagiert nur eines der beiden Ereignisse.
- **[E_RS_SYM_INIT](E_RS_SYM_INIT.md)**: dieselbe Grundfunktion, erweitert um eine explizite `INIT`/`INITO`-Schnittstelle zum gezielten Setzen des Startwerts.
- **[E_SR_SYM](E_SR_SYM.md)**: funktional identisch, lediglich die Reihenfolge von `S`/`R` in der Schnittstellendefinition ist vertauscht (Namenskonvention analog zu `E_RS`/`E_SR`).

## Fazit

`E_RS_SYM` liefert ein bistabiles Speicherelement mit garantiert definiertem Verhalten direkt ab dem ersten eintreffenden Ereignis und eignet sich damit überall dort, wo das Verhalten von `E_RS`/`E_SR` im Anfangszustand nicht ausreicht.
