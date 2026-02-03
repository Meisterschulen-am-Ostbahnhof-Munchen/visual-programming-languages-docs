# AND_2

```{index} single: AND_2
```

![AND_2](https://user-images.githubusercontent.com/116869307/214143461-f2104d1b-a147-4a9f-a118-f527fc245b5f.png)

OUT wird nur geschalten wenn an IN1 und IN2 ein Bool (Signal anliegt) Z.b. von einem Schalter

![](https://user-images.githubusercontent.com/113907580/227966597-94049ae9-429e-49d8-93ca-b46b31b27550.png)

bei allen anderen "AND" Bausteinen selbe prinzip nur dass immer alle IN eingänge immer True sein müssen

* * * * * * * * * *

## Einleitung
Der AND_2 Funktionsblock ist ein generischer Baustein zur Berechnung der bitweisen booleschen UND-Verknüpfung. Er implementiert eine Standard-Funktion gemäß IEC 61131-3 und kann mit beliebigen Bit-Datentypen verwendet werden.

![AND_2](AND_2.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung - löst die Berechnung der UND-Verknüpfung aus

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung - signalisiert den Abschluss der Berechnung

### **Daten-Eingänge**
- **IN1** (ANY_BIT): UND-Eingang 1 - erster Operand für die bitweise UND-Verknüpfung
- **IN2** (ANY_BIT): UND-Eingang 2 - zweiter Operand für die bitweise UND-Verknüpfung

### **Daten-Ausgänge**
- **OUT** (ANY_BIT): UND-Ergebnis - Resultat der bitweisen UND-Verknüpfung

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Bei Eintreffen des REQ-Ereignisses führt der Funktionsblock eine bitweise UND-Verknüpfung zwischen den beiden Eingangswerten IN1 und IN2 durch. Das Ergebnis wird am Datenausgang OUT ausgegeben und gleichzeitig wird das CNF-Ereignis zur Bestätigung der Ausführung generiert.

Die Operation wird für jedes Bit der Eingangswerte separat durchgeführt:
- Bit = 1, wenn beide entsprechenden Bits der Eingänge 1 sind
- Bit = 0, wenn mindestens eines der entsprechenden Bits der Eingänge 0 ist

## Technische Besonderheiten
- **Generischer Datentyp**: Verwendet ANY_BIT, was die Verwendung mit verschiedenen Bit-Datentypen (BOOL, BYTE, WORD, DWORD, LWORD) ermöglicht
- **Bitweise Operation**: Führt die UND-Operation auf Bitebene durch
- **Ereignisgesteuert**: Die Ausführung wird durch Ereignisse gesteuert, nicht durch Zykluszeiten

## Zustandsübergang
1. **Wartezustand**: Block wartet auf REQ-Ereignis
2. **Berechnungszustand**: Bei REQ-Ereignis werden IN1 und IN2 verarbeitet
3. **Ausgabezustand**: Ergebnis wird an OUT ausgegeben und CNF-Ereignis wird generiert
4. Rückkehr in Wartezustand

## Anwendungsszenarien
- Bitmasken-Operationen in Steuerungsanwendungen
- Filterung von Daten durch Maskierung unerwünschter Bits
- Logische Verknüpfungen in digitalen Schaltungen
- Datenvorverarbeitung in Kommunikationsprotokollen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen logischen Verknüpfungsblöcken:
- AND_2 ist generisch und unterstützt verschiedene Bit-Datentypen
- Arbeitet bitweise im Gegensatz zu rein booleschen UND-Blöcken
- Ereignisgesteuert im Gegensatz zu zyklusgesteuerten Blöcken






## Zugehörige Übungen

* [Uebung_002a](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_002a.md)
* [Uebung_002a_AX](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_002a_AX.md)
* [Uebung_002b2](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_002b2.md)
* [Uebung_002b3_AX](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_002b3_AX.md)
* [Uebung_006a3_AX](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_006a3_AX.md)
* [Uebung_088](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_088.md)

## Fazit
Der AND_2 Funktionsblock bietet eine flexible und standardkonforme Lösung für bitweise UND-Operationen in IEC 61131-3 basierten Steuerungssystemen. Seine generische Natur ermöglicht den Einsatz in vielfältigen Anwendungsbereichen, während die ereignisgesteuerte Architektur eine effiziente Ressourcennutzung gewährleistet.