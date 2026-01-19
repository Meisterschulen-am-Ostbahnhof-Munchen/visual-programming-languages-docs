# F_SQRT

```{index} single: F_SQRT
```

![F_SQRT](https://user-images.githubusercontent.com/116869307/214145163-97573336-a23e-420b-88ab-99876f5083e5.png)

* * * * * * * * * *

## Einleitung
Der F_SQRT Funktionsblock ist ein Standardfunktionsblock gemäß IEC 61131-3, der die Quadratwurzel einer numerischen Eingabe berechnet. Er gehört zur Kategorie der numerischen Funktionen und dient zur mathematischen Berechnung der Quadratwurzel eines beliebigen reellen Eingabewertes.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Service-Anfrage - löst die Berechnung der Quadratwurzel aus

### **Ereignis-Ausgänge**
- **CNF**: Bestätigung der angeforderten Serviceleistung - signalisiert den Abschluss der Berechnung

### **Daten-Eingänge**
- **IN** (ANY_REAL): Eingabewert, von dem die Quadratwurzel berechnet werden soll

### **Daten-Ausgänge**
- **OUT** (ANY_REAL): Ergebnis der Quadratwurzelberechnung

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der F_SQRT Funktionsblock berechnet die Quadratwurzel des Eingabewertes IN. Bei Aktivierung durch das REQ-Ereignis wird die Berechnung durchgeführt. Nach Abschluss der Berechnung wird das CNF-Ereignis ausgelöst und das Ergebnis über die OUT-Variable ausgegeben.

## Technische Besonderheiten
- Verwendet den ANY_REAL Datentyp für maximale Flexibilität mit verschiedenen realen Zahlentypen
- Einhaltung der IEC 61131-3 Standard-Spezifikation
- Einfache und direkte Funktionalität ohne zusätzliche Parameter

## Zustandsübergänge
1. **Wartezustand**: Block wartet auf REQ-Ereignis
2. **Berechnungszustand**: Bei REQ-Ereignis wird die Quadratwurzel berechnet
3. **Ausgabezustand**: Nach Berechnung wird CNF-Ereignis ausgelöst und Ergebnis ausgegeben

## Anwendungsszenarien
- Mathematische Berechnungen in Steuerungssystemen
- Signalverarbeitung und Filterung
- Wissenschaftliche und technische Anwendungen
- Regelungstechnik und Prozesssteuerung

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen mathematischen Funktionsblöcken bietet F_SQRT eine spezialisierte Funktion für die Quadratwurzelberechnung. Andere Blöcke wie F_ADD oder F_MUL bieten grundlegende arithmetische Operationen, während F_SQRT eine spezifische mathematische Funktion bereitstellt.

## Fazit
Der F_SQRT Funktionsblock ist ein essentielles Werkzeug für numerische Berechnungen in IEC 61131-3 basierten Steuerungssystemen. Seine einfache Schnittstelle und zuverlässige Funktionalität machen ihn zu einer wertvollen Komponente für mathematische Operationen in industriellen Automatisierungslösungen.