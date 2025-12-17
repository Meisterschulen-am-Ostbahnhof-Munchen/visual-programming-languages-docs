# F_DT_TO_TOD

<img width="1198" height="187" alt="F_DT_TO_TOD" src="https://github.com/user-attachments/assets/15e611cf-4581-41b1-a782-bf2f2d2920af" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_DT_TO_TOD` dient der Konvertierung eines Datums- und Zeitwerts (DT) in einen reinen Zeitwert (TOD - Time of Day). Diese Funktion ist besonders nützlich, wenn nur die Tageszeit aus einem kombinierten Datums- und Zeitstempel extrahiert werden soll.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird dieser Eingang ausgelöst, führt der Funktionsblock die Umwandlung durch.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert die erfolgreiche Beendigung der Konvertierung.

### **Daten-Eingänge**
- **IN**: Der Eingang vom Typ `DT`, der den zu konvertierenden Datums- und Zeitwert enthält.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang vom Typ `TOD`, der den konvertierten Zeitwert (ohne Datum) bereitstellt.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Auslösung des `REQ`-Ereignisses wird der Algorithmus ausgeführt, der den Eingabewert `IN` vom Typ `DT` in einen `TOD`-Wert umwandelt. Das Ergebnis wird am Ausgang `OUT` ausgegeben und das `CNF`-Ereignis signalisiert die erfolgreiche Beendigung der Operation.

## Technische Besonderheiten
- Der Funktionsblock ist als einfacher FB (SimpleFB) implementiert, was eine schnelle und effiziente Ausführung gewährleistet.
- Die Konvertierung erfolgt über die eingebaute Funktion `DT_TO_TOD`.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung wird bei jedem `REQ`-Ereignis neu durchgeführt.

## Anwendungsszenarien
- Extraktion der Tageszeit aus Zeitstempeln für Zeitsteuerungen.
- Vorverarbeitung von Daten für Systeme, die nur die Tageszeit benötigen.

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu `F_TOD_TO_DT` konvertiert dieser Baustein in die entgegengesetzte Richtung.
- Ähnliche Bausteine wie `F_DT_TO_DATE` oder `F_DT_TO_TIME` extrahieren andere Teile eines DT-Werts.

## Fazit
Der `F_DT_TO_TOD`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, die Tageszeit aus einem kombinierten Datums- und Zeitwert zu extrahieren. Seine klare Schnittstelle und einfache Funktionsweise machen ihn zu einem nützlichen Werkzeug in Steuerungsanwendungen.
