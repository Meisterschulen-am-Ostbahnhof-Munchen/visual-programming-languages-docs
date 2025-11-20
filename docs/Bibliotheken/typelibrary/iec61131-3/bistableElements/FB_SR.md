# FB_SR

<img width="1312" height="242" alt="FB_SR" src="https://github.com/user-attachments/assets/97406c32-e30d-47c7-958c-cb76b2fcd83c" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `FB_SR` ist ein bistabiles Element, das als Set-Reset-Flipflop (SR-Flipflop) fungiert. Es speichert einen Zustand basierend auf den Eingangssignalen und behält diesen bei, bis er durch neue Eingangssignale geändert wird.

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
- Der Funktionsblock ist ein einfaches bistabiles Element ohne zusätzliche Zustandsverwaltung oder komplexe Zeitsteuerung.
- Die Ausführung wird durch das Ereignis `REQ` getriggert und bestätigt durch `CNF`.

## Zustandsübersicht
Der Zustand des Flipflops (`Q1`) hängt von den aktuellen Werten von `S1` und `R` ab:
- `S1 = TRUE`: `Q1` wird auf `TRUE` gesetzt (unabhängig von `R`).
- `R = TRUE`: `Q1` wird auf `FALSE` gesetzt (falls `S1` nicht `TRUE` ist).
- `S1 = FALSE` und `R = FALSE`: `Q1` bleibt unverändert.

## Anwendungsszenarien
- Speicherung von binären Zuständen in Steuerungsanwendungen.
- Verwendung in Schaltnetzen und Schaltwerken, wo ein einfaches Speicherelement benötigt wird.
- Integration in größere Steuerungssysteme, die bistabile Elemente erfordern.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen bistabilen Elementen wie `FB_RS` (Reset-Set-Flipflop) priorisiert `FB_SR` den Set-Eingang (`S1`) über den Reset-Eingang (`R`).
- Einfacher als komplexe Speicherelemente mit zusätzlichen Funktionen wie Taktsteuerung oder zusätzlichen Eingängen.

## Fazit
Der `FB_SR` ist ein grundlegender und effizienter Funktionsblock für die Speicherung binärer Zustände in Steuerungsanwendungen. Seine einfache Logik und klare Schnittstelle machen ihn ideal für den Einsatz in verschiedenen industriellen Automatisierungslösungen.
