# F_COS

```{index} single: F_COS
```

![F_COS](https://user-images.githubusercontent.com/116869307/214145027-b4a8a395-2535-4bd6-853c-644685e13ade.png)

* * * * * * * * * *

## Einleitung
Der F_COS Funktionsblock berechnet den Kosinus eines Eingangswertes in Bogenmaß (Radiant). Es handelt sich um eine Standardfunktion für numerische Berechnungen gemäß IEC 61131-3.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Service-Anfrage - löst die Berechnung des Kosinus aus

### **Ereignis-Ausgänge**
- **CNF**: Bestätigung der angeforderten Serviceleistung - signalisiert die Beendigung der Berechnung

### **Daten-Eingänge**
- **IN**: Eingangswert in Radiant (ANY_REAL Datentyp)

### **Daten-Ausgänge**
- **OUT**: Berechneter Kosinuswert des Eingangswertes (ANY_REAL Datentyp)

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Bei Empfang eines REQ-Ereignisses berechnet der F_COS-Block den Kosinus des an IN übergebenen Wertes. Der Eingangswert wird als Winkel in Radiant interpretiert. Nach Abschluss der Berechnung wird das CNF-Ereignis zusammen mit dem Ergebnis an OUT ausgegeben.

## Technische Besonderheiten
- Unterstützt den ANY_REAL Datentyp für maximale Flexibilität
- Berechnung erfolgt in Radiant (Bogenmaß)
- Einhaltung des IEC 61131-3 Standards
- Teil des iec61131::numerical Pakets

## Zustandsübergänge
1. **Wartezustand**: Block wartet auf REQ-Ereignis
2. **Berechnungszustand**: Bei REQ-Ereignis wird Kosinus berechnet
3. **Ausgabezustand**: CNF-Ereignis mit Ergebnis wird ausgegeben
4. **Rückkehr**: Zurück in Wartezustand

## Anwendungsszenarien
- Signalverarbeitung in Regelungstechnik
- Mathematische Berechnungen in Steuerungssystemen
- Winkelfunktionen in technischen Anwendungen
- Berechnungen in Robotik und Motion Control

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen trigonometrischen Funktionen:
- F_SIN: Berechnet Sinus statt Kosinus
- F_TAN: Berechnet Tangens
- F_ACOS: Berechnet Arkuskosinus (Umkehrfunktion)

## Fazit
Der F_COS Funktionsblock bietet eine zuverlässige und standardkonforme Implementierung der Kosinus-Funktion für industrielle Steuerungssysteme. Seine einfache Schnittstelle und flexible Datentypunterstützung machen ihn ideal für verschiedene Anwendungen in der Automatisierungstechnik.