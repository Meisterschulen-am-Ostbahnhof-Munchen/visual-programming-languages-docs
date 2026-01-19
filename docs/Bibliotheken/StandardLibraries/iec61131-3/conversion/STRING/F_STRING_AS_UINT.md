# F_STRING_AS_UINT

```{index} single: F_STRING_AS_UINT
```

<img width="1467" height="212" alt="F_STRING_AS_UINT" src="https://github.com/user-attachments/assets/f8cf5972-de3c-4670-aef7-935e96a795d1" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_STRING_AS_UINT` dient der Konvertierung eines `STRING`-Wertes in einen `UINT`-Wert (unsigned integer). Diese Funktion ist besonders nützlich, wenn numerische Werte als Zeichenketten vorliegen und für weitere Berechnungen oder Steuerungsaufgaben in numerischer Form benötigt werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung des `STRING`-Wertes zu `UINT`. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (`STRING`): Der Eingang für den zu konvertierenden Zeichenkettenwert.

### **Daten-Ausgänge**
- **OUT** (`UINT`): Der Ausgang für den konvertierten numerischen Wert.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Bei Auslösung des Ereignisses `REQ` wird der Algorithmus ausgeführt, der den `STRING`-Wert von `IN` mittels der Funktion `STRING_AS_UINT` in einen `UINT`-Wert umwandelt. Das Ergebnis wird an `OUT` ausgegeben und das Ereignis `CNF` signalisiert den erfolgreichen Abschluss der Konvertierung.

## Technische Besonderheiten
- Der Funktionsblock ist einfach aufgebaut und enthält nur einen Algorithmus für die Konvertierung.
- Die Konvertierung erfolgt direkt und ohne zusätzliche Parameter oder komplexe Zustandslogik.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Ausführung erfolgt unmittelbar bei Auslösung von `REQ`.

## Anwendungsszenarien
- Verarbeitung von Benutzereingaben, die als Zeichenketten vorliegen.
- Konvertierung von Daten aus Textdateien oder Kommunikationsprotokollen für die weitere numerische Verarbeitung.
- Integration in Steuerungssysteme, die numerische Werte aus String-Quellen benötigen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsblöcken ist `F_STRING_AS_UINT` spezialisiert auf die Umwandlung von `STRING` zu `UINT` und bietet daher eine einfache und direkte Lösung für diesen spezifischen Anwendungsfall.
- Andere Blöcke könnten zusätzliche Funktionen wie Fehlerbehandlung oder verschiedene numerische Formate unterstützen, was hier nicht der Fall ist.

## Fazit
Der `F_STRING_AS_UINT` Funktionsblock ist eine effiziente und unkomplizierte Lösung für die Konvertierung von Zeichenketten in unsigned integer Werte. Seine Einfachheit macht ihn besonders geeignet für Anwendungen, bei denen eine schnelle und direkte Umwandlung benötigt wird.