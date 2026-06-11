# AQ_TO_AX


![AQ_TO_AX](./AQ_TO_AX.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AQ_TO_AX` dient der Konvertierung eines AQ-Adapters (Quarter Byte) in einen AX-Adapter (BOOL) unter Verwendung einer STATUS-Logik. Er ermöglicht die einfache Integration von AQ-basierten Signalen in Systeme, die ausschließlich mit AX-Schnittstellen arbeiten. Intern nutzt er den Baustein `QUARTER_TO_BOOL`, um die Datenkonvertierung durchzuführen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- Keine direkten Ereignis-Eingänge vorhanden. Ereignisse werden über den AQ-Adapter (Socket `IN`) empfangen.

### **Ereignis-Ausgänge**
- Keine direkten Ereignis-Ausgänge vorhanden. Ereignisse werden über den AX-Adapter (Plug `OUT`) gesendet.

### **Daten-Eingänge**
- Keine direkten Daten-Eingänge vorhanden. Daten werden über den AQ-Adapter (Socket `IN`) empfangen.

### **Daten-Ausgänge**
- Keine direkten Daten-Ausgänge vorhanden. Daten werden über den AX-Adapter (Plug `OUT`) gesendet.

### **Adapter**
- **`IN` (Socket)**: Typ `adapter::types::unidirectional::AQ` – AQ-Eingang (Quarter Byte)
- **`OUT` (Plug)**: Typ `adapter::types::unidirectional::AX` – BOOL-Ausgang (AX)

## Funktionsweise
Der `AQ_TO_AX` Baustein besitzt keine eigenen Event- oder Daten-Ein-/Ausgänge, sondern realisiert die Konvertierung ausschließlich über zwei Adapter-Schnittstellen. Intern wird eine Instanz des Bausteins `QUARTER_TO_BOOL` eingesetzt:
1. **Ereignisweiterleitung**: Das Ereignis `E1` des eingehenden AQ-Adapters wird mit dem `REQ`-Eingang von `QUARTER_TO_BOOL` verbunden. Dessen `CNF`-Ereignis wird auf dem `E1`-Ausgang des AX-Adapters ausgegeben.
2. **Datenweiterleitung**: Das Datenwort `D1` des AQ-Adapters (Quarter Byte) wird an den `IB`-Eingang von `QUARTER_TO_BOOL` geleitet. Der konvertierte BOOL-Wert aus dem Ausgang `Q` von `QUARTER_TO_BOOL` wird auf den `D1`-Ausgang des AX-Adapters gegeben.

Die gesamte Ablaufsteuerung und Datenkonvertierung erfolgt somit transparent im Inneren des Bausteins.

## Technische Besonderheiten
- Der Baustein fungiert als reiner Adapter-Konverter und besitzt keine eigenen Zustände oder Anwendungslogik; die gesamte Funktionalität wird durch den eingebetteten `QUARTER_TO_BOOL` bereitgestellt.
- Die Verwendung von Adaptern (Socket/Plug) erlaubt eine lose Kopplung in der 4diac-IDE und erleichtert den Austausch von Kommunikationsschnittstellen.
- Der Kommentar „using STATUS logic“ deutet darauf hin, dass die Konvertierung möglicherweise auf einer Status-Abfrage basiert (z.B. gültige/nicht gültige Daten), was im internen Baustein umgesetzt wird.

## Zustandsübersicht
Der Baustein definiert keine eigenen Zustände. Die Zustandslogik liegt vollständig in dem internen Funktionsblock `QUARTER_TO_BOOL`.

## Anwendungsszenarien
- **Schnittstellenanpassung**: Einbindung eines AQ-basierten Sensors oder Aktors in ein System, das ausschließlich AX-kompatible Adapter unterstützt.
- **Adapter-Transformation**: Einsatz in Hierarchien, in denen unterschiedliche Adapter-Typen aufeinander abgestimmt werden müssen, ohne die zugrundeliegende Datenlogik zu ändern.
- **Prototypen und Migration**: Schnelles Umschalten zwischen AQ- und AX-Varianten während der Entwicklungs- oder Testphase.

## Vergleich mit ähnlichen Bausteinen
- **`QUARTER_TO_BOOL`**: Direkte Konvertierung eines Quarter-Byte-Wertes in einen BOOL-Wert mit eigenem Event-Interface; `AQ_TO_AX` kapselt diesen Baustein in einem Adapter-Kontext.
- **`BYTE_TO_BOOL` oder `WORD_TO_BOOL`**: Ähnliche Konvertern für andere Bit-Breiten, jedoch nicht speziell für die Adapter-Kopplung ausgelegt.
- **Direkte Kopplung von AQ und AX**: Ohne Konvertierung wäre eine Verbindung nicht möglich, da die Adapter-Typen inkompatibel sind.

## Fazit
`AQ_TO_AX` ist ein schlanker, aber essentieller Adapter-Konverter, der die Lücke zwischen AQ- und AX-Schnittstellen schließt. Er vereinfacht die Integration von Quarter-Byte-Signalen in BOOL-basierte Steuerungen und trägt zur Wiederverwendbarkeit von Funktionsbausteinen in verschiedenen Adapter-Umgebungen bei.