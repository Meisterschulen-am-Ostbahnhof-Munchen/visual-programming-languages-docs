# ILOCK_SWITCH_AX


![ILOCK_SWITCH_AX](./ILOCK_SWITCH_AX.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *

## Einleitung

Der Funktionsblock **ILOCK_SWITCH_AX** realisiert eine verriegelnde Weichensteuerung für bidirektionale Achsen. Er priorisiert den zuletzt aktiven Eingang und stellt sicher, dass nie beide Richtungen gleichzeitig aktiviert werden. Die Kommunikation erfolgt ausschließlich über Adapter-Schnittstellen vom Typ `adapter::types::unidirectional::AX`. Diese Version ist speziell für den Einsatz in modularen Steuerungssystemen mit standardisierten Adaptern konzipiert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine (sämtliche Ereignisse werden über die Adapter-Sockets übertragen).

### **Ereignis-Ausgänge**

Keine (sämtliche Ereignisse werden über die Adapter-Plugs übertragen).

### **Daten-Eingänge**

Keine (sämtliche Daten werden über die Adapter-Sockets übertragen).

### **Daten-Ausgänge**

Keine (sämtliche Daten werden über die Adapter-Plugs übertragen).

### **Adapter**

| Name | Typ | Richtung | Kommentar |
|------|-----|----------|-----------|
| UP_IN | `adapter::types::unidirectional::AX` | Socket | Eingang für Vorwärts-/Aufwärts-Richtung |
| DOWN_IN | `adapter::types::unidirectional::AX` | Socket | Eingang für Rückwärts-/Abwärts-Richtung |
| UP_OUT | `adapter::types::unidirectional::AX` | Plug | Ausgang für Vorwärts-/Aufwärts-Richtung |
| DOWN_OUT | `adapter::types::unidirectional::AX` | Plug | Ausgang für Rückwärts-/Abwärts-Richtung |

Jeder Adapter stellt einen Ereignisausgang `E1` und einen Daten-Eingang/Ausgang `D1` (vom Typ BOOL) bereit. Die Sockets empfangen Anforderungen, die Plugs geben die geschalteten Zustände weiter.

## Funktionsweise

Die Logik wird durch einen endlichen Zustandsautomaten (ECC) realisiert. Der FB befindet sich zunächst im Zustand `STOP`. Ein Wechsel in die Zustände `UP` oder `DOWN` erfolgt, wenn der entsprechende Socket ein Ereignis `E1` mit gesetztem Datenwert `D1` liefert (d.h. `UP_IN.E1[UP_IN.D1]` oder `DOWN_IN.E1[DOWN_IN.D1]`).

- Im Zustand `UP` wird `UP_OUT.D1` auf `TRUE` und `DOWN_OUT.D1` auf `FALSE` gesetzt.
- Im Zustand `DOWN` wird `DOWN_OUT.D1` auf `TRUE` und `UP_OUT.D1` auf `FALSE` gesetzt.

Ein Wechsel vom aktuellen Zustand in den jeweils anderen ist nur möglich, wenn der andere Socket aktiv wird (Priorisierung des letzten aktiven Eingangs). Dabei werden die Bedingungen differenziert:
- **UP → DOWN**: entweder direkt durch `DOWN_IN.E1[DOWN_IN.D1]` oder wenn der eigene Eingang wegfällt und der andere aktiv ist (`UP_IN.E1[NOT UP_IN.D1 AND DOWN_IN.D1]`).
- **DOWN → UP**: analog durch `UP_IN.E1[UP_IN.D1]` oder `DOWN_IN.E1[NOT DOWN_IN.D1 AND UP_IN.D1]`.

Fällt der aktive Eingang weg, ohne dass der andere aktiv wird, wird ein Zwischenzustand (`UP_STOP` bzw. `DOWN_STOP`) erreicht. Dort werden die Ausgänge auf `FALSE` gesetzt, und anschließend wechselt der Automat sofort in den `STOP`-Zustand.

## Technische Besonderheiten

- **Adapterbasierte Schnittstelle**: Der Funktionsblock verwendet ausschließlich Adapter des Typs `unidirectional::AX`, was eine saubere Kapselung von Ereignis- und Datenkommunikation ermöglicht und die Wiederverwendung in verschiedenen Kontexten erleichtert.
- **Priorisierung des letzten aktiven Eingangs**: Im Gegensatz zu einem einfachen Zustandsautomaten, der nur auf steigende Flanken reagiert, wird hier das zuletzt gesendete gültige Signal berücksichtigt.
- **Sichere Verriegelung**: Durch die ECC-Struktur ist ausgeschlossen, dass beide Ausgänge gleichzeitig `TRUE` werden.
- **Explizite Stop-Zwischenzustände**: Die Zustände `UP_STOP` und `DOWN_STOP` gewährleisten eine definierte Reaktion auf das Verschwinden eines Steuersignals, bevor in den Ruhezustand zurückgekehrt wird.

## Zustandsübersicht

| Zustand | UP_OUT.D1 | DOWN_OUT.D1 | Beschreibung |
|---------|-----------|-------------|--------------|
| `STOP` | FALSE | FALSE | Ruhezustand, keine Richtung aktiv |
| `UP` | TRUE | FALSE | Vorwärts-/Aufwärts-Richtung aktiv |
| `DOWN` | FALSE | TRUE | Rückwärts-/Abwärts-Richtung aktiv |
| `UP_STOP` | FALSE | FALSE | Zwischenzustand nach Verlassen von UP |
| `DOWN_STOP` | FALSE | FALSE | Zwischenzustand nach Verlassen von DOWN |

## Anwendungsszenarien

- **Steuerung von Hub-/Senkantrieben** (z.B. Hebezeug, Hydraulikzylinder) – verhindert gleichzeitiges Heben und Senken.
- **Verriegelung von Weichen** in Fördersystemen – priorisiert die jeweils letzte Anforderung.
- **Sicherheitsgerichtete Umschaltung** in modularen Automatisierungsanlagen, bei denen ein Adapter-basiertes Datenmodell verwendet wird (z.B. logiBUS).

## Vergleich mit ähnlichen Bausteinen

- **ILOCK_SWITCH** (ohne Adapter): Bietet ähnliche Verriegelungslogik, verwendet aber direkte Ereignis- und Datenports. Die Adapter-Version `ILOCK_SWITCH_AX` erlaubt eine einfachere Kopplung an standardisierte Schnittstellen und ist besser für hierarchische Architekturen geeignet.
- **SR-Flipflop** (Set-Reset): Kann ebenfalls zwei Zustände verriegeln, priorisiert aber immer den Set- oder Reset-Eingang (je nach Implementierung) und nicht den zuletzt aktiven.

## Fazit

Der Funktionsblock `ILOCK_SWITCH_AX` bietet eine robuste, adapterbasierte Verriegelung für bidirektionale Steuerungen. Durch die Zustandsautomatik wird stets nur eine Richtung aktiv geschaltet, wobei die Priorität dem zuletzt eingehenden Befehl zufällt. Die saubere Trennung von Ereignis- und Datenkanälen sowie die definierten Stop-Zustände machen ihn zu einem zuverlässigen Baustein in sicherheitskritischen Anwendungen.