# F_MUX_3

* * * * * * * * * *

## Einleitung
Der F_MUX_3 ist ein Multiplexer-Funktionsblock, der als Auswahlfunktion nach IEC 61131-3 Standard dient. Der Baustein ermöglicht die Auswahl eines von drei Eingangswerten basierend auf einem Steuersignal.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Service Request - Löst die Auswahloperation aus

### **Ereignis-Ausgänge**
- **CNF**: Confirmation of Requested Service - Bestätigt die abgeschlossene Auswahloperation

### **Daten-Eingänge**
- **K** (ANY_INT): Selektiert einen der n Eingänge (0, 1 oder 2)
- **IN1** (ANY): Eingangswert 1
- **IN2** (ANY): Eingangswert 2  
- **IN3** (ANY): Eingangswert 3

### **Daten-Ausgänge**
- **OUT** (ANY): Ausgabe des selektierten Eingangswerts (IN1 für K=0, IN2 für K=1, IN3 für K=2)

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Beim Eintreffen eines REQ-Ereignisses wertet der F_MUX_3 den Steuerwert K aus und leitet den entsprechenden Eingangswert an den Ausgang OUT weiter. Die Zuordnung erfolgt nach folgendem Schema:
- K = 0: OUT = IN1
- K = 1: OUT = IN2  
- K = 2: OUT = IN3

Nach erfolgreicher Auswahl wird das CNF-Ereignis generiert.

## Technische Besonderheiten
- Unterstützt beliebige Datentypen (ANY) für die Eingänge IN1, IN2, IN3 und Ausgang OUT
- Verwendet ganzzahligen Datentyp (ANY_INT) für die Steuerung K
- Garantiert typsichere Operationen durch konsistente Datentypverwendung

## Zustandsübergänge
1. **Wartezustand**: Keine aktive Operation
2. **Aktivierungszustand**: Bei REQ-Ereignis
3. **Ausführungszustand**: Auswertung von K und Auswahl des Eingangs
4. **Abschlusszustand**: Generierung von CNF mit dem selektierten Wert

## Anwendungsszenarien
- Signalweiche in Steuerungsanwendungen
- Auswahl zwischen verschiedenen Betriebsmodi
- Umschaltung zwischen verschiedenen Sensordaten
- Modulare Systeme mit konfigurierbaren Datenpfaden

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu F_MUX_2 bietet F_MUX_3 eine zusätzliche dritte Eingangsmöglichkeit, was die Flexibilität bei Auswahloperationen erhöht. Die grundlegende Funktionsweise bleibt dabei konsistent.

## Fazit
Der F_MUX_3 ist ein vielseitig einsetzbarer Multiplexer, der durch seine Unterstützung beliebiger Datentypen und die klare, intuitive Steuerung über den K-Eingang eine zuverlässige Lösung für Auswahloperationen in Automatisierungssystemen darstellt.