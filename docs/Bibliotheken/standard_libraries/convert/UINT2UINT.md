# UINT2UINT

<img width="1171" height="182" alt="UINT2UINT" src="https://github.com/user-attachments/assets/798c64a4-e0cd-446e-ac15-18a235fbb311" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `UINT2UINT` dient der einfachen Konvertierung eines vorzeichenlosen Integer-Wertes (UINT) in einen anderen vorzeichenlosen Integer-Wert (UINT). Dabei wird der Eingabewert direkt auf den Ausgabewert übertragen. Der FB ist Teil des `eclipse4diac::convert` Pakets.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Normaler Ausführungsanforderung. Löst die Konvertierung aus.

### **Ereignis-Ausgänge**
- `CNF`: Ausführungsbestätigung. Wird nach erfolgreicher Konvertierung ausgelöst.

### **Daten-Eingänge**
- `IN` (UINT): Der Eingabewert, der konvertiert werden soll.

### **Daten-Ausgänge**
- `OUT` (UINT): Der konvertierte Ausgabewert.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt eine direkte Zuweisung des Eingabewertes `IN` zum Ausgabewert `OUT` durch. Bei Auslösung des `REQ`-Ereignisses wird der Algorithmus ausgeführt, der `OUT` den Wert von `IN` zuweist. Anschließend wird das `CNF`-Ereignis ausgelöst.

## Technische Besonderheiten
- Einfache direkte Zuweisung ohne weitere Verarbeitung.
- Keine zusätzliche Logik oder Bedingungen.

## Zustandsübersicht
Der FB besitzt keine internen Zustände. Die Ausführung erfolgt direkt bei Anforderung (`REQ`).

## Anwendungsszenarien
- Einfache Datentypkonvertierung in Steuerungssystemen.
- Weiterleitung von Werten ohne Änderung in komplexeren FB-Netzwerken.
- Test- und Debugging-Zwecke, um Werte durchzureichen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungs-FBs wie `INT2UINT` oder `BOOL2INT` bietet dieser FB keine Datentypumwandlung, sondern nur eine direkte Zuweisung.
- Ähnlich wie `IDENTITY`-FBs, jedoch spezifisch für UINT-Datentypen.

## Fazit
Der `UINT2UINT`-Funktionsblock ist ein einfaches, aber nützliches Werkzeug für die direkte Weitergabe von UINT-Werten in IEC 61499-Systemen. Seine Einfachheit macht ihn zuverlässig und leicht verständlich, jedoch ohne zusätzliche Funktionalität.
