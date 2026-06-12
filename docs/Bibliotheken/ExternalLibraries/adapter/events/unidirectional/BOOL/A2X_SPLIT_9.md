# A2X_SPLIT_9


![A2X_SPLIT_9](./A2X_SPLIT_9.svg)

* * * * * * * * * *
## Einleitung
Der **A2X_SPLIT_9** ist ein generischer Funktionsblock, der einen eingehenden A2X-Adapter (Socket) auf neun separate A2X-Ausgangsadapter (Plugs) aufteilt. Er ermöglicht die sternförmige Verteilung eines A2X-Signals an bis zu neun unabhängige Empfänger, ohne dass eine eigene Logik oder Zustandsautomaten erforderlich sind.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine

### **Ereignis-Ausgänge**
Keine

### **Daten-Eingänge**
Keine

### **Daten-Ausgänge**
Keine

### **Adapter**
| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| Socket | IN | Eingang | Eingehender A2X-Adapter, dessen Signale auf die neun Ausgänge verteilt werden. |
| Plug | OUT1 … OUT9 | Ausgang | Neun gleichartige A2X-Ausgangsadapter, die die Daten des Eingangs weiterleiten. |

## Funktionsweise
Der Funktionsblock besitzt keinerlei interne Logik oder Zustandsautomaten. Er fungiert als reine „Verdrahtungshilfe“ in der 4diac-IDE: Der am Socket **IN** anliegende A2X-Adapter wird unverändert und parallel an alle neun Plugs **OUT1** bis **OUT9** weitergegeben. Somit erhalten alle angeschlossenen Empfänger identische Signale wie der Eingang.

## Technische Besonderheiten
- **Generischer Baustein**: Der FB ist als generisch deklariert (Attribut `GenericClassName` = `'GEN_A2X_SPLIT'`). In der IDE kann er für verschiedene konkrete A2X-Adaptertypen parametrisiert werden.
- **Keine Laufzeitlogik**: Der FB enthält keine ECC (Execution Control Chart) und keine Algorithmen – die gesamte Funktionalität wird durch die interne Verbindung der Adapter realisiert.
- **Unidirektionale Adapter**: Die verwendeten Adapter `adapter::types::unidirectional::A2X` erlauben nur eine Datenflussrichtung (vom Socket zu den Plugs).

## Zustandsübersicht
Eine Zustandsübersicht entfällt, da der Baustein keinen internen Zustand besitzt. Der Datenfluss erfolgt kontinuierlich und ohne Steuerung durch Ereignisse.

## Anwendungsszenarien
- **Signalverteilung in der Automatisierung**: Verteilen eines analogen oder binären A2X-Signals an mehrere Aktoren oder übergeordnete Steuerungen.
- **Test- und Simulationsaufbauten**: Einspeisen eines Referenzsignals in mehrere parallele Prüfpfade.
- **Topologieumsetzung**: Sternförmige Verkabelung in der grafischen Konfiguration, um einen zentralen Datenpunkt mehrfach zu nutzen.

## Vergleich mit ähnlichen Bausteinen
- **A2X_SPLIT_N**: Ein parametrierbarer Splitter mit variabler Anzahl von Ausgängen, z. B. 2, 4 oder 8. Der **A2X_SPLIT_9** ist fest auf neun Ausgänge ausgelegt.
- **A2X_MERGE**: Der umgekehrte Baustein, der mehrere Eingänge zu einem Ausgang zusammenführt (z. B. für Bus-Topologien).
- **Ereignisbasierte Splitter**: Bausteine wie `SPLIT` oder `E_SPLIT` arbeiten mit Ereignissignalen und erfordern Steuerlogik – der **A2X_SPLIT_9** kommt ohne Ereignisse aus.

## Fazit
Der **A2X_SPLIT_9** ist ein einfacher, aber effektiver Funktionsblock zur Verteilung eines A2X-Signals auf neun identische Ausgänge. Durch seine generische Natur und das Fehlen interner Logik ist er leichtgewichtig und ideal für reine Verdrahtungsszenarien in der 4diac-IDE. Er eignet sich besonders für Anwendungen, bei denen ein Signal mehrfach benötigt wird, ohne zusätzliche Programmierarbeit.