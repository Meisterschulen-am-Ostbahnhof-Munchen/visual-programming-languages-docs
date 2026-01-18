# F_BOOL_TO_DINT

```{index} single: F_BOOL_TO_DINT
```

<img width="1235" height="182" alt="F_BOOL_TO_DINT" src="https://github.com/user-attachments/assets/a1422f1d-6480-464e-9ae1-5251c70d054e" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_BOOL_TO_DINT` dient der Konvertierung eines booleschen Wertes (`BOOL`) in einen 32-Bit-Integer-Wert (`DINT`). Diese Konvertierung ist nützlich, wenn boolesche Signale in numerische Berechnungen oder Steuerungen integriert werden müssen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Bei Auslösung dieses Ereignisses wird der boolesche Eingangswert (`IN`) in einen `DINT`-Wert umgewandelt.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieses Ereignis wird zusammen mit dem konvertierten Ausgangswert (`OUT`) ausgegeben.

### **Daten-Eingänge**
- **IN**: Der boolesche Eingangswert (`BOOL`), der in einen `DINT`-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der konvertierte 32-Bit-Integer-Wert (`DINT`). Der Wert ist `1`, wenn `IN` `TRUE` ist, andernfalls `0`.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `BOOL` zu `DINT` durch, indem er den booleschen Wert `TRUE` in `1` und `FALSE` in `0` umwandelt. Die Konvertierung wird durch das Ereignis `REQ` ausgelöst und das Ergebnis wird mit dem Ereignis `CNF` bestätigt.

## Technische Besonderheiten
- Die Konvertierung erfolgt mittels der Funktion `BOOL_TO_DINT`, die im Algorithmus des Funktionsblocks implementiert ist.
- Der Funktionsblock ist einfach und deterministisch, da er keine internen Zustände oder komplexe Berechnungen beinhaltet.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Integration boolescher Signale in numerische Steuerungen.
- Umwandlung von Schaltzuständen (`TRUE`/`FALSE`) in numerische Werte für weitere Berechnungen.
- Schnittstellen zwischen booleschen und numerischen Systemkomponenten.

## Vergleich mit ähnlichen Bausteinen
- **F_BOOL_TO_INT**: Konvertiert `BOOL` in einen 16-Bit-Integer (`INT`). Im Gegensatz dazu liefert `F_BOOL_TO_DINT` einen 32-Bit-Integer.
- **F_BOOL_TO_REAL**: Konvertiert `BOOL` in einen Gleitkommawert (`REAL`). `F_BOOL_TO_DINT` liefert hingegen einen ganzzahligen Wert.

## Fazit
Der Funktionsblock `F_BOOL_TO_DINT` ist ein einfaches und effizientes Werkzeug zur Konvertierung boolescher Werte in 32-Bit-Integer. Er eignet sich besonders für Anwendungen, bei denen boolesche Signale in numerische Steuerungen integriert werden müssen. Die deterministische Funktionsweise und die klare Schnittstellenstruktur machen ihn zu einem zuverlässigen Baustein in der IEC 61499-basierten Automatisierung.
