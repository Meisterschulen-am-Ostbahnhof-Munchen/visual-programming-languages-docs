# F_USINT_TO_REAL

```{index} single: F_USINT_TO_REAL
```

<img width="1451" height="214" alt="F_USINT_TO_REAL" src="https://github.com/user-attachments/assets/f1f498f3-f7f6-48bb-9136-b03a341a2ec4" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_USINT_TO_REAL` dient der Konvertierung eines vorzeichenlosen 8-Bit-Integer-Werts (USINT) in einen 32-Bit-Gleitkommawert (REAL). Diese Konvertierung ist insbesondere in Szenarien erforderlich, in denen numerische Werte unterschiedlicher Datentypen verarbeitet oder weiterverwendet werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Ein vorzeichenloser 8-Bit-Integer-Wert (USINT), der in einen REAL-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der resultierende 32-Bit-Gleitkommawert (REAL) nach der Konvertierung.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, indem der USINT-Wert von `IN` direkt in den REAL-Datentyp umgewandelt und an `OUT` ausgegeben wird. Die Konvertierung erfolgt synchron bei Empfang des `REQ`-Ereignisses und wird durch das `CNF`-Ereignis bestätigt.

## Technische Besonderheiten
- Die Konvertierung erfolgt ohne zusätzliche Skalierung oder Rundung.
- Der Block ist für einfache Konvertierungen optimiert und bietet keine Fehlerbehandlung für ungültige Werte.

## Zustandsübersicht
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Processing**: Führt die Konvertierung durch.
3. **Completed**: Sendet das `CNF`-Ereignis und gibt den konvertierten Wert aus.

## Anwendungsszenarien
- Konvertierung von Sensorwerten (z.B. ADC-Rohdaten) in Gleitkommawerte für weitere Berechnungen.
- Integration in Steuerungssysteme, die unterschiedliche Datentypen verarbeiten müssen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsblöcken ist `F_USINT_TO_REAL` spezialisiert und daher effizienter für diese spezifische Konvertierung.
- Andere Blöcke wie `F_INT_TO_REAL` oder `F_DINT_TO_REAL` sind für andere Integer-Datentypen ausgelegt.

## Fazit
Der `F_USINT_TO_REAL`-Funktionsblock ist ein einfacher und effizienter Baustein für die Konvertierung von vorzeichenlosen 8-Bit-Integern in Gleitkommawerte. Seine Einfachheit und direkte Funktionsweise machen ihn ideal für Anwendungen, die eine schnelle und zuverlässige Typumwandlung erfordern.