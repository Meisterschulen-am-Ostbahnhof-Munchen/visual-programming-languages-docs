# F_NOW

```{index} single: F_NOW
```

![F_NOW](https://github.com/user-attachments/assets/3a8b2855-6d9a-49b3-ae77-6050fb2763d9)

* * * * * * * * * *

## Einleitung
Die **F_NOW**-Funktion ist eine IEC 61499-1-konforme Hilfsfunktion zur Abfrage des aktuellen lokalen Datums und der Uhrzeit, entwickelt unter EPL-2.0 Lizenz (Version 3.0).
Die Funktion dient als Wrapper für die ST-Funktion NOW().

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Löst die Zeitabfrage aus

### **Ereignis-Ausgänge**
- `CNF`: Bestätigung der Zeitabfrage

### **Daten-Ausgänge**
| Parameter | Typ | Beschreibung | Format |
|-----------|-----|--------------|--------|
| (implizit) | DATE_AND_TIME | Aktueller Zeitstempel | DT#2025-04-14-15:30:45 |

## Funktionsweise

1. **Abfrage**:
   - `REQ` triggert die Zeitabfrage
   - Systemzeit wird in lokaler Zeitzone erfasst

2. **Ausgabe**:
   - `CNF` liefert das Ergebnis im DATE_AND_TIME-Format
   - Enthält Datum und Uhrzeit mit Sekundengenauigkeit

## Technische Besonderheiten

✔ **IEC 61499-1 konform**
✔ **Lokale Zeitzonenunterstützung** (inkl. Sommer/Winterzeit)
✔ **Einfache Integration** als NOW()-Wrapper
✔ **Eclipse 4diac Integration**

## Anwendungsszenarien

- **Protokollierung**: Zeitstempel für Ereignisse
- **Berichte**: Generierung mit Erstellungsdatum
- **Zeitgesteuerte Prozesse**: Aktuellzeitprüfung
- **Diagnose**: Zeitliche Fehleranalyse

## Beispielwerte

| Aufrufzeitpunkt | Rückgabewert |
|-----------------|--------------|
| 14.04.2025 15:30:45 | DT#2025-04-14-15:30:45 |
| 31.12.2024 23:59:59 | DT#2024-12-31-23:59:59 |

## ⚖️ Vergleich mit ähnlichen Funktionen

| Feature | F_NOW | NOW | TIME() |
|---------|-------|-----|--------|
| Rückgabetyp | DATE_AND_TIME | DATE_AND_TIME | TIME |
| Zeitzone | Lokal | Lokal | System |
| Genauigkeit | Sekunden | Sekunden | Millisekunden |
| Sommerzeit | Ja | Ja | Nein |

## Einschränkungen

⚠ **Zeitsprünge möglich** bei:
- Sommer/Winterzeit-Umstellung
- Manuellen Zeitanpassungen
- NTP-Synchronisation

## Fazit

Die F_NOW-Funktion bietet einfachen Zugriff auf die Systemzeit:

- **Praktisch**: Schnelle Integration vorhandener NOW-Funktion
- **Lokalisiert**: Automatische Zeitzonenanpassung
- **Standardkonform**: IEC-kompatible Implementierung

Idealer Einsatz bei:
- Ereignisprotokollierung
- Zeitgesteuerten Prozessen
- Diagnosefunktionen
- Berichtsgenerierung

*Die einfache Lösung für zeitkritische Anwendungen in 4diac*