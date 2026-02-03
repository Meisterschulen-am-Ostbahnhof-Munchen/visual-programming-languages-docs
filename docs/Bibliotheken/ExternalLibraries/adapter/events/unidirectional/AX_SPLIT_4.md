# AX_SPLIT_4

```{index} single: AX_SPLIT_4
```

<img width="705" height="331" alt="image" src="https://github.com/user-attachments/assets/66b5a8a2-0227-4af4-8d00-17e48bfbe98c" />

* * * * * * * * * *
## Einleitung
Der AX_SPLIT_4 Funktionsblock ist ein generischer Baustein, der einen AX-Adapter-Eingang auf vier separate AX-Adapter-Ausgänge aufteilt. Der Baustein dient als Verteiler für unidirektionale AX-Adapter und ermöglicht die Weitergabe von Daten und Ereignissen an mehrere Empfänger.

![AX_SPLIT_4](AX_SPLIT_4.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine direkten Ereignis-Eingänge vorhanden (Ereignisverarbeitung erfolgt über Adapter)

### **Ereignis-Ausgänge**
Keine direkten Ereignis-Ausgänge vorhanden (Ereignisverarbeitung erfolgt über Adapter)

### **Daten-Eingänge**
Keine direkten Daten-Eingänge vorhanden (Datenverarbeitung erfolgt über Adapter)

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge vorhanden (Datenverarbeitung erfolgt über Adapter)

### **Adapter**
**Eingangsadapter:**
- `IN` - AX-Adapter (Socket) - Empfängt unidirektionale AX-Daten und Ereignisse

**Ausgangsadapter:**
- `OUT1` - AX-Adapter (Plug) - Erster Ausgangskanal
- `OUT2` - AX-Adapter (Plug) - Zweiter Ausgangskanal
- `OUT3` - AX-Adapter (Plug) - Dritter Ausgangskanal
- `OUT4` - AX-Adapter (Plug) - Vierter Ausgangskanal

## Funktionsweise
Der AX_SPLIT_4 Block empfängt Daten und Ereignisse über den Eingangsadapter `IN` und verteilt diese parallel an alle vier Ausgangsadapter (`OUT1` bis `OUT4`). Alle eingehenden Informationen werden gleichzeitig an alle Ausgänge weitergeleitet, wodurch eine 1:4-Verteilung realisiert wird.

## Technische Besonderheiten
- Generische Implementierung für maximale Wiederverwendbarkeit
- Verwendet unidirektionale AX-Adapter für die Datenübertragung
- Keine Pufferung oder Verzögerung der Datenweitergabe
- Parallele Verteilung ohne Priorisierung der Ausgänge

## Zustandsübersicht
Der Baustein arbeitet zustandslos - eingehende Daten und Ereignisse werden sofort an alle Ausgänge weitergeleitet ohne internen Zustand zu speichern.

## Anwendungsszenarien
- Verteilung von Steuerbefehlen an mehrere Aktoren
- Broadcasting von Sensordaten an verschiedene Verarbeitungseinheiten
- Aufteilung von Steuerinformationen in verteilten Systemen
- Redundante Datenverteilung für Sicherheitsanwendungen

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen Split-Bausteinen bietet AX_SPLIT_4 eine spezifische 1:4-Aufteilung für AX-Adapter. Andere Split-Varianten könnten unterschiedliche Anzahlen von Ausgängen oder andere Adaptertypen unterstützen.

Vergleich mit [E_SPLIT](../../../../StandardLibraries/events/E_SPLIT.md)

## Fazit
Der AX_SPLIT_4 Funktionsblock bietet eine einfache und effiziente Lösung zur Verteilung von AX-Adapter-Daten auf vier parallele Ausgänge. Seine generische Natur und die Verwendung standardisierter Adapter machen ihn vielseitig einsetzbar in verschiedenen Automatisierungsanwendungen.