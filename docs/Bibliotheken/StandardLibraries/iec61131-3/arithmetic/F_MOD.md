# F_MOD

```{index} single: F_MOD
```

![F_MOD](https://user-images.githubusercontent.com/116869307/214143235-f81abc8c-2970-409c-8626-aeb9ec537286.png)

* * * * * * * * * *

## Einführung
Der **F_MOD** ist ein arithmetischer Funktionsbaustein zur Berechnung des Divisionsrests, entwickelt unter EPL-2.0 Lizenz. Version 1.0 ermöglicht die Modulo-Operation für ganzzahlige Datentypen gemäß IEC 61131-3 Standard.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Berechnungsanforderung (mit Dividend und Divisor)

### **Ereignis-Ausgänge**
- `CNF`: Berechnungsbestätigung (mit Restwert)

### **Daten-Eingänge**
- `IN1` (ANY_INT): Dividend (ganzzahlig)
- `IN2` (ANY_INT): Divisor (ganzzahlig)

### **Daten-Ausgänge**
- `OUT` (ANY_NUM): Rest der Division (IN1 mod IN2)

## Funktionsweise

1. **Aktivierung**:
   - Durch `REQ`-Ereignis ausgelöst
   - Verarbeitet zwei ganzzahlige Werte

2. **Modulo-Operation**:
   - Berechnet IN1 modulo IN2
   - Formel: OUT = IN1 - (IN1 / IN2) * IN2
   - Unterstützte Typen: INT, DINT, UINT, UDINT

3. **Ergebnisausgabe**:
   - `CNF`-Ereignis mit Restwert
   - Vorzeichen entspricht Dividend (IN1)

## Technische Spezifikationen

✔ **Ganzzahlige Modulo-Operation**
✔ **Unterstützung für vorzeichenbehaftete und -lose Typen**
✔ **IEC 61131-3 konform**
✔ **Deterministische Ausführung**

## Anwendungsbeispiele

- **Zyklische Zählung**: Ringpuffer-Indizes
- **Zeitberechnungen**: Wochentagsbestimmung
- **Nachrichtenverarbeitung**: Prüfsummenberechnung
- **Positionierung**: Schrittmotorsteuerung

## Fehlerbehandlung

- **Division durch Null**:
  - OUT = IN1 (Originalwert bleibt erhalten)
  - Kein Abbruch der Ausführung

- **Typinkompatibilität**:
  - Automatische Typanpassung
  - Keine Exception-Generierung

## Besondere Hinweise

- **Vorzeichenbehandlung**:
  - Ergebnis hat Vorzeichen des Dividenden
  - Beispiel: (-7 mod 3) = -1

- **Performance**:
  - Optimierte Berechnung für alle ganzzahligen Typen
  - Ein Zyklus Latenzzeit

## Vergleich mit ähnlichen Bausteinen

| Merkmal        | F_MOD  | F_DIV   | F_REM   |
|----------------|--------|---------|---------|
| Operation      | Modulo | Division | Remainder |
| Eingangstypen  | ANY_INT| ANY_NUM | ANY_NUM |
| Ausgangstyp    | ANY_NUM| ANY_NUM | ANY_NUM |

## Fazit

Der F_MOD-Baustein bietet essentielle Funktionen für zyklische Berechnungen:

- Effiziente Restwertberechnung
- Flexible Typunterstützung
- Zuverlässige Fehlerbehandlung

Unverzichtbar für Steuerungsanwendungen mit periodischen Mustern oder Indexberechnungen. Die standardkonforme Implementierung ermöglicht den Einsatz in Echtzeitsystemen mit deterministischen Anforderungen.