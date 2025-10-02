# AND_5

* * * * * * * * * *

## Einleitung
Der AND_5-Funktionsblock ist ein generischer Baustein zur Berechnung der bitweisen logischen UND-Verknüpfung mit fünf Eingängen. Er implementiert eine Standard-Bitoperation gemäß IEC 61131-3 und kann mit beliebigen Bit-Datentypen arbeiten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung - löst die Berechnung der UND-Verknüpfung aus

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung - signalisiert den Abschluss der Berechnung

### **Daten-Eingänge**
- **IN1**: UND-Eingang 1 (ANY_BIT Datentyp)
- **IN2**: UND-Eingang 2 (ANY_BIT Datentyp)
- **IN3**: UND-Eingang 3 (ANY_BIT Datentyp)
- **IN4**: UND-Eingang 4 (ANY_BIT Datentyp)
- **IN5**: UND-Eingang 5 (ANY_BIT Datentyp)

### **Daten-Ausgänge**
- **OUT**: UND-Ergebnis (ANY_BIT Datentyp)

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Bei Eintreffen des REQ-Ereignisses führt der Funktionsblock eine bitweise UND-Operation über alle fünf Eingänge durch. Das Ergebnis wird am Datenausgang OUT ausgegeben und gleichzeitig wird das CNF-Ereignis zur Bestätigung der abgeschlossenen Berechnung gesendet.

Die Operation wird für jedes Bitposition separat durchgeführt:
OUT[i] = IN1[i] ∧ IN2[i] ∧ IN3[i] ∧ IN4[i] ∧ IN5[i]

## Technische Besonderheiten
- **Generischer Datentyp**: Verwendet ANY_BIT, wodurch der Baustein mit verschiedenen Bit-Datentypen (BOOL, BYTE, WORD, DWORD, LWORD) kompatibel ist
- **Fünf Eingänge**: Ermöglicht die Verknüpfung von bis zu fünf verschiedenen Bitwerten
- **Ereignisgesteuert**: Die Berechnung wird nur bei Anforderung durch das REQ-Ereignis durchgeführt

## Zustandsübergang
1. **Wartezustand**: Block wartet auf REQ-Ereignis
2. **Berechnungszustand**: Bei REQ-Eingang werden alle Eingänge bitweise UND-verknüpft
3. **Ausgabezustand**: Ergebnis wird an OUT ausgegeben und CNF-Ereignis wird gesendet
4. Rückkehr in Wartezustand

## Anwendungsszenarien
- Bitmasken-Operationen in Steuerungsanwendungen
- Mehrfache Bedingungsprüfungen in Sicherheitssystemen
- Signalverarbeitung mit mehreren Eingangssignalen
- Filteroperationen in Datenverarbeitungssystemen

## Vergleich mit ähnlichen Bausteinen
- **AND_2**: Bietet nur zwei Eingänge für die UND-Verknüpfung
- **OR_5**: Führt bitweise ODER-Verknüpfungen mit fünf Eingängen durch
- **XOR_5**: Führt bitweise exklusive ODER-Verknüpfungen durch

## Fazit
Der AND_5-Funktionsblock bietet eine flexible und effiziente Lösung für bitweise UND-Operationen mit fünf Eingängen. Seine generische Natur ermöglicht den Einsatz mit verschiedenen Bit-Datentypen, was ihn zu einem vielseitigen Baustein für komplexe logische Verknüpfungen in Automatisierungsanwendungen macht.