# OR_2

```{index} single: OR_2
```

![OR_2](https://user-images.githubusercontent.com/116869307/214144026-378fb776-128a-41b0-ad4c-4d23d70d12d0.png)

Ein häufiger Anwendungsfall ist ein Soft KI und ein AUX Button

TRUE dominiert, also sobald an einem IN ein TRUE anliegt wird der OUT auf TRUE geschalten

![](https://user-images.githubusercontent.com/113907580/227976949-e73303db-993f-431e-b679-477dd9ad877e.png)

* * * * * * * * * *

## Einleitung
Der OR_2-Funktionsblock ist ein generischer Baustein zur Berechnung der bitweisen booleschen ODER-Verknüpfung. Er führt eine logische ODER-Operation auf zwei Eingabewerten durch und gibt das Ergebnis aus. Der Baustein ist gemäß der Norm IEC 61131-3 klassifiziert und unterstützt generische Datentypen für maximale Flexibilität.

![OR_2](OR_2.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung - löst die Berechnung der ODER-Operation aus

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung - signalisiert die Beendigung der Berechnung

### **Daten-Eingänge**
- **IN1**: ODER-Eingang 1 (Typ: ANY_BIT) - erster Operand für die ODER-Operation
- **IN2**: ODER-Eingang 2 (Typ: ANY_BIT) - zweiter Operand für die ODER-Operation

### **Daten-Ausgänge**
- **OUT**: ODER-Ergebnis (Typ: ANY_BIT) - Ergebnis der bitweisen ODER-Verknüpfung

### **Adapter**
Der Baustein verwendet keine Adapter.

## Funktionsweise
Bei Eintreffen des REQ-Ereignisses führt der OR_2-Baustein eine bitweise ODER-Verknüpfung zwischen den beiden Eingabewerten IN1 und IN2 durch. Das Ergebnis wird am Datenausgang OUT ausgegeben und gleichzeitig wird das CNF-Ereignis zur Bestätigung der erfolgreichen Berechnung generiert.

Die ODER-Operation wird auf Bitebene durchgeführt, wobei jedes Bit der Eingabewerte separat verarbeitet wird. Das Ergebnisbit ist 1, wenn mindestens eines der entsprechenden Eingabebits 1 ist.

## Technische Besonderheiten
- **Generische Typunterstützung**: Verwendet den ANY_BIT-Datentyp, was bedeutet, dass der Baustein mit verschiedenen Bit-Datentypen (BOOL, BYTE, WORD, DWORD, LWORD) arbeiten kann
- **Standardkonforme Implementierung**: Entspricht der IEC 61131-3 Norm für bitweise boolesche Funktionen
- **Ereignisgesteuerte Ausführung**: Nur bei aktivem REQ-Ereignis wird die Berechnung durchgeführt

## Zustandsübergänge
1. **Wartezustand**: Block wartet auf REQ-Ereignis
2. **Berechnungszustand**: Bei REQ-Ereignis werden IN1 und IN2 verarbeitet
3. **Ausgabezustand**: Ergebnis wird an OUT ausgegeben und CNF-Ereignis wird generiert
4. **Rückkehr**: Block kehrt in Wartezustand zurück

## Anwendungsszenarien
- Bitweise Maskenoperationen in Steuerungsanwendungen
- Kombination von Statusflags in Prozesssteuerungen
- Logische Verknüpfungen in digitalen Schaltungen
- Datenmanipulation in Kommunikationsprotokollen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen booleschen Operationen wie AND oder XOR bietet OR_2 die spezifische Eigenschaft, dass das Ergebnis wahr ist, wenn mindestens einer der Operanden wahr ist. Im Gegensatz zu einfachen booleschen ODER-Bausteinen unterstützt OR_2 generische Bit-Datentypen und ermöglicht somit die Verarbeitung verschiedener Datenbreiten.





## Zugehörige Übungen

* [Uebung_002a3](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_002a3.md)
* [Uebung_002a3_AX](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_002a3_AX.md)
* [Uebung_002b2](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_002b2.md)
* [Uebung_002b3_AX](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_002b3_AX.md)
* [Uebung_035a](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_035a.md)
* [Uebung_035a2](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_035a2.md)
* [Uebung_035a2_AX](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_035a2_AX.md)
* [Uebung_035a3](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_035a3.md)
* [Uebung_035a3_AX](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_035a3_AX.md)
* [Uebung_039_sub_Outputs](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_039_sub_Outputs.md)
* [Uebung_089](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_089.md)
* [Uebung_160_AX](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_160_AX.md)
* [Uebung_160b2_AX](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_160b2_AX.md)
* [Uebung_160b_AX](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_160b_AX.md)

## Fazit
Der OR_2-Funktionsblock stellt eine flexible und normkonforme Lösung für bitweise ODER-Operationen in Automatisierungssystemen dar. Seine generische Natur ermöglicht den Einsatz in verschiedenen Anwendungskontexten mit unterschiedlichen Datentypen, während die ereignisgesteuerte Architektur eine effiziente Ressourcennutzung gewährleistet.