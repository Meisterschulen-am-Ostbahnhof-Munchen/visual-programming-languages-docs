# AI_TO_AX


![AI_TO_AX](./AI_TO_AX.svg)

* * * * * * * * * *
## Einleitung

Der Baustein `AI_TO_AX` ist ein Composite-Funktionsblock (Typ-Adapter), der eine unidirektionale Schnittstelle eines INT-Adapters (`AI`) in eine entsprechende BOOL-Schnittstelle eines Adapters (`AX`) umwandelt. Er dient dazu, analoge Integer-Signale (z. B. aus Sensoren) in binäre Boolesche Werte zu überführen, die beispielsweise für Schaltsignale oder Alarmmeldungen genutzt werden können.

## Schnittstellenstruktur

Der Baustein besitzt lediglich Adapter-Anschlüsse (Socket und Plug), über die Ereignisse und Daten fließen. Die nachfolgende Tabelle fasst die logischen Ein‑/Ausgänge zusammen, die sich aus den verbundenen Adaptern ergeben.

### **Ereignis-Eingänge**

| Bezeichnung | Datentyp | Beschreibung |
|-------------|----------|--------------|
| `AI_IN.E1`  | EVENT    | Eingangsereignis, das die Konvertierung anstößt. |

### **Ereignis-Ausgänge**

| Bezeichnung | Datentyp | Beschreibung |
|-------------|----------|--------------|
| `AX_OUT.E1` | EVENT    | Ausgangsereignis, das nach abgeschlossener Konvertierung gesendet wird. |

### **Daten-Eingänge**

| Bezeichnung | Datentyp | Beschreibung |
|-------------|----------|--------------|
| `AI_IN.D1`  | INT      | Analoger Integer-Eingangswert (z. B. 0…32767). |

### **Daten-Ausgänge**

| Bezeichnung | Datentyp | Beschreibung |
|-------------|----------|--------------|
| `AX_OUT.D1` | BOOL     | Boolescher Ausgangswert: `TRUE` wenn der Eingangswert ungleich 0 ist, sonst `FALSE`. |

### **Adapter**

| Typ        | Name     | Richtung |
|------------|----------|----------|
| `AI` (Eingangs-Adapter) | `AI_IN`  | Socket   |
| `AX` (Ausgangs-Adapter) | `AX_OUT` | Plug     |

## Funktionsweise

Der Baustein nutzt intern den IEC‑61131‑Vergleichsbaustein `F_NE` (Not Equal). Sobald am Ereigniseingang `AI_IN.E1` ein Ereignis eintrifft, wird `F_NE.REQ` getriggert. Dieser vergleicht den über `AI_IN.D1` anliegenden INT-Wert mit dem konstanten Wert `INT#0`.

- Ist der Eingangswert **ungleich 0**, so liefert `F_NE.OUT` den Wert `TRUE`.
- Ist der Eingangswert **gleich 0**, so liefert `F_NE.OUT` den Wert `FALSE`.

Das Ergebnis wird an den Datenausgang `AX_OUT.D1` weitergegeben und gleichzeitig das Ereignis `AX_OUT.E1` ausgelöst, um nachgelagerte Bausteine zu benachrichtigen.

## Technische Besonderheiten

- **Composite-Baustein:** Der `AI_TO_AX` besteht aus verschalteten Grundbausteinen, wodurch er als wiederverwendbare Komponente in verschiedenen Projekten eingesetzt werden kann.
- **Verwendung von IEC‑61131‑Bausteinen:** Die Vergleichslogik wird durch den standardisierten Baustein `F_NE` realisiert, was Portabilität und Einhaltung der Norm unterstützt.
- **Kein eigenständiger Zustand:** Der Baustein ist zustandslos – jeder Ereignis-Impuls erzeugt eine aktuelle Berechnung ohne Speicherung von Zwischenwerten.

## Zustandsübersicht

Der Baustein besitzt keinen expliziten Endlichen Automaten. Die interne Logik ist rein kombinatorisch: Nach Eintreffen eines Ereignisses werden die Daten sofort verarbeitet und das Ergebnis ausgegeben.

## Anwendungsszenarien

- **Analog-Digital-Umwandlung auf Signalebene:** Ein analoger Messwert (z. B. Drucksensor, Temperaturfühler) wird in ein „Ein/Aus“-Signal umgesetzt – z. B. Aktivierung einer Pumpe bei Drucküberschreitung.
- **Schwellwertentscheidung:** Der Baustein kann als einfache Ungleich-Null-Erkennung eingesetzt werden, um z. B. die Anwesenheit eines Signals oder einen aktivierten Zählerstand zu signalisieren.
- **Adapter-Kopplung:** In Systemen, die unterschiedliche Adapterschnittstellen nutzen, ermöglicht `AI_TO_AX` die nahtlose Verbindung zwischen INT- und BOOL‑basierten Komponenten.

## Vergleich mit ähnlichen Bausteinen

- **Direkte Vergleichsbausteine (z. B. F_EQ, F_GT):** Diese liefern Boolesche Ergebnisse für beliebige Vergleiche, benötigen aber zwei Eingänge und sind nicht als Adapter-Konverter ausgelegt.
- **Eigene Adapter‑Wrapper:** Entwickler könnten selbst eine Kapselung vornehmen; der `AI_TO_AX` bietet jedoch eine standardisierte, sofort einsetzbare Lösung mit geringerem Entwicklungsaufwand.
- **Typ‑Konverter ohne Ereignissteuerung:** Manche Konverter arbeiten kontinuierlich ohne Ereignis‑Auslöser; der `AI_TO_AX` hingegen reagiert nur auf Ereignisse und ist daher besser in ereignisgesteuerte Architekturen integrierbar.

## Fazit

Der `AI_TO_AX` ist ein praktischer Composite-Baustein, der die Umwandlung von INT-Adapter-Signalen in BOOL-Adapter-Signale vereinfacht. Er eignet sich hervorragend für Anwendungen, in denen analoge Messwerte als binäre Zustände interpretiert werden müssen, und fügt sich dank der ereignisgesteuerten Verarbeitung nahtlos in IEC‑61499‑basierte Automatisierungssysteme ein.