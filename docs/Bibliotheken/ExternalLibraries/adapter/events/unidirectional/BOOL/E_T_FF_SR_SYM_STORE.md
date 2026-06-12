# E_T_FF_SR_SYM_STORE


![E_T_FF_SR_SYM_STORE](./E_T_FF_SR_SYM_STORE.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `E_T_FF_SR_SYM_STORE` realisiert ein ereignisgesteuertes bistabiles Kippglied (Flipflop) mit den Funktionen **Setzen** (S), **Rücksetzen** (R) und **Toggeln** (CLK). Das besondere Merkmal ist das **symmetrische Start‑Up‑Verhalten**: Der Initialzustand des Ausgangs Q wird über einen Adapter (`Q_INIT`) beim Hochfahren oder nach einem `INIT`‑Ereignis festgelegt. Dadurch verhält sich der Baustein zu jedem Startzeitpunkt deterministisch und wiederholbar – eine wichtige Eigenschaft für sicherheitskritische oder vorhersagbare Automatisierungssysteme.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `S`   | Event | Setzen des Ausgangs Q auf TRUE |
| `R`   | Event | Rücksetzen des Ausgangs Q auf FALSE |
| `CLK` | Event | Toggle – wechselt Q (TRUE → FALSE oder FALSE → TRUE) |

### **Ereignis-Ausgänge**

| Name | Typ | Mit Daten | Kommentar |
|------|-----|-----------|-----------|
| `EO`  | Event | Q | Zeigt an, dass sich der Wert von Q geändert hat |

### **Daten-Eingänge**

Keine (alle Eingaben erfolgen über Ereignisse).

### **Daten-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `Q`   | BOOL | Aktueller Wert des Flipflops (TRUE oder FALSE) |

### **Adapter**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `Q_INIT` | `adapter::types::bidirectional::AX2` | Legt den Startwert von Q beim INIT‑Ereignis fest. Der Adapter stellt einen ereignisgesteuerten bidirektionalen Kanal bereit: Q_INIT.EI1 löst die Initialisierung aus, Q_INIT.DI1 liefert den gewünschten Initialwert (TRUE oder FALSE). Zusätzlich gibt der Baustein über Q_INIT.DO1 den gesetzten Wert zurück. |

## Funktionsweise

Der interne Ablauf wird durch die Endliche Zustandsmaschine (ECC) gesteuert:

1. **START‑Zustand:** Nach Spannungsversorgung oder System‑Reset befindet sich der Baustein im Zustand `START`.
2. **Initialisierung (Zustand `Init`):** Sobald das Ereignis `Q_INIT.EI1` eintrifft, wird der Zustand `Init` erreicht. Anschließend wird anhand des booleschen Wertes von `Q_INIT.DI1` entschieden:
   - `TRUE` → Übergang in den Zustand `SET`
   - `FALSE` → Übergang in den Zustand `RESET`
3. **Betriebs‑Zustände `SET` und `RESET`:**
   - **SET:** Setzt `Q := TRUE` und `Q_INIT.DO1 := TRUE`. Sendet Ausgangsereignis `EO` und Adapter‑Ausgangsereignis `Q_INIT.EO1`.
   - **RESET:** Setzt `Q := FALSE` und `Q_INIT.DO1 := FALSE`. Sendet ebenfalls `EO` und `Q_INIT.EO1`.
4. **Umschalten zwischen SET und RESET:**
   - Ereignis `S` (wenn im Zustand RESET) → wechselt in SET.
   - Ereignis `R` (wenn im Zustand SET) → wechselt in RESET.
   - Ereignis `CLK` (immer) → toggelt zwischen den beiden Zuständen.

Der Ausgang `EO` wird bei jeder Zustandsänderung von Q aktiviert.

## Technische Besonderheiten

- **Symmetrisches Start‑Up:** Anders als einfache SR‑Flipflops mit festem Startwert (z. B. FALSE) kann der Startwert über den Adapter konfiguriert werden. Dies erhöht die Flexibilität und Reproduzierbarkeit.
- **Toggle‑Funktion:** Der `CLK`‑Eingang erlaubt ein Wechseln des Zustands ohne Kenntnis des aktuellen Wertes – nützlich für Zähler, Blinkgeber oder Zustandsautomaten.
- **Bidirektionale Adapter‑Schnittstelle:** Der Baustein meldet seinen gesetzten Wert zurück an den Adapter (`Q_INIT.DO1`), sodass der Initialisierungsgeber den endgültigen Zustand bestätigen kann.
- **Priorisierung:** Bei gleichzeitigem Eintreffen von `S`, `R` oder `CLK` wird nur das zuerst verarbeitete Ereignis berücksichtigt (basierend auf der Event‑Reihenfolge in der 4diac‑IDE). Im konkreten Entwurf wird `CLK` als Toggle auf den aktuellen Zustand angewendet, während `S` und `R` unabhängig vom Toggle den Zustand setzen. Die Zustandsübergänge zeigen, dass `CLK` aus jedem Zustand in den jeweils anderen führt.

## Zustandsübersicht

Die Zustandsmaschine (ECC) umfasst vier Zustände:

| Zustand | Beschreibung | Ausgehende Transitionen |
|---------|--------------|--------------------------|
| `START` | Initialer Ruhezustand nach dem Einschalten | → `Init` bei `Q_INIT.EI1` |
| `Init` | Initialisierungs‑Zustand – entscheidet über Startwert | → `SET` bei `TRUE = Q_INIT.DI1`<br>→ `RESET` bei `FALSE = Q_INIT.DI1` |
| `SET` | Q = TRUE | → `RESET` bei `R` oder `CLK` |
| `RESET` | Q = FALSE | → `SET` bei `S` oder `CLK` |

Nach dem Verlassen von `Init` wird der Zustand `SET` oder `RESET` erreicht; die Zustände `START` und `Init` werden im Normalbetrieb nicht mehr durchlaufen.

## Anwendungsszenarien

- **Maschinensteuerung mit definiertem Startzustand:** Eine Anlage soll nach einem Reset immer in einem bestimmten Arbeitsmodus starten. Über `Q_INIT` kann z. B. über eine SPS‑Konfiguration vorgegeben werden, ob eine Ventilposition beim Start geöffnet oder geschlossen ist.
- **Toggeln als Blinkfunktion:** Der `CLK`‑Eingang kann periodisch getriggert werden (z. B. durch einen Timer‑Baustein), um eine blinkende Signalisierung zu realisieren.
- **Redundante Rückmeldung:** Der Adapter‑Ausgang `Q_INIT.DO1` liefert den gesetzten Wert zurück – ideal für Sicherheitsfunktionen, die eine Rückmeldung des Schaltzustandes benötigen.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Eigenschaften | Unterschied zu `E_T_FF_SR_SYM_STORE` |
|----------|--------------|---------------------------------------|
| `E_SR_FF` (Standard‑SR‑Flipflop) | Setzen, Rücksetzen; meist kein Toggle, kein konfigurierbarer Startwert | Fehlende Toggle‑Funktion; Startwert oft fest auf FALSE |
| `E_RS_FF` | Setzen priorisiert | Andere Priorisierung; kein Toggle |
| `E_D_FF` (D‑Flipflop) | Übernahme eines Dateneingangs mit Takt | Kein Setzen/Rücksetzen ohne Daten; kein symmetrischer Start |
| `E_CTU` (Zähler) | Zählen von Ereignissen | kein bistabiles Verhalten, sondern Zählerstand |

Der `E_T_FF_SR_SYM_STORE` vereint SR‑Funktion, Toggle und initialisierten Startwert in einem Baustein – eine seltene Kombination in der IEC 61499‑Welt.

## Fazit

Der **E_T_FF_SR_SYM_STORE** ist ein leistungsfähiger ereignisgesteuerter Flipflop‑Baustein für die 4diac‑IDE. Er bietet eine vollständige SR‑Funktion, eine Toggle‑Option und ein symmetrisches, über einen Adapter konfigurierbares Start‑Up‑Verhalten. Dies macht ihn besonders für Anwendungen geeignet, die deterministische Initialisierung und flexible Umschaltmechanismen erfordern. Die bidirektionale Adapter‑Schnittstelle erhöht die Integrationstiefe in komplexe Steuerungsarchitekturen.