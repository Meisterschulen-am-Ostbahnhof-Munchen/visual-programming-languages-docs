# F_LN

```{index} single: F_LN
```

![F_LN](https://user-images.githubusercontent.com/116869307/214145086-21782799-0c9c-4cbd-9bde-286e5e78f7a6.png)

* * * * * * * * * *

## Einleitung
Der F_LN Funktionsblock berechnet den natürlichen Logarithmus (Logarithmus zur Basis e) eines numerischen Eingangswerts. Er gehört zur Kategorie der Standardfunktionen für eine numerische Variable gemäß IEC 61131-3 Standard.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Service-Anfrage - löst die Berechnung des natürlichen Logarithmus aus

### **Ereignis-Ausgänge**
- **CNF**: Bestätigung der angeforderten Serviceleistung - signalisiert den Abschluss der Berechnung

### **Daten-Eingänge**
- **IN**: Numerischer Eingangswert vom Typ ANY_REAL, für den der natürliche Logarithmus berechnet werden soll

### **Daten-Ausgänge**
- **OUT**: Berechneter natürlicher Logarithmus des Eingangswerts vom Typ ANY_REAL

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Bei Empfang eines REQ-Ereignisses berechnet der F_LN-Block den natürlichen Logarithmus (ln) des an IN übergebenen Wertes. Das Ergebnis wird an OUT ausgegeben und gleichzeitig wird das CNF-Ereignis generiert, um den erfolgreichen Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- Unterstützt den ANY_REAL Datentyp, was verschiedene numerische Datentypen wie REAL, LREAL etc. umfasst
- Implementiert gemäß IEC 61131-3 Standard für numerische Funktionen
- Echtzeitfähige Ausführung bei Ereignissteuerung

## Zustandsübersicht
Der Funktionsblock verfügt über einen einfachen Zustandsautomaten:
1. **Wartezustand**: Block wartet auf REQ-Ereignis
2. **Berechnungszustand**: Verarbeitet die Logarithmusberechnung
3. **Ausgabezustand**: Sendet CNF-Ereignis mit berechnetem Ergebnis

## Anwendungsszenarien
- Wissenschaftliche Berechnungen und mathematische Modellierung
- Signalverarbeitung und Datenanalyse
- Steuerungstechnik bei exponentiellen Prozessen
- Skalierung von Messwerten in logarithmischen Darstellungen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen mathematischen Funktionsblöcken:
- F_LN spezialisiert auf natürliche Logarithmen (Basis e)
- F_LOG berechnet Logarithmen zu beliebiger Basis
- F_EXP berechnet die Exponentialfunktion (Umkehrfunktion zu LN)
- Einfacherer Aufbau als allgemeine Logarithmus-Funktionen

## Fazit
Der F_LN Funktionsblock bietet eine effiziente und standardkonforme Implementierung zur Berechnung des natürlichen Logarithmus. Durch seine ereignisgesteuerte Architektur eignet er sich besonders für Echtzeitanwendungen, bei denen mathematische Operationen präzise und zuverlässig durchgeführt werden müssen.