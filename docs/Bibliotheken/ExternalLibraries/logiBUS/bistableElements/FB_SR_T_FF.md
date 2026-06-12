# FB_SR_T_FF


![FB_SR_T_FF](./FB_SR_T_FF.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein `FB_SR_T_FF` realisiert ein bistabiles, set-dominantes RS-Flipflop mit zusätzlicher Toggle-Funktion. Die Schaltung kombiniert das Verhalten eines SR-Latches (Set-Dominant) mit einem flankengesteuerten T-Flipflop, das bei jedem Taktzyklus den Ausgangszustand wechselt, wenn weder Set noch Reset aktiv sind.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ | Event | Normaler Ausführungsauftrag (löst Verarbeitung aus) |

### **Ereignis-Ausgänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF | Event | Bestätigung der Ausführung |

### **Daten-Eingänge**
| Name | Typ | Initialwert | Kommentar |
|------|-----|-------------|-----------|
| S1 | BOOL | - | Set-Eingang (dominant) |
| R | BOOL | - | Reset-Eingang |
| CLK | BOOL | - | Taktsignal (steigende Flanke löst Toggle aus) |

### **Daten-Ausgänge**
| Name | Typ | Initialwert | Kommentar |
|------|-----|-------------|-----------|
| Q1 | BOOL | - | Ausgangssignal |

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Baustein wird durch ein Ereignis am Eingang `REQ` aktiviert. Bei jeder Ausführung werden die Eingänge `S1`, `R` und `CLK` abgetastet und der interne Zustand (`Q1`) nach folgenden Regeln aktualisiert:

1. **Set-Dominanz:** Ist `S1 = TRUE`, wird `Q1` auf `TRUE` gesetzt (unabhängig von `R` und `CLK`).
2. **Reset:** Falls `S1 = FALSE` und `R = TRUE`, wird `Q1` auf `FALSE` gesetzt.
3. **Toggle bei steigender Flanke:** Falls weder `S1` noch `R` aktiv sind (`S1 = FALSE` und `R = FALSE`) und der aktuelle Wert von `CLK` `TRUE` ist, während er im vorherigen Zyklus `FALSE` war (d.h. steigende Flanke), wird der Ausgang `Q1` invertiert (`Q1 := NOT Q1`). Andernfalls bleibt `Q1` unverändert.

Der interne Hilfsmerker `EDGE` speichert den letzten Zustand von `CLK`, um Flankenerkennung zu ermöglichen. Initial ist `EDGE = TRUE`, sodass bei der ersten Ausführung keine steigende Flanke erkannt wird, es sei denn, `CLK` ist von Anfang an `FALSE`.

Der Algorithmus wird in Structured Text (ST) implementiert und nach jeder Verarbeitung das Bestätigungsereignis `CNF` gesendet.

## Technische Besonderheiten
- **Set-dominantes Verhalten:** Solange `S1 = TRUE`, wird `R` ignoriert. Dies verhindert den undefinierten Zustand eines klassischen RS-Flipflops.
- **Flankengesteuertes Toggle:** Die Toggle-Funktion wird nur bei einer steigenden Flanke von `CLK` ausgelöst, nicht bei jedem Taktzyklus. Dadurch ist das Verhalten deterministisch und ermöglicht eine Synchronisation mit dem Taktsignal.
- **Interne Speicherung der Flanke:** Der interne Merker `EDGE` speichert den vorherigen Wert von `CLK`. Initial auf `TRUE` gesetzt, damit der erste Zyklus keine Toggle-Auslösung erzwingt.
- **Zyklische Abarbeitung:** Eine Verarbeitung kann beliebig oft aufgerufen werden; die Funktion hängt nur von den aktuellen Eingangswerten und dem gespeicherten Flankenzustand ab.

## Zustandsübersicht
Der Baustein besitzt einen funktionalen Zustandsautomaten mit einem Zustand `REQ`. Dieser Zustand führt den Algorithmus aus und sendet anschließend `CNF`. Es gibt keine weiteren expliziten Zustände im Automaten, da das Flipflop-Verhalten rein datengetrieben im Algorithmus abgebildet wird.

| Zustand | Eingehende Ereignisse | Aktion | Ausgehende Ereignisse |
|---------|-----------------------|--------|------------------------|
| REQ | REQ | Ausführen des Algorithmus, Aktualisierung von `Q1` und `EDGE` | CNF |

## Anwendungsszenarien
- **Steuerung mit Set/Reset-Vorrang:** Der Baustein eignet sich für Anwendungen, bei denen ein Vorrang von Set vor Reset erforderlich ist (z.B. Sicherheitsschaltungen).
- **Toggle-Funktion mit Takt:** Kombiniert mit einem Taktgeber kann der Ausgang bei jedem Taktimpuls umschalten, solange keine Set- oder Reset-Anforderung vorliegt. Dies kann z.B. für modulare Zähler oder Zustandsmaschinen genutzt werden.
- **Flankengesteuerte Schaltungen:** In Automatisierungsprozessen, bei denen Zustandsänderungen nur zu bestimmten Zeitpunkten erfolgen dürfen (z.B. Abtastungen).

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einem reinen SR-Flipflop (z.B. `SR_FF`) bietet dieser Baustein eine eingebaute Toggle-Funktion, die den Ausgang bei jedem Taktzyklus invertieren kann. Gegenüber einem T-Flipflop (`T_FF`) hat der Baustein zusätzlich die Set- und Reset-Eingänge mit Dominanz. Das klassische JK-Flipflop besitzt zwei steuernde Eingänge (J, K) ohne Dominanz, während dieses Baustein eine Kombination aus Set-Dominant und flankengesteuertem Toggle darstellt.

## Fazit
Der `FB_SR_T_FF` ist ein vielseitiger, kompakter Funktionsbaustein, der die Eigenschaften eines set-dominanten RS-Flipflops und eines flankengesteuerten T-Flipflops vereint. Dank der einfachen Schnittstelle (ein Ereigniseingang, drei boolesche Eingänge) lässt er sich leicht in bestehende Steuerungslogiken integrieren und eignet sich für eine Vielzahl von Anwendungen, bei denen ein priorisierter Set/Reset mit zusätzlicher Umschaltfunktion benötigt wird. Die Implementierung in Structured Text gewährleistet klare Lesbarkeit und einfache Anpassung.