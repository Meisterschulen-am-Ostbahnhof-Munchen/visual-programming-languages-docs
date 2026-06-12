# ILOCK_FB_SR


![ILOCK_FB_SR](./ILOCK_FB_SR.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock ILOCK_FB_SR realisiert ein bistabiles set-dominantes SR-Latch (Set-Dominant Latch), das speziell für die Verwendung in Verriegelungsschaltungen (Interlocks) ausgelegt ist. Er erweitert ein einfaches SR-Latch um bidirektionale Adapter zur Kopplung mit anderen FB, sodass komplexe Verschaltungen und Prioritätslogiken abgebildet werden können.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung | Mitgeführte Daten |
|----------|--------------|-------------------|
| `REQ` | Ausführungsanforderung zur Verarbeitung der Set- und Reset-Signale | `S1`, `R` |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung | Mitgeführte Daten |
|----------|--------------|-------------------|
| `CNF` | Bestätigung der Ausführung, gibt den aktuellen Ausgangswert aus | `Q1` |

### **Daten-Eingänge**

| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| `S1` | `BOOL` | Set-Eingang |
| `R`  | `BOOL` | Reset-Eingang |

### **Daten-Ausgänge**

| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| `Q1` | `BOOL` | Ausgang des Latches (set-dominant) |

### **Adapter**

| Adapter | Typ | Richtung | Beschreibung |
|---------|-----|----------|--------------|
| `ILOCK_IN` | `adapter::types::bidirectional::AX2` | Socket | Empfängt Daten und Ereignisse von einem vorgelagerten Interlock-Baustein |
| `ILOCK_OUT` | `adapter::types::bidirectional::AX2` | Plug | Sendet Daten und Ereignisse an einen nachgelagerten Interlock-Baustein |

Die Adapter ermöglichen eine bidirektionale Verkettung von Interlock-Bausteinen, indem sie sowohl den Empfang von Freigabe-/Verriegelungssignalen als auch die Weitergabe von Zuständen erlauben.

## Funktionsweise

Der Kern des Bausteins ist ein internes SR-Latch (`FB_SR`), das **set-dominant** arbeitet: Wenn sowohl Set (`S1`) als auch Reset (`R`) gleichzeitig aktiv sind, setzt der Baustein den Ausgang `Q1` auf `TRUE`.

Die Logik wird durch drei OR-Gatter ergänzt:
- **OR_3_BOOL** vereint die Signale des Set-Eingangs (`S1`) mit den Rückmeldungen der benachbarten Interlock-Bausteine (`ILOCK_IN.DO1` und `ILOCK_OUT.DI1`). Das Ergebnis wird dem Set-Eingang des internen SR-Latches zugeführt.
- **OR_2_BOOL_IN** verknüpft das Set-Signal (`S1`) und das Signal des nachgeschalteten Interlock-Bausteins (`ILOCK_OUT.DI1`). Das Ergebnis wird über den Adapter `ILOCK_IN.DI1` an den vorgelagerten Baustein gesendet.
- **OR_2_BOOL_OUT** verknüpft das Set-Signal (`S1`) und das Signal des vorgelagerten Interlock-Bausteins (`ILOCK_IN.DO1`). Das Ergebnis wird über den Adapter `ILOCK_OUT.DO1` an den nachgelagerten Baustein gesendet.

Durch diese Struktur können mehrere Interlock-Bausteine kaskadiert werden: Ein Set-Signal kann durch einen vorgelagerten Baustein blockiert oder weitergeleitet werden. Gleichzeitig wird die Freigabe des eigenen Latches an die benachbarten Bausteine gemeldet.

## Technische Besonderheiten

- **Set-dominantes Verhalten**: Im Konfliktfall (S1=TRUE, R=TRUE) hat das Set-Signal Vorrang.
- **Adapterbasierte Kopplung**: Die bidirektionalen Adapter `ILOCK_IN` und `ILOCK_OUT` erlauben eine modulare Verschaltung, ohne dass direkte Daten- oder Ereignisverbindungen zwischen den Bausteinen manuell gezogen werden müssen.
- **Rückkopplung**: Die interne Logik verarbeitet sowohl externe Set- und Reset-Signale als auch Zustände benachbarter Bausteine, wodurch eine dynamische Verriegelungskette entsteht.

## Zustandsübersicht

Das interne SR-Latch kennt vier Zustände basierend auf den (kombinierten) Eingängen:

| S1 (nach Logik) | R | Q1 (vorheriger) | Q1 (neuer) |
|-----------------|---|-----------------|------------|
| 0 | 0 | 0 | 0 |
| 0 | 0 | 1 | 1 |
| 0 | 1 | 0 | 0 |
| 0 | 1 | 1 | 0 |
| 1 | 0 | 0 | 1 |
| 1 | 0 | 1 | 1 |
| 1 | 1 | 0 | 1 |
| 1 | 1 | 1 | 1 |

Die effektiven Werte für S1 (Set) ergeben sich aus der ODER-Verknüpfung von `S1`, `ILOCK_IN.DO1` und `ILOCK_OUT.DI1`.

## Anwendungsszenarien

- **Sicherheitsverriegelungen**: In Anlagen, bei denen mehrere Bedingungen gleichzeitig erfüllt sein müssen, bevor ein Vorgang freigegeben wird (z. B. Schutztüren, Not-Halt).
- **Kaskadierte Steuerungen**: Über- und untergeordnete Verriegelungseinheiten, die sich gegenseitig über Adapter beeinflussen (z. B. in Produktionslinien).
- **Prioritätsbasierte Setzungen**: Einsatz in Systemen, in denen ein Set-Signal Vorrang vor einem Reset haben muss, um sicherheitskritische Zustände zu erzwingen.

## Vergleich mit ähnlichen Bausteinen

- **IEC 61131 SR (reset-dominant)**: Standard-SR-Latch, bei dem im Konfliktfall der Reset gewinnt. Der ILOCK_FB_SR kehrt diese Priorität um.
- **IEC 61131 RS (set-dominant)**: Ähnliches Verhalten im Kern, jedoch ohne die adapterbasierte Verschaltung und die Logik zur Verkettung mehrerer Bausteine.
- **D-Flipflop**: Getaktete Speicherzelle, die nur bei einer Flanke übernimmt – hier liegt ein asynchrones, taktunabhängiges Latch vor.

Der ILOCK_FB_SR ist speziell für Interlock-Ketten optimiert, während einfache SR-Latches isoliert arbeiten.

## Fazit

Der ILOCK_FB_SR bietet eine flexible und robuste Lösung für set-dominante Verriegelungsschaltungen. Durch die Kombination eines SR-Latches mit bidirektionalen Adaptern und OR-Logik lassen sich beliebig komplexe Verkettungen aufbauen, ohne dass eine aufwändige Verdrahtung der Signale zwischen den Bausteinen erforderlich ist. Das set-dominante Verhalten ist insbesondere in sicherheitskritischen Anwendungen von Vorteil, wenn ein Set-Signal Vorrang haben muss.