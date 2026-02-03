# F_BYTE_AS_STRING

```{index} single: F_BYTE_AS_STRING
```

<img width="1257" height="183" alt="F_BYTE_AS_STRING" src="https://github.com/user-attachments/assets/8c04d5bd-c228-49a9-a534-2d29765aedb1" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_BYTE_AS_STRING` dient der Konvertierung eines BYTE-Wertes in einen STRING. Diese Funktionalität ist besonders nützlich, wenn numerische Daten in eine für die Anzeige oder Protokollierung geeignete Textform umgewandelt werden müssen.

![F_BYTE_AS_STRING](F_BYTE_AS_STRING.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Löst die Konvertierung aus.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Wird nach erfolgreicher Konvertierung ausgelöst.

### **Daten-Eingänge**
- **IN**: BYTE-Wert, der in einen STRING konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Ergebnis der Konvertierung als STRING.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Auslösung des REQ-Ereignisses wird der eingehende BYTE-Wert (IN) in einen STRING konvertiert und über den Ausgang OUT ausgegeben. Gleichzeitig wird das CNF-Ereignis ausgelöst, um die erfolgreiche Ausführung zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung erfolgt mittels der Funktion `BYTE_AS_STRING`.
- Der Funktionsblock ist einfach und hat keine internen Zustände oder komplexe Logik.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine Zustandsübergänge oder -maschinen.

## Anwendungsszenarien
- Konvertierung von Sensorwerten für die Anzeige auf einem HMI.
- Vorbereitung von Daten für die Protokollierung oder Kommunikation mit anderen Systemen, die String-Daten erwarten.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen wie `F_WORD_AS_STRING` oder `F_DWORD_AS_STRING` ist dieser speziell für BYTE-Werte optimiert.
- Einfacher und spezialisierter als generische Konvertierungsbausteine.

## Fazit
Der `F_BYTE_AS_STRING` Funktionsblock bietet eine einfache und effiziente Möglichkeit, BYTE-Werte in Strings umzuwandeln. Seine Einfachheit macht ihn zuverlässig und leicht in verschiedene Anwendungen integrierbar.