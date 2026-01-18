# F_STRING_AS_BYTE

```{index} single: F_STRING_AS_BYTE
```

<img width="1464" height="213" alt="F_STRING_AS_BYTE" src="https://github.com/user-attachments/assets/cf7a5899-d56c-4a37-b212-e79196ce79e9" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_STRING_AS_BYTE` dient der Konvertierung eines `STRING`-Wertes in einen `BYTE`-Wert. Diese Funktionalität ist besonders nützlich, wenn Zeichenketten in ihre entsprechenden Byte-Werte umgewandelt werden müssen, beispielsweise für die Verarbeitung in Protokollen oder bei der Kommunikation mit Hardware.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Dieser Ereigniseingang löst die Konvertierung aus. Er ist mit dem Dateneingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Dieses Ereignis wird nach erfolgreicher Konvertierung ausgelöst und ist mit dem Datenausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Eingabe vom Typ `STRING`, der in einen `BYTE`-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Ausgabe vom Typ `BYTE`, die das Ergebnis der Konvertierung enthält.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung des `STRING`-Wertes `IN` in einen `BYTE`-Wert `OUT` durch, sobald das Ereignis `REQ` empfangen wird. Die Konvertierung erfolgt mittels der Funktion `STRING_AS_BYTE`. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Der Funktionsblock ist ein einfacher Funktionsblock (`SimpleFB`) und verwendet einen ST-Algorithmus für die Konvertierung.
- Die Konvertierung erfolgt direkt und ohne zusätzliche Verzögerung.

## Zustandsübersicht
1. **Wartezustand**: Der Funktionsblock wartet auf das Ereignis `REQ`.
2. **Ausführungszustand**: Bei Empfang von `REQ` wird die Konvertierung durchgeführt.
3. **Bestätigungszustand**: Nach erfolgreicher Konvertierung wird `CNF` ausgelöst und der Funktionsblock kehrt in den Wartezustand zurück.

## Anwendungsszenarien
- Konvertierung von Zeichenketten in Byte-Werte für die Kommunikation mit seriellen Schnittstellen.
- Verarbeitung von ASCII-Zeichen in Byte-Form für Protokolle oder Hardware-Steuerungen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen wie `F_STRING_TO_INT` oder `F_STRING_TO_REAL` ist `F_STRING_AS_BYTE` speziell auf die Umwandlung in einen `BYTE`-Wert ausgelegt.
- Ein ähnlicher Baustein könnte `F_CHAR_AS_BYTE` sein, der jedoch einzelne Zeichen konvertiert, während `F_STRING_AS_BYTE` auf Zeichenketten arbeitet.

## Fazit
Der Funktionsblock `F_STRING_AS_BYTE` bietet eine einfache und effiziente Möglichkeit, Zeichenketten in Byte-Werte umzuwandeln. Durch seine klare Schnittstellenstruktur und direkte Funktionsweise eignet er sich ideal für Anwendungen, die eine solche Konvertierung erfordern.
