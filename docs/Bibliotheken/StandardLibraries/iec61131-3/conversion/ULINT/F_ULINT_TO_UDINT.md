# F_ULINT_TO_UDINT

```{index} single: F_ULINT_TO_UDINT
```

<img width="1462" height="214" alt="F_ULINT_TO_UDINT" src="https://github.com/user-attachments/assets/15f7dfad-1b32-45df-af59-bbad295a6c11" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_ULINT_TO_UDINT` dient der Konvertierung eines 64-Bit unsigned integer Wertes (ULINT) in einen 32-Bit unsigned integer Wert (UDINT). Diese Konvertierung ist nützlich, wenn Daten zwischen Systemen oder Komponenten ausgetauscht werden, die unterschiedliche Datentypen verwenden.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Wird mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: ULINT (64-Bit unsigned integer) - Der Eingangswert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: UDINT (32-Bit unsigned integer) - Der konvertierte Ausgangswert.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt eine direkte Konvertierung eines ULINT-Wertes in einen UDINT-Wert durch. Die Konvertierung erfolgt durch den Aufruf der Funktion `ULINT_TO_UDINT` im Algorithmus `REQ`. Bei der Konvertierung wird der 64-Bit Wert auf 32-Bit gekürzt. Es ist zu beachten, dass dabei Datenverlust auftreten kann, wenn der ursprüngliche Wert größer als der maximale Wert eines UDINT ist.

## Technische Besonderheiten
- Der Funktionsblock ist einfach und hat keine internen Zustände.
- Die Konvertierung erfolgt in einem einzigen Algorithmus (`REQ`), der bei jedem Aufruf des `REQ`-Ereignisses ausgeführt wird.
- Es gibt keine Fehlerbehandlung für Überlaufbedingungen. Der Benutzer muss sicherstellen, dass der Eingabewert innerhalb des zulässigen Bereichs für UDINT liegt.

## Zustandsübersicht
Da der Funktionsblock zustandslos ist, gibt es keine Zustandsübergänge oder interne Zustände.

## Anwendungsszenarien
- Datenkonvertierung in Steuerungssystemen, wo unterschiedliche Datentypen verwendet werden.
- Reduzierung der Speicheranforderungen, wenn 64-Bit Werte nicht benötigt werden.
- Kompatibilität mit älteren Systemen, die nur 32-Bit Werte unterstützen.

## Vergleich mit ähnlichen Bausteinen
- **F_ULINT_TO_INT**: Konvertiert ULINT in INT (signed integer), wobei hier zusätzlich das Vorzeichen beachtet werden muss.
- **F_ULINT_TO_LINT**: Konvertiert ULINT in LINT (64-Bit signed integer), was keine Datenreduktion bedeutet, aber das Vorzeichen ändert.
- **F_UDINT_TO_ULINT**: Umgekehrte Konvertierung von UDINT zu ULINT, die keine Datenverluste verursacht.

## Fazit
Der `F_ULINT_TO_UDINT` Funktionsblock ist ein einfaches und effizientes Werkzeug zur Konvertierung von 64-Bit unsigned integer Werten in 32-Bit unsigned integer Werte. Er ist besonders nützlich in Szenarien, wo Speichereffizienz oder Kompatibilität mit älteren Systemen erforderlich ist. Benutzer sollten jedoch darauf achten, dass keine Überläufe auftreten, da der Baustein keine automatische Fehlerbehandlung bietet.
