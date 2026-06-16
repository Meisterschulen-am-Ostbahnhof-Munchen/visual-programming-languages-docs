# AUI_TO_ADI


![AUI_TO_ADI](./AUI_TO_ADI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock AUI_TO_ADI ist ein Composite-Baustein, der einen unidirektionalen AUI-Adapter (Datentyp UINT) in einen unidirektionalen ADI-Adapter (Datentyp DINT) umwandelt. Er dient als standardisierte Schnittstelle zwischen Komponenten, die unterschiedliche Datentypen für analoge Ein- oder Ausgangswerte verwenden.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine. Die Ereignissteuerung erfolgt über den angeschlossenen AUI-Adapter (Socket AUI_IN).

### **Ereignis-Ausgänge**
Keine. Die Ereignisausgabe erfolgt über den ADI-Adapter (Plug ADI_OUT).

### **Daten-Eingänge**
Keine. Die Dateneingabe erfolgt über den angeschlossenen AUI-Adapter.

### **Daten-Ausgänge**
Keine. Die Datenausgabe erfolgt über den ADI-Adapter.

### **Adapter**

| Name | Richtung | Typ | Beschreibung |
|------|----------|-----|--------------|
| AUI_IN | Socket (Eingang) | `adapter::types::unidirectional::AUI` | UINT-Adapter zum Empfangen von Eingangsdaten und Ereignissen. |
| ADI_OUT | Plug (Ausgang) | `adapter::types::unidirectional::ADI` | DINT-Adapter zum Senden der konvertierten Daten und Ereignisse. |

## Funktionsweise
Der FB empfängt über den Socket AUI_IN ein Ereignis sowie einen UINT-Wert. Dieses Ereignis triggert den internen Konvertierungsbaustein `F_UINT_TO_DINT`, der den Wert vom Typ UINT in den Typ DINT umwandelt. Nach erfolgreicher Konvertierung wird ein Ereignis über den Plug ADI_OUT ausgegeben, zusammen mit dem konvertierten DINT-Wert. Die Konvertierung erfolgt entsprechend der IEC‑61131‑Norm und ist verlustfrei, da der Wertebereich von UINT (0…65535) vollständig in DINT abgebildet werden kann.

## Technische Besonderheiten
- Der FB ist als **Composite-Baustein** realisiert, d.h. seine Funktionalität basiert auf einem enthaltenen IEC‑61131‑Baustein (`F_UINT_TO_DINT`).
- Die Kommunikation erfolgt ausschließlich über **unidirektionale Adapter** – es werden keine eigenständigen Ereignis- oder Dateneingänge/-ausgänge auf oberster Ebene benötigt.
- Der interne Konverter arbeitet **ereignisgesteuert**: Jedes eingehende Ereignis am AUI_IN-Adapter löst eine Konvertierung aus.

## Zustandsübersicht
Der FB besitzt keine eigene Zustandsmaschine. Die Zustandslogik wird vollständig durch den internen Baustein `F_UINT_TO_DINT` abgebildet, der bei jedem REQ-Ereignis eine einmalige Konvertierung durchführt und mit CNF quittiert.

## Anwendungsszenarien
- **Schnittstellenanpassung**: Ein Sensor liefert über einen UINT-basierten AUI-Adapter Messwerte, die nachgeschaltete Logik benötigt jedoch DINT-Werte (z.B. für arithmetische Operationen oder Visualisierung).
- **Systemintegration**: In heterogenen Automatisierungssystemen, in denen unterschiedliche Komponenten verschiedene Adaptertypen verwenden, kann der Baustein als vermittelnde Schicht eingesetzt werden.
- **Migration**: Bestehende Anlagen mit UINT-Datenpfaden sollen schrittweise auf DINT umgestellt werden.

## Vergleich mit ähnlichen Bausteinen
- **F_UINT_TO_DINT**: Direkter IEC‑61131-Konverter, jedoch ohne Adapterkapselung. Erfordert separate Ereignis- und Datenleitungen.
- **AUI_TO_ABOOL**: Analoger Konverter für binäre Ausgaben (UINT → BOOL), nicht für numerische Typen.
- **ATO_TO_ADI**: Konvertiert ATO-Adapter (DWORD) nach ADI, andere Datenbreite.

Der vorliegende Baustein hebt sich durch die vollständige Adapterintegration und die unidirektionale Auslegung ab, was den Einsatz in adapterbasierten Architekturen erleichtert.

## Fazit
Der Funktionsblock `AUI_TO_ADI` bietet eine saubere, gekapselte Lösung zur Typkonvertierung von UINT auf DINT über standardisierte Adapter. Er reduziert den Verdrahtungsaufwand und erhöht die Wiederverwendbarkeit in modularen Automatisierungslösungen. Durch die Nutzung eines bewährten IEC‑61131-Bausteins ist die Korrektheit der Konvertierung sichergestellt.