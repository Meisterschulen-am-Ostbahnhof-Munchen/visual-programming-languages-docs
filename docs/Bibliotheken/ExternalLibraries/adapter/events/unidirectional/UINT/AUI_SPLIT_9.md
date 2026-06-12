# AUI_SPLIT_9

[Bild des FB nicht verfügbar]


![AUI_SPLIT_9](./AUI_SPLIT_9.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein **AUI_SPLIT_9** dient als generischer Splitter für unidirektionale AUI-Adapterverbindungen. Er empfängt ein eingehendes AUI-Signal über den Socket `IN` und verteilt dieses identisch auf neun separate Ausgangs-Plugs (`OUT1` bis `OUT9`). Der Baustein ist typisiert als generischer FB (`GEN_AUI_SPLIT`) und kann in verschiedenen Automatisierungsumgebungen eingesetzt werden, in denen ein AUI-Signal an mehrere nachfolgende Komponenten weitergegeben werden muss.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Nicht vorhanden. Der FB arbeitet rein adapterbasiert ohne Ereignissteuerung.

### **Ereignis-Ausgänge**

Nicht vorhanden.

### **Daten-Eingänge**

Nicht vorhanden.

### **Daten-Ausgänge**

Nicht vorhanden.

### **Adapter**

**Socket (Eingang):**
- `IN` – Typ: `adapter::types::unidirectional::AUI`  
  Empfängt das zu verteilende AUI-Signal.

**Plugs (Ausgänge):**
- `OUT1` bis `OUT9` – jeweils Typ: `adapter::types::unidirectional::AUI`  
  Neun identische Ausgänge, die das eingehende AUI-Signal unverändert weiterleiten.

Der FB ist ein reiner Adapter-Splitter ohne zusätzliche Logik und arbeitet unidirektional. Alle Plugs sind vom gleichen Typ wie der Socket.

## Funktionsweise

Der Baustein kopiert das am Socket `IN` anliegende AUI-Signal auf alle neun Ausgangs-Plugs. Es findet keine Signalaufbereitung, Verzögerung oder Filterung statt – die Ausgänge sind exakte Repliken des Eingangs. Die Verteilung erfolgt parallel und ohne Datenpufferung. Da es sich um einen generischen Baustein handelt, ist der konkrete Signaltyp (z. B. Feldbusdaten, Messwerte, Steuerbefehle) nicht festgelegt; er ergibt sich aus der AUI-Adapterdefinition.

## Technische Besonderheiten

- **Generischer Typ**: Der FB ist als `GEN_AUI_SPLIT` mit einem Type-Hash attributiert, was die dynamische Erzeugung von Instanzen zur Laufzeit in 4diac-IDE unterstützt.
- **Keine Zustandsabhängigkeit**: Der Baustein besitzt keine internen Zustände oder Zeitverhalten – die Ausgänge sind immer eine direkte Wegschaltung des Eingangs.
- **Erweiterbarkeit**: Durch die unidirektionale Adapter-Schnittstelle kann der FB in beliebige AUI-basierte Kommunikationsketten eingefügt werden.
- **Kompatibilität**: Erfordert die Importe `eclipse4diac::core::GenericClassName` und `eclipse4diac::core::TypeHash`, die in der Ziel-4diac-Umgebung verfügbar sein müssen.

## Zustandsübersicht

Der FB besitzt keinen Zustandsautomaten. Es findet keine sequentielle Abarbeitung statt; die Signalweitergabe erfolgt statisch und kontinuierlich. Ein expliziter Zustand entfällt.

## Anwendungsszenarien

- **Signalverteilung in Feldbussystemen**: Aufteilung eines AUI-basierten Bussignals an mehrere Teilanlagen oder Aktoren.
- **Test- und Debugging-Umgebungen**: Einem Signalgenerator nachgeschaltet, um mehrere Testpunkte parallel zu versorgen.
- **Redundanz oder Parallelbetrieb**: Wenn ein Signal gleichzeitig an mehrere Steuerungen oder Überwachungseinheiten gesendet werden muss.
- **Prototypenentwicklung**: Als Platzhalter für spätere Verzweigungen in der Adapterlogik.

## Vergleich mit ähnlichen Bausteinen

- **AUI_SPLIT_4 / AUI_SPLIT_16**: Diese Bausteine bieten die gleiche Funktionalität mit 4 bzw. 16 Ausgängen. Die Wahl hängt von der benötigten Anzahl der Abzweigungen ab.
- **AUI_MERGE_***: Ein Merger fasst mehrere AUI-Eingänge zu einem Ausgang zusammen – die entgegengesetzte Funktion. Der Splitter verteilt hingegen.
- **Generische Splitter anderer Adaptertypen (z. B. Daten-basiert)**: Im Gegensatz zu Daten-Ereignis-Splittern arbeitet AUI_SPLIT_9 rein auf Adapterebene und benötigt keine Ereignissteuerung, was den Implementierungsaufwand reduziert.

## Fazit

Der **AUI_SPLIT_9** ist ein einfacher, aber effektiver Funktionsbaustein zur Mehrfachverteilung unidirektionaler AUI-Signale. Seine generische Natur ermöglicht eine flexible Wiederverwendung in verschiedenen Projekten. Aufgrund der fehlenden Eigenlogik ist der Baustein ressourcenschonend und leicht verständlich. Er eignet sich besonders für die schnelle Realisierung von 1-zu-n-Verbindungen in adapterbasierten Automatisierungsarchitekturen.