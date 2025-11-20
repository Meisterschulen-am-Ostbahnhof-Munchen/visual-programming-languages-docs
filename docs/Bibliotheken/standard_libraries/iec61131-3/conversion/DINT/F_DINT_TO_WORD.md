# F_DINT_TO_WORD

<img width="1438" height="211" alt="F_DINT_TO_WORD" src="https://github.com/user-attachments/assets/0eae21ae-dfc1-44bc-a956-609f3c8000a1" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_DINT_TO_WORD` dient der Konvertierung eines 32-Bit Ganzzahlwertes (DINT) in einen 16-Bit Wortwert (WORD). Diese Konvertierung ist besonders nützlich, wenn Daten zwischen Systemen mit unterschiedlicher Wortbreite ausgetauscht werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird dieser Eingang ausgelöst, wird der Wert am Daten-Eingang `IN` gelesen und konvertiert.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert die erfolgreiche Beendigung der Konvertierung. Der konvertierte Wert steht am Daten-Ausgang `OUT` zur Verfügung.

### **Daten-Eingänge**
- **IN**: Der zu konvertierende 32-Bit Ganzzahlwert (DINT).

### **Daten-Ausgänge**
- **OUT**: Der konvertierte 16-Bit Wortwert (WORD).

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Bei Auslösung des Ereigniseingangs `REQ` wird der Algorithmus ausgeführt, der den Wert von `IN` von DINT in WORD konvertiert und das Ergebnis an `OUT` ausgibt. Anschließend wird das Ereignis `CNF` ausgelöst, um den Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung schneidet die oberen 16 Bit des DINT-Wertes ab, da ein WORD nur 16 Bit speichern kann. Es ist daher wichtig sicherzustellen, dass der ursprüngliche DINT-Wert innerhalb des darstellbaren Bereichs eines WORD liegt (0 bis 65535), um Datenverlust zu vermeiden.
- Der Funktionsblock ist deterministisch und hat keine internen Zustände.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock ohne interne Zustände handelt, gibt es keine Zustandsübergänge. Der Block führt die Konvertierung bei jedem `REQ`-Ereignis aus und signalisiert den Abschluss mit `CNF`.

## Anwendungsszenarien
- Kommunikation zwischen Systemen, die unterschiedliche Wortbreiten verwenden.
- Anpassung von Daten für Peripheriegeräte, die nur WORD-Daten verarbeiten können.
- Einsatz in Steuerungssystemen, wo Speicherplatz optimiert werden muss.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsblöcken wie `F_ANY_TO_ANY` ist `F_DINT_TO_WORD` spezialisiert und daher effizienter, wenn genau diese Konvertierung benötigt wird.
- Ähnliche Blöcke wie `F_INT_TO_WORD` arbeiten mit kleineren Ganzzahltypen, während `F_DINT_TO_WORD` mit dem größeren DINT-Typ umgeht.

## Fazit
Der `F_DINT_TO_WORD` Funktionsblock ist ein spezialisiertes und effizientes Werkzeug für die Konvertierung von 32-Bit Ganzzahlen in 16-Bit Wörter. Seine Einfachheit und Determinismus machen ihn zu einer verlässlichen Komponente in Steuerungsanwendungen, insbesondere bei der Datenanpassung zwischen unterschiedlichen Systemen.
