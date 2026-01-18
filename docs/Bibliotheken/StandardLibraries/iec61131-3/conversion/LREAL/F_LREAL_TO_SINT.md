# F_LREAL_TO_SINT

```{index} single: F_LREAL_TO_SINT
```

<img width="1453" height="214" alt="F_LREAL_TO_SINT" src="https://github.com/user-attachments/assets/033b49c4-f1c6-452a-a19e-2b4e91b60282" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LREAL_TO_SINT` dient der Konvertierung eines `LREAL`-Wertes (64-Bit Gleitkommazahl) in einen `SINT`-Wert (8-Bit Ganzahl). Diese Konvertierung ist nützlich, wenn Gleitkommazahlen in eine kompakte Ganzzahl-Darstellung umgewandelt werden müssen, z.B. für die Speicherung oder Übertragung in Systemen mit begrenzter Bandbreite.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (`LREAL`): Der Eingangswert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (`SINT`): Der konvertierte Ausgangswert.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das Ereignis `REQ` empfangen wird. Dabei wird der `LREAL`-Wert am Eingang `IN` in einen `SINT`-Wert umgewandelt und am Ausgang `OUT` ausgegeben. Das Ereignis `CNF` signalisiert den Abschluss der Konvertierung.

## Technische Besonderheiten
- Die Konvertierung erfolgt durch die Funktion `LREAL_TO_SINT`, die den `LREAL`-Wert in einen `SINT`-Wert umwandelt.
- Es handelt sich um einen einfachen Funktionsblock ohne Zustandsverwaltung oder komplexe Logik.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung wird bei jedem `REQ`-Ereignis neu ausgeführt.

## Anwendungsszenarien
- Konvertierung von Gleitkommazahlen in Ganzzahlen für die Speicherung in begrenzten Speicherbereichen.
- Verwendung in Steuerungssystemen, wo Gleitkommazahlen in kompakte Ganzzahlformate umgewandelt werden müssen.
- Integration in Datenverarbeitungsketten, wo eine Reduktion der Datenbreite erforderlich ist.

## Vergleich mit ähnlichen Bausteinen
- **F_REAL_TO_SINT**: Konvertiert `REAL` (32-Bit Gleitkommazahl) in `SINT`. Im Vergleich zu `F_LREAL_TO_SINT` wird hier eine geringere Präzision der Eingangsdaten verarbeitet.
- **F_LREAL_TO_INT**: Konvertiert `LREAL` in `INT` (16-Bit Ganzzahl). Bietet eine größere Ausgangsbreite im Vergleich zu `F_LREAL_TO_SINT`.

## Fazit
Der Funktionsblock `F_LREAL_TO_SINT` ist ein einfaches und effizientes Werkzeug zur Konvertierung von 64-Bit Gleitkommazahlen in 8-Bit Ganzzahlen. Seine einfache Schnittstelle und direkte Funktionsweise machen ihn ideal für Anwendungen, wo Platz- oder Bandbreitenbeschränkungen eine Rolle spielen.
