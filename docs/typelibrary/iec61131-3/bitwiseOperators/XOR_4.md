# XOR_4

* * * * * * * * * *
## Einleitung
Der XOR_4 Funktionsblock ist ein generischer Baustein zur Berechnung der bitweisen XOR-Verknüpfung mit vier Eingängen. Er implementiert die exklusive ODER-Operation auf Bitebene gemäß dem IEC 61131-3 Standard und kann mit verschiedenen Bit-Datentypen arbeiten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung - löst die Berechnung der XOR-Operation aus

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung - signalisiert den Abschluss der Berechnung

### **Daten-Eingänge**
- **IN1**: XOR-Eingang 1 (ANY_BIT Datentyp)
- **IN2**: XOR-Eingang 2 (ANY_BIT Datentyp)
- **IN3**: XOR-Eingang 3 (ANY_BIT Datentyp)
- **IN4**: XOR-Eingang 4 (ANY_BIT Datentyp)

### **Daten-Ausgänge**
- **OUT**: XOR-Ergebnis (ANY_BIT Datentyp)

### **Adapter**
Der Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Eintreffen des REQ-Ereignisses führt der XOR_4-Block eine bitweise XOR-Operation auf allen vier Eingängen durch. Die Operation wird gemäß der folgenden Logik ausgeführt:
```
OUT = IN1 XOR IN2 XOR IN3 XOR IN4
```
Nach Abschluss der Berechnung wird das CNF-Ereignis zusammen mit dem Ergebnis an OUT ausgegeben.

## Technische Besonderheiten
- **Generischer Datentyp**: Verwendet ANY_BIT, was die Verwendung mit verschiedenen Bit-Datentypen (BOOL, BYTE, WORD, DWORD, LWORD) ermöglicht
- **Vierfache XOR-Operation**: Verarbeitet vier Eingänge in einer einzigen Operation
- **Ereignisgesteuert**: Die Ausführung wird durch das REQ-Ereignis getriggert
- **Standardkonform**: Entspricht der IEC 61131-3 Norm für bitweise boolesche Funktionen

## Zustandsübergänge
1. **Wartezustand**: Block wartet auf REQ-Ereignis
2. **Berechnungszustand**: Bei REQ-Ereignis werden alle Eingänge verarbeitet
3. **Ausgabezustand**: CNF-Ereignis wird mit dem berechneten Ergebnis ausgegeben
4. Rückkehr in Wartezustand

## Anwendungsszenarien
- **Bitmanipulation**: Verwendung in Steuerungsanwendungen für bitweise Operationen
- **Paritätsprüfung**: Implementierung von Paritätsbits oder Fehlererkennung
- **Datenverschlüsselung**: Einfache kryptografische Operationen
- **Signalverarbeitung**: Kombination mehrerer digitaler Signale

## Vergleich mit ähnlichen Bausteinen
- **AND/OR-Bausteine**: Verarbeiten logische UND/ODER-Operationen statt exklusivem ODER
- **XOR mit weniger Eingängen**: Dieser Block bietet vier Eingänge im Vergleich zu Standard-XOR-Blöcken mit typischerweise zwei Eingängen
- **Generische vs. spezifische Blöcke**: Kann verschiedene Bit-Datentypen verarbeiten, während spezifische Blöcke auf einen Datentyp beschränkt sind

## Fazit
Der XOR_4 Funktionsblock bietet eine flexible und standardkonforme Lösung für bitweise XOR-Operationen mit vier Eingängen. Seine generische Natur ermöglicht den Einsatz in verschiedenen Anwendungsbereichen, während die ereignisgesteuerte Architektur eine effiziente Integration in Steuerungssysteme gewährleistet.