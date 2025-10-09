# F_REAL_AS_STRING

<img width="1256" height="180" alt="F_REAL_AS_STRING" src="https://github.com/user-attachments/assets/7ac6c577-f078-4c20-a63e-216db88cf2e7" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_REAL_AS_STRING` dient der Konvertierung eines REAL-Wertes in einen STRING-Wert. Er ist Teil des Pakets `iec61131::conversion` und ermöglicht die einfache Umwandlung von numerischen Werten in eine Zeichenkette.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung des REAL-Wertes in einen STRING. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der REAL-Wert, der in einen STRING konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der konvertierte STRING-Wert des Eingangs `IN`.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Bei einem anliegenden Ereignis am Eingang `REQ` wird der Algorithmus ausgeführt, der den REAL-Wert von `IN` in einen STRING konvertiert und das Ergebnis an `OUT` ausgibt. Anschließend wird das Ereignis `CNF` ausgelöst, um den erfolgreichen Abschluss der Konvertierung zu signalisieren.

## Technische Besonderheiten
- Der Funktionsblock verwendet die Funktion `REAL_AS_STRING` zur Konvertierung.
- Es handelt sich um einen einfachen Funktionsblock ohne Zustandsautomat.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine Zustandsübergänge. Die Konvertierung erfolgt direkt bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Konvertierung von Sensorwerten für die Anzeige auf einem HMI.
- Umwandlung von numerischen Werten für die Protokollierung in Textdateien.
- Integration in Systeme, die String-basierte Kommunikation erfordern.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen wie `F_INT_AS_STRING` oder `F_BOOL_AS_STRING` ist dieser speziell für REAL-Werte ausgelegt.
- Einfacher und direkter als universelle Konvertierungsbausteine, die möglicherweise zusätzliche Parameter benötigen.

## Fazit
Der `F_REAL_AS_STRING` Funktionsblock bietet eine effiziente und unkomplizierte Möglichkeit, REAL-Werte in STRINGs umzuwandeln. Seine einfache Schnittstelle und direkte Funktionsweise machen ihn ideal für Anwendungen, bei denen numerische Werte als Zeichenketten verarbeitet werden müssen.
