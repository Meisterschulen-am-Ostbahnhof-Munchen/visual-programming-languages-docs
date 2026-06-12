# AI_TO_AL


![AI_TO_AL](./AI_TO_AL.svg)

* * * * * * * * * *
## Einleitung

Der Composite-Funktionsbaustein **AI_TO_AL** dient zur Umwandlung eines INT-Werts, der über den unidirektionalen AI-Adapter (Typ `adapter::types::unidirectional::AI`) bereitgestellt wird, in einen LWORD-Wert, der über den unidirektionalen AL-Adapter (Typ `adapter::types::unidirectional::AL`) ausgegeben wird. Der Baustein kapselt die Konvertierungslogik und ermöglicht so eine saubere Trennung zwischen INT- und LWORD-basierten Adapter-Schnittstellen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine eigenständigen Ereignis-Eingänge am Baustein. Die Ereignissteuerung erfolgt ausschließlich über den integrierten Socket `AI_IN`, der das Ereignis `E1` als Trigger für die Konvertierung bereitstellt.

### **Ereignis-Ausgänge**
Keine eigenständigen Ereignis-Ausgänge am Baustein. Das Ergebnisereignis der internen Konvertierung wird über den Plug `AL_OUT` als Ereignis `E1` ausgegeben.

### **Daten-Eingänge**
Keine eigenständigen Daten-Eingänge am Baustein. Der zu konvertierende INT-Wert wird über den Socket `AI_IN` (Datenpunkt `D1`) in den Baustein eingelesen.

### **Daten-Ausgänge**
Keine eigenständigen Daten-Ausgänge am Baustein. Der konvertierte LWORD-Wert wird über den Plug `AL_OUT` (Datenpunkt `D1`) ausgegeben.

### **Adapter**

| Bezeichnung | Typ | Richtung | Kommentar |
|-------------|-----|----------|-----------|
| `AI_IN` | `adapter::types::unidirectional::AI` | Socket (Input) | INT-Adapter-Eingang |
| `AL_OUT` | `adapter::types::unidirectional::AL` | Plug (Output) | LWORD-Adapter-Ausgang |

## Funktionsweise

1. Ein eingehendes Ereignis `E1` am Adapter `AI_IN` aktiviert die Datenkonvertierung.
2. Der interne Funktionsbaustein `F_INT_TO_LWORD` (aus der Bibliothek `iec61131::conversion`) wird über dessen Ereigniseingang `REQ` getriggert und wandelt den an `IN` anliegenden INT-Wert in einen LWORD-Wert um.
3. Nach Abschluss der Konvertierung signalisiert der Baustein dies über den Ereignisausgang `CNF`.
4. Dieses Ereignis wird an den Adapter `AL_OUT` als Ereignis `E1` weitergeleitet und gibt gleichzeitig den konvertierten LWORD-Wert über `D1` aus.

Die Datenpfade lauten:
- `AI_IN.D1` → `Convert.IN`
- `Convert.OUT` → `AL_OUT.D1`

Die Ereignispfade lauten:
- `AI_IN.E1` → `Convert.REQ`
- `Convert.CNF` → `AL_OUT.E1`

## Technische Besonderheiten

- **Composite-Baustein:** Der `AI_TO_AL` ist als Composite implementiert und enthält keine eigene algorithmische Logik. Er delegiert die Konvertierung vollständig an den definierten Funktionsbaustein `F_INT_TO_LWORD`.
- **Standardkonvertierung:** Die verwendete Konvertierungsfunktion ist Teil der IEC 61131-Bibliothek und gewährleistet eine standardkonforme Typumwandlung von INT (16-Bit) nach LWORD (64-Bit).
- **Adapterbasiert:** Der Baustein arbeitet ausschließlich über die spezifizierten Adapter-Schnittstellen und kann daher nahtlos in eine adapterbasierte Architektur integriert werden.
- **Lizenz und Version:** Der Baustein steht unter der Eclipse Public License 2.0 (EPL-2.0) und wurde in Version 1.0 von der HR Agrartechnik GmbH veröffentlicht.
- **Erstellungsdatum:** 17. Februar 2026, Autor: Franz Höpfinger.

## Zustandsübersicht

Als Composite-Baustein besitzt `AI_TO_AL` keinen eigenen internen Zustandsautomaten. Die gesamte Zustandslogik wird durch den integrierten Baustein `F_INT_TO_LWORD` gesteuert, der seinerseits eine einfache Anforderungs-Bestätigungs-Sequenz (REQ/CNF) ausführt. Der Baustein ist daher rein datenflussgetrieben und verfügt über keine persistenten Zustände.

## Anwendungsszenarien

- **Buskopplung:** Wenn ein Sensor oder Aktor einen INT-Wert über einen AI-Adapter liefert, das nachgelagerte System aber einen LWORD-Wert über einen AL-Adapter erwartet (z. B. bei Anbindung an einen Feldbus mit 64-Bit-Datentypen).
- **Protokollanpassung:** In heterogenen Automatisierungssystemen, in denen verschiedene Adaptertypen (AI und AL) miteinander verbunden werden müssen.
- **Datenaufbereitung:** Vor der Weiterverarbeitung von INT-Daten in einer Steuerung, die intern mit LWORD arbeitet.

## Vergleich mit ähnlichen Bausteinen

- **Andere Konvertierungsadapter:** Es existieren ähnliche Composite-Bausteine für andere Datentyp-Paare wie z. B. `WORD_TO_DWORD`, `BYTE_TO_WORD` oder `DINT_TO_LWORD`. Der `AI_TO_AL` ist auf die spezifische Kombination INT → LWORD ausgelegt.
- **Direkte Konvertierung:** Alternativ könnte die Konvertierung auch ohne Adapter-Kapselung direkt mit `F_INT_TO_LWORD` erfolgen. Der Vorteil des `AI_TO_AL` liegt in der standardisierten Adapter-Schnittstelle, die den Austausch und die Wiederverwendbarkeit in adapterbasierten Netzwerken erleichtert.

## Fazit

Der `AI_TO_AL`-Funktionsbaustein ist ein einfacher, aber wertvoller Adapter-Konverter, der die Lücke zwischen INT- und LWORD-basierten Adapter-Schnittstellen schließt. Durch die Kapselung der Konvertierungslogik in einem Composite-Baustein bleibt die Applikationslogik übersichtlich und die Wiederverwendbarkeit wird erhöht. Er eignet sich besonders für den Einsatz in modularen Automatisierungssystemen, die auf der unidirektionalen Adapter-Kommunikation basieren.