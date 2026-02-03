# OR_5

```{index} single: OR_5
```

![OR_5](https://user-images.githubusercontent.com/116869307/214143625-4af69974-60f8-424f-a81f-1dbeafacb707.png)

* * * * * * * * * *

## Einleitung
Der OR_5 Funktionsblock ist ein generischer Baustein zur Durchführung einer bitweisen ODER-Verknüpfung mit fünf Eingängen. Er implementiert eine Standard-Bitfunktion gemäß IEC 61131-3 und kann mit beliebigen Bit-Datentypen arbeiten.

![OR_5](OR_5.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung - löst die Berechnung der ODER-Verknüpfung aus

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung - signalisiert den Abschluss der Berechnung

### **Daten-Eingänge**
- **IN1**: ODER-Eingang 1 (ANY_BIT Datentyp)
- **IN2**: ODER-Eingang 2 (ANY_BIT Datentyp)
- **IN3**: ODER-Eingang 3 (ANY_BIT Datentyp)
- **IN4**: ODER-Eingang 4 (ANY_BIT Datentyp)
- **IN5**: ODER-Eingang 5 (ANY_BIT Datentyp)

### **Daten-Ausgänge**
- **OUT**: ODER-Ergebnis (ANY_BIT Datentyp)

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der OR_5 Funktionsblock führt eine bitweise ODER-Verknüpfung aller fünf Eingangswerte durch. Bei Aktivierung des REQ-Ereignisses werden die Werte an IN1 bis IN5 verarbeitet und das Ergebnis an OUT ausgegeben. Das CNF-Ereignis signalisiert den Abschluss der Operation.

Die ODER-Operation wird nach folgender Logik durchgeführt:
```
OUT = IN1 OR IN2 OR IN3 OR IN4 OR IN5
```

## Technische Besonderheiten
- **Generischer Datentyp**: Verwendet ANY_BIT, was die Verwendung mit verschiedenen Bit-Datentypen (BOOL, BYTE, WORD, DWORD, LWORD) ermöglicht
- **Fünf Eingänge**: Bietet mehr Flexibilität als Standard-ODER-Bausteine mit typischerweise zwei Eingängen
- **Ereignisgesteuert**: Arbeitet nach dem Echtzeit-Prinzip mit REQ/CNF-Signalisierung

## Zustandsübergang
1. **Warte-Zustand**: Block wartet auf REQ-Ereignis
2. **Berechnungs-Zustand**: Bei REQ werden alle Eingänge verarbeitet
3. **Ausgabe-Zustand**: Ergebnis wird an OUT gesetzt und CNF wird ausgelöst
4. Rückkehr zu Warte-Zustand

## Anwendungsszenarien
- Kombination mehrerer binärer Signale in Steuerungsanwendungen
- Überwachungssysteme mit mehreren Eingangsbedingungen
- Signalverarbeitung in industriellen Automatisierungssystemen
- Verwendung in Sicherheitsschaltungen mit mehreren Überwachungssensoren

## ⚖️ Vergleich mit ähnlichen Bausteinen
- **Standard OR-Bausteine**: Typischerweise nur zwei Eingänge, OR_5 bietet fünf Eingänge
- **AND-Bausteine**: Führen UND-Verknüpfungen statt ODER-Verknüpfungen durch
- **XOR-Bausteine**: Führen exklusive ODER-Operationen durch

## Fazit
Der OR_5 Funktionsblock ist ein vielseitiger und leistungsstarker Baustein für bitweise ODER-Operationen mit fünf Eingängen. Seine generische Natur ermöglicht den Einsatz in verschiedenen Anwendungsbereichen, während die ereignisgesteuerte Architektur eine präzise Steuerung der Ausführungszeitpunkte gewährleistet.