# F_UINT_TO_USINT

```{index} single: F_UINT_TO_USINT
```

<img width="1454" height="216" alt="F_UINT_TO_USINT" src="https://github.com/user-attachments/assets/a0991cf7-1e8b-4cee-971c-5bf9334f137f" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_UINT_TO_USINT` dient der Konvertierung eines vorzeichenlosen 16-Bit-Integer-Werts (UINT) in einen vorzeichenlosen 8-Bit-Integer-Wert (USINT). Der Baustein ist Teil der `iec61131::conversion`-Bibliothek und implementiert eine einfache Typumwandlung.

![F_UINT_TO_USINT](F_UINT_TO_USINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung der Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (UINT): Der vorzeichenlose 16-Bit-Integer-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (USINT): Der resultierende vorzeichenlose 8-Bit-Integer-Wert nach der Konvertierung.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Auslösung des `REQ`-Ereignisses wird der Algorithmus ausgeführt, der den `IN`-Wert von UINT zu USINT konvertiert und das Ergebnis an `OUT` ausgibt. Anschließend wird das `CNF`-Ereignis ausgelöst, um den erfolgreichen Abschluss der Operation zu signalisieren. Die Konvertierung erfolgt durch Abschneiden der höherwertigen Bits, falls der Eingabewert den Wertebereich von USINT überschreitet.

## Technische Besonderheiten
- **Wertebereichsbehandlung**: Da USINT nur Werte von 0 bis 255 darstellen kann, werden bei Eingabewerten außerhalb dieses Bereichs die höherwertigen Bits verworfen. Dies kann zu Datenverlust führen.
- **Deterministisches Verhalten**: Die Konvertierung erfolgt in einem einzigen Ausführungsschritt ohne Zustandsverwaltung.

## Zustandsübersicht
Der Funktionsblock ist zustandslos und führt die Konvertierung bei jedem `REQ`-Ereignis neu aus.

## Anwendungsszenarien
- **Datenreduktion**: Verwendung in Systemen, wo Speicherplatz begrenzt ist und eine Reduktion der Datengröße erforderlich ist.
- **Protokollanpassung**: Anpassung von Datenformaten für Kommunikationsprotokolle, die nur 8-Bit-Daten unterstützen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- **F_UINT_TO_SINT**: Konvertiert UINT in einen vorzeichenbehafteten 8-Bit-Integer (SINT), wobei der Wertebereich anders behandelt wird.
- **F_UINT_TO_INT**: Behält die 16-Bit-Größe bei, konvertiert aber in einen vorzeichenbehafteten Typ.

## Fazit
`F_UINT_TO_USINT` ist ein einfacher und effizienter Funktionsblock für die Konvertierung von 16-Bit- zu 8-Bit-Daten ohne Vorzeichen. Seine Verwendung ist ideal in Szenarien, wo eine platzsparende Darstellung erforderlich ist, jedoch sollte die Möglichkeit eines Datenverlusts bei großen Eingabewerten berücksichtigt werden.