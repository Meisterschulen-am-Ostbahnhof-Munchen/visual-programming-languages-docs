# F_WSTRING_AS_LWORD

<img width="1491" height="214" alt="F_WSTRING_AS_LWORD" src="https://github.com/user-attachments/assets/70e780c5-b20e-4cf1-86f9-bc905ada9d1e" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_WSTRING_AS_LWORD` dient der Konvertierung eines WSTRING-Datentyps in einen LWORD-Datentyp. Diese Funktionalität ist insbesondere in Szenarien nützlich, in denen Zeichenketten in eine für die weitere Verarbeitung geeignete binäre Form umgewandelt werden müssen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Dieser Ereigniseingang löst die Konvertierung aus.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Dieses Ereignis wird nach erfolgreicher Konvertierung ausgegeben.

### **Daten-Eingänge**
- **IN**: Eingabe vom Typ WSTRING. Dies ist die Zeichenkette, die konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Ausgabe vom Typ LWORD. Dies ist das Ergebnis der Konvertierung.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von WSTRING zu LWORD durch, sobald das Ereignis `REQ` empfangen wird. Die Konvertierung erfolgt mittels der integrierten Funktion `WSTRING_AS_LWORD`. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgegeben, zusammen mit dem konvertierten Wert.

## Technische Besonderheiten
- Der Funktionsblock ist ein einfacher FB (SimpleFB) und verwendet einen ST-Algorithmus für die Konvertierung.
- Die Konvertierung erfolgt direkt und ohne weitere Verzögerung.

## Zustandsübersicht
1. **Idle**: Wartet auf das Ereignis `REQ`.
2. **Processing**: Führt die Konvertierung durch.
3. **Completed**: Gibt das Ereignis `CNF` aus und kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- Konvertierung von Zeichenketten in binäre Daten für die weitere Verarbeitung in Steuerungssystemen.
- Verwendung in Protokollumsetzungen, wo Zeichenketten in eine binäre Form gebracht werden müssen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen wie `F_STRING_AS_LWORD` arbeitet dieser FB spezifisch mit dem WSTRING-Datentyp, der Unicode-Zeichen unterstützt.

## Fazit
Der `F_WSTRING_AS_LWORD` Funktionsblock bietet eine einfache und effiziente Möglichkeit, WSTRING-Daten in LWORD-Daten umzuwandeln. Seine klare Schnittstellenstruktur und direkte Funktionsweise machen ihn zu einem nützlichen Werkzeug in verschiedenen Anwendungsfällen.
