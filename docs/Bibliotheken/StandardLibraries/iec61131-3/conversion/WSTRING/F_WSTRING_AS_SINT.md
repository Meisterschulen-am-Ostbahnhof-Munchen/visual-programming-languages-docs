# F_WSTRING_AS_SINT

```{index} single: F_WSTRING_AS_SINT
```

<img width="1481" height="214" alt="F_WSTRING_AS_SINT" src="https://github.com/user-attachments/assets/5c42bc49-eddd-4518-b97f-197880155b0d" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_WSTRING_AS_SINT` dient der Konvertierung eines WSTRING-Wertes in einen SINT-Wert (8-Bit Ganzzahl). Der Block ist besonders nützlich in Szenarien, wo Zeichenketten in numerische Werte umgewandelt werden müssen.

![F_WSTRING_AS_SINT](F_WSTRING_AS_SINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Auslösendes Ereignis für die Konvertierung. Wird mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Bestätigt die erfolgreiche Ausführung der Konvertierung. Wird mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (WSTRING): Die Eingabezeichenkette, die in einen SINT-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (SINT): Der resultierende 8-Bit Ganzzahlwert nach der Konvertierung.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das `REQ`-Ereignis eintrifft. Dabei wird die Funktion `WSTRING_AS_SINT` auf den Eingabewert `IN` angewendet und das Ergebnis an `OUT` ausgegeben. Die erfolgreiche Ausführung wird durch das `CNF`-Ereignis signalisiert.

## Technische Besonderheiten
- Die Konvertierung erfolgt mittels der eingebauten Funktion `WSTRING_AS_SINT`.
- Der Block ist für die Verwendung in IEC 61131-3-konformen Umgebungen optimiert.

## Zustandsübersicht
Der Block hat keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Konvertierung von Benutzereingaben in numerische Werte.
- Verarbeitung von Zeichenketten aus externen Quellen (z.B. Sensoren oder Netzwerkkommunikation).

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsblöcken ist `F_WSTRING_AS_SINT` spezialisiert auf die Umwandlung von WSTRING zu SINT.
- Andere Blöcke könnten zusätzliche Funktionen wie Fehlerbehandlung oder Typüberprüfung bieten.

## Fazit
Der `F_WSTRING_AS_SINT`-Block bietet eine effiziente und direkte Methode zur Konvertierung von WSTRING-Werten in SINT-Werte. Seine Einfachheit und Spezialisierung machen ihn ideal für spezifische Anwendungsfälle.