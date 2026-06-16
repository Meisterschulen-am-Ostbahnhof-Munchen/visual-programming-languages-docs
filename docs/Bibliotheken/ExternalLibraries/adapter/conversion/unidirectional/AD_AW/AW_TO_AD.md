# AW_TO_AD


![AW_TO_AD](./AW_TO_AD.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein **AW_TO_AD** ist ein zusammengesetzter Baustein (Composite FB), der einen unidirektionalen WORD-Adapter (AW) in einen unidirektionalen DWORD-Adapter (AD) umwandelt. Er dient als Schnittstellenkonverter und ermöglicht die Anbindung von Komponenten, die unterschiedliche Adaptertypen verwenden. Der FB leitet Ereignisse und Daten direkt vom Eingangs- zum Ausgangsadapter weiter, wobei implizit eine Typkonvertierung von 16‑Bit-WORD auf 32‑Bit-DWORD erfolgt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **AW_IN.E1** – Ereigniseingang über den Socket `AW_IN`. Ein eingehendes Ereignis wird direkt an den Ausgang weitergeleitet.

### **Ereignis-Ausgänge**
- **AD_OUT.E1** – Ereignisausgang über den Plug `AD_OUT`. Das vom Eingang durchgereichte Ereignis wird hier ausgegeben.

### **Daten-Eingänge**
- **AW_IN.D1** – Dateneingang (Typ: WORD, 16 Bit) über den Socket `AW_IN`.

### **Daten-Ausgänge**
- **AD_OUT.D1** – Datenausgang (Typ: DWORD, 32 Bit) über den Plug `AD_OUT`. Die empfangenen 16 Bit werden auf die unteren 16 Bit des DWORD abgebildet; die oberen 16 Bit werden mit Nullen aufgefüllt (implizite Konvertierung).

### **Adapter**

| Name | Typ | Richtung | Beschreibung |
|------|-----|----------|--------------|
| `AW_IN` | `adapter::types::unidirectional::AW` | Socket (Eingang) | WORD-Adapter, der Ereignis‑ und Dateneingänge bereitstellt |
| `AD_OUT` | `adapter::types::unidirectional::AD` | Plug (Ausgang) | DWORD-Adapter, der Ereignis‑ und Datenausgänge bereitstellt |

## Funktionsweise

Der Baustein ist als reine Weiterleitung konzipiert. Im internen FBNetzwerk sind die Ereignis- und Datenleitungen zwischen `AW_IN` und `AD_OUT` direkt verbunden:

- Ein Ereignis an `AW_IN.E1` wird sofort an `AD_OUT.E1` durchgereicht.
- Der 16‑Bit-Datenwert von `AW_IN.D1` wird auf `AD_OUT.D1` übertragen. Dabei erfolgt eine implizite Erweiterung auf 32 Bit: Der WORD-Wert wird in die niederwertigen 16 Bit des DWORD kopiert, die höherwertigen Bit werden auf `0` gesetzt.

Es findet keine eigene Verarbeitung oder Zwischenspeicherung statt – der FB fungiert als einfacher Adapter-Konverter.

## Technische Besonderheiten

- **Composite FB ohne eigene Zustandslogik:** Der Baustein besitzt keinen ECC (Execution Control Chart) und arbeitet zustandslos. Alle Abläufe werden durch die direkten Verbindungen im FBNetzwerk bestimmt.
- **Unidirektionale Richtung:** Die Konvertierung erfolgt nur in eine Richtung (AW → AD). Für die umgekehrte Richtung wäre ein separater Baustein erforderlich.
- **Implizite Typkonvertierung:** Die Daten werden ohne explizite Konvertierungslogik von WORD nach DWORD gecastet. Falls eine andere Abbildung (z. B. Vorzeichenbehandlung) gewünscht wird, muss ein eigener Funktionsbaustein verwendet werden.
- **Paket & Lizenz:** Der Baustein ist im Paket `adapter::conversion::unidirectional` unter der Eclipse Public License 2.0 verfügbar.

## Zustandsübersicht

Da der FB als Composite ohne ECC realisiert ist, existiert kein interner Zustandsautomat. Die gesamte Funktionalität erschöpft sich in der direkten Durchleitung von Ereignissen und Daten. Der FB ist daher **zustandslos** und reagiert sofort auf jedes eingehende Ereignis.

## Anwendungsszenarien

- **Schnittstellenmigration:** Austausch einer Komponente, die einen WORD-Adapter erwartet, gegen eine Komponente mit DWORD-Adapter.
- **Systemintegration:** Anbindung eines bestehenden WORD‑basierten Moduls an eine DWORD‑basierte Steuerung.
- **Protokollanpassung:** Wenn ein Subsystem Daten im WORD‑Format liefert, das Ziel jedoch einen DWORD‑Eingang benötigt.
- **Test und Simulation:** Einfache Konvertierung für Testzwecke, ohne komplexe Logik implementieren zu müssen.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Beschreibung |
|----------|--------------|
| `WORD_TO_DWORD` | Reine Datenkonvertierung ohne Adapter-Schnittstelle |
| `AW_TO_AD` | Konvertiert komplette unidirektionale Adapter (Ereignis + Daten) |
| `AD_TO_AW` (nicht vorhanden) | Theoretischer Baustein für die umgekehrte Richtung |

Im Gegensatz zu einem reinen Datenkonverter berücksichtigt `AW_TO_AD` auch die Ereignisweiterleitung und ist direkt in Adapter-basierte Architekturen integrierbar.

## Fazit

`AW_TO_AD` ist ein einfacher, aber nützlicher Composite-Funktionsbaustein zur Adapter-Konvertierung von WORD nach DWORD. Er ermöglicht eine schnelle und saubere Anpassung von Schnittstellen in 4diac‑Projekten, ohne dass eigene Konvertierungslogik geschrieben werden muss. Aufgrund seiner Zustandslosigkeit und der direkten Durchleitung eignet er sich besonders für unidirektionale Verbindungen in bestehenden Automatisierungslösungen.