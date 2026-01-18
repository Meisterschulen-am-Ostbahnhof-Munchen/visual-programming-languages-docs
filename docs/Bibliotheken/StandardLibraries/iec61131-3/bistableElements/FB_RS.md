# FB_RS

```{index} single: FB_RS
```

<img width="1308" height="242" alt="FB_RS" src="https://github.com/user-attachments/assets/ff0ca1ab-bc02-459b-bbda-2ef4f8aa880b" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock FB_RS ist ein bistabiles Element, das als Set-Reset-Flipflop (RS-Flipflop) fungiert. Es speichert einen Zustand und ändert diesen basierend auf den Eingangssignalen S (Set) und R1 (Reset). Der Block ist gemäß dem IEC 61499-1 Standard implementiert und eignet sich für Steuerungsanwendungen, die eine Zustandsspeicherung erfordern.

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
- **Priorität**: Der Reset-Eingang (R1) hat Priorität über den Set-Eingang (S).
- **Speicherverhalten**: Der Block behält seinen Zustand bei, solange keine Änderung an S oder R1 erfolgt.

## Zustandsübersicht
Der FB_RS hat zwei stabile Zustände:
1. **Q1 = TRUE**: Wenn S zuletzt TRUE war und R1 FALSE ist.
2. **Q1 = FALSE**: Wenn R1 zuletzt TRUE war oder beide Eingänge FALSE sind.

## Anwendungsszenarien
- Speicherung von Schaltzuständen in Steuerungsanwendungen.
- Implementierung von Verriegelungslogik (z.B. Not-Aus-Schaltungen).
- Zustandssteuerung in Automatisierungsprozessen.

## Vergleich mit ähnlichen Bausteinen
- **FB_SR**: Ein ähnlicher Funktionsblock, bei dem der Set-Eingang Priorität über den Reset-Eingang hat.
- **FB_RS_EXT**: Erweiterte Version mit zusätzlichen Features wie einem zusätzlichen Reset-Eingang oder einem Enable-Signal.

## Fazit
Der FB_RS ist ein grundlegender und robuster Funktionsblock für Zustandsspeicherung in IEC 61499-basierten Steuerungssystemen. Seine einfache und klare Logik macht ihn besonders geeignet für Anwendungen, bei denen ein zuverlässiges Set-Reset-Verhalten erforderlich ist. Die Priorisierung des Reset-Eingangs stellt sicher, dass Sicherheitsfunktionen zuverlässig ausgeführt werden können.
