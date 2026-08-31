# AULI_SPLIT_5_UNGATED

> ℹ️ **UNGATED-Variante:** Dieser Baustein ist die ungegatete Version von [`AULI_SPLIT_5`](AULI_SPLIT_5.md). Er unterdrückt **keine** unveränderten Wiederholungen – jedes neu berechnete Ergebnis wird bedingungslos weitergegeben, auch ohne Wertänderung. Das ist wichtig für Verbraucher, die eine periodische Kadenz unabhängig von Wertänderung brauchen (z. B. Ableitungs-/Frequenzberechnungen, die sonst nicht gegen Null abklingen). Alle Angaben zu Änderungserkennung/Change-Gating weiter unten auf dieser Seite gelten **nicht** für diesen Baustein.

![AULI_SPLIT_5_UNGATED](./AULI_SPLIT_5_UNGATED.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AULI_SPLIT_5_UNGATED** dient als generischer Splitter für den unidirektionalen AULI-Adaptertyp. Er erzeugt aus einem eingehenden AULI-Signal fünf identische Ausgangssignale, die an separate Verbraucher weitergegeben werden können. Der Baustein ist als generischer FB realisiert und wird durch die Attribute `GenericClassName` und `TypeHash` für das Eclipse 4diac Core Framework parametrisiert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine Ereignis-Eingänge vorhanden.

### **Ereignis-Ausgänge**

Keine Ereignis-Ausgänge vorhanden.

### **Daten-Eingänge**

Keine Daten-Eingänge vorhanden.

### **Daten-Ausgänge**

Keine Daten-Ausgänge vorhanden.

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
| ---------- | ------ | ----- | -------------- |
| Socket | `IN` | `adapter::types::unidirectional::AULI` | Eingehender AULI-Adapter (Quelle) |
| Plug | `OUT1` | `adapter::types::unidirectional::AULI` | Erster ausgehender AULI-Adapter |
| Plug | `OUT2` | `adapter::types::unidirectional::AULI` | Zweiter ausgehender AULI-Adapter |
| Plug | `OUT3` | `adapter::types::unidirectional::AULI` | Dritter ausgehender AULI-Adapter |
| Plug | `OUT4` | `adapter::types::unidirectional::AULI` | Vierter ausgehender AULI-Adapter |
| Plug | `OUT5` | `adapter::types::unidirectional::AULI` | Fünfter ausgehender AULI-Adapter |

Das Interface besteht ausschließlich aus einem Socket und fünf Plugs desselben Typs. Alle Adapter sind unidirektional ausgelegt.

## Funktionsweise

Der FB leitet das am Socket `IN` ankommende AULI-Signal ohne Verzögerung oder Bearbeitung an alle fünf Plugs (`OUT1` … `OUT5`) weiter. Es findet eine reine **1-zu-5-Vervielfachung** statt. Der Baustein besitzt keine Logik, keine Zustände und keinen internen Puffer. Die Weitergabe erfolgt passiv: Sobald der Quell-Adapter Daten sendet, werden diese an alle Ausgänge repliziert.

## Technische Besonderheiten

- **Generischer Baustein**: Der FB ist als generischer Typ deklariert (`GenericClassName = 'GEN_AULI_SPLIT'`). Der konkret verwendete Typ wird erst zur Laufzeit durch das Eclipse 4diac Core Framework aufgelöst.
- **Unidirektionale Adapter**: Sämtliche Adapter verwenden den Typ `adapter::types::unidirectional::AULI`, der nur eine Datenflussrichtung von der Quelle zu den Senken erlaubt.
- **Keine Bedingungen oder Filter**: Das Eingangssignal wird ohne Qualitätsprüfung, Umwandlung oder Synchronisation auf alle Ausgänge verteilt.
- **Kompatibilität**: Der FB ist für den Einsatz in IEC 61499-2 konformen Systemen ausgelegt und erfordert das Importieren der Pakete `eclipse4diac::core::GenericClassName` und `eclipse4diac::core::TypeHash`.

## Zustandsübersicht

Der FB besitzt **keinen internen Zustandsautomaten**. Es existieren keine Zustände, keine Transitionen und keine Aktionen. Die Funktionalität beschränkt sich auf die passive Signalverteilung.

## Anwendungsszenarien

- **Signalverteilung**: Ein Sensorwert oder ein Steuersignal (z. B. ein AULI-basierter Datensfrom) muss an mehrere parallele Verarbeitungseinheiten oder Aktoren gesendet werden.
- **Testumgebungen**: In Simulations- oder Testsystemen kann das gleiche Eingangssignal gleichzeitig an mehrere Analyseblöcke oder Logfunktionen angelegt werden.
- **Redundante Ausgaben**: Wenn mehrere Subsysteme denselben Wert benötigen, jedoch keine kaskadierte Verkettung gewünscht ist.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Typ | Ausgänge | Besonderheit |
| ---------- | ----- | ---------- | -------------- |
| `AULI_SPLIT_5_UNGATED` | generischer Splitter | 5 | spezifisch für AULI-Adapter |
| `SPLIT_2` (nicht standardisiert) | generischer Splitter | 2 | meist für Datentypen wie INT oder BOOL |
| `F_SPLIT` (aus IEC 61499-Bibliotheken) | funktionaler Splitter | variabel | basiert auf ECC und Ereignissen |

Der `AULI_SPLIT_5_UNGATED` ist im Gegensatz zu ereignisbasierten Splittern **ereignislos** und rein adapterbasiert. Er lässt sich daher besonders in Datenflusssystemen ohne Taktsignal einsetzen.

- **[`AULI_SPLIT_5`](AULI_SPLIT_5.md)**: Die gegatete Variante – aktualisiert den Ausgang nur bei tatsächlicher Wertänderung.

## Änderungserkennung

Dieser Baustein führt **keine** Änderungserkennung durch. Jedes neu berechnete Ergebnis wird bedingungslos auf den Ausgang geschrieben und das zugehörige Adapter-Event gesendet, unabhängig davon, ob sich der Wert gegenüber dem vorherigen Durchlauf geändert hat.

## Fazit

Der `AULI_SPLIT_5_UNGATED` ist ein minimalistischer, aber nützlicher Funktionsblock zur Vervielfachung eines unidirektionalen AULI-Signals auf fünf Ausgänge. Seine generische Natur erlaubt eine flexible Parametrisierung im Eclipse-4diac-Framework. Aufgrund des fehlenden Zustandsautomaten und der reinen Durchleitung ist er extrem ressourcenschonend und für Hochgeschwindigkeits-Datenverteilungen geeignet.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
