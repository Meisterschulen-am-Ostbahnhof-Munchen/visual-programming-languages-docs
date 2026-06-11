# AI_TO_AUDI


![AI_TO_AUDI](./AI_TO_AUDI.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `AI_TO_AUDI` ist ein Composite-Baustein, der einen **AI-Adapter** (Daten vom Typ `INT`) in einen **AUDI-Adapter** (Daten vom Typ `UDINT`) umwandelt. Er dient als unidirektionale Schnittstelle zwischen unterschiedlichen Adaptertypen und ermöglicht eine nahtlose Datenkonvertierung innerhalb der 4diac-IDE.

## Schnittstellenstruktur

Der Baustein besitzt keine klassischen Ereignis- und Datenein-/ausgänge, sondern realisiert seine Ein- und Ausgaben über **Adapter-Schnittstellen**. Folgende Ports sind über die internen Adapter verfügbar:

### Ereignis-Eingänge

| Port   | Adapter | Beschreibung                              |
|--------|---------|-------------------------------------------|
| `E1`   | `AI_IN` | Startet die Konvertierung des INT-Wertes. |

### Ereignis-Ausgänge

| Port   | Adapter   | Beschreibung                              |
|--------|-----------|-------------------------------------------|
| `E1`   | `AUDI_OUT`| Signalisiert Abschluss der Konvertierung. |

### Daten-Eingänge

| Port   | Adapter | Datentyp | Beschreibung                     |
|--------|---------|----------|----------------------------------|
| `D1`   | `AI_IN` | `INT`    | Zu konvertierender Integer-Wert. |

### Daten-Ausgänge

| Port   | Adapter   | Datentyp | Beschreibung                   |
|--------|-----------|----------|--------------------------------|
| `D1`   | `AUDI_OUT`| `UDINT`  | Konvertierter unsigned Integer. |

### Adapter

| Richtung | Name       | Typ                          | Beschreibung                 |
|----------|------------|------------------------------|-----------------------------|
| Socket   | `AI_IN`    | `adapter::types::unidirectional::AI`    | Eingangsadapter (INT).      |
| Plug     | `AUDI_OUT` | `adapter::types::unidirectional::AUDI`  | Ausgangsadapter (UDINT).    |

## Funktionsweise

Der Baustein ist als Composite-FB realisiert. Intern nutzt er den Standard-Konvertierungsbaustein `iec61131::conversion::F_INT_TO_UDINT`.

**Ablauf:**

1. Am Socket `AI_IN` trifft ein Ereignis am Eingang `E1` ein, begleitet von einem INT-Wert an `D1`.
2. Dieses Ereignis wird an den internen Baustein `Convert` (Typ `F_INT_TO_UDINT`) weitergeleitet.
3. Der interne Baustein führt die Typkonvertierung von `INT` nach `UDINT` durch (gemäß IEC 61131-3).
4. Nach erfolgreicher Konvertierung wird ein Ereignis am Ausgang `CNF` des internen Bausteins erzeugt.
5. Dieses Ereignis wird an den Plug `AUDI_OUT` (Ereignisausgang `E1`) weitergegeben, gleichzeitig liegt der konvertierte UDINT-Wert am Datenausgang `D1` an.

Die Verbindungen im FBNetwork sind:
- `AI_IN.E1` → `Convert.REQ`
- `Convert.CNF` → `AUDI_OUT.E1`
- `AI_IN.D1` → `Convert.IN`
- `Convert.OUT` → `AUDI_OUT.D1`

## Technische Besonderheiten

- **Composite-Baustein:** Vereinfacht die Wiederverwendung und Kapselung der Konvertierungslogik.
- **Standardkonvertierung:** Verwendet den IEC 61131-3 Baustein `F_INT_TO_UDINT`, der eine saubere und portable Typumwandlung gewährleistet.
- **Unidirektionale Adapter:** Sowohl der Eingangs- als auch der Ausgangsadapter sind als unidirektionale Schnittstellen (Socket bzw. Plug) ausgeführt – die Daten fließen nur in eine Richtung.
- **Ereignisgesteuert:** Die Konvertierung wird durch ein Ereignis am Eingangsadapter ausgelöst und durch ein Ereignis am Ausgangsadapter quittiert (Handshake-Prinzip).

## Zustandsübersicht

Der Baustein selbst besitzt keine eigene Zustandsmaschine, da er ausschließlich aus einer direkten Verkettung von Adapterports und dem internen Konvertierungsbaustein besteht. Der interne FB `F_INT_TO_UDINT` führt die Konvertierung in einem Schritt aus – eine Zustandsübersicht entfällt daher.

## Anwendungsszenarien

- **Datenbrücke zwischen verschiedenen Adaptertypen:** Wenn ein übergeordnetes System oder eine Bibliothek Adapter vom Typ `AI` (mit INT-Daten) bereitstellt, aber nachgelagerte Komponenten einen `AUDI`-Adapter (mit UDINT-Daten) erwarten.
- **Signalanpassung in Automatisierungslösungen:** Zum Beispiel bei der Verarbeitung von Zählerwerten oder Positionsdaten, die als vorzeichenbehaftete 16‑Bit‑Werte ankommen, aber als vorzeichenlose 32‑Bit‑Werte weitergegeben werden müssen.
- **Modulare Adapterkonvertierung:** Einfacher Austausch oder Erweiterung der Konvertierungslogik durch Austausch des internen Bausteins.

## Vergleich mit ähnlichen Bausteinen

Es existieren weitere Adapter-Konvertierungsbausteine in der Bibliothek, z. B.:
- `AI_TO_AI` – weiterleiten ohne Konvertierung
- `AUDI_TO_AI` – umgekehrte Richtung (UDINT → INT)
- Direkte Nutzung des `F_INT_TO_UDINT`-Bausteins mit manueller Adapterverdrahtung

Der Baustein `AI_TO_AUDI` kapselt nicht nur die Typkonvertierung, sondern auch die komplette Adapteranbindung, was den Entwurf übersichtlicher macht und Fehler durch falsche Verdrahtung vermeidet.

## Fazit

Der Composite-Baustein `AI_TO_AUDI` bietet eine einfache, aber saubere Lösung zur Konvertierung eines INT-basierten Adapterprotokolls in ein UDINT-basiertes Protokoll. Durch die Verwendung des genormten IEC‑Bausteins sowie die ereignisgesteuerte Kopplung ist er zuverlässig und leicht in größere 4diac‑Projekte integrierbar.