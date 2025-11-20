# F_BYTE_TO_DWORD

<img width="1243" height="183" alt="F_BYTE_TO_DWORD" src="https://github.com/user-attachments/assets/12ed4687-4afb-4a1c-8e33-7b03054d593d" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_BYTE_TO_DWORD` dient der Konvertierung eines `BYTE`-Wertes in einen `DWORD`-Wert. Dieser Baustein ist besonders nützlich in Szenarien, bei denen eine Erweiterung der Datenbreite erforderlich ist, beispielsweise bei der Verarbeitung von Sensordaten oder der Kommunikation zwischen Systemen mit unterschiedlichen Datenformaten.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Dieser Eingang ist mit dem Daten-Eingang `IN` gekoppelt.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ausgang ist mit dem Daten-Ausgang `OUT` gekoppelt.

### **Daten-Eingänge**
- **IN**: Der Eingangswert vom Typ `BYTE`, der in einen `DWORD`-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgangswert vom Typ `DWORD`, der das Ergebnis der Konvertierung enthält.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Auslösung des Ereigniseingangs `REQ` wird der Algorithmus ausgeführt, der den `BYTE`-Wert am Eingang `IN` in einen `DWORD`-Wert konvertiert und das Ergebnis am Ausgang `OUT` ausgibt. Anschließend wird das Ereignis `CNF` ausgelöst, um den erfolgreichen Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- Der Funktionsblock ist einfach und effizient, da er direkt die eingebaute Funktion `BYTE_TO_DWORD` nutzt.
- Keine zusätzlichen Zustände oder komplexe Logik erforderlich.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine Zustandsübergänge oder interne Zustände. Die Operation wird atomar bei Auslösung von `REQ` durchgeführt.

## Anwendungsszenarien
- Erweiterung von Datenbreiten in Kommunikationsprotokollen.
- Verarbeitung von Sensordaten, die als `BYTE` vorliegen, aber in `DWORD` weiterverarbeitet werden müssen.
- Kompatibilitätsanpassungen zwischen verschiedenen Systemkomponenten.

## Vergleich mit ähnlichen Bausteinen
- **F_WORD_TO_DWORD**: Konvertiert `WORD` zu `DWORD`, ähnlich in der Funktionsweise, aber mit einer anderen Eingangsdatengröße.
- **F_BYTE_TO_WORD**: Konvertiert `BYTE` zu `WORD`, bietet eine geringere Ausgangsdatengröße im Vergleich zu `F_BYTE_TO_DWORD`.

## Fazit
Der `F_BYTE_TO_DWORD` Funktionsblock ist ein einfaches und effizientes Werkzeug zur Konvertierung von `BYTE`- zu `DWORD`-Werten. Seine klare Schnittstelle und direkte Funktionsweise machen ihn ideal für Anwendungen, bei denen eine Datenbreitenerweiterung benötigt wird.
