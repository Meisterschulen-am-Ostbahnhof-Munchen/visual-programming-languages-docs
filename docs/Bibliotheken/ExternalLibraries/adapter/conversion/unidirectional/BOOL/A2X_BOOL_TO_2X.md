# A2X_BOOL_TO_2X

```{index} single: A2X_BOOL_TO_2X
```

<img width="1145" height="205" alt="image" src="https://github.com/user-attachments/assets/8248af7a-7ffe-41f8-af30-bd33f4e69bed" />

* * * * * * * * * *
## Einleitung
Der A2X_BOOL_TO_2X ist ein zusammengesetzter Funktionsblock, der zwei BOOL-Werte in ein A2X-Ausgabeformat konvertiert. Dieser Baustein dient als Brücke zwischen einfachen booleschen Steuersignalen und dem standardisierten A2X-Adapterinterface.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **E_UP**: Ereigniseingang für die Aufwärts-/Vorwärtsbewegung
- **E_DOWN**: Ereigniseingang für die Abwärts-/Rückwärtsbewegung

### **Ereignis-Ausgänge**
*Keine direkten Ereignisausgänge vorhanden*

### **Daten-Eingänge**
- **UP**: BOOL-Eingang für Aufwärts-/Vorwärtsrichtung (TRUE = vorwärts, oben, rechts, im Uhrzeigersinn)
- **DOWN**: BOOL-Eingang für Abwärts-/Rückwärtsrichtung (TRUE = rückwärts, unten, links, gegen den Uhrzeigersinn)

### **Daten-Ausgänge**
*Keine direkten Datenausgänge vorhanden*

### **Adapter**
- **A2X_OUT**: Unidirektionaler A2X-Ausgabeadapter für die Weiterleitung der konvertierten Signale

## Funktionsweise
Der Funktionsblock empfängt zwei unabhängige boolesche Eingangssignale (UP und DOWN) zusammen mit den zugehörigen Ereigniseingängen. Diese werden direkt an den A2X-Ausgabeadapter weitergeleitet, wobei die Ereignis- und Datenverbindungen parallel verarbeitet werden.

## Technische Besonderheiten
- Komplett unidirektionale Signalverarbeitung
- Direkte Durchschaltung ohne zusätzliche Logikverarbeitung
- Verwendet das standardisierte A2X-Adapterinterface
- Keine internen Zustände oder Verzögerungen

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände und arbeitet stateless. Jedes eingehende Ereignis wird sofort an den entsprechenden Adapterausgang weitergeleitet.

## Anwendungsszenarien
- Steuerung von bidirektionalen Aktoren (z.B. Motoren, Zylinder)
- Interface zwischen einfachen Schaltlogiken und komplexeren Steuerungssystemen
- Konvertierung von Taster-/Schaltersignalen in standardisierte Bewegungssignale
- Antriebssteuerungen mit Vorwärts-/Rückwärtsfunktion

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen Konvertierungsbausteinen bietet A2X_BOOL_TO_2X die spezifische Kombination aus zwei booleschen Eingängen mit einem standardisierten A2X-Interface. Andere Bausteine könnten einzelne BOOL-zu-A2X-Konvertierungen durchführen, dieser Baustein kombiniert jedoch beide Richtungen in einer einzigen Komponente.

## Fazit
Der A2X_BOOL_TO_2X ist ein spezialisierter Interface-Baustein, der eine einfache und effiziente Schnittstelle zwischen grundlegenden booleschen Steuersignalen und dem standardisierten A2X-Protokoll bereitstellt. Seine klare Struktur und direkte Durchschaltung machen ihn zu einer zuverlässigen Lösung für bidirektionale Steuerungsanwendungen.
