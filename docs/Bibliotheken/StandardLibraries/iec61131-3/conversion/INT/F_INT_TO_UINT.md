# F_INT_TO_UINT

```{index} single: F_INT_TO_UINT
```

<img width="1218" height="183" alt="F_INT_TO_UINT" src="https://github.com/user-attachments/assets/ab9715b9-eb59-48da-9f6d-c159088ae19c" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_INT_TO_UINT` dient der Konvertierung eines vorzeichenbehafteten Integer-Werts (`INT`) in einen vorzeichenlosen Integer-Wert (`UINT`). Diese Konvertierung ist nützlich, wenn Daten zwischen Systemen ausgetauscht werden, die unterschiedliche Datentypen verwenden, oder wenn eine vorzeichenlose Verarbeitung erforderlich ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- **IN** (`INT`): Der vorzeichenbehaftete Integer-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (`UINT`): Der resultierende vorzeichenlose Integer-Wert nach der Konvertierung.

### **Adapter**
Es werden keine Adapter verwendet.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `INT` zu `UINT` durch, wenn das Ereignis `REQ` ausgelöst wird. Die Konvertierung erfolgt mittels der Funktion `INT_TO_UINT(IN)`. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst, und der konvertierte Wert steht am Ausgang `OUT` zur Verfügung.

## Technische Besonderheiten
- Die Konvertierung erfolgt ohne zusätzliche Parameter oder Konfiguration.
- Der Block ist als einfacher Funktionsblock (`SimpleFB`) implementiert und verwendet einen ST-Algorithmus für die Konvertierung.

## Zustandsübersicht
1. **Idle-Zustand**: Wartet auf das `REQ`-Ereignis.
2. **Konvertierungszustand**: Führt die Konvertierung durch und setzt den Ausgang `OUT`.
3. **Bestätigungszustand**: Löst das `CNF`-Ereignis aus und kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- **Datenverarbeitung**: Konvertierung von Sensorwerten oder Steuerungsdaten, die als `INT` vorliegen, für Systeme, die `UINT` erwarten.
- **Kommunikation**: Vorbereitung von Daten für die Übertragung zwischen Systemen mit unterschiedlichen Datentypanforderungen.

## Vergleich mit ähnlichen Bausteinen
- **F_UINT_TO_INT**: Führt die umgekehrte Konvertierung von `UINT` zu `INT` durch.
- **Generische Konvertierungsblöcke**: Bieten möglicherweise mehr Flexibilität, sind aber auch komplexer in der Handhabung.

## Fazit
Der `F_INT_TO_UINT`-Funktionsblock ist ein einfaches und effizientes Werkzeug für die Konvertierung von vorzeichenbehafteten zu vorzeichenlosen Integer-Werten. Seine klare Schnittstelle und einfache Funktionsweise machen ihn ideal für Anwendungen, bei denen eine schnelle und zuverlässige Typumwandlung erforderlich ist.