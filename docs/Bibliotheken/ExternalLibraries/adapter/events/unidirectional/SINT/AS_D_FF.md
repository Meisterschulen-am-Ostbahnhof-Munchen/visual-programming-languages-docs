# AS_D_FF


![AS_D_FF](./AS_D_FF.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein **AS_D_FF** realisiert ein einfaches Datenlatch (D-Flipflop) auf Basis von Adaptern. Er speichert einen eingehenden Datenwert bei jedem eingehenden Ereignis und gibt den gespeicherten Wert als Ausgangssignal weiter. Der Baustein kapselt die Logik des 4diac-Standardbausteins `E_D_FF_ANY` und stellt seine Schnittstellen ausschließlich über unidirektionale Adapter vom Typ `adapter::types::unidirectional::AS` bereit. Dies ermöglicht eine modulare und standardisierte Einbindung in komplexere Systeme.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine direkten Ereigniseingänge. Der Baustein empfängt Ereignisse ausschließlich über den Adapter **I** (Socket). Das Ereignis wird am Adapter-Eingang `I.E1` bereitgestellt.

### **Ereignis-Ausgänge**

Keine direkten Ereignisausgänge. Der Baustein sendet Ereignisse ausschließlich über den Adapter **Q** (Plug). Das ausgegebene Ereignis erscheint am Adapter-Ausgang `Q.E1`.

### **Daten-Eingänge**

Keine direkten Dateneingänge. Der zu speichernde Datenwert wird über den Adapter **I** (Socket) als `I.D1` bereitgestellt.

### **Daten-Ausgänge**

Keine direkten Datenausgänge. Der gespeicherte Datenwert wird über den Adapter **Q** (Plug) als `Q.D1` ausgegeben.

### **Adapter**

| Adapter | Richtung | Typ | Beschreibung |
|---------|----------|-----|--------------|
| **I** | Socket (Eingang) | `adapter::types::unidirectional::AS` | Stellt das Eingangsereignis (`E1`) und den zu latchenden Datenwert (`D1`) bereit. |
| **Q** | Plug (Ausgang) | `adapter::types::unidirectional::AS` | Gibt ein Ausgangsereignis (`E1`) und den gespeicherten Datenwert (`D1`) aus. |

## Funktionsweise

Der Baustein **AS_D_FF** arbeitet als asynchroner Datenlatch.  
Bei jedem positiven Ereignis auf `I.E1` wird der aktuelle Wert von `I.D1` im internen Speicher des Bausteins übernommen. Unmittelbar danach wird ein Ereignis auf `Q.E1` ausgelöst, und der gespeicherte Wert steht auf `Q.D1` zur Verfügung.  
Diese Logik wird durch den intern verwendeten Baustein `E_D_FF_ANY` realisiert:

- `I.E1` → `E_D_FF_ANY.CLK`  
- `I.D1` → `E_D_FF_ANY.D`  
- `E_D_FF_ANY.EO` → `Q.E1`  
- `E_D_FF_ANY.Q` → `Q.D1`

Der Baustein verhält sich somit wie ein klassisches D-Flipflop, jedoch mit einer standardisierten Adapter-Schnittstelle anstelle von direkten Ein-/Ausgängen.

## Technische Besonderheiten

- **Adapter-basierte Kapselung**: Der gesamte Datenaustausch erfolgt ausschließlich über unidirektionale Adapter vom Typ `adapter::types::unidirectional::AS`. Dies erleichtert die Wiederverwendung in unterschiedlichen Kontexten und gewährleistet eine klare Trennung zwischen Ereignis- und Datenflüssen.
- **Interne Nutzung von `E_D_FF_ANY`**: Der Baustein greift auf den Standard-Funktionsbaustein `iec61499::events::E_D_FF_ANY` zurück, der eine bewährte und effiziente Implementierung eines D-Flipflops bietet.
- **Keine direkten E/A-Pins**: Der Baustein definiert selbst keine Ereignis- oder Dateneingänge/-ausgänge; die gesamte Kommunikation wird über die Adapter abgewickelt.
- **Unidirektionale Adapter**: Beide Adapter (I und Q) sind als unidirektional definiert, d.h. Ereignis- und Datenfluss erfolgen nur in eine Richtung (vom Socket zum Plug).

## Zustandsübersicht

Der Baustein besitzt keine explizite Zustandsmaschine. Sein Verhalten wird durch das interne D-Flipflop bestimmt, das zwei logische Zustände kennt:

- **Zustand 0**: Der gespeicherte Datenwert ist 0 (bzw. `FALSE`).
- **Zustand 1**: Der gespeicherte Datenwert ist 1 (bzw. `TRUE`).

Der Zustand wird durch ein Ereignis auf `I.E1` umgeschaltet (sofern sich der Datenwert geändert hat) und bleibt bis zum nächsten Ereignis erhalten.

## Anwendungsszenarien

- **Signalpufferung**: Zwischenspeichern eines digitalen Signals, das zu bestimmten Zeitpunkten übernommen werden soll (z.B. Sample-and-Hold).
- **Synchronisation**: Anpassen von asynchronen Datenströmen an einen taktgesteuerten Ablauf, indem ein Wert bei einem Ereignis festgehalten wird.
- **Modulare Verschaltung**: Einsatz in Systemen, die auf Adapter-Kommunikation basieren, um eine einheitliche Schnittstelle beizubehalten (z.B. in einer Kette von Verarbeitungsblöcken).
- **Einfache Zustandsspeicherung**: Realisierung von einfachen Speicherfunktionen in Automatisierungsanwendungen, ohne auf komplexe Speicherbausteine zurückgreifen zu müssen.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Eigenschaft | Unterschied zu AS_D_FF |
|----------|-------------|------------------------|
| **SR_FF** | Set-Reset-Flipflop | Hat separate Set- und Reset-Eingänge, kein Taktsignal. |
| **E_D_FF_ANY** | Reines D-Flipflop mit direkten E/A | Bietet keine Adapter-Schnittstelle; erfordert direkte Verbindungen. |
| **AS_FF_RS** (hypothetisch) | RS-Flipflop mit Adaptern | Verwendet zwei Adapter für Set und Reset, kein Taktsignal. |

Der **AS_D_FF** kombiniert die klare Logik eines D-Flipflops mit der Flexibilität einer Adapter-basierten Schnittstelle. Er eignet sich besonders für Systeme, die eine standardisierte, unidirektionale Kommunikation bevorzugen.

## Fazit

Der Funktionsbaustein **AS_D_FF** stellt eine praktische Kapselung eines D-Flipflops dar, die ausschließlich über Adapter kommuniziert. Sein internes Verhalten entspricht einem zuverlässigen Datenlatch, das auf jedes eingehende Ereignis reagiert. Die Verwendung von Adaptern erhöht die Modularität und Wiederverwendbarkeit, während die Implementation auf dem bewährten `E_D_FF_ANY` basiert. Der Baustein eignet sich ideal für alle Anwendungen, die eine einfache, ereignisgesteuerte Datenspeicherung mit standardisierter Schnittstelle erfordern.