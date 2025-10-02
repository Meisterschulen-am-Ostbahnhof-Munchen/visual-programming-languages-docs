# OR_2

* * * * * * * * * *

## Einleitung
Der OR_2-Funktionsblock ist ein generischer Baustein zur Berechnung der bitweisen booleschen ODER-Verknüpfung. Er führt eine logische ODER-Operation auf zwei Eingabewerten durch und gibt das Ergebnis aus. Der Baustein ist gemäß der Norm IEC 61131-3 klassifiziert und unterstützt generische Datentypen für maximale Flexibilität.

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

## Fazit
Der OR_2-Funktionsblock stellt eine flexible und normkonforme Lösung für bitweise ODER-Operationen in Automatisierungssystemen dar. Seine generische Natur ermöglicht den Einsatz in verschiedenen Anwendungskontexten mit unterschiedlichen Datentypen, während die ereignisgesteuerte Architektur eine effiziente Ressourcennutzung gewährleistet.