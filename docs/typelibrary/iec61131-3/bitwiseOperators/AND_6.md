# AND_6

* * * * * * * * * *
## Einleitung
Der AND_6 Funktionsblock ist ein generischer Baustein zur Berechnung der bitweisen booleschen UND-Verknüpfung mit sechs Eingängen. Er implementiert eine Standard-Funktion gemäß IEC 61131-3 und führt eine logische UND-Operation auf Bit-Ebene für bis zu sechs Eingangswerte durch.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ** (Normal Execution Request): Startet die Ausführung der UND-Operation. Löst die Verarbeitung der Eingangsdaten aus.

### **Ereignis-Ausgänge**
- **CNF** (Execution Confirmation): Signalisiert den Abschluss der Berechnung und die Verfügbarkeit des Ergebnisses.

### **Daten-Eingänge**
- **IN1** (ANY_BIT): UND-Eingang 1
- **IN2** (ANY_BIT): UND-Eingang 2  
- **IN3** (ANY_BIT): UND-Eingang 3
- **IN4** (ANY_BIT): UND-Eingang 4
- **IN5** (ANY_BIT): UND-Eingang 5
- **IN6** (ANY_BIT): UND-Eingang 6

### **Daten-Ausgänge**
- **OUT** (ANY_BIT): UND-Ergebnis der bitweisen Verknüpfung aller sechs Eingänge

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Bei Aktivierung des REQ-Ereignisses führt der AND_6-Block eine bitweise UND-Verknüpfung aller sechs Eingangswerte durch. Die Operation wird für jedes Bitposition separat ausgeführt: Das Ergebnisbit an Position i ist nur dann 1, wenn alle sechs Eingangsbits an Position i den Wert 1 haben. Nach Abschluss der Berechnung wird das CNF-Ereignis ausgelöst und das Ergebnis am OUT-Ausgang verfügbar gemacht.

## Technische Besonderheiten
- Verwendet den generischen Datentyp ANY_BIT, der verschiedene Bit-Datentypen (BOOL, BYTE, WORD, DWORD, LWORD) unterstützt
- Alle Eingänge müssen denselben Datentyp aufweisen
- Das Ergebnis hat denselben Datentyp wie die Eingänge
- Implementiert als generischer Funktionsblock mit der Klasse 'GEN_AND'

## Zustandsübergang
1. **Wartezustand**: Block wartet auf REQ-Ereignis
2. **Berechnungszustand**: Bei REQ werden alle Eingänge bitweise UND-verknüpft
3. **Ausgabezustand**: Ergebnis wird an OUT ausgegeben und CNF-Ereignis wird ausgelöst
4. Rückkehr in Wartezustand

## Anwendungsszenarien
- Bitmasken-Operationen in Steuerungsanwendungen
- Mehrfache Bedingungsprüfungen in logischen Schaltungen
- Signalverarbeitung mit mehreren Eingangssignalen
- Sicherheitsrelevante Schaltungen mit mehreren Überwachungssignalen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfacheren UND-Blöcken mit weniger Eingängen bietet AND_6 die Möglichkeit, bis zu sechs Signale gleichzeitig zu verknüpfen, was die Programmstruktur vereinfacht und weniger Verknüpfungsbausteine erfordert. Gegenüber seriellen UND-Verknüpfungen bietet er eine bessere Übersichtlichkeit und geringere Latenz.

## Fazit
Der AND_6 Funktionsblock stellt eine effiziente und übersichtliche Lösung für komplexe bitweise UND-Verknüpfungen mit bis zu sechs Eingängen dar. Seine generische Implementierung ermöglicht den Einsatz mit verschiedenen Bit-Datentypen und macht ihn zu einem vielseitigen Werkzeug in der Automatisierungstechnik.