# AX_SPLIT_8

```{index} single: AX_SPLIT_8
```

<img width="618" height="415" alt="image" src="https://github.com/user-attachments/assets/2f54eb67-b52a-498d-b27b-6225a19450fd" />

* * * * * * * * * *
## Einleitung
Der AX_SPLIT_8 Funktionsblock ist ein generischer Baustein, der einen einzelnen AX-Adapter auf acht separate AX-Ausgänge aufteilt. Er dient zur Verteilung von Adapter-Signalen in komplexen Steuerungsarchitekturen.

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
- **IN** (Socket): AX-Adapter-Eingang vom Typ `adapter::types::unidirectional::AX`

**Ausgangsadapter:**
- **OUT1** (Plug): AX-Adapter-Ausgang 1 vom Typ `adapter::types::unidirectional::AX`
- **OUT2** (Plug): AX-Adapter-Ausgang 2 vom Typ `adapter::types::unidirectional::AX`
- **OUT3** (Plug): AX-Adapter-Ausgang 3 vom Typ `adapter::types::unidirectional::AX`
- **OUT4** (Plug): AX-Adapter-Ausgang 4 vom Typ `adapter::types::unidirectional::AX`
- **OUT5** (Plug): AX-Adapter-Ausgang 5 vom Typ `adapter::types::unidirectional::AX`
- **OUT6** (Plug): AX-Adapter-Ausgang 6 vom Typ `adapter::types::unidirectional::AX`
- **OUT7** (Plug): AX-Adapter-Ausgang 7 vom Typ `adapter::types::unidirectional::AX`
- **OUT8** (Plug): AX-Adapter-Ausgang 8 vom Typ `adapter::types::unidirectional::AX`

## Funktionsweise
Der AX_SPLIT_8 Funktionsblock verteilt eingehende Adapter-Signale vom Eingangsadapter IN gleichzeitig an alle acht Ausgangsadapter (OUT1 bis OUT8). Als unidirektionaler Adapter-Baustein leitet er alle eingehenden Ereignisse und Daten parallel an alle angeschlossenen Ausgänge weiter.

## Technische Besonderheiten
- Generischer Funktionsblock mit der generischen Klasse 'GEN_AX_SPLIT'
- Verwendet unidirektionale AX-Adapter
- Keine interne Signalverarbeitung oder -filterung
- Parallele Signalverteilung ohne Verzögerung

## Zustandsübersicht
Der Baustein besitzt keinen internen Zustand und arbeitet stateless. Alle eingehenden Signale werden sofort an alle Ausgänge weitergeleitet.

## Anwendungsszenarien
- Verteilung von Steuersignalen an multiple Aktoren
- Aufteilung von Sensorinformationen an verschiedene Verarbeitungseinheiten
- Signalverteilung in redundanten Systemarchitekturen
- Kaskadierung von Adapter-basierten Steuerungssystemen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen Split-Bausteinen bietet AX_SPLIT_8 eine feste Anzahl von acht Ausgängen und arbeitet ausschließlich auf Adapter-Ebene. Andere Split-Komponenten können variabel viele Ausgänge besitzen oder auf Daten- bzw. Ereignisebene operieren.

Vergleich mit [E_SPLIT](../../../../StandardLibraries/events/E_SPLIT.md)

## Fazit
Der AX_SPLIT_8 Funktionsblock stellt eine einfache und effiziente Lösung zur Verteilung von Adapter-Signalen in 4diac-Systemen dar. Seine feste Ausgangsanzahl von acht Ports macht ihn besonders geeignet für standardisierte Verteilungsaufgaben in industriellen Steuerungsanwendungen.
