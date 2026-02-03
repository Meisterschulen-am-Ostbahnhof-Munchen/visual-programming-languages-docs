# F_EXP

```{index} single: F_EXP
```

![F_EXP](https://user-images.githubusercontent.com/116869307/214145048-d4df6519-62bb-4841-bdd6-c1a7820972e3.png)

* * * * * * * * * *
## Einleitung
Der F_EXP Funktionsblock berechnet die natürliche Exponentialfunktion (e^x) für numerische Eingabewerte. Er gehört zu den Standardfunktionen für numerische Variablen nach IEC 61131-3 und wird für mathematische Berechnungen in Steuerungsanwendungen eingesetzt.

![F_EXP](F_EXP.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Service Request - Löst die Berechnung der Exponentialfunktion aus

### **Ereignis-Ausgänge**
- **CNF**: Confirmation of Requested Service - Bestätigt die erfolgreiche Berechnung

### **Daten-Eingänge**
- **IN**: ANY_REAL - Numerischer Eingabewert, für den die Exponentialfunktion berechnet werden soll

### **Daten-Ausgänge**
- **OUT**: ANY_REAL - Ergebnis der Exponentialfunktion (e^IN)

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Bei Eintreffen eines REQ-Ereignisses berechnet der F_EXP-Block die natürliche Exponentialfunktion des an IN übergebenen Wertes. Das Ergebnis wird an OUT ausgegeben und durch ein CNF-Ereignis bestätigt. Die Funktion entspricht mathematisch der Berechnung von e^x, wobei x der Eingabewert ist.

## Technische Besonderheiten
- Unterstützt den ANY_REAL Datentyp für maximale Flexibilität bei numerischen Eingaben
- Echtzeitfähige Berechnung der Exponentialfunktion
- Einfache und direkte Schnittstelle ohne zusätzliche Parameter
- Konforme Implementierung nach IEC 61131-3 Standard

## Zustandsübergänge
1. **Wartezustand**: Block wartet auf REQ-Ereignis
2. **Berechnungszustand**: Bei REQ-Ereignis wird e^IN berechnet
3. **Ausgabezustand**: Ergebnis wird an OUT gesetzt und CNF-Ereignis ausgelöst
4. Rückkehr in Wartezustand

## Anwendungsszenarien
- Mathematische Modellierung und Simulation
- Verstärkungsberechnungen in Regelungstechnik
- Wachstumsprozesse und exponentielle Entwicklungen
- Signalverarbeitung und Filterung
- Wissenschaftliche Berechnungen in industriellen Steuerungen

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen mathematischen Funktionenblöcken wie F_LN (natürlicher Logarithmus) oder F_POWER (Potenzfunktion) bietet F_EXP eine spezialisierte Implementierung für die Exponentialfunktion mit optimierter Performance. Die Verwendung von ANY_REAL ermöglicht breitere Kompatibilität als typspezifische Implementierungen.

## Fazit
Der F_EXP Funktionsblock stellt eine zuverlässige und normkonforme Implementierung der natürlichen Exponentialfunktion für industrielle Steuerungssysteme bereit. Durch seine einfache Schnittstelle und flexible Datentypunterstützung eignet er sich ideal für verschiedene mathematische Anwendungen in Automatisierungsprojekten.