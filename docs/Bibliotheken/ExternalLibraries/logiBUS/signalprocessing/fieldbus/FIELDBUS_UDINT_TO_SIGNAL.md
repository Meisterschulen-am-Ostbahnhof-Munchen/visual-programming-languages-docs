# FIELDBUS_UDINT_TO_SIGNAL


![FIELDBUS_UDINT_TO_SIGNAL](./FIELDBUS_UDINT_TO_SIGNAL.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **FIELDBUS_UDINT_TO_SIGNAL** dient dazu, einen eingehenden UDINT-Wert auf Gültigkeit zu prüfen und diesen bei bestandener Prüfung unverändert an den Ausgang weiterzuleiten. Ist der Wert ungültig, wird der Ausgang auf einen definierten Fehlerwert (0) gesetzt und die Gültigkeitsanzeige deaktiviert. Der Baustein wird typischerweise in der Feldbus-Signalverarbeitung eingesetzt, um nur valide Mess- oder Steuerwerte an nachfolgende Logik weiterzugeben.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Event | Beschreibung |
|-------|--------------|
| REQ   | Normaler Ausführungsanforderung; löst die Verarbeitung des Eingangs IN aus. |

### **Ereignis-Ausgänge**

| Event | Beschreibung |
|-------|--------------|
| CNF   | Bestätigt die abgeschlossene Verarbeitung. Wird nach dem Algorithmus ausgelöst. |

### **Daten-Eingänge**

| Name | Typ   | Initialwert                                    | Beschreibung |
|------|-------|------------------------------------------------|--------------|
| IN   | UDINT | `DWORD_TO_UDINT(NOT_AVAILABLE_DWM)`            | Der zu prüfende Eingangswert. |

### **Daten-Ausgänge**

| Name  | Typ   | Initialwert | Beschreibung |
|-------|-------|-------------|--------------|
| OUT   | UDINT | `16#00000000` | Der gefilterte Ausgangswert. Bei gültigem Signal entspricht er IN, sonst 0. |
| VALID | BOOL  | FALSE       | TRUE, wenn das Signal gültig ist, d.h. IN innerhalb des gültigen Bereichs liegt. |

### **Adapter**
Keine.

## Funktionsweise
Sobald ein Ereignis am Eingang **REQ** eintrifft, wird der Algorithmus ausgeführt:
1. Der Wert von **IN** wird mit dem vordefinierten Grenzwert `VALID_SIGNAL_DW` verglichen.
2. Falls **IN** kleiner oder gleich diesem Grenzwert ist, wird **OUT** auf **IN** gesetzt und **VALID** auf `TRUE`.
3. Andernfalls wird **OUT** auf `0` (UDINT) gesetzt und **VALID** auf `FALSE`.

Der Grenzwert `VALID_SIGNAL_DW` sowie der Initialwert `NOT_AVAILABLE_DWM` sind als Konstanten aus dem Paket `eclipse4diac::signalprocessing::FIELDBUS_SIGNAL` importiert. Sie repräsentieren einen maximal zulässigen Signalwert bzw. einen „nicht verfügbar“-Marker.

## Technische Besonderheiten
- **Datentyp** – Der Baustein arbeitet ausschließlich mit dem Typ `UDINT` (Unsigned Double Integer, 32 Bit).
- **Initialwert** – Der Eingang IN wird standardmäßig auf den Wert `NOT_AVAILABLE_DWM` gesetzt. Dieser wird über die Funktion `DWORD_TO_UDINT` aus einem vorher definierten DWORD konvertiert.
- **Grenzwert** – Die Gültigkeit wird durch einen einfachen Vergleich mit der importierten Konstanten `VALID_SIGNAL_DW` bestimmt. Alle Werte ≤ diesem Grenzwert gelten als gültig.
- **Einfache Zustandslogik** – Der FB besteht aus genau einem Zustand (REQ) und führt bei jeder Anforderung den Algorithmus aus.

## Zustandsübersicht
Der Funktionsblock ist als einfacher FB (SimpleFB) realisiert und besitzt nur einen einzigen Zustand:

| Zustand | Aktion      | Ausgangsereignis |
|---------|-------------|------------------|
| REQ     | Algorithmus REQ | CNF              |

Es findet keine Zustandsmaschine mit mehreren Schritten oder Verzweigungen statt.

## Anwendungsszenarien
- **Feldbus-Signalaufbereitung** – In Automatisierungssystemen, bei denen UDINT-Werte über einen Feldbus eingehen, wird der Baustein genutzt, um ungültige oder außerhalb des gültigen Bereichs liegende Werte zu filtern (z. B. bei Sensordaten, die einen Maximalwert nicht überschreiten dürfen).
- **Landtechnik** – Ursprünglich für den Einsatz in landwirtschaftlichen Steuerungen entwickelt (z. B. HR Agrartechnik), um analoge Messwerte wie Drehzahlen oder Drücke auf Gültigkeit zu prüfen.
- **Qualitätssicherung** – Vorverarbeitung von Messdaten, bevor sie in Regelkreise oder Protokollierungen einfließen.

## Vergleich mit ähnlichen Bausteinen
- **FIELDBUS_DINT_TO_SIGNAL** – Analoger Baustein für vorzeichenbehaftete 32‑Bit‑Werte (DINT).
- **FIELDBUS_BOOL_TO_SIGNAL** – Vergleichbarer Baustein für boolesche Signale; dort entfällt die Schwellwertprüfung.
- **FIELDBUS_REAL_TO_SIGNAL** – Für Gleitkommazahlen, mit gegebenenfalls anderer Toleranzlogik.

Der vorliegende Baustein ist speziell auf den Datentyp UDINT zugeschnitten und nutzt einen einfachen absoluten Grenzwert zur Validierung.

## Fazit
**FIELDBUS_UDINT_TO_SIGNAL** ist ein kompakter und effizienter Funktionsblock zur Filterung von UDINT-Feldbussignalen. Durch die klare Trennung in gültige und ungültige Werte sowie die einfache Schnittstelle eignet er sich gut für robuste Automatisierungslösungen. Die Verwendung von importierten Konstanten erhöht die Wiederverwendbarkeit und Anpassbarkeit an verschiedene Feldbusprotokolle.