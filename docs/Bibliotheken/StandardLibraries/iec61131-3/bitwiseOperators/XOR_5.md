# XOR_5

```{index} single: XOR_5
```

![XOR_5](https://user-images.githubusercontent.com/116869307/214144268-b188a2d3-cbc1-48b6-a90d-300b875efdc0.png)

* * * * * * * * * *

## Einleitung
Der XOR_5 Funktionsblock ist ein generischer Baustein zur Berechnung der bitweisen booleschen XOR-Operation mit fünf Eingängen. Er implementiert die exklusive ODER-Verknüpfung für beliebige Bit-Datentypen gemäß dem IEC 61131-3 Standard.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung - löst die Berechnung der XOR-Operation aus

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung - signalisiert den Abschluss der Berechnung

### **Daten-Eingänge**
- **IN1**: XOR Eingang 1 (ANY_BIT Datentyp)
- **IN2**: XOR Eingang 2 (ANY_BIT Datentyp)
- **IN3**: XOR Eingang 3 (ANY_BIT Datentyp)
- **IN4**: XOR Eingang 4 (ANY_BIT Datentyp)
- **IN5**: XOR Eingang 5 (ANY_BIT Datentyp)

### **Daten-Ausgänge**
- **OUT**: XOR Ergebnis (ANY_BIT Datentyp)

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Bei Eintreffen des REQ-Ereignisses führt der Funktionsblock eine bitweise XOR-Operation über alle fünf Eingangswerte durch. Das Ergebnis wird an den OUT-Ausgang ausgegeben und gleichzeitig wird das CNF-Ereignis zur Bestätigung der abgeschlossenen Berechnung generiert.

Die XOR-Operation wird nach folgendem Prinzip durchgeführt:
- Jedes Bitposition wird einzeln verarbeitet
- Das Ergebnisbit ist 1, wenn eine ungerade Anzahl der Eingangsbits an dieser Position 1 ist
- Das Ergebnisbit ist 0, wenn eine gerade Anzahl der Eingangsbits an dieser Position 1 ist

## Technische Besonderheiten
- Verwendet den generischen ANY_BIT Datentyp, der mit verschiedenen Bit-Datentypen (BOOL, BYTE, WORD, DWORD, LWORD) kompatibel ist
- Unterstützt die Verarbeitung von fünf Eingangswerten
- Implementiert als generischer Funktionsblock gemäß IEC 61131-3 Standard
- Package-Zuordnung: iec61131::bitwiseOperators

## Zustandsübersicht
Der Funktionsblock besitzt einen einfachen Zustandsautomaten:
1. **Wartezustand**: Warten auf REQ-Ereignis
2. **Berechnungszustand**: Verarbeitung der XOR-Operation
3. **Ausgabezustand**: Setzen des OUT-Wertes und Auslösen des CNF-Ereignisses

## Anwendungsszenarien
- Bitweise Datenverarbeitung in Steuerungssystemen
- Paritätsprüfungen und Fehlererkennung
- Kryptografische Operationen
- Datenmanipulation und -transformation
- Signalverarbeitung mit mehreren Eingangssignalen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu Standard-XOR-Bausteinen mit weniger Eingängen bietet XOR_5:
- Erweiterte Funktionalität mit fünf statt zwei Eingängen
- Höhere Flexibilität bei komplexeren logischen Verknüpfungen
- Reduzierte Verkettungstiefe gegenüber seriellen XOR-Verknüpfungen

## Fazit
Der XOR_5 Funktionsblock stellt eine leistungsstarke und flexible Lösung für bitweise XOR-Operationen mit fünf Eingängen dar. Seine generische Implementierung ermöglicht den Einsatz mit verschiedenen Bit-Datentypen und macht ihn zu einem vielseitigen Werkzeug für verschiedene Anwendungsbereiche in der Automatisierungstechnik.