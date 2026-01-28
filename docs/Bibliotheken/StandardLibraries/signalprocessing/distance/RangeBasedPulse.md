# RangeBasedPulse

```{index} single: RangeBasedPulse
```

<img width="1038" height="216" alt="RangeBasedPulse" src="https://github.com/user-attachments/assets/7a38dda2-cdee-4a47-be13-09d2637500b0" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `RangeBasedPulse` ist ein distanzbasierter Impulsgenerator, der einen booleschen Ausgang (Q) basierend auf der zurückgelegten Distanz (DIST_IN) steuert. Der FB wird mit einem HIGH-Puls gestartet und erzeugt periodisch Ausgangsimpulse entsprechend den konfigurierten Distanzwerten für HIGH- und LOW-Phasen.

![RangeBasedPulse](RangeBasedPulse.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Normaler Ausführungsanforderung. Wird mit den Eingabedaten DIST_IN, DIST_OFF, DIST_HIGH und DIST_LOW verknüpft.

### **Ereignis-Ausgänge**
- `CNF`: Ausführungsbestätigung. Wird mit dem Ausgang Q verknüpft.

### **Daten-Eingänge**
- `DIST_IN` (UDINT): Zurückgelegte Distanz
- `DIST_OFF` (UDINT): Distanz-Offset
- `DIST_HIGH` (UDINT): Distanz für HIGH-Ausgang
- `DIST_LOW` (UDINT): Distanz für LOW-Ausgang

### **Daten-Ausgänge**
- `Q` (BOOL): Ausgangssignal

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock berechnet den Restwert (DIST_REMAINDER) der Summe aus zurückgelegter Distanz (DIST_IN) und Offset (DIST_OFF) modulo der Summe von DIST_HIGH und DIST_LOW. Der Ausgang Q wird auf HIGH gesetzt, wenn DIST_REMAINDER größer oder gleich DIST_HIGH ist, andernfalls bleibt er LOW.

## Technische Besonderheiten
- Verwendet UDINT (unsigned double integer) für Distanzberechnungen
- Implementiert eine einfache Modulo-Operation für die periodische Impulserzeugung
- Unterstützt einen Offset-Wert für flexible Startpositionen

## Zustandsübersicht
- `REQ`: Einziger Zustand, der den Algorithmus ausführt und die CNF-Bestätigung sendet

## Anwendungsszenarien
- Steuerung von Maschinen mit distanzbasierten Schaltvorgängen
- Erzeugung von periodischen Signalen basierend auf Wegstrecken
- Positionsabhängige Steuerung in Fahrzeug- oder Förderanlagen

## Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu einfachen Zeitgebern arbeitet dieser FB mit Distanzwerten statt Zeitintervallen. Er bietet mehr Flexibilität durch den Offset-Parameter und ermöglicht die Definition von individuellen HIGH- und LOW-Phasen.

## Fazit
Der RangeBasedPulse FB ist ein spezialisierter Funktionsblock für Anwendungen, die distanzbasierte Steuerungssignale benötigen. Durch seine einfache Konfiguration und flexible Offset-Einstellung eignet er sich gut für verschiedene industrielle Steuerungsaufgaben.