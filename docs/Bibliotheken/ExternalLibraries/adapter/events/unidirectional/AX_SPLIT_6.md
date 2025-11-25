# AX_SPLIT_6

<img width="705" height="397" alt="image" src="https://github.com/user-attachments/assets/1b0e2281-e41d-47e1-bad4-9690070e18e8" />

* * * * * * * * * *
## Einleitung
Der AX_SPLIT_6 Funktionsblock ist ein generischer Baustein, der dazu dient, einen einzelnen AX-Adapter in sechs separate AX-Ausgänge aufzuteilen. Der Baustein ermöglicht die Verteilung von Signalen und Datenströmen von einer zentralen Quelle zu mehreren Verbrauchern.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*Keine direkten Ereignis-Eingänge vorhanden*

### **Ereignis-Ausgänge**
*Keine direkten Ereignis-Ausgänge vorhanden*

### **Daten-Eingänge**
*Keine direkten Daten-Eingänge vorhanden*

### **Daten-Ausgänge**
*Keine direkten Daten-Ausgänge vorhanden*

### **Adapter**
**Eingangsadapter:**
- **IN** (Socket): Empfängt die eingehenden AX-Signale vom Quellsystem

**Ausgangsadapter:**
- **OUT1** (Plug): Erster Ausgangskanal
- **OUT2** (Plug): Zweiter Ausgangskanal  
- **OUT3** (Plug): Dritter Ausgangskanal
- **OUT4** (Plug): Vierter Ausgangskanal
- **OUT5** (Plug): Fünfter Ausgangskanal
- **OUT6** (Plug): Sechster Ausgangskanal

Alle Adapter verwenden den Typ: `adapter::types::unidirectional::AX`

## Funktionsweise
Der AX_SPLIT_6 Baustein fungiert als Signalverteiler. Er empfängt Signale über den Eingangsadapter IN und leitet diese parallel an alle sechs Ausgangsadapter (OUT1 bis OUT6) weiter. Da es sich um unidirektionale AX-Adapter handelt, erfolgt die Signalübertragung nur in eine Richtung - vom Eingang zu den Ausgängen.

## Technische Besonderheiten
- Generischer Funktionsblock mit der Klasse 'GEN_AX_SPLIT'
- Verwendet unidirektionale AX-Adapter für die Kommunikation
- Keine Datenverarbeitung oder -modifikation, nur Signalverteilung
- Parallele Ausgabe an alle sechs Ausgänge

## Zustandsübersicht
Der Baustein besitzt einen einfachen Zustand:
- **Bereit**: Empfängt Signale von IN und verteilt sie an OUT1-OUT6

## Anwendungsszenarien
- Verteilung von Steuersignalen an multiple Aktoren
- Aufteilung von Sensorwerten an verschiedene Verarbeitungseinheiten
- Signalverteilung in redundanten Systemen
- Multi-Casting von Steuerbefehlen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen Splitter-Bausteinen bietet AX_SPLIT_6 eine feste Anzahl von sechs Ausgängen, was für spezifische Anwendungsfälle vorteilhaft ist. Andere Splitter können variabel mehr oder weniger Ausgänge bieten, sind aber möglicherweise komplexer in der Konfiguration.

Vergleich mit [E_SPLIT](../../../../StandardLibraries/events/E_SPLIT.md)

## Fazit
AX_SPLIT_6 ist ein spezialisierter Verteilerbaustein, der sich ideal für Anwendungen eignet, bei denen ein Signal an genau sechs Empfänger verteilt werden muss. Die einfache Struktur und die Verwendung standardisierter AX-Adapter machen ihn zu einer zuverlässigen Lösung für Signalverteilungsaufgaben in automatisierungstechnischen Systemen.
