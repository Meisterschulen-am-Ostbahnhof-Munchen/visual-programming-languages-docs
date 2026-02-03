# FB_RS

```{index} single: FB_RS
```

<img width="1308" height="242" alt="FB_RS" src="https://github.com/user-attachments/assets/ff0ca1ab-bc02-459b-bbda-2ef4f8aa880b" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock FB_RS ist ein bistabiles Element, das als Set-Reset-Flipflop (RS-Flipflop) fungiert. Es speichert einen Zustand und ändert diesen basierend auf den Eingangssignalen S (Set) und R1 (Reset). Der Block ist gemäß dem IEC 61499-1 Standard implementiert und eignet sich für Steuerungsanwendungen, die eine Zustandsspeicherung erfordern.

![FB_RS](FB_RS.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Löst die Ausführung des Funktionsblocks aus. Verknüpft mit den Daten-Eingängen S und R1.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Wird nach der Verarbeitung der Eingänge ausgegeben. Verknüpft mit dem Daten-Ausgang Q1.

### **Daten-Eingänge**
- **S (BOOL)**: Set-Eingang. Setzt den Ausgang Q1 auf TRUE, wenn S TRUE ist und R1 FALSE ist.
- **R1 (BOOL)**: Reset-Eingang. Setzt den Ausgang Q1 auf FALSE, wenn R1 TRUE ist.

### **Daten-Ausgänge**
- **Q1 (BOOL)**: Ausgang. Repräsentiert den gespeicherten Zustand des RS-Flipflops.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der FB_RS verarbeitet die Eingänge S und R1 bei jedem REQ-Ereignis. Der Ausgang Q1 wird nach folgender Logik aktualisiert:
- Wenn R1 TRUE ist, wird Q1 auf FALSE gesetzt (Reset hat Priorität).
- Wenn S TRUE ist und R1 FALSE ist, wird Q1 auf TRUE gesetzt.
- Wenn beide Eingänge FALSE sind, behält Q1 seinen vorherigen Zustand bei.

Die Logik wird durch den folgenden Algorithmus implementiert:
```ST
ALGORITHM REQ
Q1 := (NOT R1) AND (S OR Q1);
END_ALGORITHM
```

## Technische Besonderheiten
- **IEC 61131-3 Konformität**: Dieser Baustein bildet das Verhalten des klassischen `RS`-Flipflops exakt nach. Da die Eingänge `S` und `R1` Daten-Eingänge sind, die beim `REQ`-Ereignis gleichzeitig abgetastet werden, ist eine logische Priorisierung notwendig.
- **Rücksetz-Dominanz (Priorität)**: Der Reset-Eingang (`R1`) hat Vorrang. Wenn `S` und `R1` gleichzeitig `TRUE` sind, wird der Ausgang `Q1` auf `FALSE` gesetzt.
- **Speicherverhalten**: Der Block behält seinen Zustand bei, solange keine Änderung an `S` oder `R1` erfolgt (oder kein `REQ` Ereignis eintritt).

## Zustandsübersicht
Der `FB_RS` wertet die Eingänge bei `REQ` aus:
1.  **Q1 = FALSE**: Wenn `R1` TRUE ist (unabhängig von `S`). -> **Rücksetz-Dominanz**
2.  **Q1 = TRUE**: Wenn `S` TRUE ist UND `R1` FALSE ist.
3.  **Q1 unverändert**: Wenn beide FALSE sind.

## Anwendungsszenarien
- Speicherung von Schaltzuständen in Steuerungsanwendungen nach IEC 61131-3 Logik.
- Implementierung von Verriegelungslogik (z.B. Not-Aus-Schaltungen), wo das Abschalten (Reset) immer Vorrang haben muss.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- **[E_RS](../../events/E_RS.md)**: Der `E_RS` ist rein ereignisgesteuert ("Last Event Wins"). Der `FB_RS` hingegen wertet statische Signale zum Zeitpunkt `REQ` aus und erzwingt die Rücksetz-Dominanz.
- **[FB_SR](FB_SR.md)**: Das Gegenstück mit **Setz-Dominanz**.




## 🛠️ Zugehörige Übungen

* [Uebung_006e2](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_006e2.md)
* [Uebung_006e2_AX](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_006e2_AX.md)
* [Uebung_160b2](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_160b2.md)
* [Uebung_160b2_AX](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_160b2_AX.md)

## Fazit
Der FB_RS ist ein grundlegender und robuster Funktionsblock für Zustandsspeicherung in IEC 61499-basierten Steuerungssystemen. Seine einfache und klare Logik macht ihn besonders geeignet für Anwendungen, bei denen ein zuverlässiges Set-Reset-Verhalten erforderlich ist. Die Priorisierung des Reset-Eingangs stellt sicher, dass Sicherheitsfunktionen zuverlässig ausgeführt werden können.