# AUI_SPLIT_2


![AUI_SPLIT_2](./AUI_SPLIT_2.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AUI_SPLIT_2** verteilt ein von einem AUI-Adapter (Socket) eingehendes Signal unverändert auf zwei identische AUI-Adapter (Plugs). Er wird als generischer Baustein (GenericClassName = `'GEN_AUI_SPLIT'`) ausgeliefert und ermöglicht die einfache Aufteilung eines unidirektionalen AUI-Datenstroms auf zwei unabhängige Senken.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine Ereignis-Eingänge vorhanden.

### **Ereignis-Ausgänge**
Keine Ereignis-Ausgänge vorhanden.

### **Daten-Eingänge**
Keine direkten Dateneingänge vorhanden. Der Datentransport erfolgt ausschließlich über die Adapter.

### **Daten-Ausgänge**
Keine direkten Datenausgänge vorhanden. Der Datentransport erfolgt ausschließlich über die Adapter.

### **Adapter**

| Name | Typ | Richtung / Rolle |
|------|-----|------------------|
| `IN` | `adapter::types::unidirectional::AUI` | Socket (Eingang) |
| `OUT1` | `adapter::types::unidirectional::AUI` | Plug (Ausgang 1) |
| `OUT2` | `adapter::types::unidirectional::AUI` | Plug (Ausgang 2) |

Alle drei Adapter sind vom Typ **AUI** und arbeiten unidirektional. Der Socket `IN` empfängt Daten, die Plugs `OUT1` und `OUT2` senden die gleichen Daten weiter.

## Funktionsweise
Der Baustein leitet jedes ankommende AUI-Signal am Socket `IN` gleichzeitig an beide Plugs `OUT1` und `OUT2` weiter. Es findet keine Verarbeitung, Filterung oder Pufferung der Daten statt – die Daten werden **1:1 kopiert und gesendet**. Die Aufteilung erfolgt streng deterministisch und ohne zusätzliche Verzögerung (abgesehen von der Laufzeit der internen Verbindung).

## Technische Besonderheiten
- **Generischer Typ**: Der FB wird durch das Attribut `GenericClassName` als `'GEN_AUI_SPLIT'` identifiziert und kann durch Type-Hash-Mechanismen (`TypeHash` aktuell leer) zur Laufzeit instanziiert werden.
- **Keine ECC (Execution Control Chart)**: Da keine ereignisgesteuerte Logik vorhanden ist, besitzt der Baustein keine Zustandsmaschine. Die Weiterleitung erfolgt rein datengetrieben.
- **EPL-2.0 Lizenziert**: Der Baustein wird unter der Eclipse Public License 2.0 bereitgestellt.

## Zustandsübersicht
Der AUI_SPLIT_2 verfügt über **keine Zustandsmaschine**. Es gibt keine internen Zustände oder Übergänge – das Signal wird kontinuierlich und ohne Taktung weitergeleitet.

## Anwendungsszenarien
- **Signalverteilung**: Ein AUI-Datenstrom muss parallel an zwei unabhängige Empfänger oder Subsysteme übergeben werden (z. B. zwei Controller, Anzeigen oder Aktoren).
- **Redundanz**: Identische Daten sollen auf zwei Pfaden bereitgestellt werden, um Failover-Mechanismen zu unterstützen.
- **Protokoll-Multicasting**: Ein unidirektionaler AUI-Stream wird an mehrere Verbraucher verteilt, ohne dass der Sender mehrfach angesprochen werden muss.

## Vergleich mit ähnlichen Bausteinen
- **AUI_SPLIT_N**: Erweiterte Variante, die einen Eingang auf N Ausgänge aufteilt (z. B. 1:3, 1:4). Der AUI_SPLIT_2 ist der einfachste Vertreter dieser Familie.
- **AUI_MERGE_2**: Führt zwei AUI-Eingänge zu einem Ausgang zusammen (ggf. mit Arbitration). Der Splitter arbeitet in die entgegengesetzte Richtung.
- **AUI_PASS**: Ein reiner 1:1-Durchgangsadapter ohne Verzweigung.

## Fazit
Der **AUI_SPLIT_2** ist ein minimalistischer, aber nützlicher Funktionsblock zur Aufteilung eines unidirektionalen AUI-Signals auf zwei Ausgänge. Dank seiner generischen Implementierung und dem Verzicht auf komplexe Logik eignet er sich ideal für Szenarien, in denen eine saubere, verlustfreie Vervielfältigung von Datenströmen erforderlich ist.