# F_WSTRING_AS_LREAL

```{index} single: F_WSTRING_AS_LREAL
```

<img width="1491" height="214" alt="F_WSTRING_AS_LREAL" src="https://github.com/user-attachments/assets/b9ea26e0-7746-451f-944c-2f89290dd9c1" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_WSTRING_AS_LREAL` dient der Konvertierung eines WSTRING-Wertes in einen LREAL-Wert. Dieser Baustein ist besonders nützlich, wenn Zeichenketten in numerische Werte umgewandelt werden müssen, beispielsweise für mathematische Berechnungen oder Datenverarbeitung.

![F_WSTRING_AS_LREAL](F_WSTRING_AS_LREAL.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung des Funktionsblocks. Wird dieser Eingang aktiviert, beginnt die Konvertierung des WSTRING-Wertes am Eingang `IN` in einen LREAL-Wert.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den erfolgreichen Abschluss der Konvertierung. Der konvertierte LREAL-Wert ist am Ausgang `OUT` verfügbar.

### **Daten-Eingänge**
- **IN** (WSTRING): Der Eingang für die Zeichenkette, die in einen LREAL-Wert umgewandelt werden soll.

### **Daten-Ausgänge**
- **OUT** (LREAL): Der Ausgang für den konvertierten LREAL-Wert.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Der Funktionsblock führt bei Aktivierung des `REQ`-Ereignisses die Konvertierung des WSTRING-Wertes am Eingang `IN` in einen LREAL-Wert durch. Die Konvertierung erfolgt mittels der Funktion `WSTRING_AS_LREAL`. Nach erfolgreicher Konvertierung wird das `CNF`-Ereignis ausgelöst und der konvertierte Wert am Ausgang `OUT` bereitgestellt.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt und ohne zusätzliche Parameter.
- Der Funktionsblock ist für die Verwendung in Echtzeitsystemen optimiert.

## Zustandsübersicht
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Processing**: Führt die Konvertierung durch.
3. **Complete**: Signalisiert den Abschluss mit dem `CNF`-Ereignis.

## Anwendungsszenarien
- Konvertierung von Benutzereingaben in numerische Werte.
- Verarbeitung von Textdaten aus externen Quellen für Berechnungen.
- Integration in Systeme, die sowohl Zeichenketten als auch numerische Werte verarbeiten müssen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen ist `F_WSTRING_AS_LREAL` speziell auf die Umwandlung von WSTRING in LREAL ausgelegt.
- Andere Bausteine könnten zusätzliche Parameter oder Fehlerbehandlung bieten, dieser Baustein ist jedoch auf Einfachheit und Effizienz optimiert.

## Fazit
Der `F_WSTRING_AS_LREAL` Funktionsblock bietet eine einfache und effiziente Möglichkeit, WSTRING-Werte in LREAL-Werte umzuwandeln. Seine klare Schnittstellenstruktur und direkte Funktionsweise machen ihn zu einem wertvollen Baustein in vielen Anwendungen.