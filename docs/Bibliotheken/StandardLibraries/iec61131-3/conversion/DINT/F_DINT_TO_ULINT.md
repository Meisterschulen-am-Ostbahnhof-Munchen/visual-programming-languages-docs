# F_DINT_TO_ULINT

```{index} single: F_DINT_TO_ULINT
```

<img width="1451" height="217" alt="F_DINT_TO_ULINT" src="https://github.com/user-attachments/assets/00d56131-c3f4-44e3-b204-7fb2373bc4e8" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_DINT_TO_ULINT` dient der Konvertierung eines 32-Bit vorzeichenbehafteten Integer-Werts (`DINT`) in einen 64-Bit vorzeichenlosen Integer-Wert (`ULINT`). Dieser Baustein ist besonders nützlich, wenn Daten zwischen Systemen mit unterschiedlichen Datentypen ausgetauscht werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Bei Aktivierung dieses Ereignisses wird der Wert am Daten-Eingang `IN` gelesen und konvertiert.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieses Ereignis wird zusammen mit dem konvertierten Wert am Daten-Ausgang `OUT` ausgegeben.

### **Daten-Eingänge**
- **IN** (`DINT`): Der vorzeichenbehaftete 32-Bit Integer-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (`ULINT`): Der vorzeichenlose 64-Bit Integer-Wert, der das Ergebnis der Konvertierung enthält.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `DINT` zu `ULINT` durch, sobald das Ereignis `REQ` empfangen wird. Der Algorithmus `REQ` wird ausgeführt, wobei der Wert von `IN` mittels der Funktion `DINT_TO_ULINT` konvertiert und an `OUT` ausgegeben wird. Anschließend wird das Ereignis `CNF` ausgelöst, um den erfolgreichen Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- Der Baustein unterstützt die direkte Konvertierung ohne zusätzliche Parameter.
- Die Konvertierung erfolgt ohne Datenverlust, da der `ULINT`-Typ einen größeren Wertebereich als `DINT` abdeckt.

## Zustandsübersicht
1. **Idle-Zustand**: Wartet auf das `REQ`-Ereignis.
2. **Konvertierungszustand**: Führt die Konvertierung durch und setzt den Ausgang `OUT`.
3. **Bestätigungszustand**: Löst das `CNF`-Ereignis aus und kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- Datenkonvertierung in Steuerungssystemen, die unterschiedliche Datentypen verwenden.
- Integration von Komponenten, die vorzeichenlose 64-Bit Werte erfordern.
- Erweiterung der Kompatibilität zwischen verschiedenen Systemen.

## Vergleich mit ähnlichen Bausteinen
- **F_INT_TO_ULINT**: Konvertiert einen kleineren vorzeichenbehafteten Integer (`INT`) zu `ULINT`.
- **F_LINT_TO_ULINT**: Konvertiert einen 64-Bit vorzeichenbehafteten Integer (`LINT`) zu `ULINT`.
- **F_DINT_TO_LINT**: Konvertiert `DINT` zu einem vorzeichenbehafteten 64-Bit Integer (`LINT`).

## Fazit
Der `F_DINT_TO_ULINT`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, vorzeichenbehaftete 32-Bit Integer-Werte in vorzeichenlose 64-Bit Integer-Werte umzuwandeln. Durch seine klare Schnittstelle und zuverlässige Funktionsweise eignet er sich ideal für Anwendungen, die eine sichere und verlustfreie Datentypkonvertierung erfordern.