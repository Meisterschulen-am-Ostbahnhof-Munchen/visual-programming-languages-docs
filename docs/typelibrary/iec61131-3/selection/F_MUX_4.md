# F_MUX_4

* * * * * * * * * *

## Einleitung
Der F_MUX_4 ist ein Multiplexer-Funktionsblock gemäß IEC 61131-3 Standard, der als Auswahlfunktion dient. Er ermöglicht die Selektion eines von vier Eingangswerten basierend auf einem Steuersignal und gibt den ausgewählten Wert am Ausgang weiter.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Service-Anfrage - löst die Auswahloperation aus

### **Ereignis-Ausgänge**
- **CNF**: Bestätigung der angeforderten Service-Operation

### **Daten-Eingänge**
- **K** (ANY_INT): Selektionsindex - wählt den gewünschten Eingang (0-3)
- **IN1** (ANY): Eingangswert 1
- **IN2** (ANY): Eingangswert 2  
- **IN3** (ANY): Eingangswert 3
- **IN4** (ANY): Eingangswert 4

### **Daten-Ausgänge**
- **OUT** (ANY): Ausgangswert - enthält den selektierten Eingangswert

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Beim Eintreffen eines REQ-Ereignisses wertet der Funktionsblock den Selektionsindex K aus und leitet den entsprechenden Eingangswert an den Ausgang OUT weiter. Die Zuordnung erfolgt wie folgt:
- K = 0: OUT = IN1
- K = 1: OUT = IN2  
- K = 2: OUT = IN3
- K = 3: OUT = IN4

Nach erfolgreicher Auswahl wird das CNF-Ereignis ausgelöst, um den Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- Unterstützt beliebige Datentypen (ANY) für die Eingangs- und Ausgangswerte
- Der Selektionsindex K muss ein ganzzahliger Typ sein (ANY_INT)
- Robuste Fehlerbehandlung bei ungültigen K-Werten (außerhalb 0-3) ist implementiert
- Echtzeitfähige Ausführung

## Zustandsübersicht
Der Funktionsblock besitzt einen einfachen Zustandsautomaten:
1. **Wartezustand**: Keine aktive Operation
2. **Verarbeitungszustand**: Bei REQ-Ereignis - Auswertung von K und Selektion des Eingangs
3. **Ausgabezustand**: Setzen von OUT und Auslösen von CNF

## Anwendungsszenarien
- Signalrouting in Steuerungssystemen
- Auswahl zwischen verschiedenen Sensordaten
- Multiplexing von Kommunikationskanälen
- Umschaltung zwischen Betriebsmodi
- Datenverteilung in verteilten Systemen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu F_MUX_3 bietet F_MUX_4 einen zusätzlichen Eingang (IN4), was die Flexibilität erhöht. Gegenüber manuellen CASE- oder IF-Anweisungen in ST bietet der Baustein eine standardisierte, wiederverwendbare Lösung mit klarer Schnittstellendefinition.

## Fazit
Der F_MUX_4 ist ein zuverlässiger und vielseitiger Multiplexer-Baustein, der sich ideal für Anwendungen eignet, bei zwischen mehreren Eingangssignalen umgeschaltet werden muss. Seine Standardkonformität und klare Schnittstellendefinition machen ihn zu einer praktischen Lösung für zahlreiche Steuerungsaufgaben.