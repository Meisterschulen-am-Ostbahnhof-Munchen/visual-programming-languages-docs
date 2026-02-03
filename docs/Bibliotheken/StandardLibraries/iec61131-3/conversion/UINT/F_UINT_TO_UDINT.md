# F_UINT_TO_UDINT

```{index} single: F_UINT_TO_UDINT
```

<img width="1448" height="216" alt="F_UINT_TO_UDINT" src="https://github.com/user-attachments/assets/25a7fa31-e6ae-414e-9283-52eb7ff84478" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_UINT_TO_UDINT` dient der Konvertierung eines 16-Bit vorzeichenlosen Integer-Werts (`UINT`) in einen 32-Bit vorzeichenlosen Integer-Wert (`UDINT`). Der Block ist Teil des `iec61131::conversion`-Pakets und eignet sich für Anwendungen, bei denen eine Erweiterung der Bitbreite von numerischen Werten erforderlich ist.

![F_UINT_TO_UDINT](F_UINT_TO_UDINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der zu konvertierende 16-Bit vorzeichenlose Integer-Wert (`UINT`).

### **Daten-Ausgänge**
- **OUT**: Der konvertierte 32-Bit vorzeichenlose Integer-Wert (`UDINT`).

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Auslösung des Ereigniseingangs `REQ` wird der Wert des Daten-Eingangs `IN` gelesen und direkt dem Daten-Ausgang `OUT` zugewiesen. Da `UDINT` eine größere Bitbreite als `UINT` hat, erfolgt die Konvertierung ohne Datenverlust. Anschließend wird das Ereignis `CNF` ausgelöst, um den Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung ist verlustfrei, da `UDINT` den Wertebereich von `UINT` vollständig abdeckt.
- Der Block ist deterministisch und hat keine internen Zustände.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Operation wird bei jedem `REQ`-Ereignis neu ausgeführt.

## Anwendungsszenarien
- Erweiterung der Bitbreite von Sensordaten für weitere Verarbeitung.
- Kompatibilitätssicherung zwischen Systemen, die unterschiedliche Integer-Formate verwenden.
- Vorverarbeitung von Daten für Algorithmen, die `UDINT` erfordern.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsblöcken ist `F_UINT_TO_UDINT` spezialisiert und optimiert für die spezifische Konvertierung von `UINT` zu `UDINT`.
- Andere Blöcke wie `F_INT_TO_DINT` behandeln vorzeichenbehaftete Integer, während dieser Block vorzeichenlose Werte verarbeitet.




## 🛠️ Zugehörige Übungen

* [Uebung_015](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_015.md)
* [Uebung_015a](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_015a.md)

## Fazit
Der `F_UINT_TO_UDINT`-Funktionsblock ist ein effizientes und zuverlässiges Werkzeug für die Konvertierung von 16-Bit zu 32-Bit vorzeichenlosen Integer-Werten. Seine Einfachheit und Determinismus machen ihn ideal für Echtzeitanwendungen, bei denen Leistung und Präzision kritisch sind.