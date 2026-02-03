# F_WSTRING_TO_STRING

```{index} single: F_WSTRING_TO_STRING
```

<img width="1507" height="214" alt="F_WSTRING_TO_STRING" src="https://github.com/user-attachments/assets/7dab60b1-32bc-41ee-a2f0-2ca57a0e11e2" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_WSTRING_TO_STRING` dient der Konvertierung eines WSTRING-Datentyps in einen STRING-Datentyp. Dieser Baustein ist besonders nützlich in Szenarien, wo eine Umwandlung von breiten Zeichenketten (Unicode) in einfache Zeichenketten (ASCII oder ähnlich) erforderlich ist.

![F_WSTRING_TO_STRING](F_WSTRING_TO_STRING.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Bei Auslösung dieses Ereignisses wird der WSTRING-Eingang `IN` verarbeitet.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung und gibt das Ergebnis über den STRING-Ausgang `OUT` aus.

### **Daten-Eingänge**
- **IN** (WSTRING): Die Eingabezeichenkette im WSTRING-Format, die konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (STRING): Die konvertierte Zeichenkette im STRING-Format.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das Ereignis `REQ` ausgelöst wird. Die Umwandlung erfolgt mittels der integrierten Funktion `WSTRING_TO_STRING`, die den WSTRING-Eingang `IN` in einen STRING-Ausgang `OUT` umwandelt. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Der FB unterstützt keine zusätzlichen Parameter oder Konfigurationen für die Konvertierung.
- Die Konvertierung erfolgt direkt und ohne Zwischenspeicherung.

## Zustandsübersicht
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Processing**: Führt die Konvertierung durch.
3. **Complete**: Löst `CNF` aus und gibt das Ergebnis aus.

## Anwendungsszenarien
- Konvertierung von Unicode-Texten in ASCII-Texten.
- Verwendung in Systemen, die keine breiten Zeichenketten unterstützen.
- Integration in bestehende Systeme, die nur mit STRING-Datentypen arbeiten.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu generischen Konvertierungsbausteinen ist `F_WSTRING_TO_STRING` spezialisiert auf die Umwandlung von WSTRING zu STRING.
- Ähnliche Bausteine könnten zusätzliche Optionen wie Zeichensatz-Konvertierung bieten, dieser FB ist jedoch auf die grundlegende Funktionalität beschränkt.

## Fazit
Der `F_WSTRING_TO_STRING` Funktionsblock bietet eine einfache und effiziente Möglichkeit, WSTRING-Daten in STRING-Daten umzuwandeln. Seine klare Schnittstelle und direkte Funktionsweise machen ihn ideal für Projekte, die eine schnelle und unkomplizierte Konvertierung benötigen.