# F_LWORD_TO_UINT

<img width="1451" height="216" alt="F_LWORD_TO_UINT" src="https://github.com/user-attachments/assets/1cbf487c-9149-449a-95ba-ada7735f19cc" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LWORD_TO_UINT` dient der Konvertierung eines `LWORD`-Datentyps in einen `UINT`-Datentyp. Dieser Baustein ist besonders nützlich in Szenarien, wo eine Typumwandlung zwischen diesen beiden Datentypen erforderlich ist, beispielsweise bei der Kommunikation zwischen Systemen mit unterschiedlichen Datenformaten.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Dieser Ereigniseingang löst die Konvertierung aus. Er ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Dieses Ereignis wird nach erfolgreicher Konvertierung ausgelöst und ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Eingangsdaten vom Typ `LWORD`, die in den `UINT`-Datentyp konvertiert werden sollen.

### **Daten-Ausgänge**
- **OUT**: Ausgangsdaten vom Typ `UINT`, die das Ergebnis der Konvertierung enthalten.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `LWORD` zu `UINT` durch, wenn das Ereignis `REQ` empfangen wird. Die Konvertierung erfolgt mittels der Funktion `LWORD_TO_UINT(IN)`, die den Wert von `IN` umwandelt und das Ergebnis an `OUT` weitergibt. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Der Funktionsblock ist ein einfacher Algorithmus (SimpleFB) und führt keine komplexen Zustandsübergänge durch.
- Die Konvertierung erfolgt direkt und ohne zusätzliche Bedingungen oder Verzögerungen.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine expliziten Zustände. Die Funktionalität beschränkt sich auf die direkte Reaktion auf das `REQ`-Ereignis mit anschließender Ausgabe des konvertierten Wertes und Auslösung des `CNF`-Ereignisses.

## Anwendungsszenarien
- Typumwandlung in Kommunikationsschnittstellen zwischen Systemen, die unterschiedliche Datentypen verwenden.
- Datenverarbeitung in Steuerungssystemen, wo eine Konvertierung von `LWORD` zu `UINT` erforderlich ist.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke könnten `F_DWORD_TO_UINT` oder `F_WORD_TO_UINT` sein, die jedoch andere Eingangsdatentypen verarbeiten.
- Der Hauptunterschied liegt im Eingangsdatentyp (`LWORD`), der eine größere Bitbreite als `DWORD` oder `WORD` aufweist.

## Fazit
Der `F_LWORD_TO_UINT` Funktionsblock bietet eine einfache und effiziente Möglichkeit, `LWORD`-Daten in den `UINT`-Datentyp umzuwandeln. Seine klare Schnittstellenstruktur und direkte Funktionsweise machen ihn zu einem nützlichen Baustein in verschiedenen Anwendungsfällen, insbesondere dort, wo Typkonvertierungen zwischen diesen Datentypen erforderlich sind.
