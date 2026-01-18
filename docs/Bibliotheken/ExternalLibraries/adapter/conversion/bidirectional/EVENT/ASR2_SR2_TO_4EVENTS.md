# ASR2_SR2_TO_4EVENTS

```{index} single: ASR2_SR2_TO_4EVENTS
```

<img width="1144" height="209" alt="image" src="https://github.com/user-attachments/assets/86e61c8f-102b-496b-bc1f-d0e024540466" />

* * * * * * * * * *

## Einleitung
Der Funktionsblock ASR2_SR2_TO_4EVENTS ist ein Composite-Funktionsblock, der zur Bereitstellung der ASR2-Adaptersignale als vier diskrete Ereignis-Endpunkte dient. Er ermöglicht die bidirektionale Umwandlung zwischen ASR2-Adapter-Schnittstellen und diskreten Ereignis-Ein- und Ausgängen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **EI_SET**: Setzen / Einschalten
- **EI_RESET**: Rücksetzen / Ausschalten

### **Ereignis-Ausgänge**
- **EO_SET**: Setzen / Einschalten
- **EO_RESET**: Rücksetzen / Ausschalten

### **Daten-Eingänge**
Keine Daten-Eingänge vorhanden.

### **Daten-Ausgänge**
Keine Daten-Ausgänge vorhanden.

### **Adapter**
- **ASR_IN**: Adapter-Eingang vom Typ `adapter::types::bidirectional::ASR2`

## Funktionsweise
Der Funktionsblock fungiert als Brücke zwischen dem ASR2-Adapter und diskreten Ereignissen. Die Ereignis-Eingänge EI_SET und EI_RESET werden direkt an den ASR2-Adapter weitergeleitet, während die Ereignis-Ausgänge EO_SET und EO_RESET direkt vom ASR2-Adapter gespeist werden. Dies ermöglicht eine bidirektionale Kommunikation zwischen den beiden Schnittstellen.

## Technische Besonderheiten
- Implementiert als Composite-Funktionsblock
- Verwendet bidirektionale Adapter-Kommunikation
- Enthält keine internen Datenverarbeitungslogiken, sondern dient primär als Signalweiterleitung
- Unterstützt die Eclipse 4diac Standardkonformität

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände, da er ausschließlich als Durchreichblock für Ereignisse fungiert. Alle eingehenden Ereignisse werden sofort an die entsprechende Schnittstelle weitergeleitet.

## Anwendungsszenarien
- Integration von ASR2-kompatiblen Komponenten in 4diac-Systeme
- Konvertierung zwischen Adapter-basierten und ereignisbasierten Schnittstellen
- Bidirektionale Signalübertragung in Automatisierungssystemen
- Kopplung unterschiedlicher Kommunikationsprotokolle

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen Konverter-Blöcken bietet ASR2_SR2_TO_4EVENTS die Besonderheit der bidirektionalen Kommunikation und die spezifische Anpassung an ASR2-Adapter. Andere Konverter-Blöcke sind oft unidirektional oder unterstützen andere Adapter-Typen.

## Fazit
Der ASR2_SR2_TO_4EVENTS Funktionsblock stellt eine effiziente Lösung für die Integration von ASR2-Schnittstellen in 4diac-basierte Steuerungssysteme dar. Durch seine einfache, aber effektive Durchreich-Architektur ermöglicht er eine nahtlose Kommunikation zwischen unterschiedlichen Schnittstellentypen ohne zusätzliche Verarbeitungslatenz.
