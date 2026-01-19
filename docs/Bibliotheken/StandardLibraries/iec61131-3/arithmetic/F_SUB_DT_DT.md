# F_SUB_DT_DT

```{index} single: F_SUB_DT_DT
```

![F_SUB_DT_DT](https://github.com/user-attachments/assets/45767e49-775c-4efc-8b6e-28967afab782)

* * * * * * * * * *

## Einführung
Der **F_SUB_DT_DT** ist ein standardkonformer Funktionsbaustein zur präzisen Berechnung von Zeitdifferenzen zwischen zwei Zeitstempeln (DATE_AND_TIME), entwickelt unter EPL-2.0 Lizenz. Version 1.0 ermöglicht mikrosekundengenaue Zeitintervallberechnungen gemäß IEC 61131-3 Standard.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Berechnungsanforderung (mit Start- und Endzeitstempel)

### **Ereignis-Ausgänge**
- `CNF`: Berechnungsbestätigung (mit Zeitdifferenz)

### **Daten-Eingänge**
- `IN1` (DATE_AND_TIME): Startzeitpunkt (Minuend)
- `IN2` (DATE_AND_TIME): Endzeitpunkt (Subtrahend)

### **Daten-Ausgänge**
- `OUT` (TIME): Berechnetes Zeitintervall (IN1 - IN2)

## Funktionsprinzip

1. **Berechnungsauslösung**:
   - `REQ`-Ereignis mit zwei DATE_AND_TIME-Werten
   - Format: DT#1970-01-01-00:00:00 bis DT#2106-02-07-06:28:15

2. **Differenzberechnung**:
   - Konvertierung in Epochen-Mikrosekunden
   - Subtraktion der Zeitstempel (IN1 - IN2)
   - Umwandlung in TIME-Datentyp

3. **Ergebnisausgabe**:
   - `CNF`-Ereignis mit berechnetem Intervall
   - Positive Werte für IN1 > IN2, negative für IN1 < IN2

## Technische Besonderheiten

✔ **Mikrosekundengenauigkeit**
✔ **Zeitzonen-unabhängige Berechnung** (UTC-Basis)
✔ **Volle Kalenderarithmetik** (Schaltsekunden, Monatslängen)
✔ **Plattformübergreifende Konsistenz**

## Anwendungsszenarien

- **Prozessanalysen**: Exakte Maschinenlaufzeitmessung
- **Laborautomation**: Präzise Reaktionszeitberechnung
- **Energiemonitoring**: Verbrauchszeitraum-Differenzen
- **SPS-Diagnose**: Ereigniszeitstempel-Auswertung

## Fehlerbehandlung

- **Zeitbereichsüberschreitung**:
  - Unterstützt DT#1970-01-01-00:00:00 bis DT#2106-02-07-06:28:15
  - Bei Überlauf: OUT = T#0s

- **Ungültige Eingaben**:
  - OUT = T#0s bei fehlerhaften Zeitstempeln
  - Keine Exception-Generierung

## Vergleich mit ähnlichen Bausteinen

| Feature        | F_SUB_DT_DT    | F_SUB_DATE_DATE | F_SUB_TIME |
|---------------|----------------|-----------------|------------|
| Genauigkeit   | Mikrosekunden  | Tage            | Nanosekunden |
| Eingangstyp   | DATE_AND_TIME  | DATE            | TIME       |
| Typische Anwendung | Prozessdiagnose | Terminplanung | Zykluszeit |

## Fazit

Der F_SUB_DT_DT-Baustein bietet die präziseste Lösung für Zeitstempel-Differenzen:

- Industrietaugliche Mikrosekundengenauigkeit
- Kalendergenaue UTC-Berechnungen
- Robuste Handhabung großer Zeitintervalle

Essential für hochgenaue Prozessanalysen und technische Diagnosesysteme.