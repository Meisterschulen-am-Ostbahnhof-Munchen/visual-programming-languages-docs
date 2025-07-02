# LinksRechts

* * * * * * * * * *
## Einleitung
Der Funktionsblock `LinksRechts` ist ein grundlegender Baustein zur Steuerung von Rechts- und Linkslauf mit Pausenfunktion. Er ermöglicht die Priorisierung des Rechtslaufs gegenüber dem Linkslauf und bietet Zustandsüberwachung durch Ausgabe des aktuellen Zustands.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `EI_ON`: Einschalten des Systems (mit Datenzuweisung `EIN`)
- `EI_Rechts`: Aktiviert Nur-Rechtslauf (mit Datenzuweisung `DI_Rechts`)
- `EI_Links`: Aktiviert Nur-Linkslauf (mit Datenzuweisung `DI_Links`)

### **Ereignis-Ausgänge**
- `EO`: Generisches Ausgangsereignis (mit Datenzuweisungen `Rechts`, `Links` und `STATE`)

### **Daten-Eingänge**
- `EIN` (BOOL): Einschaltsignal
- `DI_Rechts` (BOOL): Nur-Rechtslauf-Befehl
- `DI_Links` (BOOL): Nur-Linkslauf-Befehl

### **Daten-Ausgänge**
- `Rechts` (BOOL): Rechtslauf aktiv
- `Links` (BOOL): Linkslauf aktiv
- `STATE` (STRING): Aktueller Zustand als Zeichenkette

## Funktionsweise
Der FB implementiert eine Zustandsmaschine mit folgenden Hauptzuständen:
1. **Rechtslauf**: Aktiver Rechtslauf (Rechts=TRUE, Links=FALSE)
2. **Linkslauf**: Aktiver Linkslauf (Rechts=FALSE, Links=TRUE)
3. **Pausenzustände**: Jeweils für Rechts- und Linkslauf

Die Zustandsübergänge erfolgen basierend auf den Eingangsereignissen und den aktuellen Datenwerten. Rechtslauf hat Priorität vor Linkslauf.

## Technische Besonderheiten
- Verwendet einen String-Ausgang (`STATE`) zur Zustandsrückmeldung
- Implementiert Pausenzustände für beide Laufrichtungen
- Priorisierung: Rechtslauf > Linkslauf

## Zustandsübersicht
1. **START**: Initialzustand
2. **Rechtslauf**: Aktiver Rechtslauf
3. **Rechtslauf_Pause**: Pausenzustand nach Rechtslauf
4. **Linkslauf**: Aktiver Linkslauf
5. **Linkslauf_Pause**: Pausenzustand nach Linkslauf

## Anwendungsszenarien
- Steuerung von Förderbändern mit wechselnder Laufrichtung
- Antriebssteuerungen mit Rechts-/Linkslauf
- Systeme mit priorisierten Betriebsmodi

## Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu einfachen Rechts/Links-Steuerungen bietet dieser FB:
- Integrierte Pausenzustände
- Zustandsrückmeldung
- Klare Priorisierung der Laufrichtungen

## Fazit
Der `LinksRechts`-FB ist ein robustes Steuerungselement für Systeme mit wechselnder Laufrichtung und Pausenfunktion. Die klare Zustandsstruktur und Priorisierung machen ihn besonders geeignet für Anwendungen mit sicherheitsrelevanten Aspekten.