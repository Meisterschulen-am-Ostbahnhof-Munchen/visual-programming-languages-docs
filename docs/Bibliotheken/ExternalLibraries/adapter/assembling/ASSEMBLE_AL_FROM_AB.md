# ASSEMBLE_AL_FROM_AB


![ASSEMBLE_AL_FROM_AB](./ASSEMBLE_AL_FROM_AB.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock `ASSEMBLE_AL_FROM_AB` fasst acht einzelne Byte-Informationen aus Adaptern des Typs `AB` (unidirektional) zu einem zusammenhängenden 64-Bit-Datenwort (LWORD) zusammen. Das Ergebnis wird über einen Ausgangsadapter des Typs `AL` ausgegeben. Der Baustein dient als zentrale Sammelstelle für Byte-orientierte Daten und ermöglicht eine modulare und übersichtliche Datenstrukturierung.

## Schnittstellenstruktur

### Ereignis-Eingänge

Keine. Die Ereignissteuerung erfolgt ausschließlich über die angeschlossenen Adapter.

### Ereignis-Ausgänge

Keine. Das Ausgangsereignis wird über den Adapter `OUT` bereitgestellt.

### Daten-Eingänge

Keine. Die Dateneingänge werden über die Byte-Adapter eingespeist.

### Daten-Ausgänge

Keine. Das zusammengesetzte LWORD wird über den Adapter `OUT` ausgegeben.

### Adapter

**Sockets (Eingangsadapter)**

| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| `BYTE_00` | `adapter::types::unidirectional::AB` | Byte 0 (niederwertigstes Byte) |
| `BYTE_01` | `adapter::types::unidirectional::AB` | Byte 1 |
| `BYTE_02` | `adapter::types::unidirectional::AB` | Byte 2 |
| `BYTE_03` | `adapter::types::unidirectional::AB` | Byte 3 |
| `BYTE_04` | `adapter::types::unidirectional::AB` | Byte 4 |
| `BYTE_05` | `adapter::types::unidirectional::AB` | Byte 5 |
| `BYTE_06` | `adapter::types::unidirectional::AB` | Byte 6 |
| `BYTE_07` | `adapter::types::unidirectional::AD` | Byte 7 (höchstwertiges Byte) |

Jeder Byte-Adapter stellt ein Ereignis (`E1`) und ein Datenbyte (`D1`) bereit.

**Plugs (Ausgangsadapter)**

| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| `OUT` | `adapter::types::unidirectional::AL` | Ausgang: zusammengesetztes LWORD; Ereignisausgang über `E1`, Datenwert über `D1` |

## Funktionsweise

Der Baustein ist als Composite-FB realisiert und enthält zwei interne Funktionsblöcke: `ASSEMBLE_LWORD_FROM_BYTES` und `E_D_FF_ANY`.

1. **Datensammlung**: Sobald einer der acht Byte-Adapter (`BYTE_00` … `BYTE_07`) ein Ereignis an seinem Ausgang `E1` liefert, wird dieses Ereignis an den Eingang `REQ` von `ASSEMBLE_LWORD_FROM_BYTES` weitergeleitet. Gleichzeitig werden die zugehörigen Byte-Werte von jedem Adapter an die entsprechenden Dateneingänge des Assembler-Blocks geführt (`BYTE_00` … `BYTE_07`).

2. **Zusammenfügung**: Der interne Baustein `ASSEMBLE_LWORD_FROM_BYTES` setzt die acht Bytes in der Reihenfolge `BYTE_00` bis `BYTE_07` zu einem 64-Bit-Wort (LWORD) zusammen. `BYTE_00` ist das niederwertigste Byte, `BYTE_07` das höchstwertige. Nach Abschluss der Operation wird ein Bestätigungsereignis (`CNF`) ausgegeben und das zusammengesetzte LWORD an seinem Datenausgang bereitgestellt.

3. **Pufferung und Ausgabe**: Das Ereignis `CNF` triggert den flankengesteuerten Flip-Flop `E_D_FF_ANY`. Dieser übernimmt den aktuellen LWORD-Wert und speichert ihn zwischen. Bei jeder positiven Flanke am Takteingang (`CLK`) wird der Wert am Datenausgang `Q` aktualisiert. Der Ausgang `Q` ist mit dem Datenausgang `D1` des Adapter-Plugs `OUT` verbunden. Das gespeicherte Ereignis `EO` des Flip-Flops wird als Ausgangsereignis `E1` des Adapter-Plugs `OUT` bereitgestellt.

Somit wird bei jeder Aktualisierung eines der acht Byte-Eingänge der gesamte LWORD neu berechnet und über den Ausgangsadapter ausgegeben.

## Technische Besonderheiten

- **Adapter-basierte Schnittstellen**: Der Baustein verwendet ausschließlich Adapter für die Ein- und Ausgabe. Dies ermöglicht eine flexible und lose Kopplung mit anderen Komponenten, die denselben Adaptertyp nutzen.
- **Komposit-Architektur**: Die interne Struktur ist aus bewährten Standardbausteinen aufgebaut (`ASSEMBLE_LWORD_FROM_BYTES` und `E_D_FF_ANY`). Dadurch wird die Komplexität verborgen und die Wartbarkeit erhöht.
- **Pufferung durch Flip-Flop**: Der `E_D_FF_ANY` puffert den assemblierten Wert und gibt ihn erst nach Abschluss der Assemblierung weiter. Dies vermeidet inkonsistente Ausgaben während der Aktualisierung einzelner Bytes und stellt sicher, dass immer ein vollständiger Datenwert anliegt.
- **Ereignissynchronisation**: Alle Byte-Adaptersignale werden auf einen gemeinsamen `REQ`-Eingang geführt. Dadurch wird jede Änderung eines beliebigen Bytes sofort verarbeitet. Die Zusammenführung aller Bytes erfolgt jedoch stets auf Basis der aktuell anliegenden Werte.

## Zustandsübersicht

Da es sich um einen Composite-FB handelt, besitzt er keinen eigenen Zustandsautomaten. Der innerliegende `E_D_FF_ANY` besitzt einen internen Zustand: den gespeicherten LWORD-Wert. Dieser ändert sich nur bei positiven Flanken am Takteingang, also nach jeder erfolgreichen Assemblierung. Der Zustand bleibt erhalten, bis eine erneute Assemblierung ausgelöst wird.

## Anwendungsszenarien

- **Datenaggregation in Sensornetzwerken**: Mehrere Byte-orientierte Sensoren (z. B. Temperatur, Druck, Feuchte) werden über separate Adapter angebunden. Der Baustein setzt sie zu einem 64-Bit-Datentelegramm zusammen, das an eine zentrale Steuerung weitergeleitet wird.
- **Protokollkonvertierung**: Ein Byte-Stream, der über mehrere Adapter eingeht (z. B. serielle Schnittstelle mit 8 Nutzbytes), wird in ein einzelnes LWORD umgewandelt, das für weitere Verarbeitungsschritte einfacher zu handhaben ist.
- **Modulare E/A-Erweiterungen**: In einer modularen Automatisierungslösung können acht digitale/analoge Byte-Eingänge (z. B. über I/O-Module) zu einer gemeinsamen 64-Bit-Variablen zusammengefasst werden.

## Vergleich mit ähnlichen Bausteinen

- **`ARRAY_TO_LWORD`-Bausteine**: Diese Bausteine arbeiten meist mit Arrays als Eingang und haben eine andere Schnittstelle (keine Adapter). Der `ASSEMBLE_AL_FROM_AB` bietet eine adapterbasierte, ereignisgesteuerte Alternative, die besser in modulare, typisierte Adapterstrukturen passt.
- **Multiplexer (MUX)**: Ein Multiplexer wählt einen von mehreren Eingängen aus, während dieser Baustein alle Eingänge gleichzeitig zu einem größeren Datenwort kombiniert.
- **Direkte Bitverkettung**: Ohne diesen Baustein müsste die Byte-Zusammenführung manuell durch bitweise Verschiebung und Oder-Verknüpfung erfolgen. Der `ASSEMBLE_AL_FROM_AB` kapselt diese Logik und reduziert den Entwicklungs- und Testaufwand.

## Fazit

Der `ASSEMBLE_AL_FROM_AB` ist ein spezialisierter Funktionsblock für die modulare und ereignisgesteuerte Zusammenführung von acht Byte-Daten zu einem LWORD. Durch seine ausschließliche Verwendung von Adaptern eignet er sich hervorragend für den Einsatz in adapterbasierten Architekturen und fördert eine klare Trennung von Datenquellen und -senken. Die integrierte Pufferung über den Flip-Flop und die Auslösung über jedes eingehende Ereignis stellen sicher, dass stets ein konsistenter, vollständiger Datenwert ausgegeben wird. Der Baustein vereinfacht die Datenaggregation erheblich und trägt zu einer wartbaren und wiederverwendbaren Steuerungslogik bei.