# AIWS_SPLIT_6


![AIWS_SPLIT_6](./AIWS_SPLIT_6.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock AIWS_SPLIT_6 dient dazu, ein eingehendes AIWS-Signal (Adaptertyp) auf sechs identische Ausgänge zu verteilen. Er ist als generischer Baustein konzipiert und ermöglicht eine einfache Signalvervielfachung in Steuerungsanwendungen, die auf dem 4diac-IDE-Framework basieren.

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
**Socket (Eingang):**
- `IN` (Typ: `adapter::types::unidirectional::AIWS`): Eingangsadapter für das zu verteilende AIWS-Signal.

**Plugs (Ausgänge):**
- `OUT1` (Typ: `adapter::types::unidirectional::AIWS`): Erster Ausgang mit dem gesplitteten Signal.
- `OUT2` (Typ: `adapter::types::unidirectional::AIWS`): Zweiter Ausgang.
- `OUT3` (Typ: `adapter::types::unidirectional::AIWS`): Dritter Ausgang.
- `OUT4` (Typ: `adapter::types::unidirectional::AIWS`): Vierter Ausgang.
- `OUT5` (Typ: `adapter::types::unidirectional::AIWS`): Fünfter Ausgang.
- `OUT6` (Typ: `adapter::types::unidirectional::AIWS`): Sechster Ausgang.

## Funktionsweise
Der AIWS_SPLIT_6-Baustein nimmt das an seinem Socket `IN` anliegende AIWS-Signal entgegen und leitet es unverändert an alle sechs Plug-Ausgänge `OUT1` bis `OUT6` weiter. Es findet keine Signalverarbeitung oder -änderung statt; der Baustein fungiert als passiver Splitter (1:6). Die Kommunikation erfolgt über Adapter gemäß der unidirektionalen AIWS-Schnittstellendefinition.

## Technische Besonderheiten
- Der Baustein ist als generischer Funktionsblock implementiert, erkennbar an den Attributen `GenericClassName` und `TypeHash`. Dadurch kann er in verschiedenen Ausprägungen (z. B. AIWS_SPLIT_2, AIWS_SPLIT_4) als Instanz eines generischen Typs erstellt werden.
- Es sind keine Ereignis- oder Daten-Ein-/Ausgänge vorhanden; die gesamte Datenübertragung erfolgt ausschließlich über die Adapter-Schnittstellen.
- Der Baustein enthält keine eigene Zustandslogik oder Verarbeitungsalgorithmen.

## Zustandsübersicht
Der Baustein besitzt keine definierten Zustände, da er keine ereignisgesteuerte Ausführung erfordert. Die Signalweitergabe erfolgt kontinuierlich und passiv.

## Anwendungsszenarien
- Verteilung eines analogen Eingangssignals (z. B. von einem Sensor) an mehrere nachgeschaltete Funktionsblöcke.
- Bereitstellung eines Referenzsignals für mehrere parallele Regelkreise.
- Einsatz in modularen Automatisierungslösungen, die eine Signalvervielfachung ohne zusätzliche Hardware erfordern.

## Vergleich mit ähnlichen Bausteinen
- **AIWS_SPLIT_2, AIWS_SPLIT_4:** Diese Bausteine verteilen das Signal auf zwei bzw. vier Ausgänge. AIWS_SPLIT_6 erweitert die Anzahl auf sechs.
- **AIWS_MERGE:** Ein zusammensetzender Baustein, der mehrere AIWS-Eingänge zu einem Ausgang zusammenführt – funktionale Umkehrung des Splitters.
- **Direkte Verbindung:** Anstatt eines Splitter-Bausteins könnten mehrere parallele Verbindungen im Applikationsmodell gezogen werden, was jedoch die Übersichtlichkeit reduziert und bei Änderungen aufwändiger ist.

## Fazit
Der AIWS_SPLIT_6 ist ein einfacher, aber nützlicher Baustein zur Vervielfachung von AIWS-Signalen in IEC 61499-basierten Steuerungen. Seine generische Natur und die klare Adapter-Schnittstelle erleichtern die Wiederverwendung und Integration in größere Projekte.