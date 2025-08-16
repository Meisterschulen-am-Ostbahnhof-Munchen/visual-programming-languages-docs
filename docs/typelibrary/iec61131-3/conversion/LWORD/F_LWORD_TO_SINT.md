# F_LWORD_TO_SINT

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LWORD_TO_SINT` dient der Konvertierung eines `LWORD`-Wertes (64-Bit unsigned integer) in einen `SINT`-Wert (8-Bit signed integer). Diese Konvertierung ist nützlich, wenn Daten aus einem größeren Wertebereich in einen kleineren, spezifischeren Bereich übertragen werden müssen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung des Funktionsblocks. Bei Aktivierung wird der Eingangswert `IN` verarbeitet.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert die erfolgreiche Beendigung der Konvertierung und stellt den Ergebniswert `OUT` bereit.

### **Daten-Eingänge**
- **IN** (`LWORD`): Der Eingangswert, der von `LWORD` in `SINT` konvertiert wird.

### **Daten-Ausgänge**
- **OUT** (`SINT`): Das Ergebnis der Konvertierung.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock führt eine direkte Typumwandlung des Eingangswertes `IN` vom Typ `LWORD` in den Typ `SINT` durch. Die Konvertierung erfolgt durch die Funktion `LWORD_TO_SINT(IN)`, die im Algorithmus `REQ` implementiert ist. Bei erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- **Typumwandlung**: Da `LWORD` einen größeren Wertebereich als `SINT` abdeckt, kann es zu einem Datenverlust kommen, wenn der Eingangswert außerhalb des darstellbaren Bereichs von `SINT` (-128 bis 127) liegt.
- **Algorithmus**: Der Algorithmus ist in Structured Text (ST) implementiert und führt eine direkte Konvertierung durch.

## Zustandsübersicht
1. **Idle-Zustand**: Wartet auf das Ereignis `REQ`.
2. **Ausführungszustand**: Bei `REQ` wird die Konvertierung durchgeführt.
3. **Bestätigungszustand**: Nach erfolgreicher Konvertierung wird `CNF` ausgelöst und der Block kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- **Datenreduktion**: Wenn nur die unteren 8 Bit eines 64-Bit-Wertes relevant sind.
- **Kommunikation**: Bei der Übertragung von Daten zwischen Systemen mit unterschiedlichen Wortgrößen.
- **Speicheroptimierung**: Wenn Speicherplatz begrenzt ist und kleinere Datentypen bevorzugt werden.

## Vergleich mit ähnlichen Bausteinen
- **F_LWORD_TO_INT**: Konvertiert `LWORD` in `INT` (16-Bit signed integer).
- **F_LWORD_TO_DINT**: Konvertiert `LWORD` in `DINT` (32-Bit signed integer).
- **F_LWORD_TO_USINT**: Konvertiert `LWORD` in `USINT` (8-Bit unsigned integer).

Im Gegensatz zu diesen Blöcken ist `F_LWORD_TO_SINT` spezifisch für die Konvertierung in einen 8-Bit signed integer.

## Fazit
Der Funktionsblock `F_LWORD_TO_SINT` bietet eine einfache und effiziente Möglichkeit, 64-Bit-Werte in 8-Bit signed integers umzuwandeln. Er ist besonders nützlich in Szenarien, wo Speichereffizienz oder die Verarbeitung von Teilen eines größeren Datentyps erforderlich ist. Bei der Verwendung ist jedoch auf den möglichen Datenverlust bei Werten außerhalb des `SINT`-Bereichs zu achten.