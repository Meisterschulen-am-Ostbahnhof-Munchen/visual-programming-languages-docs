# E_SR_SYM_INIT


![E_SR_SYM_INIT](./E_SR_SYM_INIT.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `E_SR_SYM_INIT` realisiert ein ereignisgesteuertes, bistabiles Flip-Flop mit symmetrischem Start-up-Verhalten und einer INIT-Schnittstelle. Er erweitert ein einfaches SR-Flip-Flop um die Möglichkeit, beim INIT‑Event den Ausgang `Q` auf einen vorgegebenen Wert (`Q_INIT`) zu setzen und eine Deinitialisierung durchzuführen. Die Eingangsqualifikation `QI` steuert, ob die Operationen (S, R, INIT) tatsächlich auf `Q` wirken.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Event | Typ | Kommentar |
|-------|-----|-----------|
| `INIT` | EInit | Initialisierungsanforderung; wird mit `QI` und `Q_INIT` ausgewertet |
| `S` | Event | Setze den Ausgang `Q` auf `TRUE` (nur wirksam wenn `QI = TRUE`) |
| `R` | Event | Setze den Ausgang `Q` auf `FALSE` (nur wirksam wenn `QI = TRUE`) |

### **Ereignis-Ausgänge**
| Event | Typ | Kommentar |
|-------|-----|-----------|
| `INITO` | EInit | Bestätigung der Initialisierung/Deinitialisierung |
| `EO` | Event | Wird ausgelöst, wenn sich `Q` geändert hat (durch S oder R) |

### **Daten-Eingänge**
| Variable | Typ | Kommentar |
|----------|-----|-----------|
| `QI` | BOOL | Eingangsqualifikator; steuert, ob die Operationen (S, R, INIT) auf `Q` wirken |
| `Q_INIT` | BOOL | Wert, den `Q` bei einer erfolgreichen Initialisierung (`INIT` mit `QI = TRUE`) annehmen soll |

### **Daten-Ausgänge**
| Variable | Typ | Kommentar |
|----------|-----|-----------|
| `QO` | BOOL | Ausgangsqualifikator; gibt den Wert von `QI` während der letzten Aktion zurück (bei Deinitialisierung `FALSE`) |
| `Q` | BOOL | Wert des Flip-Flops (bistabiler Ausgang) |

### **Adapter**
Keine.

## Funktionsweise
Der FB besitzt fünf Zustände: `START`, `Init`, `DeInit`, `SET` und `RESET`.

- **START**: Ruhezustand nach der Initialisierung.
- **Init**: Wird durch `INIT` mit `QI = TRUE` erreicht. Der Algorithmus `initialize` setzt `QO := QI`. Anschließend wird abhängig von `Q_INIT` in den Zustand `SET` (wenn `Q_INIT = TRUE`) oder `RESET` (wenn `Q_INIT = FALSE`) gewechselt. Dabei wird `Q` auf den Wert von `Q_INIT` gesetzt (über die Algorithmen `SET` bzw. `RESET`) und `EO` ausgelöst.
- **DeInit**: Wird durch `INIT` mit `QI = FALSE` aus den Zuständen `SET` oder `RESET` erreicht. Der Algorithmus `deInitialize` setzt `QO := FALSE`. Anschließend geht der FB automatisch zurück in den Zustand `START`.
- **SET** und **RESET**: Normale Arbeitszustände des Flip-Flops. Bei einem `S`-Ereignis wird der Algorithmus `SET` ausgeführt: `QO := QI` und falls `QI = TRUE` wird `Q := TRUE` gesetzt; `EO` wird ausgelöst. Bei einem `R`-Ereignis analog `Q := FALSE`. Ein `INIT` mit `QI = FALSE` führt zurück nach `DeInit`; `INIT` mit `QI = TRUE` wäre nur vom Zustand `START` möglich.

Die Qualifikation `QI` wirkt wie ein Freigabesignal: Nur wenn `QI = TRUE` beeinflussen `S`, `R` und die Initialisierung den Ausgang `Q`. Der Ausgang `QO` spiegelt den zuletzt gültigen Wert von `QI` wider (außer nach `DeInit`, dann ist `QO = FALSE`).

## Technische Besonderheiten
- **Symmetrisches Start-up**: Der Wert von `Q` nach einer Initialisierung wird ausschließlich durch `Q_INIT` bestimmt – unabhängig vom vorherigen Zustand. Dies ermöglicht ein deterministisches Verhalten nach dem Start.
- **Qualifizierte Operationen**: Alle Aktionen (S, R, INIT) werden nur ausgeführt, wenn `QI = TRUE`. Damit kann der FB z. B. über eine übergeordnete Steuerung ein- und ausgeschaltet werden.
- **Deinitialisierung**: Durch ein `INIT` mit `QI = FALSE` gelangt der FB in einen definierten Deinitialisierungszustand (`DeInit`), der keine weiteren Aktionen mehr zulässt, bis ein erneutes `INIT` mit `QI = TRUE` erfolgt.
- **Keine Speicherung von QO**: `QO` wird bei jeder Transition neu gesetzt, es erfolgt keine eigene Speicherung.

## Zustandsübersicht
```
START
  │
  │ INIT[QI = TRUE]
  ▼
Init ─────────────────────────────────┐
  │                                    │
  │ [Q_INIT = TRUE]  [Q_INIT = FALSE] │
  ▼                    ▼               │
 SET                 RESET             │
  │                    │               │
  │ R                  │ S             │
  └───────→ RESET      │               │
         ←───────────┘                │
  │                    │               │
  │ INIT[QI = FALSE]  │ INIT[QI=FALSE]│
  └────────────────────┴───────────────┘
                      ▼
                    DeInit
                      │
                      │ 1 (immer)
                      ▼
                    START
```

## Anwendungsszenarien
- **Steuerungen, die nach dem Einschalten einen definierten Ausgangszustand benötigen** (z. B. Maschinen: Ventil geschlossen oder geöffnet).
- **Systeme mit sicherheitskritischer Initialisierung**, bei denen der Ausgang erst nach Freigabe durch einen Qualifikator (`QI`) gesetzt werden darf.
- **Bausteinketten**, bei denen eine Deinitialisierung (z. B. bei einem Reset des Gesamtsystems) den FB in einen Grundzustand zurückversetzen soll, ohne dass die eigentlichen S/R-Signale noch wirken.

## Vergleich mit ähnlichen Bausteinen
- **E_SR** (Standard SR-Flipflop): Hat kein INIT-Verhalten, startet undefiniert oder mit letztem Wert. `E_SR_SYM_INIT` erweitert dies um eine definierte Initialisierung und Deinitialisierung.
- **E_RS**: Vertauscht Set/Reset-Priorität, aber ohne INIT-Mechanismus.
- **E_SR_SYM**: Symmetrisches SR-Flipflop ohne INIT-Schnittstelle; `E_SR_SYM_INIT` fügt die INIT-Startlogik hinzu.

Der Vorteil des `E_SR_SYM_INIT` liegt in der Kombination von qualifizierter Initialisierung mit einem expliziten Deinitialisierungspfad.

## Fazit
Der Funktionsblock `E_SR_SYM_INIT` bietet ein robustes, qualifiziertes Flip-Flop mit definiertem Startzustand. Die symmetrische Startlogik und die Deinitialisierungsmöglichkeit machen ihn ideal für Anwendungen, die ein reproduzierbares Verhalten nach Systemstart oder -reset erfordern. Die Trennung von Ereignissen und Qualifikation erlaubt eine flexible Einbindung in übergeordnete Steuerungsstrukturen.