# ATM_AX_TON


![ATM_AX_TON](./ATM_AX_TON.svg)

* * * * * * * * * *
## Einleitung

Der **ATM_AX_TON** ist ein Funktionsblock zur Verzögerung beim Einschalten (On-Delay). Er realisiert eine Standard-Timer-Funktionalität nach IEC 61499-2, die über eine Adapter-Schnittstelle (AX/AT) angesteuert wird. Der Baustein ermöglicht es, einen Timer über einen Eingangsadapter zu starten und den Ausgangszustand sowie die Ablaufbestätigung über einen Ausgangsadapter bereitzustellen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| EIPT | Event | Setzt die Vorlaufzeit (nicht auslösend) |

### **Ereignis-Ausgänge**

Der FB besitzt keine eigenen Ereignis-Ausgänge. Bestätigungen und Zustandsänderungen werden über den Adapter **Q** (E1) kommuniziert.

### **Daten-Eingänge**

Der FB hat keine expliziten Daten-Eingänge. Alle Eingabedaten werden über die Adapter-Schnittstellen bereitgestellt.

### **Daten-Ausgänge**

Der FB hat keine expliziten Daten-Ausgänge. Ausgabedaten werden über den Adapter **Q** (D1) bereitgestellt.

### **Adapter**

| Richtung | Name | Typ | Kommentar |
|----------|------|-----|-----------|
| Socket | IN | adapter::types::unidirectional::AX | Timer-Eingang (AX-Adapter) – liefert das boolsche Eingangssignal und den Startimpuls |
| Socket | PT | adapter::types::unidirectional::ATM | Vorlaufzeit (AT-Adapter) – stellt die Verzögerungszeit bereit |
| Plug | Q | adapter::types::unidirectional::AX | Timer-Ausgang (AX-Adapter) – gibt den Timer-Zustand und die Bestätigung aus |

## Funktionsweise

Der **ATM_AX_TON** kapselt einen standardmäßigen On-Delay-Timer (E_TON) aus der IEC 61499-Bibliothek. Die Funktionsweise im Detail:

1. **Start der Zeitmessung:**  
   Der Eingangsadapter **IN** liefert über sein Ereignis **E1** den Startimpuls (REQ) und über sein Datensignal **D1** den boolschen Wert **IN**. Wenn **IN.D1** auf WAHR wechselt, wird der Timer gestartet.

2. **Verzögerungszeit:**  
   Die gewünschte Verzögerungszeit wird über den Adapter **PT** bereitgestellt (über **PT.D1**). Sobald der Timer läuft, wird nach Ablauf dieser Zeit der Ausgang **Q.D1** auf WAHR gesetzt.

3. **Ausgangssignal und Bestätigung:**  
   Der Ausgangsadapter **Q** gibt über **Q.D1** den aktuellen Timer-Zustand aus (WAHR, wenn die Verzögerungszeit abgelaufen ist, FALSE, wenn der Eingang auf FALSE geht). Das Ereignis **Q.E1** wird nach jeder Zustandsänderung gesendet (CNF des internen E_TON).

4. **Setzen der Vorlaufzeit ohne Auslösung:**  
   Der Ereignis-Eingang **EIPT** dient laut Spezifikation dazu, die Vorlaufzeit **PT** zu setzen, ohne den Timer zu starten. Im vorliegenden FBNetzwerk wird dieser Eingang jedoch nicht intern verbunden – er steht für externe Nutzung zur Verfügung, falls eine Anwendung eine Vorabsetzung der Zeit benötigt.

5. **Rückfall:**  
   Wenn **IN** auf FALSE geht, wird der Timer sofort zurückgesetzt und **Q.D1** wird FALSE (unverzögert).

## Technische Besonderheiten

- **Adapterbasierte Schnittstelle:** Der FB nutzt ausschließlich Adapter (AX und ATM) für die Kommunikation, keine traditionellen Ein-/Ausgangsgrooves. Dies ermöglicht eine flexible Kapselung und Wiederverwendung in komplexen Systemen.
- **Unidirektionale Adapter:** Die verwendeten Adapter sind unidirektional (AX für boolsche Werte und ATM für Zeitwerte). Der FB erwartet, dass die Adapter korrekt in die übergeordnete Hierarchie eingebunden werden.
- **Nicht verbundener Event-Eingang EIPT:** Der **EIPT**-Eingang ist definiert, aber nicht mit dem internen E_TON verbunden. Dies könnte auf eine geplante Erweiterung oder eine externe Verwendung durch den Anwender hindeuten. In der aktuellen Version hat er keine direkte Funktion im FBNetzwerk.
- **Autoren und Version:** Der Baustein wurde ursprünglich von Franz Höpfinger (HR Agrartechnik GmbH) entwickelt und später von Patrick Aigner überarbeitet (Version 3.0, April 2025). Er ist unter der Eclipse Public License 2.0 verfügbar.

## Zustandsübersicht

Der FB selbst verwaltet keinen eigenen Zustandsautomaten – die Zustandslogik liegt im integrierten **E_TON**. Dennoch lässt sich das Verhalten wie folgt beschreiben:

| Zustand des Eingangs IN | Verhalten | Ausgang Q.D1 |
|-------------------------|-----------|--------------|
| FALSE → TRUE (steigende Flanke) | Timer startet; nach Ablauf von PT wird Q TRUE | FALSE (bis PT abgelaufen) → TRUE |
| TRUE (während Timer läuft) | Timer läuft weiter | FALSE |
| TRUE → FALSE (fallende Flanke) | Timer wird sofort zurückgesetzt | TRUE → FALSE |
| TRUE (nach Timerablauf) | Ausgang bleibt TRUE, solange IN TRUE | TRUE |
| FALSE (beliebig) | Ausgang bleibt FALSE | FALSE |

## Anwendungsszenarien

- **Maschinensteuerung:** Verzögerung beim Einschalten von Antrieben oder Ventilen, um ein gleichzeitiges Anlaufen mehrerer Komponenten zu verhindern.
- **Signalaufbereitung:** Entprellen von Schaltsignalen, indem ein kurzer Impuls erst nach einer definierten Zeit als gültig betrachtet wird.
- **Prozessautomatisierung:** Einleitung von Folgeschritten erst nach Ablauf einer Wartezeit (z. B. in Förderbändern oder Dosieranlagen).
- **Adapter-Integration:** Einsatz in Systemen, die bereits auf dem AX/AT-Adapterprotokoll basieren, ohne zusätzliche Datenleitungen.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Typ | Besonderheit |
|----------|-----|--------------|
| **E_TON** (IEC 61499) | Standard On-Delay | Klassische Ein-/Ausgangsschnittstelle; direkte Ereignis- und Datenports |
| **ATM_AX_TON** | Adapter-basiert | Kapselt E_TON und bietet AX/AT-Adapter; zusätzlicher EIPT-Eingang (nicht verbunden) |
| **E_TOF** | Off-Delay | Verzögerung beim Ausschalten (entgegengesetztes Verhalten) |
| **E_CTU** | Aufwärtszähler | Zählt Ereignisse, kein Timer |

Der **ATM_AX_TON** unterscheidet sich durch seine reine Adapterschnittstelle und die fehlende direkte Datenkopplung. Er eignet sich besonders für modulare, hierarchisch aufgebaute Steuerungen.

## Fazit

Der **ATM_AX_TON** ist ein fertig konfektionierter On-Delay-Timer mit einer modernen, adapterbasierten Anbindung. Er vereinfacht die Einbindung von Zeitverzögerungen in größere Systeme, die bereits das AX/AT-Konzept verwenden. Der nicht angeschlossene **EIPT**-Eingang bietet Potenzial für zukünftige Erweiterungen oder kundenspezifische Anpassungen. Insgesamt ist der Baustein robust, gut dokumentiert und unter freier Lizenz verfügbar.