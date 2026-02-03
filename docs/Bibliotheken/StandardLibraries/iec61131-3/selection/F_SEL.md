# F_SEL

```{index} single: F_SEL
```

![image](https://user-images.githubusercontent.com/69573151/210802734-9caf89bd-f437-43d3-8ed5-294c89df8c3d.png)

<https://content.helpme-codesys.com/en/CODESYS%20Development%20System/_cds_operator_sel.html>

* * * * * * * * * *

## Einleitung
Der F_SEL Funktionsblock ist ein binärer Selektor gemäß IEC 61131-3 Standard. Er ermöglicht die Auswahl zwischen zwei Eingangswerten basierend auf einem Steuersignal. Der Baustein dient zur bedingten Datenauswahl in Steuerungsanwendungen.

![F_SEL](F_SEL.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Service-Anfrage - löst die Auswahloperation aus

### **Ereignis-Ausgänge**
- **CNF**: Bestätigung der angeforderten Service-Operation

### **Daten-Eingänge**
- **G**: Selektor (BOOL) - Steuersignal für die Auswahl
- **IN0**: Auswählbare Eingangsvariable (ANY) - Erster Eingang
- **IN1**: Auswählbare Eingangsvariable (ANY) - Zweiter Eingang

### **Daten-Ausgänge**
- **OUT**: Ausgewählter Eingang (ANY) - Ergebnis der Selektion

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Bei Eintreffen eines REQ-Ereignisses wertet der F_SEL-Block den Selektor-Eingang G aus:
- Wenn G = FALSE (0): OUT wird auf den Wert von IN0 gesetzt
- Wenn G = TRUE (1): OUT wird auf den Wert von IN1 gesetzt

Nach Abschluss der Auswahloperation wird das CNF-Ereignis mit dem berechneten Ausgangswert ausgegeben.

## Technische Besonderheiten
- Verwendet generische Datentypen (ANY) für die Ein- und Ausgänge IN0, IN1 und OUT
- Ermöglicht damit die Verarbeitung verschiedener Datentypen
- Echtzeitfähige Ausführung bei Ereignisauslösung
- Einfache und deterministische Funktionsweise

## Zustandsübergänge
1. **Warte-Zustand**: Block wartet auf REQ-Ereignis
2. **Ausführungs-Zustand**: Bei REQ-Ereignis erfolgt Auswertung von G und Datenauswahl
3. **Ausgabe-Zustand**: CNF-Ereignis mit Ergebnis wird ausgegeben, Rückkehr in Warte-Zustand

## Anwendungsszenarien
- Umschaltung zwischen zwei Sensoren oder Messwerten
- Auswahl zwischen verschiedenen Betriebsmodi
- Bedingte Datenweiterleitung in Prozessketten
- Implementierung von Multiplexer-Funktionalität

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen Selektionsbausteinen bietet F_SEL:
- Einfache binäre Auswahl (nur zwei Eingänge)
- Flexible Typunterstützung durch ANY-Datentyp
- Standardisierte Ereignissteuerung gemäß IEC 61131-3




## Zugehörige Übungen

* [Uebung_015](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_015.md)
* [Uebung_016](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_016.md)
* [Uebung_060](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_060.md)

## Fazit
Der F_SEL-Block stellt eine grundlegende und vielseitige Selektionsfunktion für Steuerungsanwendungen bereit. Seine einfache Struktur und die flexible Typunterstützung machen ihn zu einem wertvollen Baustein für verschiedene Auswahl- und Umschaltaufgaben in industriellen Automatisierungssystemen.