# AUDI_TO_AB


![AUDI_TO_AB](./AUDI_TO_AB.svg)

* * * * * * * * * *
## Einleitung

Der **AUDI_TO_AB** Funktionsblock ist ein zusammengesetzter Baustein (Composite FB), der eine UDINT‑Schnittstelle (AUDI, 32‑Bit unsigned Integer) in eine BYTE‑Schnittstelle (AB, 8‑Bit) umwandelt. Er kapselt die Konvertierungslogik und stellt zwei unidirektionale Adapter bereit: einen Socket für den AUDI‑Eingang und einen Plug für den AB‑Ausgang. Der Baustein wird typischerweise eingesetzt, um Datenkommunikation zwischen Systemen zu ermöglichen, die unterschiedliche Datentypen über Adapter verwenden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| `AUDI_IN.E1` | Ereignis (über Adapter) | Trigger für die Datenkonvertierung – ein eingehendes Ereignis startet die Umwandlung des aktuellen UDINT‑Werts in einen BYTE‑Wert. |

### **Ereignis-Ausgänge**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| `AB_OUT.E1` | Ereignis (über Adapter) | Bestätigung der Konvertierung – nach erfolgreicher Umwandlung wird ein Ereignis ausgegeben, das dem nachgeschalteten System den neuen BYTE‑Wert signalisiert. |

### **Daten-Eingänge**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| `AUDI_IN.D1` | UDINT (32‑Bit) | Der umzuwandelnde 32‑Bit unsigned Integer‑Wert, der über den AUDI‑Adapter bereitgestellt wird. |

### **Daten-Ausgänge**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| `AB_OUT.D1` | BYTE (8‑Bit) | Der konvertierte 8‑Bit Wert, der über den AB‑Adapter ausgegeben wird. |

### **Adapter**

| Name | Typ | Richtung | Beschreibung |
|------|-----|----------|--------------|
| `AUDI_IN` | adapter::types::unidirectional::AUDI | Socket (Eingang) | Unidirektionaler Adapter, der Ereignisse und Daten vom Typ UDINT bereitstellt. |
| `AB_OUT` | adapter::types::unidirectional::AB | Plug (Ausgang) | Unidirektionaler Adapter, der Ereignisse und Daten vom Typ BYTE ausgibt. |

## Funktionsweise

1. Ein externes System sendet ein Ereignis über den Adapter `AUDI_IN` (E1).  
2. Dieses Ereignis triggert den internen Konvertierungsbaustein `F_UDINT_TO_BYTE` (aus der IEC 61131‑Bibliothek) über dessen `REQ`‑Eingang.  
3. Gleichzeitig wird der aktuelle Datenwert von `AUDI_IN.D1` an den `IN`‑Eingang des Konvertierungsbausteins übergeben.  
4. Der Konvertierungsbaustein wandelt den UDINT‑Wert in einen BYTE‑Wert um und legt das Ergebnis an seinem `OUT`‑Ausgang an.  
5. Nach Abschluss der Konvertierung sendet der `F_UDINT_TO_BYTE` ein Bestätigungsereignis (`CNF`), das an den `AB_OUT`‑Adapter (E1) weitergeleitet wird.  
6. Gleichzeitig wird der konvertierte BYTE‑Wert an `AB_OUT.D1` ausgegeben und steht dem empfangenden System zur Verfügung.

Die gesamte Verarbeitung erfolgt ereignisgesteuert und ohne Zwischenspeicherung – jedes eingehende Ereignis erzeugt genau ein ausgehendes Ereignis.

## Technische Besonderheiten

- **Composite‑Struktur**: Der Baustein ist als Netzwerk von Unterbausteinen realisiert. Er nutzt den vordefinierten Konvertierungsbaustein `F_UDINT_TO_BYTE` aus der IEC 61131‑Bibliothek, wodurch eine standardisierte und testbare Konvertierung gewährleistet wird.  
- **Unidirektionale Adapter**: Sowohl der Eingangs‑ als auch der Ausgangsadapter sind unidirektional. Dies reduziert die Kopplung und ermöglicht eine einfache Integration in Datenflüsse, die nur eine Richtung benötigen.  
- **Keine Zustandsspeicherung**: Der Baustein ist rein kombinatorisch (keine internen Zustände). Er reagiert auf jedes eingehende Ereignis sofort und gibt das Ergebnis ohne Verzögerung aus.  
- **Kompatibilität**: Erfüllt den Standard IEC 61499‑2 und kann in Umgebungen eingesetzt werden, die unidirektionale Adapter (AUDI/AB) unterstützen.

## Zustandsübersicht

Der Baustein besitzt keinen expliziten Zustandsautomaten. Er arbeitet ereignisgesteuert nach dem Prinzip „Eingangsereignis → Konvertierung → Ausgangsereignis“. Es gibt keine Warteschlangen oder Verzögerungen – die Verarbeitung ist atomar und erfolgt innerhalb eines einzigen Zyklus.

## Anwendungsszenarien

- **Datenanpassung in Adapter‑basierten Systemen**: Wenn eine Komponente oder ein Protokoll einen UDINT‑Wert über einen AUDI‑Adapter liefert, der nachgeschaltete Baustein aber einen BYTE‑Wert über einen AB‑Adapter erwartet, kann dieser Baustein zur nahtlosen Kopplung eingesetzt werden.  
- **Übergang von 32‑Bit auf 8‑Bit Schnittstellen**: Beispielsweise in der Sensor‑Aktor‑Kommunikation, wo ein Sensor 32‑Bit Rohdaten liefert, das Stellglied aber nur 8‑Bit Kommandos verarbeitet.  
- **Test- und Simulationsumgebungen**: Erlaubt das einfache Austauschen von Adaptern, ohne die gesamte Datenpfadlogik ändern zu müssen.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Beschreibung | Unterschied zu AUDI_TO_AB |
|----------|--------------|----------------------------|
| `F_UDINT_TO_BYTE` | Direkte Konvertierungsfunktion ohne Adapter | Erwartet Standard‑Ereignis‑ und Daten‑Schnittstellen; AUDI_TO_AB kapselt die Konvertierung in Adapter‑Signaturen. |
| `UDINT_TO_BYTE` (Composite mit Standard‑Ports) | Ähnliche Logik, aber mit SOCKET/PLUG‑Schnittstelle | Verwendet möglicherweise andere Adapter‑Typen oder bidirektionale Schnittstellen; AUDI_TO_AB ist auf unidirektionale Adapter spezialisiert. |

## Fazit

Der **AUDI_TO_AB** Funktionsblock bietet eine saubere, wiederverwendbare Lösung zur Typumwandlung zwischen UDINT‑ und BYTE‑Werten unter Verwendung unidirektionaler Adapter. Seine kompakte Composite‑Struktur, die auf einer standardisierten IEC‑Konvertierungsfunktion aufbaut, macht ihn zuverlässig und einfach integrierbar. Durch die ereignisgesteuerte Architektur ohne Zustandsspeicherung eignet er sich besonders für zeitkritische Datenflüsse in der Automatisierungstechnik.