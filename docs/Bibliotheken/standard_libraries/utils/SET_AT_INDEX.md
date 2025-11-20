# SET_AT_INDEX

![SET_AT_INDEX](https://github.com/user-attachments/assets/258da2bc-1d8e-4fd4-88ed-21ca5161466b)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `SET_AT_INDEX` dient dazu, einen Wert an einer bestimmten Position in einem Array zu setzen. Die Datentypen des zu setzenden Wertes müssen mit dem Datentyp des Arrays übereinstimmen. Der resultierende Ausgabearray hat denselben Datentyp wie der Eingabearray.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Service-Anforderung, die das Setzen des Wertes auslöst. Wird mit den Variablen `IN_ARRAY`, `INDEX` und `VALUE` verknüpft.

### **Ereignis-Ausgänge**
- `CNF`: Bestätigung der angeforderten Serviceausführung. Wird mit den Variablen `QO` und `OUT_ARRAY` verknüpft.

### **Daten-Eingänge**
- `IN_ARRAY` (Typ: `ANY`): Der Eingabearray, in dem ein Wert gesetzt werden soll.
- `INDEX` (Typ: `UINT`): Der Index, an dem der Wert gesetzt werden soll.
- `VALUE` (Typ: `ANY`): Der Wert, der an der angegebenen Position im Array gesetzt werden soll.

### **Daten-Ausgänge**
- `QO` (Typ: `BOOL`): Qualifikator für die Ereignisausgabe, der den Erfolg oder Misserfolg der Operation anzeigt.
- `OUT_ARRAY` (Typ: `ANY`): Der resultierende Array nach dem Setzen des Wertes.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock `SET_AT_INDEX` nimmt einen Eingabearray (`IN_ARRAY`), einen Index (`INDEX`) und einen Wert (`VALUE`) entgegen. Bei Auslösung des `REQ`-Ereignisses wird der Wert `VALUE` an der Position `INDEX` im Array `IN_ARRAY` gesetzt. Das Ergebnis wird im Ausgabearray `OUT_ARRAY` ausgegeben, und das `CNF`-Ereignis wird mit dem Qualifikator `QO` bestätigt.

## Technische Besonderheiten
- Der Funktionsblock unterstützt generische Datentypen (`ANY`), was bedeutet, dass er mit verschiedenen Array-Datentypen verwendet werden kann, solange der Datentyp von `VALUE` mit dem des Arrays übereinstimmt.
- Der Index (`INDEX`) muss vom Typ `UINT` sein, um sicherzustellen, dass er eine gültige Array-Position darstellt.

## Zustandsübersicht
Der Funktionsblock hat keine expliziten Zustände. Die Operation wird bei jedem `REQ`-Ereignis ausgeführt und mit einem `CNF`-Ereignis bestätigt.

## Anwendungsszenarien
- Ändern eines bestimmten Elements in einem Array, z.B. in Datenverarbeitungs- oder Steuerungsanwendungen.
- Dynamische Aktualisierung von Array-Inhalten basierend auf Benutzereingaben oder Sensorwerten.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu einfachen Array-Operationen wie `ARRAY_ACCESS` bietet `SET_AT_INDEX` die Möglichkeit, Werte direkt im Array zu ändern, anstatt sie nur auszulesen.
- Andere ähnliche Blöcke könnten spezifischere Datentypen erfordern, während `SET_AT_INDEX` generisch ist.

## Fazit
Der `SET_AT_INDEX`-Funktionsblock ist ein vielseitiges Werkzeug zur Manipulation von Arrays in 4diac-IDE. Seine generische Natur ermöglicht die Verwendung mit verschiedenen Datentypen, während seine einfache Schnittstelle die Integration in bestehende Anwendungen erleichtert.
