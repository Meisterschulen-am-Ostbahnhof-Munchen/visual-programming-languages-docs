# FIELDBUS_WORD_TO_PERCENT

```{index} single: FIELDBUS_WORD_TO_PERCENT
```

<img width="888" height="143" alt="FIELDBUS_WORD_TO_PERCENT" src="https://github.com/user-attachments/assets/e6b552d3-4641-408d-b965-e2eb5c8cdef0" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `FIELDBUS_WORD_TO_PERCENT` konvertiert einen REAL-Wert im Bereich von 0.0 bis 100.0 in einen WORD-Wert im Bereich von 0 bis FAFF (hexadezimal). Dies ist besonders nützlich für die Signalverarbeitung in Feldbussystemen, die nach den Standards SAE J1939 und ISO 11783 arbeiten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird mit dem Daten-Eingang `WI` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Bestätigt die abgeschlossene Konvertierung. Liefert den konvertierten Wert über den Daten-Ausgang `WO`.

### **Daten-Eingänge**
- **WI** (WORD): Der Eingangswert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **WO** (WORD): Eine Spiegelung des Eingangswerts `WI`, falls das Signal gültig ist.
- **(REAL)**: Der konvertierte REAL-Wert im Bereich von 0.0 bis 100.0.

## Funktionsweise
Der Funktionsblock überprüft zunächst, ob der Eingangswert `WI` kleiner oder gleich dem definierten `VALID_SIGNAL_W` ist. Falls ja, wird der Wert gespiegelt (`WO := WI`) und anschließend in einen REAL-Wert zwischen 0.0 und 100.0 umgerechnet. Die Umrechnung erfolgt durch die Division des konvertierten WORD-Werts durch den maximalen gültigen Signalwert (`VALID_SIGNAL_W`).

## Technische Besonderheiten
- Der Block unterstützt die Standards SAE J1939 und ISO 11783.
- Die Konvertierung erfolgt nur, wenn das Eingangssignal gültig ist (`WI <= VALID_SIGNAL_W`).
- Der Ausgang `WO` dient zur Validierung des Eingangssignals.

## Zustandsübersicht
1. **Initialisierung**: Der Block wartet auf ein `REQ`-Ereignis.
2. **Verarbeitung**: Bei `REQ` wird `WI` überprüft und ggf. konvertiert.
3. **Ausgabe**: Bei erfolgreicher Konvertierung wird `CNF` ausgelöst und die Ergebnisse ausgegeben.

## Anwendungsszenarien
- Signalverarbeitung in landwirtschaftlichen Maschinen (ISO 11783).
- Steuerungssysteme in Nutzfahrzeugen (SAE J1939).
- Allgemeine Feldbuskommunikation, wo WORD- zu REAL-Konvertierungen benötigt werden.

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu generischen Konvertierungsblöcken ist `FIELDBUS_WORD_TO_PERCENT` speziell auf die Anforderungen von SAE J1939 und ISO 11783 optimiert.
- Andere Blöcke bieten möglicherweise keine direkte Spiegelung des Eingangssignals zur Validierung.

## Fazit
Der `FIELDBUS_WORD_TO_PERCENT`-Block ist ein spezialisierter Konverter für die Signalverarbeitung in Feldbussystemen. Durch seine einfache Schnittstelle und robuste Funktionsweise eignet er sich ideal für Anwendungen, die eine zuverlässige Umwandlung von WORD- zu REAL-Werten erfordern.