# F_BOOL_TO_BYTE

```{index} single: F_BOOL_TO_BYTE
```

<img width="1231" height="182" alt="F_BOOL_TO_BYTE" src="https://github.com/user-attachments/assets/726d9bee-c530-487f-ab01-086582dfd936" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_BOOL_TO_BYTE` dient der Konvertierung eines booleschen Wertes (`BOOL`) in einen Byte-Wert (`BYTE`). Diese Konvertierung ist nützlich, wenn boolesche Signale in Systemen verarbeitet werden müssen, die Byte-Daten erfordern.

![F_BOOL_TO_BYTE](F_BOOL_TO_BYTE.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Dieser Ereigniseingang löst die Ausführung des Funktionsblocks aus. Er ist mit dem Dateneingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Dieser Ereignisausgang signalisiert die erfolgreiche Ausführung des Funktionsblocks. Er ist mit dem Datenausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (`BOOL`): Der boolesche Eingangswert, der in ein Byte konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (`BYTE`): Der resultierende Byte-Wert nach der Konvertierung.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `BOOL` zu `BYTE` durch, sobald das Ereignis `REQ` ausgelöst wird. Der boolesche Wert `IN` wird in einen Byte-Wert umgewandelt, wobei `FALSE` zu `0` und `TRUE` zu `1` konvertiert wird. Das Ergebnis wird über den Ausgang `OUT` ausgegeben, und das Ereignis `CNF` signalisiert die erfolgreiche Ausführung.

## Technische Besonderheiten
- Der Funktionsblock ist ein einfacher Funktionsblock (`SimpleFB`) und verwendet einen ST-Algorithmus (`ST`) für die Konvertierung.
- Die Konvertierung erfolgt durch die Funktion `BOOL_TO_BYTE`, die intern den booleschen Wert in einen Byte-Wert umwandelt.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Ausführung erfolgt unmittelbar bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- **Signalverarbeitung**: Konvertierung von booleschen Steuersignalen in Byte-Werte für die Kommunikation mit Geräten, die Byte-Daten erwarten.
- **Datenprotokollierung**: Umwandlung von booleschen Statusinformationen in Byte-Format für die Speicherung oder Übertragung.

## Vergleich mit ähnlichen Bausteinen
- **F_BOOL_TO_INT**: Konvertiert einen booleschen Wert in einen Integer-Wert, während `F_BOOL_TO_BYTE` speziell für Byte-Ausgaben optimiert ist.
- **F_BOOL_TO_WORD**: Ähnlich wie `F_BOOL_TO_BYTE`, aber für größere Datenformate (Word) ausgelegt.

## Fazit
Der Funktionsblock `F_BOOL_TO_BYTE` ist ein einfaches und effizientes Werkzeug zur Konvertierung von booleschen Werten in Byte-Daten. Er eignet sich besonders für Anwendungen, die eine kompakte Darstellung von booleschen Signalen in Byte-Format erfordern. Durch seine einfache Schnittstelle und direkte Funktionsweise ist er leicht in bestehende Systeme integrierbar.