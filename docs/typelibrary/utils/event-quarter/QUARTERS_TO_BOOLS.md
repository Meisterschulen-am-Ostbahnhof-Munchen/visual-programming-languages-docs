# QUARTERS_TO_BOOLS

![QUARTERS_TO_BOOLS](https://github.com/user-attachments/assets/88884a13-9dc5-49a3-969c-4158ac0da540)

* * * * * * * * * *
## Einleitung
Der Funktionsblock QUARTERS_TO_BOOLS ist ein Composite-FB, der 16 QUARTER_TO_BOOL-Funktionsblöcke kapselt. Er dient zur Konvertierung von 2-Bit-Quarter-Byte-Eingängen (4 Zustände) in einzelne BOOL-Ausgänge. Der FB ist besonders nützlich in Steuerungssystemen, wo komprimierte Daten in einzelne digitale Signale umgewandelt werden müssen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderungs-Event (triggert die Verarbeitung)
  - Verknüpft mit allen 16 IB_xx Eingängen

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigungs-Event (wird nach Abschluss der Verarbeitung ausgelöst)
  - Verknüpft mit allen 16 Q_xx Ausgängen

### **Daten-Eingänge**
16 Eingänge vom Typ BYTE (IB_00 bis IB_15):
- Jeder Eingang repräsentiert ein 2-Bit Quarter-Byte mit 4 möglichen Zuständen
- Initialwert: quarter::COMMAND_DISABLE
- Kommentar: "2bit (quarter Byte) Output with 4 States"

### **Daten-Ausgänge**
16 Ausgänge vom Typ BOOL (Q_00 bis Q_15):
- Jeder Ausgang repräsentiert ein konvertiertes Boolesches Signal
- Initialwert: FALSE
- Kommentar: "BOOL Output"

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
1. Bei Empfang des REQ-Events werden alle 16 Quarter-Byte-Eingänge (IB_00 bis IB_15) parallel verarbeitet
2. Jeder Eingang wird durch einen internen QUARTER_TO_BOOL-FB in ein Boolesches Signal umgewandelt
3. Die Verarbeitung erfolgt in einer Kaskade (serielle Ausführung der internen FBs)
4. Nach Abschluss aller 16 Konvertierungen wird das CNF-Event ausgelöst
5. Die konvertierten BOOL-Werte stehen an den Ausgängen Q_00 bis Q_15 zur Verfügung

## Technische Besonderheiten
- Verwendet 16 interne QUARTER_TO_BOOL-Funktionsblöcke
- Die Verarbeitung erfolgt seriell über eine Eventkaskade
- Alle Eingänge haben standardmäßig den Wert quarter::COMMAND_DISABLE
- Alle Ausgänge sind standardmäßig FALSE

## Zustandsübersicht
Der FB hat keine expliziten Zustände. Die Verarbeitung erfolgt:
1. Wartend (keine aktive Verarbeitung)
2. Verarbeitend (während der Quarter-Byte-Konvertierung)
3. Abschließend (Auslösen des CNF-Events)

## Anwendungsszenarien
- Dekodierung von komprimierten Steuersignalen
- Schnittstelle zwischen Systemen mit unterschiedlicher Datenrepräsentation
- Zustandsüberwachung von Systemen mit komprimierten Statusinformationen
- Steuerung von digitalen Ausgängen basierend auf komprimierten Eingangsdaten

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu einfachen Konvertern verarbeitet dieser FB 16 Signale gleichzeitig
- Bietet eine strukturierte Lösung im Vergleich zur manuellen Verkettung einzelner Konverter
- Ermöglicht die Verarbeitung von komprimierten Daten (4 Zustände pro 2 Bit) im Gegensatz zu einfachen BOOL-Konvertern

## Fazit
Der QUARTERS_TO_BOOLS-FB bietet eine effiziente Lösung für die Massenkonvertierung von Quarter-Byte-Signalen in Boolesche Werte. Durch die Kapselung von 16 Konvertern in einem einzigen FB vereinfacht er die Systemarchitektur und reduziert den Verdrahtungsaufwand in komplexen Steuerungssystemen. Die serielle Verarbeitung über die Eventkaskade gewährleistet eine deterministische Ausführungsreihenfolge.
