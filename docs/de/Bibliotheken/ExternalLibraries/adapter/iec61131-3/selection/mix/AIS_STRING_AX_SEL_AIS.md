# AIS_STRING_AX_SEL_AIS


![AIS_STRING_AX_SEL_AIS](./AIS_STRING_AX_SEL_AIS.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AIS_STRING_AX_SEL_AIS` dient zur binären Auswahl (Selektion) zwischen zwei Signalquellen unterschiedlicher Struktur: einem Adapter-Eingang vom Typ `AIS` und einem klassischen String-Eingang (`IN1`). Die Steuerung, welches Signal an den Ausgangs-Adapter weitergegeben wird, erfolgt über einen Selektor-Adapter vom Typ `AX`. Intern nutzt der Baustein die standardisierte Selektionslogik nach IEC 61131-3, verpackt in eine vollständig ereignisgesteuerte IEC 61499-Netzwerkstruktur.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*   **EI1**: Triggert die Übernahme des Daten-Eingangs `IN1` (zugeordnete Datenvariable: `IN1`).

### **Ereignis-Ausgänge**

*   *Keine direkten Ereignis-Ausgänge vorhanden.* (Die Ereignissteuerung erfolgt implizit über den Ausgangs-Adapter `OUT`).

### **Daten-Eingänge**

*   **IN1** (STRING): Auswählbare Eingangsvariable (Zeichenkette).

### **Daten-Ausgänge**

*   *Keine direkten Daten-Ausgänge vorhanden.* (Die Datenweitergabe erfolgt über den Ausgangs-Adapter `OUT`).

### **Adapter**

*   **OUT** (Plug / Stecker, Typ: `adapter::types::unidirectional::AIS`): Der ausgewählte und aktualisierte Ausgang. Sendet das selektierte Signal an die nachfolgende Logik.
*   **IN0** (Socket / Buchse, Typ: `adapter::types::unidirectional::AIS`): Erster auswählbarer Eingang via Adapter-Verbindung.
*   **G** (Socket / Buchse, Typ: `adapter::types::unidirectional::AX`): Der Selektor-Adapter. Bestimmt über sein Datensignal, welcher Eingang durchgeschaltet wird.

## Funktionsweise

Der Baustein arbeitet als ereignisgesteuerter Multiplexer für String- bzw. Adapter-Signale:

1.  **Auswahl-Logik:** 
    *   Ist das Auswahlsignal am Adapter `G` (Datenfeld `D1`) **FALSE**, wird der Wert vom Eingang `IN0` (Datenfeld `D1`) an den Ausgang `OUT` (Datenfeld `D1`) durchgereicht.
    *   Ist das Auswahlsignal **TRUE**, wird der String-Wert des Eingangs `IN1` an den Ausgang `OUT` weitergeleitet.
2.  **Ereignis-Verarbeitung:** 
    *   Jede Änderung an den Eingängen (`IN0`, `IN1` via `EI1`) oder dem Selektor `G` triggert über interne Event-D-Flipflops (`E_D_FF` bzw. `E_D_FF_ANY`) und Zuweisungsbausteine (`F_MOVE`) eine Neuberechnung.
    *   Nach erfolgreicher Selektion wird das Ausgangsereignis `OUT.E1` generiert, um nachfolgende Bausteine über das Vorliegen neuer Daten zu informieren.

## Technische Besonderheiten

*   **Hybride Schnittstelle:** Ermöglicht die nahtlose Kopplung von strukturierten Adapter-Schnittstellen (`AIS`, `AX`) mit einfachen IEC 61131-Datentypen (`STRING`).
*   **Datentypsicherheit:** Durch die interne Verwendung von datentypunabhängigen Event-Flipflops und dedizierten `F_MOVE`-Kopierern (konfiguriert auf den Datentyp `STRING`) ist eine konsistente Datenkonsistenz bei jedem Schaltvorgang gewährleistet.
*   **Unidirektionale Adapter:** Die Verwendung unidirektionaler Adaptertypen sorgt für einen klaren, rückwirkungsfreien Signalfluss.

## Zustandsübersicht

Da es sich um einen zusammengesetzten Funktionsbaustein (Composite FB) handelt, wird das Verhalten durch das interne Zusammenspiel der Komponenten gesteuert. Die logische Zustandstabelle verhält sich wie folgt:

| Selektor (`G.D1`) | Zustand / Änderung an Eingängen | Ausgang (`OUT.D1`) | Ereignis am Ausgang (`OUT.E1`) |
| :--- | :--- | :--- | :--- |
| **FALSE** | `IN0.D1` ändert sich / Ereignis `IN0.E1` | Wert von `IN0.D1` | Wird ausgelöst |
| **TRUE** | `IN1` ändert sich / Ereignis `EI1` | Wert von `IN1` | Wird ausgelöst |
| **Wechsel (beliebig)** | Ereignis an `G.E1` | Aktueller Wert gemäß Selektor | Wird ausgelöst |

## Anwendungsszenarien

*   **Status- und Textanzeigen:** Umschalten einer Visualisierungsanzeige zwischen einem Standard-Systemstatus (geliefert über den Adapter `IN0`) und einer dynamischen Benutzermeldung (übergeben als String an `IN1`).
*   **Fehler-Routing:** Bedingtes Aufschalten von vordefinierten Fehlermeldungen auf einen zentralen Diagnose-Bus.
*   **Rezepturverwaltung:** Auswahl zwischen einem Standard-Prozessparameter-String und einem manuell eingegebenen Korrekturwert in automatisierten Produktionsanlagen.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zum Standard-Auswahlbaustein `F_SEL` bietet dieser Baustein eine direkte Integration von IEC 61499-Adaptern. Entwickler müssen die Adapter-Signale nicht erst mühsam in Einzeldaten zerlegen, um sie zu selektieren. Die gesamte Ereignissynchronisation wird out-of-the-box innerhalb des Bausteins gelöst.

## Fazit

`AIS_STRING_AX_SEL_AIS` stellt eine komfortable und robuste Lösung dar, um in ereignisgesteuerten Systemen eine Brücke zwischen der strukturierten Adapterwelt und einfachen String-Variablen zu schlagen. Er minimiert den Verdrahtungsaufwand im übergeordneten Funktionsplan erheblich und garantiert ein deterministisches Verhalten bei Signalwechseln.