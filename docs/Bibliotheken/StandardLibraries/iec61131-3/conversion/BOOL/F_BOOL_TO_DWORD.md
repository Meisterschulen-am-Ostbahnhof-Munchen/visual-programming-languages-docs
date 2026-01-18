# F_BOOL_TO_DWORD

```{index} single: F_BOOL_TO_DWORD
```

<img width="1241" height="182" alt="F_BOOL_TO_DWORD" src="https://github.com/user-attachments/assets/50cc2830-dbd7-4208-8a02-78369915f85c" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_BOOL_TO_DWORD` dient der Konvertierung eines booleschen Wertes (`BOOL`) in einen 32-Bit-unsigned-Integer-Wert (`DWORD`). Der Block ist besonders nützlich in Szenarien, wo boolesche Signale in numerische Werte umgewandelt werden müssen, beispielsweise für die Kommunikation mit Systemen, die nur numerische Eingaben verarbeiten können.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der boolesche Wert (`BOOL`), der in ein `DWORD` konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der konvertierte 32-Bit-unsigned-Integer-Wert (`DWORD`). Der Wert ist `1` (TRUE) oder `0` (FALSE).

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das Ereignis `REQ` empfangen wird. Der boolesche Wert `IN` wird in ein `DWORD` umgewandelt:
- `TRUE` wird zu `1`
- `FALSE` wird zu `0`

Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst, und der konvertierte Wert steht am Ausgang `OUT` zur Verfügung.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt und ohne Verzögerung.
- Der Block ist deterministisch und hat keine internen Zustände.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung wird bei jedem `REQ`-Ereignis neu durchgeführt.

## Anwendungsszenarien
- Umwandlung von Schaltzuständen (Ein/Aus) in numerische Steuersignale.
- Integration in Steuerungssysteme, die nur numerische Eingaben verarbeiten können.
- Protokollierung von booleschen Ereignissen als numerische Werte.

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu `F_BOOL_TO_INT` oder `F_BOOL_TO_REAL` konvertiert dieser Block spezifisch in einen `DWORD`-Typ, der für 32-Bit-Systeme optimiert ist.
- Ähnliche Blöcke wie `F_DWORD_TO_BOOL` führen die umgekehrte Konvertierung durch.

## Fazit
Der `F_BOOL_TO_DWORD`-Funktionsblock ist ein einfacher und effizienter Baustein für die Konvertierung von booleschen Werten in `DWORD`. Seine deterministische Funktionsweise und die klare Schnittstelle machen ihn zu einer zuverlässigen Komponente in Steuerungs- und Kommunikationsanwendungen.