# AD_SPLIT_3


![AD_SPLIT_3](./AD_SPLIT_3.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AD_SPLIT_3` dient als generischer Splitter für einen unidirektionalen Adapter (AD). Er nimmt einen eingehenden AD entgegen und leitet ihn an drei separate Ausgänge weiter. Dies ermöglicht eine Mehrfachnutzung desselben Daten- oder Signalpfades.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine.

### **Ereignis-Ausgänge**
Keine.

### **Daten-Eingänge**
Keine.

### **Daten-Ausgänge**
Keine.

### **Adapter**
| Typ | Richtung | Bezeichnung | Beschreibung |
|------|----------|-------------|--------------|
| Socket (Eingang) | Input | IN | Unidirektionaler Adapter-Eingang, der auf die drei Ausgänge verteilt wird. |
| Plug (Ausgang) | Output | OUT1 | Erster Ausgang mit dupliziertem Adapter-Signal. |
| Plug (Ausgang) | Output | OUT2 | Zweiter Ausgang mit dupliziertem Adapter-Signal. |
| Plug (Ausgang) | Output | OUT3 | Dritter Ausgang mit dupliziertem Adapter-Signal. |

Alle Adapter sind vom Typ `adapter::types::unidirectional::AD`.

## Funktionsweise
Der Baustein arbeitet als reiner Splitter: Der am Socket `IN` anliegende Adapter (Daten- oder Ereignisstrom) wird auf die drei Plugs `OUT1`, `OUT2` und `OUT3` identisch vervielfältigt. Änderungen oder Ereignisse am Eingang wirken sich unverzögert auf alle drei Ausgänge aus. Es erfolgt keine Umformung, Pufferung oder Logik – die Signalverteilung geschieht transparent.

## Technische Besonderheiten
- **Generischer Typ**: Der FB ist als generischer Adapter-Splitter ausgelegt (`GenericClassName = 'GEN_AD_SPLIT'`) und kann mit beliebigen unidirektionalen Adaptern des Typs `adapter::types::unidirectional::AD` verwendet werden.
- **Reine Adapterschnittstelle**: Der Baustein besitzt weder Ereignis- noch Daten-Ein-/Ausgänge im klassischen Sinne, sondern kommuniziert ausschließlich über Adapter-Plugs und -Sockets.
- **Unidirektionalität**: Die Kommunikation erfolgt nur in eine Richtung (vom Socket zu den Plugs), daher ist keine Rückkopplung oder Handshake-Mechanismus erforderlich.
- **Keine Laufzeitabhängigkeit**: Die Verteilung erfolgt instantan und ohne Verzögerung.

## Zustandsübersicht
Der `AD_SPLIT_3` verfügt über kein eigenes Zustandsdiagramm (ECC). Die Ausgänge folgen dem Eingang ohne innere Logik oder Speicherverhalten. Daher existiert nur ein einziger, passiver Zustand, in dem ständig die aktuelle Eingabe an die Ausgänge weitergegeben wird.

## Anwendungsszenarien
1. **Signalfan-Out**: Ein Sensorsignal oder ein Befehl (z. B. Steuerwort oder Status) soll an mehrere parallele Verbraucher gesendet werden.
2. **Protokollierung**: Ein Datenstrom wird einmal verarbeitet und ein zweites Mal zur Aufzeichnung oder Überwachung weitergeleitet.
3. **Redundanz**: Ein kritischer Adapter-Pfad wird auf mehrere unabhängige Systeme verteilt.
4. **Testumgebungen**: In Simulations- oder Testaufbauten kann ein Signal an mehrere Prüfstellen gespiegelt werden.

## Vergleich mit ähnlichen Bausteinen
- **AD_SPLIT_2**: Verteilt den Eingang auf nur zwei Ausgänge. `AD_SPLIT_3` erweitert dies auf drei Ausgänge.
- **AD_MERGE**: Führt mehrere Adapter-Eingänge zu einem Ausgang zusammen – funktionell das Gegenteil.
- **Spezifische Daten-Splitter**: Bausteine wie `SPLIT_INT` oder `SPLIT_BOOL` arbeiten auf Daten-Ebene, nicht auf Adapter-Ebene. `AD_SPLIT_3` ist für vollständige Adapterstrukturen (Daten plus Ereignisse) gedacht.

## Fazit
Der `AD_SPLIT_3` ist ein einfacher, aber nützlicher generischer Baustein zur Vervielfachung von unidirektionalen Adaptern. Durch seine reine Adapterschnittstelle und fehlende Logik eignet er sich besonders für modulare Architekturen, in denen ein Signal auf mehrere Empfänger verteilt werden muss, ohne zusätzliche Komplexität einzuführen.