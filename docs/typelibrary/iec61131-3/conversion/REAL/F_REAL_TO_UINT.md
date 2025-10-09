# F_REAL_TO_UINT

<img width="1440" height="213" alt="F_REAL_TO_UINT" src="https://github.com/user-attachments/assets/c70dcb74-21d4-4caa-8404-2518a95ca3b4" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_REAL_TO_UINT` dient der Konvertierung eines REAL-Wertes (Fließkommazahl) in einen UINT-Wert (vorzeichenlose Ganzzahl). Diese Konvertierung ist besonders nützlich, wenn Daten zwischen Systemen ausgetauscht werden, die unterschiedliche Datentypen verwenden oder wenn eine explizite Typumwandlung erforderlich ist.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird dieser Ereigniseingang ausgelöst, wird der Algorithmus zur Umwandlung des REAL-Wertes in einen UINT-Wert ausgeführt.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieses Ereignis wird ausgelöst, sobald der Algorithmus erfolgreich durchlaufen wurde.

### **Daten-Eingänge**
- **IN**: Der Eingangswert vom Typ REAL, der in einen UINT-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgangswert vom Typ UINT, der das Ergebnis der Konvertierung darstellt.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter-Schnittstellen.

## Funktionsweise
Der Funktionsblock `F_REAL_TO_UINT` führt bei Auslösung des `REQ`-Ereignisses die Konvertierung des REAL-Wertes am Eingang `IN` in einen UINT-Wert durch. Das Ergebnis wird am Ausgang `OUT` ausgegeben und das `CNF`-Ereignis signalisiert den erfolgreichen Abschluss der Operation.

Der zugrundeliegende Algorithmus lautet:
```ST
ALGORITHM REQ
OUT := REAL_TO_UINT(IN);
END_ALGORITHM
```

## Technische Besonderheiten
- Die Konvertierung erfolgt durch die Standardfunktion `REAL_TO_UINT`, die den REAL-Wert in den nächstgelegenen UINT-Wert rundet.
- Es ist zu beachten, dass bei Werten außerhalb des darstellbaren Bereichs von UINT (0 bis 65535) undefiniertes Verhalten auftreten kann.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo Fließkommawerte in Ganzzahlen umgewandelt werden müssen.
- Datenaufbereitung für Systeme, die nur vorzeichenlose Ganzzahlen verarbeiten können.
- Schnittstellen zwischen unterschiedlichen Systemkomponenten mit verschiedenen Datentypen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen wie `F_REAL_TO_INT` oder `F_REAL_TO_UDINT` ist dieser Funktionsblock spezialisiert auf die Umwandlung in vorzeichenlose 16-Bit-Ganzzahlen (UINT).
- Ähnliche Bausteine könnten zusätzliche Parameter wie Rundungsmodi oder Bereichsprüfungen bieten, was hier nicht der Fall ist.

## Fazit
Der `F_REAL_TO_UINT` Funktionsblock bietet eine einfache und effiziente Möglichkeit, Fließkommazahlen in vorzeichenlose Ganzzahlen umzuwandeln. Seine klare Schnittstellenstruktur und direkte Funktionsweise machen ihn ideal für Anwendungen, bei denen eine schnelle und unkomplizierte Typumwandlung benötigt wird. Bei der Verwendung ist jedoch auf den gültigen Wertebereich zu achten, um unerwartetes Verhalten zu vermeiden.
