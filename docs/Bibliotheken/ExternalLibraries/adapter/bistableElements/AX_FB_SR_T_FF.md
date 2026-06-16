# AX_FB_SR_T_FF


![AX_FB_SR_T_FF](./AX_FB_SR_T_FF.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AX_FB_SR_T_FF** realisiert ein bistabiles, setzdominantes Latch (SR-Flipflop) kombiniert mit einer Toggle-Funktion. Die gesamte Kommunikation erfolgt über Adapter-Schnittstellen, die sowohl Ereignis- als auch Datensignale bündeln.

## Schnittstellenstruktur
Der Baustein besitzt keine direkten Ereignis- oder Dateneingänge/-ausgänge, sondern ausschließlich Adapter. Diese stellen jeweils ein Ereignis (`E1`) und einen Datenwert (`D1`) vom Typ `BOOL` bereit.

### **Ereignis-Eingänge**
Keine direkten Ereigniseingänge. Die folgenden Adapter stellen über ihr Ereignis `E1` den Triggermechanismus bereit:
- **SET1** – Setzereignis
- **RESET** – Rücksetzereignis
- **CLK** – Taktereignis (für Toggle)

### **Ereignis-Ausgänge**
Keine direkten Ereignisausgänge. Der Adapter **Q1** stellt über sein Ereignis `E1` die Bestätigung der Ausgangsänderung bereit.

### **Daten-Eingänge**
Die drei Eingangsadapter liefern jeweils einen Datenwert `D1` (BOOL):
- **SET1.D1** – Setzsignal (aktiv bei TRUE)
- **RESET.D1** – Rücksetzsignal (aktiv bei TRUE)
- **CLK.D1** – Taktsignal (positive Flanke löst Toggle aus)

### **Daten-Ausgänge**
Der Ausgangsadapter **Q1** gibt über **Q1.D1** den aktuellen Zustand des Latch als BOOL-Wert aus.

### **Adapter**

| Adapter | Typ | Richtung | Beschreibung |
|---------|-----|----------|--------------|
| `SET1`  | `adapter::types::unidirectional::AX` | Socket (Eingang) | Setz-Eingang |
| `RESET` | `adapter::types::unidirectional::AX` | Socket (Eingang) | Rücksetz-Eingang |
| `CLK`   | `adapter::types::unidirectional::AX` | Socket (Eingang) | Takt-Eingang für Toggle |
| `Q1`    | `adapter::types::unidirectional::AX` | Plug (Ausgang) | Ausgang des Latch |

## Funktionsweise
Der Baustein arbeitet nach folgendem prioritätsgesteuerten Algorithmus:
1. **Setzdominanz**: Wenn `SET1.D1 = TRUE` ist, wird der Ausgang `Q1.D1` auf `TRUE` gesetzt.
2. **Rücksetzen**: Sonst, wenn `RESET.D1 = TRUE` ist, wird `Q1.D1` auf `FALSE` gesetzt.
3. **Toggle**: Falls weder Setzen noch Rücksetzen aktiv sind und am Takteingang `CLK.D1` eine **steigende Flanke** (Übergang von FALSE auf TRUE) erkannt wird, wird der aktuelle Ausgangswert umgeschaltet (`Q1.D1 := NOT Q1.D1`).

Die Flankenerkennung erfolgt durch die interne Variable `EDGE`: Sie speichert den vorherigen Wert von `CLK.D1`. Der Algorithmus prüft, ob `CLK.D1 = TRUE` und `EDGE = FALSE` ist. Nach der Berechnung wird `EDGE` auf den aktuellen `CLK.D1` gesetzt.

## Technische Besonderheiten
- **Reine Adapter-Schnittstelle**: Der Baustein nutzt keine klassischen Ereignis-/Datenports, sondern kapselt die Signale in Adaptern. Dies ermöglicht eine flexible Wiederverwendung und Kapselung von Schnittstellen.
- **Set-Dominant-Verhalten**: Ein gleichzeitiges Setzen und Rücksetzen führt immer zum Setzen des Ausgangs.
- **Toggle mit positiver Flanke**: Die Toggle-Funktion reagiert nur auf steigende Flanken des Taktsignals, nicht auf statische Pegel.
- **Einziger ECC-Zustand**: Das ECC besteht nur aus dem Zustand `REQ`. Jedes eingehende Ereignis (`SET1.E1`, `RESET.E1` oder `CLK.E1`) führt sofort zur erneuten Ausführung des Algorithmus.

## Zustandsübersicht
Der Funktionsblock besitzt nur einen Zustand:
- **REQ** – Wartet auf eingehende Ereignisse. Bei jedem Ereignis wird der Algorithmus `REQ` durchlaufen. Alle Transitionen führen zurück zu `REQ`.

Intern wird die Variable `EDGE` zur Flankenerkennung verwendet; sie ist Teil des internen Zustands, aber nicht als ECC-Zustand sichtbar.

## Anwendungsszenarien
- **Steuerung mit Vorrang**: Wenn ein Setzimpuls immer Vorrang vor einem Rücksetzimpuls haben soll, z. B. bei Sicherheitsschaltungen.
- **Kombinierte Set/Reset- und Toggle-Funktion**: Für Anwendungen, bei denen ein Ausgang sowohl durch externe Signale gesetzt/rückgesetzt als auch durch einen Taster umgeschaltet werden kann (z. B. manuelle Bedienung mit Vorrang).
- **Adapter-basierte Systeme**: In einer modularen Umgebung, in der Schnittstellen über Adapter standardisiert sind (z. B. AX-Adaptersystem).

## Vergleich mit ähnlichen Bausteinen
- **SR-Flipflop (setzdominant)** – reine Set/Reset-Funktion ohne Toggle. Der vorliegende Baustein erweitert dies um die Toggle-Möglichkeit.
- **T-Flipflop** – nur Toggle (kein Setzen/Rücksetzen). AX_FB_SR_T_FF bietet zusätzliche Setz- und Rücksetzpriorität.
- **Resetdominante SR-Flipflops** – bei Konflikten wird zurückgesetzt. Dieser Baustein verhält sich gegenteilig.

## Fazit
Der **AX_FB_SR_T_FF** vereint ein setzdominantes SR-Latch mit einer flankengetriggerten Toggle-Funktion in einem kompakten Baustein. Die ausschließliche Verwendung von Adaptern macht ihn ideal für modulare, adapterbasierte Automatisierungslösungen. Die klare Priorisierung und die Flankenerkennung bieten ein vorhersagbares und robustes Schaltverhalten.