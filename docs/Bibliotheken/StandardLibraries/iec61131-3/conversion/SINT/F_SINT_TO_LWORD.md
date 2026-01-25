# F_SINT_TO_LWORD

```{index} single: F_SINT_TO_LWORD
```

<img width="1448" height="213" alt="F_SINT_TO_LWORD" src="https://github.com/user-attachments/assets/97fc01cb-6efa-4b3f-9184-c61d04ddc8f4" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_SINT_TO_LWORD` dient der Konvertierung eines vorzeichenbehafteten 8-Bit-Integer-Werts (`SINT`) in einen vorzeichenlosen 64-Bit-Integer-Wert (`LWORD`). Dieser Baustein ist Teil des `iec61131::conversion`-Pakets und wird typischerweise in Automatisierungsanwendungen eingesetzt, wo Datentypkonvertierungen erforderlich sind.

![F_SINT_TO_LWORD](F_SINT_TO_LWORD.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ** (Normal Execution Request): Startet die Ausführung des Funktionsblocks. Wird mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF** (Execution Confirmation): Signalisiert den Abschluss der Konvertierung. Wird mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (`SINT`): Der vorzeichenbehaftete 8-Bit-Integer-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (`LWORD`): Der resultierende vorzeichenlose 64-Bit-Integer-Wert nach der Konvertierung.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `SINT` zu `LWORD` durch, sobald das Ereignis `REQ` ausgelöst wird. Die Konvertierung erfolgt mittels der integrierten Funktion `SINT_TO_LWORD`. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst, und der konvertierte Wert steht am Ausgang `OUT` zur Verfügung.

## Technische Besonderheiten
- Die Konvertierung erfolgt ohne zusätzliche Parameter oder Konfiguration.
- Der Baustein ist deterministisch und hat keine internen Zustände.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine Zustandsübergänge oder interne Zustände. Die Ausführung erfolgt unmittelbar bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Typkonvertierung in Steuerungsanwendungen, wo unterschiedliche Datentypen verarbeitet werden müssen.
- Integration in größere Funktionsblocknetzwerke, wo Daten von einem niedrigeren zu einem höheren Präzisionsformat konvertiert werden müssen.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_INT_TO_LWORD` oder `F_DINT_TO_LWORD` führen Konvertierungen von anderen Integer-Typen zu `LWORD` durch. `F_SINT_TO_LWORD` ist spezifisch für die Konvertierung von 8-Bit-Integern.
- Im Gegensatz zu generischen Konvertierungsblöcken bietet dieser Baustein eine typsichere und optimierte Lösung für die spezifische Konvertierung.

## Fazit
Der `F_SINT_TO_LWORD`-Funktionsblock bietet eine effiziente und einfache Möglichkeit, `SINT`-Werte in `LWORD`-Werte zu konvertieren. Durch seine deterministische Arbeitsweise und klare Schnittstellen eignet er sich ideal für den Einsatz in Automatisierungsprojekten, wo solche Typkonvertierungen regelmäßig benötigt werden.