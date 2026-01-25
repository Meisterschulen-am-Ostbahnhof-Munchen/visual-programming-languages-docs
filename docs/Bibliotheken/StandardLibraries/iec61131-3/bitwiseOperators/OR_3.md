# OR_3

```{index} single: OR_3
```

![OR_3](https://user-images.githubusercontent.com/116869307/214144056-e850a789-92e3-46c0-ba3c-97960b404daa.png)

* * * * * * * * * *

## Einleitung
Der OR_3 Funktionsblock ist ein generischer Baustein zur Berechnung der bitweisen booleschen ODER-Verknüpfung mit drei Eingängen. Er führt eine logische ODER-Operation auf Bitebene durch und unterstützt verschiedene Bit-Datentypen gemäß der IEC 61131-3 Norm.

![OR_3](OR_3.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung - löst die Berechnung der ODER-Verknüpfung aus

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung - signalisiert den Abschluss der Berechnung

### **Daten-Eingänge**
- **IN1**: OR-Eingang 1 (ANY_BIT Datentyp)
- **IN2**: OR-Eingang 2 (ANY_BIT Datentyp)
- **IN3**: OR-Eingang 3 (ANY_BIT Datentyp)

### **Daten-Ausgänge**
- **OUT**: OR-Ergebnis (ANY_BIT Datentyp)

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der OR_3 Funktionsblock führt bei jedem REQ-Ereignis eine bitweise ODER-Verknüpfung der drei Eingangswerte IN1, IN2 und IN3 durch. Das Ergebnis wird am Datenausgang OUT ausgegeben und gleichzeitig wird das CNF-Ereignis generiert, um den Abschluss der Operation zu signalisieren.

Die Operation wird für jeden Bit-Position separat durchgeführt: OUT[i] = IN1[i] OR IN2[i] OR IN3[i]

## Technische Besonderheiten
- Unterstützt den generischen ANY_BIT Datentyp, was die Verwendung mit verschiedenen Bit-Datentypen wie BOOL, BYTE, WORD, DWORD etc. ermöglicht
- Implementiert als generischer Funktionsblock gemäß IEC 61131-3 Standard
- Gehört zum Package "iec61131::bitwiseOperators"

## Zustandsübersicht
1. **Wartezustand**: Block wartet auf REQ-Ereignis
2. **Berechnungszustand**: Bei REQ-Ereignis werden die Eingänge verarbeitet
3. **Ausgabezustand**: Ergebnis wird an OUT ausgegeben und CNF-Ereignis wird generiert

## Anwendungsszenarien
- Kombination mehrerer digitaler Signale in Steuerungsanwendungen
- Maskenoperationen in der Datenverarbeitung
- Parallele Verarbeitung mehrerer Bedingungen
- Signalverknüpfung in Automatisierungssystemen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen ODER-Bausteinen mit nur zwei Eingängen bietet OR_3 die Möglichkeit, drei Eingänge direkt zu verknüpfen, was die Programmstruktur vereinfacht und zusätzliche Verkettungen vermeidet. Gegenüber arithmetischen Bausteinen arbeitet OR_3 ausschließlich auf Bitebene.

## Fazit
Der OR_3 Funktionsblock stellt eine effiziente und flexible Lösung für bitweise ODER-Operationen mit drei Eingängen dar. Seine generische Natur ermöglicht den Einsatz in verschiedenen Anwendungsbereichen und mit unterschiedlichen Bit-Datentypen, was ihn zu einem vielseitigen Werkzeug in der Automatisierungstechnik macht.