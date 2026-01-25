# F_STRING_AS_LREAL

```{index} single: F_STRING_AS_LREAL
```

<img width="1478" height="213" alt="F_STRING_AS_LREAL" src="https://github.com/user-attachments/assets/880cb73d-8178-4d13-866b-ef55bab0ae2a" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_STRING_AS_LREAL` dient der Konvertierung eines STRING-Wertes in einen LREAL-Wert (64-Bit Fließkommazahl). Dieser Baustein ist besonders nützlich, wenn Zeichenketten in numerische Werte umgewandelt werden müssen, z.B. bei der Verarbeitung von Benutzereingaben oder beim Lesen von Daten aus externen Quellen.

![F_STRING_AS_LREAL](F_STRING_AS_LREAL.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- `CNF`: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- `IN` (STRING): Der zu konvertierende Zeichenkettenwert.

### **Daten-Ausgänge**
- `OUT` (LREAL): Das Ergebnis der Konvertierung als 64-Bit Fließkommazahl.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Auslösung des `REQ`-Ereignisses wird der Wert am Eingang `IN` als Zeichenkette eingelesen und in einen LREAL-Wert konvertiert. Das Ergebnis wird am Ausgang `OUT` ausgegeben und das `CNF`-Ereignis signalisiert die erfolgreiche Ausführung.

Der Konvertierungsalgorithmus ist als ST-Code implementiert:
```ST
ALGORITHM REQ
OUT := STRING_AS_LREAL(IN);
END_ALGORITHM
```

## Technische Besonderheiten
- Die Konvertierung folgt den Standardregeln für die Umwandlung von STRING zu LREAL in IEC 61131-3.
- Bei ungültigen Eingabewerten (z.B. nicht-numerische Zeichenketten) kann das Verhalten abhängig von der Laufzeitumgebung variieren.

## Zustandsübersicht
Der Funktionsblock besitzt einen einfachen Zustandsautomaten:
1. Wartet auf `REQ`-Ereignis
2. Führt Konvertierung durch
3. Sendet `CNF`-Ereignis
4. Kehrt in Wartezustand zurück

## Anwendungsszenarien
- Verarbeitung von Benutzereingaben in numerischen Steuerungen
- Konvertierung von Textdaten aus Dateien oder Netzwerkquellen
- Schnittstellen zu Systemen, die numerische Daten als Zeichenketten übertragen

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsbausteinen ist dieser Funktionsblock spezialisiert auf die STRING-zu-LREAL-Konvertierung.
- Andere ähnliche Bausteine könnten zusätzliche Parameter für die Zahlenformatierung bieten.

## Fazit
Der `F_STRING_AS_LREAL` Funktionsblock bietet eine einfache und effiziente Möglichkeit, Zeichenketten in 64-Bit Fließkommazahlen umzuwandeln. Seine klare Schnittstelle und einfache Funktionsweise machen ihn besonders geeignet für Standardkonvertierungsaufgaben in Automatisierungsprojekten.