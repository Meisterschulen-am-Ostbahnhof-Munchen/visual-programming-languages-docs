# AW_D_FF


![AW_D_FF](./AW_D_FF.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AW_D_FF** realisiert ein datengesteuertes Flipflop (D‑Latch) nach IEC 61499. Er übernimmt einen binären Datenwert an seinem Eingang und gibt diesen taktgesteuert an seinem Ausgang weiter. Die Schnittstelle erfolgt ausschließlich über Adapter, was eine modulare und flexible Einbindung in bestehende Komponenten ermöglicht.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine direkten Ereignis-Eingänge auf FB‑Ebene. Die Ereignissteuerung erfolgt über den Eingangsadapter **I**.

### **Ereignis-Ausgänge**
Keine direkten Ereignis-Ausgänge auf FB‑Ebene. Die Ereignisausgabe erfolgt über den Ausgangsadapter **Q**.

### **Daten-Eingänge**
Keine direkten Daten-Eingänge auf FB‑Ebene. Die Datenübergabe erfolgt über den Eingangsadapter **I**.

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge auf FB‑Ebene. Die Datenausgabe erfolgt über den Ausgangsadapter **Q**.

### **Adapter**

| Adapter | Typ | Beschreibung |
|---------|-----|--------------|
| **I** (Socket) | `adapter::types::unidirectional::AW` | Eingangsadapter – erhält das zu latchende Datum (D1) und das Taktsignal (E1). |
| **Q** (Plug) | `adapter::types::unidirectional::AW` | Ausgangsadapter – gibt das latched Datum (D1) sowie ein Bestätigungsereignis (E1) aus. |

Beide Adapter sind vom gleichen unidirektionalen Typ und kapseln jeweils ein Ereignis und einen Datenwert.

## Funktionsweise

Der Baustein arbeitet intern mit dem IEC‑61499-Standardbaustein `E_D_FF_ANY`.  
Bei einer positiven Flanke des Taktsignals (Ereignis `E1` am Adapter **I**) wird der aktuelle Datenwert (`D1`) übernommen und am Ausgang bereitgestellt. Der Ausgangswert bleibt so lange erhalten, bis eine neue positive Taktflanke einen neuen Wert übernimmt.

Die logische Tabelle (D‑Flipflop) lautet:

| Takt (E1) | Eingang D | Ausgang Q (nach Takt) |
|-----------|-----------|----------------------|
| ↑         | 0         | 0                    |
| ↑         | 1         | 1                    |
| sonst     | beliebig  | unverändert          |

## Technische Besonderheiten

- **Adapterbasierte Schnittstelle**: Der FB verwendet ausschließlich Adapter für die Kommunikation, was eine lose Kopplung und einfache Wiederverwendung in verschiedenen Kontexten ermöglicht.
- **Standardkonformität**: Entwickelt gemäß IEC 61499‑1 Annex A und unter der Eclipse Public License 2.0 (EPL‑2.0) lizenziert.
- **Interne Implementierung**: Nutzt den vordefinierten Baustein `E_D_FF_ANY`, der ein allgemeines D‑Flipflop bereitstellt.
- **Unidirektionaler Datenfluss**: Die Adapter sind unidirektional ausgelegt, d. h. der Daten- und Ereignisfluss ist nur in eine Richtung definiert.

## Zustandsübersicht

Ein D‑Flipflop besitzt zwei stabile Zustände für den Ausgang Q (logisch 0 oder 1). Der Zustandswechsel erfolgt ausschließlich bei einer steigenden Flanke des Taktsignals:

- **Zustand 0**: Ausgang Q = 0 (solange kein Takt mit D=1 eintrifft)
- **Zustand 1**: Ausgang Q = 1 (nach einem Takt mit D=1, bis ein Takt mit D=0 eintrifft)

Es gibt keinen internen weiteren Zustandsautomaten; die Funktionalität ist rein speichernd.

## Anwendungsszenarien

- **Synchronisation asynchroner Signale**: Ein stabiler Datenwert wird zu einem definierten Zeitpunkt (Takt) übernommen.
- **Zustandsregister**: Als 1‑Bit‑Speicher in einfachen Steuerungslogiken.
- **Datenpuffer**: Kurzzeitiges Zwischenspeichern eines Binärwerts für nachfolgende Verarbeitungsschritte.
- **Taktgesteuerte Schwellwertentscheidungen**: Nur bei Taktflanke wird ein Eingangswert als gültig betrachtet.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Eigenschaft | Unterschied zu AW_D_FF |
|----------|-------------|------------------------|
| **RS‑Flipflop** | Setzt/rücksetzt asynchron | AW_D_FF benötigt Takt, keine getrennten Set‑/Reset‑Eingänge. |
| **T‑Flipflop** | Toggelt bei Takt | AW_D_FF übernimmt den Wert von D, keine Toggle‑Funktion. |
| **JK‑Flipflop** | Universell (Set, Reset, Toggle) | AW_D_FF ist einfacher (nur D‑Eingang), kein Toggle‑Modus. |
| **E_D_FF_ANY** | Direkt nutzbar mit Events/Daten | AW_D_FF kapselt diesen Baustein und bietet eine Adapter‑Schnittstelle. |

## Fazit

Der **AW_D_FF** ist ein kompakter und standardkonformer D‑Flipflop‑Baustein, der durch seine Adapter‑Schnittstelle besonders flexibel in modularen IEC‑61499‑Anwendungen einsetzbar ist. Er bietet eine zuverlässige taktgesteuerte Datenübernahme und eignet sich ideal für synchronisierte Speicheroperationen in industriellen Steuerungssystemen.