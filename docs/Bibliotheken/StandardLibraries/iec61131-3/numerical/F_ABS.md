# F_ABS

```{index} single: F_ABS
```

![F_ABS](https://user-images.githubusercontent.com/116869307/214144890-f2f5a18b-13b5-47b4-bcf1-57e064e6dc00.png)

* * * * * * * * * *

## Einleitung
Der F_ABS Funktionsblock berechnet den absoluten Wert einer numerischen Eingabe. Er gehört zur Kategorie der Standardfunktionen für numerische Variablen gemäß IEC 61131-3 und ist Teil des iec61131::numerical Pakets.

![F_ABS](F_ABS.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Service-Anfrage - löst die Berechnung des absoluten Wertes aus

### **Ereignis-Ausgänge**
- **CNF**: Bestätigung der angeforderten Serviceleistung - signalisiert die Beendigung der Berechnung

### **Daten-Eingänge**
- **IN**: Numerische Eingabe (ANY_NUM) - der Wert, dessen absoluter Wert berechnet werden soll

### **Daten-Ausgänge**
- **OUT**: Numerische Ausgabe (ANY_NUM) - der berechnete absolute Wert der Eingabe

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Bei Empfang eines REQ-Ereignisses berechnet der F_ABS Block den absoluten Wert des an IN übergebenen numerischen Wertes. Das Ergebnis wird an OUT ausgegeben und durch ein CNF-Ereignis bestätigt. Der Block unterstützt alle numerischen Datentypen (ANY_NUM).

## Technische Besonderheiten
- Unterstützt alle numerischen Datentypen gemäß IEC 61131-3
- Einfache, deterministische Funktionsweise ohne interne Zustände
- Sofortige Berechnung bei REQ-Ereignis

## Zustandsübersicht
Der F_ABS Block besitzt keine internen Zustände. Er verhält sich rein funktional und reagiert sofort auf eingehende REQ-Ereignisse.

## Anwendungsszenarien
- Signalverarbeitung zur Entfernung von Vorzeichen
- Betragsberechnungen in mathematischen Operationen
- Verwendung in Regelungstechnik für Abstandsberechnungen
- Vorverarbeitung von Messwerten

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen mathematischen Funktionsblöcken zeichnet sich F_ABS durch seine Einfachheit und spezifische Funktionalität aus. Während Blöcke wie F_ADD oder F_MUL komplexere Operationen durchführen, konzentriert sich F_ABS ausschließlich auf die Betragsbildung.

## Fazit
Der F_ABS Funktionsblock bietet eine zuverlässige und standardkonforme Lösung zur Berechnung absoluter Werte in IEC 61131-3-basierten Steuerungssystemen. Seine einfache Schnittstelle und deterministische Funktionsweise machen ihn zu einem robusten Baustein für numerische Operationen.