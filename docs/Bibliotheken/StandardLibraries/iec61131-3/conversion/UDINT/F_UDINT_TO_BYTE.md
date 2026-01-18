# F_UDINT_TO_BYTE

```{index} single: F_UDINT_TO_BYTE
```

<img width="1454" height="212" alt="F_UDINT_TO_BYTE" src="https://github.com/user-attachments/assets/55120ea3-8221-4095-8f59-51cc6eb4207a" />

* * * * * * * * * *
## 📺 Video

* [Zusätzlich: Uebung_083: Aufwärts/Abwärts zählen: E_CTUD_UDINT Datentyp UDINT; mit Anzeige am VT.](https://www.youtube.com/watch?v=oTPDtsw5eAw)

## Einleitung
Der Funktionsblock `F_UDINT_TO_BYTE` dient der Konvertierung eines 32-Bit-unsigned-Integer-Werts (UDINT) in einen 8-Bit-unsigned-Integer-Wert (BYTE). Diese Konvertierung ist nützlich, wenn Daten zwischen Systemen mit unterschiedlichen Wortbreiten ausgetauscht werden müssen oder wenn Speicherplatz optimiert werden soll.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der zu konvertierende 32-Bit-unsigned-Integer-Wert (UDINT).

### **Daten-Ausgänge**
- **OUT**: Der resultierende 8-Bit-unsigned-Integer-Wert (BYTE) nach der Konvertierung.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, wenn das Ereignis `REQ` empfangen wird. Dabei wird der Wert am Eingang `IN` vom Typ UDINT in einen BYTE-Wert umgewandelt und am Ausgang `OUT` ausgegeben. Das Ereignis `CNF` signalisiert den erfolgreichen Abschluss der Konvertierung.

## Technische Besonderheiten
- Die Konvertierung erfolgt durch die Funktion `UDINT_TO_BYTE`, die den UDINT-Wert auf einen BYTE-Wert abbildet. Dabei kann es zu einem Datenverlust kommen, wenn der ursprüngliche Wert außerhalb des darstellbaren Bereichs eines BYTE (0 bis 255) liegt.
- Der Funktionsblock ist als einfacher Funktionsblock (SimpleFB) implementiert und verwendet einen ST-Algorithmus für die Konvertierung.

## Zustandsübersicht
1. **Idle-Zustand**: Der Funktionsblock wartet auf das Ereignis `REQ`.
2. **Konvertierungszustand**: Bei Empfang von `REQ` wird die Konvertierung durchgeführt und `CNF` ausgelöst.

## Anwendungsszenarien
- **Datenreduktion**: Wenn nur die unteren 8 Bits eines 32-Bit-Werts relevant sind.
- **Schnittstellenanpassung**: Bei der Kommunikation mit Systemen, die nur BYTE-Daten verarbeiten können.
- **Speicheroptimierung**: In Umgebungen mit begrenztem Speicherplatz.

## Vergleich mit ähnlichen Bausteinen
- **F_DINT_TO_BYTE**: Konvertiert einen 32-Bit-signed-Integer (DINT) in einen BYTE-Wert.
- **F_INT_TO_BYTE**: Konvertiert einen 16-Bit-signed-Integer (INT) in einen BYTE-Wert.
- **F_UDINT_TO_WORD**: Konvertiert einen 32-Bit-unsigned-Integer (UDINT) in einen 16-Bit-unsigned-Integer (WORD).

## Fazit
Der Funktionsblock `F_UDINT_TO_BYTE` bietet eine einfache und effiziente Möglichkeit, 32-Bit-unsigned-Integer-Werte in 8-Bit-unsigned-Integer-Werte umzuwandeln. Er ist besonders nützlich in Szenarien, bei denen Speicherplatz oder Kommunikationsbandbreite optimiert werden müssen. Beachten Sie jedoch die möglichen Datenverluste bei Werten außerhalb des BYTE-Bereichs.