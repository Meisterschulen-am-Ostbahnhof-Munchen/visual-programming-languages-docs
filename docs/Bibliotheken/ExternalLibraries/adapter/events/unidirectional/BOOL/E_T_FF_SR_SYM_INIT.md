# E_T_FF_SR_SYM_INIT


![E_T_FF_SR_SYM_INIT](./E_T_FF_SR_SYM_INIT.svg)

**Bild des Funktionsblocks:** (nicht verfügbar)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `E_T_FF_SR_SYM_INIT` realisiert ein ereignisgesteuertes, bistabiles Flipflop mit Set-, Reset- und Toggle‑Funktion. Es zeichnet sich durch ein symmetrisches Start‑up‑Verhalten aus: Beim Initialisierungsereignis (`INIT`) wird der Ausgang `Q` auf den am Eingang `Q_INIT` vorgegebenen Wert gesetzt, sofern der Qualifier `QI` aktiv ist. Der Baustein kombiniert die Eigenschaften eines SR‑Flipflops und eines Toggle‑Flipflops in einer Einheit.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Name  | Typ    | Kommentar                                |
|-------|--------|------------------------------------------|
| INIT  | EInit  | Initialisierungsanforderung              |
| S     | Event  | Setzt den Ausgang Q (gesetzt)            |
| R     | Event  | Setzt den Ausgang Q (zurückgesetzt)      |
| CLK   | Event  | Takt für das Umschalten (Toggle) von Q   |

### **Ereignis-Ausgänge**
| Name  | Typ    | Kommentar                                |
|-------|--------|------------------------------------------|
| INITO | EInit  | Bestätigung der Initialisierung          |
| EO    | Event  | Signalisiert eine Änderung von Q         |

### **Daten-Eingänge**
| Name    | Typ   | Kommentar                                    |
|---------|-------|----------------------------------------------|
| QI      | BOOL  | Ereignisqualifier (steuert die Ausführung)   |
| Q_INIT  | BOOL  | Wert, den Q bei INIT annehmen soll           |

### **Daten-Ausgänge**
| Name | Typ   | Kommentar                                |
|------|-------|------------------------------------------|
| QO   | BOOL  | Ausgangsqualifier (Spiegel von QI)       |
| Q    | BOOL  | Wert des Flipflops                       |

### **Adapter**
Keine.

## Funktionsweise
Der Baustein durchläuft einen endlichen Automaten mit fünf Zuständen: `START`, `Init`, `DeInit`, `SET` und `RESET`.

- **Initialisierung (`INIT`)**  
  Wenn am Ereigniseingang `INIT` ein Signal anliegt, wird abhängig vom Zustand des Qualifiers `QI` unterschieden:
  - Ist `QI = TRUE`, wechselt der Baustein in den Zustand `Init`. Dort wird der Ausgangsqualifier `QO` auf den Wert von `QI` gesetzt (also `TRUE`) und der Ausgang `INITO` wird ausgelöst. Anschließend geht der Automat – wiederum abhängig von `Q_INIT` – in den Zustand `SET` (falls `Q_INIT = TRUE`) oder in den Zustand `RESET` (falls `Q_INIT = FALSE`). Somit erhält `Q` den gewünschten Startwert.
  - Ist `QI = FALSE`, wechselt der Baustein in den Zustand `DeInit`. Dort wird `QO` auf `FALSE` gesetzt und `INITO` ausgelöst. Danach kehrt der Automat in den Startzustand zurück.

- **Setzen (`S`)**  
  Bei einem Ereignis an `S` wird der Algorithmus `SET` ausgeführt:  
  `QO` erhält den Wert von `QI`. Ist `QI = TRUE`, wird `Q` auf `TRUE` gesetzt. Der Ausgang `EO` wird ausgelöst, um eine Änderung von `Q` zu signalisieren.

- **Rücksetzen (`R`)**  
  Bei einem Ereignis an `R` wird der Algorithmus `RESET` ausgeführt:  
  `QO` erhält den Wert von `QI`. Ist `QI = TRUE`, wird `Q` auf `FALSE` gesetzt. Auch hier wird `EO` ausgelöst.

- **Toggle (`CLK`)**  
  Ein Ereignis an `CLK` bewirkt stets einen Wechsel des Zustands:  
  Befindet sich der Automat im Zustand `SET`, wechselt er zu `RESET` und umgekehrt. Dabei wird der jeweilige Algorithmus (`SET` bzw. `RESET`) mit der aktuellen Bewertung von `QI` ausgeführt. Der Ausgang `Q` wird also bei jedem Takt umgeschaltet, sofern `QI = TRUE` ist.

## Technische Besonderheiten
- **Symmetrisches Start‑up‑Verhalten**: Der initiale Wert von `Q` wird durch den parametrierbaren Eingang `Q_INIT` festgelegt und nicht etwa auf einen festen Default gesetzt. Dadurch kann das System reproduzierbar in einen definierten Zustand starten.
- **Ereignisqualifier `QI`**: Alle Aktionen (`SET`, `RESET`) werden nur dann tatsächlich ausgeführt, wenn `QI = TRUE` ist. Bei `QI = FALSE` wird der Ausgangsqualifier `QO` lediglich auf `FALSE` gesetzt, der Wert von `Q` bleibt unverändert. Dies ermöglicht eine bedingte Steuerung durch vorgeschaltete Bausteine.
- **Deinitialisierung**: Wird während der Laufzeit ein `INIT`-Ereignis mit `QI = FALSE` empfangen, so wird der Baustein deinitialisiert und geht in den Ruhezustand (`START`). In diesem Zustand reagiert er auf keine weiteren Ereignisse, bis er erneut initialisiert wird.

## Zustandsübersicht
| Zustand | Beschreibung                                 | Aktion bei Eintritt                         |
|---------|----------------------------------------------|---------------------------------------------|
| START   | Warten auf Initialisierung                   | –                                           |
| Init    | Initialisierung von QO                       | `QO := QI`; Auslösen von `INITO`           |
| DeInit  | Deinitialisierung (bei QI=false)            | `QO := FALSE`; Auslösen von `INITO`        |
| SET     | Q ist gesetzt (`TRUE`)                       | `Q := TRUE` (nur wenn QI=true); Auslösen `EO` |
| RESET   | Q ist zurückgesetzt (`FALSE`)                | `Q := FALSE` (nur wenn QI=true); Auslösen `EO` |

Übergänge:
- `START` → `Init` : bei `INIT` und `QI = TRUE`
- `START` → `DeInit` : bei `INIT` und `QI = FALSE`
- `Init` → `SET` : wenn `Q_INIT = TRUE`
- `Init` → `RESET` : wenn `Q_INIT = FALSE`
- `SET` ⇄ `RESET` : durch `S`, `R` oder `CLK` (jeweils unter Berücksichtigung von QI)
- `SET` → `DeInit` : bei erneuter `INIT` mit `QI = FALSE`
- `RESET` → `DeInit` : bei erneuter `INIT` mit `QI = FALSE`
- `DeInit` → `START` : immer (Transition mit Bedingung `1`)

## Anwendungsszenarien
- **Steuerung mit definiertem Startzustand**: In Sicherheitssteuerungen oder Anlagen, die nach einem Neustart einen bestimmten Ausgangszustand benötigen, kann `Q_INIT` entsprechend gesetzt werden.
- **Toggle-Funktion für Befehlsschalter**: Ein einziger Taster (verbunden mit `CLK`) schaltet einen Ausgang bei jedem Drücken um – z. B. für Lichtsteuerungen.
- **Bedingte Set-/Reset-Logik**: Der Qualifier `QI` erlaubt es, die Aktionen von übergeordneten Bedingungen abhängig zu machen, ohne dass der Zustand des Flipflops verloren geht.

## Vergleich mit ähnlichen Bausteinen
- **Standard SR-Flipflop (`E_SR`)**: Bietet nur Setzen und Rücksetzen, keine Toggle-Funktion und kein einstellbarer Startwert.
- **Toggle-Flipflop (`E_TOGGLE`)**: Nur Umschalten bei jedem Takt, kein separates Setzen/Rücksetzen, kein definierter Startwert.
- **SR-Flipflop mit Initialisierung (`E_SR_INIT`)**: Ähnlich, aber ohne Toggle-Funktion.

Der vorliegende Baustein vereint alle drei Funktionen (Set, Reset, Toggle) mit einem flexiblen Initialisierungsverhalten – eine umfassende Lösung für viele ereignisgesteuerte Steuerungsaufgaben.

## Fazit
`E_T_FF_SR_SYM_INIT` ist ein vielseitiger Funktionsblock für die IEC‑61499‑basierte ereignisgesteuerte Automatisierung. Durch die Kombination von Setzen, Rücksetzen und Toggeln sowie der parametrierbaren Initialisierung deckt er ein breites Spektrum an Anforderungen ab. Die Verwendung des Qualifiers `QI` erhöht die Flexibilität und ermöglicht eine sichere Einbindung in komplexe Ablaufsteuerungen.