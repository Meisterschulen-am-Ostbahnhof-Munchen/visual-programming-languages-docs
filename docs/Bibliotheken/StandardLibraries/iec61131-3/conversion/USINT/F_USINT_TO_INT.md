# F_USINT_TO_INT

```{index} single: F_USINT_TO_INT
```

<img width="1436" height="214" alt="F_USINT_TO_INT" src="https://github.com/user-attachments/assets/d630e0ac-d3d0-4568-913f-698cfdc7ad6c" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_USINT_TO_INT` dient der Konvertierung eines vorzeichenlosen 8-Bit-Integer-Werts (USINT) in einen vorzeichenbehafteten 16-Bit-Integer-Wert (INT). Dieser Baustein ist Teil des `iec61131::conversion` Pakets und ermöglicht eine einfache Typumwandlung zwischen diesen beiden Datentypen.

![F_USINT_TO_INT](F_USINT_TO_INT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Dieser Ereigniseingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ereignisausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (USINT): Der vorzeichenlose 8-Bit-Integer-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (INT): Der resultierende vorzeichenbehaftete 16-Bit-Integer-Wert nach der Konvertierung.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, indem der Wert des Eingangs `IN` direkt dem Ausgang `OUT` zugewiesen wird. Die Konvertierung erfolgt bei Auftreten des Ereignisses `REQ` und wird durch das Ereignis `CNF` bestätigt.

## Technische Besonderheiten
- **Einfache Typumwandlung**: Der Baustein führt keine zusätzliche Verarbeitung oder Prüfung der Daten durch.
- **Effiziente Implementierung**: Die Konvertierung erfolgt direkt in einem ST-Algorithmus ohne zusätzliche Logik.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Auftreten des `REQ`-Ereignisses.

## Anwendungsszenarien
- **Typumwandlung in Steuerungsanwendungen**: Wenn ein vorzeichenloser 8-Bit-Wert in einen vorzeichenbehafteten 16-Bit-Wert umgewandelt werden muss.
- **Datenkompatibilität**: In Szenarien, wo verschiedene Komponenten unterschiedliche Datentypen erwarten.

## Vergleich mit ähnlichen Bausteinen
- **F_USINT_TO_UINT**: Konvertiert USINT zu UINT (vorzeichenloser 16-Bit-Integer).
- **F_USINT_TO_DINT**: Konvertiert USINT zu DINT (vorzeichenbehafteter 32-Bit-Integer).
- **F_USINT_TO_UDINT**: Konvertiert USINT zu UDINT (vorzeichenloser 32-Bit-Integer).

## Fazit
Der `F_USINT_TO_INT` Funktionsblock bietet eine einfache und effiziente Möglichkeit, vorzeichenlose 8-Bit-Integer-Werte in vorzeichenbehaftete 16-Bit-Integer-Werte umzuwandeln. Er ist besonders nützlich in Anwendungen, wo eine Typumwandlung ohne zusätzliche Verarbeitung erforderlich ist.