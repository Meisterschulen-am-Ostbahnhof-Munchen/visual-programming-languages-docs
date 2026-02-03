# F_DWORD_TO_ULINT

```{index} single: F_DWORD_TO_ULINT
```

<img width="1254" height="181" alt="F_DWORD_TO_ULINT" src="https://github.com/user-attachments/assets/e5bbb4d1-3d9a-4a73-b891-646529c28a89" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_DWORD_TO_ULINT` dient der Konvertierung eines `DWORD`-Wertes in einen `ULINT`-Wert. Er ist Teil des `iec61131::conversion`-Pakets und wird typischerweise in Automatisierungsanwendungen eingesetzt, wo eine Typumwandlung zwischen diesen beiden Datentypen erforderlich ist.

![F_DWORD_TO_ULINT](F_DWORD_TO_ULINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Dieser Eingang löst die Ausführung des Funktionsblocks aus. Er ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Dieser Ausgang signalisiert die erfolgreiche Ausführung des Funktionsblocks. Er ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingang erwartet einen `DWORD`-Wert, der in einen `ULINT`-Wert umgewandelt werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang liefert den konvertierten `ULINT`-Wert.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `DWORD` zu `ULINT` durch, sobald das `REQ`-Ereignis eintrifft. Der Algorithmus innerhalb des Funktionsblocks nutzt die Funktion `DWORD_TO_ULINT`, um die Umwandlung durchzuführen. Nach erfolgreicher Konvertierung wird das `CNF`-Ereignis ausgelöst, und der konvertierte Wert steht am `OUT`-Ausgang zur Verfügung.

## Technische Besonderheiten
- Der Funktionsblock ist als einfacher Funktionsblock (`SimpleFB`) implementiert.
- Die Konvertierung erfolgt direkt und ohne zusätzliche Verzögerung.
- Der Funktionsblock ist unter der Eclipse Public License 2.0 lizenziert.

## Zustandsübersicht
Der Funktionsblock hat keinen internen Zustand. Die Ausführung erfolgt ausschließlich bei Eintreffen des `REQ`-Ereignisses.

## Anwendungsszenarien
- Typumwandlung in Automatisierungsanwendungen, wo `DWORD`-Werte in `ULINT`-Werte umgewandelt werden müssen.
- Integration in größere Steuerungssysteme, die unterschiedliche Datentypen verarbeiten.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_WORD_TO_UINT` oder `F_BYTE_TO_USINT` führen ähnliche Konvertierungen durch, jedoch für andere Datentypen.
- `F_DWORD_TO_ULINT` ist spezialisiert auf die Umwandlung von `DWORD` zu `ULINT` und bietet keine zusätzliche Funktionalität.

## Fazit
Der `F_DWORD_TO_ULINT`-Funktionsblock ist ein einfaches und effizientes Werkzeug zur Typumwandlung in IEC 61131-3-basierten Steuerungssystemen. Seine klare Schnittstelle und direkte Funktionsweise machen ihn zu einer zuverlässigen Komponente in Automatisierungsprojekten.