# F_STRING_AS_LINT

<img width="1463" height="213" alt="F_STRING_AS_LINT" src="https://github.com/user-attachments/assets/e550d809-5da9-4c01-b2c4-0041510891ef" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_STRING_AS_LINT` dient der Konvertierung eines `STRING`-Wertes in einen `LINT`-Wert. Diese Funktionalität ist insbesondere dann nützlich, wenn Zeichenketten in numerische Werte umgewandelt werden müssen, um sie in weiteren Berechnungen oder Steuerungslogiken zu verwenden.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung des `STRING`-Wertes zu einem `LINT`-Wert. Dieser Ereigniseingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ereignisausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingang für den `STRING`-Wert, der in einen `LINT`-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang für den konvertierten `LINT`-Wert.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung des `STRING`-Wertes zu einem `LINT`-Wert durch, sobald das `REQ`-Ereignis ausgelöst wird. Die Konvertierung erfolgt mithilfe der Funktion `STRING_AS_LINT()`. Nach erfolgreicher Konvertierung wird das `CNF`-Ereignis ausgelöst, und der konvertierte Wert steht am `OUT`-Ausgang zur Verfügung.

## Technische Besonderheiten
- Der Funktionsblock ist ein einfacher Funktionsblock (SimpleFB) und führt die Konvertierung in einem einzigen Algorithmus durch.
- Die Konvertierung erfolgt direkt und ohne zusätzliche Zustandsverwaltung.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine komplexen Zustandsübergänge. Der Block führt die Konvertierung bei jedem `REQ`-Ereignis aus und signalisiert den Abschluss mit dem `CNF`-Ereignis.

## Anwendungsszenarien
- Konvertierung von Benutzereingaben in numerische Werte.
- Verarbeitung von Zeichenketten, die numerische Daten enthalten, in Steuerungssystemen.
- Integration in größere Steuerungslogiken, die numerische Berechnungen erfordern.

## Vergleich mit ähnlichen Bausteinen
- **F_STRING_AS_INT**: Konvertiert einen `STRING` in einen `INT`-Wert, ist jedoch auf kleinere Zahlenbereiche beschränkt.
- **F_STRING_AS_REAL**: Konvertiert einen `STRING` in einen `REAL`-Wert, ist für Gleitkommazahlen geeignet.
- **F_LINT_AS_STRING**: Führt die umgekehrte Konvertierung durch, also von `LINT` zu `STRING`.

## Fazit
Der Funktionsblock `F_STRING_AS_LINT` bietet eine einfache und effiziente Möglichkeit, Zeichenketten in große numerische Werte (`LINT`) umzuwandeln. Durch seine direkte Funktionsweise und klare Schnittstellenstruktur ist er ideal für den Einsatz in Steuerungssystemen, die eine solche Konvertierung erfordern.
