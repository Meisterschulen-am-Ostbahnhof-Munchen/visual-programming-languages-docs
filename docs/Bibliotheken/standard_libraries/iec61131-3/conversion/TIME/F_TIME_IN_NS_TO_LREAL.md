# F_TIME_IN_NS_TO_LREAL

<img width="1538" height="212" alt="F_TIME_IN_NS_TO_LREAL" src="https://github.com/user-attachments/assets/c94f3148-26d5-44a8-88fc-e5eeb5938a75" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_TIME_IN_NS_TO_LREAL` dient zur Konvertierung eines Zeitwertes in Nanosekunden (`TIME`) in einen Fließkommawert (`LREAL`). Diese Umwandlung ist insbesondere in Steuerungsanwendungen nützlich, wo Zeitwerte in mathematischen Berechnungen verwendet werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung des Funktionsblocks. Der Eingang ist mit dem Dateneingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Datenausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingang erwartet einen Zeitwert in Nanosekunden (`TIME`).

### **Daten-Ausgänge**
- **OUT**: Gibt den konvertierten Fließkommawert (`LREAL`) zurück.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung des Zeitwertes `IN` von Nanosekunden (`TIME`) in einen Fließkommawert (`LREAL`) durch. Die Umwandlung erfolgt bei jedem Auftreten des Ereignisses `REQ`. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst, und der Ergebniswert steht am Ausgang `OUT` zur Verfügung.

## Technische Besonderheiten
- Der Funktionsblock ist als einfacher FB (`SimpleFB`) implementiert.
- Die Konvertierung erfolgt mithilfe der eingebauten Funktion `TIME_IN_NS_TO_LREAL`.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Ausführung erfolgt unmittelbar bei Auftreten des `REQ`-Ereignisses.

## Anwendungsszenarien
- Zeitmessungen in Steuerungssystemen, die eine weitere Verarbeitung in mathematischen Ausdrücken erfordern.
- Integration in Regelkreise, wo Zeitwerte als Fließkommazahlen benötigt werden.

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu generischen Konvertierungsblöcken ist `F_TIME_IN_NS_TO_LREAL` speziell auf die Umwandlung von Zeitwerten in Nanosekunden zu Fließkommazahlen optimiert.
- Andere Blöcke wie `F_TIME_TO_LREAL` könnten eine ähnliche Funktionalität bieten, jedoch ohne die explizite Angabe der Nanosekunden-Einheit.

## Fazit
Der Funktionsblock `F_TIME_IN_NS_TO_LREAL` bietet eine effiziente und spezialisierte Lösung für die Konvertierung von Zeitwerten in Fließkommazahlen. Seine einfache Handhabung und direkte Integration machen ihn ideal für Anwendungen, die präzise Zeitverarbeitung erfordern.
