# OR_6

```{index} single: OR_6
```

![OR_6](https://user-images.githubusercontent.com/116869307/214143660-1a2216f3-f723-4864-8a8a-8deeb4e0ea8c.png)

* * * * * * * * * *
## Einleitung
Der OR_6 Funktionsblock ist ein generischer Bitweise-ODER-Baustein, der sechs Eingangswerte verarbeitet. Er führt eine bitweise logische ODER-Operation auf den sechs Eingangswerten durch und gibt das Ergebnis aus. Der Baustein ist nach der IEC 61131-3 Norm klassifiziert und kann mit beliebigen Bit-Datentypen (ANY_BIT) arbeiten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung - löst die Berechnung der ODER-Operation aus

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung - signalisiert die Beendigung der Berechnung

### **Daten-Eingänge**
- **IN1**: ODER-Eingang 1 (ANY_BIT)
- **IN2**: ODER-Eingang 2 (ANY_BIT)
- **IN3**: ODER-Eingang 3 (ANY_BIT)
- **IN4**: ODER-Eingang 4 (ANY_BIT)
- **IN5**: ODER-Eingang 5 (ANY_BIT)
- **IN6**: ODER-Eingang 6 (ANY_BIT)

### **Daten-Ausgänge**
- **OUT**: ODER-Ergebnis (ANY_BIT)

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Bei Empfang des REQ-Ereignisses führt der OR_6-Baustein eine bitweise ODER-Operation auf allen sechs Eingangswerten durch. Die Operation wird nach folgender Logik ausgeführt:
```
OUT = IN1 OR IN2 OR IN3 OR IN4 OR IN5 OR IN6
```
Nach Abschluss der Berechnung wird das CNF-Ereignis zusammen mit dem Ergebniswert ausgegeben.

## Technische Besonderheiten
- **Generischer Datentyp**: Verwendet ANY_BIT, was die Verwendung mit verschiedenen Bit-Datentypen (BOOL, BYTE, WORD, DWORD, LWORD) ermöglicht
- **Sechs Eingänge**: Verarbeitet bis zu sechs Eingangswerte in einer einzigen Operation
- **Bitweise Operation**: Führt die ODER-Operation auf Bitebene durch
- **Ereignisgesteuert**: Nur bei REQ-Ereignis wird die Berechnung durchgeführt

## Zustandsübergänge
1. **Wartezustand**: Block wartet auf REQ-Ereignis
2. **Berechnungszustand**: Bei REQ-Ereignis werden alle Eingänge verarbeitet
3. **Ausgabezustand**: Nach Berechnung wird CNF-Ereignis mit Ergebnis ausgegeben
4. **Rückkehr**: Rückkehr in Wartezustand

## Anwendungsszenarien
- **Bitmasken-Operationen**: Kombination mehrerer Bitmasken
- **Steuerungslogik**: Zusammenfassung mehrerer Bedingungen
- **Signalverarbeitung**: Verknüpfung mehrerer digitaler Signale
- **Datenfilterung**: Selektive Aktivierung von Bits aus verschiedenen Quellen

## Vergleich mit ähnlichen Bausteinen
- **OR_2**: Verarbeitet nur zwei Eingänge
- **OR_4**: Verarbeitet vier Eingänge
- **GEN_OR**: Generische Basisimplementierung, die OR_6 erweitert
- **XOR-Bausteine**: Führen exklusive ODER-Operationen durch

## Fazit
Der OR_6 Funktionsblock bietet eine effiziente Lösung für bitweise ODER-Operationen mit bis zu sechs Eingangswerten. Seine generische Natur ermöglicht maximale Flexibilität bei der Verwendung verschiedener Bit-Datentypen, während die ereignisgesteuerte Architektur eine präzise Steuerung der Berechnungszeitpunkte gewährleistet.