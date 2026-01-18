# F_TAN

```{index} single: F_TAN
```

![F_TAN](https://user-images.githubusercontent.com/116869307/214145191-77e281a6-b6e0-4ead-bc17-9638dc4fdf03.png)

* * * * * * * * * *
## Einleitung
Der F_TAN Funktionsblock berechnet den Tangens eines Eingabewertes in Radiant. Es handelt sich um eine Standardfunktion für numerische Berechnungen gemäß IEC 61131-3.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Service-Anfrage - löst die Berechnung des Tangens aus

### **Ereignis-Ausgänge**
- **CNF**: Bestätigung der angeforderten Serviceleistung - signalisiert die Beendigung der Berechnung

### **Daten-Eingänge**
- **IN**: Eingabewert in Radiant (ANY_REAL Datentyp)

### **Daten-Ausgänge**
- **OUT**: Berechneter Tangens-Wert (ANY_REAL Datentyp)

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Bei Empfang eines REQ-Ereignisses berechnet der F_TAN-Block den Tangens des an IN übergebenen Winkels in Radiant. Das Ergebnis wird an OUT ausgegeben und gleichzeitig wird das CNF-Ereignis generiert, um den Abschluss der Berechnung zu signalisieren.

## Technische Besonderheiten
- Unterstützt den ANY_REAL Datentyp für maximale Flexibilität bei numerischen Eingaben
- Berechnung erfolgt in Radiant (nicht in Grad)
- Implementiert nach IEC 61131-3 Standard für numerische Funktionen
- Mathematische Besonderheit: Bei Winkeln nahe π/2 + kπ (k ∈ ℤ) können sehr große Werte oder Überläufe auftreten

## Zustandsübergang
1. **Wartezustand**: Block wartet auf REQ-Ereignis
2. **Berechnungszustand**: Bei REQ-Ereignis wird Tangens berechnet
3. **Ausgabezustand**: Ergebnis wird an OUT gesendet und CNF-Ereignis generiert
4. Rückkehr in Wartezustand

## Anwendungsszenarien
- Trigonometrische Berechnungen in Steuerungssystemen
- Signalverarbeitung und Filterung
- Robotik und Bewegungssteuerung
- Mathematische Modellierung und Simulation
- Regelungstechnik und Positionsbestimmung

## Vergleich mit ähnlichen Bausteinen
- **F_SIN**: Berechnet Sinus statt Tangens
- **F_COS**: Berechnet Kosinus statt Tangens
- **F_ATAN**: Inverse Funktion (Arcustangens)
- **F_TAN** bietet spezifisch die Tangens-Funktion für trigonometrische Anwendungen

## Fazit
Der F_TAN Funktionsblock ist ein essentielles Element für trigonometrische Berechnungen in IEC 61131-3 basierten Steuerungssystemen. Seine einfache und standardkonforme Schnittstelle ermöglicht eine zuverlässige Integration in komplexere Steuerungsalgorithmen, insbesondere in Anwendungen, die Winkelfunktionen erfordern.
