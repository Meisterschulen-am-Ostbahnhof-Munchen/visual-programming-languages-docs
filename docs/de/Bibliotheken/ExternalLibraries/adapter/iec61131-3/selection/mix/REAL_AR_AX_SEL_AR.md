# REAL_AR_AX_SEL_AR


![REAL_AR_AX_SEL_AR](./REAL_AR_AX_SEL_AR.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `REAL_AR_AX_SEL_AR` dient der binären Auswahl (Selektion) zwischen zwei reellwertigen Eingangssignalen (Typ `REAL`). Er vereint dabei die klassische signalbasierte Programmierung mit moderner, adapterbasierter Kommunikation nach IEC 61499. 

Ein Eingang wird als direkter Datenwert bereitgestellt, während der zweite Auswahleingang, das Steuersignal (Selektor) sowie der Ausgang über standardisierte, unidirektionale Adapter gekoppelt sind. Dies ermöglicht eine saubere Strukturierung und Reduzierung von Verbindungslinien innerhalb der 4diac-IDE.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*   **EI0**: Übernimmt und setzt den an `IN0` anliegenden Wert.

### **Ereignis-Ausgänge**

*   *(Keine direkten Ereignis-Ausgänge vorhanden. Die Ereignisweiterleitung erfolgt gekapselt über den Ausgangs-Plug `OUT`)*

### **Daten-Eingänge**

*   **IN0** (REAL): Der erste auswählbare Eingangswert (wird selektiert, wenn das Auswahlsignal `FALSE` ist).

### **Daten-Ausgänge**

*   *(Keine direkten Daten-Ausgänge vorhanden. Die Datenweiterleitung erfolgt gekapselt über den Ausgangs-Plug `OUT`)*

### **Adapter**

*   **OUT** (Plug, Typ: `adapter::types::unidirectional::AR`): Der ausgewählte Ausgangswert (Selected Output).
*   **IN1** (Socket, Typ: `adapter::types::unidirectional::AR`): Der zweite auswählbare Eingangswert.
*   **G** (Socket, Typ: `adapter::types::unidirectional::AX`): Der Selektor (Auswahlschalter). Steuert, welcher Eingang auf den Ausgang durchgeschaltet wird.

## Funktionsweise

Das interne Verhalten des Funktionsbausteins wird durch ein Netzwerk aus Standard-Auswahlbausteinen (`F_SEL`), Signal-Kopierern (`F_MOVE`) und Event-D-Flip-Flops (`E_D_FF` / `E_D_FF_ANY`) realisiert:

1.  **Wertpufferung**: Die Eingangswerte von `IN0` (über `EI0`), `IN1` (über das Adapter-Ereignis `IN1.E1`) sowie das Auswahlsignal `G` (über das Adapter-Ereignis `G.E1`) werden bei Eintreffen des jeweiligen Ereignisses in internen Flip-Flops zwischengespeichert.
2.  **Selektionslogik**: Der interne Baustein `F_SEL` wertet das Signal des Selektors `G.D1` aus:
    *   Ist das Signal am Selektor-Adapter **FALSE**, wird der Wert von `IN0` gewählt.
    *   Ist das Signal am Selektor-Adapter **TRUE**, wird der Wert des Adapters `IN1` (über `IN1.D1`) gewählt.
3.  **Ausgabe**: Der ausgewählte Wert wird über einen Konversionsschritt (`F_MOVE_OUT`) an den Ausgangs-Plug `OUT.D1` übergeben und zeitgleich das Ausgangsereignis `OUT.E1` getriggert.

## Technische Besonderheiten

*   **Mischbetrieb**: Ermöglicht die direkte Brückenbildung zwischen klassischen Datenleitungen (wie `IN0`) und strukturierten Adapter-Schnittstellen.
*   **Sichere Event-Verarbeitung**: Durch den Einsatz von Event-D-Flip-Flops wird sichergestellt, dass Datenwerte nur bei gültigen Flankenereignissen übernommen werden, was inkonsistente Zustände und Signalstörungen (Glitches) verhindert.
*   **Unidirektionale Adapter**: Die Verwendung der Typen `AR` (Analog Real) und `AX` (Analog Boolean/Selection) optimiert den Datenfluss für reine Sender-Empfänger-Strukturen ohne Rückkanal.

## Zustandsübersicht

Der Baustein besitzt als Netzwerk-Funktionsbaustein (Composite FB) keinen eigenen expliziten Zustandsautomaten (ECC). Sein Verhalten ist rein daten- und ereignisgesteuert:

| Triggerndes Ereignis | Zustand Selektor `G` | Resultierende Aktion |
| :--- | :--- | :--- |
| `EI0` | `FALSE` | Wert von `IN0` wird an `OUT.D1` ausgegeben; `OUT.E1` wird getriggert. |
| `EI0` | `TRUE` | Wert wird intern aktualisiert, hat aber keinen Einfluss auf den Ausgang. |
| `IN1.E1` | `TRUE` | Wert von `IN1.D1` wird an `OUT.D1` ausgegeben; `OUT.E1` wird getriggert. |
| `IN1.E1` | `FALSE` | Wert wird intern aktualisiert, hat aber keinen Einfluss auf den Ausgang. |
| `G.E1` | Signalwechsel | Der Ausgang wird basierend auf dem neuen Zustand von `G.D1` sofort neu evaluiert und ausgegeben. |

## Anwendungsszenarien

*   **Sollwert-Umschaltung**: Wechsel zwischen einem manuell vorgegebenen Festwert (über `IN0` an einem HMI) und einem automatischen Profilwert (über den Adapter-Eingang `IN1`).
*   **Signal-Bypass**: Aktivierung eines Notlauf- oder Standardwerts im Falle von Sensorstörungen im Hauptzweig (`IN1`).
*   **Modularer Anlagenbau**: Koppelung von Teilsystemen, bei denen Signale platzsparend über Adapter transportiert und bedarfsweise umgeschaltet werden müssen.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einem Standard-IEC-61131-3-Baustein `F_SEL` bietet `REAL_AR_AX_SEL_AR` den Vorteil, dass die Signalpfade nicht einzeln als lose Datenleitungen verdrahtet werden müssen. Die Zusammenfassung von Daten und Ereignissen in den Adaptern `IN1`, `G` und `OUT` sorgt für eine wesentlich übersichtlichere und wartungsfreundlichere Applikationslandschaft in der 4diac-IDE.

## Fazit

Der `REAL_AR_AX_SEL_AR` ist ein hochgradig praxistauglicher Hilfsbaustein für die moderne und strukturierte Programmierung mit 4diac. Er eignet sich hervorragend zur Reduzierung der Komplexität von Signal- und Event-Verkabelungen bei Auswahl- und Umschaltvorgängen von Fließkommawerten.