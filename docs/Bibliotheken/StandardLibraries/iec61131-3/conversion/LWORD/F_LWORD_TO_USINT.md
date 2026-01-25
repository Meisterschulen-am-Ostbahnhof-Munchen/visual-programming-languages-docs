# F_LWORD_TO_USINT

```{index} single: F_LWORD_TO_USINT
```

<img width="1462" height="214" alt="F_LWORD_TO_USINT" src="https://github.com/user-attachments/assets/3e074b62-8455-47a2-93d5-a1b212894115" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LWORD_TO_USINT` dient der Konvertierung eines 64-Bit-Wertes (LWORD) in einen 8-Bit-unsigned-Integer-Wert (USINT). Diese Konvertierung ist besonders nützlich, wenn Daten aus einem größeren Wertebereich in einen kleineren, spezifischeren Bereich umgewandelt werden müssen.

![F_LWORD_TO_USINT](F_LWORD_TO_USINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Dieser Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung und liefert das Ergebnis über den Daten-Ausgang `OUT`.

### **Daten-Eingänge**
- **IN (LWORD)**: Der 64-Bit-Wert, der in einen USINT-Wert umgewandelt werden soll.

### **Daten-Ausgänge**
- **OUT (USINT)**: Der resultierende 8-Bit-unsigned-Integer-Wert nach der Konvertierung.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das Ereignis `REQ` ausgelöst wird. Der Algorithmus wandelt den 64-Bit-Eingangswert `IN` in einen 8-Bit-unsigned-Integer-Wert um und speichert das Ergebnis in `OUT`. Anschließend wird das Ereignis `CNF` ausgelöst, um den erfolgreichen Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung erfolgt durch die eingebaute Funktion `LWORD_TO_USINT`.
- Es ist zu beachten, dass bei der Konvertierung von einem größeren zu einem kleineren Datentyp Daten verloren gehen können, wenn der ursprüngliche Wert außerhalb des darstellbaren Bereichs des Zieltyps liegt.

## Zustandsübersicht
1. **Idle-Zustand**: Wartet auf das `REQ`-Ereignis.
2. **Konvertierungs-Zustand**: Führt die Konvertierung durch.
3. **Bestätigungs-Zustand**: Sendet das `CNF`-Ereignis und kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- Verarbeitung von 64-Bit-Daten, die auf 8-Bit reduziert werden müssen.
- Kommunikation zwischen Systemen mit unterschiedlichen Datenbreiten.
- Speicherplatzoptimierung in eingebetteten Systemen.

## Vergleich mit ähnlichen Bausteinen
- **F_LWORD_TO_BYTE**: Konvertiert ebenfalls LWORD in einen 8-Bit-Wert, jedoch ohne Vorzeichen (BYTE).
- **F_LWORD_TO_INT**: Konvertiert in einen 16-Bit-signed-Integer, bietet einen größeren Wertebereich, aber mit Vorzeichen.

## Fazit
Der `F_LWORD_TO_USINT` Funktionsblock ist ein einfaches und effizientes Werkzeug zur Konvertierung von 64-Bit-Daten in 8-Bit-unsigned-Integer-Werte. Er ist besonders in Szenarien nützlich, wo Speicherplatz oder Datenbandbreite begrenzt sind. Es sollte jedoch sichergestellt werden, dass die ursprünglichen Daten innerhalb des darstellbaren Bereichs des Zieltyps liegen, um Datenverluste zu vermeiden.