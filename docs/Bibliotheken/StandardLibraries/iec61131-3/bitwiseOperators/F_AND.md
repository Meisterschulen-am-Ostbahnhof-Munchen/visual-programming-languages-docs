# F_AND

```{index} single: F_AND
```

<img width="1336" height="244" alt="F_AND" src="https://github.com/user-attachments/assets/a65a419c-0126-4dd6-9ab3-6e40b32ddcac" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_AND` ist ein standardisierter bitweiser boolescher UND-Operator gemäß IEC 61131-3. Er führt eine bitweise UND-Verknüpfung auf zwei Eingangsvariablen durch und gibt das Ergebnis an den Ausgang weiter. Dieser Block ist besonders nützlich für logische Operationen in Steuerungsanwendungen.

![F_AND](F_AND.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Dienstaufforderung. Löst die Ausführung der UND-Operation aus. Verknüpft mit den Daten-Eingängen `IN1` und `IN2`.

### **Ereignis-Ausgänge**
- **CNF**: Bestätigung der angeforderten Dienstleistung. Wird nach erfolgreicher Ausführung der Operation ausgelöst. Verknüpft mit dem Daten-Ausgang `OUT`.

### **Daten-Eingänge**
- **IN1**: Erster Eingang für die bitweise UND-Operation. Typ: `ANY_BIT`.
- **IN2**: Zweiter Eingang für die bitweise UND-Operation. Typ: `ANY_BIT`.

### **Daten-Ausgänge**
- **OUT**: Ergebnis der bitweisen UND-Operation. Typ: `ANY_BIT`.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der `F_AND`-Block führt eine bitweise UND-Verknüpfung zwischen den Eingangsvariablen `IN1` und `IN2` durch, wenn das Ereignis `REQ` ausgelöst wird. Das Ergebnis wird an den Ausgang `OUT` weitergegeben und das Ereignis `CNF` wird ausgelöst, um die erfolgreiche Ausführung zu bestätigen.

## Technische Besonderheiten
- Unterstützt den Datentyp `ANY_BIT`, was bedeutet, dass verschiedene Bit-Typen wie `BOOL`, `BYTE`, `WORD`, `DWORD`, etc. verwendet werden können.
- Der Block ist standardkonform nach IEC 61131-3 und in der Kategorie "standard bitwise boolean function" klassifiziert.

## Zustandsübersicht
1. **Idle-Zustand**: Wartet auf das `REQ`-Ereignis.
2. **Ausführungszustand**: Führt die bitweise UND-Operation aus, wenn `REQ` empfangen wird.
3. **Bestätigungszustand**: Sendet das `CNF`-Ereignis und gibt das Ergebnis an `OUT` aus.

## Anwendungsszenarien
- Logische Steuerungen in industriellen Automatisierungssystemen.
- Bitweise Maskenoperationen in Datenverarbeitungsanwendungen.
- Kombination mit anderen logischen Blöcken für komplexe Steuerungslogik.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- **F_OR**: Führt eine bitweise ODER-Verknüpfung durch.
- **F_XOR**: Führt eine bitweise exklusive ODER-Verknüpfung durch.
- **F_NOT**: Führt eine bitweise Negation durch.




## 🛠️ Zugehörige Übungen

* [Uebung_002a2](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_002a2.md)
* [Uebung_002a2_AX](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_002a2_AX.md)

## Fazit
Der `F_AND`-Funktionsblock ist ein grundlegender Baustein für bitweise logische Operationen in IEC 61131-3-konformen Steuerungssystemen. Seine einfache und standardisierte Schnittstelle macht ihn zuverlässig und vielseitig einsetzbar in verschiedenen Automatisierungsanwendungen.