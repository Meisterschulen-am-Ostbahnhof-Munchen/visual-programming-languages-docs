# F_STRING_AS_DINT

```{index} single: F_STRING_AS_DINT
```

<img width="1464" height="213" alt="F_STRING_AS_DINT" src="https://github.com/user-attachments/assets/cbb2bda3-8b1f-45cd-a56f-e4a1958ac543" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_STRING_AS_DINT` dient der Konvertierung eines `STRING`-Wertes in einen `DINT`-Wert. Diese Funktion ist besonders nützlich, wenn Zeichenketten in numerische Werte umgewandelt werden müssen, beispielsweise bei der Verarbeitung von Benutzereingaben oder der Interpretation von Textdaten.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Dieser Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (`STRING`): Der zu konvertierende Zeichenkettenwert.

### **Daten-Ausgänge**
- **OUT** (`DINT`): Das Ergebnis der Konvertierung als 32-Bit-Ganzzahl.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das Ereignis `REQ` ausgelöst wird. Dabei wird der `STRING`-Wert am Eingang `IN` in einen `DINT`-Wert umgewandelt und am Ausgang `OUT` ausgegeben. Die Konvertierung erfolgt mithilfe der Funktion `STRING_AS_DINT`. Nach Abschluss der Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Die Konvertierung kann fehlschlagen, wenn der `STRING`-Wert keine gültige numerische Repräsentation enthält. In solchen Fällen kann der Ausgang `OUT` einen undefinierten Wert annehmen.
- Der Funktionsblock ist Teil des Pakets `iec61131::conversion`.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Verarbeitung von Benutzereingaben, die als Zeichenketten vorliegen.
- Interpretation von Textdaten aus Dateien oder Netzwerkquellen.
- Umwandlung von konfigurierbaren Parametern, die als Zeichenketten gespeichert sind.

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu `F_STRING_TO_*`-Funktionsblöcken, die explizite Typkonvertierungen durchführen, interpretiert `F_STRING_AS_DINT` den `STRING`-Wert direkt als `DINT`.
- Ähnliche Funktionsblöcke wie `F_STRING_TO_DINT` könnten zusätzliche Parameter für die Formatierung bieten, sind jedoch in der Standardbibliothek nicht enthalten.

## Fazit
Der `F_STRING_AS_DINT`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, Zeichenketten in 32-Bit-Ganzzahlen umzuwandeln. Seine Verwendung ist besonders in Szenarien sinnvoll, in denen eine direkte Interpretation der Zeichenkette als numerischer Wert erforderlich ist.