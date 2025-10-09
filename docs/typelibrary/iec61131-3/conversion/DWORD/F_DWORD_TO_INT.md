# F_DWORD_TO_INT

<img width="1233" height="184" alt="F_DWORD_TO_INT" src="https://github.com/user-attachments/assets/06ada230-9c73-4717-8b06-0aee3362b757" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_DWORD_TO_INT` dient der Konvertierung eines DWORD-Wertes in einen INT-Wert. Er ist Teil des Pakets `iec61131::conversion` und ermöglicht die einfache Umwandlung zwischen diesen beiden Datentypen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung der Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingang vom Typ `DWORD`, der den zu konvertierenden Wert enthält.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang vom Typ `INT`, der das Ergebnis der Konvertierung liefert.

### **Adapter**
Der Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Bei Empfang eines Ereignisses am Eingang `REQ` wird der Algorithmus ausgeführt, der den Wert von `IN` vom Typ `DWORD` in einen Wert vom Typ `INT` konvertiert. Das Ergebnis wird am Ausgang `OUT` ausgegeben und durch das Ereignis `CNF` bestätigt.

## Technische Besonderheiten
- Der Funktionsblock verwendet die Standardfunktion `DWORD_TO_INT` für die Konvertierung.
- Es handelt sich um einen einfachen Funktionsblock ohne interne Zustände oder komplexe Logik.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Konvertierung von DWORD-Werten, die von Hardware oder anderen Systemen geliefert werden, in INT-Werte für die weitere Verarbeitung.
- Integration in Steuerungssysteme, die unterschiedliche Datentypen verarbeiten müssen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen wie `F_WORD_TO_INT` oder `F_BYTE_TO_INT` ist dieser Funktionsblock speziell für die Konvertierung von DWORD zu INT optimiert.
- Er bietet eine einfache und direkte Lösung ohne zusätzliche Funktionen oder Parameter.

## Fazit
Der `F_DWORD_TO_INT` Funktionsblock ist ein nützliches Werkzeug für die Konvertierung zwischen DWORD- und INT-Datentypen. Seine Einfachheit und direkte Funktionsweise machen ihn zu einer zuverlässigen Lösung in verschiedenen Anwendungsfällen.
