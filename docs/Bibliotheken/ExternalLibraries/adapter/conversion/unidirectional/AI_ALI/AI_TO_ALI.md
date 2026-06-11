# AI_TO_ALI


![AI_TO_ALI](./AI_TO_ALI.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock AI_TO_ALI ist ein Composite-Funktionsblock, der einen Eingangsadapter vom Typ AI (INT) in einen Ausgangsadapter vom Typ ALI (LINT) umwandelt. Er dient als einfache Konvertierungsschnittstelle zwischen unterschiedlichen Adaptertypen für die unidirektionale Kommunikation.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine eigenen Ereignis-Eingänge. Die Ereignisübertragung erfolgt über den Eingangsadapter AI_IN.  
Adapter AI_IN stellt den Ereignis-Eingang E1 bereit.

### **Ereignis-Ausgänge**
Keine eigenen Ereignis-Ausgänge. Die Ereignisweitergabe erfolgt über den Ausgangsadapter ALI_OUT.  
Adapter ALI_OUT stellt den Ereignis-Ausgang E1 bereit.

### **Daten-Eingänge**
Keine eigenen Daten-Eingänge. Die Datenübertragung erfolgt über den Eingangsadapter AI_IN.  
Adapter AI_IN stellt den Daten-Eingang D1 (Datentyp INT) bereit.

### **Daten-Ausgänge**
Keine eigenen Daten-Ausgänge. Die Datenweitergabe erfolgt über den Ausgangsadapter ALI_OUT.  
Adapter ALI_OUT stellt den Daten-Ausgang D1 (Datentyp LINT) bereit.

### **Adapter**
- **AI_IN** (Socket): Typ `adapter::types::unidirectional::AI` – INT-Eingangsschnittstelle.
- **ALI_OUT** (Plug): Typ `adapter::types::unidirectional::ALI` – LINT-Ausgangsschnittstelle.

**Hinweis:** Die eigentlichen Ereignis- und Datenschnittstellen werden durch die Adapter definiert. Der FB selbst besitzt keine eigenen Schnittstellen.

## Funktionsweise
Der FB arbeitet als reine Durchreiche: Das Ereignis- und Datensignal vom Eingangsadapter AI_IN wird direkt an den Ausgangsadapter ALI_OUT weitergeleitet. Dabei wird der INT-Datenwert implizit in einen LINT-Wert konvertiert, da LINT einen größeren Wertebereich abdeckt. Die Umwandlung erfolgt ohne zusätzliche Logik oder Verarbeitung.

## Technische Besonderheiten
- Es handelt sich um einen Composite-FB, der keine eigene Funktionalität implementiert, sondern lediglich zwei Adapter verdrahtet.
- Die Konvertierung von INT nach LINT ist verlustfrei, da LINT (64-Bit) den gesamten Wertebereich von INT (32-Bit) abdeckt.
- Der FB ist für den Einsatz in unidirektionalen Kommunikationspfaden vorgesehen, bei denen eine Anpassung des Datentyps zwischen Adapterschnittstellen erforderlich ist.
- Die Verwendung von Adaptern ermöglicht eine lose Kopplung zwischen Komponenten.

## Zustandsübersicht
Der FB besitzt keinen eigenen Zustandsautomaten, da die Funktionalität auf die reine Durchleitung von Ereignissen und Daten reduziert ist. Der interne Zustand ist nicht relevant; das Verhalten ist deterministisch und reagiert instantan auf eingehende Ereignisse.

## Anwendungsszenarien
- **Schnittstellenanpassung:** Ein Modul liefert einen INT-Wert über einen AI-Adapter, ein nachfolgendes Modul erwartet jedoch einen LINT-Wert über einen ALI-Adapter.
- **Erweiterung von Wertebereichen:** Wenn ein bestehender INT-Datenpfad auf einen größeren Wertebereich umgestellt werden muss, kann dieser FB als Zwischenstück eingesetzt werden.
- **Adapter-Protokollkonvertierung:** In heterogenen Systemen, in denen verschiedene Adaptertypen verwendet werden, dient der FB als einfacher Konverter.

## Vergleich mit ähnlichen Bausteinen
- **AI_TO_ALI** ist spezifisch für die Konvertierung von AI nach ALI. Andere Bausteine könnten z. B. AI_TO_AL (INT nach WORD) oder unterschiedliche Richtungen (ALI_TO_AI) realisieren.
- Im Vergleich zu einem generischen Typkonverter (z. B. mit Parametrierung) ist dieser FB spezialisiert und daher einfacher in der Anwendung, aber weniger flexibel.
- Composite-FBs wie dieser bieten eine klare Trennung der Verantwortlichkeiten und können in Bibliotheken für Standardkonvertierungen abgelegt werden.

## Fazit
Der AI_TO_ALI-Funktionsblock ist ein nützliches Werkzeug zur Adapterkonvertierung in IEC 61499-basierten Systemen. Er ermöglicht eine nahtlose Integration von Komponenten mit unterschiedlichen Datentypen auf der Adapterebene. Durch seine einfache, durchreichende Natur ist er zuverlässig und leicht zu verstehen. Er eignet sich besonders für Projekte, die auf das adapterbasierte unidirektionale Kommunikationsmodell setzen.