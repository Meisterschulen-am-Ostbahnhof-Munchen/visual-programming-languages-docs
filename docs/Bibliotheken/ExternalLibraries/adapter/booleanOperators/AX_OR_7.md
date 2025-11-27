# AX_OR_7

<img width="960" height="436" alt="image" src="https://github.com/user-attachments/assets/239ec61a-ac42-409e-9a51-94394f41ef93" />

* * * * * * * * * *
## Einleitung
Der AX_OR_7 Funktionsblock ist ein generischer Baustein zur Berechnung der booleschen ODER-Verknüpfung. Er verfügt über sieben Eingänge und berechnet das logische ODER aller Eingangssignale.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine Ereignis-Eingänge vorhanden.

### **Ereignis-Ausgänge**
Keine Ereignis-Ausgänge vorhanden.

### **Daten-Eingänge**
Keine direkten Daten-Eingänge vorhanden.

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge vorhanden.

### **Adapter**
**Eingangsadapter:**
- **IN1** - ODER Eingang 1
- **IN2** - ODER Eingang 2  
- **IN3** - ODER Eingang 3
- **IN4** - ODER Eingang 4
- **IN5** - ODER Eingang 5
- **IN6** - ODER Eingang 6
- **IN7** - ODER Eingang 7

**Ausgangsadapter:**
- **OUT** - ODER Ergebnis

Alle Adapter verwenden den Typ `adapter::types::unidirectional::AX`.

## Funktionsweise
Der Funktionsblock berechnet kontinuierlich die boolesche ODER-Verknüpfung aller sieben Eingangssignale. Das Ergebnis wird über den Ausgangsadapter OUT ausgegeben. Das Ausgangssignal ist TRUE, wenn mindestens einer der sieben Eingänge TRUE ist.

## Technische Besonderheiten
- Generischer Funktionsblock mit der Klasse 'GEN_AX_OR'
- Verwendet unidirektionale AX-Adapter für alle Schnittstellen
- Keine Ereignissteuerung - arbeitet kontinuierlich
- Sieben unabhängige Eingänge für maximale Flexibilität

## Zustandsübersicht
Da es sich um einen rein kombinatorischen Baustein ohne Ereignissteuerung handelt, besitzt der AX_OR_7 keine Zustandsmaschine. Die Ausgabe wird direkt aus den aktuellen Eingangswerten berechnet.

## Anwendungsszenarien
- Sicherheitskreise mit mehreren Not-Aus-Tastern
- Mehrfach-Bedienstationen in Maschinensteuerungen
- Überwachungssysteme mit mehreren Sensoren
- Verknüpfung mehrerer Freigabesignale

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu Standard-ODER-Bausteinen bietet AX_OR_7 die Besonderheit von sieben Eingängen, was die Verkabelung vereinfacht, da weniger Bausteine in Reihe geschaltet werden müssen. Die Verwendung von Adaptern statt direkter Datenanschlüsse ermöglicht eine flexiblere Integration in verschiedene Systemarchitekturen.

Vergleich mit [OR_7](../../../StandardLibraries/iec61131-3/bitwiseOperators/OR_7.md)

## Fazit
Der AX_OR_7 ist ein spezialisierter ODER-Baustein für Anwendungen mit vielen Eingangssignalen. Durch die sieben Eingänge und die Adapter-basierte Schnittstelle eignet er sich besonders für komplexe Steuerungsaufgaben, bei denen mehrere Signale logisch verknüpft werden müssen.
