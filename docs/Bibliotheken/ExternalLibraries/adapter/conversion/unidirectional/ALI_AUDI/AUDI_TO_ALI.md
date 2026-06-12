# AUDI_TO_ALI


![AUDI_TO_ALI](./AUDI_TO_ALI.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AUDI_TO_ALI** ist ein Composite-Baustein, der eine Brücke zwischen einem **AUDI**-Adapter (vom Typ *UDINT*) und einem **ALI**-Adapter (vom Typ *LINT*) bereitstellt. Er wandelt eingehende UDINT-Werte über eine standardisierte Konvertierungsfunktion in LINT-Werte um und leitet sie an den Ausgangsadapter weiter. Der Baustein wird typischerweise in Anwendungen eingesetzt, die unterschiedliche Adress- oder Integertypen innerhalb eines 4diac-Adapterkonzepts verbinden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Beschreibung |
|------|--------------|
| *keine eigenen Ereignis-Eingänge* | Die Ereignissteuerung erfolgt über den internen Socket AUDI_IN.E1. |

### **Ereignis-Ausgänge**

| Name | Beschreibung |
|------|--------------|
| *keine eigenen Ereignis-Ausgänge* | Die Ereignisweitergabe erfolgt über den internen Plug ALI_OUT.E1. |

### **Daten-Eingänge**

| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| *keine eigenen Daten-Eingänge* | – | Der Datenwert wird vom Socket AUDI_IN.D1 geliefert. |

### **Daten-Ausgänge**

| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| *keine eigenen Daten-Ausgänge* | – | Der konvertierte Wert wird über den Plug ALI_OUT.D1 bereitgestellt. |

### **Adapter**

| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| **AUDI** (unidirektional) | `AUDI_IN` | Socket (Eingang) | UDINT-Datenadapter, der einen Wert über das Ereignis E1 und das Datum D1 bereitstellt. |
| **ALI** (unidirektional) | `ALI_OUT` | Plug (Ausgang) | LINT-Datenadapter, der den konvertierten Wert über das Ereignis E1 und das Datum D1 ausgibt. |

## Funktionsweise

Der Baustein arbeitet als reine **Typkonvertierungsbrücke** für Adapter:

1. **Ereignisempfang**: Ein Ereignis auf dem Socket `AUDI_IN.E1` aktiviert den internen Konvertierungsbaustein `F_UDINT_TO_LINT` über dessen Ereigniseingang `REQ`.
2. **Datenkonvertierung**: Der aktuelle UDINT-Wert von `AUDI_IN.D1` wird auf den Dateneingang `IN` des Konverters gelegt. `F_UDINT_TO_LINT` führt die IEC-61131-konforme Umwandlung von einer vorzeichenlosen 32‑Bit-Ganzzahl (UDINT) in eine vorzeichenbehaftete 64‑Bit-Ganzzahl (LINT) durch.
3. **Ausgabe**: Nach erfolgreicher Konvertierung signalisiert der Konverter mit `CNF`, dass der Ausgangswert gültig ist. Dieses Ereignis wird direkt an den Plug `ALI_OUT.E1` weitergegeben, und der konvertierte LINT-Wert von `Convert.OUT` wird auf `ALI_OUT.D1` gelegt.

Die gesamte Verarbeitung ist **ereignisgesteuert** und erfolgt innerhalb eines einzigen Ausführungsschrittes (ohne zusätzliche Verzögerung).

## Technische Besonderheiten

- **Composite-Baustein** – er enthält keine eigene Logik, sondern delegiert die Konvertierung vollständig an den IEC-61131-Baustein `F_UDINT_TO_LINT`.
- **Adapter-orientierte Schnittstelle** – alle Ein- und Ausgaben erfolgen über standardisierte unidirektionale Adapter (`AUDI` und `ALI`), was eine einfache Integration in bestehende Adapter-Netzwerke ermöglicht.
- **Lizenz & Copyright** – Der Baustein unterliegt der **Eclipse Public License 2.0** und wurde von **HR Agrartechnik GmbH** entwickelt (Stand 2026).
- **Typsicherheit** – die Konvertierung von UDINT (unsigned 32 Bit) nach LINT (signed 64 Bit) ist verlustfrei, da der Wert einfach vorzeichenerweitert wird.
- **Paketname** – im CompilerInfo ist der Baustein unter `adapter::conversion::unidirectional` organisiert.

## Zustandsübersicht

Als Composite-Baustein besitzt `AUDI_TO_ALI` keine eigenen Zustände. Die Zustandslogik liegt innerhalb des integrierten `F_UDINT_TO_LINT`-Bausteins, der nach jedem `REQ`-Ereignis in einen Verarbeitungszustand übergeht und mit `CNF` quittiert.

## Anwendungsszenarien

- **Übergang zwischen unterschiedlichen Automatisierungsprotokollen** – wenn ein System UDINT-Werte über AUDI-Adapter liefert, das Zielsystem aber LINT-Werte über ALI-Adapter erwartet.
- **Datenanpassung in Adapter-Hierarchien** – Umleitung von 32‑Bit‑Zählerwerten (z. B. Drehzahl, Impulszähler) auf einen 64‑Bit‑Bus.
- **Migration** – Altanlagen mit UDINT-Bereichen können ohne Änderung der Adapterstruktur an neue 64‑Bit‑Schnittstellen angebunden werden.
- **Testumgebungen** – einfaches Einschleifen einer Typkonvertierung zwischen zwei Adaptern, ohne separate Konvertierungsbausteine im Netzwerk.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Typ | Besonderheit |
|----------|-----|--------------|
| `F_UDINT_TO_LINT` | reiner Konverter | keine Adapter, direkte Daten-E/A; kein Ereignis-Handling über Adapter, erfordert eigene Ansteuerung. |
| `AUDI_TO_ALI` (dieser) | Adapter-Konverter | kapselt die Konvertierung in einer adapterbasierten Schnittstelle; Ereignisse und Daten werden automatisch über die Adapter weitergeleitet. |
| `ALI_TO_AUDI` (hypothetisch) | Adapter-Konverter | würde LINT rückwärts nach UDINT wandeln (potenziell verlustbehaftet). |

Der **Hauptunterschied** zu einer direkten Verwendung von `F_UDINT_TO_LINT` ist die nahtlose Einbindung in Adapter-Netzwerke und die Vermeidung zusätzlicher Leitungen für Ereignis- und Datenverbindungen.

## Fazit

Der **AUDI_TO_ALI**-Funktionsblock ist ein praktischer Adapter-Konverter, der die Lücke zwischen einem UDINT-basierten AUDI-Adapter und einem LINT-basierten ALI-Adapter schließt. Durch die interne Verwendung des standardisierten IEC-61131-Konverters `F_UDINT_TO_LINT` ist die Umwandlung effizient und typsicher. Der Baustein eignet sich besonders für modulare Architekturen, bei denen unterschiedliche Adressbreiten aufeinander treffen, und vereinfacht die Wiederverwendung von Adapter-Schnittstellen in heterogenen Automatisierungsumgebungen.