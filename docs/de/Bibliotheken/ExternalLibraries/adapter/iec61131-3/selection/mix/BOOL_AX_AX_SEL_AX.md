# BOOL_AX_AX_SEL_AX


![BOOL_AX_AX_SEL_AX](./BOOL_AX_AX_SEL_AX.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `BOOL_AX_AX_SEL_AX` ist ein zusammengesetzter Funktionsbaustein (Composite Function Block) für die IEC 61499. Er dient der binären Auswahl (Selektion) zwischen zwei booleschen Signalquellen und leitet das ausgewählte Signal an einen Ausgang weiter. 

Das Besondere an diesem Baustein ist die Kombination aus klassischen Event-basierten Datenkanälen und modernen, adapterbasierten Schnittstellen. Er eignet sich ideal, um ein einfaches boolesches Signal und ein adapterbasiertes Signal dynamisch anhand eines Selektors zu filtern und weiterzuleiten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*   **EI0**: Setzt den Wert des direkten Dateneingangs `IN0` und triggert dessen Verarbeitung im internen Netzwerk.

### **Ereignis-Ausgänge**

*   *Keine direkten Ereignis-Ausgänge vorhanden. Ereignisse werden über den Ausgangs-Adapter `OUT` ausgegeben.*

### **Daten-Eingänge**

*   **IN0** (BOOL): Direkt anliegende boolesche Eingangsvariable, die zur Auswahl steht.

### **Daten-Ausgänge**

*   *Keine direkten Daten-Ausgänge vorhanden. Die Datenübertragung erfolgt über den Ausgangs-Adapter `OUT`.*

### **Adapter**

*   **IN1** (Socket, Typ: `adapter::types::unidirectional::AX`): Adapterbasierter, auswählbarer Datenkanal.
*   **G** (Socket, Typ: `adapter::types::unidirectional::AX`): Der Selektor-Kanal. Das hier anliegende Signal bestimmt, welcher Eingang durchgeschaltet wird.
*   **OUT** (Plug, Typ: `adapter::types::unidirectional::AX`): Der ausgewählte Ausgangskanal, der das Signal des gewählten Eingangs führt.

## Funktionsweise

Der Baustein basiert intern auf der Standard-Auswahllogik der IEC 61131-3 (`F_SEL`). Er schaltet die Signale wie folgt durch:

1.  **Selektion (`G` = FALSE):** Liefert der Selektor-Adapter `G` den logischen Zustand `FALSE`, wird der direkt anliegende Dateneingang `IN0` auf den Ausgangs-Adapter `OUT` geschaltet.
2.  **Selektion (`G` = TRUE):** Liefert der Selektor-Adapter `G` den logischen Zustand `TRUE`, wird der adapterbasierte Eingang `IN1` auf den Ausgangs-Adapter `OUT` geschaltet.

Die internen Speicher- und Konvertierungsglieder (`E_D_FF`, `E_D_FF_ANY` und `F_MOVE`) sorgen dafür, dass die Datenwerte bei jedem relevanten Ereignis (`EI0`, `G.E1` oder `IN1.E1`) zwischengespeichert und konsistent an den Ausgang übertragen werden. Jede Änderung triggert eine Aktualisierung des Ausgangs-Adapters `OUT` inklusive des dazugehörigen Ereignisses.

## Technische Besonderheiten

*   **Hybrid-Schnittstelle:** Der Baustein fungiert als Brücke zwischen der klassischen IEC 61499-Ereignissteuerung (für `IN0`) und der adapterbasierten Signalübertragung (für `IN1`, `G`, `OUT`).
*   **Ereignis-Konsistenz:** Durch die Verwendung von D-Flip-Flops (`E_D_FF` / `E_D_FF_ANY`) im internen Netzwerk wird sichergestellt, dass Daten nur dann weitergegeben werden, wenn ein gültiges Trigger-Ereignis die Gültigkeit der Daten signalisiert.

## Zustandsübersicht

Die Auswahl des Ausgangssignals verhält sich nach folgender Logik:

| Zustand Selektor (G.D1) | Aktiver Eingang | Ausgangswert (OUT.D1) | Auslösendes Ereignis für Ausgang (OUT.E1) |
| :--- | :--- | :--- | :--- |
| **FALSE** | `IN0` | Wert von `IN0` | `EI0` (sofern ausgewählt) oder Flanke auf `G.E1` |
| **TRUE** | `IN1.D1` | Wert von `IN1.D1` | `IN1.E1` (sofern ausgewählt) oder Flanke auf `G.E1` |

## Anwendungsszenarien

*   **Hand-/Automatik-Umschaltung:** Ein Steuersignal soll im Automatikbetrieb aus einem komplexen Software-Subsystem via Adapter (`IN1`) bezogen werden. Im Handbetrieb oder bei Wartungsarbeiten soll ein physischer, direkt verdrahteter Taster (`IN0`) die Kontrolle übernehmen. Die Umschaltung erfolgt über den Selektor `G`.
*   **Signal-Override / Bypass-Steuerung:** Temporäres Aufschalten eines Notfall- oder Test-Signals auf eine standardisierte Adapter-Leitung.

## Vergleich mit ähnlichen Bausteinen

*   **Standard `F_SEL`:** Der klassische Selektions-Baustein der IEC 61131-3 verarbeitet ausschließlich elementare Datentypen und besitzt keine Ereignissteuerung oder Adapter-Kompatibilität. `BOOL_AX_AX_SEL_AX` erweitert diese Funktionalität für verteilte, ereignisgesteuerte Systeme.
*   **Rein adapterbasierte Selektoren:** Im Gegensatz zu reinen Adapter-Kopplern erlaubt dieser Baustein die direkte Einspeisung eines standardmäßigen Bool-Datenpunkts (`IN0`), ohne dass dafür zuvor ein extra Adapter-Konstrukteur aufgerufen werden muss.

## Fazit

Der `BOOL_AX_AX_SEL_AX` ist ein nützlicher Hilfsbaustein für modulare Steuerungskonzepte in 4diac. Er vereinfacht das Signalrouting in gemischten Systemarchitekturen, bei denen sowohl klassische EA-Signale als auch strukturierte Adapterverbindungen koexistieren.