# AI_SPLIT_6

## Einleitung


![AI_SPLIT_6](./AI_SPLIT_6.svg)

Der Funktionsblock **AI_SPLIT_6** dient als generischer Splitter, der einen analogen Eingangswert (AI) auf sechs identische Ausgänge verteilt. Er realisiert eine 1:6-Verteilung eines AI-Adapters, ohne dass Daten oder Ereignisse modifiziert werden. Der Baustein ist als generischer FB (GenericClassName: `GEN_AI_SPLIT`) definiert und arbeitet rein adapterbasiert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine Ereignis-Eingänge vorhanden.

### **Ereignis-Ausgänge**

Keine Ereignis-Ausgänge vorhanden.

### **Daten-Eingänge**

Keine Daten-Eingänge vorhanden.

### **Daten-Ausgänge**

Keine Daten-Ausgänge vorhanden.

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| Eingang (Socket) | IN | `adapter::types::unidirectional::AI` | Einzige analoge Eingangsadapter (Quelle) |
| Ausgang (Plug) | OUT1 | `adapter::types::unidirectional::AI` | Erster Ausgang (1:1-Weiterleitung von IN) |
| Ausgang (Plug) | OUT2 | `adapter::types::unidirectional::AI` | Zweiter Ausgang |
| Ausgang (Plug) | OUT3 | `adapter::types::unidirectional::AI` | Dritter Ausgang |
| Ausgang (Plug) | OUT4 | `adapter::types::unidirectional::AI` | Vierter Ausgang |
| Ausgang (Plug) | OUT5 | `adapter::types::unidirectional::AI` | Fünfter Ausgang |
| Ausgang (Plug) | OUT6 | `adapter::types::unidirectional::AI` | Sechster Ausgang |

## Funktionsweise

Der Baustein besitzt keinerlei interne Logik oder Zustandsautomaten. Er fungiert als passiver Splitter: Der am Socket **IN** anliegende AI-Adapter wird unverändert an alle sechs Plug-Ausgänge **OUT1** bis **OUT6** dupliziert. Änderungen am AI-Wert (z. B. Messwert oder Status) an der Quelle werden sofort und gleichzeitig an allen Ausgängen sichtbar.

## Technische Besonderheiten

- **Generischer FB**: Der Baustein ist mittels `eclipse4diac::core::GenericClassName` als `GEN_AI_SPLIT` markiert. Dadurch kann er je nach Laufzeitumgebung parametrisiert oder instanziiert werden, ohne seine grundlegende Splitterfunktion zu ändern.
- **Reine Adapter‑Kopplung**: Es werden weder Ereignisse noch Datenport‑Variablen verwendet, sondern ausschließlich unidirektionale Adapter des Typs `adapter::types::unidirectional::AI`. Dies reduziert den Overhead und ermöglicht eine direkte Verschaltung mit anderen AI‑Adapter‑Bausteinen.
- **Keine Zustände**: Da kein ECC (Execution Control Chart) vorhanden ist, benötigt der FB keine Algorithmen oder Zustandsübergänge. Die Weiterleitung erfolgt rein strukturell.

## Zustandsübersicht

Der Baustein besitzt keine Zustandsmaschine (ECC) und führt keine aktiven Operationen aus. Es gibt keine unterscheidbaren Betriebszustände.

## Anwendungsszenarien

- **Verteilung eines analogen Sensorsignals**: Ein einzelner analoger Eingang (z. B. 4‑20 mA‑Messumformer) soll parallel an mehrere Steuerungsfunktionen oder Anzeigeeinheiten weitergegeben werden.
- **Redundanz / Plausibilisierung**: Derselbe Messwert wird auf mehrere parallel arbeitende Auswerte‑Bausteine geführt, die z. B. eine Mittelwertbildung oder Fehlererkennung durchführen.
- **Simulation und Test**: Ein simulierter AI‑Adapter wird auf mehrere Testbausteine verteilt, um das Systemverhalten unter Last zu prüfen.

## Vergleich mit ähnlichen Bausteinen

- **AI_SPLIT_2 / AI_SPLIT_4**: Diese Bausteine teilen einen AI‑Eingang auf zwei bzw. vier Ausgänge. **AI_SPLIT_6** stellt die Variante mit sechs Ausgängen dar. Alle Splitter haben identische Funktionsweise und unterscheiden sich nur in der Anzahl der Ausgangsadapter.
- **AI_DUPLICATE (hypothetisch)**: Ein Baustein, der den Wert zu Kopierzwecken dupliziert, jedoch meist mit Datenports arbeitet. AI_SPLIT_6 nutzt dagegen ausschließlich Adapter, was die direkte Kopplung ohne zusätzliche Ereignissteuerung erlaubt.

## Fazit

Der **AI_SPLIT_6** ist ein minimaler, aber nützlicher Baustein zur Verteilung analoger Adaptersignale in der 4diac‑IDE. Seine generische Definition und die reine Adapter‑Schnittstelle machen ihn besonders geeignet für Architekturen, die eine lose Kopplung und einfache Erweiterbarkeit erfordern. Durch die Aufteilung auf sechs Ausgänge wird eine flexible Mehrfachnutzung eines analogen Eingangswerts ermöglicht.