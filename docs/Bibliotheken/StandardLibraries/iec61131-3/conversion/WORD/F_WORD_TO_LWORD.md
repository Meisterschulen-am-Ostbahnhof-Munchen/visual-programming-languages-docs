# F_WORD_TO_LWORD

```{index} single: F_WORD_TO_LWORD
```

<img width="1451" height="214" alt="F_WORD_TO_LWORD" src="https://github.com/user-attachments/assets/ccfea12c-64cc-4b10-91db-6d39f78fc006" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_WORD_TO_LWORD` dient der Konvertierung eines `WORD`-Datentyps in einen `LWORD`-Datentyp. Dieser Baustein ist besonders nützlich in Szenarien, wo eine Erweiterung der Datenbreite erforderlich ist, beispielsweise bei der Kommunikation zwischen Systemen mit unterschiedlichen Datenwortgrößen.

![F_WORD_TO_LWORD](F_WORD_TO_LWORD.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Dieser Ereigniseingang ist mit dem Dateneingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ereignisausgang ist mit dem Datenausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Erwartet eine Eingabe vom Typ `WORD`, die in einen `LWORD` konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Gibt das konvertierte Ergebnis vom Typ `LWORD` aus.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das Ereignis `REQ` empfangen wird. Die Konvertierung erfolgt mittels der Funktion `WORD_TO_LWORD`, welche den Eingabewert `IN` vom Typ `WORD` in den Ausgabewert `OUT` vom Typ `LWORD` umwandelt. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Die Konvertierung ist direkt und ohne zusätzliche Parameter oder Zustandsverwaltung.
- Der Baustein ist für die Verwendung in Echtzeitsystemen geeignet, da er keine Verzögerungen oder komplexe Berechnungen beinhaltet.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Operation ist stateless und wird bei jedem `REQ`-Ereignis neu ausgeführt.

## Anwendungsszenarien
- Erweiterung der Datenbreite für nachfolgende Verarbeitungsschritte.
- Kompatibilitätssicherung zwischen Systemen mit unterschiedlichen Wortgrößen.
- Einfache Datentypkonvertierung in Steuerungs- und Automatisierungssystemen.

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu generischen Konvertierungsbausteinen bietet `F_WORD_TO_LWORD` eine spezialisierte und effiziente Lösung für die Konvertierung von `WORD` zu `LWORD`. Andere Bausteine könnten allgemeiner sein, aber weniger optimiert für diese spezifische Aufgabe.

## Fazit
Der `F_WORD_TO_LWORD` Funktionsblock ist ein einfacher, aber effektiver Baustein für die spezifische Konvertierung von `WORD` zu `LWORD`. Seine Einfachheit und direkte Funktionsweise machen ihn zu einer zuverlässigen Wahl in vielen Automatisierungs- und Steuerungsszenarien.