# F_WORD_TO_DWORD

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_WORD_TO_DWORD` dient der Konvertierung eines `WORD`-Wertes in einen `DWORD`-Wert. Er ist Teil des Pakets `iec61131::conversion` und ermöglicht eine einfache und effiziente Typumwandlung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung des Funktionsblocks. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingang vom Typ `WORD`, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang vom Typ `DWORD`, der das Ergebnis der Konvertierung enthält.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `WORD` zu `DWORD` durch, sobald das Ereignis `REQ` empfangen wird. Die Konvertierung erfolgt mittels der Funktion `WORD_TO_DWORD(IN)`. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Der Funktionsblock ist ein einfacher Funktionsblock (`SimpleFB`) und verwendet einen ST-Algorithmus für die Konvertierung.
- Die Konvertierung erfolgt direkt und ohne zusätzliche Verarbeitungsschritte.

## Zustandsübersicht
1. **Idle**: Wartet auf das Ereignis `REQ`.
2. **Processing**: Führt die Konvertierung durch.
3. **Completed**: Sendet das Ereignis `CNF` und kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo `WORD`-Werte in `DWORD`-Werte umgewandelt werden müssen.
- Integration in größere Steuerungssysteme, die eine Typkompatibilität erfordern.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen bietet `F_WORD_TO_DWORD` eine spezialisierte Funktionalität für die Umwandlung von `WORD` zu `DWORD` ohne zusätzliche Features oder Komplexität.

## Fazit
Der `F_WORD_TO_DWORD` Funktionsblock ist ein einfaches und effizientes Werkzeug für die Typumwandlung in IEC 61131-3-basierten Steuerungssystemen. Seine klare Schnittstellenstruktur und direkte Funktionsweise machen ihn zu einer zuverlässigen Lösung für Konvertierungsaufgaben.