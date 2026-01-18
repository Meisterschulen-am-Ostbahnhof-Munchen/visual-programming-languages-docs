# F_MIN

```{index} single: F_MIN
```

![F_MIN](https://user-images.githubusercontent.com/116869307/214145380-70470032-f41d-4e56-b478-a1a7d237ca1d.png)

* * * * * * * * * *

## Einleitung
Der F_MIN Funktionsblock ist ein Standard-Selektionsfunktionsblock gemäß IEC 61131-3, der das Minimum zweier Eingangswerte ermittelt. Der Baustein vergleicht zwei beliebige elementare Datentypen und gibt den kleineren der beiden Werte als Ergebnis zurück.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Service-Anfrage - löst die Berechnung des Minimums aus

### **Ereignis-Ausgänge**
- **CNF**: Bestätigung der angeforderten Serviceleistung - signalisiert die Beendigung der Berechnung

### **Daten-Eingänge**
- **IN1**: Eingabewert 1 (beliebiger elementarer Datentyp)
- **IN2**: Eingabewert 2 (beliebiger elementarer Datentyp)

### **Daten-Ausgänge**
- **OUT**: Minimalwert (gleicher Datentyp wie die Eingänge)

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Bei Aktivierung des REQ-Ereignisses vergleicht der F_MIN-Block die beiden Eingangswerte IN1 und IN2. Der kleinere der beiden Werte wird am Ausgang OUT ausgegeben. Gleichzeitig wird das CNF-Ereignis generiert, um den Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- Unterstützt beliebige elementare Datentypen (ANY_ELEMENTARY)
- Typsicherheit: Ausgang hat denselben Datentyp wie die Eingänge
- Echtzeitfähige Ausführung
- Einfache und deterministische Funktionsweise

## Zustandsübergänge
1. **Wartezustand**: Block wartet auf REQ-Ereignis
2. **Berechnungszustand**: Bei REQ-Ereignis werden IN1 und IN2 verglichen
3. **Ausgabezustand**: Minimalwert wird an OUT ausgegeben und CNF-Ereignis generiert
4. Rückkehr in Wartezustand

## Anwendungsszenarien
- Grenzwertüberwachung in Regelungstechnik
- Minimum-Selektion in Datenverarbeitungsketten
- Sicherheitsrelevante Begrenzungen
- Signalverarbeitung mit dynamischen Eingangswerten

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu F_MAX (Maximum-Funktion) ermittelt F_MIN den kleineren statt den größeren Wert. Beide Blöcke teilen die gleiche Schnittstellenstruktur und arbeiten mit beliebigen elementaren Datentypen.

## Fazit
Der F_MIN-Block stellt eine einfache, zuverlässige und standardkonforme Lösung zur Minimum-Bestimmung in IEC 61131-3-basierten Steuerungssystemen dar. Seine Flexibilität bezüglich der unterstützten Datentypen macht ihn zu einem universell einsetzbaren Baustein in verschiedenen Automatisierungsanwendungen.