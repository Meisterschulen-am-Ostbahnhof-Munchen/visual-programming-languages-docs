# AND_10

* * * * * * * * * *
## Einleitung
Der `AND_10` Funktionsblock ist ein generischer Baustein zur Berechnung einer bitweisen logischen UND-Verknüpfung. Er unterstützt bis zu 10 Eingangsvariablen und ist gemäß der IEC 61131-3 Norm klassifiziert. Der FB ist Teil des `iec61131::bitwiseOperators` Pakets und eignet sich für Anwendungen, die logische Operationen auf Bit-Ebene erfordern.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung des Funktionsblocks. Wird mit allen Eingängen (`IN1` bis `IN10`) verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Berechnung. Wird mit dem Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN1** bis **IN10** (`ANY_BIT`): Bis zu 10 Eingangsvariablen für die bitweise UND-Verknüpfung. Jeder Eingang kann einen beliebigen Bit-Datentyp (z.B. BOOL, BYTE, WORD, DWORD) annehmen.

### **Daten-Ausgänge**
- **OUT** (`ANY_BIT`): Ergebnis der bitweisen UND-Verknüpfung aller Eingänge. Der Datentyp entspricht dem der Eingänge.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der `AND_10` FB führt eine bitweise logische UND-Operation auf den Werten aller aktiven Eingänge (`IN1` bis `IN10`) aus. Das Ergebnis wird am Ausgang `OUT` ausgegeben, sobald das `REQ`-Ereignis empfangen wird. Die Berechnung wird durch das `CNF`-Ereignis bestätigt.

## Technische Besonderheiten
- **Generische Implementierung**: Der FB nutzt die generische Klasse `GEN_AND`, was eine flexible Verwendung mit verschiedenen Bit-Datentypen ermöglicht.
- **Skalierbarkeit**: Unterstützt bis zu 10 Eingänge, was komplexere logische Verknüpfungen ermöglicht.

## Zustandsübersicht
1. **Idle-Zustand**: Wartet auf das `REQ`-Ereignis.
2. **Berechnungszustand**: Führt die UND-Verknüpfung aus, sobald `REQ` aktiviert wird.
3. **Ausgabezustand**: Gibt das Ergebnis über `OUT` aus und signalisiert den Abschluss mit `CNF`.

## Anwendungsszenarien
- Logische Filterung von Signalgruppen.
- Bitweise Maskierung von Datenwerten.
- Steuerungslogik in industriellen Automatisierungssystemen.

## Vergleich mit ähnlichen Bausteinen
- **Standard-AND-FB**: Unterstützt typischerweise nur 2 Eingänge. `AND_10` bietet mehr Flexibilität durch 10 Eingänge.
- **Generic Logic Blocks**: Ähnlich generische Blöcke könnten weniger Eingänge oder spezifischere Datentypen unterstützen.

## Fazit
Der `AND_10` Funktionsblock ist ein vielseitiges Werkzeug für bitweise logische Operationen in IEC 61131-3-basierten Steuerungssystemen. Seine generische Natur und die Unterstützung für bis zu 10 Eingänge machen ihn besonders nützlich für komplexe Verknüpfungsaufgaben.