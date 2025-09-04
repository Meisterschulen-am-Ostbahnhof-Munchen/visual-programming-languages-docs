# F_WSTRING_AS_ULINT

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_WSTRING_AS_ULINT` dient der Konvertierung eines WSTRING-Datentyps in einen ULINT-Datentyp. Dieser Baustein ist besonders nützlich in Szenarien, wo Zeichenketten in numerische Werte umgewandelt werden müssen, beispielsweise bei der Verarbeitung von Benutzereingaben oder beim Parsen von Daten aus externen Quellen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Dieser Ereigniseingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ereignisausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (WSTRING): Die Eingabezeichenkette, die in einen ULINT-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (ULINT): Der konvertierte numerische Wert.

### **Adapter**
Es sind keine Adapter für diesen Funktionsblock definiert.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, wenn das `REQ`-Ereignis empfangen wird. Die Konvertierung erfolgt mittels der Funktion `WSTRING_AS_ULINT`, die die Zeichenkette `IN` in einen vorzeichenlosen 64-Bit-Integer (`ULINT`) umwandelt. Nach erfolgreicher Konvertierung wird das `CNF`-Ereignis ausgelöst, und der konvertierte Wert steht am Ausgang `OUT` zur Verfügung.

## Technische Besonderheiten
- Die Konvertierung erfolgt streng typisiert, d.h., die Eingabe muss eine gültige numerische Repräsentation in der Zeichenkette enthalten, um korrekte Ergebnisse zu liefern.
- Der Funktionsblock unterstützt keine Fehlerbehandlung für ungültige Eingaben. Es liegt in der Verantwortung des Anwenders, sicherzustellen, dass die Eingabe korrekt formatiert ist.

## Zustandsübersicht
1. **Idle**: Der Funktionsblock wartet auf das `REQ`-Ereignis.
2. **Processing**: Bei Empfang von `REQ` wird die Konvertierung durchgeführt.
3. **Completed**: Nach der Konvertierung wird das `CNF`-Ereignis ausgelöst, und der Funktionsblock kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- Konvertierung von Benutzereingaben in numerische Werte.
- Parsen von Daten aus externen Quellen (z.B. Dateien, Netzwerk) in numerische Formate.
- Verwendung in Steuerungsanwendungen, wo Zeichenketten in Steuerungswerte umgewandelt werden müssen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsbausteinen ist `F_WSTRING_AS_ULINT` spezialisiert auf die Konvertierung von WSTRING zu ULINT und bietet daher eine optimierte und typsichere Lösung für diesen spezifischen Anwendungsfall.
- Andere Bausteine wie `F_STRING_AS_INT` oder `F_WSTRING_AS_LINT` bieten ähnliche Funktionalitäten, jedoch für andere Datentypen.

## Fazit
Der `F_WSTRING_AS_ULINT`-Funktionsblock ist ein effizientes Werkzeug für die Konvertierung von Zeichenketten in vorzeichenlose 64-Bit-Integer-Werte. Seine Einfachheit und Spezialisierung machen ihn ideal für Anwendungen, die eine schnelle und typsichere Konvertierung erfordern. Beachten Sie jedoch, dass keine integrierte Fehlerbehandlung für ungültige Eingaben vorhanden ist.