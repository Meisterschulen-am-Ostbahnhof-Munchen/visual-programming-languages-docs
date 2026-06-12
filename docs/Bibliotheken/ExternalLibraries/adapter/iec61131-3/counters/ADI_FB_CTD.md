# ADI_FB_CTD


![ADI_FB_CTD](./ADI_FB_CTD.svg)

* * * * * * * * * *

## Einleitung

Der **ADI_FB_CTD** ist ein Abwärtszähler (Down Counter) für Werte vom Typ `DINT`, der ausschließlich über ADI‑Adapter kommuniziert. Er kapselt einen internen Standardzähler und ermöglicht das Herunterzählen, Laden eines Vorgabewerts sowie die Ausgabe des aktuellen Zählerstands – alles über einheitliche Adapterschnittstellen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der FB besitzt keine direkten Ereignis-Eingänge. Ereignisse werden über die Adapter-Sockets **CD**, **LD** und **PV** bereitgestellt.

### **Ereignis-Ausgänge**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| CNF  | Event | Bestätigungssignal, das nach jeder Verarbeitung eines eingehenden Ereignisses ausgegeben wird. |

### **Daten-Eingänge**

Keine direkten Daten-Eingänge; Daten werden über die Adapter-Sockets bereitgestellt.

### **Daten-Ausgänge**

Keine direkten Daten-Ausgänge; Daten werden über die Adapter-Plugs bereitgestellt.

### **Adapter**

| Name | Typ | Richtung | Beschreibung |
|------|-----|----------|--------------|
| CD   | `adapter::types::unidirectional::AX` | Socket (Eingang) | Ereignis zum Herunterzählen; der Datenwert (D1) wird als CD-Impuls an den internen Zähler weitergegeben. |
| LD   | `adapter::types::unidirectional::AX` | Socket (Eingang) | Ereignis zum Laden des Zählers mit dem aktuellen Wert von **PV**; der Datenwert (D1) signalisiert den Ladevorgang. |
| PV   | `adapter::types::unidirectional::ADI` | Socket (Eingang) | Vorgabewert (Preset Value) als `DINT`; das Ereignis (E1) löst eine Aktualisierung des internen PV-Registers aus. |
| Q    | `adapter::types::unidirectional::AX` | Plug (Ausgang) | Ausgangssignal, das anzeigt, ob der Zählerstand den Wert Null erreicht hat (z. B. `TRUE` bei Null). |
| CV   | `adapter::types::unidirectional::ADI` | Plug (Ausgang) | Aktueller Zählerstand als `DINT`; wird bei jeder Aktualisierung ausgegeben. |

## Funktionsweise

Der ADI_FB_CTD verwendet einen internen IEC‑61131‑Zähler (`FB_CTD_DINT`). Die gesamte Kommunikation erfolgt über ADI‑Adapter, die ein Ereignis (E1) und einen Datenwert (D1) kombinieren:

- Ein Ereignis am **CD**-Socket veranlasst den internen Zähler, den aktuellen Wert um **1** zu dekrementieren.
- Ein Ereignis am **LD**-Socket lädt den Zähler auf den Wert, der zuletzt über **PV** bereitgestellt wurde.
- Ein Ereignis am **PV**-Socket aktualisiert den Vorgabewert im internen Register; der Zähler selbst wird dabei nicht verändert. Erst ein nachfolgendes LD-Ereignis übernimmt den neuen Wert.

Alle eingehenden Ereignisse (CD, LD und PV) werden auf den gemeinsamen `REQ`-Eingang des internen Zählers geführt. Der interne Baustein unterscheidet anhand der Datenwerte, ob gezählt oder geladen werden soll. Nach Abschluss der Aktion wird das Ereignis `CNF` ausgelöst, das gleichzeitig die Ausgangsadapter **Q** und **CV** bedient und den `CNF`-Ereignisausgang setzt.

## Technische Besonderheiten

- **Immer aktive Ausgabe:** Der FB gibt bei **jeder** Aktualisierung (durch CD, LD oder PV) ein Ereignis auf dem **Q**-Adapter aus – auch wenn sich der zugehörige Datenwert nicht ändert. Ist eine auslösende Ausgabe nur bei tatsächlicher Zustandsänderung erwünscht, muss ein Filtrier-Baustein wie `AX_D_FF` vorgeschaltet werden.
- **Adapter‑basierte Schnittstelle:** Alle Ein‑ und Ausgänge sind als ADI‑Adapter realisiert. Dies ermöglicht eine lose Kopplung und einfache Wiederverwendbarkeit in modularen Steuerungsarchitekturen.
- **Interner Standardzähler:** Die Zähllogik basiert auf einem etablierten IEC‑61131‑Baustein und ist daher robust und zuverlässig.

## Zustandsübersicht

Der FB besitzt keinen eigenen Zustandsautomaten. Sein Verhalten wird durch den internen `FB_CTD_DINT` bestimmt, der sich in folgenden Betriebsarten befinden kann:

- **Laden:** Bei einem Ereignis am **LD**-Adapter wird der Zähler auf den aktuellen PV-Wert gesetzt.
- **Zählen:** Bei einem Ereignis am **CD**-Adapter wird der Zähler dekrementiert.
- **Warten:** Kein Ereignis liegt an; der Zähler behält seinen aktuellen Stand.

Nach jeder Verarbeitung ist der FB sofort bereit für das nächste Ereignis (keine Blockierung).

## Anwendungsszenarien

- **Werkstückzählung:** Ein Sensor meldet jedes durchlaufende Werkstück als Ereignis auf **CD**. Der Zähler dekrementiert von einem vorgegebenen Startwert (**PV**) bis auf Null. Bei Erreichen von Null kann über **Q** ein Signal (z. B. „Behälter voll“) ausgegeben werden.
- **Zeitverzögerung:** In Kombination mit einem Taktgeber fungiert der Zähler als Abwärtstimer, dessen Restzeit über **CV** ausgelesen wird.
- **Steuerung von Abläufen:** Der aktuelle Zählerstand (**CV**) dient als Parameter für nachgeschaltete Schritte (z. B. Positionierung, Mengensteuerung).

## Vergleich mit ähnlichen Bausteinen

- **CTU (Aufwärtszähler)** – zählt nur aufwärts; ADI_FB_CTD nur abwärts.
- **CTUD (Aufwärts/Abwärtszähler)** – kann in beide Richtungen zählen; ADI_FB_CTD ist auf eine Richtung spezialisiert.
- **Standard‑IEC‑61499‑Zähler** – verwenden separate Ereignis‑ und Datenports, während ADI_FB_CTD die Schnittstellen über Adapter vereinheitlicht.
- **ADI_FB_CTU** – strukturell identisch, jedoch mit Aufwärtszähllogik (ebenfalls als Adapterversion).

Der Vorteil der Adapterversion liegt in der modulareren, wiederverwendbaren Schnittstelle; der Nachteil ist der höhere Abstraktionsgrad und die erforderliche Filterung bei Bedarf.

## Fazit

Der ADI_FB_CTD ist ein zuverlässiger Abwärtszähler für `DINT`-Werte, der sich durch seine durchgängig adapterbasierte Schnittstelle ideal in lose gekoppelte Steuerungsarchitekturen einfügt. Die Tatsache, dass der **Q**-Ausgang bei jeder Aktualisierung auslöst, muss bei der Systemauslegung berücksichtigt werden. Dank des internen Standardzählers ist die Zähllogik robust und erprobt – ein bewährter Baustein für Abwärtszählszenarien.