# FB_SR

```{index} single: FB_SR
```

<img width="1312" height="242" alt="FB_SR" src="https://github.com/user-attachments/assets/97406c32-e30d-47c7-958c-cb76b2fcd83c" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `FB_SR` ist ein bistabiles Element, das als Set-Reset-Flipflop (SR-Flipflop) fungiert. Es speichert einen Zustand basierend auf den Eingangssignalen und behält diesen bei, bis er durch neue Eingangssignale geändert wird.

![FB_SR](FB_SR.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung (Trigger für die Ausführung des Funktionsblocks)

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung (wird nach der Verarbeitung der Eingänge ausgelöst)

### **Daten-Eingänge**
- **S1** (BOOL): Set-Eingang (setzt den Ausgang `Q1` auf `TRUE`, wenn `TRUE`)
- **R** (BOOL): Reset-Eingang (setzt den Ausgang `Q1` auf `FALSE`, wenn `TRUE`)

### **Daten-Ausgänge**
- **Q1** (BOOL): Ausgang (gespeicherter Zustand des Flipflops)

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock `FB_SR` verarbeitet die Eingänge `S1` (Set) und `R` (Reset) gemäß der folgenden Logik:
- Wenn `S1` `TRUE` ist, wird `Q1` auf `TRUE` gesetzt.
- Wenn `R` `TRUE` ist, wird `Q1` auf `FALSE` gesetzt.
- Wenn beide Eingänge `FALSE` sind, behält `Q1` seinen vorherigen Zustand bei.

Die Logik wird durch den folgenden Algorithmus implementiert:
```ST
ALGORITHM REQ
Q1 := S1 OR ((NOT R) AND Q1);
END_ALGORITHM
```

## Technische Besonderheiten
- **IEC 61131-3 Konformität**: Dieser Baustein bildet das Verhalten des klassischen `SR`-Flipflops exakt nach. Da die Eingänge `S1` und `R` Daten-Eingänge sind, die beim `REQ`-Ereignis gleichzeitig abgetastet werden, ist eine logische Priorisierung notwendig.
- **Setz-Dominanz**: Der Baustein implementiert eine **Setz-Priorität**. Wenn `S1` und `R` gleichzeitig `TRUE` sind, wird der Ausgang `Q1` auf `TRUE` gesetzt.
- **Trigger**: Die Ausführung (Logikberechnung) erfolgt nur beim Ereignis `REQ`.

## Zustandsübersicht
Der Zustand des Flipflops (`Q1`) hängt von den aktuellen Werten von `S1` und `R` ab (zum Zeitpunkt des `REQ`):
- `S1 = TRUE`: `Q1` wird auf `TRUE` gesetzt (unabhängig von `R`). -> **Setz-Dominanz**
- `R = TRUE` UND `S1 = FALSE`: `Q1` wird auf `FALSE` gesetzt.
- `S1 = FALSE` und `R = FALSE`: `Q1` bleibt unverändert.

## Anwendungsszenarien
- Speicherung von binären Zuständen in Steuerungsanwendungen, wo IEC 61131-3 Verhalten gefordert ist.
- Verwendung in Schaltnetzen, bei denen die Dominanz des Setz-Signals sicherheitsrelevant oder prozessbedingt notwendig ist.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- **[E_SR](../../events/E_SR.md)**: Der `E_SR` ist rein ereignisgesteuert. Dort gibt es keine gleichzeitigen Signale und somit keine Dominanz in diesem Sinne (das letzte Ereignis gewinnt). Der `FB_SR` hingegen wertet statische Signale zum Zeitpunkt `REQ` aus und erzwingt die Setz-Dominanz.
- **[FB_RS](FB_RS.md)**: Das Gegenstück mit **Rücksetz-Dominanz** (Reset Priority).




## 🛠️ Zugehörige Übungen

* [Uebung_006e1](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_006e1.md)
* [Uebung_006e1_AX](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_006e1_AX.md)

## Fazit
Der `FB_SR` ist ein grundlegender und effizienter Funktionsblock für die Speicherung binärer Zustände in Steuerungsanwendungen. Seine einfache Logik und klare Schnittstelle machen ihn ideal für den Einsatz in verschiedenen industriellen Automatisierungslösungen.