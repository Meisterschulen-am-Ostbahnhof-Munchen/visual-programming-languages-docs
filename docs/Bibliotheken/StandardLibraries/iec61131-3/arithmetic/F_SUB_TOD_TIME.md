# F_SUB_TOD_TIME

```{index} single: F_SUB_TOD_TIME
```

![F_SUB_TOD_TIME](https://github.com/user-attachments/assets/6e8ab24c-c318-4a9f-916c-777af4e7be34)

* * * * * * * * * *

![F_SUB_TOD_TIME](F_SUB_TOD_TIME.svg)


## Einführung
Der **F_SUB_TOD_TIME** ist ein standardkonformer Funktionsbaustein zur Subtraktion von Zeitintervallen von Tageszeiten (TIME_OF_DAY), entwickelt unter EPL-2.0 Lizenz. Version 1.0 ermöglicht tageszeitbezogene Berechnungen gemäß IEC 61131-3 Standard.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Berechnungsanforderung (mit Tageszeit und Zeitintervall)

### **Ereignis-Ausgänge**
- `CNF`: Berechnungsbestätigung (mit korrigierter Tageszeit)

### **Daten-Eingänge**
- `IN1` (TIME_OF_DAY): Basis-Tageszeit (TOD#hh:mm:ss)
- `IN2` (TIME): Abzuziehendes Zeitintervall

### **Daten-Ausgänge**
- `OUT` (TIME_OF_DAY): Berechnete Tageszeit (IN1 - IN2)

## Funktionsprinzip

1. **Berechnungsauslösung**:
   - `REQ`-Ereignis mit TIME_OF_DAY und TIME-Wert
   - Gültiger Bereich: TOD#00:00:00 bis TOD#23:59:59.999999

2. **Zeitpunktberechnung**:
   - Umrechnung in Sekunden seit Mitternacht
   - Subtraktion des Zeitintervalls
   - Tageszeitliche Rückrechnung mit Überlaufbehandlung

3. **Ergebnisausgabe**:
   - `CNF`-Ereignis mit neuer Tageszeit
   - Automatischer 24h-Überlauf (zirkuläre Berechnung)

## Technische Besonderheiten

✔ **Mikrosekundengenauigkeit**
✔ **24h-Überlaufbehandlung** (zirkuläre Tageszeit)
✔ **Negative Intervalle** (Addition von Zeit)
✔ **Echtzeitfähige Berechnung**

## Anwendungsszenarien

- **Schichtplanung**: Arbeitsbeginn berechnen
- **Lichtsteuerung**: Sonnenaufgangszeiten korrigieren
- **Produktionsplanung**: Maschinenlaufzeiten rückrechnen
- **Verkehrsleitsysteme**: Fahrplananpassungen

## Fehlerbehandlung

- **Überlaufbehandlung**:
  - Bei Überschreitung: zirkuläre Berechnung (modulo 24h)
  - Beispiel: TOD#01:00:00 - T#2h = TOD#23:00:00

- **Sonderfälle**:
  - IN2 = T#0s → OUT = IN1
  - IN2 negativ → Addition der Zeit (TOD#10:00 + T#-2h = TOD#12:00)

## Vergleich mit ähnlichen Bausteinen

| Feature        | F_SUB_TOD_TIME | F_ADD_TOD_TIME | F_SUB_DT_TIME |
|---------------|----------------|----------------|---------------|
| Operation     | Tageszeit - Intervall | Tageszeit + Intervall | Zeitstempel - Intervall |
| Ergebnis      | TIME_OF_DAY    | TIME_OF_DAY    | DATE_AND_TIME |
| Überlauf      | Zirkulär 24h   | Zirkulär 24h   | Kalenderbasiert |

## Fazit

Der F_SUB_TOD_TIME-Baustein bietet eine optimierte Lösung für tageszeitliche Berechnungen:

- Präzise zirkuläre Zeitrechnung
- Einfache Handhabung von Schicht- und Betriebszeiten
- Intuitive Behandlung von Tagesübergängen

Ideale Wahl für alle Anwendungen mit tageszeitabhängigen Steuerungen.