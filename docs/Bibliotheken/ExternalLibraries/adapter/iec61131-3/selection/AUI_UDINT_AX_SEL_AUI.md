# AUI_UDINT_AX_SEL_AUI


![AUI_UDINT_AX_SEL_AUI](./AUI_UDINT_AX_SEL_AUI.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `AUI_UDINT_AX_SEL_AUI` realisiert eine binäre Auswahl (Binary Selection) zwischen zwei Eingangswerten, gesteuert durch einen Adapter vom Typ *AX*. Der ausgewählte Wert wird über einen *AUI*-Adapter ausgegeben. Der Baustein ist nach IEC 61131-3 als Standard-Selektionsfunktion klassifiziert und eignet sich für die Verwendung in Automatisierungsanwendungen, die eine flexible, ereignisgesteuerte Signalumschaltung erfordern.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| `EI0` | Event | Setzt/übernimmt den Wert von `IN0` (mit `IN0` verknüpft) |
| `EI1` | Event | Setzt/übernimmt den Wert von `IN1` (mit `IN1` verknüpft) |

### **Ereignis-Ausgänge**

Der FB besitzt keinen eigenständigen Ereignis-Ausgang. Das Ausgangsereignis wird über den *AUI*-Adapter `OUT` bereitgestellt (siehe Adapter).

### **Daten-Eingänge**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| `IN0` | UINT | Erster auswählbarer Eingangswert |
| `IN1` | ANY_ELEMENTARY | Zweiter auswählbarer Eingangswert (polymorph, beliebiger elementarer Datentyp) |

### **Daten-Ausgänge**

Keine direkten Datenausgänge. Der ausgewählte Wert wird über den *AUI*-Adapter `OUT` ausgegeben.

### **Adapter**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| `G` (Socket) | AX | Steueradapter (Selektor); liefert das Auswahlsignal `D1` und das Triggerereignis `E1` |
| `OUT` (Plug) | AUI | Ergebnisadapter; gibt den selektierten Wert über `D1` und ein Abschlussereignis über `E1` aus |

## Funktionsweise

Der Funktionsblock kapselt einen IEC 61131-3 Standardbaustein `F_SEL` (binary selection). Die Selektion erfolgt ereignisgesteuert:

1. Die Ereigniseingänge `EI0` und `EI1` dienen der Aktualisierung bzw. Übernahme der beiden Eingangswerte. Sie sind mit den Daten `IN0` bzw. `IN1` verknüpft.
2. Der Steueradapter `G` empfängt von außen ein Ereignis (`G.E1`) und einen booleschen/digitalen Wert (`G.D1`). Das Ereignis triggert den internen `F_SEL` (über dessen `REQ`-Eingang).
3. Der interne `F_SEL` wählt anhand des Steuersignals (`F_SEL.G`) den Wert von `IN0` (wenn `G = FALSE`) oder `IN1` (wenn `G = TRUE`) aus und legt ihn am Ausgang `F_SEL.OUT` an.
4. Das Bestätigungsereignis `F_SEL.CNF` wird an den Ausgangsadapter `OUT.E1` weitergeleitet, und der selektierte Wert wird über `OUT.D1` ausgegeben.

Somit fungiert der Baustein als einheitliche, adapterbasierte Schnittstelle für binäre Auswahloperationen.

## Technische Besonderheiten

- **Adapter statt Einzelsignale:** Anstelle einzelner Ereignis- und Datenausgänge verwendet der FB Adapter (`AUI` und `AX`). Dies ermöglicht eine modulare Kapselung und vereinfacht die Einbindung in adapterbasierte Architekturen.
- **Polymorphismus:** Der zweite Eingang (`IN1`) ist als `ANY_ELEMENTARY` deklariert, sodass er Werte verschiedener elementarer Datentypen (z.B. INT, BOOL, REAL) akzeptiert. Der Ausgang nimmt diesen Typ an, sofern er mit dem ersten Eingang kompatibel ist.
- **Ereignisgesteuerte Verarbeitung:** Die Selektion wird nur bei Eintreffen eines Ereignisses auf `G.E1` ausgeführt, was die Nebenläufigkeit und den kontrollierten Datenfluss unterstützt.
- **Copyright-Hinweis:** Der Baustein unterliegt der Eclipse Public License 2.0 (EPL-2.0). Entwickelt von TU Wien ACIN und HR Agrartechnik GmbH.

## Zustandsübersicht

Der FB besitzt keine eigene Zustandsmaschine, sondern delegiert die Auswahl an den internen `F_SEL`-Baustein. Das Verhalten ist rein ereignisgesteuert:

- Bei einer positiven Flanke von `G.E1` wird eine Selektion ausgelöst.
- Die Ereignisse `EI0` und `EI1` haben keine direkte Auswirkung auf die Auswahl; sie dienen lediglich der Übernahme der Eingangswerte (z.B. aus einem asynchronen Prozess).

Eine detaillierte Zustandsbeschreibung des internen `F_SEL` kann der IEC 61131-3 Spezifikation oder der Dokumentation des Standardbausteins entnommen werden.

## Anwendungsszenarien

- **Signalumschaltung:** Auswahl zwischen zwei Messwerten oder Steuersignalen in einer Automatisierungsstrecke, gesteuert durch ein Freigabe- oder Modussignal (z.B. Hand/Auto).
- **Adapterbasierte Architekturen:** Einsatz in Systemen, die auf dem Adapter-Pattern der 4diac-IDE aufbauen (z.B. zur Verbindung von Komponenten mit standardisierten Schnittstellen).
- **Polymorphe Datenpfade:** Verarbeitung unterschiedlicher Datentypen (z.B. wahlweise UINT oder BOOL) innerhalb desselben Funktionsblocks, ohne dass eine separate Konvertierung nötig ist.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zum einfachen IEC 61131-3 Baustein `SEL` (der mit binärem Eingang und zwei Datenwerten arbeitet) erweitert `AUI_UDINT_AX_SEL_AUI` die Funktionalität um Adapter-Schnittstellen und die ereignisgesteuerte Ansteuerung. Standard-SEL-FBs arbeiten meist ohne explizite Ereignisse und geben das Ergebnis sofort aus. Dieser FB bietet eine strengere Kopplung zwischen Daten- und Ereignisfluss, was in ereignisorientierten Systemen (z.B. verteilten Automatisierungssystemen) vorteilhaft ist.

## Fazit

Der Funktionsblock `AUI_UDINT_AX_SEL_AUI` stellt eine flexible, adapterbasierte Binärselektion bereit. Er kombiniert die bewährte IEC 61131-3 Logik mit modernen Schnittstellenkonzepten (Adapter, ANY_ELEMENTARY). Durch die klare Trennung von Ereignis- und Datenpfaden eignet er sich besonders für modulare, ereignisgesteuerte Automatisierungslösungen, die auf der 4diac-IDE-Plattform realisiert werden.