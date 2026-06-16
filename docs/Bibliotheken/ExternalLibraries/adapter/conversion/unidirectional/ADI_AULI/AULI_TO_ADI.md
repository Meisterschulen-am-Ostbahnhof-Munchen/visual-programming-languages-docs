# AULI_TO_ADI


![AULI_TO_ADI](./AULI_TO_ADI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AULI_TO_ADI** ist ein zusammengesetzter Baustein zur Umwandlung eines **AULI**-Adapters (unsignierter 64‑Bit‑Wert) in einen **ADI**-Adapter (vorzeichenbehafteter 32‑Bit‑Wert). Er ermöglicht die einfache Konvertierung zwischen zwei unidirektionalen Adapterschnittstellen und nutzt intern eine IEC‑61131‑Typumwandlungsfunktion.

## Schnittstellenstruktur
Der Baustein besitzt keine eigenen Ereignis‑ oder Dateneingänge/-ausgänge. Die gesamte Kommunikation erfolgt ausschließlich über die beiden Adapter.

### **Ereignis-Eingänge**
Keine (ausschließlich über Adapter).

### **Ereignis-Ausgänge**
Keine (ausschließlich über Adapter).

### **Daten-Eingänge**
Keine (ausschließlich über Adapter).

### **Daten-Ausgänge**
Keine (ausschließlich über Adapter).

### **Adapter**

| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::AULI` | `AULI_IN` | Socket / Eingang | Aufnahme eines ULINT‑Werts über Ereignis‑ und Datenkanäle (E1, D1) |
| `adapter::types::unidirectional::ADI` | `ADI_OUT` | Plug / Ausgang | Bereitstellung des konvertierten DINT‑Werts über Ereignis‑ und Datenkanäle (E1, D1) |

## Funktionsweise
Der Baustein arbeitet als reine Kaskade:
1. Ein Ereignis am Socket `AULI_IN.E1` löst die Datenübergabe von `AULI_IN.D1` (ULINT) aus.
2. Dieses Ereignis wird auf den Eingang `REQ` des internen Konvertierungsbausteins `F_ULINT_TO_DINT` (IEC‑61131‑Typumwandlung) übertragen.
3. Der Konverter wandelt den ULINT‑Wert in einen DINT‑Wert um und legt ihn an seinem Ausgang `OUT` an.
4. Nach Abschluss der Umwandlung signalisiert der Konverter mit `CNF` das Ereignis, das den Plug `ADI_OUT.E1` auslöst und gleichzeitig den konvertierten Wert auf `ADI_OUT.D1` bereitstellt.
5. Der angeschlossene Empfänger erhält so einen DINT‑Wert, der dem ursprünglichen ULINT‑Wert – soweit darstellbar (Wertebereich DINT: -2³¹ … 2³¹‑1) – entspricht.

## Technische Besonderheiten
- **Adapterbasiert**: Der FB implementiert keine direkten Ein‑/Ausgangsvariablen, sondern nutzt ausschließlich Adapter‑Sockets und ‑Plugs für lose Kopplung.
- **Typumwandlung**: Die Konvertierung erfolgt mittels des IEC‑61131‑Standardbausteins `F_ULINT_TO_DINT`. Dabei können ULINT‑Werte außerhalb des DINT‑Bereichs zu Überläufen oder unerwarteten Ergebnissen führen.
- **Kompakte Struktur**: Da keine Zustandslogik oder Verzweigungen vorhanden sind, arbeitet der Baustein deterministisch und ohne Verzögerung jenseits der reinen Konvertierungszeit.
- **Paket**: Der Baustein ist im Package `adapter::conversion::unidirectional` zusammengefasst.

## Zustandsübersicht
Der FB besitzt keinen internen Zustandsautomaten. Er verhält sich wie eine reine funktionale Abbildung: Auf ein Eingangsereignis folgt unmittelbar ein Ausgangsereignis mit dem umgewandelten Wert.

## Anwendungsszenarien
- **Schnittstellenanpassung**: Wenn ein Sensor oder eine Steuerung einen ULINT‑Adapter liefert, das nachgelagerte System aber einen DINT‑Adapter erwartet.
- **Datenreduktion**: Reduzierung der Bitbreite von 64 auf 32 Bit in Fällen, in denen die Auflösung von 32 Bit ausreicht.
- **Adapterkaskaden**: Verwendung als ein Glied in einer lückenlosen Umwandlungskette zwischen unterschiedlichen Datenadaptertypen.

## Vergleich mit ähnlichen Bausteinen
- **AULI_TO_UDI**: Wandelt ULINT in UDINT (unsigned 32‑Bit) – hier bleibt der Wertebereich positiv und Überläufe treten erst bei Werten > 2³²‑1 auf.
- **DIRECT_CONVERT**: Ein generischer Baustein mit direktem Dateneingang und -ausgang, der keine Adapter verwendet – AULI_TO_ADI bietet dagegen lose Kopplung und standardisierte Adapterschnittstellen.
- **Manuelle Konvertierung**: Ohne diesen Baustein müsste die Umwandlung im Anwendungs‑FB selbst implementiert werden – AULI_TO_ADI kapselt diese Aufgabe und fördert die Wiederverwendbarkeit.

## Fazit
**AULI_TO_ADI** ist ein spezialisierter, adapterbasierter Konvertierungsbaustein, der die Umwandlung von ULINT‑ auf DINT‑Daten über unidirektionale Adapter effizient und standardisiert abwickelt. Durch die Nutzung eines IEC‑61131‑Konvertierungs‑FBs ist die Umwandlung zuverlässig, und die reine Adapter‑Schnittstelle ermöglicht eine flexible Integration in bestehende Systeme. Der Baustein eignet sich besonders für lose gekoppelte Architekturen, in denen Datenformate angepasst werden müssen, ohne die Anwendungslogik mit Typkonvertierung zu belasten.