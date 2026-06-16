# ATM_AX_TLIM


![ATM_AX_TLIM](./ATM_AX_TLIM.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock **ATM_AX_TLIM** ist ein standardisierter Zeitüberwachungsbaustein (Timer) mit einer speziellen Adapter-Schnittstelle. Er realisiert eine Zeitbegrenzung (Time-Limiting / Timeout) für boolesche Eingangssignale. Der Baustein kommuniziert über Adapter statt über einzelne Ereignis- und Datenports, was eine flexible und gekapselte Integration in industrielle Steuerungssysteme ermöglicht.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Name  | Typ    | Kommentar                              |
|-------|--------|----------------------------------------|
| EIPT  | Event  | Set Preset Time (nicht auslösend)      |

### **Ereignis-Ausgänge**
Der Baustein besitzt keine separaten Ereignis-Ausgänge. Die Ereignisweiterleitung erfolgt ausschließlich über den Adapterausgang **Q**, der nach einer Änderung des Ausgangssignals ein Ereignis auf seinem `E1`-Port auslöst.

### **Daten-Eingänge**
Es existieren keine direkten Dateneingänge. Die erforderlichen Daten (Eingangssignal IN und Zeitgrenze PT) werden über die entsprechenden Adapterports bereitgestellt.

### **Daten-Ausgänge**
Analog dazu gibt es keine direkten Datenausgänge. Das Resultat (boolescher Wert Q) wird über den Adapterausgang **Q** (Port `D1`) ausgegeben.

### **Adapter**

| Bezeichnung | Typ    | Richtung  | Kommentar                            |
|-------------|--------|-----------|--------------------------------------|
| IN          | AX     | Eingang   | Boolescher Eingang (Adapter)         |
| PT          | ATM    | Eingang   | Zeitgrenze (Adapter)                 |
| Q           | AX     | Ausgang   | Boolescher Ausgang (Adapter)         |

## Funktionsweise
Der Baustein arbeitet intern mit dem Standard-Funktionsblock **E_TLIM** und verleiht diesem eine Adapter-Hülle. Die Logik ist wie folgt:

1. **Aktivierung**: Ein Ereignis am Adaptereingang **IN** (Port `E1`) löst die Verarbeitung aus. Gleichzeitig wird der boolesche Wert von **IN.D1** übernommen.
2. **Zeitmessung**: Wird das Eingangssignal `IN` **TRUE**, setzt der Baustein den Ausgang `Q` auf **TRUE** und startet einen Timer mit der Dauer **PT** (von Adapter **PT**, Port `D1`).
3. **Timeout**: Bleibt `IN` länger als `PT` aktiv, so wird `Q` auf **FALSE** zurückgesetzt (Timeout).
4. **Vorzeitiges Ende**: Wird `IN` vor Ablauf der Zeit **FALSE**, so setzt der Baustein `Q` sofort zurück (ebenfalls **FALSE**).
5. **Setzen der Zeitgrenze**: Der Ereigniseingang **EIPT** erlaubt es, den Wert von **PT** vorzugeben, ohne eine neue Auslösung zu starten. Dies dient zur Konfiguration des Zeitlimits vor dem eigentlichen Einsatz.

Der Ausgangsadapter **Q** gibt auf seinem `E1`-Port ein Ereignis aus, sobald sich `Q` ändert (steigende oder fallende Flanke).

## Technische Besonderheiten
- **Adapterbasierte Kommunikation**: Statt einzelner Ereignis- und Datenports werden AX-/ATM-Adapter verwendet. Diese ermöglichen eine modulare und wiederverwendbare Kopplung mit anderen Bausteinen.
- **Interner Standardbaustein**: Die Implementierung nutzt den etablierten **E_TLIM** (IEC 61499), womit eine zuverlässige und getestete Zeitlogik gewährleistet ist.
- **Nicht-auslösendes Setzen der Zeit**: Der Eingang **EIPT** ändert nur das Zeitlimit, ohne den Timer zu starten oder zurückzusetzen. Dies ist nützlich, um Parameter dynamisch anzupassen.
- **Typische Zeitmessung**: Geeignet für Überwachungen, bei denen ein Signal nicht länger als eine bestimmte Dauer aktiv sein darf.

## Zustandsübersicht
Der FB durchläuft implizit folgende Zustände:

| Zustand    | Beschreibung                                                  |
|------------|--------------------------------------------------------------|
| **Idle**   | IN = FALSE, Q = FALSE, Timer läuft nicht.                    |
| **Timing** | IN = TRUE, Q = TRUE, Timer läuft.                            |
| **Timeout**| IN = TRUE, Timer abgelaufen, Q = FALSE (bleibt bis IN = FALSE). |

Ein Wechsel zurück nach **Idle** erfolgt, sobald IN auf FALSE geht. Der Zustand **Timeout** wird nur erreicht, wenn die Zeitüberschreitung eingetreten ist.

## Anwendungsszenarien
- **Überwachung von Signalen** in der Automatisierungstechnik (z. B. maximale Einschaltdauer eines Aktors).
- **Sicherheitsfunktionen**, bei denen ein Ausgang deaktiviert werden muss, wenn ein Signal zu lange ansteht.
- **Zeitgesteuerte Resets** in Kommunikationsprotokollen (Watchdog-Funktionalität).
- **Einfache zeitliche Begrenzung** in komplexen Steuerungssystemen, die auf Adapter-Schnittstellen basieren.

## Vergleich mit ähnlichen Bausteinen
- **E_TLIM (Standard)**: Bietet die gleiche Kernlogik, jedoch mit klassischen Ein-/Ausgangsports. **ATM_AX_TLIM** kapselt diese Logik in eine Adapter-Schnittstelle und ist somit besser für modulare und wiederverwendbare Komponenten geeignet.
- **E_TON / E_TOF**: Diese Bausteine realisieren Einschalt- bzw. Ausschaltverzögerungen. Im Gegensatz dazu überwacht **ATM_AX_TLIM** die maximale Dauer eines aktiven Signals und reagiert mit einem Timeout.
- **E_CYCLE**: Ein zyklischer Timer, der periodisch Signale erzeugt, hat eine andere Zielsetzung als die reine Überwachung.

## Fazit
Der Funktionsblock **ATM_AX_TLIM** bietet eine kompakte und adapterbasierte Lösung für Zeitüberwachungsaufgaben. Er kombiniert die bewährte Funktionalität des Standard-Timers **E_TLIM** mit der Flexibilität von Adapter-Schnittstellen und erlaubt eine dynamische Vorgabe der Zeitgrenze über **EIPT**. Dadurch eignet er sich besonders für moderne, modulare Automatisierungsprojekte, die auf IEC 61499 basieren und eine klare Trennung von Schnittstellen und Logik erfordern.