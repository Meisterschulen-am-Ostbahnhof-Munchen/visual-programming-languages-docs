# AX_SPLIT_5

```{index} single: AX_SPLIT_5
```

<img width="705" height="370" alt="image" src="https://github.com/user-attachments/assets/cccee27c-e0ef-4c16-8e20-6ba612d866e5" />

* * * * * * * * * *

## Einleitung
Der AX_SPLIT_5 Funktionsblock ist ein generischer Baustein, der dazu dient, einen AX-Adapter in fünf separate AX-Ausgänge aufzuteilen. Der Block ermöglicht die Verteilung eines Eingangssignals auf mehrere Ausgangskanäle und findet insbesondere in Steuerungsanwendungen Verwendung, wo Signale auf verschiedene Komponenten verteilt werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine direkten Ereignis-Eingänge vorhanden (Ereignisverarbeitung erfolgt über Adapter)

### **Ereignis-Ausgänge**
Keine direkten Ereignis-Ausgänge vorhanden (Ereignisverarbeitung erfolgt über Adapter)

### **Daten-Eingänge**
Keine direkten Daten-Eingänge vorhanden

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge vorhanden

### **Adapter**
**Eingangsadapter:**
- **IN** - AX unidirektionaler Adapter (Socket)

**Ausgangsadapter:**
- **OUT1** - AX unidirektionaler Adapter (Plug)
- **OUT2** - AX unidirektionaler Adapter (Plug)
- **OUT3** - AX unidirektionaler Adapter (Plug)
- **OUT4** - AX unidirektionaler Adapter (Plug)
- **OUT5** - AX unidirektionaler Adapter (Plug)

## Funktionsweise
Der AX_SPLIT_5 Funktionsblock empfängt Signale über den Eingangsadapter IN und verteilt diese gleichzeitig auf alle fünf Ausgangsadapter (OUT1 bis OUT5). Jedes am IN-Adapter eingehende Ereignis wird parallel an alle Ausgänge weitergeleitet, wodurch eine 1:5-Verteilung realisiert wird.

## Technische Besonderheiten
- Generischer Funktionsblock mit der Klasse 'GEN_AX_SPLIT'
- Verwendet unidirektionale AX-Adapter für die Kommunikation
- Keine Datenverarbeitung oder -transformation
- Reine Ereignisverteilung ohne Verzögerung

## Zustandsübersicht
Der Block besitzt einen einfachen Zustand: Im Ruhezustand wartet er auf eingehende Ereignisse am IN-Adapter. Bei Empfang eines Ereignisses werden sofort alle fünf Ausgangsadapter aktiviert.

## Anwendungsszenarien
- Verteilung von Steuersignalen auf multiple Aktoren
- Aufteilung von Sensorwerten auf verschiedene Verarbeitungseinheiten
- Parallele Aktivierung mehrerer Subsysteme
- Signalverteilung in dezentralen Steuerungsarchitekturen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen Split-Bausteinen bietet AX_SPLIT_5 eine feste Anzahl von fünf Ausgängen. Andere Split-Varianten können unterschiedliche Ausgangszahlen oder konfigurierbare Verteilungslogiken bieten. Der Fokus liegt hier auf der einfachen, festen 1:5-Verteilung.

Vergleich mit [E_SPLIT](../../../../StandardLibraries/events/E_SPLIT.md)

## Fazit
Der AX_SPLIT_5 ist ein spezialisierter Verteilerbaustein, der durch seine einfache und deterministische Funktionsweise ideal für Anwendungen geeignet ist, bei denen ein Signal auf genau fünf Empfänger verteilt werden muss. Die Verwendung standardisierter AX-Adapter gewährleistet Kompatibilität innerhalb bestehender Steuerungssysteme.