# F_SINT_AS_STRING

<img width="1464" height="213" alt="F_SINT_AS_STRING" src="https://github.com/user-attachments/assets/8f81385a-a997-414c-938e-4a08f519242c" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_SINT_AS_STRING` dient der Konvertierung eines `SINT`-Wertes (8-Bit Ganzzahl) in einen `STRING` (Zeichenkette). Dieser Baustein ist besonders nützlich, wenn numerische Werte für die Anzeige oder Weiterverarbeitung als Text benötigt werden.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der zu konvertierende `SINT`-Wert (8-Bit Ganzzahl).

### **Daten-Ausgänge**
- **OUT**: Der konvertierte `STRING`-Wert.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das `REQ`-Ereignis eintrifft. Der `SINT`-Wert am Eingang `IN` wird in einen `STRING` umgewandelt und am Ausgang `OUT` ausgegeben. Die Konvertierung erfolgt mittels der Funktion `SINT_AS_STRING`. Nach Abschluss der Konvertierung wird das `CNF`-Ereignis ausgelöst.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt und ohne zusätzliche Parameter.
- Der Funktionsblock ist einfach und effizient, da er nur eine grundlegende Datentypumwandlung durchführt.

## Zustandsübersicht
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Konvertierung**: Führt die Umwandlung durch und gibt das Ergebnis aus.
3. **Bestätigung**: Löst das `CNF`-Ereignis aus und kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- Anzeige von numerischen Werten in Benutzeroberflächen.
- Protokollierung von numerischen Daten als Text.
- Vorbereitung von Daten für die Kommunikation über textbasierte Protokolle.

## Vergleich mit ähnlichen Bausteinen
- **F_INT_AS_STRING**: Konvertiert einen `INT`-Wert (16-Bit) in einen `STRING`.
- **F_DINT_AS_STRING**: Konvertiert einen `DINT`-Wert (32-Bit) in einen `STRING`.
- **F_LINT_AS_STRING**: Konvertiert einen `LINT`-Wert (64-Bit) in einen `STRING`.

Im Vergleich zu diesen Bausteinen ist `F_SINT_AS_STRING` spezialisiert auf die Konvertierung von 8-Bit Ganzzahlen.

## Fazit
Der `F_SINT_AS_STRING`-Funktionsblock ist ein einfaches und effizientes Werkzeug zur Konvertierung von `SINT`-Werten in `STRING`s. Seine klare Schnittstelle und direkte Funktionsweise machen ihn ideal für Anwendungen, bei denen kleine Ganzzahlen als Text dargestellt werden müssen.
