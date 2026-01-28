# AX_BOOL_TO_X

```{index} single: AX_BOOL_TO_X
```

<img width="1151" height="231" alt="image" src="https://github.com/user-attachments/assets/d7e1acea-074c-48d3-afa2-37176d3d2d1f" />

* * * * * * * * * *

## Einleitung
Der AX_BOOL_TO_X Funktionsblock ist ein Composite-Funktionsblock, der zur Konvertierung eines BOOL-Werts in das AX-Adapterformat dient. Er ermöglicht die einfache Umwandlung von booleschen Werten in ein standardisiertes Ausgabeformat für die weitere Verarbeitung in Automatisierungssystemen.

![AX_BOOL_TO_X](AX_BOOL_TO_X.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Anfrage-Event zur Auslösung der Konvertierung

### **Ereignis-Ausgänge**
- Keine direkten Ereignis-Ausgänge vorhanden

### **Daten-Eingänge**
- **OUT**: BOOL-Eingangswert, der konvertiert werden soll

### **Daten-Ausgänge**
- Keine direkten Daten-Ausgänge vorhanden

### **Adapter**
- **AX_OUT**: Unidirektionaler AX-Adapter-Ausgang für die konvertierten Daten

## Funktionsweise
Der Funktionsblock empfängt einen booleschen Wert am Daten-Eingang OUT und wandelt diesen bei Eintreffen des REQ-Ereignisses in das AX-Adapterformat um. Die Konvertierung erfolgt automatisch und der konvertierte Wert wird über den AX_OUT-Adapter ausgegeben. Der Block fungiert als Brücke zwischen einfachen booleschen Signalen und dem standardisierten AX-Kommunikationsformat.

## Technische Besonderheiten
- Composite-Funktionsblock mit interner Vernetzung
- Verwendet unidirektionalen AX-Adapter für die Ausgabe
- Automatische Weiterleitung von Ereignissen und Daten an den Adapter
- Einfache und direkte Signalumwandlung ohne zusätzliche Logik

## Zustandsübersicht
Der Funktionsblock besitzt einen einfachen Zustandsautomaten:
1. **Wartezustand**: Wartet auf REQ-Ereignis
2. **Verarbeitungszustand**: Bei REQ-Ereignis wird der BOOL-Wert konvertiert und über den Adapter ausgegeben
3. Rückkehr in Wartezustand nach Abschluss der Konvertierung

## Anwendungsszenarien
- Integration von einfachen Schaltzuständen in komplexere AX-basierte Systeme
- Schnittstellenanpassung zwischen verschiedenen Automatisierungskomponenten
- Protokollumwandlung in verteilten Steuerungssystemen
- Einbindung von Basis-Sensoren in AX-konforme Architekturen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen Konvertierungsbausteinen zeichnet sich AX_BOOL_TO_X durch seine spezifische Ausrichtung auf das AX-Adapterformat aus. Während allgemeine Konvertierungsblöcke oft mehrere Ausgabeformate unterstützen, bietet dieser Block eine optimierte Lösung für die spezifische AX-Schnittstelle.

## Fazit
AX_BOOL_TO_X ist ein spezialisierter Konvertierungsbaustein, der eine einfache und effiziente Schnittstelle zwischen booleschen Signalen und dem AX-Adapterformat bereitstellt. Seine klare Struktur und direkte Funktionsweise machen ihn zu einer zuverlässigen Lösung für Integrationsaufgaben in Automatisierungssystemen.