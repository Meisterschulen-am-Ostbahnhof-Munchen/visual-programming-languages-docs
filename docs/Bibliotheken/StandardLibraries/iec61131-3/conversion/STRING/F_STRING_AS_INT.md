# F_STRING_AS_INT

```{index} single: F_STRING_AS_INT
```

<img width="1451" height="213" alt="F_STRING_AS_INT" src="https://github.com/user-attachments/assets/ed2bb7a0-e638-438c-92d8-997cb313e3dd" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_STRING_AS_INT` dient der Konvertierung eines `STRING`-Wertes in einen `INT`-Wert. Diese Funktionalität ist besonders nützlich, wenn Zeichenketten, die numerische Werte repräsentieren, in ganzzahlige Werte umgewandelt werden müssen.

![F_STRING_AS_INT](F_STRING_AS_INT.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird dieser Ereigniseingang ausgelöst, wird der `STRING`-Wert am Daten-Eingang `IN` in einen `INT`-Wert umgewandelt.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert die erfolgreiche Beendigung der Konvertierung. Dieses Ereignis wird zusammen mit dem konvertierten `INT`-Wert am Daten-Ausgang `OUT` ausgegeben.

### **Daten-Eingänge**
- **IN**: Der `STRING`-Wert, der in einen `INT`-Wert umgewandelt werden soll.

### **Daten-Ausgänge**
- **OUT**: Der konvertierte `INT`-Wert.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das `REQ`-Ereignis empfangen wird. Dabei wird die eingebaute Funktion `STRING_AS_INT` verwendet, um den `STRING`-Wert am Eingang `IN` in einen `INT`-Wert umzuwandeln. Das Ergebnis wird am Ausgang `OUT` ausgegeben und durch das `CNF`-Ereignis bestätigt.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt und ohne zusätzliche Parameter.
- Der Funktionsblock ist einfach und effizient implementiert, ohne komplexe Zustandslogik.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Verarbeitung von Benutzereingaben, die als Zeichenketten vorliegen, aber als numerische Werte benötigt werden.
- Umwandlung von Daten aus Textdateien oder Kommunikationsprotokollen in numerische Werte.
- Integration in Systeme, die Zeichenketten-basierte Datenquellen nutzen, aber numerische Verarbeitung erfordern.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsbausteinen ist `F_STRING_AS_INT` spezialisiert auf die Umwandlung von `STRING` zu `INT`.
- Andere Bausteine könnten zusätzliche Funktionen wie Fehlerbehandlung oder Unterstützung für verschiedene numerische Formate bieten, was hier nicht der Fall ist.

## Fazit
Der `F_STRING_AS_INT`-Funktionsblock ist ein einfaches und effektives Werkzeug zur Konvertierung von Zeichenketten in ganzzahlige Werte. Seine Stärke liegt in der Einfachheit und direkten Anwendbarkeit, ohne zusätzliche Komplexität. Für Anwendungen, die eine schnelle und unkomplizierte Umwandlung benötigen, ist dieser Baustein ideal geeignet.