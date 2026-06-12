# AX_SR_SYM


![AX_SR_SYM](./AX_SR_SYM.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AX_SR_SYM** ist ein ereignisgesteuertes, bistabiles Flipflop mit symmetrischem Einschaltverhalten. Er implementiert einen Set-Reset-Speicher, der über die Ereignisse `S` (Set) und `R` (Reset) angesteuert wird. Im Gegensatz zu ähnlichen Bausteinen ist der Startzustand nicht vordefiniert; der Baustein reagiert auf das erste eintreffende Ereignis – unabhängig davon, ob es sich um `S` oder `R` handelt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Name | Typ   | Beschreibung               |
|------|-------|----------------------------|
| S    | Event | Setzt den Ausgang Q auf TRUE. |
| R    | Event | Setzt den Ausgang Q auf FALSE. |

### **Ereignis-Ausgänge**
Keine (der Ausgangswert wird über einen Adapter bereitgestellt).

### **Daten-Eingänge**
Keine.

### **Daten-Ausgänge**
Keine (der Ausgangswert wird über einen Adapter bereitgestellt).

### **Adapter**
| Name | Typ                                          | Beschreibung                          |
|------|----------------------------------------------|---------------------------------------|
| Q    | `adapter::types::unidirectional::AX`         | Bietet den aktuellen binären Zustand. Der Adapter stellt ein Ereignis (`E1`) und einen Datenwert (`D1`) bereit. Nach jeder Zustandsänderung wird `Q.E1` ausgelöst und der neue Wert an `Q.D1` ausgegeben. |

## Funktionsweise
Der Baustein basiert auf einem einfachen Zustandsautomaten mit drei Zuständen:
- **START**: Initialzustand nach dem Start. Es wird kein Ausgangswert ausgegeben.
- **SET**: Der Ausgang wird auf TRUE gesetzt. Bei Betreten dieses Zustands wird `Q.E1` ausgelöst und `Q.D1` auf `TRUE` gesetzt.
- **RESET**: Der Ausgang wird auf FALSE gesetzt. Bei Betreten dieses Zustands wird `Q.E1` ausgelöst und `Q.D1` auf `FALSE` gesetzt.

Die Transitionen erfolgen ausschließlich durch die Ereignisse `S` und `R`. Aus dem START-Zustand führt sowohl `S` nach SET als auch `R` nach RESET (symmetrisches Verhalten). Aus SET gelangt man nur mit `R` nach RESET, und aus RESET nur mit `S` zurück nach SET.

## Technische Besonderheiten
- **Symmetrisches Start-up-Verhalten**: Der Baustein startet im Zustand START, ohne einen definierten Ausgangswert. Erst das erste eintreffende Ereignis (S oder R) bestimmt den Anfangszustand. Dies unterscheidet sich von Bausteinen, die standardmäßig auf FALSE oder TRUE initialisieren.
- **Adapter-Schnittstelle**: Der Zustand wird nicht direkt als Datenausgang geführt, sondern über einen unidirektionalen Adapter (`AX`). Änderungen werden durch ein Ereignis (`Q.E1`) signalisiert, sodass der empfangende Baustein asynchron reagieren kann.

## Zustandsübersicht
| Zustand | Beschreibung                                         |
|---------|------------------------------------------------------|
| START   | Warte auf erstes Ereignis; kein Ausgangswert definiert. |
| SET     | Ausgangswert TRUE; gesetzt durch Ereignis `S`.        |
| RESET   | Ausgangswert FALSE; zurückgesetzt durch Ereignis `R`. |

**Transitionen:**
- START → SET bei Ereignis `S`
- START → RESET bei Ereignis `R`
- SET → RESET bei Ereignis `R`
- RESET → SET bei Ereignis `S`

## Anwendungsszenarien
- **Speicherung eines binären Zustands** in Steuerungslogiken, bei denen der Anfangswert erst durch ein Ereignis definiert werden soll.
- **Ereignisgesteuerte Schalter** in Verbindung mit Adapter-basierten Kommunikationsmustern.
- **Ersetzen eines SR-Flipflops**, wenn ein symmetrisches Einschaltverhalten gefordert ist.

## Vergleich mit ähnlichen Bausteinen
- **SR-Flipflop** (z. B. `AX_SR`): Besitzt oft einen definierten Startwert (z. B. FALSE) und verhält sich asymmetrisch, wenn beide Eingänge gleichzeitig aktiv sind. Der `AX_SR_SYM` legt dagegen den Anfangswert erst durch das erste Ereignis fest.
- **RS-Flipflop**: Grundsätzlich ähnliche Logik, aber mit umgekehrter Priorität (Reset dominiert). Der `AX_SR_SYM` hat keine Priorität – der zuletzt empfangene Eingang bestimmt den Zustand.
- **Adapterbasierte Bausteine**: Vorteil der ereignisgesteuerten Zustandsübergabe über Adapter; viele Standard-FB verwenden stattdessen direkte Datenausgänge.

## Fazit
Der `AX_SR_SYM` eignet sich ideal für Anwendungen, die ein bistabiles Speicherverhalten mit nicht vorbestimmtem Startwert erfordern. Die symmetrische Reaktion auf `S` und `R` im Startzustand sowie die Ausgabe über einen Adapter machen ihn zu einer flexiblen Komponente in ereignisgesteuerten Automatisierungssystemen.