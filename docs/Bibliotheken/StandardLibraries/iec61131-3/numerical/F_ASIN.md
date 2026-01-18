# F_ASIN

```{index} single: F_ASIN
```

![F_ASIN](https://user-images.githubusercontent.com/116869307/214144951-8d3d1b57-2dd9-4f99-8fb8-5c2bbac522d2.png)

* * * * * * * * * *

## Einleitung
Der F_ASIN Funktionsblock ist ein Standard-Funktionsbaustein gemäß IEC 61131-3, der den Arkussinus (Arcussinus) einer numerischen Eingabe berechnet. Er gehört zur Kategorie der mathematischen Standardfunktionen für eine numerische Variable und liefert den Hauptwert der Arkussinus-Funktion.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Service-Anfrage - löst die Berechnung des Arkussinus aus

### **Ereignis-Ausgänge**
- **CNF**: Bestätigung der angeforderten Serviceleistung - signalisiert die Beendigung der Berechnung

### **Daten-Eingänge**
- **IN**: Eingabewert vom Typ ANY_REAL - der Wert, für den der Arkussinus berechnet werden soll

### **Daten-Ausgänge**
- **OUT**: Ausgabewert vom Typ ANY_REAL - das Ergebnis der Arkussinus-Berechnung

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der F_ASIN Funktionsblock berechnet den Arkussinus (inverse Sinusfunktion) des Eingabewertes IN. Bei Aktivierung des REQ-Ereignisses wird die Berechnung durchgeführt. Nach Abschluss der Berechnung wird das CNF-Ereignis zusammen mit dem Ergebniswert OUT ausgegeben.

Die Funktion arbeitet nach der mathematischen Definition: OUT = arcsin(IN), wobei das Ergebnis im Bereich [-π/2, π/2] Radiant liegt.

## Technische Besonderheiten
- Unterstützt den ANY_REAL Datentyp für maximale Flexibilität mit verschiedenen realen Zahlentypen
- Einhaltung des IEC 61131-3 Standards für numerische Funktionen
- Einfache ereignisgesteuerte Verarbeitung
- Liefert den Hauptwert der Arkussinus-Funktion

## Zustandsübersicht
Der Funktionsblock besitzt einen einfachen Zustandsautomaten:
1. **Wartezustand**: Wartet auf REQ-Ereignis
2. **Berechnungszustand**: Führt Arkussinus-Berechnung durch
3. **Ausgabezustand**: Sendet CNF-Ereignis mit Ergebnis

## Anwendungsszenarien
- Berechnung von Winkeln aus Sinuswerten in trigonometrischen Anwendungen
- Signalverarbeitung in Regelungstechnik und Automatisierung
- Geometrische Berechnungen in technischen Systemen
- Wissenschaftliche und ingenieurtechnische Berechnungen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen trigonometrischen Funktionen:
- F_ASIN ist die inverse Funktion zu F_SIN
- Ähnlich zu F_ACOS (Arkuskosinus) und F_ATAN (Arkustangens)
- Liefert Ergebnisse im spezifischen Wertebereich für Arkussinus

## Fazit
Der F_ASIN Funktionsblock bietet eine standardkonforme, zuverlässige Implementierung der Arkussinus-Funktion für Automatisierungsanwendungen. Seine einfache Schnittstelle und ereignisgesteuerte Verarbeitung machen ihn ideal für den Einsatz in komplexeren Steuerungsalgorithmen, die trigonometrische Berechnungen erfordern.
