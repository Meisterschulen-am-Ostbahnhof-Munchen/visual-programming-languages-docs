# F_SIN

```{index} single: F_SIN
```

![F_SIN](https://user-images.githubusercontent.com/116869307/214145144-c567d2d6-40d6-4df3-a9ef-5e336b6ff32f.png)

* * * * * * * * * *

## Einleitung
Der F_SIN Funktionsblock berechnet den Sinus eines Eingangswerts in Radiant. Es handelt sich um eine Standardfunktion für numerische Berechnungen gemäß IEC 61131-3, die mathematische Sinusoperationen in Steuerungsanwendungen ermöglicht.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Service-Anfrage - löst die Berechnung des Sinus aus

### **Ereignis-Ausgänge**
- **CNF**: Bestätigung der angeforderten Serviceleistung - signalisiert die Beendigung der Berechnung

### **Daten-Eingänge**
- **IN**: Eingabewert in Radiant (Typ: ANY_REAL) - der Winkel, dessen Sinus berechnet werden soll

### **Daten-Ausgänge**
- **OUT**: Ausgabewert (Typ: ANY_REAL) - das Ergebnis der Sinusberechnung

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Bei Empfang eines REQ-Ereignisses berechnet der Funktionsblock den Sinus des an IN übergebenen Wertes. Das Ergebnis wird an OUT ausgegeben und gleichzeitig wird ein CNF-Ereignis generiert, um die erfolgreiche Berechnung zu signalisieren. Die Berechnung erfolgt nach der mathematischen Standarddefinition der Sinusfunktion.

## Technische Besonderheiten
- Unterstützt den ANY_REAL Datentyp für maximale Flexibilität bei numerischen Eingaben
- Einhaltung des IEC 61131-3 Standards für Programmierbare Steuerungen
- Einfache ereignisgesteuerte Verarbeitung
- Direkte Abbildung der mathematischen Sinusfunktion

## Zustandsübergänge
Der Funktionsblock verfügt über zwei Hauptzustände:
1. **Wartezustand**: Wartet auf REQ-Ereignis
2. **Berechnungszustand**: Verarbeitet die Sinusberechnung und generiert CNF-Ereignis

## Anwendungsszenarien
- Signalverarbeitung in Regelungstechnik
- Berechnung von Schwingungen und periodischen Vorgängen
- Mathematische Transformationen in technischen Anwendungen
- Positionsberechnungen in Robotik und Motion Control

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen trigonometrischen Funktionen wie F_COS (Kosinus) oder F_TAN (Tangens) bietet F_SIN die spezifische Sinusberechnung. Gegenüber universellen mathematischen Blöcken zeichnet sich F_SIN durch seine spezialisierte und optimierte Implementierung aus.

## Fazit
Der F_SIN Funktionsblock stellt eine zuverlässige und standardkonforme Lösung für Sinusberechnungen in IEC 61131-3 basierten Steuerungssystemen dar. Seine einfache Schnittstelle und direkte Funktionalität machen ihn ideal für zahlreiche technische Anwendungen, die trigonometrische Berechnungen erfordern.