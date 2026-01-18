# AND_4

```{index} single: AND_4
```

![AND_4](https://user-images.githubusercontent.com/116869307/214143907-734625fe-6ca3-48ce-b30e-ae7b7edfc288.png)

* * * * * * * * * *

## Einleitung
Der AND_4 Funktionsblock ist ein generischer Baustein zur Berechnung der bitweisen booleschen UND-Verknüpfung. Er verarbeitet vier Eingangswerte und führt eine logische UND-Operation auf Bitebene durch. Der Baustein ist nach dem IEC 61131-3 Standard klassifiziert und unterstützt beliebige Bit-Datentypen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung - löst die Berechnung aus

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung - signalisiert den Abschluss der Berechnung

### **Daten-Eingänge**
- **IN1**: AND-Eingang 1 (ANY_BIT Datentyp)
- **IN2**: AND-Eingang 2 (ANY_BIT Datentyp)
- **IN3**: AND-Eingang 3 (ANY_BIT Datentyp)
- **IN4**: AND-Eingang 4 (ANY_BIT Datentyp)

### **Daten-Ausgänge**
- **OUT**: AND-Ergebnis (ANY_BIT Datentyp)

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Bei Empfang des REQ-Ereignisses führt der AND_4-Baustein eine bitweise UND-Verknüpfung aller vier Eingangswerte durch. Das Ergebnis wird am Datenausgang OUT bereitgestellt und gleichzeitig wird das CNF-Ereignis zur Bestätigung der erfolgreichen Berechnung ausgegeben. Die Operation wird für jedes Bit der Eingangswerte separat durchgeführt.

## Technische Besonderheiten
- Unterstützt den generischen Datentyp ANY_BIT, was die Verwendung mit verschiedenen Bit-Datentypen wie BOOL, BYTE, WORD, DWORD etc. ermöglicht
- Vier unabhängige Eingänge für flexible Verknüpfungsmöglichkeiten
- Ereignisgesteuerte Ausführung für deterministisches Verhalten
- Kompatibel mit IEC 61131-3 Standard

## Zustandsübergang
1. **Wartezustand**: Block wartet auf REQ-Ereignis
2. **Berechnungszustand**: Bei REQ-Empfang werden alle vier Eingänge bitweise UND-verknüpft
3. **Ausgabezustand**: Ergebnis wird an OUT ausgegeben und CNF-Ereignis wird getriggert
4. Rückkehr in Wartezustand

## Anwendungsszenarien
- Bitmasken-Operationen in Steuerungsanwendungen
- Paritätsprüfungen und Fehlererkennung
- Signalverarbeitung in industriellen Automatisierungssystemen
- Logische Verknüpfungen mehrerer digitaler Signale
- Filteroperationen in Datenverarbeitungssystemen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu Standard-AND-Blöcken mit weniger Eingängen bietet AND_4 die Möglichkeit, vier Signale gleichzeitig zu verknüpfen, was komplexere logische Operationen in einem einzigen Schritt ermöglicht. Gegenüber sequenziellen AND-Verknüpfungen mehrerer Blöcke bietet AND_4 eine kompaktere Lösung mit besserer Übersichtlichkeit.

## Fazit
Der AND_4 Funktionsblock stellt eine effiziente und flexible Lösung für bitweise UND-Verknüpfungen mit vier Eingängen dar. Seine generische Natur ermöglicht den Einsatz in verschiedenen Anwendungsbereichen, während die ereignisgesteuerte Architektur eine zuverlässige Integration in komplexere Steuerungssysteme gewährleistet.