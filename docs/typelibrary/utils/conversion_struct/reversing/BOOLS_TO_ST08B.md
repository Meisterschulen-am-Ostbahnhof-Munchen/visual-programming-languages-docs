# BOOLS_TO_ST08B

![BOOLS_TO_ST08B](https://github.com/user-attachments/assets/b85e850c-e5d0-48fd-a82b-71608ad03374)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `BOOLS_TO_ST08B` dient zur Konvertierung von acht einzelnen BOOL-Werten in einen zusammengesetzten ST08B-Datentyp. Dieser Block ist besonders nützlich, wenn einzelne Binärsignale zu einem strukturierten Byte zusammengefasst werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Ausführungsanforderung (triggert die Konvertierung)

### **Ereignis-Ausgänge**
- `CNF`: Bestätigung der Ausführung (wird nach erfolgreicher Konvertierung ausgelöst)

### **Daten-Eingänge**
- `IN_00` bis `IN_07`: Acht einzelne BOOL-Eingänge (Bit 00 bis Bit 07)

### **Daten-Ausgänge**
- `OUT`: Zusammengesetzter ST08B-Ausgang (enthält alle 8 Bits als strukturierten Datentyp)

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock nimmt acht einzelne BOOL-Werte entgegen und kombiniert sie zu einem ST08B-Datentyp. Bei Erhalt des REQ-Ereignisses werden die Eingangswerte gelesen und in die entsprechenden Bits des Ausgangsdatentyps geschrieben. Nach erfolgreicher Konvertierung wird das CNF-Ereignis ausgelöst.

## Technische Besonderheiten
- Direkte 1:1-Zuordnung der BOOL-Eingänge zu den Bits des ST08B-Datentyps
- Keine zusätzliche Logik oder Verarbeitung - reine Datentypkonvertierung
- ST08B ist ein strukturierter Datentyp, der 8 einzelne Bits enthält

## Zustandsübersicht
1. Wartezustand: Block wartet auf REQ-Ereignis
2. Ausführungszustand: Bei REQ werden Eingänge gelesen und Ausgang gesetzt
3. Bestätigungszustand: CNF wird ausgelöst und Block kehrt in Wartezustand zurück

## Anwendungsszenarien
- Zusammenfassen einzelner Binärsignale für die Kommunikation mit anderen Systemen
- Vorbereitung von Daten für Protokolle, die strukturierte Bytes erwarten
- Vereinfachung der Programmstruktur durch Bündelung verwandter Signale

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu Bit-Shift-Operationen bietet dieser Block eine direkte, lesbare Zuordnung
- Ähnlich zu BYTE_TO_BOOLS-Blöcken, aber in umgekehrter Richtung
- Spezialisierter als generische Konvertierungsblöcke

## Fazit
Der BOOLS_TO_ST08B-Block ist ein spezialisiertes, aber nützliches Werkzeug für die Konvertierung zwischen einzelnen BOOL-Signalen und strukturierten Byte-Datentypen. Seine einfache und direkte Funktionsweise macht ihn besonders geeignet für Anwendungen, bei denen Lesbarkeit und Klarheit im Vordergrund stehen.
