# AX_T_FF_SR_SYM_INIT


![AX_T_FF_SR_SYM_INIT](./AX_T_FF_SR_SYM_INIT.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AX_T_FF_SR_SYM_INIT** realisiert ein ereignisgesteuertes bistabiles Kippglied (Flip-Flop) mit **Set**‑, **Reset**‑ und **Toggle**‑Funktionalität. Er zeichnet sich durch ein **symmetrisches Start‑up‑Verhalten** aus, bei dem der Ausgangszustand nach dem INIT‑Ereignis über den Parameter `Q_INIT` definiert werden kann. Der Baustein ist gemäß IEC 61499‑1 Annex A ausgelegt und eignet sich für Anwendungen, die einen rückgesetzten, gesetzten oder umschaltbaren binären Zustand mit einer initialisierbaren Voreinstellung benötigen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Event | Typ     | Kommentar                                     |
|-------|---------|-----------------------------------------------|
| INIT  | EInit   | Initialisierungsanforderung                   |
| S     | Event   | Setzen des Ausgangs Q (abhängig von QI)       |
| R     | Event   | Rücksetzen des Ausgangs Q (abhängig von QI)   |
| CLK   | Event   | Takt zum Umschalten (Toggle) von Q            |

### **Ereignis-Ausgänge**

| Event  | Typ     | Kommentar                               |
|--------|---------|-----------------------------------------|
| INITO  | EInit   | Bestätigung der Initialisierung         |

### **Daten-Eingänge**

| Variable  | Typ    | Kommentar                                      |
|-----------|--------|------------------------------------------------|
| QI        | BOOL   | Ereignisqualifizierer (Freigabe von Aktionen)  |
| Q_INIT    | BOOL   | Wert von Q beim INIT‑Ereignis                  |

### **Daten-Ausgänge**

| Variable | Typ    | Kommentar                                       |
|----------|--------|-------------------------------------------------|
| QO       | BOOL   | Ausgangs‑Ereignisqualifizierer                  |

### **Adapter**

| Adapter | Typ                                 | Kommentar                   |
|---------|-------------------------------------|-----------------------------|
| Q       | adapter::types::unidirectional::AX  | Wert des Flip‑Flops (D1)    |

## Funktionsweise

Der Baustein besitzt eine endliche Zustandsmaschine mit fünf Zuständen: **START**, **Init**, **DeInit**, **SET** und **RESET**.

- **START** ist der initiale Zustand nach dem Einschalten.
- Ein **INIT**‑Ereignis leitet die Initialisierung ein:
  - Wenn `QI = TRUE`, wird in den **Init**‑Zustand gewechselt. Die Algorithmen `initialize` setzen `QO := QI`.
  - Anschließend wird anhand von `Q_INIT` entschieden, ob in den **SET**‑Zustand (`Q_INIT = TRUE`) oder in den **RESET**‑Zustand (`Q_INIT = FALSE`) übergegangen wird.
- Während des Betriebs können **S**, **R** oder **CLK** verarbeitet werden:
  - Bei **S** (Set) wird im Algorithmus `SET` der Adapter‑Ausgang `Q.D1` auf `TRUE` gesetzt, sofern `QI = TRUE` ist. `QO` erhält den Wert von `QI`.
  - Bei **R** (Reset) wird `Q.D1` auf `FALSE` gesetzt, ebenfalls nur bei aktivem `QI`.
  - Bei **CLK** (Toggle) wird der Zustand umgeschaltet: Ist der FB im Zustand **SET**, führt ein CLK‑Ereignis in den **RESET**‑Zustand; ist er in **RESET**, führt es in **SET**. Die Toggle‑Funktion arbeitet unabhängig von `QI`? *Anmerkung:* Die Transitionen `SET—CLK→RESET` und `RESET—CLK→SET` sind ohne weitere Bedingung definiert, jedoch wird in den Algorithmen `Q.D1` nur bei `QI = TRUE` geändert. Falls `QI = FALSE`, bleibt der Adapter‑Wert unverändert, aber der Zustandsübergang findet trotzdem statt. Der interne Zustand (SET/RESET) wird also immer gewechselt, die tatsächliche Ausgabe auf `Q.D1` erfolgt aber nur, wenn `QI` wahr ist.
- Ein erneutes **INIT**‑Ereignis mit `QI = FALSE` führt in den **DeInit**‑Zustand, in dem `QO := FALSE` gesetzt wird. Danach kehrt der FB in den **START**‑Zustand zurück.

Der Ausgang `QO` wird bei jedem ausgeführten Algorithmus auf den aktuellen Wert von `QI` gesetzt. Er dient als Ereignisqualifizierer für den INITO‑Ausgang.

## Technische Besonderheiten

- **Symmetrisches Start‑up‑Verhalten**: Der Anfangswert des Ausgangs wird über `Q_INIT` festgelegt, sodass sowohl gesetzte als auch rückgesetzte Startzustände möglich sind.
- **Ereignisqualifizierer QI**: Die eigentliche Änderung des Adapters `Q.D1` (also des Flip‑Flop‑Ausgangs) wird nur dann ausgeführt, wenn `QI` = `TRUE` ist. Bei `QI = FALSE` werden die Ereignisse S, R und CLK zwar verarbeitet (Zustandswechsel), aber der Adapter‑Wert bleibt unverändert.
- **Toggle‑Funktionalität**: Durch das CLK‑Ereignis kann der Ausgang zwischen 0 und 1 umgeschaltet werden, was in vielen Anwendungen eine einfache Rechteckgenerierung oder Zustandswechsel ermöglicht.
- **INIT‑Behandlung**: Das INIT‑Ereignis kann sowohl für die Erstinitialisierung (`QI = TRUE`) als auch für die Deinitialisierung (`QI = FALSE`) genutzt werden.

## Zustandsübersicht

| Zustand | Aktion | Ausgang/Ereignis | Beschreibung |
|---|---|---|---|
| **START** | – | – | Wartet auf erstes INIT‑Ereignis. |
| **Init** | `initialize` | INITO | Setzt `QO := QI`; danach Wechsel zu SET oder RESET je nach `Q_INIT`. |
| **DeInit** | `deInitialize` | INITO | Setzt `QO := FALSE`; danach Rücksprung zu START. |
| **SET** | `SET` | Q.E1 | Setzt `Q.D1 := TRUE` (falls QI = TRUE) und `QO := QI`. |
| **RESET** | `RESET` | Q.E1 | Setzt `Q.D1 := FALSE` (falls QI = TRUE) und `QO := QI`. |

**Transitionen** (auszugsweise):
- START → Init: `INIT[QI = TRUE]`
- Init → SET: `Q_INIT = TRUE`
- Init → RESET: `Q_INIT = FALSE`
- SET → RESET: `R` oder `CLK`
- RESET → SET: `S` oder `CLK`
- SET → DeInit: `INIT[QI = FALSE]`
- RESET → DeInit: `INIT[QI = FALSE]`
- DeInit → START: (immer, Bedingung = 1)

## Anwendungsszenarien

- **Maschinensteuerung**: Definierter Startzustand nach Einschalten (z.B. Ventil geschlossen = `Q_INIT = FALSE`).
- **Zustandswechsel mit Toggle**: Umschalten einer Beleuchtung oder eines Antriebs bei jedem CLK‑Impuls.
- **Sichere Initialisierung**: Über `QI` kann die Aktion an Bedingungen geknüpft werden (z.B. Freigabe durch übergeordnete Steuerung).
- **Fehlerrückstellung**: Ein RESET‑Ereignis setzt den Ausgang zurück, während ein Setzen durch S möglich ist.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Besonderheit |
|---|---|
| `E_SR` (Standard IEC 61499) | Reines Set/Reset‑Flip‑Flop ohne Toggle und ohne INIT‑Symmetrie. |
| `E_RS` | Wie E_SR, aber Reset hat Vorrang. |
| `E_Toggle` | Nur Toggle‑Funktion, kein Set/Reset, keine Initialisierung. |
| `AX_T_FF_SR_SYM_INIT` | Kombiniert Set, Reset, **Toggle**, **symmetrische INIT‑Voreinstellung** und Ereignisqualifizierer `QI`. |

Der hier beschriebene FB bietet somit eine höhere Flexibilität für Anwendungen, die mehrere Betriebsmodi und einen definierten Anfangszustand erfordern.

## Fazit

Der **AX_T_FF_SR_SYM_INIT** ist ein vielseitiger und robuster Funktionsblock für die binäre Zustandssteuerung in IEC 61499‑Systemen. Seine Kombination aus Set, Reset und Toggle, gepaart mit einem frei konfigurierbaren Startzustand über `Q_INIT` und dem Qualifizierer `QI`, ermöglicht eine kompakte und sichere Abbildung vieler Automatisierungsanforderungen. Durch das durchdachte INIT‑Handling eignet er sich besonders für Anwendungen, die ein definiertes und reproduzierbares Start‑up‑Verhalten verlangen.