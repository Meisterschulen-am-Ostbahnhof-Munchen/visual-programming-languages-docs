# F_DWORD_TO_DINT

```{index} single: F_DWORD_TO_DINT
```

<img width="1248" height="184" alt="F_DWORD_TO_DINT" src="https://github.com/user-attachments/assets/118c3a3a-7bd4-4adb-a8e1-f927a4ca8bab" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_DWORD_TO_DINT` dient der Konvertierung eines `DWORD`-Wertes in einen `DINT`-Wert. Diese Konvertierung ist insbesondere dann notwendig, wenn Daten zwischen Systemen ausgetauscht werden, die unterschiedliche Datentypen verwenden. Der Block ist Teil des Pakets `iec61131::conversion` und folgt dem Standard 61499-1.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- **IN**: Der Eingang erwartet einen `DWORD`-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang liefert den konvertierten `DINT`-Wert.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `DWORD` zu `DINT` durch, sobald das Ereignis `REQ` empfangen wird. Die Konvertierung erfolgt mittels der Funktion `DWORD_TO_DINT(IN)`. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst und der konvertierte Wert über den Ausgang `OUT` ausgegeben.

## Technische Besonderheiten
- Der Block ist als einfacher Funktionsblock (`SimpleFB`) implementiert.
- Die Konvertierung erfolgt direkt und ohne zusätzliche Zustandsverwaltung.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine expliziten Zustände. Die Konvertierung wird bei jedem `REQ`-Ereignis durchgeführt.

## Anwendungsszenarien
- Konvertierung von `DWORD`-Daten, die von einem System geliefert werden, in `DINT`-Daten für ein anderes System.
- Verwendung in Steuerungssystemen, wo Datentypen harmonisiert werden müssen.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Blöcke könnten `F_WORD_TO_INT` oder `F_LWORD_TO_LINT` sein, die jedoch andere Datentypen konvertieren.
- Im Gegensatz zu komplexeren Konvertierungsblöcken bietet `F_DWORD_TO_DINT` eine direkte und einfache Lösung für die spezifische Konvertierung.

## Fazit
Der Funktionsblock `F_DWORD_TO_DINT` bietet eine effiziente und einfache Möglichkeit, `DWORD`-Werte in `DINT`-Werte zu konvertieren. Durch seine klare Schnittstelle und direkte Funktionsweise ist er ideal für Anwendungen, die eine schnelle und zuverlässige Typkonvertierung erfordern.