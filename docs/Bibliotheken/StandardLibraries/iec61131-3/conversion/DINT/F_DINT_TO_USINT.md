# F_DINT_TO_USINT

```{index} single: F_DINT_TO_USINT
```

<img width="1451" height="213" alt="F_DINT_TO_USINT" src="https://github.com/user-attachments/assets/843c633e-25cf-4450-8dd4-2682e876426a" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_DINT_TO_USINT` dient der Konvertierung eines 32-Bit Ganzzahlwerts (DINT) in einen 8-Bit vorzeichenlosen Ganzzahlwert (USINT). Diese Konvertierung ist nützlich, wenn Daten zwischen Systemen oder Komponenten ausgetauscht werden müssen, die unterschiedliche Datentypen verwenden.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Dieser Ereigniseingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ereignisausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingangswert vom Typ `DINT` (32-Bit Ganzzahl), der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgangswert vom Typ `USINT` (8-Bit vorzeichenlose Ganzzahl), der das Ergebnis der Konvertierung enthält.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Auslösung des Ereigniseingangs `REQ` wird der Algorithmus ausgeführt, der den Wert am Eingang `IN` vom Typ `DINT` in einen Wert vom Typ `USINT` konvertiert und das Ergebnis am Ausgang `OUT` ausgibt. Anschließend wird der Ereignisausgang `CNF` aktiviert, um den erfolgreichen Abschluss der Konvertierung zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung erfolgt durch die eingebaute Funktion `DINT_TO_USINT`.
- Es ist zu beachten, dass bei der Konvertierung von `DINT` zu `USINT` ein möglicher Datenverlust auftreten kann, da der Wertebereich von `USINT` (0 bis 255) kleiner ist als der von `DINT` (-2.147.483.648 bis 2.147.483.647).

## Zustandsübersicht
1. **Idle-Zustand**: Der Funktionsblock wartet auf das Ereignis `REQ`.
2. **Aktiver Zustand**: Bei Empfang von `REQ` wird die Konvertierung durchgeführt und `CNF` ausgelöst.
3. **Abschlusszustand**: Nach der Konvertierung kehrt der Funktionsblock in den Idle-Zustand zurück.

## Anwendungsszenarien
- Datenkonvertierung in Steuerungssystemen, wenn unterschiedliche Datentypen verwendet werden.
- Reduzierung der Speicherbelegung, wenn nur kleine vorzeichenlose Werte benötigt werden.
- Schnittstellenanpassung zwischen verschiedenen Systemkomponenten.

## Vergleich mit ähnlichen Bausteinen
- **F_INT_TO_USINT**: Konvertiert einen 16-Bit Ganzzahlwert (INT) in einen 8-Bit vorzeichenlosen Ganzzahlwert (USINT). Im Vergleich dazu verarbeitet `F_DINT_TO_USINT` größere Eingangswerte.
- **F_LINT_TO_USINT**: Konvertiert einen 64-Bit Ganzzahlwert (LINT) in einen 8-Bit vorzeichenlosen Ganzzahlwert (USINT). `F_DINT_TO_USINT` ist für kleinere Eingangsbereiche ausgelegt.

## Fazit
Der Funktionsblock `F_DINT_TO_USINT` bietet eine einfache und effiziente Möglichkeit, 32-Bit Ganzzahlen in 8-Bit vorzeichenlose Ganzzahlen zu konvertieren. Er ist besonders nützlich in Szenarien, wo Speicherplatz optimiert oder Daten zwischen Systemen mit unterschiedlichen Datentypen ausgetauscht werden müssen. Aufgrund des möglichen Datenverlusts sollte jedoch sichergestellt werden, dass die Eingangswerte innerhalb des zulässigen Bereichs von `USINT` liegen.