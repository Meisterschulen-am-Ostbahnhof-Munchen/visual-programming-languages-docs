# F_UDINT_TO_LINT

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_UDINT_TO_LINT` dient der Konvertierung eines 32-Bit vorzeichenlosen Integer-Werts (UDINT) in einen 64-Bit vorzeichenbehafteten Integer-Wert (LINT). Dieser Baustein ist Teil des `iec61131::conversion`-Pakets und ermöglicht eine einfache und effiziente Typumwandlung zwischen diesen beiden Datentypen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung der Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (UDINT): Der 32-Bit vorzeichenlose Integer-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (LINT): Der resultierende 64-Bit vorzeichenbehaftete Integer-Wert nach der Konvertierung.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Auslösung des Ereigniseingangs `REQ` wird der Wert des Daten-Eingangs `IN` (UDINT) in den Daten-Ausgang `OUT` (LINT) kopiert. Die Konvertierung erfolgt direkt, da LINT einen größeren Wertebereich als UDINT abdeckt und somit alle möglichen UDINT-Werte ohne Datenverlust darstellen kann. Nach Abschluss der Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- **Algorithmus**: Der Funktionsblock verwendet einen einfachen ST-Algorithmus, der den Eingabewert direkt dem Ausgabewert zuweist.
- **Datenverlust**: Da LINT einen größeren Wertebereich als UDINT hat, gibt es bei dieser Konvertierung keinen Datenverlust.
- **Performance**: Die Konvertierung ist sehr effizient und erfolgt in konstanter Zeit.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- **Typumwandlung**: In Szenarien, wo ein vorzeichenloser 32-Bit-Wert in einen vorzeichenbehafteten 64-Bit-Wert umgewandelt werden muss, z.B. bei der Verarbeitung von Sensordaten oder in mathematischen Berechnungen.
- **Datenkompatibilität**: Bei der Integration von Systemen, die unterschiedliche Integer-Typen verwenden.

## Vergleich mit ähnlichen Bausteinen
- **F_UDINT_TO_DINT**: Konvertiert UDINT zu DINT (32-Bit vorzeichenbehaftet), kann jedoch zu Überlauf führen, da DINT einen kleineren Wertebereich hat.
- **F_UDINT_TO_ULINT**: Konvertiert UDINT zu ULINT (64-Bit vorzeichenlos), behält jedoch den vorzeichenlosen Charakter bei.

## Fazit
Der `F_UDINT_TO_LINT`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, vorzeichenlose 32-Bit-Integer-Werte in vorzeichenbehaftete 64-Bit-Integer-Werte umzuwandeln. Durch seine direkte und verlustfreie Konvertierung eignet er sich ideal für Anwendungen, die eine Erweiterung des Wertebereichs erfordern.