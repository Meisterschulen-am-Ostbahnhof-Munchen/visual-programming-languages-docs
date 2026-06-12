# E_SR_SYM


![E_SR_SYM](./E_SR_SYM.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock E_SR_SYM ist ein ereignisgesteuertes bistabiles Element mit symmetrischem Startverhalten. Er realisiert ein Flip-Flop, das auf Set- und Reset‑Ereignisse reagiert und dessen Anfangszustand nicht vorab festgelegt ist, sondern durch das erste eintreffende Ereignis bestimmt wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **S** (Event): Setzt den Ausgang \( Q \) auf `TRUE`.
- **R** (Event): Setzt den Ausgang \( Q \) auf `FALSE`.

### **Ereignis-Ausgänge**

- **EO** (Event): Wird ausgelöst, sobald sich der Wert von \( Q \) ändert (nach einem S- oder R-Ereignis). Der Ausgangsdatenspeicher \( Q \) ist diesem Ereignis zugeordnet (`With Var="Q"`).

### **Daten-Eingänge**

Keine.

### **Daten-Ausgänge**

- **Q** (BOOL): Aktueller logischer Zustand des Flip-Flops (`TRUE` oder `FALSE`).

### **Adapter**

Keine.

## Funktionsweise

Der Baustein arbeitet zustandsbasiert und verfügt über drei Zustände:

- **START** – Initialzustand nach dem Einschalten oder Zurücksetzen der Steuerung.
- **SET** – Zustand nach einem Set‑Ereignis.
- **RESET** – Zustand nach einem Reset‑Ereignis.

Trifft im Zustand START ein Ereignis an **S** ein, wechselt der Baustein in den Zustand SET, setzt \( Q := \text{TRUE} \) und sendet das Ereignis **EO**. Trifft stattdessen ein Ereignis an **R** ein, wechselt er in RESET, setzt \( Q := \text{FALSE} \) und sendet ebenfalls **EO**.

Befindet sich der Baustein bereits in einem der aktiven Zustände (SET oder RESET), so kann er durch das jeweils andere Ereignis umgeschaltet werden. Dadurch ergibt sich ein symmetrisches Verhalten: Weder S noch R haben eine Priorität – der letzte eingegangene Impuls bestimmt den Ausgang.

## Technische Besonderheiten

- **Symmetrisches Startverhalten:** Im Gegensatz zu klassischen SR‑Flip‑Flops, die nach dem Start einen festen Anfangswert (meist `FALSE`) liefern, wartet E_SR_SYM im Zustand START auf das erste Ereignis. Der Ausgang \( Q \) bleibt bis dahin in einem undefinierten bzw. nicht gesetzten Zustand. Dies ermöglicht eine flexible Initialisierung durch die Umgebung.
- **Zustandsautomaten mit drei Zuständen:** Die ECC verwendet die Zustände START, SET und RESET sowie zwei Algorithmen (SET, RESET) in Structured Text.
- **Kompakte Schnittstelle:** Nur zwei Ereigniseingänge, ein Ereignisausgang und ein Datenausgang – dadurch einfach in größere Ablaufsteuerungen integrierbar.

## Zustandsübersicht

| Zustand | Bedeutung | Aktion beim Eintritt | Auslöser für Transitionen |
|---------|-----------|----------------------|---------------------------|
| **START** | Initialzustand | Keine (Warten auf erstes Ereignis) | S → SET, R → RESET |
| **SET** | Ausgang \( Q \) ist `TRUE` | Führe Algorithmus SET aus (\( Q := \text{TRUE} \)), sende EO | R → RESET |
| **RESET** | Ausgang \( Q \) ist `FALSE` | Führe Algorithmus RESET aus (\( Q := \text{FALSE} \)), sende EO | S → SET |

Transitionen:
- START → SET bei **S**
- START → RESET bei **R**
- SET → RESET bei **R**
- RESET → SET bei **S**

## Anwendungsszenarien

- **Ereignisgesteuerte Freigabesignale:** Ein binäres Freigabesignal wird durch einen Set‑Impuls gesetzt und durch einen Reset‑Impuls zurückgesetzt.
- **Initial unbestimmte Systeme:** Anlaufverhalten, bei dem der erste gültige Befehl (Setzen oder Zurücksetzen) den weiteren Ablauf bestimmt.
- **Einfache Zweipunktregelung:** Schalten von Aktoren (z. B. Ventil auf/zu) mittels externer Befehlsgeber.
- **Toggel‑Ersatz:** Kombination mit nachgeschalteten Logikbausteinen ermöglicht auch Toggle‑Funktionen.

## Vergleich mit ähnlichen Bausteinen

Der Standardbaustein **E_SR** (bzw. E_RS) besitzt in der Regel einen vordefinierten Anfangszustand (meist `FALSE`) und setzt sich nach dem Start sofort in den Zustand RESET. Bei E_SR_SYM hingegen ist der Anfangszustand neutral (START), was eine symmetrische Behandlung beider Ereignisse erlaubt. Im Gegensatz zu dominanten Varianten (E_SR mit Set‑Dominanz oder E_RS mit Reset‑Dominanz) gibt es hier keine Priorität – das zuletzt eingetroffene Ereignis bestimmt den Ausgang.

## Fazit

Der Funktionsblock **E_SR_SYM** bietet eine flexible, ereignisgesteuerte bistabile Speicherzelle mit symmetrischem Startverhalten. Seine einfache Zustandsmaschine und die klare Schnittstelle machen ihn besonders für Steuerungsaufgaben geeignet, bei denen der Anfangszustand nicht vorgegeben, sondern durch den ersten Impuls der Umgebung bestimmt werden soll. Dadurch unterscheidet er sich von klassischen SR‑Bausteinen und erweitert den Werkzeugkasten für ereignisbasierte Automatisierungslösungen.