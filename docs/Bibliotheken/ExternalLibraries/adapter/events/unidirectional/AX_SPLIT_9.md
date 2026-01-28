# AX_SPLIT_9

```{index} single: AX_SPLIT_9
```

<img width="618" height="438" alt="image" src="https://github.com/user-attachments/assets/12cd00f4-dd8c-4d77-8da8-187b2aef4a83" />

* * * * * * * * * *

## Einleitung
Der AX_SPLIT_9 Funktionsblock ist ein generischer Baustein, der einen einzelnen AX-Adapter auf neun separate AX-Ausgänge aufteilt. Der Block dient als Verteiler für unidirektionale Adapterverbindungen und ermöglicht die Verteilung eines Eingangssignals auf multiple Ausgangskanäle.

![AX_SPLIT_9](AX_SPLIT_9.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*Keine direkten Ereigniseingänge vorhanden*

### **Ereignis-Ausgänge**
*Keine direkten Ereignisausgänge vorhanden*

### **Daten-Eingänge**
*Keine direkten Dateneingänge vorhanden*

### **Daten-Ausgänge**
*Keine direkten Datenausgänge vorhanden*

### **Adapter**

**Eingangsadapter:**
- `IN` - Unidirektionaler AX-Adapter (Socket)

**Ausgangsadapter:**
- `OUT1` bis `OUT9` - Neun unidirektionale AX-Adapter (Plugs)

## Funktionsweise
Der AX_SPLIT_9 Block fungiert als Adapter-Splitter, der eingehende Signale und Daten vom Eingangsadapter `IN` parallel auf alle neun Ausgangsadapter (`OUT1` bis `OUT9`) verteilt. Jeder Ausgang erhält dabei eine identische Kopie des Eingangssignals.

## Technische Besonderheiten
- Generische Implementierung für maximale Wiederverwendbarkeit
- Unidirektionale Adapterarchitektur
- Parallele Signalverteilung ohne Verzögerung
- Keine Datenverarbeitung oder -modifikation

## Zustandsübersicht
Der Funktionsblock besitzt einen einfachen Zustand: Bei Aktivierung des Eingangsadapters werden alle neun Ausgangsadapter gleichzeitig aktiviert.

## Anwendungsszenarien
- Verteilung von Steuersignalen auf multiple Aktoren
- Aufteilung von Sensorwerten auf verschiedene Verarbeitungseinheiten
- Signalverteilung in komplexen Steuerungssystemen
- Redundante Signalweiterleitung

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfacheren Splitter-Blöcken bietet AX_SPLIT_9 eine höhere Anzahl an Ausgängen (9 statt typischerweise 2-4). Gegenüber seriellen Verteilern ermöglicht er eine gleichzeitige Aktivierung aller Ausgänge ohne sequentielle Verzögerung.

Vergleich mit [E_SPLIT](../../../../StandardLibraries/events/E_SPLIT.md)

## Fazit
Der AX_SPLIT_9 Funktionsblock stellt eine effiziente Lösung für die parallele Verteilung unidirektionaler Adaptersignale dar. Seine generische Natur und die hohe Anzahl an Ausgängen machen ihn besonders geeignet für komplexe Steuerungsanwendungen, bei denen ein Signal an multiple Empfänger verteilt werden muss.