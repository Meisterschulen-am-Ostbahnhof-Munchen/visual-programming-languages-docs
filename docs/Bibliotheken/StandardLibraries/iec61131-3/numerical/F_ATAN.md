# F_ATAN

```{index} single: F_ATAN
```

![F_ATAN](https://user-images.githubusercontent.com/116869307/214144971-bb9f4445-caa8-466d-a1dc-026d8e0a982b.png)

* * * * * * * * * *

## Einleitung
Der F_ATAN Funktionsblock berechnet den Arkustangens (Arcustangens) einer reellen Zahl. Es handelt sich um eine Standardfunktion für eine numerische Variable gemäß IEC 61131-3. Der Funktionsblock wandelt einen Tangenswert in den entsprechenden Winkel im Bogenmaß um.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Service-Anfrage - löst die Berechnung des Arkustangens aus

### **Ereignis-Ausgänge**
- **CNF**: Bestätigung der angeforderten Serviceleistung - signalisiert die Beendigung der Berechnung

### **Daten-Eingänge**
- **IN**: Eingabewert vom Typ ANY_REAL - der Tangenswert, für den der Arkustangens berechnet werden soll

### **Daten-Ausgänge**
- **OUT**: Ausgabewert vom Typ ANY_REAL - der berechnete Arkustangens-Wert im Bogenmaß

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Bei Empfang eines REQ-Ereignisses berechnet der F_ATAN Funktionsblock den Arkustangens des an IN übergebenen Wertes. Das Ergebnis wird an OUT ausgegeben und gleichzeitig wird das CNF-Ereignis generiert, um den Abschluss der Berechnung zu signalisieren.

Die Funktion berechnet den Hauptwert des Arkustangens, der im Bereich von -π/2 bis π/2 liegt.

## Technische Besonderheiten
- Unterstützt den ANY_REAL Datentyp, was verschiedene reelle Datentypen (REAL, LREAL) ermöglicht
- Einhaltung des IEC 61131-3 Standards
- Deterministisches Verhalten bei der Berechnung
- Geeignet für Echtzeitanwendungen

## Zustandsübergänge
1. **Initialzustand**: Warten auf REQ-Ereignis
2. **Berechnungszustand**: Bei REQ-Ereignis wird ATAN(IN) berechnet
3. **Ausgabezustand**: Ergebnis wird an OUT gesendet und CNF-Ereignis wird ausgelöst
4. Rückkehr zum Initialzustand

## Anwendungsszenarien
- Winkelmessung und -berechnung in Steuerungssystemen
- Koordinatentransformationen in Robotikanwendungen
- Regelungstechnik bei Positionssteuerungen
- Signalverarbeitung in mathematischen Berechnungen
- Navigation und Orientierungssysteme

## Vergleich mit ähnlichen Bausteinen
- **F_ATAN2**: Berechnet den Arkustangens von zwei Koordinaten (x,y) und liefert einen Winkel im Bereich von -π bis π
- **F_SIN/F_COS**: Trigonometrische Grundfunktionen für Sinus und Cosinus
- **F_TAN**: Berechnet den Tangens eines Winkels (Umkehrfunktion zu F_ATAN)

## Fazit
Der F_ATAN Funktionsblock bietet eine zuverlässige und standardkonforme Implementierung der Arkustangens-Funktion für Automatisierungsanwendungen. Seine einfache Schnittstelle und deterministische Funktionsweise machen ihn ideal für Echtzeitanwendungen in der Industrieautomation, wo trigonometrische Berechnungen benötigt werden.