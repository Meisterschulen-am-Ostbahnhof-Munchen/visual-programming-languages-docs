# DWORD2DWORD

<img width="1197" height="182" alt="DWORD2DWORD" src="https://github.com/user-attachments/assets/454cadb1-37c4-40f8-bdcf-a4f1b96a6d87" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `DWORD2DWORD` dient zur direkten Übertragung eines DWORD-Wertes vom Eingang zum Ausgang. Es handelt sich um einen einfachen Konvertierungsbaustein, der hauptsächlich zur Signalweiterleitung oder zur expliziten Typkonvertierung eingesetzt werden kann.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ` (Normal Execution Request): Löst die Ausführung des Funktionsblocks aus. Der Eingang ist mit der Datenvariable `IN` verknüpft.

### **Ereignis-Ausgänge**
- `CNF` (Execution Confirmation): Signalisiert die erfolgreiche Ausführung des Funktionsblocks. Der Ausgang ist mit der Datenvariable `OUT` verknüpft.

### **Daten-Eingänge**
- `IN` (DWORD): Der Eingangswert, der weitergeleitet werden soll.

### **Daten-Ausgänge**
- `OUT` (DWORD): Der Ausgangswert, der dem Eingangswert entspricht.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock kopiert bei Auslösung durch das `REQ`-Ereignis den Wert des Daten-Eingangs `IN` direkt auf den Daten-Ausgang `OUT` und bestätigt die Ausführung mit dem `CNF`-Ereignis.

## Technische Besonderheiten
- Einfache und direkte Wertübertragung ohne weitere Verarbeitung.
- Geringe Latenz, da keine komplexen Operationen durchgeführt werden.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Ausführung erfolgt unmittelbar bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Signalweiterleitung in Steuerungsanwendungen.
- Explizite Typkonvertierung, um die Lesbarkeit des Codes zu verbessern.
- Verwendung als Platzhalter für spätere Funktionserweiterungen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen wie `INT2DWORD` oder `BYTE2DWORD` führt `DWORD2DWORD` keine Typumwandlung durch, sondern dient lediglich der expliziten Weiterleitung.
- Ähnlich einfache Bausteine wie `BOOL2BOOL` oder `INT2INT` haben vergleichbare Funktionen, jedoch für andere Datentypen.

## Fazit
Der `DWORD2DWORD`-Funktionsblock ist ein grundlegender Baustein zur direkten Wertübertragung innerhalb von Steuerungsanwendungen. Seine Einfachheit macht ihn zu einem zuverlässigen Werkzeug für Signalweiterleitungen und explizite Typkonvertierungen.
