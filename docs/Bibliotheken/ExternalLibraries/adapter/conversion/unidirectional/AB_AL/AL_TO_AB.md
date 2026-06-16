# AL_TO_AB


![AL_TO_AB](./AL_TO_AB.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AL_TO_AB** ist ein Composite-FB, der eine unidirektionale Konvertierung von einem LWORD-Adapter (AL) zu einem BYTE-Adapter (AB) ermöglicht. Er wird eingesetzt, um Daten eines LWORD-basierten Adapters in das Format eines BYTE-Adapters zu überführen, wobei die Konvertierung intern durch den IEC‑61131‑3-Baustein `F_LWORD_TO_BYTE` realisiert wird.

## Schnittstellenstruktur
### **Adapter (Eingang)**

| Name | Typ | Beschreibung |
|------|-----|-------------|
| AL_IN | `adapter::types::unidirectional::AL` | LWORD-Adapter-Socket. Über diesen Adapter werden die zu konvertierenden LWORD-Daten empfangen. Der Adapter stellt standardmäßig einen Ereignisausgang `E1` und einen Datenausgang `D1` (Datentyp LWORD) zur Verfügung. |

### **Adapter (Ausgang)**

| Name | Typ | Beschreibung |
|------|-----|-------------|
| AB_OUT | `adapter::types::unidirectional::AB` | BYTE-Adapter-Plug. Über diesen Adapter werden die konvertierten BYTE-Daten ausgegeben. Der Adapter besitzt einen Ereigniseingang `E1` und einen Dateneingang `D1` (Datentyp BYTE). |

**Hinweis:** Der FB besitzt keine separaten Ereignis‑ oder Dateneingänge/-ausgänge; die gesamte Kommunikation erfolgt über die beiden Adapter-Schnittstellen.

## Funktionsweise
1. Über den Socket `AL_IN` wird ein Ereignis (am Ereignisausgang `E1` des Adapters) empfangen, das gleichzeitig einen LWORD-Wert über den Datenausgang `D1` bereitstellt.
2. Dieses Ereignis triggert intern den Baustein `F_LWORD_TO_BYTE` (Typ: `iec61131::conversion::F_LWORD_TO_BYTE`), welcher die Umwandlung des LWORD-Wertes in einen BYTE-Wert vornimmt.
3. Nach erfolgreicher Konvertierung signalisiert `F_LWORD_TO_BYTE` den Abschluss über seinen Ereignisausgang `CNF`, der das Ereignis an den Plug `AB_OUT` weiterleitet.
4. Gleichzeitig wird der konvertierte BYTE-Wert über den Datenausgang `OUT` des Konverters an den Dateneingang `D1` von `AB_OUT` übergeben.
5. Der angeschlossene Empfänger am Plug `AB_OUT` erhält somit das Ereignis und den konvertierten Datenwert.

## Technische Besonderheiten
- **Einbindung von IEC‑61131‑3**: Die Konvertierung nutzt den standardisierten Baustein `F_LWORD_TO_BYTE` aus der IEC‑61131‑3-Bibliothek. Dadurch ist die Konvertierungslogik normkonform und portabel.
- **Composite-Struktur**: Der FB besteht ausschließlich aus einem internen Netzwerk, besitzt keinen eigenen Ablaufzustand (ECC) und arbeitet daher ereignisgesteuert ohne Verzögerung.
- **Unidirektionale Adapter**: Verwendet werden die unidirektionalen Adapter `AL` und `AB`, die eine klare Richtung der Daten- und Ereignisflüsse vorgeben.
- **Paketstruktur**: Der FB ist im Paket `adapter::conversion::unidirectional` organisiert, was die Wiederverwendung in modularen Projekten erleichtert.

## Zustandsübersicht
Der Funktionsblock besitzt keinen eigenen Zustandsautomaten. Die gesamte Ablaufsteuerung erfolgt über die Ereigniskette des internen Netzwerks. Eine Zustandsüberwachung ist daher nicht erforderlich.

## Anwendungsszenarien
- **Protokollanpassung**: Wenn in einem verteilten System ein Adapter, der LWORD-Daten liefert, durch einen Adapter ersetzt werden muss, der nur BYTE-Daten verarbeitet.
- **Systemintegration**: Kopplung von Komponenten, die unterschiedliche Adapterformate verwenden (z. B. AL‑und AB‑Adapter), ohne Änderungen an den originären Bausteinen vorzunehmen.
- **Datenreduktion**: Gezielte Umwandlung von 64‑Bit‑LWORD in 8‑Bit‑BYTE, wenn die höheren Bytes nicht benötigt werden oder eine schmalere Schnittstelle erforderlich ist.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Funktion | Unterschied |
|----------|----------|-------------|
| `LWORD_TO_BYTE` | Reine Datentypkonvertierung ohne Adapter | Keine Adapter‑Schnittstelle; direkte Daten‑ und Ereignisports |
| `AB_TO_AL` | Umgekehrte Konvertierung (BYTE → LWORD) | Gegensätzliche Richtung; ebenfalls Composite mit Adaptern |
| `WORD_TO_BYTE` | Konvertierung von WORD (16 Bit) zu BYTE | Anderer Datentyp; ähnliche Struktur, aber andere Adaptertypen |

Der **AL_TO_AB** ist speziell auf die Verwendung der unidirektionalen Adapter `AL` und `AB` zugeschnitten und bietet eine saubere, wiederverwendbare Kapselung.

## Fazit
Der Funktionsblock `AL_TO_AB` stellt eine einfache, aber effektive Lösung zur Umwandlung eines LWORD-Adapter-Signals in ein BYTE-Adapter-Signal dar. Durch die Verwendung eines standardisierten IEC‑61131‑3‑Konverters und die konsequente Adapter‑Schnittstelle ist er leicht in bestehende Systeme integrierbar und fördert einen modularen, wartbaren Entwurf.