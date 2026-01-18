# F_SUB_TOD_TOD

```{index} single: F_SUB_TOD_TOD
```

![F_SUB_TOD_TOD](https://github.com/user-attachments/assets/24f90fce-ebfe-4c5f-9449-ddf8e41a6821)

* * * * * * * * * *

## Einführung
Der **F_SUB_TOD_TOD** ist ein standardkonformer Funktionsbaustein zur Berechnung von Zeitdifferenzen zwischen zwei Tageszeiten (TIME_OF_DAY), entwickelt unter EPL-2.0 Lizenz. Version 1.0 ermöglicht präzise Tageszeitberechnungen gemäß IEC 61131-3 Standard.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Berechnungsanforderung (mit Start- und End-Tageszeit)

### **Ereignis-Ausgänge**
- `CNF`: Berechnungsbestätigung (mit Zeitdifferenz)

### **Daten-Eingänge**
- `IN1` (TIME_OF_DAY): Start-Tageszeit (TOD#hh:mm:ss)
- `IN2` (TIME_OF_DAY): End-Tageszeit

### **Daten-Ausgänge**
- `OUT` (TIME): Berechnetes Zeitintervall (IN1 - IN2)

## Funktionsprinzip

1. **Berechnungsauslösung**:
   - `REQ`-Ereignis mit zwei TIME_OF_DAY-Werten
   - Gültiger Bereich: TOD#00:00:00 bis TOD#23:59:59.999999

2. **Differenzberechnung**:
   - Umrechnung beider Werte in Sekunden seit Mitternacht
   - Differenzbildung mit 24h-Überlaufberücksichtigung
   - Ergebnis als TIME-Datentyp

3. **Ergebnisausgabe**:
   - `CNF`-Ereignis mit berechnetem Intervall
   - Positive Werte für IN1 > IN2 (innerhalb desselben Tages)
   - Negative Werte bei Tagesübergang

## Technische Besonderheiten

✔ **Mikrosekundengenauigkeit**
✔ **Automatische 24h-Überlaufbehandlung**
✔ **Bidirektionale Differenzberechnung**
✔ **Echtzeitfähige Ausführung**

## Anwendungsszenarien

- **Arbeitszeiterfassung**: Schichtdauerberechnung
- **Energiemanagement**: Lastspitzenzeiten-Analyse
- **Produktionslogistik**: Durchlaufzeitmessung
- **Gebäudeautomation**: Tageslichtnutzungszeiten

## Fehlerbehandlung

- **Sonderfälle**:
  - IN1 = IN2 → OUT = T#0s
  - Über Mitternacht: OUT = -(24h - Differenz)
  - Beispiel: TOD#01:00:00 - TOD#23:00:00 = T#-22h

- **Grenzwerte**:
  - Maximale Differenz: ±T#23:59:59.999999
  - Keine Überlaufausnahme

## Vergleich mit ähnlichen Bausteinen

| Feature        | F_SUB_TOD_TOD | F_SUB_DT_DT   | F_SUB_TIME   |
|---------------|---------------|---------------|-------------|
| Eingangstypen | TOD - TOD     | DT - DT       | TIME - TIME |
| Ausgangstyp   | TIME          | TIME          | TIME        |
| Besonderheit  | 24h-zirkulär  | Kalenderbasiert| Einfache Differenz |

## Fazit

Der F_SUB_TOD_TOD-Baustein bietet die optimale Lösung für tageszeitliche Differenzberechnungen:

- Präzise Behandlung von Tagesübergängen
- Einfache Messung von Betriebszeitintervallen
- Standardkonforme Implementierung

Besonders wertvoll für alle Anwendungen mit tageszeitabhängigen Prozessanalysen.