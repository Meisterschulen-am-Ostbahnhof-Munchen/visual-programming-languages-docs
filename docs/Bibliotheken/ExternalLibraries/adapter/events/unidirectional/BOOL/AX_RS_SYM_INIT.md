# AX_RS_SYM_INIT


![AX_RS_SYM_INIT](./AX_RS_SYM_INIT.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AX_RS_SYM_INIT** realisiert einen ereignisgesteuerten, bistabilen Flip-Flop (RS-Flip-Flop) mit symmetrischem Start-up-Verhalten und explizitem Initialisierungsmechanismus. Er erweitert einen einfachen RS-Flip-Flop um die Fähigkeit, beim Start (INIT) einen vorgegebenen Zustand einzunehmen und über den Ereignis-Eingang INIT sowohl die Initialisierung als auch die Deinitialisierung zu steuern. Der tatsächliche Zustand des Flip-Flops wird über einen Adapter bereitgestellt, während die Datenausgänge QO und der Adapter-Ausgang Q.D1 synchronisiert werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name  | Typ   | Kommentar                                   |
|-------|-------|---------------------------------------------|
| INIT  | EInit | Initialisierungsanforderung (mit QI, Q_INIT) |
| R     | Event | Reset-Signal (setzt Q zurück)               |
| S     | Event | Set-Signal (setzt Q)                        |

### **Ereignis-Ausgänge**

| Name  | Typ   | Kommentar                                   |
|-------|-------|---------------------------------------------|
| INITO | EInit | Initialisierungsbestätigung (mit QO)        |

### **Daten-Eingänge**

| Name   | Typ  | Kommentar                                     |
|--------|------|-----------------------------------------------|
| QI     | BOOL | Ereignis-Qualifier – steuert die Ausführung   |
| Q_INIT | BOOL | Gewünschter Wert von Q bei der Initialisierung |

### **Daten-Ausgänge**

| Name | Typ  | Kommentar                                |
|------|------|------------------------------------------|
| QO   | BOOL | Ereignis-Qualifier – gibt QI an INITO oder bei S/R weiter |

### **Adapter**

| Name | Typ                                | Kommentar                                |
|------|------------------------------------|------------------------------------------|
| Q    | adapter::types::unidirectional::AX | Adapter für den Wert des Flip-Flops (D1) |

## Funktionsweise

Der FB durchläuft verschiedene Zustände, gesteuert durch die Ereignisse INIT, S und R.

- Im **START**-Zustand wartet er auf ein INIT-Ereignis.
  - Wird INIT mit `QI = TRUE` empfangen, wechselt er in den **Init**-Zustand. Die Aktion `initialize` setzt `QO := QI`.
  - Abhängig vom Wert von `Q_INIT`:
    - Ist `Q_INIT = TRUE` → Wechsel in **SET**-Zustand.
    - Ist `Q_INIT = FALSE` → Wechsel in **RESET**-Zustand.
  - Nach der Aktion wird `INITO` ausgelöst.

- Wird INIT mit `QI = FALSE` empfangen (egal ob aus **SET** oder **RESET**), wechselt er in den **DeInit**-Zustand. Die Aktion `deInitialize` setzt `QO := FALSE`. Anschließend wird `INITO` ausgelöst und der FB geht zurück zu **START**.

- In den Zuständen **SET** und **RESET** verhält sich der FB wie ein herkömmlicher RS-Flip-Flop:
  - Bei **S**-Ereignis wird die Aktion `SET` ausgeführt: `QO := QI`; wenn `QI = TRUE`, wird zusätzlich `Q.D1 := TRUE` gesetzt (Adapter-Ausgang).
  - Bei **R**-Ereignis wird die Aktion `RESET` ausgeführt: `QO := QI`; wenn `QI = TRUE`, wird `Q.D1 := FALSE` gesetzt.
  - Das Ereignis an `Q.E1` wird nach jeder Aktion gesendet.

Die `QI`-Variable fungiert als Qualifier: Nur wenn `QI = TRUE`, werden die Operationen auf den Adapter (Setzen/Rücksetzen von `Q.D1`) tatsächlich durchgeführt. Andernfalls wird nur `QO` weitergereicht.

## Technische Besonderheiten

- **Symmetrisches Start-up-Verhalten**: Die Initialisierung berücksichtigt den Wert von `Q_INIT`, sodass der Flip-Flop gezielt in den SET- oder RESET-Zustand starten kann. Das Verhalten ist symmetrisch, da beide Möglichkeiten explizit abgebildet sind.
- **Adapter-Kopplung**: Der Zustand des Flip-Flops wird nicht direkt als Datenausgang geführt, sondern über einen **unidirektionalen Adapter** (`Q`) mit dem Ausgang `D1` bereitgestellt. Dies ermöglicht eine lose Kopplung mit weiteren Bausteinen.
- **Deinitialisierung**: Durch INIT mit `QI = FALSE` wird der FB zurückgesetzt und kehrt in den START-Zustand zurück. Dabei werden alle internen Variablen auf definierte Werte gesetzt (`QO = FALSE`).
- **Ereignis-Qualifier**: `QI` und `QO` dienen der Steuerung der Ereignisweitergabe und bieten eine zusätzliche Bedingungsebene.

## Zustandsübersicht

| Zustand | Beschreibung                                      |
|---------|---------------------------------------------------|
| START   | Warten auf INIT-Ereignis                          |
| Init    | Initialisierung: Setzt QO und wählt Zielzustand   |
| DeInit  | Deinitialisierung: Setzt QO = FALSE               |
| SET     | Aktiver Set-Zustand (Q.D1 = TRUE)                 |
| RESET   | Aktiver Reset-Zustand (Q.D1 = FALSE)              |

**Wichtige Transitionen:**
- START → Init bei INIT mit QI = TRUE
- Init → SET bei Q_INIT = TRUE
- Init → RESET bei Q_INIT = FALSE
- SET → RESET bei R
- RESET → SET bei S
- SET/RESET → DeInit bei INIT mit QI = FALSE
- DeInit → START (automatisch nach Abschluss)

## Anwendungsszenarien

- **Anlaufsteuerung**: Ein Flip-Flop, der nach einem Start oder Reset einen definierten Anfangszustand einnehmen soll (z. B. Maschine startet im Zustand „Bereit“).
- **Sichere Initialisierung**: In sicherheitskritischen Systemen, bei denen der Startzustand explizit vorgegeben werden muss.
- **Modularer Aufbau**: Einsatz als grundlegendes Speicherelement in einer Adapter-basierten Architektur, bei der der Zustand über den Adapter an andere Bausteine weitergegeben wird.

## Vergleich mit ähnlichen Bausteinen

- **Standard RS (z. B. RS-Flipflop)**: Einfacher RS-Flip-Flop ohne INIT und ohne Adapter. `AX_RS_SYM_INIT` erweitert dies um Initialisierungslogik und Adapter-Schnittstelle.
- **Bistabile Kippglieder mit Reset**: Viele Bausteine bieten nur asynchrones Rücksetzen. Dieser FB integriert das Reset in das EVENT-gesteuerte Verhalten und erlaubt eine symmetrische Zielvorgabe.
- **SR-Latch mit INIT**: Ähnliche Bausteine existieren, jedoch meist ohne den Qualifier `QI` und die Deinitialisierungsmöglichkeit.

## Fazit

Der FB `AX_RS_SYM_INIT` kombiniert ein klassisches RS-Flipflop-Verhalten mit einer flexiblen Initialisierungslogik, die sowohl Setzen als auch Rücksetzen beim Start erlaubt. Die Verwendung eines Adapters für den Zustandswert und die Einbeziehung von Qualifiern (`QI`, `QO`) machen ihn zu einem robusten und vielseitigen Baustein für ereignisgesteuerte Automatisierungsanwendungen, die einen definierten und rücksetzbaren Anfangszustand benötigen.