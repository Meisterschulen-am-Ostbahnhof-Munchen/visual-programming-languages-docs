# F_USINT_TO_LWORD

```{index} single: F_USINT_TO_LWORD
```

<img width="1466" height="214" alt="F_USINT_TO_LWORD" src="https://github.com/user-attachments/assets/1a7fa270-9594-45e3-be4d-fb8e84a64db2" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_USINT_TO_LWORD` dient der Konvertierung eines `USINT`-Wertes (8-Bit unsigned integer) in einen `LWORD`-Wert (64-Bit unsigned integer). Diese Konvertierung ist nützlich, wenn Daten unterschiedlicher Bitlängen verarbeitet werden müssen, insbesondere in Systemen, die eine einheitliche Datenbreite erfordern.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird dieser Eingang ausgelöst, wird der Wert am Daten-Eingang `IN` gelesen und konvertiert.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der konvertierte Wert steht am Daten-Ausgang `OUT` zur Verfügung.

### **Daten-Eingänge**
- **IN**: Erwartet einen `USINT`-Wert (8-Bit unsigned integer), der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Liefert den konvertierten `LWORD`-Wert (64-Bit unsigned integer).

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter-Schnittstellen.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das Ereignis `REQ` ausgelöst wird. Der Algorithmus liest den Wert von `IN`, konvertiert ihn von `USINT` zu `LWORD` und stellt das Ergebnis an `OUT` bereit. Anschließend wird das `CNF`-Ereignis ausgelöst, um den erfolgreichen Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung erfolgt ohne Datenverlust, da der `USINT`-Wert in den größeren `LWORD`-Typ umgewandelt wird.
- Der Funktionsblock ist deterministisch und hat keine internen Zustände.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Ausführung erfolgt rein ereignisgesteuert durch das `REQ`-Ereignis.

## Anwendungsszenarien
- Datenkonvertierung in Steuerungssystemen, wo unterschiedliche Datenbreiten verarbeitet werden müssen.
- Integration in größere Funktionsblocknetzwerke, die eine einheitliche Datenbreite erfordern.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen (z.B. `F_INT_TO_LWORD`) ist dieser speziell für die Konvertierung von 8-Bit unsigned Integern optimiert.
- Ähnliche Bausteine könnten zusätzliche Features wie Skalierung oder Fehlerbehandlung bieten, dieser Block ist jedoch auf die reine Konvertierung beschränkt.

## Fazit
Der `F_USINT_TO_LWORD` Funktionsblock ist ein einfacher und effizienter Baustein zur Konvertierung von 8-Bit unsigned Integern in 64-Bit unsigned Integer. Seine Einfachheit und Determinismus machen ihn zu einer zuverlässigen Komponente in Steuerungssystemen.