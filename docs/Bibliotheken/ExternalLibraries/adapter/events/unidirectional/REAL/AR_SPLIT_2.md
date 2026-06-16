# AR_SPLIT_2


![AR_SPLIT_2](./AR_SPLIT_2.svg)

* * * * * * * * * *
## Einleitung
Der **AR_SPLIT_2** ist ein generischer Funktionsbaustein, der einen eingehenden Adapter vom Typ `adapter::types::unidirectional::AR` auf zwei separate Ausgänge (OUT1, OUT2) aufteilt. Er dient zur Weiterleitung eines Signals an zwei nachfolgende Bausteine, ohne die Daten zu verändern. Der Baustein ist als generischer Typ (`GEN_AR_SPLIT`) implementiert und wird zur Laufzeit parametrisiert.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine Ereignis-Eingänge vorhanden.

### **Ereignis-Ausgänge**
Keine Ereignis-Ausgänge vorhanden.

### **Daten-Eingänge**
Keine Daten-Eingänge vorhanden.

### **Daten-Ausgänge**
Keine Daten-Ausgänge vorhanden.

### **Adapter**

| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::AR` | IN | Socket | Eingangssignal (AR) |
| `adapter::types::unidirectional::AR` | OUT1 | Plug | Erster Ausgang (identisch zu IN) |
| `adapter::types::unidirectional::AR` | OUT2 | Plug | Zweiter Ausgang (identisch zu IN) |

## Funktionsweise
Der Baustein leitet das am Socket **IN** anliegende AR-Signal unverändert auf beide Plugs **OUT1** und **OUT2** weiter. Es findet keine Datenmanipulation, Filterung oder Verzögerung statt. Die Aufteilung erfolgt rein strukturell: Jeder Ausgang erhält eine eigene Kopie der Referenz auf das zugrundeliegende AR-Objekt.

## Technische Besonderheiten
- **Generische Implementierung**: Der FB verwendet das Generic-Class-Name-Attribut (`eclipse4diac::core::GenericClassName`) mit dem Wert `'GEN_AR_SPLIT'`, sodass er anwendungsspezifisch konfiguriert werden kann.
- **Unidirektionale Adapter**: Alle Adapter sind vom Typ `adapter::types::unidirectional::AR` (nur Vorwärtsrichtung).
- **Keine Zustandsautomatik**: Der Baustein besitzt keinen expliziten ECC (Execution Control Chart); die Weiterleitung erfolgt direkt und ereignisunabhängig.

## Zustandsübersicht
Der Baustein implementiert keine Zustandsautomaten. Die Funktionalität beschränkt sich auf die passive Weiterleitung des Eingangssignals an beide Ausgänge. Eine Zustandsvisualisierung ist daher nicht erforderlich.

## Anwendungsszenarien
- **Signalverteilung**: Aufteilung eines AR-basierten Sensorsignals an zwei parallel arbeitende Steuerungskomponenten.
- **Redundanz**: Bereitstellung des gleichen AR-Datenstroms für ein primäres und ein redundantes System.
- **Debugging**: Anschluss eines Analyse- oder Logging-Bausteins parallel zum bestehenden Pfad, ohne die Originalsignalkette zu unterbrechen.

## Vergleich mit ähnlichen Bausteinen
Ähnliche Funktionalität bieten Bausteine wie `AR_SPLIT_3` oder `AR_SPLIT_N`, die ein Signal auf drei bzw. N Ausgänge verteilen. Die Auswahl hängt von der benötigten Anzahl an Ausgängen ab. Ein Verbinden mehrerer `AR_SPLIT_2`-Instanzen in Kaskade ist ebenfalls möglich, erhöht jedoch die Komplexität gegenüber einem dedizierten Splitter mit mehreren Ausgängen.

## Fazit
Der **AR_SPLIT_2** ist ein einfacher, aber essenzieller Baustein zur Vervielfachung eines AR-Signals in IEC 61499-basierten Steuerungssystemen. Seine generische Auslegung und die klare Schnittstelle machen ihn zur ersten Wahl, wenn ein Signal an zwei unabhängige Zielbausteine weitergegeben werden muss.