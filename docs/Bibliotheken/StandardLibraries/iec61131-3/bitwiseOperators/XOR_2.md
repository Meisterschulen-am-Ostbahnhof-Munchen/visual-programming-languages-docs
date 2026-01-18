# XOR_2

```{index} single: XOR_2
```

![XOR_2](https://user-images.githubusercontent.com/116869307/214143689-2a5c46a2-8706-400e-9fc7-fc74efa57eea.png)

* * * * * * * * * *

## Einleitung
Der XOR_2-Funktionsblock ist ein generischer Baustein zur Berechnung der bitweisen booleschen XOR-Operation. Er führt eine exklusive ODER-Verknüpfung zwischen zwei Eingabewerten durch und gibt das Ergebnis aus. Der Baustein ist für alle ANY_BIT-Datentypen geeignet und ermöglicht somit eine flexible Verwendung mit verschiedenen Bit-Längen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung - löst die Berechnung der XOR-Operation aus

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung - signalisiert die Beendigung der Berechnung

### **Daten-Eingänge**
- **IN1** (ANY_BIT): XOR-Eingang 1 - erster Operand für die XOR-Operation
- **IN2** (ANY_BIT): XOR-Eingang 2 - zweiter Operand für die XOR-Operation

### **Daten-Ausgänge**
- **OUT** (ANY_BIT): XOR-Ergebnis - Resultat der bitweisen XOR-Operation

### **Adapter**
Der Baustein verfügt über keine Adapter-Schnittstellen.

## Funktionsweise
Bei Eintreffen des REQ-Ereignisses führt der XOR_2-Baustein eine bitweise XOR-Operation zwischen den beiden Eingabewerten IN1 und IN2 durch. Die Operation wird für jedes Bitpaar der Eingabewerte separat ausgeführt:
- Wenn beide Bits gleich sind (beide 0 oder beide 1), wird das Ergebnisbit auf 0 gesetzt
- Wenn die Bits unterschiedlich sind, wird das Ergebnisbit auf 1 gesetzt

Nach Abschluss der Berechnung wird das Ergebnis über den OUT-Ausgang ausgegeben und das CNF-Ereignis zur Bestätigung der Ausführung gesendet.

## Technische Besonderheiten
- **Generische Implementierung**: Unterstützt alle ANY_BIT-Datentypen (BOOL, BYTE, WORD, DWORD, LWORD)
- **Bitweise Operation**: Führt die XOR-Operation auf Bitebene durch
- **Ereignisgesteuerte Ausführung**: Synchronisation über REQ/CNF-Ereignisse
- **Typensicherheit**: Garantiert korrekte Operation für alle unterstützten Datentypen

## Zustandsübergänge
1. **Wartezustand**: Baustein wartet auf REQ-Ereignis
2. **Berechnungszustand**: Bei REQ-Ereignis führt Baustein XOR-Operation aus
3. **Ausgabezustand**: Nach Berechnung wird OUT gesetzt und CNF-Ereignis gesendet
4. **Rückkehr**: Baustein kehrt in Wartezustand zurück

## Anwendungsszenarien
- **Bitmanipulation**: Umkehrung spezifischer Bits in Datenwörtern
- **Paritätsprüfung**: Erstellung von Paritätsbits für Fehlererkennung
- **Datenverschlüsselung**: Einfache kryptographische Operationen
- **Steuerungstechnik**: Logische Verknüpfungen in Automatisierungssystemen
- **Datenvergleich**: Erkennung von Unterschieden zwischen Datenwerten

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen logischen Bausteinen bietet XOR_2:
- **Flexibilität**: Unterstützung verschiedener Bit-Längen durch ANY_BIT-Typ
- **Spezifische Logik**: Exklusive ODER-Operation im Gegensatz zu AND/OR-Operationen
- **Generische Implementierung**: Wiederverwendbarkeit über verschiedene Datentypen hinweg

## Fazit
Der XOR_2-Funktionsblock stellt eine effiziente und flexible Lösung für bitweise XOR-Operationen in 4diac-Systemen dar. Seine generische Natur ermöglicht den Einsatz in vielfältigen Anwendungsbereichen, während die ereignisgesteuerte Architektur eine zuverlässige Integration in komplexe Steuerungssysteme gewährleistet.
