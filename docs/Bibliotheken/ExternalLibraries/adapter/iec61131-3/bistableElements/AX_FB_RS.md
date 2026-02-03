# AX_FB_RS


![AX_FB_RS](.././AX_FB_RS.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein **AX_FB_RS** realisiert ein bistabiles Kippglied mit vorrangigem Rücksetzen (Reset-Dominanz), basierend auf der IEC 61131-3 Norm. Im Gegensatz zum Standard-`RS`-Baustein nutzt dieser FB Adapter-Schnittstellen (`AX`), um Ereignisse und Daten gebündelt zu übertragen. Dies ermöglicht eine kompaktere Darstellung in Steuerungsdiagrammen, da Daten- und Ereignisverbindungen in einer einzigen Linie zusammengefasst werden.

## Schnittstellenstruktur

Da dieser Baustein ausschließlich auf Adaptern basiert, sind die klassischen Ereignis- und Daten-Ein-/Ausgänge leer. Die Kommunikation erfolgt vollständig über die definierten Plugs und Sockets.

### **Ereignis-Eingänge**
*Keine direkten Ereignis-Eingänge vorhanden.*

### **Ereignis-Ausgänge**
*Keine direkten Ereignis-Ausgänge vorhanden.*

### **Daten-Eingänge**
*Keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**
*Keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

Der Baustein verwendet den Adapter-Typ `adapter::types::unidirectional::AX`. Dieser Adaptertyp bündelt typischerweise ein boolesches Signal (`D1`) und ein zugehöriges Ereignis (`E1`).

| Name | Typ | Richtung | Beschreibung |
| :--- | :--- | :--- | :--- |
| **Q1** | AX | Plug (Ausgang) | Der Ausgang des Flip-Flops (Status). |
| **SET** | AX | Socket (Eingang) | Der Setz-Eingang. Wenn aktiv, wird der Ausgang `Q1` auf TRUE gesetzt (sofern `RESET1` nicht aktiv ist). |
| **RESET1** | AX | Socket (Eingang) | Der Rücksetz-Eingang. Wenn aktiv, wird der Ausgang `Q1` auf FALSE gesetzt. Dieser Eingang hat Priorität vor `SET`. |

## Funktionsweise

Der **AX_FB_RS** implementiert die Logik eines RS-Flip-Flops mit Reset-Dominanz. Der interne Zustand und der Ausgang `Q1` werden basierend auf den Eingangswerten der Adapter `SET` und `RESET1` berechnet.

Die logische Funktion lautet:
`Q1 := (NOT RESET1) AND (SET OR Q1)`

Das Verhalten lässt sich wie folgt zusammenfassen:
1.  **Rücksetzen:** Wenn `RESET1.D1` TRUE ist, wird `Q1.D1` sofort FALSE, unabhängig vom Zustand von `SET.D1`.
2.  **Setzen:** Wenn `SET.D1` TRUE ist und `RESET1.D1` FALSE ist, wird `Q1.D1` TRUE.
3.  **Speichern:** Wenn sowohl `SET.D1` als auch `RESET1.D1` FALSE sind, behält `Q1.D1` seinen vorherigen Zustand bei.

Sobald ein Ereignis (`E1`) an einem der Eingangs-Adapter (`SET` oder `RESET1`) empfangen wird, führt der Baustein den Algorithmus aus und feuert anschließend ein Ereignis am Ausgangs-Adapter `Q1.E1`.

## Technische Besonderheiten

*   **Adapter-Technologie:** Durch die Verwendung von `AX`-Adaptern reduziert der Baustein die visuelle Komplexität in 4diac-Anwendungen, da für das Paar aus Ereignis und booleschem Wert nur eine Verbindungslinie gezogen werden muss.
*   **Ereignisgesteuert:** Der Algorithmus wird bei Eintreffen eines Events über den `SET`- oder `RESET1`-Adapter ausgelöst.
*   **Reset-Dominanz:** Dies ist ein sicherheitsrelevantes Merkmal. Im Falle eines Konflikts (beide Eingänge TRUE) schaltet der Ausgang sicher ab (FALSE).

## Zustandsübersicht

Der Baustein basiert auf einem einfachen ECC (Execution Control Chart) mit einem einzigen Hauptzustand.

*   **Zustandsname:** `REQ`
*   **Aktion:** Führt den Algorithmus `REQ` aus und sendet ein Ereignis über `Q1.E1`.
*   **Transitionen:**
    *   Der Zustand `REQ` hat Selbstübergänge (Self-Loops), die durch das Eintreffen von Ereignissen an den Adaptern `SET.E1` oder `RESET1.E1` ausgelöst werden.

Dies bedeutet, dass der Baustein immer bereit ist, Eingangssignale zu verarbeiten und sofort darauf zu reagieren.

## Anwendungsszenarien

*   **Motorsteuerungen (Start/Stop):** Typische Anwendung für Start- (Set) und Stop-Taster (Reset), wobei der Stop-Taster aus Sicherheitsgründen Vorrang hat (Not-Halt-Logik).
*   **Alarm-Speicher:** Ein Alarm wird gesetzt und bleibt bestehen, bis er explizit zurückgesetzt (quittiert) wird.
*   **Zustandsmerker:** Speichern von binären Zuständen innerhalb einer adapterbasierten Steuerungslogik.
*   **Modulare Systeme:** Einsatz in Systemen, die konsequent auf Adapter-Schnittstellen setzen, um "Spaghetti-Code" in der grafischen Darstellung zu vermeiden.

## Vergleich mit ähnlichen Bausteinen

| Merkmal | AX_FB_RS | AX_FB_SR | RS (Standard) |
| :--- | :--- | :--- | :--- |
| **Dominanz** | **Reset-Dominant** (Ausgang FALSE bei S=1, R=1) | Set-Dominant (Ausgang TRUE bei S=1, R=1) | Reset-Dominant |
| **Schnittstelle** | Adapter (`AX`) | Adapter (`AX`) | Boolesche Ereignis-/Datenports |
| **Verdrahtung** | Minimalistisch (gebündelt) | Minimalistisch (gebündelt) | Klassisch (getrennte Leitungen) |

## Fazit

Der **AX_FB_RS** ist eine moderne, adapterbasierte Implementierung des klassischen RS-Flip-Flops. Er eignet sich hervorragend für komplexe Steuerungsanwendungen in 4diac, bei denen Übersichtlichkeit und Kapselung von Signalen im Vordergrund stehen. Durch die integrierte Reset-Dominanz ist er besonders für Anwendungen geeignet, bei denen das sichere Abschalten Vorrang vor dem Einschalten haben muss.