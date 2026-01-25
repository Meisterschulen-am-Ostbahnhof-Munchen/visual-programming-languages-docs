# OR_4

```{index} single: OR_4
```

![OR_4](https://user-images.githubusercontent.com/116869307/214143582-4f76941e-a1fd-411f-96d2-9a28b48f8147.png)

* * * * * * * * * *

## Einleitung
Der OR_4 Funktionsblock ist ein generischer Baustein zur Berechnung der bitweisen logischen ODER-Verknüpfung mit vier Eingängen. Er führt eine bitweise ODER-Operation auf den Eingabedaten durch und gibt das Ergebnis an seinem Ausgang aus. Der Baustein ist für alle ANY_BIT Datentypen geeignet und ermöglicht somit eine flexible Verwendung mit verschiedenen Bit-Datentypen.

![OR_4](OR_4.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung - löst die Berechnung der ODER-Verknüpfung aus

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung - signalisiert die Beendigung der Berechnung

### **Daten-Eingänge**
- **IN1**: ODER-Eingang 1 (ANY_BIT)
- **IN2**: ODER-Eingang 2 (ANY_BIT)
- **IN3**: ODER-Eingang 3 (ANY_BIT)
- **IN4**: ODER-Eingang 4 (ANY_BIT)

### **Daten-Ausgänge**
- **OUT**: ODER-Ergebnis (ANY_BIT)

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Bei Eintreffen des REQ-Ereignisses führt der OR_4-Baustein eine bitweise ODER-Verknüpfung aller vier Eingänge durch. Die Operation wird für jedes Bitposition separat ausgeführt: OUT[i] = IN1[i] OR IN2[i] OR IN3[i] OR IN4[i]. Nach Abschluss der Berechnung wird das CNF-Ereignis zusammen mit dem Ergebnis ausgegeben.

## Technische Besonderheiten
- Generischer Baustein für ANY_BIT Datentypen
- Unterstützt verschiedene Bit-Datentypen (BOOL, BYTE, WORD, DWORD, LWORD)
- Bitweise Verarbeitung aller Eingänge
- Vier unabhängige Eingänge für maximale Flexibilität

## Zustandsübergang
1. **Wartezustand**: Block wartet auf REQ-Ereignis
2. **Berechnungszustand**: Bei REQ-Ereignis führt Block ODER-Berechnung durch
3. **Ausgabezustand**: Sendet CNF-Ereignis mit Ergebnis und kehrt in Wartezustand zurück

## Anwendungsszenarien
- Bitmasken-Operationen in Steuerungssystemen
- Kombination mehrerer Statusbits zu einem Gesamtstatus
- Parallele Verarbeitung mehrerer Bedingungen
- Signalverarbeitung in industriellen Automatisierungssystemen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfacheren ODER-Bausteinen mit weniger Eingängen bietet OR_4 die Möglichkeit, vier Eingänge parallel zu verarbeiten, was die Anzahl benötigter Bausteine in komplexen Schaltungen reduziert. Gegenüber Bausteinen mit festen Datentypen bietet OR_4 durch die Verwendung von ANY_BIT eine höhere Flexibilität.

## Fazit
Der OR_4 Funktionsblock ist ein vielseitiger und effizienter Baustein für bitweise ODER-Operationen mit vier Eingängen. Seine generische Natur ermöglicht den Einsatz in verschiedenen Anwendungsfällen, während die klare Ereignissteuerung eine zuverlässige Integration in komplexere Steuerungsabläufe gewährleistet.