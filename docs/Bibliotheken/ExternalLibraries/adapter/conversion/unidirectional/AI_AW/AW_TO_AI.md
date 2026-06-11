# AW_TO_AI


![AW_TO_AI](./AW_TO_AI.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AW_TO_AI** ist ein Composite FB, der einen unidirektionalen **WORD-Adapter (AW)** in einen unidirektionalen **INT-Adapter (AI)** konvertiert. Er kapselt die Typumwandlung von 16‑Bit Wort‑ in Integer‑Werte und ermöglicht so die nahtlose Integration von Komponenten, die unterschiedliche Adaptertypen verwenden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Über den angeschlossenen AW-Socket werden folgende Ereignisse empfangen:

| Name | Beschreibung |
|------|--------------|
| E1 (AW_IN.E1) | Trigger für die Konvertierung des anliegenden WORD‑Wertes |

### **Ereignis-Ausgänge**

Über den AI-Plug werden folgende Ereignisse gesendet:

| Name | Beschreibung |
|------|--------------|
| E1 (AI_OUT.E1) | Bestätigt die erfolgreiche Konvertierung und stellt den INT‑Wert bereit |

### **Daten-Eingänge**

Eingang über den AW-Socket:

| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| D1 (AW_IN.D1) | WORD | Der zu konvertierende 16‑Bit Wortwert |

### **Daten-Ausgänge**

Ausgang über den AI-Plug:

| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| D1 (AI_OUT.D1) | INT | Der konvertierte Integer‑Wert (16‑Bit vorzeichenbehaftet) |

### **Adapter**

| Richtung | Adapter | Typ | Beschreibung |
|----------|---------|-----|--------------|
| Socket (Eingang) | AW_IN | `adapter::types::unidirectional::AW` | Empfängt WORD‑Werte und zugehörige Ereignisse |
| Plug (Ausgang) | AI_OUT | `adapter::types::unidirectional::AI` | Sendet INT‑Werte und zugehörige Ereignisse |

## Funktionsweise

Der FB enthält eine Instanz des Standard‑Konvertierungsbausteins `F_WORD_TO_INT` aus der IEC‑61131‑Bibliothek. Das interne Netzwerk ist wie folgt verdrahtet:

1. Ein eingehendes Ereignis **AW_IN.E1** triggert den Eingang `REQ` des Konvertierungsbausteins.
2. Gleichzeitig wird der Datenwert **AW_IN.D1** auf den Eingang `IN` des Bausteins gelegt.
3. Der Baustein wandelt den WORD‑Wert in einen INT‑Wert um und gibt ihn an seinem Ausgang `OUT` aus.
4. Das vom Baustein erzeugte Bestätigungsereignis `CNF` wird direkt an **AI_OUT.E1** weitergeleitet.
5. Der konvertierte Integer‑Wert (Ausgang `OUT`) wird auf **AI_OUT.D1** geschrieben.

Die gesamte Verarbeitung erfolgt streng ereignisgesteuert: Nur bei einem neuen Ereignis am Eingang findet eine Umwandlung statt.

## Technische Besonderheiten

- **Reine Datenkonvertierung:** Es werden keine Zustände gespeichert oder zusätzliche Logik ausgeführt.
- **Standardbibliothek:** Der verwendete `F_WORD_TO_INT` ist ein etablierter Konvertierungsbaustein und stellt eine korrekte Abbildung des WORD‑Wertes (0…65535) auf den INT‑Wert (-32768…32767) sicher.
- **Unidirektional:** Sowohl der Eingangs‑ als auch der Ausgangsadapter sind unidirektional ausgelegt, d.h. sie übertragen Ereignis‑ und Datenflüsse nur in eine Richtung (Eingang → Ausgang).
- **Kein Datenverlust durch Typanpassung:** Die Bitbreite bleibt identisch (16 Bit), lediglich die Interpretation als vorzeichenlos (WORD) bzw. vorzeichenbehaftet (INT) ändert sich.

## Zustandsübersicht

Der FB ist ein **Composite FB** und besitzt keine eigene Zustandsmaschine (ECC). Das Verhalten wird vollständig durch die Verdrahtung des internen Bausteins bestimmt. Es existieren nur die impliziten Zustände:

- **Idle:** Warten auf ein Ereignis am Eingang.
- **Konvertierung aktiv:** Nach Eingang von `AW_IN.E1` bis zum Eintreffen von `Convert.CNF`.

## Anwendungsszenarien

- **Adapter-Konvertierung in heterogenen Systemen:** Ein Steuerungsmodul arbeitet mit INT‑Werten, eine angeschlossene Sensorik liefert jedoch WORD‑Daten über einen AW‑Adapter.
- **Bibliothekseinbindung:** Vorhandene Funktionsblöcke, die nur einen AI‑Adapter akzeptieren, sollen mit Komponenten verbunden werden, die einen AW‑Adapter bereitstellen.
- **Prototypsysteme:** Schnelle Kopplung verschiedener Bausteine während der Entwicklung, ohne die zugrundeliegenden Adapterdefinitionen zu ändern.

## Vergleich mit ähnlichen Bausteinen

- **AW_TO_AI** konvertiert **WORD → INT** (unidirektional).
- Vergleichbare Konverter aus derselben Bibliothek (`iec61131::conversion`) decken andere Typumwandlungen ab, z.B. `F_INT_TO_WORD` oder `F_WORD_TO_DINT`. Diese sind als traditionelle Funktionsblöcke ohne Adapter verfügbar.
- Falls eine bidirektionale Konversion oder andere Adapter‑Typen benötigt werden, sind ähnliche Composite‑Bausteine mit entsprechenden Umwandlungsblöcken denkbar (z.B. `AI_TO_AW`).

## Fazit

Der Composite FB **AW_TO_AI** stellt eine einfache und zuverlässige Möglichkeit dar, einen unidirektionalen WORD‑Adapter in einen INT‑Adapter umzuwandeln. Durch die Verwendung des IEC‑61131‑Standardbausteins bleibt die Konvertierung transparent und effizient. Der Baustein ist besonders dann nützlich, wenn unterschiedliche Adapter‑Typen in einem System harmonisiert werden müssen, ohne die ursprünglichen Komponenten zu verändern.