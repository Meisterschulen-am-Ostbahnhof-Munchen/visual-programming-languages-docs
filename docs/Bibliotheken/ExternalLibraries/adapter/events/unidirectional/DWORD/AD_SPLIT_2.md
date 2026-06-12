# AD_SPLIT_2


![AD_SPLIT_2](./AD_SPLIT_2.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock AD_SPLIT_2 dient dazu, einen eingehenden unidirektionalen Adapter (AD) auf zwei identische Ausgangsadapter aufzuteilen. Er ist als generischer Baustein implementiert und ermöglicht die einfache Verzweigung eines Adaptersignals in zwei parallele Pfade.

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
| Name | Typ | Richtung |
|------|-----|----------|
| IN   | adapter::types::unidirectional::AD | Socket (Eingang) |
| OUT1 | adapter::types::unidirectional::AD | Plug (Ausgang) |
| OUT2 | adapter::types::unidirectional::AD | Plug (Ausgang) |

## Funktionsweise
Der Baustein empfängt einen unidirektionalen Adapter über den Socket `IN`. Alle über diesen Adapter übertragenen Daten und Ereignisse werden unverändert an beide Ausgangsadapter `OUT1` und `OUT2` weitergegeben. Es findet keine Vebarbeitung oder Filterung statt – die Signale werden lediglich dupliziert. Die Aufteilung erfolgt ohne Zeitverzögerung und ohne interne Pufferung.

## Technische Besonderheiten
- **Generische Ausführung**: Der FB nutzt die Generics-Mechanismen von Eclipse 4diac (`GenericClassName`). Dadurch kann der konkrete Adaptertyp zur Entwurfszeit oder Laufzeit parametrisiert werden, solange er dem Adapter-Schema `unidirectional::AD` entspricht.
- **Typreinheit**: Die Ausgangsadapter sind vom selben Typ wie der Eingangsadapter; eine Typkonvertierung findet nicht statt.
- **Keine Zustandslogik**: Der Baustein besitzt keine interne Zustandsmaschine (ECC) und reagiert ereignisgesteuert auf die Adapterkommunikation.

## Zustandsübersicht
Der Funktionsblock hat keine expliziten Zustände. Er arbeitet kontinuierlich und leitet jedes ankommende Signal sofort an beide Ausgänge weiter.

## Anwendungsszenarien
- Aufteilung eines Sensordatenstroms auf zwei unabhängige Steuerungs- oder Überwachungseinheiten.
- Parallelisierung von Adaptersignalen in industriellen Automatisierungssystemen (z. B. Verteilung eines Feldbus-Adapterwerts auf zwei Regelkreise).
- Test- und Simulationsaufbauten, bei denen ein Signal simultan an verschiedene Verbraucher gesendet werden muss.

## Vergleich mit ähnlichen Bausteinen
- **AD_SPLIT_3, AD_SPLIT_4**: Erweiterungen mit mehreren Ausgängen, basierend auf demselben Mechanismus.
- **AD_MERGE**: Führt mehrere Adaptereingänge zu einem Ausgang zusammen – die Umkehrfunktion zu AD_SPLIT_2.
- **AD_SELECT**: Wählt einen von mehreren Adaptereingängen aus und gibt ihn weiter, erfordert hingegen eine Steuerlogik.

## Fazit
Der AD_SPLIT_2 ist ein einfacher, aber effektiver Baustein zur Signalverteilung in Adapter-basierten Architekturen. Seine generische Natur und die fehlende Zustandslogik machen ihn leicht konfigurierbar und ressourcenschonend. Er eignet sich besonders für modulare Automatisierungsprojekte, in denen ein Adaptersignal auf mehrere nachgelagerte Komponenten verteilt werden muss.