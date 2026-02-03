# F_NOT

```{index} single: F_NOT
```

![F_NOT](https://user-images.githubusercontent.com/116869307/214144000-4586686b-f3a0-4caa-9896-3dfb75baa550.png)

* * * * * * * * * *

## Einleitung
Der F_NOT Funktionsblock implementiert eine bitweise logische NOT-Operation gemäß dem IEC 61131-3 Standard. Er führt eine bitweise Invertierung des Eingangswertes durch und gibt das Ergebnis am Ausgang aus.

![F_NOT](F_NOT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Service Request - Löst die Berechnung der NOT-Operation aus

### **Ereignis-Ausgänge**
- **CNF**: Confirmation of Requested Service - Signalisiert die Beendigung der Berechnung

### **Daten-Eingänge**
- **IN**: Eingangswert vom Typ ANY_BIT - Der zu invertierende Wert

### **Daten-Ausgänge**
- **OUT**: Ausgangswert vom Typ ANY_BIT - Das invertierte Ergebnis

### **Adapter**
Keine Adapter vorhanden

## Funktionsweise
Bei Empfang eines REQ-Ereignisses führt der F_NOT-Block eine bitweise logische NOT-Operation auf den Eingangswert IN aus. Jedes Bit des Eingangswertes wird invertiert (0 wird zu 1, 1 wird zu 0). Das Ergebnis wird am Ausgang OUT ausgegeben und durch das CNF-Ereignis bestätigt.

## Technische Besonderheiten
- Unterstützt den ANY_BIT-Datentyp, was die Verwendung mit verschiedenen Bit-Datentypen (BOOL, BYTE, WORD, DWORD, etc.) ermöglicht
- Echtzeitfähige Ausführung
- Standardkonforme Implementierung nach IEC 61131-3

## Zustandsübergang
1. Wartezustand auf REQ-Ereignis
2. Bei REQ: Ausführung der NOT-Operation
3. Ausgabe des Ergebnisses an OUT
4. Senden des CNF-Ereignisses
5. Rückkehr in Wartezustand

## Anwendungsszenarien
- Bitmanipulation in Steuerungsprogrammen
- Invertierung von Statusbits
- Logische Verneinung von Bedingungen
- Signalumkehr in digitalen Schaltungen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen logischen Operationen wie F_AND oder F_OR führt F_NOT ausschließlich eine unäre Operation (ein Operand) durch, während andere logische Bausteine typischerweise binäre Operationen (zwei Operanden) implementieren.






## Zugehörige Übungen

* [Uebung_006a3_sub](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_006a3_sub.md)

## Fazit
Der F_NOT Funktionsblock bietet eine standardkonforme, effiziente Lösung für bitweise Invertierungsoperationen in IEC 61131-3 kompatiblen Steuerungssystemen. Seine einfache Schnittstelle und universelle ANY_BIT-Typunterstützung machen ihn zu einem vielseitig einsetzbaren Baustein für verschiedene Anwendungsfälle.