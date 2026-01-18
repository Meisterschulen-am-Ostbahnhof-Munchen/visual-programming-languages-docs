# F_UDINT_TO_DWORD

```{index} single: F_UDINT_TO_DWORD
```

<img width="1464" height="212" alt="F_UDINT_TO_DWORD" src="https://github.com/user-attachments/assets/2a17af0b-98a8-4d4b-ac10-de4278c1451a" />

* * * * * * * * * *
## 📺 Video

* [Zusätzlich: Uebung_083: Aufwärts/Abwärts zählen: E_CTUD_UDINT Datentyp UDINT; mit Anzeige am VT.](https://www.youtube.com/watch?v=oTPDtsw5eAw)

## Einleitung
Der Funktionsblock `F_UDINT_TO_DWORD` dient der Konvertierung eines `UDINT`-Wertes (32-Bit unsignierte Ganzzahl) in einen `DWORD`-Wert (32-Bit Datenwort). Diese Konvertierung ist insbesondere in Szenarien nützlich, in denen numerische Werte als Bitmuster weiterverarbeitet oder übertragen werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (`UDINT`): Der zu konvertierende 32-Bit unsignierte Ganzzahlwert.

### **Daten-Ausgänge**
- **OUT** (`DWORD`): Das Ergebnis der Konvertierung als 32-Bit Datenwort.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Bei Auslösung des `REQ`-Ereignisses wird der Wert am Eingang `IN` vom Typ `UDINT` in einen `DWORD`-Wert konvertiert und am Ausgang `OUT` ausgegeben. Das `CNF`-Ereignis signalisiert den erfolgreichen Abschluss der Konvertierung.

Der zugrundeliegende Algorithmus ist in Structured Text (ST) implementiert:
```ST
ALGORITHM REQ
OUT := UDINT_TO_DWORD(IN);
END_ALGORITHM
```

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt durch eine Typumwandlung, ohne Änderung der Bitrepräsentation.
- Der Funktionsblock ist deterministisch und hat keine internen Zustände.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Umwandlung von numerischen Werten für die bitweise Verarbeitung.
- Kompatibilität mit Systemen, die `DWORD`-Daten erwarten.
- Datenvorbereitung für Kommunikationsprotokolle oder Hardware-Register.

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu arithmetischen Funktionsblöcken ändert `F_UDINT_TO_DWORD` nicht den Wert, sondern nur den Datentyp.
- Ähnliche Konvertierungsblöcke existieren für andere Datentypen (z.B. `INT_TO_DINT`), jedoch mit unterschiedlichen Quell- und Zieltypen.

## Fazit
`F_UDINT_TO_DWORD` ist ein einfacher, aber essentieller Funktionsblock für Typkonvertierungen in IEC 61499-basierten Steuerungssystemen. Seine deterministische Funktionsweise und klare Schnittstelle machen ihn zu einem verlässlichen Werkzeug für Datenumwandlungen.