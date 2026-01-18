# F_WSTRING_AS_UDINT

```{index} single: F_WSTRING_AS_UDINT
```

<img width="1494" height="214" alt="F_WSTRING_AS_UDINT" src="https://github.com/user-attachments/assets/80526643-8f3a-4829-a9c8-7fec610340b8" />

* * * * * * * * * *
## 📺 Video

* [Zusätzlich: Uebung_083: Aufwärts/Abwärts zählen: E_CTUD_UDINT Datentyp UDINT; mit Anzeige am VT.](https://www.youtube.com/watch?v=oTPDtsw5eAw)

## Einleitung
Der Funktionsblock `F_WSTRING_AS_UDINT` dient der Konvertierung eines WSTRING-Wertes in einen UDINT-Wert. Dieser Baustein ist besonders nützlich in Szenarien, wo Zeichenketten in numerische Werte umgewandelt werden müssen, beispielsweise bei der Verarbeitung von Benutzereingaben oder der Interpretation von Daten aus externen Quellen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Dieser Eingang löst die Konvertierung aus.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Dieser Ausgang signalisiert den Abschluss der Konvertierung.

### **Daten-Eingänge**
- **IN**: WSTRING. Die Eingabezeichenkette, die in einen UDINT-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: UDINT. Der konvertierte numerische Wert.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, wenn das Ereignis `REQ` empfangen wird. Die Konvertierung erfolgt mittels der Funktion `WSTRING_AS_UDINT`, die den WSTRING-Eingang `IN` in einen UDINT-Wert umwandelt und das Ergebnis an `OUT` ausgibt. Nach Abschluss der Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Der Funktionsblock ist einfach und effizient, da er direkt die eingebaute Konvertierungsfunktion nutzt.
- Es gibt keine zusätzliche Fehlerbehandlung für ungültige Eingaben; die Konvertierung erfolgt gemäß den Regeln der IEC 61131-3.

## Zustandsübersicht
Der Funktionsblock hat einen einfachen Zustandsautomaten:
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Processing**: Führt die Konvertierung durch.
3. **Complete**: Sendet das `CNF`-Ereignis und kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- **Datenverarbeitung**: Konvertierung von Benutzereingaben oder externen Daten in numerische Werte.
- **Protokollierung**: Umwandlung von Zeichenketten in numerische IDs für die Speicherung oder Weiterverarbeitung.
- **Schnittstellenkommunikation**: Vorbereitung von Daten für die Übertragung über Protokolle, die numerische Werte erfordern.

## Vergleich mit ähnlichen Bausteinen
- **F_STRING_AS_UDINT**: Ähnlicher Funktionsblock, jedoch für STRING anstelle von WSTRING.
- **F_UDINT_AS_WSTRING**: Führt die umgekehrte Konvertierung durch (UDINT zu WSTRING).

## Fazit
Der `F_WSTRING_AS_UDINT` Funktionsblock ist ein einfaches und effektives Werkzeug für die Konvertierung von WSTRING-Werten in UDINT. Seine klare Schnittstelle und direkte Funktionsweise machen ihn ideal für Anwendungen, die solche Konvertierungen erfordern.