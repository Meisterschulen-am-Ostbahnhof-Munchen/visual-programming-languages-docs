# AX_SR_SYM_INIT


![AX_SR_SYM_INIT](./AX_SR_SYM_INIT.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AX_SR_SYM_INIT** realisiert ein ereignisgesteuertes, bistabiles Flipflop (Set-Reset) mit symmetrischem Start‑up‑Verhalten und einer speziellen Initialisierungslogik. Er erweitert das klassische SR‑Flipflop um einen qualifizierten Initialisierungs- und Deinitialisierungsablauf, bei dem der Ausgangszustand über den Eingang `Q_INIT` vorgegeben wird und die gesamte Logik nur dann aktiv ist, wenn der Qualifier `QI` den Wert `TRUE` besitzt.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Typ | Beschreibung |
|----------|-----|--------------|
| INIT     | EInit | Initialisierungsanforderung; mit `QI` und `Q_INIT` verknüpft |
| S        | Event | Setzt den Ausgang `Q` (über Adapter) |
| R        | Event | Setzt den Ausgang `Q` zurück |

### **Ereignis-Ausgänge**
| Ereignis | Typ | Beschreibung |
|----------|-----|--------------|
| INITO    | EInit | Initialisierungsbestätigung; mit `QO` verknüpft |

### **Daten-Eingänge**
| Variable | Typ   | Beschreibung |
|----------|-------|--------------|
| QI       | BOOL | Eingangsqualifier – steuert, ob Aktionen ausgeführt werden |
| Q_INIT   | BOOL | Gewünschter Wert des Ausgangs `Q` nach einer Initialisierung |

### **Daten-Ausgänge**
| Variable | Typ   | Beschreibung |
|----------|-------|--------------|
| QO       | BOOL | Ausgangsqualifier – spiegelt den Wert von `QI` zum Zeitpunkt des auslösenden Ereignisses |

### **Adapter**
| Adapter | Typ | Beschreibung |
|---------|-----|--------------|
| Q       | adapter::types::unidirectional::AX | Wert des Flipflops – wird über die Schnittstelle gesetzt/ zurückgesetzt |

## Funktionsweise
Der Baustein besitzt vier Hauptzustände: `START`, `Init`, `DeInit`, `SET` und `RESET`.

- **`START`** – Wartezustand nach dem Systemstart.
- **`Init`** – Wird aktiviert, wenn auf `INIT` eintrifft **und** `QI = TRUE`. In diesem Zustand wird der Algorithmus `initialize` ausgeführt, der `QO := QI` setzt. Anschließend verzweigt der Zustand je nach `Q_INIT`:
  - Ist `Q_INIT = TRUE`, wird in den `SET`‑Zustand gewechselt (Flipflop wird gesetzt).
  - Ist `Q_INIT = FALSE`, wird in den `RESET`‑Zustand gewechselt (Flipflop wird zurückgesetzt).
- **`DeInit`** – Wird aktiviert, wenn auf `INIT` eintrifft **und** `QI = FALSE` (aus den Zuständen `SET` oder `RESET`). Der Algorithmus `deInitialize` setzt `QO := FALSE`. Danach springt der Zustand zurück zu `START`.
- **`SET`** – Wird durch das Ereignis `S` erreicht (aus `RESET` oder nach Initialisierung mit `Q_INIT=TRUE`). Der Algorithmus `SET` setzt `QO := QI` und schreibt **nur wenn `QI = TRUE`** den Wert `TRUE` auf den Adapterausgang `Q.D1`. Ein erneutes `S` bleibt wirkungslos, solange der Zustand `SET` aktiv ist.
- **`RESET`** – Wird durch das Ereignis `R` erreicht (aus `SET` oder nach Initialisierung mit `Q_INIT=FALSE`). Der Algorithmus `RESET` setzt `QO := QI` und schreibt **nur wenn `QI = TRUE`** den Wert `FALSE` auf `Q.D1`. Ein erneutes `R` bleibt wirkungslos.

Die Transitionen zwischen `SET` und `RESET` werden nur durch die Ereignisse `S` bzw. `R` ausgelöst. Die INIT‑Transitionen können aus beiden stabilen Zuständen in `DeInit` führen, wenn `QI = FALSE` ist.

## Technische Besonderheiten
- **Qualifier‑abhängige Aktionen**: Die eigentliche Änderung des Flipflop‑Ausgangs (`Q.D1`) erfolgt nur, wenn `QI = TRUE`. Andernfalls werden nur die Output‑Qualifier (`QO`) aktualisiert, der Adapter bleibt unverändert.
- **Symmetrisches Start‑up**: Der Baustein kann sowohl mit einem „gesetzten“ als auch mit einem „zurückgesetzten“ Zustand initialisiert werden – abhängig vom Wert `Q_INIT`.
- **Deinitialisierung**: Wenn während der Initialisierung `QI = FALSE` ist, wird der Baustein in den `DeInit`‑Zustand versetzt, der den Ausgangsqualifier löscht und dann in den Startzustand zurückkehrt.
- **Guard‑Bedingungen**: Die Zustandsübergänge nutzen Bedingungen wie `INIT[TRUE = QI]` oder `[FALSE = Q_INIT]`, um die Logik präzise zu steuern.

## Zustandsübersicht
- **START** → Ruhezustand nach Start.
- **Init** → Initialisierungslauf (nur bei `QI=TRUE`).
- **DeInit** → Deinitialisierungslauf (nur bei `QI=FALSE`).
- **SET** → Stabiler Zustand, in dem `Q.D1 = TRUE` (sofern zuvor gesetzt).
- **RESET** → Stabiler Zustand, in dem `Q.D1 = FALSE` (sofern zuvor zurückgesetzt).

Übergänge:
- `START` → `Init` : wenn `INIT` & `QI=TRUE`
- `Init` → `SET` : wenn `Q_INIT=TRUE`
- `Init` → `RESET` : wenn `Q_INIT=FALSE`
- `SET` → `RESET` : wenn `R`
- `RESET` → `SET` : wenn `S`
- `SET` → `DeInit` : wenn `INIT` & `QI=FALSE`
- `RESET` → `DeInit` : wenn `INIT` & `QI=FALSE`
- `DeInit` → `START` : automatisch nach Abschluss des DeInit‑Algorithmus

## Anwendungsszenarien
- **Steuerung von Aktoren mit definiertem Startverhalten**: Ein Motor oder Ventil soll nach dem Einschalten einen bestimmten Zustand einnehmen (z. B. geschlossen = `Q=FALSE`), abhängig von einer Initialisierungsvorgabe.
- **Qualifizierte Zustandsänderungen**: In Systemen, in denen ein Freigabesignal (`QI`) erst die eigentliche Wertänderung erlaubt, während der Qualifier‑Ausgang (`QO`) die Gültigkeit signalisiert.
- **Reset‑fähige Initialisierungsroutine**: Eine Komponente kann durch einen INIT‑Aufruf entweder gesetzt oder zurückgesetzt werden, kann aber später durch erneuten INIT‑Aufruf mit `QI=FALSE` in einen definierten Ruhezustand versetzt werden.

## Vergleich mit ähnlichen Bausteinen
- **Standard‑SR‑Flipflop (z. B. `SR` oder `AX_SR`)**: Einfaches Set/Reset ohne Initialisierung und ohne Qualifier. `AX_SR_SYM_INIT` bietet zusätzlich einen qualifizierten Initialisierungs‑ und Deinitialisierungsablauf.
- **Bausteine mit INIT‑Schnittstelle (z. B. `E_SR` mit `INIT`)**: Diese haben oft keine ausgeprägte Deinitialisierung oder keinen Qualifier. Der hier vorgestellte FB unterscheidet sich durch das symmetrische Verhalten – sowohl Setzen als auch Zurücksetzen kann im INIT‑Schritt vorgegeben werden.
- **Bausteine mit Adapter (`unidirectional::AX`)**: Werden verwendet, um den Zustand über eine standardisierte Adapterschnittstelle nach außen zu tragen. Der `AX_SR_SYM_INIT` kapselt diese Logik in einem FB.

## Fazit
Der `AX_SR_SYM_INIT` ist ein vielseitiger Funktionsblock für Anwendungen, die ein qualifiziertes Start‑ und Initialisierungsverhalten erfordern. Durch die Kombination von Ereignissteuerung, Qualifier‑Logik und Adapter‑Schnittstelle eignet er sich besonders für modulare Automatisierungslösungen nach IEC 61499, bei denen ein definierter Systemstart und eine saubere Deinitialisierung gefordert sind.