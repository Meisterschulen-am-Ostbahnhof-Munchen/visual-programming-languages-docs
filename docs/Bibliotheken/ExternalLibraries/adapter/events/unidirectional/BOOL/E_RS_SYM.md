# E_RS_SYM


![E_RS_SYM](./E_RS_SYM.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **E_RS_SYM** ist ein ereignisgesteuertes, bistabiles Flipflop mit symmetrischem Startverhalten. Er realisiert eine Set-Reset-Funktionalität, bei der der Ausgang Q sowohl durch ein Set- als auch durch ein Reset-Ereignis definiert geschaltet wird. Im Gegensatz zu einem klassischen RS‑Flipflop besitzt der Baustein einen expliziten Startzustand, der auf beide Ereignisse gleichermaßen reagiert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ    | Beschreibung            |
|------|--------|-------------------------|
| `R`  | Event  | Reset des Ausgangs Q    |
| `S`  | Event  | Setzen des Ausgangs Q   |

### **Ereignis-Ausgänge**

| Name | Typ    | Beschreibung                        | Mit Daten |
|------|--------|-------------------------------------|-----------|
| `EO` | Event  | Ausgang Q hat sich geändert         | Ja (mit Q)|

### **Daten-Eingänge**

Keine Daten-Eingänge vorhanden.

### **Daten-Ausgänge**

| Name | Typ    | Beschreibung              |
|------|--------|---------------------------|
| `Q`  | BOOL   | Wert des Flipflops (TRUE/FALSE) |

### **Adapter**

Keine Adapter vorhanden.

## Funktionsweise

Der Baustein befindet sich nach dem Einschalten im **START**-Zustand. Von diesem Zustand aus wird bei einem Ereignis an `S` der Zustand **SET** und bei einem Ereignis an `R` der Zustand **RESET** erreicht. Dabei wird jeweils der Ausgang `Q` auf `TRUE` (SET) bzw. `FALSE` (RESET) gesetzt und das Ereignis `EO` ausgegeben.

- Im **SET**-Zustand führt ein Ereignis an `R` zurück in den **RESET**-Zustand.
- Im **RESET**-Zustand führt ein Ereignis an `S` zurück in den **SET**-Zustand.
- Der Ausgang `Q` wird nur bei einem Zustandswechsel (d.h. bei Übergang nach SET oder RESET) aktualisiert.

Das symmetrische Startverhalten bedeutet, dass unmittelbar nach der Initialisierung sowohl ein Set- als auch ein Reset-Ereignis akzeptiert werden – es gibt keine Voreinstellung von `Q`.

## Technische Besonderheiten

- **Symmetrisches Startverhalten:** Im START-Zustand ist kein Ausgangswert festgelegt. Der Baustein reagiert auf das erste eintreffende Ereignis (S oder R) gleichberechtigt. Dies unterscheidet ihn von üblichen RS-Flipflops, die nach dem Start meist einen definierten (häufig FALSE) Anfangswert liefern.
- **Ereignisgesteuerter Ausgang:** Das Ereignis `EO` wird genau dann ausgelöst, wenn sich der Wert von `Q` ändert. Somit wird eine Signaländerung explizit weitergegeben.
- **Keine Daten-Eingänge:** Der Baustein arbeitet rein ereignisgesteuert ohne zusätzliche Datenparameter.

## Zustandsübersicht

Der FB besitzt drei Zustände:

| Zustand | Beschreibung |
|---------|--------------|
| START   | Initialzustand nach dem Einschalten; wartet auf erstes S- oder R-Ereignis. |
| SET     | Q = TRUE; kann durch R in den RESET-Zustand wechseln. |
| RESET   | Q = FALSE; kann durch S in den SET-Zustand wechseln. |

**Transitionen:**

- START → SET bei Ereignis `S`
- START → RESET bei Ereignis `R`
- SET → RESET bei Ereignis `R`
- RESET → SET bei Ereignis `S`

## Anwendungsszenarien

- **Initialisierung von Speicherbits** in Steuerungen, bei denen der Anfangswert bewusst nicht vorgegeben werden soll.
- **Symmetrische Umschaltlogiken**, die sowohl das Setzen als auch das Rücksetzen eines Merkers zu Beginn gleichermaßen erlauben.
- **Alternative zu klassischen RS-Haltern**, wenn ein definiertes Anlaufverhalten vermieden werden muss (z. B. bei sicherheitskritischen Anwendungen, wo ein unbestimmter Anfangszustand toleriert wird).

## Vergleich mit ähnlichen Bausteinen

| Baustein | Eigenschaft |
|----------|-------------|
| **E_RS** | Klassisches RS-Flipflop mit meist asymmetrischem Startverhalten (Q initial FALSE). |
| **E_RS_SYM** | Wie E_RS, aber mit symmetrischem Startverhalten – kein voreingestellter Wert, Startzustand akzeptiert beide Ereignisse gleich. |
| **SR-Flipflop** | Ähnliche Funktion, jedoch häufig mit Priorität für Set oder Reset; E_RS_SYM ist prioritätsneutral. |

## Fazit

Der **E_RS_SYM** eignet sich für alle Anwendungen, die ein einfaches, aber start‑symmetrisches Speicherverhalten benötigen. Durch die saubere Trennung von Ereignisänderung (EO) und Datenausgabe (Q) lässt er sich gut in ereignisgesteuerte Steuerungsarchitekturen nach IEC 61499 einbinden. Seine klare Zustandsmaschine macht ihn zuverlässig und einfach verständlich.